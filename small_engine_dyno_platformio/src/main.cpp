//Available pins on 8048S070 are 11, 12, 13, 17, 18 Used; 12/Hall Trigger, 17/hx711 clk, 18 hx711 data 

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
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p ) {
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
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data ) {
  if (touch_has_signal()) {
    if (touch_touched()) {
      data->state = LV_INDEV_STATE_PR;

      //Set the coordinates
      data->point.x = touch_last_x;
      data->point.y = touch_last_y;
    }
    else if (touch_released()) {
      data->state = LV_INDEV_STATE_REL;
    }
  }
  else {
    data->state = LV_INDEV_STATE_REL;
  }
}

//Global
#define DOUT  18 // HX711 data pin
#define CLK  17 // HX711 clock pin
#define hallPin 12 // Hall sensor at pin 5
float maxHorsepower = 0; // Just what you'd think, variable to store highest horsepower seen since reset or during run
float maxTorque = 0; //Again, pretty obvious variable
volatile float horsepower; // Declare horsepower variable to be calculated
float snapHorsepower;
volatile float torque; // Declare torque variable
float snapTorque;
long previousMillis = 0; //Declare a time variable to use for the runMode
long runTime = 10000;  //The runMode will last for 10 seconds
long torqueNeedlePos = 0; // Declare torqueNeedlePos variable to rotate torque gauge needles
volatile int rpm; // Declare variable to store engine RPM
float snapRpm;
volatile long scaleReading; //Declare varible for raw scale data
int horsepowerNeedlePos = 0; // Declare horsepowerNeedlePos variable to rotate horsepower gauge needles
int rpmNeedlePos = 0; // Declare rpmNeedlePos variable to rotate RPM gauge needles
long noWeight; // The varaible for storing the scale output when at zero weight used for calibration
long calibration = 2000000; // Variable for storing the raw scale output when 20 pound weight is hung from calibration arm
int maxHorsepowerRpm; //RPM at which maxHp is set
int maxTorqueRpm; //RPM at which maxTorque is set

//Human readable variables
char maxTorqueVal[10];
char maxTorqueRpmVal[10];
char maxHorsepowerVal[10];
char maxHorsepowerRpmVal[10];
char timeRemaining[10];
//bools
bool runMode = 0;
bool serialLoggingActive = false;
//Variables for chart positions
const int MAX_BINS = 70;
volatile int t_bins[MAX_BINS] = {0};
volatile int h_bins[MAX_BINS] = {0};
int lastBinIndex = -1; // Important for interpolation
int binIndex = -1;
// Global variable to share the active bin count with the chart callback
int activeGraphBinCount = MAX_BINS; 

// --- DYNAMIC SETTINGS ---
int globalMaxRpm = 20000; // The Mathematical Limit (Slider)
int currentGaugeFaceLimit = 20000; // The Visual Limit (Gauge Face)

// Default Tuning Variables
float primaryReduction = 1.0f;   
float gearRatio = 1.0f;        
float finalDriveRatio = 1.0f; 
int   magnetCount = 1;        
float engineToShaftRatio = 1.0f;
float calibrationWeight = 20.0f;

volatile unsigned long MIN_PULSE_DELTA = 3000; // Calculated based on globalMaxRpm

//variables for rpm reading
volatile unsigned long lastPulseTime = 0;
volatile unsigned long pulseDelta = 0;
const unsigned long RPM_TIMEOUT = 200000;   // 0.5s without pulse = 0 RPM

// PROTOCOL VERSION 1.0
// Columns: RPM, Torque, HP
const char* DATA_HEADER = "RPM,Torque,HP"; 
const int PROTOCOL_VERSION = 1;
//rpm smoothing
const int FILTER_SIZE = 3;
unsigned long pulseBuffer[FILTER_SIZE] = {0};
int bufferIndex = 0;
unsigned long pulseSum = 0;

// Helper to set RPM from GUI
// This updates the Max RPM and recalculates the noise filter automatically
void setDynoMaxRpm(int rpm) {
  if(rpm < 2000) rpm = 2000;   // Safety lower limit
  if(rpm > 20000) rpm = 20000; // Safety upper limit
  globalMaxRpm = rpm;

  // Recalculate Noise Filter
  // Formula: 60,000,000 / (TargetNoiseRPM)
  // We set the noise floor at MaxRPM + 20% headroom. 
  // Example: If Max is 10k, filter rejects anything above 12k.
  float noiseCeiling = (float)rpm * 1.20f; 
  MIN_PULSE_DELTA = (unsigned long)(60000000.0f / noiseCeiling);
}

