//Available pins on 8048S070 are 11, 12, 13, 17, 18 Used; 12/Hall Trigger, 11 wideband controller, 17/hx711 clk, 18 hx711 data 

#include <Arduino.h>
#include <lvgl.h>
#include <ui.h>
#include <Arduino_GFX_Library.h>
#include "HX711.h"
#include <Wire.h>
#include "Adafruit_MCP9600.h"
#include <Preferences.h> // Native ESP32 library for saving settings
Preferences preferences; // Create the storage object

Adafruit_MCP9600 mcp;

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

//Global
#define DOUT  18 // HX711 data pin
#define CLK  17 // HX711 clock pin
#define hallPin 12 // Hall sensor at pin 5
#define afrPin 11
#define TFT_BL 2 //#define GFX_BL DF_GFX_BL (backlight pin)

//RPM EGT AFR HP Torque variables
float snapEgt = 0; // The current instant temperature
float snapAfr = 0.0; // Variable to store the current Air/Fuel Ratio
volatile int rpm; // Declare variable to store engine RPM
float snapRpm;
int rpmNeedlePos = 0; // Declare rpmNeedlePos variable to rotate RPM gauge needles
volatile float horsepower; // Declare horsepower variable to be calculated
float snapHorsepower;
float maxHorsepower = 0; // Just what you'd think, variable to store highest horsepower seen since reset or during run
int maxHorsepowerRpm; //RPM at which maxHp is set
int horsepowerNeedlePos = 0; // Declare horsepowerNeedlePos variable to rotate horsepower gauge needles
volatile float torque; // Declare torque variable
float snapTorque;
float maxTorque = 0; //Again, pretty obvious variable
int maxTorqueRpm; //RPM at which maxTorque is set
long torqueNeedlePos = 0; // Declare torqueNeedlePos variable to rotate torque gauge needles

//Scale variables
HX711 scale; //Declare scale to call HX711 library
volatile long scaleReading; //Declare varible for raw scale data
long noWeight; // The varaible for storing the scale output when at zero weight used for calibration
long calibration = 2000000; // Variable for storing the raw scale output when 20 pound weight is hung from calibration arm

//Timing variables
long previousMillis = 0; //Declare a time variable to use for the runMode
volatile unsigned long lastPulseTime = 0;
volatile unsigned long pulseDelta = 0;

//Change to your screen resolution
static uint32_t screenWidth;
static uint32_t screenHeight;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t *disp_draw_buf;
static lv_disp_drv_t disp_drv;

//Human readable variables
char maxTorqueVal[10];
char maxTorqueRpmVal[10];
char maxHorsepowerVal[10];
char maxHorsepowerRpmVal[10];
char timeRemaining[10];

//bools
bool runMode = 0;
bool serialLoggingActive = false;
bool egtFound = false; 
bool afrFound = false;

//Variables for chart positions
const int MAX_BINS = 70;
volatile int t_bins[MAX_BINS] = {0};
volatile int h_bins[MAX_BINS] = {0};
volatile int e_bins[MAX_BINS] = {0};
volatile int a_bins[MAX_BINS] = {0};
int lastBinIndex = -1; // Important for interpolation
int binIndex = -1;
int activeGraphBinCount = MAX_BINS; // Global variable to share the active bin count with the chart callback

// Perfomance and mechanical settings
int globalMaxRpm = 20000; // The Mathematical Limit (Slider)
volatile unsigned long MIN_PULSE_DELTA = 3000; // Calculated based on globalMaxRpm
long runTime = 10000;  //The runMode will last for 10 seconds
unsigned long currentRpmTimeout = 200000;   // 0.5s without pulse = 0 RPM
const int FILTER_SIZE = 3; //rpm smoothing
float primaryReduction = 1.0f;   
float gearRatio = 1.0f;        
float finalDriveRatio = 1.0f; 
int   magnetCount = 1;        
float engineToShaftRatio = 1.0f;
float calibrationWeight = 20.0f;

//Forward declarations
static void chart_draw_event_cb(lv_event_t * e);
void SensorTaskLoop(void * pvParameters); 
TaskHandle_t SensorTask;
SemaphoreHandle_t dataMutex;

