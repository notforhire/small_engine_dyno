#include "ui.h"

// --- SETTINGS SCREEN ---
lv_obj_t * ui_settingsScreen;
lv_obj_t * ui_continueButton;
lv_obj_t * ui_continueButtonLabel;
lv_obj_t * ui_settingsChartButton;
lv_obj_t * ui_settingsChartButtonLabel;
lv_obj_t * ui_settingsHomeButton;
lv_obj_t * ui_settingsHomeButtonLabel;
lv_obj_t * ui_settingsInstructions;
// Slider Objects
lv_obj_t * ui_maxRpmSlider;
lv_obj_t * ui_maxRpmLabel;
lv_obj_t * ui_maxRpmTitle;
// New Inputs
lv_obj_t * ui_finalDriveLabel;
lv_obj_t * ui_finalDriveTextArea;
lv_obj_t * ui_magnetCountLabel;
lv_obj_t * ui_magnetCountTextArea;
lv_obj_t * ui_settingsKeyboard;

// --- HOME SCREEN ---
lv_obj_t * ui_homeScreen;
lv_obj_t * ui_dynoRunButton;
lv_obj_t * ui_dynoRunButtonLabel;
lv_obj_t * ui_settingsButton;
lv_obj_t * ui_settingsButtonLabel;
lv_obj_t * ui_freestyleButton;
lv_obj_t * ui_freestyleButtonLabel;
lv_obj_t * ui_calibrateButton;
lv_obj_t * ui_calibrateButtonLabel;
lv_obj_t * ui_calibrationWarning;
lv_obj_t * ui_safetyAdvisement;
lv_obj_t * ui_dumbFriendWarning;

// --- CALIBRATION SCREEN ---
lv_obj_t * ui_calibrationScreen;
lv_obj_t * ui_calibrationPageHomeButton;
lv_obj_t * ui_calibrationPageHomeButtonLabel;
lv_obj_t * ui_calibrationInstructions;
lv_obj_t * ui_calibrationGauge;
lv_obj_t * ui_calibrationGaugeNeedle;
lv_obj_t * ui_setZeroButton;
lv_obj_t * ui_setZeroButtonLabel;
lv_obj_t * ui_calibrateButtonGreen;
lv_obj_t * ui_calibrateButtonGreenLabel;
lv_obj_t * ui_calibrateButtonWhite;
lv_obj_t * ui_calibrateButtonWhiteLabel;
lv_obj_t * ui_calibrationScreenGaugeArc;
// New Inputs
lv_obj_t * ui_calWeightTitle;
lv_obj_t * ui_calWeightTextArea;
lv_obj_t * ui_calibrationKeyboard;

// --- DYNO RUN SETUP SCREEN ---
lv_obj_t * ui_dynoRunScreen;
lv_obj_t * ui_dynoStartButton;
lv_obj_t * ui_dynoStartButtonLabel;
lv_obj_t * ui_dynoStartHomeButton;
lv_obj_t * ui_dynoStartHomeButtonLabel;
lv_obj_t * ui_dynoRunDirections;

