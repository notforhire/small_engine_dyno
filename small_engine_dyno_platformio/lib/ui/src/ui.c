#include "ui.h"
#include "ui_helpers.h"

void ui_settingsScreen_screen_init(void);
lv_obj_t * ui_settingsScreen;
void ui_event_continueButton(lv_event_t * e);
lv_obj_t * ui_continueButton;
lv_obj_t * ui_continueButtonLabel;
void ui_event_rpmRangeSwitch(lv_event_t * e);
lv_obj_t * ui_rpmRangeSwitch;
lv_obj_t * ui_firstGreenButton;
lv_obj_t * ui_firstGreenButtonLabel;
void ui_event_firstWhiteButton(lv_event_t * e);
lv_obj_t * ui_firstWhiteButton;
lv_obj_t * ui_firstWhiteButtonLabel;
lv_obj_t * ui_secondGreenButton;
lv_obj_t * ui_secondGreenButtonLabel;
void ui_event_secondWhiteButton(lv_event_t * e);
lv_obj_t * ui_secondWhiteButton;
lv_obj_t * ui_secondWhiteButtonLabel;
lv_obj_t * ui_thirdGreenButton;
lv_obj_t * ui_thirdGreenButtonLabel;
void ui_event_thirdWhiteButton(lv_event_t * e);
lv_obj_t * ui_thirdWhiteButton;
lv_obj_t * ui_thirdWhiteButtonLabel;
lv_obj_t * ui_fourthGreenButton;
lv_obj_t * ui_fourthGreenButtonLabel;
void ui_event_fourthWhiteButton(lv_event_t * e);
lv_obj_t * ui_fourthWhiteButton;
lv_obj_t * ui_fourthWhiteButtonLabel;
lv_obj_t * ui_settingsInstructions;
lv_obj_t * ui_rpmHighLabel;
lv_obj_t * ui_rpmLowLabel;
void ui_event_settingsChartButton(lv_event_t * e);
lv_obj_t * ui_settingsChartButton;
lv_obj_t * ui_settingsChartButtonLabel;
void ui_event_settingsHomeButton(lv_event_t * e);
lv_obj_t * ui_settingsHomeButton;
lv_obj_t * ui_settingsHomeButtonLabel;

void ui_homeScreen_screen_init(void);
lv_obj_t * ui_homeScreen;
void ui_event_dynoRunButton(lv_event_t * e);
lv_obj_t * ui_dynoRunButton;
lv_obj_t * ui_dynoRunButtonLabel;
void ui_event_settingsButton(lv_event_t * e);
lv_obj_t * ui_settingsButton;
lv_obj_t * ui_settingsButtonLabel;
void ui_event_freestyleButton(lv_event_t * e);
lv_obj_t * ui_freestyleButton;
lv_obj_t * ui_freestyleButtonLabel;
void ui_event_calibrateButton(lv_event_t * e);
lv_obj_t * ui_calibrateButton;
lv_obj_t * ui_calibrateButtonLabel;
lv_obj_t * ui_calibrationWarning;
lv_obj_t * ui_safetyAdvisement;
lv_obj_t * ui_dumbFriendWarning;

void ui_calibrationScreen_screen_init(void);
lv_obj_t * ui_calibrationScreen;
void ui_event_calibrationPageHomeButton(lv_event_t * e);
lv_obj_t * ui_calibrationPageHomeButton;
lv_obj_t * ui_calibrationPageHomeButtonLabel;
lv_obj_t * ui_calibrationInstructions;
lv_obj_t * ui_calibrationGauge;
lv_obj_t * ui_calibrationGaugeNeedle;
void ui_event_setZeroButton(lv_event_t * e);
lv_obj_t * ui_setZeroButton;
lv_obj_t * ui_setZeroButtonLabel;
void ui_event_calibrateButtonGreen(lv_event_t * e);
lv_obj_t * ui_calibrateButtonGreen;
lv_obj_t * ui_calibrateButtonGreenLabel;
lv_obj_t * ui_calibrateButtonWhite;
lv_obj_t * ui_calibrateButtonWhiteLabel;
lv_obj_t * ui_calibrationScreenGaugeArc;

