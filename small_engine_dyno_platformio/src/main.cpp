//Available pins on 8048S070 are 11, 12, 13, 17, 18

#include <Arduino.h>
#include <lvgl.h>
#include <ui.h>
#include <Arduino_GFX_Library.h>
#include "HX711.h"
#define TFT_BL 2 //#define GFX_BL DF_GFX_BL (backlight pin)

Arduino_ESP32RGBPanel *bus = new Arduino_ESP32RGBPanel(
    GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
    41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 42 /* PCLK */,
    14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
    9 /* G0 */, 46 /* G1 */, 3 /* G2 */, 8 /* G3 */, 16 /* G4 */, 1 /* G5 */,
    15 /* B0 */, 7 /* B1 */, 6 /* B2 */, 5 /* B3 */, 4 /* B4 */
);

Arduino_RPi_DPI_RGBPanel *gfx = new Arduino_RPi_DPI_RGBPanel(
    bus,
    800 /* width */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 30 /* hsync_pulse_width */, 16 /* hsync_back_porch */,
    480 /* height */, 0 /* vsync_polarity */, 22 /* vsync_front_porch */, 13 /* vsync_pulse_width */, 10 /* vsync_back_porch */,
    1 /* pclk_active_neg */, 12000000 /* prefer_speed */, true /* auto_flush */
);

#include "touch.h"

//Change to your screen resolution
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

//Display flushing
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p )
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

  #if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
  #else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
  #endif

    lv_disp_flush_ready(disp);
}

//Read the touchpad
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data )
{
    if (touch_has_signal())
    {
      if (touch_touched())
      {
        data->state = LV_INDEV_STATE_PR;

        //Set the coordinates
        data->point.x = touch_last_x;
        data->point.y = touch_last_y;
      }
      else if (touch_released())
      {
        data->state = LV_INDEV_STATE_REL;
      }
    }
    else
    {
      data->state = LV_INDEV_STATE_REL;
    }
}

//Global
#define DOUT  18 // HX711 data pin
#define CLK  17 // HX711 clock pin
#define hallPin 12 // Hall sensor at pin 5
double maxHorsepower = 0; // Just what you'd think, variable to store highest horsepower seen since reset or during run
double maxTorque = 0; //Again, pretty obvious variable
double horsepower; // Declare horsepower variable to be calculated
double torque; // Declare torque variable
double duration; // Declare time variable for engine RPM calculation
long previousMillis = 0; //Declare a time variable to use for the runMode
long runTime = 10000;  //The runMode will last for 10 seconds
long torqueNeedlePos = 0; // Declare torqueNeedlePos variable to rotate torque gauge needles
int rpm; // Declare variable to store engine RPM
int scaleReading; //Declare varible for raw scale data
int horsepowerNeedlePos = 0; // Declare horsepowerNeedlePos variable to rotate horsepower gauge needles
int rpmNeedlePos = 0; // Declare rpmNeedlePos variable to rotate RPM gauge needles
int noWeight; // The varaible for storing the scale output when at zero weight used for calibration
int calibration = 20000; // Variable for storing the raw scale output when 20 pound weight is hung from calibration arm
int maxHorsepowerRpm; //RPM at which maxHp is set
int maxTorqueRpm; //RPM at which maxTorque is set
int torqueGraphRange = 2000; //Range variable for scaling draph
int horsepowerGraphRange = 2000;  //Range variable for scaling graph
//Human readable variables
char maxTorqueVal[10];
char maxTorqueRpmVal[10];
char maxHorsepowerVal[10];
char maxHorsepowerRpmVal[10];
char timeRemaining[10];
//bools
bool runMode = 0;
bool rpmMet = 0;
bool brakeOn = 0;
bool rpmRange = 0;
bool serialLoggingActive = false;
//Variables for chart positions
const int MAX_BINS = 31;
short t_bins[MAX_BINS] = {0};
short h_bins[MAX_BINS] = {0};
//variables for rpm reading
volatile unsigned long lastPulseTime = 0;
volatile unsigned long pulseDelta = 0;
const unsigned long MIN_PULSE_DELTA = 3000; // Filter: Ignores > 20,000 RPM (Noise)
const unsigned long RPM_TIMEOUT = 500000;   // 0.5s without pulse = 0 RPM

