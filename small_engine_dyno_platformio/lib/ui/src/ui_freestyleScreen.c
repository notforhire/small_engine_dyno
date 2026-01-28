#include "ui.h"

void ui_freestyleScreen_screen_init(void)
{
    ui_freestyleScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_img_src(ui_freestyleScreen, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- LARGE TORQUE GAUGE ---
    ui_freestyleTorqueGauge = lv_img_create(ui_freestyleScreen);
    lv_img_set_src(ui_freestyleTorqueGauge, &ui_img_hp_gauge_png);
    lv_obj_set_width(ui_freestyleTorqueGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleTorqueGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleTorqueGauge, -270);
    lv_obj_set_y(ui_freestyleTorqueGauge, -90);
    lv_obj_set_align(ui_freestyleTorqueGauge, LV_ALIGN_CENTER);

    ui_freestyleTorqueGaugeNeedle = lv_img_create(ui_freestyleTorqueGauge);
    lv_img_set_src(ui_freestyleTorqueGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_freestyleTorqueGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleTorqueGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleTorqueGaugeNeedle, 0);
    lv_obj_set_y(ui_freestyleTorqueGaugeNeedle, 78);
    lv_obj_set_align(ui_freestyleTorqueGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_freestyleTorqueGaugeNeedle, 10, -36);

    ui_freestyleTorqueGaugeArc = lv_arc_create(ui_freestyleScreen);
    lv_obj_set_width(ui_freestyleTorqueGaugeArc, 250);
    lv_obj_set_height(ui_freestyleTorqueGaugeArc, 250);
    lv_obj_set_x(ui_freestyleTorqueGaugeArc, -270);
    lv_obj_set_y(ui_freestyleTorqueGaugeArc, -90);
    lv_obj_set_align(ui_freestyleTorqueGaugeArc, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_freestyleTorqueGaugeArc, LV_OBJ_FLAG_CLICKABLE);
    lv_arc_set_value(ui_freestyleTorqueGaugeArc, 0);
    lv_arc_set_bg_angles(ui_freestyleTorqueGaugeArc, 0, 360);
    lv_obj_set_style_opa(ui_freestyleTorqueGaugeArc, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_freestyleTorqueGaugeArc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_freestyleTorqueGaugeArc, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_freestyleTorqueGaugeArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // --- LARGE HORSEPOWER GAUGE ---
    ui_freestyleHorsepowerGauge = lv_img_create(ui_freestyleScreen);
    lv_img_set_src(ui_freestyleHorsepowerGauge, &ui_img_hp_gauge_png);
    lv_obj_set_width(ui_freestyleHorsepowerGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleHorsepowerGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleHorsepowerGauge, 270);
    lv_obj_set_y(ui_freestyleHorsepowerGauge, -90);
    lv_obj_set_align(ui_freestyleHorsepowerGauge, LV_ALIGN_CENTER);

    ui_freestyleHorsepowerGaugeNeedle = lv_img_create(ui_freestyleHorsepowerGauge);
    lv_img_set_src(ui_freestyleHorsepowerGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_freestyleHorsepowerGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleHorsepowerGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleHorsepowerGaugeNeedle, 0);
    lv_obj_set_y(ui_freestyleHorsepowerGaugeNeedle, 78);
    lv_obj_set_align(ui_freestyleHorsepowerGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_freestyleHorsepowerGaugeNeedle, 10, -36);

    ui_freestyleHorsepowerGaugeArc = lv_arc_create(ui_freestyleScreen);
    lv_obj_set_width(ui_freestyleHorsepowerGaugeArc, 250);
    lv_obj_set_height(ui_freestyleHorsepowerGaugeArc, 250);
    lv_obj_set_x(ui_freestyleHorsepowerGaugeArc, 270);
    lv_obj_set_y(ui_freestyleHorsepowerGaugeArc, -90);
    lv_obj_set_align(ui_freestyleHorsepowerGaugeArc, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_freestyleHorsepowerGaugeArc, LV_OBJ_FLAG_CLICKABLE);
    lv_arc_set_value(ui_freestyleHorsepowerGaugeArc, 0);
    lv_arc_set_bg_angles(ui_freestyleHorsepowerGaugeArc, 0, 360);
    lv_obj_set_style_opa(ui_freestyleHorsepowerGaugeArc, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_freestyleHorsepowerGaugeArc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_freestyleHorsepowerGaugeArc, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_freestyleHorsepowerGaugeArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // --- RPM GAUGE ---
    ui_freestyleRpmGauge = lv_img_create(ui_freestyleScreen);
    lv_img_set_src(ui_freestyleRpmGauge, &ui_img_rpm_gauge_png);
    lv_obj_set_width(ui_freestyleRpmGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleRpmGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleRpmGauge, 0);
    lv_obj_set_y(ui_freestyleRpmGauge, -90);
    lv_obj_set_align(ui_freestyleRpmGauge, LV_ALIGN_CENTER);

    ui_freestyleRpmGaugeNeedle = lv_img_create(ui_freestyleRpmGauge);
    lv_img_set_src(ui_freestyleRpmGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_freestyleRpmGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleRpmGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleRpmGaugeNeedle, 0);
    lv_obj_set_y(ui_freestyleRpmGaugeNeedle, 78);
    lv_obj_set_align(ui_freestyleRpmGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_freestyleRpmGaugeNeedle, 10, -36);

    ui_freestyleRpmGaugeArc = lv_arc_create(ui_freestyleScreen);
    lv_obj_set_width(ui_freestyleRpmGaugeArc, 250);
    lv_obj_set_height(ui_freestyleRpmGaugeArc, 250);
    lv_obj_set_x(ui_freestyleRpmGaugeArc, 0);
    lv_obj_set_y(ui_freestyleRpmGaugeArc, -90);
    lv_obj_set_align(ui_freestyleRpmGaugeArc, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_freestyleRpmGaugeArc, LV_OBJ_FLAG_CLICKABLE);
    lv_arc_set_value(ui_freestyleRpmGaugeArc, 0);
    lv_arc_set_bg_angles(ui_freestyleRpmGaugeArc, 0, 360);
    lv_obj_set_style_opa(ui_freestyleRpmGaugeArc, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_freestyleRpmGaugeArc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_freestyleRpmGaugeArc, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_freestyleRpmGaugeArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // --- BUTTONS ---
    ui_freestyleHomeButton = lv_img_create(ui_freestyleScreen);
    lv_img_set_src(ui_freestyleHomeButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_freestyleHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleHomeButton, 320);
    lv_obj_set_y(ui_freestyleHomeButton, 195);
    lv_obj_set_align(ui_freestyleHomeButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_freestyleHomeButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_freestyleHomeButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_freestyleHomeButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_freestyleHomeButtonLabel = lv_label_create(ui_freestyleHomeButton);
    lv_obj_set_align(ui_freestyleHomeButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_freestyleHomeButtonLabel, "Home");
    lv_obj_set_style_text_font(ui_freestyleHomeButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_freestyleChartButton = lv_img_create(ui_freestyleScreen);
    lv_img_set_src(ui_freestyleChartButton, &ui_img_gray_button_long_png);
    lv_obj_set_width(ui_freestyleChartButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleChartButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleChartButton, 170);
    lv_obj_set_y(ui_freestyleChartButton, 195);
    lv_obj_set_align(ui_freestyleChartButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_freestyleChartButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_freestyleChartButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_freestyleChartButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_freestyleChartButtonLabel = lv_label_create(ui_freestyleChartButton);
    lv_obj_set_align(ui_freestyleChartButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_freestyleChartButtonLabel, "Chart");
    lv_obj_set_style_text_font(ui_freestyleChartButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- TEXT LABELS & FIELDS ---
    ui_freestyleTorquelabel = lv_label_create(ui_freestyleScreen);
    lv_obj_set_x(ui_freestyleTorquelabel, -125);
    lv_obj_set_y(ui_freestyleTorquelabel, 125);
    lv_obj_set_align(ui_freestyleTorquelabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_freestyleTorquelabel, "Max ft/lbs Torque:               @              RPM");
    lv_obj_set_style_text_font(ui_freestyleTorquelabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_freestyleTorquelabel, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_freestyleTorquelabel, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_freestyleHorsepowerLabel = lv_label_create(ui_freestyleScreen);
    lv_obj_set_x(ui_freestyleHorsepowerLabel, -126);
    lv_obj_set_y(ui_freestyleHorsepowerLabel, 200);
    lv_obj_set_align(ui_freestyleHorsepowerLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_freestyleHorsepowerLabel, "Max Horsepower:               @              RPM");
    lv_obj_set_style_text_font(ui_freestyleHorsepowerLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_freestyleHorsepowerLabel, lv_color_hex(0x1E00FE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_freestyleHorsepowerLabel, 70, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_freestyleTorqueField = lv_textarea_create(ui_freestyleScreen);
    lv_obj_set_width(ui_freestyleTorqueField, 92);
    lv_obj_set_height(ui_freestyleTorqueField, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleTorqueField, -100);
    lv_obj_set_y(ui_freestyleTorqueField, 125);
    lv_obj_set_align(ui_freestyleTorqueField, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_freestyleTorqueField, "39.99");
    lv_textarea_set_one_line(ui_freestyleTorqueField, true);
    lv_obj_clear_flag(ui_freestyleTorqueField, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_text_color(ui_freestyleTorqueField, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_freestyleTorqueField, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_freestyleTorqueField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_freestyleTorqueField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_freestyleHorsepowerField = lv_textarea_create(ui_freestyleScreen);
    lv_obj_set_width(ui_freestyleHorsepowerField, 119);
    lv_obj_set_height(ui_freestyleHorsepowerField, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleHorsepowerField, -89);
    lv_obj_set_y(ui_freestyleHorsepowerField, 200);
    lv_obj_set_align(ui_freestyleHorsepowerField, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_freestyleHorsepowerField, "39.99");
    lv_textarea_set_one_line(ui_freestyleHorsepowerField, true);
    lv_obj_set_style_text_font(ui_freestyleHorsepowerField, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_freestyleHorsepowerField, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_freestyleHorsepowerField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_freestyleHorsepowerField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_freestyleTorqueRpmField = lv_textarea_create(ui_freestyleScreen);
    lv_obj_set_width(ui_freestyleTorqueRpmField, 90);
    lv_obj_set_height(ui_freestyleTorqueRpmField, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleTorqueRpmField, 2);
    lv_obj_set_y(ui_freestyleTorqueRpmField, 125);
    lv_obj_set_align(ui_freestyleTorqueRpmField, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_freestyleTorqueRpmField, "9999");
    lv_textarea_set_one_line(ui_freestyleTorqueRpmField, true);
    lv_obj_set_style_text_font(ui_freestyleTorqueRpmField, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_freestyleTorqueRpmField, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_freestyleTorqueRpmField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_freestyleTorqueRpmField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_freestyleHorsepowerRpmField = lv_textarea_create(ui_freestyleScreen);
    lv_obj_set_width(ui_freestyleHorsepowerRpmField, 89);
    lv_obj_set_height(ui_freestyleHorsepowerRpmField, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleHorsepowerRpmField, -2);
    lv_obj_set_y(ui_freestyleHorsepowerRpmField, 200);
    lv_obj_set_align(ui_freestyleHorsepowerRpmField, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_freestyleHorsepowerRpmField, "9999");
    lv_textarea_set_one_line(ui_freestyleHorsepowerRpmField, true);
    lv_obj_set_style_text_font(ui_freestyleHorsepowerRpmField, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_freestyleHorsepowerRpmField, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_freestyleHorsepowerRpmField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_freestyleHorsepowerRpmField, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // --- SMALL GAUGES (RESTORED) ---
    ui_freestyleSmallHorsepowerGauge = lv_img_create(ui_freestyleScreen);
    lv_img_set_src(ui_freestyleSmallHorsepowerGauge, &ui_img_hp_gauge_pussy_png);
    lv_obj_set_width(ui_freestyleSmallHorsepowerGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleSmallHorsepowerGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleSmallHorsepowerGauge, 270);
    lv_obj_set_y(ui_freestyleSmallHorsepowerGauge, -90);
    lv_obj_set_align(ui_freestyleSmallHorsepowerGauge, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_freestyleSmallHorsepowerGauge, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_zoom(ui_freestyleSmallHorsepowerGauge, 250);

    ui_freestyleSmallHorsepowerGaugeNeedle = lv_img_create(ui_freestyleSmallHorsepowerGauge);
    lv_img_set_src(ui_freestyleSmallHorsepowerGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_freestyleSmallHorsepowerGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleSmallHorsepowerGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleSmallHorsepowerGaugeNeedle, 0);
    lv_obj_set_y(ui_freestyleSmallHorsepowerGaugeNeedle, 78);
    lv_obj_set_align(ui_freestyleSmallHorsepowerGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_freestyleSmallHorsepowerGaugeNeedle, 10, -36);

    ui_freestyleSmallTorqueGauge = lv_img_create(ui_freestyleScreen);
    lv_img_set_src(ui_freestyleSmallTorqueGauge, &ui_img_hp_gauge_pussy_png);
    lv_obj_set_width(ui_freestyleSmallTorqueGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleSmallTorqueGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleSmallTorqueGauge, -270);
    lv_obj_set_y(ui_freestyleSmallTorqueGauge, -90);
    lv_obj_set_align(ui_freestyleSmallTorqueGauge, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_freestyleSmallTorqueGauge, LV_OBJ_FLAG_HIDDEN);
    lv_img_set_zoom(ui_freestyleSmallTorqueGauge, 250);

    ui_freestyleSmallTorqueGaugeNeedle = lv_img_create(ui_freestyleSmallTorqueGauge);
    lv_img_set_src(ui_freestyleSmallTorqueGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_freestyleSmallTorqueGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleSmallTorqueGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleSmallTorqueGaugeNeedle, 0);
    lv_obj_set_y(ui_freestyleSmallTorqueGaugeNeedle, 78);
    lv_obj_set_align(ui_freestyleSmallTorqueGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_freestyleSmallTorqueGaugeNeedle, 10, -36);

    // --- RANGE SWITCH ---
    ui_rangeSelectSwitch = lv_switch_create(ui_freestyleScreen);
    lv_obj_set_width(ui_rangeSelectSwitch, 139);
    lv_obj_set_height(ui_rangeSelectSwitch, 50);
    lv_obj_set_x(ui_rangeSelectSwitch, 244);
    lv_obj_set_y(ui_rangeSelectSwitch, 80);
    lv_obj_set_align(ui_rangeSelectSwitch, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_rangeSelectSwitch, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rangeSelectSwitch, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rangeSelectSwitch, lv_color_hex(0x282828), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rangeSelectSwitch, 190, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_rangeSelectLabel = lv_label_create(ui_freestyleScreen);
    lv_obj_set_width(ui_rangeSelectLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_rangeSelectLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_rangeSelectLabel, 245);
    lv_obj_set_y(ui_rangeSelectLabel, 130);
    lv_obj_set_align(ui_rangeSelectLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_rangeSelectLabel, "Select Gauge Range");
    lv_obj_set_style_text_font(ui_rangeSelectLabel, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_highLabel = lv_label_create(ui_freestyleScreen);
    lv_obj_set_width(ui_highLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_highLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_highLabel, 139);
    lv_obj_set_y(ui_highLabel, 80);
    lv_obj_set_align(ui_highLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_highLabel, "High");
    lv_obj_set_style_text_font(ui_highLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lowLabel = lv_label_create(ui_freestyleScreen);
    lv_obj_set_width(ui_lowLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_lowLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_lowLabel, 345);
    lv_obj_set_y(ui_lowLabel, 80);
    lv_obj_set_align(ui_lowLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lowLabel, "Low");
    lv_obj_set_style_text_font(ui_lowLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_gaugeLabel = lv_label_create(ui_freestyleScreen);
    lv_obj_set_width(ui_gaugeLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_gaugeLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_gaugeLabel, 60);
    lv_obj_set_y(ui_gaugeLabel, -30);
    lv_obj_set_align(ui_gaugeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_gaugeLabel, "ft/lbs                                                         RPM                                                              HP");
    lv_obj_set_style_text_font(ui_gaugeLabel, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelEGT = lv_label_create(ui_freestyleScreen);
    lv_obj_set_width(ui_LabelEGT, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelEGT, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelEGT, -135);
    lv_obj_set_y(ui_LabelEGT, 20); 
    lv_obj_set_align(ui_LabelEGT, LV_ALIGN_CENTER);
    lv_obj_set_style_text_align(ui_LabelEGT, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(ui_LabelEGT, "EGT\n000 F");
    lv_obj_set_style_text_color(ui_LabelEGT, lv_color_hex(0xFFD700), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelEGT, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelEGT, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    // HIDE BY DEFAULT - Unhidden in main.cpp if sensor found
    lv_obj_add_flag(ui_LabelEGT, LV_OBJ_FLAG_HIDDEN);

    ui_LabelAFR = lv_label_create(ui_freestyleScreen);
    lv_obj_set_width(ui_LabelAFR, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelAFR, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelAFR, 135);
    lv_obj_set_y(ui_LabelAFR, 20); 
    lv_obj_set_align(ui_LabelAFR, LV_ALIGN_CENTER);
    lv_obj_set_style_text_align(ui_LabelAFR, LV_TEXT_ALIGN_CENTER, 0);
    lv_label_set_text(ui_LabelAFR, "AFR\n000 ");
    lv_obj_set_style_text_color(ui_LabelAFR, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAFR, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAFR, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);
    // HIDE BY DEFAULT - Unhidden in main.cpp if sensor found
    //lv_obj_add_flag(ui_LabelAFR, LV_OBJ_FLAG_HIDDEN);

    lv_obj_add_flag(ui_freestyleRpmGauge, LV_OBJ_FLAG_CLICKABLE); // Enable touch
    lv_obj_add_event_cb(ui_freestyleRpmGauge, toggleRpmScale, LV_EVENT_CLICKED, NULL); // Attach function
    lv_obj_add_event_cb(ui_freestyleHomeButton, ui_event_freestyleHomeButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_freestyleChartButton, ui_event_freestyleChartButton, LV_EVENT_ALL, NULL);
    // Directly call the gaugeSelect function in main.cpp
    lv_obj_add_event_cb(ui_rangeSelectSwitch, gaugeSelect, LV_EVENT_ALL, NULL);
}