#ifndef _DYNO_UI_H
#define _DYNO_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"

void ui_settingsScreen_screen_init(void);
extern lv_obj_t * ui_settingsScreen;
void ui_event_continueButton(lv_event_t * e);
extern lv_obj_t * ui_continueButton;
extern lv_obj_t * ui_continueButtonLabel;
void ui_event_rpmRangeSwitch(lv_event_t * e);
extern lv_obj_t * ui_rpmRangeSwitch;
extern lv_obj_t * ui_firstGreenButton;
extern lv_obj_t * ui_firstGreenButtonLabel;
void ui_event_firstWhiteButton(lv_event_t * e);
extern lv_obj_t * ui_firstWhiteButton;
extern lv_obj_t * ui_firstWhiteButtonLabel;
extern lv_obj_t * ui_secondGreenButton;
extern lv_obj_t * ui_secondGreenButtonLabel;
void ui_event_secondWhiteButton(lv_event_t * e);
extern lv_obj_t * ui_secondWhiteButton;
extern lv_obj_t * ui_secondWhiteButtonLabel;
extern lv_obj_t * ui_thirdGreenButton;
extern lv_obj_t * ui_thirdGreenButtonLabel;
void ui_event_thirdWhiteButton(lv_event_t * e);
extern lv_obj_t * ui_thirdWhiteButton;
extern lv_obj_t * ui_thirdWhiteButtonLabel;
extern lv_obj_t * ui_fourthGreenButton;
extern lv_obj_t * ui_fourthGreenButtonLabel;
void ui_event_fourthWhiteButton(lv_event_t * e);
extern lv_obj_t * ui_fourthWhiteButton;
extern lv_obj_t * ui_fourthWhiteButtonLabel;
extern lv_obj_t * ui_settingsInstructions;
extern lv_obj_t * ui_rpmHighLabel;
extern lv_obj_t * ui_rpmLowLabel;
void ui_event_settingsChartButton(lv_event_t * e);
extern lv_obj_t * ui_settingsChartButton;
extern lv_obj_t * ui_settingsChartButtonLabel;
void ui_event_settingsHomeButton(lv_event_t * e);
extern lv_obj_t * ui_settingsHomeButton;
extern lv_obj_t * ui_settingsHomeButtonLabel;

void ui_homeScreen_screen_init(void);
extern lv_obj_t * ui_homeScreen;
void ui_event_dynoRunButton(lv_event_t * e);
extern lv_obj_t * ui_dynoRunButton;
extern lv_obj_t * ui_dynoRunButtonLabel;
void ui_event_settingsButton(lv_event_t * e);
extern lv_obj_t * ui_settingsButton;
extern lv_obj_t * ui_settingsButtonLabel;
void ui_event_freestyleButton(lv_event_t * e);
extern lv_obj_t * ui_freestyleButton;
extern lv_obj_t * ui_freestyleButtonLabel;
void ui_event_calibrateButton(lv_event_t * e);
extern lv_obj_t * ui_calibrateButton;
extern lv_obj_t * ui_calibrateButtonLabel;
extern lv_obj_t * ui_calibrationWarning;
extern lv_obj_t * ui_safetyAdvisement;
extern lv_obj_t * ui_dumbFriendWarning;

void ui_calibrationScreen_screen_init(void);
extern lv_obj_t * ui_calibrationScreen;
void ui_event_calibrationPageHomeButton(lv_event_t * e);
extern lv_obj_t * ui_calibrationPageHomeButton;
extern lv_obj_t * ui_calibrationPageHomeButtonLabel;
extern lv_obj_t * ui_calibrationInstructions;
extern lv_obj_t * ui_calibrationGauge;
extern lv_obj_t * ui_calibrationGaugeNeedle;
void ui_event_setZeroButton(lv_event_t * e);
extern lv_obj_t * ui_setZeroButton;
extern lv_obj_t * ui_setZeroButtonLabel;
void ui_event_calibrateButtonGreen(lv_event_t * e);
extern lv_obj_t * ui_calibrateButtonGreen;
extern lv_obj_t * ui_calibrateButtonGreenLabel;
extern lv_obj_t * ui_calibrateButtonWhite;
extern lv_obj_t * ui_calibrateButtonWhiteLabel;
extern lv_obj_t * ui_calibrationScreenGaugeArc;

void ui_dynoRunScreen_screen_init(void);
extern lv_obj_t * ui_dynoRunScreen;
void ui_event_dynoStartButton(lv_event_t * e);
extern lv_obj_t * ui_dynoStartButton;
extern lv_obj_t * ui_dynoStartButtonLabel;
void ui_event_dynoStartHomeButton(lv_event_t * e);
extern lv_obj_t * ui_dynoStartHomeButton;
extern lv_obj_t * ui_dynoStartHomeButtonLabel;
extern lv_obj_t * ui_dynoRunDirections;

