#include "ui.h"

void ui_ChartScreen_screen_init(void)
{
    ui_ChartScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_img_src(ui_ChartScreen, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- HOME BUTTON ---
    ui_chartScreenHomeButton = lv_img_create(ui_ChartScreen);
    lv_img_set_src(ui_chartScreenHomeButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_chartScreenHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_chartScreenHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_chartScreenHomeButton, 320);
    lv_obj_set_y(ui_chartScreenHomeButton, 195);
    lv_obj_set_align(ui_chartScreenHomeButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_chartScreenHomeButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_chartScreenHomeButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chartScreenHomeButtonLabel = lv_label_create(ui_chartScreenHomeButton);
    lv_obj_set_align(ui_chartScreenHomeButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_chartScreenHomeButtonLabel, "Home");
    lv_obj_set_style_text_font(ui_chartScreenHomeButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- RESET BUTTON ---
    ui_chartResetButton = lv_img_create(ui_ChartScreen);
    lv_img_set_src(ui_chartResetButton, &ui_img_gray_button_long_png);
    lv_obj_set_width(ui_chartResetButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_chartResetButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_chartResetButton, 170);
    lv_obj_set_y(ui_chartResetButton, 195);
    lv_obj_set_align(ui_chartResetButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_chartResetButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_chartResetButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_chartResetButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chartResetButtonLabel = lv_label_create(ui_chartResetButton);
    lv_obj_set_align(ui_chartResetButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_chartResetButtonLabel, "Reset");
    lv_obj_set_style_text_font(ui_chartResetButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- MAX VALUE LABELS ---
    ui_chartScreenMapHplabel = lv_label_create(ui_ChartScreen);
    lv_obj_set_x(ui_chartScreenMapHplabel, -126);
    lv_obj_set_y(ui_chartScreenMapHplabel, 215);
    lv_obj_set_align(ui_chartScreenMapHplabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_chartScreenMapHplabel, "Max Horsepower:               @              RPM");
    lv_obj_set_style_text_font(ui_chartScreenMapHplabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_chartScreenMapHplabel, lv_color_hex(0x1E00FE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_chartScreenMapHplabel, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chartScreenMaxTorqueLabel = lv_label_create(ui_ChartScreen);
    lv_obj_set_x(ui_chartScreenMaxTorqueLabel, -125);
    lv_obj_set_y(ui_chartScreenMaxTorqueLabel, 165);
    lv_obj_set_align(ui_chartScreenMaxTorqueLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_chartScreenMaxTorqueLabel, "Max ft/lbs Torque:               @              RPM");
    lv_obj_set_style_text_font(ui_chartScreenMaxTorqueLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_chartScreenMaxTorqueLabel, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_chartScreenMaxTorqueLabel, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- DATA FIELDS ---
    ui_chartScreenMaxTorqueField = lv_textarea_create(ui_ChartScreen);
    lv_obj_set_width(ui_chartScreenMaxTorqueField, 92);
    lv_obj_set_height(ui_chartScreenMaxTorqueField, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_chartScreenMaxTorqueField, -100);
    lv_obj_set_y(ui_chartScreenMaxTorqueField, 165);
    lv_obj_set_align(ui_chartScreenMaxTorqueField, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_chartScreenMaxTorqueField, "39.99");
    lv_textarea_set_one_line(ui_chartScreenMaxTorqueField, true);
    lv_obj_set_style_text_color(ui_chartScreenMaxTorqueField, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_chartScreenMaxTorqueField, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_chartScreenMaxTorqueField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_chartScreenMaxTorqueField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chartScreenMaxHpField = lv_textarea_create(ui_ChartScreen);
    lv_obj_set_width(ui_chartScreenMaxHpField, 119);
    lv_obj_set_height(ui_chartScreenMaxHpField, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_chartScreenMaxHpField, -89);
    lv_obj_set_y(ui_chartScreenMaxHpField, 215);
    lv_obj_set_align(ui_chartScreenMaxHpField, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_chartScreenMaxHpField, "39.99");
    lv_textarea_set_one_line(ui_chartScreenMaxHpField, true);
    lv_obj_set_style_text_font(ui_chartScreenMaxHpField, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_chartScreenMaxHpField, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_chartScreenMaxHpField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_chartScreenMaxHpField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chartScreenMaxHpRpmField = lv_textarea_create(ui_ChartScreen);
    lv_obj_set_width(ui_chartScreenMaxHpRpmField, 89);
    lv_obj_set_height(ui_chartScreenMaxHpRpmField, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_chartScreenMaxHpRpmField, 1);
    lv_obj_set_y(ui_chartScreenMaxHpRpmField, 215);
    lv_obj_set_align(ui_chartScreenMaxHpRpmField, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_chartScreenMaxHpRpmField, "9999");
    lv_textarea_set_one_line(ui_chartScreenMaxHpRpmField, true);
    lv_obj_set_style_text_font(ui_chartScreenMaxHpRpmField, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_chartScreenMaxHpRpmField, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_chartScreenMaxHpRpmField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_chartScreenMaxHpRpmField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_chartScreenMaxTorqueRpmField = lv_textarea_create(ui_ChartScreen);
    lv_obj_set_width(ui_chartScreenMaxTorqueRpmField, 90);
    lv_obj_set_height(ui_chartScreenMaxTorqueRpmField, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_chartScreenMaxTorqueRpmField, 5);
    lv_obj_set_y(ui_chartScreenMaxTorqueRpmField, 165);
    lv_obj_set_align(ui_chartScreenMaxTorqueRpmField, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_chartScreenMaxTorqueRpmField, "9999");
    lv_textarea_set_one_line(ui_chartScreenMaxTorqueRpmField, true);
    lv_obj_set_style_text_font(ui_chartScreenMaxTorqueRpmField, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_chartScreenMaxTorqueRpmField, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_chartScreenMaxTorqueRpmField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_chartScreenMaxTorqueRpmField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_chartScreenHomeButton, ui_event_chartScreenHomeButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_chartResetButton, ui_event_chartResetButton, LV_EVENT_ALL, NULL);
}