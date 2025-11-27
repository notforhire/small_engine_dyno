#include "ui.h"

void ui_calibrationScreen_screen_init(void)
{
    ui_calibrationScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_img_src(ui_calibrationScreen, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrationPageHomeButton = lv_img_create(ui_calibrationScreen);
    lv_img_set_src(ui_calibrationPageHomeButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_calibrationPageHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_calibrationPageHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_calibrationPageHomeButton, 320);
    lv_obj_set_y(ui_calibrationPageHomeButton, 195);
    lv_obj_set_align(ui_calibrationPageHomeButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_calibrationPageHomeButton, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_calibrationPageHomeButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_calibrationPageHomeButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrationPageHomeButtonLabel = lv_label_create(ui_calibrationPageHomeButton);
    lv_obj_set_width(ui_calibrationPageHomeButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_calibrationPageHomeButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_calibrationPageHomeButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_calibrationPageHomeButtonLabel, "Home");
    lv_obj_set_style_text_font(ui_calibrationPageHomeButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrationInstructions = lv_textarea_create(ui_calibrationScreen);
    lv_obj_set_width(ui_calibrationInstructions, 445);
    lv_obj_set_height(ui_calibrationInstructions, 380);
    lv_obj_set_x(ui_calibrationInstructions, 135);
    lv_obj_set_y(ui_calibrationInstructions, -40);
    lv_obj_set_align(ui_calibrationInstructions, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_calibrationInstructions,
    "Calibrating the dyno is very important to getting meaningful numbers. You MUST complete this process every time you turn the dyno on, and should never suffer any issues from doing so multiple times during each use. Begin by pressing the \"Set Zero\" button to set the zero of the scale. Confirmation of succesfully setting zero comes via the \"Calibrate\" button changing from white, and unclickable, to green. Next, install the calibration arm on the shaft and assure that it is level while locking the brake on. Hang the 20 pound weight from the hook of the calibration arm. Once everything settles press the \"Calibrate\" button. Once calibration is complete you will automatically be returned to the home page.");
    lv_obj_set_style_text_font(ui_calibrationInstructions, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_calibrationInstructions, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_calibrationInstructions, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_calibrationInstructions, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_calibrationInstructions, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_calibrationInstructions, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_calibrationInstructions, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_calibrationInstructions, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_calibrationInstructions, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_calibrationInstructions, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_calibrationInstructions, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrationGauge = lv_img_create(ui_calibrationScreen);
    lv_img_set_src(ui_calibrationGauge, &ui_img_hp_gauge_png);
    lv_obj_set_width(ui_calibrationGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_calibrationGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_calibrationGauge, -235);
    lv_obj_set_y(ui_calibrationGauge, -90);
    lv_obj_set_align(ui_calibrationGauge, LV_ALIGN_CENTER);

    ui_calibrationGaugeNeedle = lv_img_create(ui_calibrationGauge);
    lv_img_set_src(ui_calibrationGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_calibrationGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_calibrationGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_calibrationGaugeNeedle, 0);
    lv_obj_set_y(ui_calibrationGaugeNeedle, 78);
    lv_obj_set_align(ui_calibrationGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_calibrationGaugeNeedle, 10, -36);

    ui_setZeroButton = lv_img_create(ui_calibrationScreen);
    lv_img_set_src(ui_setZeroButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_setZeroButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_setZeroButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_setZeroButton, -320);
    lv_obj_set_y(ui_setZeroButton, 195);
    lv_obj_set_align(ui_setZeroButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_setZeroButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_setZeroButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_setZeroButton, 190, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_setZeroButtonLabel = lv_label_create(ui_setZeroButton);
    lv_obj_set_width(ui_setZeroButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_setZeroButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_setZeroButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_setZeroButtonLabel, "Set Zero");
    lv_obj_set_style_text_font(ui_setZeroButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrateButtonGreen = lv_img_create(ui_calibrationScreen);
    lv_img_set_src(ui_calibrateButtonGreen, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_calibrateButtonGreen, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_calibrateButtonGreen, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_calibrateButtonGreen, 0);
    lv_obj_set_y(ui_calibrateButtonGreen, 195);
    lv_obj_set_align(ui_calibrateButtonGreen, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_calibrateButtonGreen, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_calibrateButtonGreen, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_calibrateButtonGreen, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrateButtonGreenLabel = lv_label_create(ui_calibrateButtonGreen);
    lv_obj_set_width(ui_calibrateButtonGreenLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_calibrateButtonGreenLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_calibrateButtonGreenLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_calibrateButtonGreenLabel, "Calibrate");
    lv_obj_set_style_text_font(ui_calibrateButtonGreenLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrateButtonWhite = lv_img_create(ui_calibrationScreen);
    lv_img_set_src(ui_calibrateButtonWhite, &ui_img_gray_button_long_png);
    lv_obj_set_width(ui_calibrateButtonWhite, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_calibrateButtonWhite, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_calibrateButtonWhite, 0);
    lv_obj_set_y(ui_calibrateButtonWhite, 195);
    lv_obj_set_align(ui_calibrateButtonWhite, LV_ALIGN_CENTER);
    lv_obj_set_style_blend_mode(ui_calibrateButtonWhite, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_calibrateButtonWhite, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrateButtonWhiteLabel = lv_label_create(ui_calibrateButtonWhite);
    lv_obj_set_width(ui_calibrateButtonWhiteLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_calibrateButtonWhiteLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_calibrateButtonWhiteLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_calibrateButtonWhiteLabel, "Calibrate");
    lv_obj_set_style_text_font(ui_calibrateButtonWhiteLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrationScreenGaugeArc = lv_arc_create(ui_calibrationScreen);
    lv_obj_set_width(ui_calibrationScreenGaugeArc, 250);
    lv_obj_set_height(ui_calibrationScreenGaugeArc, 250);
    lv_obj_set_x(ui_calibrationScreenGaugeArc, -235);
    lv_obj_set_y(ui_calibrationScreenGaugeArc, -90);
    lv_obj_set_align(ui_calibrationScreenGaugeArc, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_calibrationScreenGaugeArc, 0);
    lv_arc_set_bg_angles(ui_calibrationScreenGaugeArc, 0, 360);
    lv_obj_set_style_opa(ui_calibrationScreenGaugeArc, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_calibrationScreenGaugeArc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui_calibrationScreenGaugeArc, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_calibrationScreenGaugeArc, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_calibrationScreenGaugeArc, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_calibrationScreenGaugeArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_calibrationPageHomeButton, ui_event_calibrationPageHomeButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_setZeroButton, ui_event_setZeroButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_calibrateButtonGreen, ui_event_calibrateButtonGreen, LV_EVENT_ALL, NULL);

}