// --- Global Chart Variables ---
lv_obj_t * ui_Chart = NULL;        // Already exists
lv_chart_series_t * global_ser_torque = NULL; 
lv_chart_series_t * global_ser_hp = NULL;     
lv_chart_series_t * global_ser_egt = NULL;    
lv_chart_series_t * global_ser_afr = NULL;

//Drawing
int currentGaugeFaceLimit = 20000; // The Visual Limit (Gauge Face)

void recalculateNoiseFilter() {
  // 1. Calculate the physical limit of the SHAFT based on engine settings
  // Formula: ShaftRPM = EngineRPM / Ratio
  // Safety: Prevent divide by zero
  float ratio = engineToShaftRatio;
  if (ratio < 0.1f) ratio = 1.0f; 
  
  float maxShaftRpm = (float)globalMaxRpm / ratio;

  // 2. Add 20% Headroom for the "Noise Ceiling"
  float noiseCeilingShaft = maxShaftRpm * 1.20f;

  // 3. Calculate the shortest allowed time between pulses (Microseconds)
  // Formula: (60,000,000 / RPM) / Magnets
  // This tells us: "If a pulse comes in faster than this, it's noise."
  MIN_PULSE_DELTA = (unsigned long)((60000000.0f / noiseCeilingShaft) / (float)magnetCount);
  
  // Base timeout (200ms) * Ratio. 
  // If Ratio is 4.0, Timeout becomes 800ms to handle the slower shaft.
  currentRpmTimeout = 200000 * engineToShaftRatio;

  // Debug line (Optional - check Serial Monitor to see it working)
  // Serial.printf("New Filter Limit: %lu us (Max Shaft RPM: %.0f)\n", MIN_PULSE_DELTA, maxShaftRpm);
}
// Helper to set RPM from GUI
// This updates the Max RPM and recalculates the noise filter automatically
void setDynoMaxRpm(int rpm) {
  if(rpm < 2000) rpm = 2000;   
  if(rpm > 20000) rpm = 20000; 
  globalMaxRpm = rpm;

  // Call the central calculator
  recalculateNoiseFilter(); 
}

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

// PROTOCOL VERSION 1.0
// Columns: RPM, Torque, HP, EGT, AFR
const char* DATA_HEADER = "RPM,Torque,HP,EGT,AFR"; 
const int PROTOCOL_VERSION = 1;

unsigned long pulseBuffer[FILTER_SIZE] = {0};
int bufferIndex = 0;
unsigned long pulseSum = 0;

//Interupt for hall effect sensor
void IRAM_ATTR rpm_isr() {
  static unsigned long prevInterval = 0; 
  unsigned long now = micros();
  unsigned long interval = now - lastPulseTime;

  // SAFETY RESET: If the gap is huge (>0.1s aka <600 RPM), the engine stopped or idled.
  // We MUST accept this pulse to restart tracking, or we'll get stuck at 0.
  if (interval > 100000) {
    pulseDelta = interval;
    prevInterval = interval;
    lastPulseTime = now;
    return;
  }
  // Uses MIN_PULSE_DELTA based on globalMaxRpm
  if (interval < MIN_PULSE_DELTA) return; 

    // We check if the new interval is drastically shorter (faster RPM) than the last one.
    if (prevInterval > 0) {
        // Multiplier format: (Interval * Percentage) / 100
        // 60 means the new interval must be at least 60% of the old one
        // Lower number = Lets MORE signal through (Easier to accelerate)
        // Higher number = MORE filtering (rejects noise better
        unsigned long accelerationLimit = (prevInterval * 40) / 100; 
        if (interval < accelerationLimit) return; // REJECT: Too fast, too soon.
    }

  // If we pass the gauntlet, it's real data.
  pulseDelta = interval;
  prevInterval = interval;
  lastPulseTime = now;
}