void ui_freestyleScreen_screen_init(void);
extern lv_obj_t * ui_freestyleScreen;
extern lv_obj_t * ui_freestyleTorqueGauge;
extern lv_obj_t * ui_freestyleTorqueGaugeNeedle;
extern lv_obj_t * ui_freestyleHorsepowerGauge;
extern lv_obj_t * ui_freestyleHorsepowerGaugeNeedle;
extern lv_obj_t * ui_freestyleRpmGauge;
extern lv_obj_t * ui_freestyleRpmGaugeNeedle;
void ui_event_freestyleHomeButton(lv_event_t * e);
extern lv_obj_t * ui_freestyleHomeButton;
extern lv_obj_t * ui_freestyleHomeButtonLabel;
void ui_event_freestyleChartButton(lv_event_t * e);
extern lv_obj_t * ui_freestyleChartButton;
extern lv_obj_t * ui_freestyleChartButtonLabel;
extern lv_obj_t * ui_freestyleTorquelabel;
extern lv_obj_t * ui_freestyleHorsepowerLabel;
extern lv_obj_t * ui_freestyleTorqueField;
extern lv_obj_t * ui_freestyleTorqueRpmField;
extern lv_obj_t * ui_freestyleHorsepowerField;
extern lv_obj_t * ui_freestyleHorsepowerRpmField;
extern lv_obj_t * ui_freestyleSmallHorsepowerGauge;
extern lv_obj_t * ui_freestyleSmallHorsepowerGaugeNeedle;
extern lv_obj_t * ui_freestyleSmallTorqueGauge;
extern lv_obj_t * ui_freestyleSmallTorqueGaugeNeedle;
void ui_event_rangeSelectSwitch(lv_event_t * e);
extern lv_obj_t * ui_rangeSelectSwitch;
extern lv_obj_t * ui_highLabel;
extern lv_obj_t * ui_lowLabel;
extern lv_obj_t * ui_rangeSelectLabel;
extern lv_obj_t * ui_freestyleRpmGaugeArc;
extern lv_obj_t * ui_freestyleHorsepowerGaugeArc;
extern lv_obj_t * ui_freestyleTorqueGaugeArc;
extern lv_obj_t * ui_gaugeLabel;

void ui_dynoRunGaugeScreen_screen_init(void);
extern lv_obj_t * ui_dynoRunGaugeScreen;
void ui_event_dynoRunGaugeBackButton(lv_event_t * e);
extern lv_obj_t * ui_dynoRunGaugeBackButton;
extern lv_obj_t * ui_dynoRunGaugeBackButtonLabel;
void ui_event_dynoRunChartButton(lv_event_t * e);
extern lv_obj_t * ui_dynoRunChartButton;
extern lv_obj_t * ui_dynoRunChartButtonLabel;
extern lv_obj_t * ui_dynoRunRpmGauge;
extern lv_obj_t * ui_dynoRunRpmGaugeNeedle;
extern lv_obj_t * ui_dynoRunRpmGaugeLabel;
extern lv_obj_t * ui_dynoRunTorqueGauge;
extern lv_obj_t * ui_dynoRunTorqueGaugeNeedle;
extern lv_obj_t * ui_dynoRunTorqueGaugeLabel;
extern lv_obj_t * ui_dynoRunHorsepowerGauge;
extern lv_obj_t * ui_dynoRunHorsepowerGaugeNeedle;
extern lv_obj_t * ui_dynoRunHorsepowerGaugeLabel;
extern lv_obj_t * ui_timeoutBar;
extern lv_obj_t * ui_runTorqueLabel;
extern lv_obj_t * ui_runHorsepowerLabel;
extern lv_obj_t * ui_dynoRunMaxTorqueField;
extern lv_obj_t * ui_dynoRunMaxHorsepowerField;
extern lv_obj_t * ui_atSymbol1;
extern lv_obj_t * ui_atSymbol2;
extern lv_obj_t * ui_dynoRunTorqueMaxRpmField;
extern lv_obj_t * ui_dynoRunHorsepowerMaxRpmField;
extern lv_obj_t * ui_rpmLabel1;
extern lv_obj_t * ui_rpmLabel2;
extern lv_obj_t * ui_dynoRunRpmGaugeArc;
extern lv_obj_t * ui_dynoRunHorsepowerGaugeArc;
extern lv_obj_t * ui_dynoRunTorqueGaugeArc;
extern lv_obj_t * ui_runTimeCounter;
extern lv_obj_t * ui_throttleNotice;
extern lv_obj_t * ui_brakeNowNotice;

void ui_ChartScreen_screen_init(void);
extern lv_obj_t * ui_ChartScreen;
void ui_event_chartScreenHomeButton(lv_event_t * e);
extern lv_obj_t * ui_chartScreenHomeButton;
extern lv_obj_t * ui_chartScreenHomeButtonLabel;
extern lv_obj_t * ui_chartScreenMapHplabel;
extern lv_obj_t * ui_chartScreenMaxTorqueLabel;
extern lv_obj_t * ui_chartScreenMaxTorqueField;
extern lv_obj_t * ui_chartScreenMaxHpField;
void ui_event_chartResetButton(lv_event_t * e);
extern lv_obj_t * ui_chartResetButton;
extern lv_obj_t * ui_chartResetButtonLabel;
extern lv_obj_t * ui_chartScreenMaxHpRpmField;
extern lv_obj_t * ui_chartScreenMaxTorqueRpmField;
extern lv_obj_t * ui____initial_actions0;
extern lv_obj_t * ui_chartScreenChartXLabel;

LV_IMG_DECLARE(ui_img_carbon_fiber3_png);
LV_IMG_DECLARE(ui_img_green_button_long_png);
LV_IMG_DECLARE(ui_img_hp_gauge_png);
LV_IMG_DECLARE(ui_img_gray_button_long_png);
LV_IMG_DECLARE(ui_img_red_button_long_png);
LV_IMG_DECLARE(ui_img_rpm_gauge_png);
LV_IMG_DECLARE(ui_img_hp_gauge_pussy_png);
LV_IMG_DECLARE(ui_img_needle_png);

LV_FONT_DECLARE(ui_font_tomorrow);
LV_FONT_DECLARE(ui_font_tomorrow150);
LV_FONT_DECLARE(ui_font_tomorrow18);
LV_FONT_DECLARE(ui_font_tomorrow28);
LV_FONT_DECLARE(ui_font_tomorrow50);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