// --- CALLBACK: SLIDER ---
// Updates Global Math Limit Only
void slider_set_max_rpm(lv_event_t * e) {
    lv_obj_t * slider = lv_event_get_target(e);
    int val = (int)lv_slider_get_value(slider);
    val = ((val + 250) / 500) * 500; // Snap to 500
    setDynoMaxRpm(val);
    
    char buf[16];
    lv_snprintf(buf, sizeof(buf), "%d RPM", val);
    lv_label_set_text(ui_maxRpmLabel, buf);
}

// --- CALLBACK: TOGGLE GAUGE FACE ---
// Updates Visual Gauge Background Only
void toggleRpmScale(lv_event_t * e) {
  // If showing 20k, switch to 10k
  if (currentGaugeFaceLimit == 20000) {
      currentGaugeFaceLimit = 10000;
      
      lv_img_set_src(ui_freestyleRpmGauge, &ui_img_rpm_gauge_png);
      if(ui_dynoRunRpmGauge) lv_img_set_src(ui_dynoRunRpmGauge, &ui_img_rpm_gauge_png);
  } 
  // If showing 10k, switch to 20k
  else {
      currentGaugeFaceLimit = 20000;
      
      lv_img_set_src(ui_freestyleRpmGauge, &ui_img_rpm_gauge_high_png);
      if(ui_dynoRunRpmGauge) lv_img_set_src(ui_dynoRunRpmGauge, &ui_img_rpm_gauge_high_png);
  }
}

// --- CALLBACK: FINAL DRIVE TEXT AREA ---
void final_drive_update(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);

    if(code == LV_EVENT_FOCUSED) {
        lv_obj_clear_flag(ui_settingsKeyboard, LV_OBJ_FLAG_HIDDEN);
        lv_keyboard_set_textarea(ui_settingsKeyboard, ta);
    }
    else if(code == LV_EVENT_READY || code == LV_EVENT_DEFOCUSED) {
        const char * txt = lv_textarea_get_text(ta);
        float val = atof(txt);
        if(val <= 0.0f) val = 1.0f;
        finalDriveRatio = val;
        engineToShaftRatio = primaryReduction * gearRatio * finalDriveRatio;
        lv_obj_add_flag(ui_settingsKeyboard, LV_OBJ_FLAG_HIDDEN);
    }
}

// --- CALLBACK: MAGNET COUNT TEXT AREA ---
void magnet_count_update(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);

    if(code == LV_EVENT_FOCUSED) {
        lv_obj_clear_flag(ui_settingsKeyboard, LV_OBJ_FLAG_HIDDEN);
        lv_keyboard_set_textarea(ui_settingsKeyboard, ta);
    }
    else if(code == LV_EVENT_READY || code == LV_EVENT_DEFOCUSED) {
        const char * txt = lv_textarea_get_text(ta);
        int val = atoi(txt);
        if(val < 1) val = 1;
        magnetCount = val;
        lv_obj_add_flag(ui_settingsKeyboard, LV_OBJ_FLAG_HIDDEN);
    }
}

// --- CALLBACK: CALIBRATION WEIGHT TEXT AREA ---
void cal_weight_update(lv_event_t * e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * ta = lv_event_get_target(e);

    if(code == LV_EVENT_FOCUSED) {
        lv_obj_clear_flag(ui_calibrationKeyboard, LV_OBJ_FLAG_HIDDEN);
        lv_keyboard_set_textarea(ui_calibrationKeyboard, ta);
    }
    else if(code == LV_EVENT_READY || code == LV_EVENT_DEFOCUSED) {
        const char * txt = lv_textarea_get_text(ta);
        float val = atof(txt);
        if(val <= 0.0f) val = 1.0f;
        calibrationWeight = val;
        lv_obj_add_flag(ui_calibrationKeyboard, LV_OBJ_FLAG_HIDDEN);
    }
}