void loadSavedSettings() {
  // Open the "dyno" namespace in Read/Write mode (false)
  preferences.begin("dyno", false); 

  // 1. Load the RAW values from the last calibration
  long savedNoWeight = preferences.getLong("noWeight", 0); 
  long savedCalibration = preferences.getLong("calibration", 2000000);
  if(savedCalibration < 1000) savedCalibration = 2000000;

  // 2. LOAD SETTINGS
  finalDriveRatio = preferences.getFloat("finalDrive", 1.0f);
  magnetCount = preferences.getInt("magnets", 1);
  globalMaxRpm = preferences.getInt("maxRpm", 7500);
  calibrationWeight = preferences.getFloat("calWeight", 20.0f);

  // 2. CALCULATE THE SPAN (The "Slope" of your sensor)
  // This is the only thing that actually matters physically.
  long calibrationSpan = savedCalibration - savedNoWeight;
  
  preferences.end();

  // 3. AUTO-TARE (The Fix)
  // Check if scale is ready (give it 500ms)
  if (scale.wait_ready_timeout(500)) {
      long currentReading = scale.read();
      
      // Update the Global "Zero" to RIGHT NOW
      noWeight = currentReading; 
      
      // Shift the "Calibration High Point" to match the new Zero
      // (New Zero + Old Span = New High Point)
      calibration = noWeight + calibrationSpan;
      
      Serial.println("✅ Auto-Tare Complete. Calibration Span Preserved.");
  } else {
      Serial.println("⚠️ Scale Missing. Using Saved Values (May drift).");
      // Fallback: Use the saved values directly if scale is unplugged
      noWeight = savedNoWeight;
      calibration = savedCalibration;
  }

  // Apply the loaded math immediately
  engineToShaftRatio = primaryReduction * gearRatio * finalDriveRatio;
  recalculateNoiseFilter(); 
  
  // Close for now
  preferences.end();
}

