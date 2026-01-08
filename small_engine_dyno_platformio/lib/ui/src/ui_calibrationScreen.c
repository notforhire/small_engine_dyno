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
    lv_obj_add_flag(ui_calibrationPageHomeButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_calibrationPageHomeButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_calibrationPageHomeButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrationPageHomeButtonLabel = lv_label_create(ui_calibrationPageHomeButton);
    lv_obj_set_align(ui_calibrationPageHomeButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_calibrationPageHomeButtonLabel, "Home");
    lv_obj_set_style_text_font(ui_calibrationPageHomeButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- INSTRUCTIONS ---
    ui_calibrationInstructions = lv_textarea_create(ui_calibrationScreen);
    lv_obj_set_width(ui_calibrationInstructions, 445);
    lv_obj_set_height(ui_calibrationInstructions, 380);
    lv_obj_set_x(ui_calibrationInstructions, 135);
    lv_obj_set_y(ui_calibrationInstructions, -40);
    lv_obj_set_align(ui_calibrationInstructions, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_calibrationInstructions,
    "Calibrating the dyno is very important to getting meaningful numbers. You MUST complete this process every time you turn the dyno on, and should never suffer any issues from doing so multiple times during each use. Begin by pressing the \"Set Zero\" button to set the zero of the scale. Confirmation of succesfully setting zero comes via the \"Calibrate\" button changing from white, and unclickable, to green. Next, install the calibration arm on the shaft and assure that it is fairly level while locking the brake on. Hang the weight from the hook of the calibration arm. Once everything settles press the \"Calibrate\" button. Once calibration is complete you will automatically be returned to the home page.");    lv_obj_set_style_text_font(ui_calibrationInstructions, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_calibrationInstructions, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_calibrationInstructions, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_calibrationInstructions, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_calibrationInstructions, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_calibrationInstructions, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_calibrationInstructions, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_calibrationInstructions, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_calibrationInstructions, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_calibrationInstructions, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_calibrationInstructions, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- GAUGE ---
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

    // --- WEIGHT INPUT ---
    ui_calWeightTitle = lv_label_create(ui_calibrationScreen);
    lv_obj_set_align(ui_calWeightTitle, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_calWeightTitle, -160); 
    lv_obj_set_y(ui_calWeightTitle, 210);
    lv_label_set_text(ui_calWeightTitle, "Enter Weight (lbs)");
    lv_obj_set_style_text_font(ui_calWeightTitle, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calWeightTextArea = lv_textarea_create(ui_calibrationScreen);
    lv_obj_set_width(ui_calWeightTextArea, 90);
    lv_obj_set_height(ui_calWeightTextArea, 50);
    lv_obj_set_x(ui_calWeightTextArea, -155);
    lv_obj_set_y(ui_calWeightTextArea, 160);
    lv_obj_set_align(ui_calWeightTextArea, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_calWeightTextArea, "20.0");
    lv_textarea_set_placeholder_text(ui_calWeightTextArea, "20.0");
    lv_textarea_set_one_line(ui_calWeightTextArea, true);
    lv_obj_set_style_text_font(ui_calWeightTextArea, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_calWeightTextArea, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_calWeightTextArea, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_calWeightTextArea, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_calWeightTextArea, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_calWeightTextArea, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_calWeightTextArea, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_calWeightTextArea, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_calWeightTextArea, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_calWeightTextArea, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_calWeightTextArea, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_calWeightTextArea, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- BUTTONS ---
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
    lv_obj_set_align(ui_calibrateButtonWhiteLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_calibrateButtonWhiteLabel, "Calibrate");
    lv_obj_set_style_text_font(ui_calibrateButtonWhiteLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- KEYBOARD (UPDATED STYLE) ---
    ui_calibrationKeyboard = lv_keyboard_create(ui_calibrationScreen);
    lv_keyboard_set_mode(ui_calibrationKeyboard, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_set_width(ui_calibrationKeyboard, 240); // Portrait
    lv_obj_set_height(ui_calibrationKeyboard, 320); 
    lv_obj_set_align(ui_calibrationKeyboard, LV_ALIGN_RIGHT_MID); // Left Side
    lv_obj_set_x(ui_calibrationKeyboard, -40); // Small Padding
    lv_obj_add_flag(ui_calibrationKeyboard, LV_OBJ_FLAG_HIDDEN);
    
    // Background Frame: Black with Red Border
    lv_obj_set_style_radius(ui_calibrationKeyboard, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_calibrationKeyboard, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_calibrationKeyboard, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_calibrationKeyboard, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_calibrationKeyboard, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_calibrationKeyboard, 20, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Keys (Items): Dark Grey with Black Trim
    lv_obj_set_style_border_color(ui_calibrationKeyboard, lv_color_hex(0x660000), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_calibrationKeyboard, 100, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_calibrationKeyboard, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_calibrationKeyboard, 5, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_calibrationKeyboard, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    // REMOVED custom font to allow default symbols (Check/Arrow) to render properly
    
    // Press State
    lv_obj_set_style_bg_color(ui_calibrationKeyboard, lv_color_hex(0xFF0000), LV_PART_ITEMS | LV_STATE_PRESSED);
    
    extern void ui_event_keyboard(lv_event_t * e); 
    lv_obj_add_event_cb(ui_calibrationKeyboard, ui_event_keyboard, LV_EVENT_ALL, NULL);

    // --- EVENTS ---
    lv_obj_add_event_cb(ui_calWeightTextArea, cal_weight_update, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(ui_calWeightTextArea, cal_weight_update, LV_EVENT_READY, NULL);
    lv_obj_add_event_cb(ui_calibrationPageHomeButton, ui_event_calibrationPageHomeButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_setZeroButton, ui_event_setZeroButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_calibrateButtonGreen, ui_event_calibrateButtonGreen, LV_EVENT_ALL, NULL);
}