void IRAM_ATTR rpm_isr() {
    unsigned long now = micros();
    unsigned long interval = now - lastPulseTime;
    if (interval > MIN_PULSE_DELTA) {
        pulseDelta = interval;
        lastPulseTime = now;
    }
}
//rpm smoothing
const int FILTER_SIZE = 8;
unsigned long pulseBuffer[FILTER_SIZE] = {0};
int bufferIndex = 0;
unsigned long pulseSum = 0;

HX711 scale; //Declare scale to call HX711 library
lv_obj_t * ui_Chart;
extern lv_obj_t * ui_Chart;

void setup()
{
  pinMode(hallPin, INPUT); //Sets hall sensor as input
  pinMode(TFT_BL, OUTPUT); //Set backlight pin as output
  digitalWrite(TFT_BL, HIGH); //Turn backlight on full brightness

  Serial.begin( 115200 ); //Prepare for possible serial debug
  scale.begin(DOUT, CLK); //Initialize scale
  gfx->begin(); //Initialize gfx
  lv_init(); //Initialize lvgl
  
  // Initialize touch device
  pinMode(TOUCH_GT911_RST, OUTPUT);
  digitalWrite(TOUCH_GT911_RST, LOW);
  delay(10);
  digitalWrite(TOUCH_GT911_RST, HIGH);
  delay(10);
  touch_init();

  //  touch.setTouch( calData );
  screenWidth = gfx->width();
  screenHeight = gfx->height();

  //Initialize the display
  disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth *screenHeight/4);
  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth *screenHeight/4);
  lv_disp_drv_init(&disp_drv);

  //Set display resolution
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  //Initialize the (dummy) input device driver
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  //zero scale on boot
  noWeight = scale.read()/100; 

  //Code to execute LVGL code generated by the drawing tool
  ui_init();

  //attach interupt to hallPin
  pinMode(hallPin, INPUT_PULLDOWN); // Ensure pin is pulled low
  attachInterrupt(digitalPinToInterrupt(hallPin), rpm_isr, FALLING);
}

//Function to zero out scale
void calibrateLow(lv_event_t * e)
{
	noWeight = scale.read()/100;
}

//Function to calibrate scales top end
void calibrateHigh(lv_event_t * e)
{
	calibration = scale.read()/100;
}

//This function is called to start the dyno run
void startDyno(lv_event_t * e)
{
	runMode = 1;
  previousMillis = 0;
  lv_obj_clear_flag(ui_throttleNotice, LV_OBJ_FLAG_HIDDEN);
}

//Funtion to reset stored max values
void resetMax(lv_event_t * e)
{
  for(int i = 0; i < MAX_BINS; i++) {
    t_bins[i] = 0; 
    h_bins[i] = 0;
  }
  maxTorque = 0;
  maxTorqueRpm = 0;
  maxHorsepower = 0;
  maxHorsepowerRpm = 0;
}

//Function name should be explicit enough
void drawChart(lv_event_t * e)
{
  //If we were logging, tell the computer to stop and show the graph
  if (serialLoggingActive) {
    Serial.println("EOF"); 
    serialLoggingActive = false;
  }

  if(ui_Chart != NULL) {
    lv_obj_del_async(ui_Chart);
  }
    
  ui_Chart = lv_chart_create(ui_ChartScreen);
  lv_obj_set_width(ui_Chart, 700);
  lv_obj_set_height(ui_Chart, 325);
  lv_obj_set_x(ui_Chart, 0);
  lv_obj_set_y(ui_Chart, -60);
  lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
  lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
  
  // Update point count to match our data bins
  lv_chart_set_point_count(ui_Chart, MAX_BINS);
  lv_chart_set_range(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 0, torqueGraphRange);
  lv_chart_set_range(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 0, horsepowerGraphRange);
  
  
  lv_chart_series_t * ser1 = lv_chart_add_series(ui_Chart, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
  lv_chart_series_t * ser2 = lv_chart_add_series(ui_Chart, lv_color_hex(0x2D00FF), LV_CHART_AXIS_SECONDARY_Y);

  // Fill chart from arrays using a loop
  for(int i = 0; i < MAX_BINS; i++) {
    ser1->y_points[i] = t_bins[i];
    ser2->y_points[i] = h_bins[i];
  }

  // Visual styling
  lv_chart_set_div_line_count(ui_Chart, 5, 16);
  lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 16, 2, false, 50);
  lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
  lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);  
  lv_obj_set_style_bg_img_src(ui_Chart, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_Chart, &ui_font_tomorrow18, LV_PART_TICKS | LV_STATE_DEFAULT);
  lv_obj_set_style_size(ui_Chart, 0, LV_PART_INDICATOR);
}