void ui_dynoRunScreen_screen_init(void);
lv_obj_t * ui_dynoRunScreen;
void ui_event_dynoStartButton(lv_event_t * e);
lv_obj_t * ui_dynoStartButton;
lv_obj_t * ui_dynoStartButtonLabel;
void ui_event_dynoStartHomeButton(lv_event_t * e);
lv_obj_t * ui_dynoStartHomeButton;
lv_obj_t * ui_dynoStartHomeButtonLabel;
lv_obj_t * ui_dynoRunDirections;

void ui_freestyleScreen_screen_init(void);
lv_obj_t * ui_freestyleScreen;
lv_obj_t * ui_freestyleTorqueGauge;
lv_obj_t * ui_freestyleTorqueGaugeNeedle;
lv_obj_t * ui_freestyleHorsepowerGauge;
lv_obj_t * ui_freestyleHorsepowerGaugeNeedle;
lv_obj_t * ui_freestyleRpmGauge;
lv_obj_t * ui_freestyleRpmGaugeNeedle;
void ui_event_freestyleHomeButton(lv_event_t * e);
lv_obj_t * ui_freestyleHomeButton;
lv_obj_t * ui_freestyleHomeButtonLabel;
void ui_event_freestyleChartButton(lv_event_t * e);
lv_obj_t * ui_freestyleChartButton;
lv_obj_t * ui_freestyleChartButtonLabel;
lv_obj_t * ui_freestyleTorquelabel;
lv_obj_t * ui_freestyleHorsepowerLabel;
lv_obj_t * ui_freestyleTorqueField;
lv_obj_t * ui_freestyleTorqueRpmField;
lv_obj_t * ui_freestyleHorsepowerField;
lv_obj_t * ui_freestyleHorsepowerRpmField;
lv_obj_t * ui_freestyleSmallHorsepowerGauge;
lv_obj_t * ui_freestyleSmallHorsepowerGaugeNeedle;
lv_obj_t * ui_freestyleSmallTorqueGauge;
lv_obj_t * ui_freestyleSmallTorqueGaugeNeedle;
void ui_event_rangeSelectSwitch(lv_event_t * e);
lv_obj_t * ui_rangeSelectSwitch;
lv_obj_t * ui_highLabel;
lv_obj_t * ui_lowLabel;
lv_obj_t * ui_rangeSelectLabel;
lv_obj_t * ui_freestyleRpmGaugeArc;
lv_obj_t * ui_freestyleHorsepowerGaugeArc;
lv_obj_t * ui_freestyleTorqueGaugeArc;
lv_obj_t * ui_gaugeLabel;

void ui_dynoRunGaugeScreen_screen_init(void);
lv_obj_t * ui_dynoRunGaugeScreen;
void ui_event_dynoRunGaugeBackButton(lv_event_t * e);
lv_obj_t * ui_dynoRunGaugeBackButton;
lv_obj_t * ui_dynoRunGaugeBackButtonLabel;
void ui_event_dynoRunChartButton(lv_event_t * e);
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

void ui_ChartScreen_screen_init(void);
lv_obj_t * ui_ChartScreen;
void ui_event_chartScreenHomeButton(lv_event_t * e);
lv_obj_t * ui_chartScreenHomeButton;
lv_obj_t * ui_chartScreenHomeButtonLabel;
lv_obj_t * ui_chartScreenMapHplabel;
lv_obj_t * ui_chartScreenMaxTorqueLabel;
lv_obj_t * ui_chartScreenMaxTorqueField;
lv_obj_t * ui_chartScreenMaxHpField;
void ui_event_chartResetButton(lv_event_t * e);
lv_obj_t * ui_chartResetButton;
lv_obj_t * ui_chartResetButtonLabel;
lv_obj_t * ui_chartScreenMaxHpRpmField;
lv_obj_t * ui_chartScreenMaxTorqueRpmField;
lv_obj_t * ui_chartScreenChartXLabel;
lv_obj_t * ui____initial_actions0;
const lv_img_dsc_t * ui_imgset_carbon_fiber[1] = {&ui_img_carbon_fiber3_png};