void setup() {
  dataMutex = xSemaphoreCreateMutex();
  pinMode(hallPin, INPUT_PULLDOWN); //Sets hall sensor as input
  attachInterrupt(digitalPinToInterrupt(hallPin), rpm_isr, FALLING);//attach interupt to hallPin
  pinMode(TFT_BL, OUTPUT); //Set backlight pin as output
  digitalWrite(TFT_BL, HIGH); //Turn backlight on full brightness

  pinMode(afrPin, INPUT_PULLDOWN); // Initialize Wideband Pin
  analogReadResolution(12); // Ensure we are using 0-4095 range (0-3.3V)

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

  // ZERO SCALE ON BOOT (With Safety Timeout)
  // We wait max 500ms for the scale to be ready. 
  // If no sensors are attached, we skip this to prevent hanging the screen.
  if (scale.wait_ready_timeout(500)) {
      noWeight = scale.read();
      Serial.println("✅ Scale Found & Zeroed.");
  } else {
      Serial.println("⚠️ Scale Missing - Skipping Boot Tare.");
      // We don't change 'noWeight' here; we let loadSavedSettings() handle it next.
  } 

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
    
  // -------------------------------------------------------------------------
  // --- FINAL EGT SENSOR SETUP (Moved here to be safe) ---
  // -------------------------------------------------------------------------
  
  if (!mcp.begin(0x67)) { 
    Serial.println("❌ MCP9600 NOT FOUND!");
    egtFound = false;
  } else {
    Serial.println("✅ MCP9600 Found & Configured!");
    
    // 12-bit Resolution (Fastest: 2ms update rate)
    mcp.setADCresolution(MCP9600_ADCRESOLUTION_14);
    
    // CHANGE 2: Turn off the hardware filter for instant reaction
    // You can set this to 1 or 2 later if the numbers jump around too much
    mcp.setFilterCoefficient(0); 
    
    mcp.setThermocoupleType(MCP9600_TYPE_K);
    mcp.enable(true);
    
    egtFound = true;
    
    // --- SHOW EGT LABEL IF SENSOR FOUND ---
    if(ui_LabelEGT) lv_obj_clear_flag(ui_LabelEGT, LV_OBJ_FLAG_HIDDEN);
  }

  // We check if the value is higher than a "Noise Floor" (approx 11.0 AFR)
  // If the sensor is connected and in free air (engine off), it will read High.
  // If disconnected, the Pulldown resistor pulls it to 0.
  delay(100); 
  int detectionRead = analogReadMilliVolts(afrPin);
  
  if(detectionRead > 2400) {  // CHANGED FROM 300 TO 3000
    afrFound = true;
    Serial.print("✅ Wideband Detected! Level: ");
    Serial.println(detectionRead);
    if(ui_LabelAFR) lv_obj_clear_flag(ui_LabelAFR, LV_OBJ_FLAG_HIDDEN);
  } else {
    afrFound = false;
    Serial.print("❌ Wideband Missing (Ghost Signal Ignored). Level: ");
    Serial.println(detectionRead);
    if(ui_LabelAFR) lv_obj_add_flag(ui_LabelAFR, LV_OBJ_FLAG_HIDDEN);
  }

  // --- LOAD SETTINGS FROM FLASH ---
  loadSavedSettings(); 

  // --- UPDATE UI FIELDS WITH LOADED VALUES ---
  // We need to overwrite the text boxes so the user sees the saved numbers
  char buf[32];

  // Update Magnet Field
  snprintf(buf, sizeof(buf), "%d", magnetCount);
  if(ui_magnetCountTextArea) lv_textarea_set_text(ui_magnetCountTextArea, buf);

  // Update Final Drive Field
  snprintf(buf, sizeof(buf), "%.2f", finalDriveRatio);
  if(ui_finalDriveTextArea) lv_textarea_set_text(ui_finalDriveTextArea, buf);

  // Update Calibration Weight Field
  snprintf(buf, sizeof(buf), "%.1f", calibrationWeight);
  if(ui_calWeightTextArea) lv_textarea_set_text(ui_calWeightTextArea, buf);

  // Update Max RPM Slider/Label
  if(ui_maxRpmSlider) lv_slider_set_value(ui_maxRpmSlider, globalMaxRpm, LV_ANIM_OFF);
  if(ui_maxRpmLabel) {
    snprintf(buf, sizeof(buf), "%d RPM", globalMaxRpm);
    lv_label_set_text(ui_maxRpmLabel, buf);
  }

  // 1. Create the Chart immediately
  ui_Chart = lv_chart_create(ui_ChartScreen);
  lv_obj_set_width(ui_Chart, 700);
  lv_obj_set_height(ui_Chart, 325);
  lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
  lv_obj_set_y(ui_Chart, -60);
  lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
  
  // 2. Styling
  lv_obj_set_style_bg_img_src(ui_Chart, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_border_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_text_font(ui_Chart, &ui_font_tomorrow18, LV_PART_TICKS | LV_STATE_DEFAULT);
  lv_chart_set_div_line_count(ui_Chart, 5, 10);
  lv_obj_set_style_size(ui_Chart, 0, LV_PART_INDICATOR); // Hide dots

  // 3. Create Series and SAVE THE POINTERS immediately
  // No guessing order. We make "Blue", we hand it to Torque. Forever.
  global_ser_torque = lv_chart_add_series(ui_Chart, lv_color_hex(0x2D00FF), LV_CHART_AXIS_PRIMARY_Y);
  global_ser_hp     = lv_chart_add_series(ui_Chart, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);

  // Only add AFR if hardware was found
  if(afrFound) {
  global_ser_afr = lv_chart_add_series(ui_Chart, lv_color_hex(0xFFFFFF), LV_CHART_AXIS_SECONDARY_Y);
  }
  
  // Only add EGT if hardware was found
  if(egtFound) {
    global_ser_egt = lv_chart_add_series(ui_Chart, lv_color_hex(0xFFD700), LV_CHART_AXIS_SECONDARY_Y);
  }
  
  // 4. Add the formatted tick callback
  lv_obj_add_event_cb(ui_Chart, chart_draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

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
  // SAVE
  preferences.begin("dyno", false);
  preferences.putLong("noWeight", noWeight);
  preferences.end();
}

//Function to calibrate scales top end
void calibrateHigh(lv_event_t * e) {
	calibration = scaleReading;
  // SAVE
  preferences.begin("dyno", false);
  preferences.putLong("calibration", calibration);
  preferences.end();
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
    e_bins[i] = 0;
    a_bins[i] = 0;
  }
  maxTorque = 0;
  maxTorqueRpm = 0;
  maxHorsepower = 0;
  maxHorsepowerRpm = 0;
  lastBinIndex = -1;

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

// --- CALLBACK: SLIDER ---
// Updates Global Math Limit Only
void slider_set_max_rpm(lv_event_t * e) {
  lv_obj_t * slider = lv_event_get_target(e);
  int val = (int)lv_slider_get_value(slider);
  val = ((val + 250) / 500) * 500; // Snap to 500
  setDynoMaxRpm(val);
  resetMax(NULL);
  // SAVE
  preferences.begin("dyno", false);
  preferences.putInt("maxRpm", val);
  preferences.end();
  char buf[16];
  snprintf(buf, sizeof(buf), "%d RPM", val);
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
        recalculateNoiseFilter(); 
        // SAVE
        preferences.begin("dyno", false);
        preferences.putFloat("finalDrive", finalDriveRatio);
        preferences.end();
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
    recalculateNoiseFilter();
    // SAVE
    preferences.begin("dyno", false);
    preferences.putInt("magnets", magnetCount);
    preferences.end();
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
      preferences.begin("dyno", false);
      preferences.putFloat("calWeight", calibrationWeight);
      preferences.end();
      lv_obj_add_flag(ui_calibrationKeyboard, LV_OBJ_FLAG_HIDDEN);
    }
}

// --- CALLBACK: CHART INDEX TO RPM SCALE ---
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
      
    snprintf(dsc->text, dsc->text_length, "%d.%dk", whole, decimal);
  }
}