//Interupt for hall effect sensor
void IRAM_ATTR rpm_isr() {
  static unsigned long prevInterval = 0; 
  unsigned long now = micros();
  unsigned long interval = now - lastPulseTime;

  // 1. SAFETY RESET: If the gap is huge (>0.1s aka <600 RPM), the engine stopped or idled.
  if (interval > 100000) {
    pulseDelta = interval;
    prevInterval = interval;
    lastPulseTime = now;
    return;
  }

  // Uses MIN_PULSE_DELTA based on globalMaxRpm
  if (interval < MIN_PULSE_DELTA) return; 

    // 3. THE "TIGHT" WINDOW 
    // We check if the new interval is drastically shorter (faster RPM) than the last one.
    if (prevInterval > 0) {
        unsigned long accelerationLimit = (prevInterval * 40) / 100; 
        if (interval < accelerationLimit) return; // REJECT: Too fast, too soon.
    }

  // If we pass the gauntlet, it's real data.
  pulseDelta = interval;
  prevInterval = interval;
  lastPulseTime = now;
}
SemaphoreHandle_t dataMutex; 
HX711 scale; //Declare scale to call HX711 library
lv_obj_t * ui_Chart;
// Forward declarations for FreeRTOS Task
void SensorTaskLoop(void * pvParameters); 
TaskHandle_t SensorTask;

void setup() {
  dataMutex = xSemaphoreCreateMutex();
  pinMode(hallPin, INPUT_PULLDOWN); //Sets hall sensor as input
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
  noWeight = scale.read(); 

  //Code to execute LVGL code generated by the drawing tool
  ui_init();

  // Initialize Defaults
  setDynoMaxRpm(7500); // Math limit
  currentGaugeFaceLimit = 10000; // Default Visual (Low)
  // Logic to pick the best face on boot
  if(globalMaxRpm <= 10000) currentGaugeFaceLimit = 10000;
  
  // Apply visual state
  if(currentGaugeFaceLimit == 10000) {
      if(ui_freestyleRpmGauge) lv_img_set_src(ui_freestyleRpmGauge, &ui_img_rpm_gauge_png);
      if(ui_dynoRunRpmGauge) lv_img_set_src(ui_dynoRunRpmGauge, &ui_img_rpm_gauge_png);
  } else {
      if(ui_freestyleRpmGauge) lv_img_set_src(ui_freestyleRpmGauge, &ui_img_rpm_gauge_high_png);
      if(ui_dynoRunRpmGauge) lv_img_set_src(ui_dynoRunRpmGauge, &ui_img_rpm_gauge_high_png);
  }

  // Sync Slider to Math Limit
  if(ui_maxRpmSlider) lv_slider_set_value(ui_maxRpmSlider, globalMaxRpm, LV_ANIM_OFF);
  if(ui_maxRpmLabel) lv_label_set_text(ui_maxRpmLabel, "7500 RPM");
  
  // Sync Text Areas
  if(ui_finalDriveTextArea) lv_textarea_set_text(ui_finalDriveTextArea, "1.00");
  if(ui_magnetCountTextArea) lv_textarea_set_text(ui_magnetCountTextArea, "1");
  if(ui_calWeightTextArea) lv_textarea_set_text(ui_calWeightTextArea, "20.0");

  engineToShaftRatio = primaryReduction * gearRatio * finalDriveRatio;

  //attach interupt to hallPin
  pinMode(hallPin, INPUT_PULLDOWN); // Ensure pin is pulled low
  attachInterrupt(digitalPinToInterrupt(hallPin), rpm_isr, FALLING);

  // Create the sensor task on Core 0
  xTaskCreatePinnedToCore(
    SensorTaskLoop,   /* Task function */
    "SensorTask",     /* Name of task */
    10000,            /* Stack size in words */
    NULL,             /* Task input parameter */
    1,                /* Priority of the task */
    &SensorTask,      /* Task handle */
    0);               /* Core 0 */
}

//Function to zero out scale
void calibrateLow(lv_event_t * e) {
	noWeight = scaleReading;
}

//Function to calibrate scales top end
void calibrateHigh(lv_event_t * e) {
	calibration = scaleReading;
}

//This function is called to start the dyno run
void startDyno(lv_event_t * e) {
	runMode = 1;
  previousMillis = 0;
  lv_obj_clear_flag(ui_throttleNotice, LV_OBJ_FLAG_HIDDEN);
}

//Funtion to reset stored max values
void resetMax(lv_event_t * e) {
  for(int i = 0; i < MAX_BINS; i++) {
    t_bins[i] = 0; 
    h_bins[i] = 0;
  }
  maxTorque = 0;
  maxTorqueRpm = 0;
  maxHorsepower = 0;
  maxHorsepowerRpm = 0;

  // This ensures the UI fields also go to exactly 0.00
  lv_textarea_set_text(ui_freestyleTorqueField, "0.00");
  lv_textarea_set_text(ui_freestyleHorsepowerField, "0.00");
}