// --- FREESTYLE SCREEN ---
lv_obj_t * ui_freestyleScreen;
lv_obj_t * ui_freestyleTorqueGauge;
lv_obj_t * ui_freestyleTorqueGaugeNeedle;
lv_obj_t * ui_freestyleHorsepowerGauge;
lv_obj_t * ui_freestyleHorsepowerGaugeNeedle;
lv_obj_t * ui_freestyleRpmGauge;
lv_obj_t * ui_freestyleRpmGaugeNeedle;
// Small Gauges
lv_obj_t * ui_freestyleSmallHorsepowerGauge;
lv_obj_t * ui_freestyleSmallHorsepowerGaugeNeedle;
lv_obj_t * ui_freestyleSmallTorqueGauge;
lv_obj_t * ui_freestyleSmallTorqueGaugeNeedle;
// Controls
lv_obj_t * ui_rangeSelectSwitch;
lv_obj_t * ui_rangeSelectLabel;
lv_obj_t * ui_highLabel;
lv_obj_t * ui_lowLabel;
lv_obj_t * ui_freestyleHomeButton;
lv_obj_t * ui_freestyleHomeButtonLabel;
lv_obj_t * ui_freestyleChartButton;
lv_obj_t * ui_freestyleChartButtonLabel;
lv_obj_t * ui_freestyleTorquelabel;
lv_obj_t * ui_freestyleHorsepowerLabel;
lv_obj_t * ui_freestyleTorqueField;
lv_obj_t * ui_freestyleTorqueRpmField;
lv_obj_t * ui_freestyleHorsepowerField;
lv_obj_t * ui_freestyleHorsepowerRpmField;
lv_obj_t * ui_freestyleRpmGaugeArc;
lv_obj_t * ui_freestyleHorsepowerGaugeArc;
lv_obj_t * ui_freestyleTorqueGaugeArc;
lv_obj_t * ui_gaugeLabel;
lv_obj_t * ui_LabelEGT;
lv_obj_t * ui_LabelAFR;

// --- DYNO RUN GAUGE SCREEN ---
lv_obj_t * ui_dynoRunGaugeScreen;
lv_obj_t * ui_dynoRunGaugeBackButton;
lv_obj_t * ui_dynoRunGaugeBackButtonLabel;
lv_obj_t * ui_dynoRunChartButton;
lv_obj_t * ui_dynoRunChartButtonLabel;
lv_obj_t * ui_dynoRunRpmGauge;
lv_obj_t * ui_dynoRunRpmGaugeNeedle;
lv_obj_t * ui_dynoRunRpmGaugeLabel;
lv_obj_t * ui_dynoRunTorqueGauge;
lv_obj_t * ui_dynoRunTorqueGaugeNeedle;
lv_obj_t * ui_dynoRunTorqueGaugeLabel;
lv_obj_t * ui_dynoRunHorsepowerGauge;
lv_obj_t * ui_dynoRunHorsepowerGaugeNeedle;
lv_obj_t * ui_dynoRunHorsepowerGaugeLabel;
// Small Gauges
lv_obj_t * ui_dynoRunSmallTorqueGauge;
lv_obj_t * ui_dynoRunSmallTorqueGaugeNeedle;
lv_obj_t * ui_dynoRunSmallHorsepowerGauge;
lv_obj_t * ui_dynoRunSmallHorsepowerGaugeNeedle;
// Controls
lv_obj_t * ui_dynoRunRangeSwitch;
lv_obj_t * ui_dynoRunRangeSelectLabel;
lv_obj_t * ui_dynoRunHighLabel;
lv_obj_t * ui_dynoRunLowLabel;
// Labels
lv_obj_t * ui_timeoutBar;
lv_obj_t * ui_runTorqueLabel;
lv_obj_t * ui_runHorsepowerLabel;
lv_obj_t * ui_dynoRunMaxTorqueField;
lv_obj_t * ui_dynoRunMaxHorsepowerField;
lv_obj_t * ui_atSymbol1;
lv_obj_t * ui_atSymbol2;
lv_obj_t * ui_dynoRunTorqueMaxRpmField;
lv_obj_t * ui_dynoRunHorsepowerMaxRpmField;
lv_obj_t * ui_rpmLabel1;
lv_obj_t * ui_rpmLabel2;
lv_obj_t * ui_dynoRunRpmGaugeArc;
lv_obj_t * ui_dynoRunHorsepowerGaugeArc;
lv_obj_t * ui_dynoRunTorqueGaugeArc;
lv_obj_t * ui_runTimeCounter;
lv_obj_t * ui_throttleNotice;
lv_obj_t * ui_brakeNowNotice;

