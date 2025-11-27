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
int calibration = 16000; // Variable for storing the raw scale output when 20 pound weight is hung from calibration arm
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
//Variables for chart positions
short t1; short t2; short t3; short t4; short t5; short t6; short t7; short t8; short t9; short t10; short t11; short t12; short t13; short t14; short t15; short t16; short t17; short t18; short t19; short t20; short t21;
short h1; short h2; short h3; short h4; short h5; short h6; short h7; short h8; short h9; short h10; short h11; short h12; short h13; short h14; short h15; short h16; short h17; short h18; short h19; short h20; short h21;

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
  t1=0; t2=0; t3=0; t4=0; t5=0; t6=0; t7=0; t8=0; t9=0; t10=0; t11=0; t12=0; t13=0; t14=0; t15=0; t16=0; t17=0; t18=0; t19=0; t20=0; t21=0;
  h1=0; h2=0; h3=0; h4=0; h5=0; h6=0; h7=0; h8=0; h9=0; h10=0; h11=0; h12=0; h13=0; h14=0; h15=0; h16=0; h17=0; h18=0; h19=0; h20=0; h21=0;
  maxTorque = 0;
  maxTorqueRpm = 0;
  maxHorsepower = 0;
  maxHorsepowerRpm = 0;
}

//Function name should be explicit enough
void drawChart(lv_event_t * e)
{
  if(ui_Chart != NULL)
  {
  lv_obj_del_async(ui_Chart);
  }
    ui_Chart = lv_chart_create(ui_ChartScreen);
    lv_obj_set_width(ui_Chart, 700);
    lv_obj_set_height(ui_Chart, 325);
    lv_obj_set_x(ui_Chart, 0);
    lv_obj_set_y(ui_Chart, -60);
    lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(ui_Chart, 21);
    lv_chart_set_range(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 0, torqueGraphRange);
    lv_chart_set_range(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 0, horsepowerGraphRange);
    lv_chart_set_div_line_count(ui_Chart, 5, 11);
    lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 11, 2, false, 50);
    lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);  
    //lv_chart_set_axis_tick(chart, axis, major_len, minor_len, major_cnt, minor_cnt, label_en, draw_size) 
    lv_chart_series_t * ui_Chart_series_1 = lv_chart_add_series(ui_Chart, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    ui_Chart_series_1->y_points[0] = t1;
    ui_Chart_series_1->y_points[1] = t2;
    ui_Chart_series_1->y_points[2] = t3;
    ui_Chart_series_1->y_points[3] = t4;
    ui_Chart_series_1->y_points[4] = t5;
    ui_Chart_series_1->y_points[5] = t6;
    ui_Chart_series_1->y_points[6] = t7;
    ui_Chart_series_1->y_points[7] = t8;
    ui_Chart_series_1->y_points[8] = t9;
    ui_Chart_series_1->y_points[9] = t10;
    ui_Chart_series_1->y_points[10] = t11;
    ui_Chart_series_1->y_points[11] = t12;
    ui_Chart_series_1->y_points[12] = t13;
    ui_Chart_series_1->y_points[13] = t14;
    ui_Chart_series_1->y_points[14] = t15;
    ui_Chart_series_1->y_points[15] = t16;
    ui_Chart_series_1->y_points[16] = t17;
    ui_Chart_series_1->y_points[17] = t18;
    ui_Chart_series_1->y_points[18] = t19;
    ui_Chart_series_1->y_points[19] = t20;
    ui_Chart_series_1->y_points[20] = t21;
    lv_chart_series_t * ui_Chart_series_2 = lv_chart_add_series(ui_Chart, lv_color_hex(0x2D00FF), LV_CHART_AXIS_SECONDARY_Y);
    ui_Chart_series_2->y_points[0] = h1;
    ui_Chart_series_2->y_points[1] = h2;
    ui_Chart_series_2->y_points[2] = h3;
    ui_Chart_series_2->y_points[3] = h4;
    ui_Chart_series_2->y_points[4] = h5;
    ui_Chart_series_2->y_points[5] = h6;
    ui_Chart_series_2->y_points[6] = h7;
    ui_Chart_series_2->y_points[7] = h8;
    ui_Chart_series_2->y_points[8] = h9;
    ui_Chart_series_2->y_points[9] = h10;
    ui_Chart_series_2->y_points[10] = h11;
    ui_Chart_series_2->y_points[11] = h12;
    ui_Chart_series_2->y_points[12] = h13;
    ui_Chart_series_2->y_points[13] = h14;
    ui_Chart_series_2->y_points[14] = h15;
    ui_Chart_series_2->y_points[15] = h16;
    ui_Chart_series_2->y_points[16] = h17;
    ui_Chart_series_2->y_points[17] = h18;
    ui_Chart_series_2->y_points[18] = h19;
    ui_Chart_series_2->y_points[19] = h20;
    ui_Chart_series_2->y_points[20] = h21;
    lv_obj_set_style_bg_img_src(ui_Chart, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Chart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui_Chart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Chart, &ui_font_tomorrow18, LV_PART_TICKS | LV_STATE_DEFAULT);
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

void loop()
{
    //Read scale and hall sensor, calculate RPM and horsepower, set gauge needle positions
    duration = pulseIn(hallPin, LOW, 100000); //times the amount of microseconds the motor is not timing IR, Times out after 100000 uS. Raise the timeout for slower RPM readings. .1 second
    if(duration > 0)
    {
      rpm = 60000.0/duration*1000; //See above
    }else
    {
      rpm = 0;
    }
    scaleReading = scale.read()/100;
    torqueNeedlePos = map(scaleReading, noWeight, calibration, 0, 1000); //1 ft/lb equals 62.5 steps on the gauge ***Here is where a correction factor is introduced. I don't like it, I wish I knew why I needed it.***
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
        Serial.print(torque);
        Serial.print(" ft/lbs @ ");
        Serial.print(rpm);
        Serial.println(" RPM");
      }
    } //End runMode

    //Stupid waste of space, time, and power. This section does the "heavy lifting" to fill in the chart arrays.
    if(rpmRange == 1)//0-10000 RPM
    { 
      lv_label_set_text(ui_chartScreenChartXLabel, "0               1              2              3              4              5              6              7              8              9              10");
      if(rpm >=0 && rpm <250){if(torque*100 > t1){t1 = torque*100;}if(horsepower*100 > h1){h1 = horsepower*100;}}
      else if(rpm >=250 && rpm <750){if(torque*100 > t2){t2 = torque*100;}if(horsepower*100 > h2){h2 = horsepower*100;}}
      else if(rpm >=750 && rpm <1250){if(torque*100 > t3){t3 = torque*100;}if(horsepower*100 > h3){h3 = horsepower*100;}}
      else if(rpm >=1250 && rpm <1750){if(torque*100 > t4){t4 = torque*100;}if(horsepower*100 > h4){h4 = horsepower*100;}}
      else if(rpm >=1750 && rpm <2250){if(torque*100 > t5){t5 = torque*100;}if(horsepower*100 > h5){h5 = horsepower*100;}}
      else if(rpm >=2250 && rpm <2750){if(torque*100 > t6){t6 = torque*100;}if(horsepower*100 > h6){h6 = horsepower*100;}}
      else if(rpm >=2750 && rpm <3250){if(torque*100 > t7){t7 = torque*100;}if(horsepower*100 > h7){h7 = horsepower*100;}}
      else if(rpm >=3250 && rpm <3750){if(torque*100 > t8){t8 = torque*100;}if(horsepower*100 > h8){h8 = horsepower*100;}}
      else if(rpm >=3750 && rpm <4250){if(torque*100 > t9){t9 = torque*100;}if(horsepower*100 > h9){h9 = horsepower*100;}}
      else if(rpm >=4250 && rpm <4750){if(torque*100 > t10){t10 = torque*100;}if(horsepower*100 > h10){h10= horsepower*100;}}
      else if(rpm >=4750 && rpm <5250){if(torque*100 > t11){t11 = torque*100;}if(horsepower*100 > h11){h11 = horsepower*100;}}
      else if(rpm >=5250 && rpm <5750){if(torque*100 > t12){t12 = torque*100;}if(horsepower*100 > h12){h12 = horsepower*100;}}
      else if(rpm >=5750 && rpm <6250){if(torque*100 > t13){t13 = torque*100;}if(horsepower*100 > h13){h13 = horsepower*100;}}
      else if(rpm >=6250 && rpm <6750){if(torque*100 > t14){t14 = torque*100;}if(horsepower*100 > h14){h14 = horsepower*100;}}
      else if(rpm >=6750 && rpm <7250){if(torque*100 > t15){t15 = torque*100;}if(horsepower*100 > h15){h15 = horsepower*100;}}
      else if(rpm >=7250 && rpm <7750){if(torque*100 > t16){t16 = torque*100;}if(horsepower*100 > h16){h16 = horsepower*100;}}
      else if(rpm >=7750 && rpm <8250){if(torque*100 > t17){t17 = torque*100;}if(horsepower*100 > h17){h17 = horsepower*100;}}
      else if(rpm >=8250 && rpm <8750){if(torque*100 > t18){t18 = torque*100;}if(horsepower*100 > h18){h18 = horsepower*100;}}
      else if(rpm >=8750 && rpm <9250){if(torque*100 > t19){t19 = torque*100;}if(horsepower*100 > h19){h19 = horsepower*100;}}
      else if(rpm >=9250 && rpm <9750){if(torque*100 > t20){t20 = torque*100;}if(horsepower*100 > h20){h20 = horsepower*100;}}
      else if(rpm >=9750){if(torque*100 > t21){t21 = torque*100;}if(horsepower*100 > h21){h21 = horsepower*100;}}
    }
    
    if(rpmRange == 0)//1000-5000 RPM
    {
      lv_label_set_text(ui_chartScreenChartXLabel, "10            14           18           22           26           30           34           38           42           46           50");
      if(rpm >=900 && rpm <1100){if(torque*100 > t1){t1 = torque*100;}if(horsepower*100 > h1){h1 = horsepower*100;}}
      else if(rpm >=1100 && rpm <1300){if(torque*100 > t2){t2 = torque*100;}if(horsepower*100 > h2){h2 = horsepower*100;}}
      else if(rpm >=1300 && rpm <1500){if(torque*100 > t3){t3 = torque*100;}if(horsepower*100 > h3){h3 = horsepower*100;}}
      else if(rpm >=1500 && rpm <1700){if(torque*100 > t4){t4 = torque*100;}if(horsepower*100 > h4){h4 = horsepower*100;}}
      else if(rpm >=1700 && rpm <1900){if(torque*100 > t5){t5 = torque*100;}if(horsepower*100 > h5){h5 = horsepower*100;}}
      else if(rpm >=1900 && rpm <2100){if(torque*100 > t6){t6 = torque*100;}if(horsepower*100 > h6){h6 = horsepower*100;}}
      else if(rpm >=2100 && rpm <2300){if(torque*100 > t7){t7 = torque*100;}if(horsepower*100 > h7){h7 = horsepower*100;}}
      else if(rpm >=2300 && rpm <2500){if(torque*100 > t8){t8 = torque*100;}if(horsepower*100 > h8){h8 = horsepower*100;}}
      else if(rpm >=2500 && rpm <2700){if(torque*100 > t9){t9 = torque*100;}if(horsepower*100 > h9){h9 = horsepower*100;}}
      else if(rpm >=2700 && rpm <2900){if(torque*100 > t10){t10 = torque*100;}if(horsepower*100 > h10){h10 = horsepower*100;}}
      else if(rpm >=2900 && rpm <3100){if(torque*100 > t11){t11 = torque*100;}if(horsepower*100 > h11){h11 = horsepower*100;}}
      else if(rpm >=3100 && rpm <3300){if(torque*100 > t12){t12 = torque*100;}if(horsepower*100 > h12){h12 = horsepower*100;}}
      else if(rpm >=3300 && rpm <3500){if(torque*100 > t13){t13 = torque*100;}if(horsepower*100 > h13){h13 = horsepower*100;}}
      else if(rpm >=3500 && rpm <3700){if(torque*100 > t14){t14 = torque*100;}if(horsepower*100 > h14){h14 = horsepower*100;}}
      else if(rpm >=3700 && rpm <3900){if(torque*100 > t15){t15 = torque*100;}if(horsepower*100 > h15){h15 = horsepower*100;}}
      else if(rpm >=3900 && rpm <4100){if(torque*100 > t16){t16 = torque*100;}if(horsepower*100 > h16){h16 = horsepower*100;}}
      else if(rpm >=4100 && rpm <4300){if(torque*100 > t17){t17 = torque*100;}if(horsepower*100 > h17){h17 = horsepower*100;}}
      else if(rpm >=4300 && rpm <4500){if(torque*100 > t18){t18 = torque*100;}if(horsepower*100 > h18){h18 = horsepower*100;}}
      else if(rpm >=4500 && rpm <4700){if(torque*100 > t19){t19 = torque*100;}if(horsepower*100 > h19){h19 = horsepower*100;}}
      else if(rpm >=4700 && rpm <4900){if(torque*100 > t20){t20 = torque*100;}if(horsepower*100 > h20){h20 = horsepower*100;}}
      else if(rpm >=4900){if(torque*100 > t21){t21 = torque*100;}if(horsepower*100 > h21){h21 = horsepower*100;}}
    }

    lv_timer_handler(); //This line is responsible for the UI doing its work
}