//Calling this function switches between high and low range torque and horsepower gauges on the freestyle screen
void gaugeSelect(lv_event_t * e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);
  if(event_code == LV_EVENT_VALUE_CHANGED) 
  {
	  bool state = lv_obj_has_state(target, LV_STATE_CHECKED);
    if(state == 0) //0-40
    {
      lv_obj_add_flag(ui_freestyleSmallTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_freestyleSmallHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
      lv_obj_clear_flag(ui_freestyleTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_freestyleHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
    }else if(state == 1) //0-20
    {
      lv_obj_add_flag(ui_freestyleTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_freestyleHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
      lv_obj_clear_flag(ui_freestyleSmallTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_freestyleSmallHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
    }
  }
}

//Calling this function switches the RPM range of the graph
void rpmRangeSelect(lv_event_t * e)
{
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);
  if(event_code == LV_EVENT_VALUE_CHANGED) 
  {
	  bool state = lv_obj_has_state(target, LV_STATE_CHECKED);
    if(state == 0)
    {
      rpmRange = 0; //1000-5000 RPM
      Serial.println(rpmRange);
    }else if(state == 1)
    {
      rpmRange = 1; //0-10000 RPM
      Serial.println(rpmRange);
    }
  }
}

//The following fuctions set the Y scale of the graph
void firstTorqueRange(lv_event_t * e)
{
  torqueGraphRange = 1000;
  horsepowerGraphRange = 1000;
}

void secondTorqueRange(lv_event_t * e)
{
  torqueGraphRange = 2000;
  horsepowerGraphRange = 2000;
}

void thirdTorqueRange(lv_event_t * e)
{
  torqueGraphRange = 3000;
  horsepowerGraphRange = 3000;
}

void fourthTorqueRange(lv_event_t * e)
{
  torqueGraphRange = 4000;
  horsepowerGraphRange = 4000;
}

void checkSerialCommands() {
    while (Serial.available() > 0) {
        char cmd = Serial.read();
        if (cmd == 's') {
            serialLoggingActive = true;
            Serial.println("READY"); 
            Serial.flush(); // FORCE the message out to the PC now
            Serial.println("RPM,Torque,Horsepower"); 
        } 
        else if (cmd == 'q') {
            serialLoggingActive = false;
        }
    }
}

void loop()
{
    static uint32_t lastUIUpdate = 0;
    unsigned long localDelta;
    unsigned long lastTime;

    //Read scale and hall sensor, calculate RPM and horsepower, set gauge needle positions
    // 1. Thread-safe capture from ISR
    noInterrupts();
    localDelta = pulseDelta;
    lastTime = lastPulseTime;
    pulseDelta = 0; // Reset so we know if a NEW pulse happened
    interrupts();

    // 2. Timeout Check (Engine stopped)
    if (micros() - lastTime > RPM_TIMEOUT) {
        rpm = 0;
        // Clear buffer so it doesn't "hold" old speed
        for(int i=0; i<FILTER_SIZE; i++) pulseBuffer[i] = 0;
        pulseSum = 0;
    } 
    // 3. New Pulse Filtering Logic
    else if (localDelta > MIN_PULSE_DELTA) { 
        // Subtract the oldest value from the sum, add the new one
        pulseSum -= pulseBuffer[bufferIndex];
        pulseBuffer[bufferIndex] = localDelta;
        pulseSum += pulseBuffer[bufferIndex];
        
        bufferIndex = (bufferIndex + 1) % FILTER_SIZE;

        // Calculate RPM based on the average delta
        unsigned long averageDelta = pulseSum / FILTER_SIZE;
        if (averageDelta > 0) {
            rpm = 60000000UL / averageDelta;
        }
    }
    
    if (scale.is_ready()) {
      scaleReading = scale.read() / 100;
      torqueNeedlePos = map(scaleReading, noWeight, calibration, 0, 1000); //there are 2500 steps in the gauge from zero to max. This number is the step expected when hanging the calibration weight. Example: 20lb weight on 1' arm with 40lb max gauge reading 2500/40=62.5 steps/pound 20 pound weight x 62.5=1250
      if (abs(torqueNeedlePos) < 25) torqueNeedlePos = 0; // Ignore tiny fluctuations at idle
      horsepowerNeedlePos = (torqueNeedlePos*rpm)/5252;
      rpmNeedlePos = map(rpm, 0, 10000, 0, 2500);
      torque = (float)torqueNeedlePos/62.5;
      horsepower = ((torque*rpm)/5252);

      //If horsepower or torque are higher than current max set to max
      if(torque > maxTorque)
      {
       maxTorque = torque;
        maxTorqueRpm = rpm;
     }
     if(horsepower > maxHorsepower)
     {
       maxHorsepower = horsepower;
       maxHorsepowerRpm = rpm;
     }
    }
  if (millis() - lastUIUpdate > 50) {
    //Convert values to something human readable for display
    itoa(maxTorqueRpm, maxTorqueRpmVal, 10);
    itoa(maxHorsepowerRpm, maxHorsepowerRpmVal, 10);
    dtostrf(maxTorque, 2, 2, maxTorqueVal);
    dtostrf(maxHorsepower, 2, 2, maxHorsepowerVal);

    //Set needle position for all torque gauges
    lv_img_set_angle(ui_dynoRunTorqueGaugeNeedle, torqueNeedlePos);
    lv_img_set_angle(ui_freestyleTorqueGaugeNeedle, torqueNeedlePos);
    lv_img_set_angle(ui_calibrationGaugeNeedle, torqueNeedlePos);
    lv_img_set_angle(ui_freestyleSmallTorqueGaugeNeedle, torqueNeedlePos*2);

    //Set needle position for all horsepower gauges
    lv_img_set_angle(ui_dynoRunHorsepowerGaugeNeedle, horsepowerNeedlePos);
    lv_img_set_angle(ui_freestyleHorsepowerGaugeNeedle, horsepowerNeedlePos);
    lv_img_set_angle(ui_freestyleSmallHorsepowerGaugeNeedle, horsepowerNeedlePos*2);

    //Set needle position for RPM gauges
    lv_img_set_angle(ui_freestyleRpmGaugeNeedle, rpmNeedlePos);
    lv_img_set_angle(ui_dynoRunRpmGaugeNeedle, rpmNeedlePos);

    //Fill torque horsepower and RPM fields of freestyle screen
    lv_textarea_set_text(ui_freestyleTorqueField, maxTorqueVal);
    lv_textarea_set_text(ui_freestyleTorqueRpmField, maxTorqueRpmVal);
    lv_textarea_set_text(ui_freestyleHorsepowerField, maxHorsepowerVal);
    lv_textarea_set_text(ui_freestyleHorsepowerRpmField, maxTorqueRpmVal);

    //Fill max fields of chart screen
    lv_textarea_set_text(ui_chartScreenMaxTorqueRpmField, maxTorqueRpmVal);
    lv_textarea_set_text(ui_chartScreenMaxTorqueField, maxTorqueVal);
    lv_textarea_set_text(ui_chartScreenMaxHpRpmField, maxHorsepowerRpmVal);
    lv_textarea_set_text(ui_chartScreenMaxHpField, maxHorsepowerVal);
    
    //Fill max fields of run screen
    lv_label_set_text(ui_dynoRunMaxHorsepowerField, maxHorsepowerVal);
    lv_label_set_text(ui_dynoRunHorsepowerMaxRpmField, maxHorsepowerRpmVal);
    lv_label_set_text(ui_dynoRunMaxTorqueField, maxTorqueVal);
    lv_label_set_text(ui_dynoRunTorqueMaxRpmField, maxTorqueRpmVal);

    lastUIUpdate = millis();
  }

    // Fill bins for chart array
    int binIndex = -1;

    if(rpmRange == 1) // 0-10000 RPM range
    { 
      lv_label_set_text(ui_chartScreenChartXLabel, "20      25      31      36      41     47      52     57      63     68     73      79      84      89      95     100");      // Calculate bin: 10000 / 31 bins = ~322.5 RPM per bin
      binIndex = (rpm - 2000) / 258.06f;
      // Simple noise filter
      if (rpm > 1900 && rpm < 11000) {
        // Safety check and Update Bins
        if(binIndex >= 0 && binIndex < MAX_BINS) 
        {
          short currentT = (short)(torque * 100);
          short currentH = (short)(horsepower * 100);
      
          if(currentT > t_bins[binIndex]) t_bins[binIndex] = currentT;
         if(currentH > h_bins[binIndex]) h_bins[binIndex] = currentH;
       }
      }
    } 
    else if(rpmRange == 0) // 1000-5000 RPM range
    {
      lv_label_set_text(ui_chartScreenChartXLabel, "10      12      15      18      20     23      25     28      31     33     36     38      41      44      47      50");      // Calculate bin: (rpm - 1000) / (4000 / 31)
      binIndex = (rpm - 1000) / 129.03f;
      // Simple noise filter
      if (rpm > 950 && rpm < 6000) {
        // Safety check and Update Bins
        if(binIndex >= 0 && binIndex < MAX_BINS) 
        {
          short currentT = (short)(torque * 100);
          short currentH = (short)(horsepower * 100);
      
          if(currentT > t_bins[binIndex]) t_bins[binIndex] = currentT;
         if(currentH > h_bins[binIndex]) h_bins[binIndex] = currentH;
       }
      }
    }

    checkSerialCommands(); // Call the listener every loop

    // Only log if we are in runMode AND the computer has requested it
    if (serialLoggingActive) {
        static uint32_t lastLogTime = 0;
        // CSV Output: RPM, Torque, Horsepower
        // Log at 10Hz (every 100ms) to keep data manageable
        if (millis() - lastLogTime > 100) {
            Serial.print(rpm);
            Serial.print(",");
            Serial.print(torque);
            Serial.print(",");
            Serial.println(horsepower);
            lastLogTime = millis();
        }
    }

    //runMode stuff runMode is the main dyno run function. It is started when we press the dynoStartButton on the dynoRunScreen.
    if(runMode == 1) 
    //If it is in runMode
    {
      unsigned long currentMillis = millis();// Set currentMillis
      if(previousMillis == 0) 
      //If it is in the beginning of the runMode procedure
      {
        if(rpm > 3500)
        {
          lv_obj_add_flag(ui_throttleNotice, LV_OBJ_FLAG_HIDDEN);
          if(torque < 4)
          {
            lv_obj_clear_flag(ui_brakeNowNotice, LV_OBJ_FLAG_HIDDEN);
          }else if(torque >= 4)
          {
            lv_obj_add_flag(ui_brakeNowNotice, LV_OBJ_FLAG_HIDDEN);
            previousMillis = currentMillis;
          }
        }
      }else if(runTime + previousMillis <= currentMillis) 
      //If it isn't the beginning, is it the end??
      {
        previousMillis = 0;
        runMode = 0;
        lv_obj_add_flag(ui_runTimeCounter, LV_OBJ_FLAG_HIDDEN);
        lv_bar_set_value(ui_timeoutBar, 1000, LV_ANIM_OFF);
      }else 
      //We are in the middle of a runMode, keep counting and update the screen.
      {
        unsigned long timeLeft = map((currentMillis - previousMillis)/1000, 0, 10, 10, 0);
        itoa(timeLeft, timeRemaining, 10);
        lv_bar_set_value(ui_timeoutBar, (currentMillis - previousMillis)/10, LV_ANIM_OFF);
        lv_obj_clear_flag(ui_runTimeCounter, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_runTimeCounter, timeRemaining);
      }
    } //End runMode

    lv_timer_handler(); //This line is responsible for the UI doing its work
}