void ui_event_continueButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_calibrateButtonGreen, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_calibrateButtonWhite, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_screen_change(&ui_calibrationScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_calibrationScreen_screen_init);
    }
}
void ui_event_rpmRangeSwitch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        rpmRangeSelect(e);
    }
}
void ui_event_firstWhiteButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        firstTorqueRange(e);
        _ui_flag_modify(ui_firstWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_firstGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_secondGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_secondWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_thirdWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_thirdGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_fourthWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_fourthGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_secondWhiteButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        secondTorqueRange(e);
        _ui_flag_modify(ui_secondWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_secondGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_firstGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_firstWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_thirdWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_thirdGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_fourthWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_fourthGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_thirdWhiteButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        thirdTorqueRange(e);
        _ui_flag_modify(ui_thirdWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_thirdGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_firstGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_firstWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_secondGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_secondWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_fourthWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_fourthGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_fourthWhiteButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        fourthTorqueRange(e);
        _ui_flag_modify(ui_fourthWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_fourthGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_firstGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_firstWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_secondGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_secondWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_thirdWhiteButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_thirdGreenButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

void ui_event_dynoRunButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_dynoRunScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_dynoRunScreen_screen_init);
    }
}
void ui_event_settingsButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_settingsScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_settingsScreen_screen_init);
    }
}
void ui_event_freestyleButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        resetMax(e);
        _ui_screen_change(&ui_freestyleScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_freestyleScreen_screen_init);
    }
}
void ui_event_calibrateButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_calibrationScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_calibrationScreen_screen_init);
        _ui_flag_modify(ui_calibrateButtonGreen, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_calibrateButtonWhite, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_calibrationPageHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_homeScreen_screen_init);
    }
}
void ui_event_setZeroButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        calibrateLow(e);
        _ui_flag_modify(ui_calibrateButtonWhite, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
        _ui_flag_modify(ui_calibrateButtonGreen, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_calibrateButtonGreen(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        calibrateHigh(e);
        _ui_screen_change(&ui_homeScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_homeScreen_screen_init);
        _ui_flag_modify(ui_calibrationPageHomeButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_settingsHomeButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        _ui_flag_modify(ui_settingsChartButton, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
        resetMax(e);
    }
}
void ui_event_dynoStartButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        resetMax(e);
        startDyno(e);
        _ui_screen_change(&ui_dynoRunGaugeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_dynoRunGaugeScreen_screen_init);
    }
}
void ui_event_dynoStartHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_homeScreen_screen_init);
    }
}
void ui_event_freestyleHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_homeScreen_screen_init);
    }
}
void ui_event_freestyleChartButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        drawChart(e);
        _ui_screen_change(&ui_ChartScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_ChartScreen_screen_init);
    }
}
void ui_event_chartResetButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        resetMax(e);
        drawChart(e);
    }
}
void ui_event_rangeSelectSwitch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        gaugeSelect(e);
    }
}
void ui_event_dynoRunGaugeBackButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_dynoRunScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_dynoRunScreen_screen_init);
    }
}
void ui_event_dynoRunChartButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        drawChart(e);
        _ui_screen_change(&ui_ChartScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_ChartScreen_screen_init);
    }
}
void ui_event_chartScreenHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_homeScreen_screen_init);
    }
}

void ui_event_settingsHomeButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_homeScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_homeScreen_screen_init);
    }
}

void ui_event_settingsChartButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        drawChart(e);
        _ui_screen_change(&ui_ChartScreen, LV_SCR_LOAD_ANIM_NONE, 10, 0, &ui_ChartScreen_screen_init);
    }
}

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_settingsScreen_screen_init();
    ui_homeScreen_screen_init();
    ui_calibrationScreen_screen_init();
    ui_dynoRunScreen_screen_init();
    ui_freestyleScreen_screen_init();
    ui_dynoRunGaugeScreen_screen_init();
    ui_ChartScreen_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_settingsScreen);
}