//Calling this function switches between high and low range torque and horsepower gauges
void gaugeSelect(lv_event_t * e) {
  lv_event_code_t event_code = lv_event_get_code(e);
  lv_obj_t * target = lv_event_get_target(e);
  
  if(event_code == LV_EVENT_VALUE_CHANGED) {
	  bool state = lv_obj_has_state(target, LV_STATE_CHECKED);
    
    // UPDATE FREESTYLE SCREEN
    if(state == 0) {//0-40 (High)
      lv_obj_add_flag(ui_freestyleSmallTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_freestyleSmallHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
      lv_obj_clear_flag(ui_freestyleTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_freestyleHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
    }
    else if(state == 1) {//0-20 (Low)
      lv_obj_add_flag(ui_freestyleTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_freestyleHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
      lv_obj_clear_flag(ui_freestyleSmallTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_freestyleSmallHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
    }

    // UPDATE DYNO RUN SCREEN (Mirrors the Freestyle settings)
    if(state == 0) {//0-40 (High)
      lv_obj_add_flag(ui_dynoRunSmallTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_dynoRunSmallHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
      lv_obj_clear_flag(ui_dynoRunTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_dynoRunHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
    }
    else if(state == 1) {//0-20 (Low)
      lv_obj_add_flag(ui_dynoRunTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_dynoRunHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
      lv_obj_clear_flag(ui_dynoRunSmallTorqueGauge, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_dynoRunSmallHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); 
    }
  }
}

// Event callback to convert Chart Index to RPM Label
static void chart_draw_event_cb(lv_event_t * e) {
  lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
  
  if(!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL)) return;

  if(dsc->id == LV_CHART_AXIS_PRIMARY_X) {
      float tickIndex = (float)dsc->value;
      float maxTickIndex = 9.0f; // 10 ticks = 0..9

      float pct = tickIndex / maxTickIndex;
      if(pct < 0) pct = 0;

      // FIXED SCALE: Now uses globalMaxRpm
      float range_width = (float)globalMaxRpm / (float)MAX_BINS;
      float maxRpmDisplayed = activeGraphBinCount * range_width;
      
      float calculatedRpm = pct * maxRpmDisplayed;

      // Integer math formatting: 5200 -> "5.2k"
      int val = (int)(calculatedRpm / 100); 
      int whole = val / 10;                 
      int decimal = val % 10;               
      
      lv_snprintf(dsc->text, dsc->text_length, "%d.%dk", whole, decimal);
  }
}

//Function name should be explicit enough
void drawChart(lv_event_t * e) {
  // 1. Stop Logging if active
  if (serialLoggingActive) {
    Serial.println("EOF"); 
    serialLoggingActive = false;
  }

  // 2. CHECK IF CHART EXISTS. Only create it if it doesn't exist.
  if(ui_Chart == NULL) {
    ui_Chart = lv_chart_create(ui_ChartScreen);
    lv_obj_set_width(ui_Chart, 700);
    lv_obj_set_height(ui_Chart, 325);
    lv_obj_set_x(ui_Chart, 0);
    lv_obj_set_y(ui_Chart, -60); // Moved up slightly to make room for X-labels
    lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
      
    // Visual styling
    // Note: Changed 7th argument to 'true' to ENABLE built-in X-axis labels
    lv_chart_set_div_line_count(ui_Chart, 5, 10); 
    lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 10, 1, true, 50); 
    lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);  
    lv_obj_set_style_bg_img_src(ui_Chart, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Chart, &ui_font_tomorrow18, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_size(ui_Chart, 0, LV_PART_INDICATOR); // Hide dots
      
    // Add the event callback for custom RPM labels
    lv_obj_add_event_cb(ui_Chart, chart_draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

    // Initialize Series ONLY ONCE
    lv_chart_add_series(ui_Chart, lv_color_hex(0x2D00FF), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_add_series(ui_Chart, lv_color_hex(0xFF0000), LV_CHART_AXIS_SECONDARY_Y);
  }
  
  // --- AUTO SCALING LOGIC ---

  // 1. Calculate Y-Axis Scale (Torque/HP)
  // Find highest value between maxTorque and maxHP
  float peakVal = (maxTorque > maxHorsepower) ? maxTorque : maxHorsepower;
  
  // Convert to chart units (x100 based on your loop logic)
  int autoRangeY = (int)(peakVal * 100.0f);
  
  // Add 10% Headroom so the line doesn't hit the very top
  autoRangeY = (int)(autoRangeY * 1.10f);
  
  // Safety: Prevent range from being 0 if no run data exists
  if(autoRangeY < 1000) autoRangeY = 1000; 

  // Apply Y Range
  lv_chart_set_range(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 0, autoRangeY);
  lv_chart_set_range(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 0, autoRangeY);

  // 2. Calculate X-Axis Scale (Data Trimming)
  // Scan backwards to find the last bin that actually has data
  int lastActiveBin = MAX_BINS - 1;
  for(int i = MAX_BINS - 1; i >= 0; i--) {
    if(t_bins[i] > 0 || h_bins[i] > 0) {
      lastActiveBin = i;
      break;
    }
  }

  // If the run was very short (noise), show at least 20% of the graph
  if(lastActiveBin < 10) lastActiveBin = 10; 

  // Store this globally so the label callback knows how wide the chart is
  activeGraphBinCount = lastActiveBin + 1;

  // Set the point count to match our data length
  // This effectively "Zooms" the X-axis to fit the data
  lv_chart_set_point_count(ui_Chart, activeGraphBinCount);

  // 3. UPDATE DATA 
  lv_chart_series_t * ser1 = lv_chart_get_series_next(ui_Chart, NULL); 
  lv_chart_series_t * ser2 = lv_chart_get_series_next(ui_Chart, ser1);

  // Only copy the bins that contain data
  for(int i = 0; i < activeGraphBinCount; i++) {
    ser1->y_points[i] = t_bins[i];
    ser2->y_points[i] = h_bins[i];
  }

  lv_chart_refresh(ui_Chart); 
}

void checkSerialCommands() {
  while (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 's') { // START LOGGING
      serialLoggingActive = true;
      
      // SEND HANDSHAKE PACKET
      Serial.println("PR_DYNO_START"); // Unique ID so app knows it's a Pit Row Dyno
      Serial.print("VER:"); Serial.println(PROTOCOL_VERSION);
      Serial.print("COLS:"); Serial.println(DATA_HEADER);
      Serial.println("READY"); 
    } 
    else if (cmd == 'q') {
      serialLoggingActive = false;
    }
  }
}

void updateDynoUI() {
  //Convert values to something human readable for display
  itoa(maxTorqueRpm, maxTorqueRpmVal, 10);
  itoa(maxHorsepowerRpm, maxHorsepowerRpmVal, 10);
  dtostrf(maxTorque, 2, 2, maxTorqueVal);
  dtostrf(maxHorsepower, 2, 2, maxHorsepowerVal);

  //Set needle position for all torque gauges
  torqueNeedlePos = (long)(snapTorque * 62.5f);
  lv_img_set_angle(ui_dynoRunTorqueGaugeNeedle, torqueNeedlePos);
  lv_img_set_angle(ui_freestyleTorqueGaugeNeedle, torqueNeedlePos);
  lv_img_set_angle(ui_calibrationGaugeNeedle, torqueNeedlePos);
  
  // Update "Small" torque gauges (x2 speed because it's a smaller range)
  if(ui_freestyleSmallTorqueGaugeNeedle) lv_img_set_angle(ui_freestyleSmallTorqueGaugeNeedle, torqueNeedlePos*2);
  if(ui_dynoRunSmallTorqueGaugeNeedle) lv_img_set_angle(ui_dynoRunSmallTorqueGaugeNeedle, torqueNeedlePos*2);

  //Set needle position for all horsepower gauges
  horsepowerNeedlePos = (long)(snapHorsepower * 62.5f);
  lv_img_set_angle(ui_dynoRunHorsepowerGaugeNeedle, horsepowerNeedlePos);
  lv_img_set_angle(ui_freestyleHorsepowerGaugeNeedle, horsepowerNeedlePos);

  // Update "Small" HP gauges
  if(ui_freestyleSmallHorsepowerGaugeNeedle) lv_img_set_angle(ui_freestyleSmallHorsepowerGaugeNeedle, horsepowerNeedlePos*2);
  if(ui_dynoRunSmallHorsepowerGaugeNeedle) lv_img_set_angle(ui_dynoRunSmallHorsepowerGaugeNeedle, horsepowerNeedlePos*2);

  // --- DECOUPLED RPM MAPPING ---
  // Map snapRpm to the current visual gauge limit (10k or 20k), NOT globalMaxRpm
  long needleMap = map(snapRpm, 0, currentGaugeFaceLimit, 0, 2500);
  
  // CLAMP: Prevent needle wrap-around if engine exceeds gauge face
  if (needleMap > 2500) needleMap = 2500; 
  if (needleMap < 0) needleMap = 0;

  rpmNeedlePos = (int)needleMap;
  
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
}

void loop() {
  static uint32_t lastUIUpdate = 0;
  unsigned long localDelta;
  unsigned long lastTime; 

  // 1. Thread-safe capture from ISR
  noInterrupts();
  localDelta = pulseDelta;
  lastTime = lastPulseTime;
  interrupts();

  // 2. Timeout Check (Engine stopped)
  if (micros() - lastTime > RPM_TIMEOUT) {
    rpm = 0;
    horsepower = 0;
    rpmNeedlePos = 0;
    horsepowerNeedlePos = 0;
    // Clear buffer so it doesn't "hold" old speed
    pulseSum = 0;
    bufferIndex = 0;
    memset(pulseBuffer, 0, sizeof(pulseBuffer));
    lastBinIndex = -1;
  } 
  // 3. New Pulse Filtering Logic
  else if (localDelta > MIN_PULSE_DELTA) { 
    // Capture and immediately reset to avoid processing the same pulse twice
    noInterrupts(); pulseDelta = 0; interrupts();

    // The Fix: If the buffer is empty (rpm is 0), fill it completely to avoid the "ramp-up" lag
    if (rpm == 0) {
      for(int i = 0; i < FILTER_SIZE; i++) {
        pulseBuffer[i] = localDelta;
      }
      pulseSum = localDelta * FILTER_SIZE;
    } 
    else {
      // Standard Moving Average for subsequent pulses
      pulseSum -= pulseBuffer[bufferIndex];
      pulseBuffer[bufferIndex] = localDelta;
      pulseSum += pulseBuffer[bufferIndex];
      bufferIndex = (bufferIndex + 1) % FILTER_SIZE;
    }

    unsigned long averageDelta = pulseSum / FILTER_SIZE;

    if (averageDelta > 0) {
      float shaftRpm = (60000000.0f / (float)averageDelta) / (float)magnetCount;
      rpm = (int)(shaftRpm * engineToShaftRatio);
      
      lastBinIndex = binIndex;
    }
  }
  
  snapRpm = rpm;
  if (xSemaphoreTake(dataMutex, 0)) { // Use 0 to not block UI if busy
    snapTorque = torque;
    xSemaphoreGive(dataMutex);
  }

  snapHorsepower = (snapTorque * (float)snapRpm) / 5252.0f;
    
  if (snapTorque > maxTorque) { 
    maxTorque = snapTorque; 
    maxTorqueRpm = snapRpm;
  }

  if (snapHorsepower > maxHorsepower) {
    maxHorsepower = snapHorsepower;
    maxHorsepowerRpm = snapRpm;
  }

  if (millis() - lastUIUpdate > 50) {
    updateDynoUI(); // Keep the loop clean
    lastUIUpdate = millis();
  }

  // --- DYNAMIC SCALING CALCULATION ---
  // Replaced with single 0-20,000 RPM Master Scale
  // CHANGED: Uses dynamic globalMaxRpm
  float range_low = 0.0f;
  float range_high = (float)globalMaxRpm;
  
  // Safety: Prevent division by zero if constants change
  float range_width = (range_high - range_low) / (float)MAX_BINS;
  
  // Clamp RPM to range
  float mapRpm = snapRpm;
  if (mapRpm < range_low) mapRpm = range_low;
  if (mapRpm > range_high) mapRpm = range_high;

  binIndex = (int)((mapRpm - range_low) / range_width);

  // --- ROBUST GAP FILLING INTERPOLATION ---
  if (binIndex >= 0 && binIndex < MAX_BINS && lastBinIndex != -1) {
    short currentT = (short)(snapTorque * 100.0f);
    short currentH = (short)(snapHorsepower * 100.0f);

    // Calculate the distance between current and last pulse
    int gapSize = abs(binIndex - lastBinIndex);

    // Only fill gaps if it's a reasonable jump (e.g., less than 20% of the chart)
    if (gapSize > 1 && gapSize < 20) {
      // Determine start and end points regardless of direction (Accel or Decel)
      int startJ = min(lastBinIndex, binIndex);
      int endJ = max(lastBinIndex, binIndex);

      for (int j = startJ; j <= endJ; j++) {
        // Safety: Double check array bounds
        if (j >= 0 && j < MAX_BINS) {
          // Update peak values for all bins in the gap
          if (currentT > t_bins[j]) t_bins[j] = currentT;
          if (currentH > h_bins[j]) h_bins[j] = currentH;
        }
      }
    } else {
        // No large gap: Standard single-bin update
        if (currentT > t_bins[binIndex]) t_bins[binIndex] = currentT;
        if (currentH > h_bins[binIndex]) h_bins[binIndex] = currentH; 
    }
  }

  checkSerialCommands(); // Call the listener every loop

  // Only log if the computer has requested it
  static uint32_t lastLogTime = 0;
  if (serialLoggingActive && (millis() - lastLogTime >= 50)) { // 20Hz sync
    Serial.print(snapRpm);
    Serial.print(",");
    Serial.print(snapTorque, 2);
    Serial.print(",");
    Serial.println(snapHorsepower, 2);
    lastLogTime = millis();
  }

  //runMode stuff runMode is the main dyno run function. It is started when we press the dynoStartButton on the dynoRunScreen.
  if(runMode == 1) {
    //If it is in runMode
    unsigned long currentMillis = millis();// Set currentMillis
    if(previousMillis == 0) {
      //If it is in the beginning of the runMode procedure
      if(snapRpm > 3500) {
        lv_obj_add_flag(ui_throttleNotice, LV_OBJ_FLAG_HIDDEN);
        if(snapTorque < 4) {
          lv_obj_clear_flag(ui_brakeNowNotice, LV_OBJ_FLAG_HIDDEN);
        }
        else if(snapTorque >= 4) {
          lv_obj_add_flag(ui_brakeNowNotice, LV_OBJ_FLAG_HIDDEN);
          previousMillis = currentMillis;
        }
      }
    }
    else if(runTime + previousMillis <= currentMillis) {
      //If it isn't the beginning, is it the end??
      previousMillis = 0;
      runMode = 0;
      lv_obj_add_flag(ui_runTimeCounter, LV_OBJ_FLAG_HIDDEN);
      lv_bar_set_value(ui_timeoutBar, 1000, LV_ANIM_OFF);
      }
      else {
        //We are in the middle of a runMode, keep counting and update the screen.
        unsigned long timeLeft = map((currentMillis - previousMillis)/1000, 0, 10, 10, 0);
        itoa(timeLeft, timeRemaining, 10);
        lv_bar_set_value(ui_timeoutBar, (currentMillis - previousMillis)/10, LV_ANIM_OFF);
        lv_obj_clear_flag(ui_runTimeCounter, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(ui_runTimeCounter, timeRemaining);
      }
  } //End runMode

  lv_timer_handler(); //This line is responsible for the UI doing its work
}

// Task handle for Core 0. This runs the HX711 reading tasks on the second core of the esp32.
void SensorTaskLoop(void * pvParameters) {
  const int AVG_SIZE = 8; 
  long readings[AVG_SIZE] = {0};
  int readIdx = 0;
  long total = 0;

  for (;;) {
    if (scale.is_ready()) {
      // 1. Running Average Calculation
      total = total - readings[readIdx];
      readings[readIdx] = scale.read();
      total = total + readings[readIdx];
      readIdx = (readIdx + 1) % AVG_SIZE;

      scaleReading = total / AVG_SIZE;

      // Calculate torque using floating point math
      float rawRange = (float)(calibration - noWeight);
      if (rawRange != 0) {
        // 1. Calculate the Torque at the BRAKE (Shaft)
        float shaftTorque = ((float)(scaleReading - noWeight) / rawRange) * calibrationWeight;
        // 2. Correct back to ENGINE Torque based on gearing
        if (xSemaphoreTake(dataMutex, portMAX_DELAY)) {
          torque = shaftTorque * engineToShaftRatio;
          xSemaphoreGive(dataMutex);
        }
      }  
    }
    vTaskDelay(pdMS_TO_TICKS(1)); 
  }
}