//Function name should be explicit enough
void drawChart(lv_event_t * e) {
  // 1. Stop Logging if active
  if (serialLoggingActive) {
    Serial.println("EOF"); 
    serialLoggingActive = false;
  }

  // Static variables for labels
  static lv_obj_t * ui_EgtPeakLabel = NULL;
  static lv_obj_t * ui_HpPeakLabel = NULL;
  static lv_obj_t * ui_TorquePeakLabel = NULL;
  static lv_obj_t * ui_AfrPeakLabel = NULL; 

  // 2. CHECK IF CHART EXISTS OR CREATE IT
  if(ui_Chart == NULL) {
    ui_Chart = lv_chart_create(ui_ChartScreen);
    
    // Positioning & Styling
    lv_obj_set_width(ui_Chart, 700);
    lv_obj_set_height(ui_Chart, 325);
    lv_obj_set_x(ui_Chart, 0);
    lv_obj_set_y(ui_Chart, -60);
    lv_obj_set_align(ui_Chart, LV_ALIGN_CENTER);
    lv_chart_set_type(ui_Chart, LV_CHART_TYPE_LINE);
    
    lv_obj_set_style_bg_img_src(ui_Chart, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Chart, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Chart, &ui_font_tomorrow18, LV_PART_TICKS | LV_STATE_DEFAULT);
    
    // --- THE FIX: EVENT HANDLER ADDED ONCE HERE ---
    lv_obj_add_event_cb(ui_Chart, chart_draw_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    // ----------------------------------------------

    // Reset global pointers since we just made a new chart
    global_ser_torque = NULL;
    global_ser_hp = NULL;
    global_ser_afr = NULL;
    global_ser_egt = NULL;
  }

  // Ensure styling properties (Safe to run multiple times, these are just settings)
  lv_chart_set_div_line_count(ui_Chart, 5, 10); 
  lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_X, 10, 5, 10, 1, true, 50); 
  lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 5, 2, true, 50);
  lv_chart_set_axis_tick(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, true, 25);  
  lv_obj_set_style_size(ui_Chart, 0, LV_PART_INDICATOR); 
  
  // ---------------------------------------------------------
  // 3. SERIES MANAGEMENT
  // ---------------------------------------------------------
  // If we just created the chart (or if it was empty), these will be NULL.
  // We check the pointers directly.
  if (global_ser_torque == NULL) {
     
     // 1. EGT (Yellow)
    if(egtFound) {
      global_ser_egt = lv_chart_add_series(ui_Chart, lv_color_hex(0xFFD700), LV_CHART_AXIS_SECONDARY_Y);
    }
    // 2. AFR (White)
    if(afrFound) {
      global_ser_afr = lv_chart_add_series(ui_Chart, lv_color_hex(0xFFFFFF), LV_CHART_AXIS_SECONDARY_Y);
    }
    // 3. HP (Blue)
    global_ser_hp = lv_chart_add_series(ui_Chart, lv_color_hex(0xFF0000), LV_CHART_AXIS_PRIMARY_Y);
    
    // 4. Torque (Red)
    global_ser_torque = lv_chart_add_series(ui_Chart, lv_color_hex(0x2D00FF), LV_CHART_AXIS_PRIMARY_Y);
  }

  // ---------------------------------------------------------
  // 4. SCALING & DATA POPULATION
  // ---------------------------------------------------------
  float peakVal = (maxTorque > maxHorsepower) ? maxTorque : maxHorsepower;
  int autoRangeY = (int)(peakVal * 100.0f);
  autoRangeY = (int)(autoRangeY * 1.10f); // 10% Headroom
  if(autoRangeY < 1000) autoRangeY = 1000; 

  lv_chart_set_range(ui_Chart, LV_CHART_AXIS_PRIMARY_Y, 0, autoRangeY);
  lv_chart_set_range(ui_Chart, LV_CHART_AXIS_SECONDARY_Y, 500, 2000); 

  // X-Axis Trimming
  int lastActiveBin = MAX_BINS - 1;
  for(int i = MAX_BINS - 1; i >= 0; i--) {
    if(t_bins[i] > 0 || h_bins[i] > 0 || e_bins[i] > 0) {
      lastActiveBin = i;
      break;
    }
  }
  if(lastActiveBin < 10) lastActiveBin = 10; 
  activeGraphBinCount = lastActiveBin + 1;
  lv_chart_set_point_count(ui_Chart, activeGraphBinCount);

  // Peak Tracking Variables
  int maxEgtVal = -1, maxEgtIdx = -1;
  int maxTorqueValLocal = -1, maxTorqueIdx = -1;
  int maxHpValLocal = -1, maxHpIdx = -1;
  int maxAfrVal = -1, maxAfrIdx = -1;

  for(int i = 0; i < activeGraphBinCount; i++) {
    if(global_ser_afr) {
        global_ser_afr->y_points[i] = a_bins[i];
        if (a_bins[i] > maxAfrVal) { maxAfrVal = a_bins[i]; maxAfrIdx = i; }
    }
    if(global_ser_torque) {
        global_ser_torque->y_points[i] = t_bins[i];
        if (t_bins[i] > maxTorqueValLocal) { maxTorqueValLocal = t_bins[i]; maxTorqueIdx = i; }
    }
    if(global_ser_hp) {
        global_ser_hp->y_points[i] = h_bins[i];
        if (h_bins[i] > maxHpValLocal) { maxHpValLocal = h_bins[i]; maxHpIdx = i; }
    }
    if(global_ser_egt) {
      global_ser_egt->y_points[i] = e_bins[i];
      if (e_bins[i] > maxEgtVal) { maxEgtVal = e_bins[i]; maxEgtIdx = i; }
    }
  }

  lv_chart_refresh(ui_Chart); 

  // ---------------------------------------------------------
  // 5. PEAK LABELS
  // ---------------------------------------------------------
  
  // AFR
  if(afrFound && global_ser_afr != NULL && maxAfrIdx != -1 && maxAfrVal > 10) {
    if(ui_AfrPeakLabel == NULL) {
      ui_AfrPeakLabel = lv_label_create(ui_ChartScreen); 
      lv_obj_set_style_text_color(ui_AfrPeakLabel, lv_color_hex(0xFFFFFF), LV_PART_MAIN); 
      lv_obj_set_style_text_font(ui_AfrPeakLabel, &ui_font_tomorrow, LV_PART_MAIN); 
    }
    lv_obj_clear_flag(ui_AfrPeakLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(ui_AfrPeakLabel); 
    lv_label_set_text_fmt(ui_AfrPeakLabel, "%d.%d:1", maxAfrVal/100, (maxAfrVal%100)/10);
    
    lv_point_t p;
    lv_chart_get_point_pos_by_id(ui_Chart, global_ser_afr, maxAfrIdx, &p);
    int finalX = p.x - 50; if (finalX < 5) finalX = 5;
    int finalY = p.y - 40; if (finalY < 5) finalY = 5;
    lv_obj_align_to(ui_AfrPeakLabel, ui_Chart, LV_ALIGN_TOP_LEFT, finalX, finalY);
  } else {
    if(ui_AfrPeakLabel) lv_obj_add_flag(ui_AfrPeakLabel, LV_OBJ_FLAG_HIDDEN);
  }

  // EGT
  if(egtFound && global_ser_egt != NULL && maxEgtIdx != -1) {
    if(ui_EgtPeakLabel == NULL) {
      ui_EgtPeakLabel = lv_label_create(ui_ChartScreen); 
      lv_obj_set_style_text_color(ui_EgtPeakLabel, lv_color_hex(0xFFD700), LV_PART_MAIN);
      lv_obj_set_style_text_font(ui_EgtPeakLabel, &ui_font_tomorrow, LV_PART_MAIN); 
    }
    lv_obj_clear_flag(ui_EgtPeakLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(ui_EgtPeakLabel); 
    lv_label_set_text_fmt(ui_EgtPeakLabel, "%d F", maxEgtVal);
    
    lv_point_t p;
    lv_chart_get_point_pos_by_id(ui_Chart, global_ser_egt, maxEgtIdx, &p);
    int finalX = p.x - 50; if (finalX < 5) finalX = 5;
    int finalY = p.y - 40; if (finalY < 5) finalY = 5;
    lv_obj_align_to(ui_EgtPeakLabel, ui_Chart, LV_ALIGN_TOP_LEFT, finalX, finalY);
  } else {
    if(ui_EgtPeakLabel) lv_obj_add_flag(ui_EgtPeakLabel, LV_OBJ_FLAG_HIDDEN);
  }

  // HP
  if(global_ser_hp != NULL && maxHpIdx != -1 && maxHpValLocal > 10) {
    if(ui_HpPeakLabel == NULL) {
      ui_HpPeakLabel = lv_label_create(ui_ChartScreen); 
      lv_obj_set_style_text_color(ui_HpPeakLabel, lv_color_hex(0xFF0000), LV_PART_MAIN); 
      lv_obj_set_style_text_font(ui_HpPeakLabel, &ui_font_tomorrow, LV_PART_MAIN); 
    }
    lv_obj_clear_flag(ui_HpPeakLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(ui_HpPeakLabel); 
    lv_label_set_text_fmt(ui_HpPeakLabel, "%d.%02dHP", maxHpValLocal/100, maxHpValLocal%100);
    
    lv_point_t p;
    lv_chart_get_point_pos_by_id(ui_Chart, global_ser_hp, maxHpIdx, &p);
    int finalX = p.x - 50; if (finalX < 5) finalX = 5;
    int finalY = p.y - 40; if (finalY < 5) finalY = 5;
    lv_obj_align_to(ui_HpPeakLabel, ui_Chart, LV_ALIGN_TOP_LEFT, finalX, finalY);
  } else {
    if(ui_HpPeakLabel) lv_obj_add_flag(ui_HpPeakLabel, LV_OBJ_FLAG_HIDDEN);
  }

  // TORQUE
  if(global_ser_torque != NULL && maxTorqueIdx != -1 && maxTorqueValLocal > 10) {
    if(ui_TorquePeakLabel == NULL) {
      ui_TorquePeakLabel = lv_label_create(ui_ChartScreen); 
      lv_obj_set_style_text_color(ui_TorquePeakLabel, lv_color_hex(0x2D00FF), LV_PART_MAIN); 
      lv_obj_set_style_text_font(ui_TorquePeakLabel, &ui_font_tomorrow, LV_PART_MAIN); 
    }
    lv_obj_clear_flag(ui_TorquePeakLabel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_move_foreground(ui_TorquePeakLabel); 
    lv_label_set_text_fmt(ui_TorquePeakLabel, "%d.%02dft/lbs", maxTorqueValLocal/100, maxTorqueValLocal%100);
    
    lv_point_t p;
    lv_chart_get_point_pos_by_id(ui_Chart, global_ser_torque, maxTorqueIdx, &p);
    int finalX = p.x - 50; if (finalX < 5) finalX = 5;
    int finalY = p.y - 40; if (finalY < 5) finalY = 5;
    lv_obj_align_to(ui_TorquePeakLabel, ui_Chart, LV_ALIGN_TOP_LEFT, finalX, finalY);
  } else {
    if(ui_TorquePeakLabel) lv_obj_add_flag(ui_TorquePeakLabel, LV_OBJ_FLAG_HIDDEN);
  }
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
  static uint32_t lastEgtUpdate = 0;

  // 1. Thread-safe capture from ISR
  noInterrupts();
  localDelta = pulseDelta;
  lastTime = lastPulseTime;
  interrupts();

  // 2. Timeout Check (Engine stopped)
  if (micros() - lastTime > currentRpmTimeout) {
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

  // Run this only every 20ms (50 times a second)
  if (millis() - lastEgtUpdate > 20) { 
    if (egtFound) {
      float tempC = mcp.readThermocouple();
      // Convert to F, but store as float for now
      snapEgt = (tempC * 1.8) + 32; 
    }
    // ONLY READ IF FOUND
    if (afrFound) {
        // 1. Get the calibrated voltage directly in Millivolts (e.g., 1500 mV)
        uint32_t pinMilliVolts = analogReadMilliVolts(afrPin);
        
        // 2. Convert to Volts (1.5V)
        float pinVoltage = pinMilliVolts / 1000.0;
        
        // 3. Undo the Voltage Divider (Same as before)
        // (pinVoltage / 0.6 scales it back up to the real 0-5V sensor output)
        float widebandVoltage = pinVoltage / 0.6; 
        
        // 4. Convert to AFR (Standard 10-20 scale)
        snapAfr = (widebandVoltage * 2.0) + 10.0;
    }

    lastEgtUpdate = millis();
  }

  if (millis() - lastUIUpdate > 50) {
    updateDynoUI(); // Keep the loop clean
    if (ui_LabelEGT) {
      lv_label_set_text_fmt(ui_LabelEGT, "EGT\n%d F", (int)snapEgt);
    }
    if (ui_LabelAFR) {
      // Logic: Split the float into whole and decimal parts for clean display
      // Example: 14.7 AFR
      int whole = (int)snapAfr;
      int decimal = (int)((snapAfr - whole) * 10);
      
      lv_label_set_text_fmt(ui_LabelAFR, "AFR\n%d.%d:1", whole, decimal);
    }
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
    short currentE = (short)(snapEgt);
    short currentA = (short)(snapAfr * 100.0f); // <--- ADD THIS (x100 scaling)

    int gapSize = abs(binIndex - lastBinIndex);

    if (gapSize > 1 && gapSize < 20) {
      int startJ = min(lastBinIndex, binIndex);
      int endJ = max(lastBinIndex, binIndex);

      for (int j = startJ; j <= endJ; j++) {
        if (j >= 0 && j < MAX_BINS) {
          if (currentT > t_bins[j]) t_bins[j] = currentT;
          if (currentH > h_bins[j]) h_bins[j] = currentH;
          if (currentE > e_bins[j]) e_bins[j] = currentE;
          if (currentA > a_bins[j]) a_bins[j] = currentA; // <--- ADD THIS
        }
      }
    } else {
      if (currentT > t_bins[binIndex]) t_bins[binIndex] = currentT;
      if (currentH > h_bins[binIndex]) h_bins[binIndex] = currentH; 
      if (currentE > e_bins[binIndex]) e_bins[binIndex] = currentE;
      if (currentA > a_bins[binIndex]) a_bins[binIndex] = currentA; // <--- ADD THIS
    }
  }

  checkSerialCommands(); // Call the listener every loop

  // Only log if the computer has requested it
  static uint32_t lastLogTime = 0;
  if (serialLoggingActive && (millis() - lastLogTime >= 50)) { 
    Serial.print(snapRpm);
    Serial.print(",");
    Serial.print(snapTorque, 2);
    Serial.print(",");
    Serial.print(snapHorsepower, 2);
    Serial.print(",");
    Serial.print(snapEgt, 1);
    Serial.print(",");      // New comma
    Serial.println(snapAfr, 1); // New AFR value
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
          torque = shaftTorque / engineToShaftRatio;
          xSemaphoreGive(dataMutex);
        }
      }  
    }
    vTaskDelay(pdMS_TO_TICKS(1)); 
  }
}

extern "C" long get_calibration_value() {
    return calibration;
}