// --- CHART SCREEN ---
lv_obj_t * ui_ChartScreen;
lv_obj_t * ui_chartScreenHomeButton;
lv_obj_t * ui_chartScreenHomeButtonLabel;
lv_obj_t * ui_chartScreenMapHplabel;
lv_obj_t * ui_chartScreenMaxTorqueLabel;
lv_obj_t * ui_chartScreenMaxTorqueField;
lv_obj_t * ui_chartScreenMaxHpField;
lv_obj_t * ui_chartResetButton;
lv_obj_t * ui_chartResetButtonLabel;
lv_obj_t * ui_chartScreenMaxHpRpmField;
lv_obj_t * ui_chartScreenMaxTorqueRpmField;


// --- EVENT CALLBACKS ---

// GENERIC KEYBOARD CLOSER
void ui_event_keyboard(lv_event_t * e) {
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * keyboard = lv_event_get_target(e);
    
    if(event_code == LV_EVENT_READY || event_code == LV_EVENT_CANCEL) {
        lv_obj_add_flag(keyboard, LV_OBJ_FLAG_HIDDEN); // Hide keyboard
    }
}

void ui_event_continueButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        // Enforce sequence: Green hidden, White visible
        lv_obj_add_flag(ui_calibrateButtonGreen, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_calibrateButtonWhite, LV_OBJ_FLAG_HIDDEN);
        
        lv_scr_load_anim(ui_calibrationScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);

        // --- NEW: Update Label to "Calibrate" for future visits ---
        lv_label_set_text(ui_continueButtonLabel, "Calibrate");
    }
}

void ui_event_dynoRunButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_scr_load_anim(ui_dynoRunScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_settingsButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_scr_load_anim(ui_settingsScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_freestyleButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        resetMax(e);
        lv_scr_load_anim(ui_freestyleScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_calibrateButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_scr_load_anim(ui_calibrationScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
        // Reset state so they must set zero again
        lv_obj_add_flag(ui_calibrateButtonGreen, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_calibrateButtonWhite, LV_OBJ_FLAG_HIDDEN);
    }
}

void ui_event_calibrationPageHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_scr_load_anim(ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_setZeroButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        calibrateLow(e);
        // Swap buttons: White hidden, Green visible
        lv_obj_add_flag(ui_calibrateButtonWhite, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(ui_calibrateButtonGreen, LV_OBJ_FLAG_HIDDEN);
    }
}

void ui_event_calibrateButtonGreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        calibrateHigh(e); // Main logic
        // Go to Home Screen
        lv_scr_load_anim(ui_homeScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
        resetMax(e);
    }
}

void ui_event_dynoStartButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        resetMax(e);
        startDyno(e);
        lv_scr_load_anim(ui_dynoRunGaugeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_dynoStartHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_scr_load_anim(ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_freestyleHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_scr_load_anim(ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_freestyleChartButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        drawChart(e);
        lv_scr_load_anim(ui_ChartScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_chartResetButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        resetMax(e);
        drawChart(e);
    }
}

void ui_event_dynoRunGaugeBackButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_scr_load_anim(ui_dynoRunScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_dynoRunChartButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        drawChart(e);
        lv_scr_load_anim(ui_ChartScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_chartScreenHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_scr_load_anim(ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_settingsHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        lv_scr_load_anim(ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_event_settingsChartButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    if(event_code == LV_EVENT_CLICKED) {
        drawChart(e);
        lv_scr_load_anim(ui_ChartScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
    }
}

void ui_init(void)
{
    // Initialize Theme
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    // Initialize Screens
    ui_settingsScreen_screen_init();
    ui_homeScreen_screen_init();
    ui_calibrationScreen_screen_init();
    ui_dynoRunScreen_screen_init();
    ui_freestyleScreen_screen_init();
    ui_dynoRunGaugeScreen_screen_init();
    ui_ChartScreen_screen_init();

    // Load Start Screen (Settings)
    lv_disp_load_scr(ui_settingsScreen);
}