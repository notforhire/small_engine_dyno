#include "ui.h"

void ui_dynoRunGaugeScreen_screen_init(void)
{
    ui_dynoRunGaugeScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_img_src(ui_dynoRunGaugeScreen, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- NAVIGATION BUTTONS ---
    ui_dynoRunGaugeBackButton = lv_img_create(ui_dynoRunGaugeScreen);
    lv_img_set_src(ui_dynoRunGaugeBackButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_dynoRunGaugeBackButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunGaugeBackButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunGaugeBackButton, 320);
    lv_obj_set_y(ui_dynoRunGaugeBackButton, 195);
    lv_obj_set_align(ui_dynoRunGaugeBackButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_dynoRunGaugeBackButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_dynoRunGaugeBackButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_dynoRunGaugeBackButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunGaugeBackButtonLabel = lv_label_create(ui_dynoRunGaugeBackButton);
    lv_obj_set_align(ui_dynoRunGaugeBackButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunGaugeBackButtonLabel, "Back");
    lv_obj_set_style_text_font(ui_dynoRunGaugeBackButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunChartButton = lv_img_create(ui_dynoRunGaugeScreen);
    lv_img_set_src(ui_dynoRunChartButton, &ui_img_gray_button_long_png);
    lv_obj_set_width(ui_dynoRunChartButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunChartButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunChartButton, 170);
    lv_obj_set_y(ui_dynoRunChartButton, 195);
    lv_obj_set_align(ui_dynoRunChartButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_dynoRunChartButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_dynoRunChartButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_dynoRunChartButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunChartButtonLabel = lv_label_create(ui_dynoRunChartButton);
    lv_obj_set_align(ui_dynoRunChartButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunChartButtonLabel, "Chart");
    lv_obj_set_style_text_font(ui_dynoRunChartButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- RPM GAUGE ---
    ui_dynoRunRpmGauge = lv_img_create(ui_dynoRunGaugeScreen);
    lv_img_set_src(ui_dynoRunRpmGauge, &ui_img_rpm_gauge_png);
    lv_obj_set_width(ui_dynoRunRpmGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunRpmGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunRpmGauge, 0);
    lv_obj_set_y(ui_dynoRunRpmGauge, -90);
    lv_obj_set_align(ui_dynoRunRpmGauge, LV_ALIGN_CENTER);

    ui_dynoRunRpmGaugeNeedle = lv_img_create(ui_dynoRunRpmGauge);
    lv_img_set_src(ui_dynoRunRpmGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_dynoRunRpmGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunRpmGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunRpmGaugeNeedle, 0);
    lv_obj_set_y(ui_dynoRunRpmGaugeNeedle, 78);
    lv_obj_set_align(ui_dynoRunRpmGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_dynoRunRpmGaugeNeedle, 10, -36);

    ui_dynoRunRpmGaugeLabel = lv_label_create(ui_dynoRunRpmGauge);
    lv_obj_set_x(ui_dynoRunRpmGaugeLabel, 70);
    lv_obj_set_y(ui_dynoRunRpmGaugeLabel, 50);
    lv_obj_set_align(ui_dynoRunRpmGaugeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunRpmGaugeLabel, "RPM");
    lv_obj_set_style_text_font(ui_dynoRunRpmGaugeLabel, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunRpmGaugeArc = lv_arc_create(ui_dynoRunGaugeScreen);
    lv_obj_set_width(ui_dynoRunRpmGaugeArc, 250);
    lv_obj_set_height(ui_dynoRunRpmGaugeArc, 250);
    lv_obj_set_x(ui_dynoRunRpmGaugeArc, 0);
    lv_obj_set_y(ui_dynoRunRpmGaugeArc, -90);
    lv_obj_set_align(ui_dynoRunRpmGaugeArc, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_dynoRunRpmGaugeArc, 0);
    lv_arc_set_bg_angles(ui_dynoRunRpmGaugeArc, 0, 360);
    lv_obj_set_style_opa(ui_dynoRunRpmGaugeArc, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_dynoRunRpmGaugeArc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_dynoRunRpmGaugeArc, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dynoRunRpmGaugeArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // --- LARGE TORQUE GAUGE ---
    ui_dynoRunTorqueGauge = lv_img_create(ui_dynoRunGaugeScreen);
    lv_img_set_src(ui_dynoRunTorqueGauge, &ui_img_hp_gauge_png);
    lv_obj_set_width(ui_dynoRunTorqueGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunTorqueGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunTorqueGauge, -270);
    lv_obj_set_y(ui_dynoRunTorqueGauge, -90);
    lv_obj_set_align(ui_dynoRunTorqueGauge, LV_ALIGN_CENTER);

    ui_dynoRunTorqueGaugeNeedle = lv_img_create(ui_dynoRunTorqueGauge);
    lv_img_set_src(ui_dynoRunTorqueGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_dynoRunTorqueGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunTorqueGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunTorqueGaugeNeedle, 0);
    lv_obj_set_y(ui_dynoRunTorqueGaugeNeedle, 78);
    lv_obj_set_align(ui_dynoRunTorqueGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_dynoRunTorqueGaugeNeedle, 10, -36);

    ui_dynoRunTorqueGaugeLabel = lv_label_create(ui_dynoRunTorqueGauge);
    lv_obj_set_x(ui_dynoRunTorqueGaugeLabel, 70);
    lv_obj_set_y(ui_dynoRunTorqueGaugeLabel, 50);
    lv_obj_set_align(ui_dynoRunTorqueGaugeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunTorqueGaugeLabel, "ft/lb");
    lv_obj_set_style_text_font(ui_dynoRunTorqueGaugeLabel, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunTorqueGaugeArc = lv_arc_create(ui_dynoRunGaugeScreen);
    lv_obj_set_width(ui_dynoRunTorqueGaugeArc, 250);
    lv_obj_set_height(ui_dynoRunTorqueGaugeArc, 250);
    lv_obj_set_x(ui_dynoRunTorqueGaugeArc, -270);
    lv_obj_set_y(ui_dynoRunTorqueGaugeArc, -90);
    lv_obj_set_align(ui_dynoRunTorqueGaugeArc, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_dynoRunTorqueGaugeArc, 0);
    lv_arc_set_bg_angles(ui_dynoRunTorqueGaugeArc, 0, 360);
    lv_obj_set_style_opa(ui_dynoRunTorqueGaugeArc, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_dynoRunTorqueGaugeArc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_dynoRunTorqueGaugeArc, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dynoRunTorqueGaugeArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // --- LARGE HORSEPOWER GAUGE ---
    ui_dynoRunHorsepowerGauge = lv_img_create(ui_dynoRunGaugeScreen);
    lv_img_set_src(ui_dynoRunHorsepowerGauge, &ui_img_hp_gauge_png);
    lv_obj_set_width(ui_dynoRunHorsepowerGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunHorsepowerGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunHorsepowerGauge, 270);
    lv_obj_set_y(ui_dynoRunHorsepowerGauge, -90);
    lv_obj_set_align(ui_dynoRunHorsepowerGauge, LV_ALIGN_CENTER);

    ui_dynoRunHorsepowerGaugeNeedle = lv_img_create(ui_dynoRunHorsepowerGauge);
    lv_img_set_src(ui_dynoRunHorsepowerGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_dynoRunHorsepowerGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunHorsepowerGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunHorsepowerGaugeNeedle, 0);
    lv_obj_set_y(ui_dynoRunHorsepowerGaugeNeedle, 78);
    lv_obj_set_align(ui_dynoRunHorsepowerGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_dynoRunHorsepowerGaugeNeedle, 10, -36);

    ui_dynoRunHorsepowerGaugeLabel = lv_label_create(ui_dynoRunHorsepowerGauge);
    lv_obj_set_x(ui_dynoRunHorsepowerGaugeLabel, 70);
    lv_obj_set_y(ui_dynoRunHorsepowerGaugeLabel, 50);
    lv_obj_set_align(ui_dynoRunHorsepowerGaugeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunHorsepowerGaugeLabel, "HP");
    lv_obj_set_style_text_font(ui_dynoRunHorsepowerGaugeLabel, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunHorsepowerGaugeArc = lv_arc_create(ui_dynoRunGaugeScreen);
    lv_obj_set_width(ui_dynoRunHorsepowerGaugeArc, 250);
    lv_obj_set_height(ui_dynoRunHorsepowerGaugeArc, 250);
    lv_obj_set_x(ui_dynoRunHorsepowerGaugeArc, 270);
    lv_obj_set_y(ui_dynoRunHorsepowerGaugeArc, -90);
    lv_obj_set_align(ui_dynoRunHorsepowerGaugeArc, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_dynoRunHorsepowerGaugeArc, 0);
    lv_arc_set_bg_angles(ui_dynoRunHorsepowerGaugeArc, 0, 360);
    lv_obj_set_style_opa(ui_dynoRunHorsepowerGaugeArc, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui_dynoRunHorsepowerGaugeArc, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui_dynoRunHorsepowerGaugeArc, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dynoRunHorsepowerGaugeArc, 0, LV_PART_KNOB | LV_STATE_DEFAULT);

    // --- SMALL GAUGES (ADDED) ---
    ui_dynoRunSmallTorqueGauge = lv_img_create(ui_dynoRunGaugeScreen);
    lv_img_set_src(ui_dynoRunSmallTorqueGauge, &ui_img_hp_gauge_pussy_png);
    lv_obj_set_width(ui_dynoRunSmallTorqueGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunSmallTorqueGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunSmallTorqueGauge, -270);
    lv_obj_set_y(ui_dynoRunSmallTorqueGauge, -90);
    lv_obj_set_align(ui_dynoRunSmallTorqueGauge, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_dynoRunSmallTorqueGauge, LV_OBJ_FLAG_HIDDEN); // Initially Hidden
    lv_img_set_zoom(ui_dynoRunSmallTorqueGauge, 250);

    ui_dynoRunSmallTorqueGaugeNeedle = lv_img_create(ui_dynoRunSmallTorqueGauge);
    lv_img_set_src(ui_dynoRunSmallTorqueGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_dynoRunSmallTorqueGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunSmallTorqueGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunSmallTorqueGaugeNeedle, 0);
    lv_obj_set_y(ui_dynoRunSmallTorqueGaugeNeedle, 78);
    lv_obj_set_align(ui_dynoRunSmallTorqueGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_dynoRunSmallTorqueGaugeNeedle, 10, -36);

    ui_dynoRunSmallHorsepowerGauge = lv_img_create(ui_dynoRunGaugeScreen);
    lv_img_set_src(ui_dynoRunSmallHorsepowerGauge, &ui_img_hp_gauge_pussy_png);
    lv_obj_set_width(ui_dynoRunSmallHorsepowerGauge, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunSmallHorsepowerGauge, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunSmallHorsepowerGauge, 270);
    lv_obj_set_y(ui_dynoRunSmallHorsepowerGauge, -90);
    lv_obj_set_align(ui_dynoRunSmallHorsepowerGauge, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_dynoRunSmallHorsepowerGauge, LV_OBJ_FLAG_HIDDEN); // Initially Hidden
    lv_img_set_zoom(ui_dynoRunSmallHorsepowerGauge, 250);

    ui_dynoRunSmallHorsepowerGaugeNeedle = lv_img_create(ui_dynoRunSmallHorsepowerGauge);
    lv_img_set_src(ui_dynoRunSmallHorsepowerGaugeNeedle, &ui_img_needle_png);
    lv_obj_set_width(ui_dynoRunSmallHorsepowerGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunSmallHorsepowerGaugeNeedle, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunSmallHorsepowerGaugeNeedle, 0);
    lv_obj_set_y(ui_dynoRunSmallHorsepowerGaugeNeedle, 78);
    lv_obj_set_align(ui_dynoRunSmallHorsepowerGaugeNeedle, LV_ALIGN_CENTER);
    lv_img_set_pivot(ui_dynoRunSmallHorsepowerGaugeNeedle, 10, -36);

    // --- RANGE SWITCH (ADDED) ---
    ui_dynoRunRangeSwitch = lv_switch_create(ui_dynoRunGaugeScreen);
    lv_obj_set_width(ui_dynoRunRangeSwitch, 139);
    lv_obj_set_height(ui_dynoRunRangeSwitch, 50);
    lv_obj_set_x(ui_dynoRunRangeSwitch, 244);
    lv_obj_set_y(ui_dynoRunRangeSwitch, 80);
    lv_obj_set_align(ui_dynoRunRangeSwitch, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_dynoRunRangeSwitch, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dynoRunRangeSwitch, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_dynoRunRangeSwitch, lv_color_hex(0x282828), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_dynoRunRangeSwitch, 190, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_dynoRunRangeSelectLabel = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_width(ui_dynoRunRangeSelectLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunRangeSelectLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunRangeSelectLabel, 245);
    lv_obj_set_y(ui_dynoRunRangeSelectLabel, 130);
    lv_obj_set_align(ui_dynoRunRangeSelectLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunRangeSelectLabel, "Select Gauge Range");
    lv_obj_set_style_text_font(ui_dynoRunRangeSelectLabel, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunHighLabel = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_width(ui_dynoRunHighLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunHighLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunHighLabel, 139);
    lv_obj_set_y(ui_dynoRunHighLabel, 80);
    lv_obj_set_align(ui_dynoRunHighLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunHighLabel, "High");
    lv_obj_set_style_text_font(ui_dynoRunHighLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunLowLabel = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_width(ui_dynoRunLowLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunLowLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunLowLabel, 345);
    lv_obj_set_y(ui_dynoRunLowLabel, 80);
    lv_obj_set_align(ui_dynoRunLowLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunLowLabel, "Low");
    lv_obj_set_style_text_font(ui_dynoRunLowLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- TIMEOUT BAR & LABELS ---
    ui_timeoutBar = lv_bar_create(ui_dynoRunGaugeScreen);
    lv_bar_set_range(ui_timeoutBar, 0, 1000);
    lv_bar_set_value(ui_timeoutBar, 900, LV_ANIM_OFF);
    lv_obj_set_width(ui_timeoutBar, 709);
    lv_obj_set_height(ui_timeoutBar, 20);
    lv_obj_set_x(ui_timeoutBar, 0);
    lv_obj_set_y(ui_timeoutBar, 63);
    lv_obj_set_align(ui_timeoutBar, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_timeoutBar, lv_color_hex(0x09F638), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_timeoutBar, 70, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_timeoutBar, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_timeoutBar, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_timeoutBar, lv_color_hex(0x09F638), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_timeoutBar, 190, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_timeoutBar, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_timeoutBar, LV_GRAD_DIR_HOR, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    ui_runTorqueLabel = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_runTorqueLabel, -278);
    lv_obj_set_y(ui_runTorqueLabel, 120);
    lv_obj_set_align(ui_runTorqueLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_runTorqueLabel, "ft/lb Torque");
    lv_obj_set_style_text_font(ui_runTorqueLabel, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_runHorsepowerLabel = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_runHorsepowerLabel, -280);
    lv_obj_set_y(ui_runHorsepowerLabel, 175);
    lv_obj_set_align(ui_runHorsepowerLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_runHorsepowerLabel, "Horsepower:");
    lv_obj_set_style_text_font(ui_runHorsepowerLabel, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunMaxTorqueField = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_dynoRunMaxTorqueField, -150);
    lv_obj_set_y(ui_dynoRunMaxTorqueField, 120);
    lv_obj_set_align(ui_dynoRunMaxTorqueField, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunMaxTorqueField, "0.00");
    lv_obj_set_style_text_font(ui_dynoRunMaxTorqueField, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunMaxHorsepowerField = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_dynoRunMaxHorsepowerField, -150);
    lv_obj_set_y(ui_dynoRunMaxHorsepowerField, 175);
    lv_obj_set_align(ui_dynoRunMaxHorsepowerField, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunMaxHorsepowerField, "0.00");
    lv_obj_set_style_text_font(ui_dynoRunMaxHorsepowerField, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_atSymbol1 = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_atSymbol1, -90);
    lv_obj_set_y(ui_atSymbol1, 120);
    lv_obj_set_align(ui_atSymbol1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_atSymbol1, "@");
    lv_obj_set_style_text_font(ui_atSymbol1, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_atSymbol2 = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_atSymbol2, -90);
    lv_obj_set_y(ui_atSymbol2, 175);
    lv_obj_set_align(ui_atSymbol2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_atSymbol2, "@");
    lv_obj_set_style_text_font(ui_atSymbol2, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunTorqueMaxRpmField = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_dynoRunTorqueMaxRpmField, -32);
    lv_obj_set_y(ui_dynoRunTorqueMaxRpmField, 120);
    lv_obj_set_align(ui_dynoRunTorqueMaxRpmField, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunTorqueMaxRpmField, "0");
    lv_obj_set_style_text_font(ui_dynoRunTorqueMaxRpmField, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunHorsepowerMaxRpmField = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_dynoRunHorsepowerMaxRpmField, -32);
    lv_obj_set_y(ui_dynoRunHorsepowerMaxRpmField, 175);
    lv_obj_set_align(ui_dynoRunHorsepowerMaxRpmField, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunHorsepowerMaxRpmField, "0");
    lv_obj_set_style_text_font(ui_dynoRunHorsepowerMaxRpmField, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rpmLabel1 = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_rpmLabel1, 40);
    lv_obj_set_y(ui_rpmLabel1, 120);
    lv_obj_set_align(ui_rpmLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_rpmLabel1, "RPM");
    lv_obj_set_style_text_font(ui_rpmLabel1, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rpmLabel2 = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_rpmLabel2, 40);
    lv_obj_set_y(ui_rpmLabel2, 175);
    lv_obj_set_align(ui_rpmLabel2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_rpmLabel2, "RPM");
    lv_obj_set_style_text_font(ui_rpmLabel2, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- NOTIFICATIONS ---
    ui_runTimeCounter = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_x(ui_runTimeCounter, -15);
    lv_obj_set_y(ui_runTimeCounter, 38);
    lv_obj_set_align(ui_runTimeCounter, LV_ALIGN_CENTER);
    lv_label_set_text(ui_runTimeCounter, "9");
    lv_obj_add_flag(ui_runTimeCounter, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui_runTimeCounter, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_runTimeCounter, &ui_font_tomorrow150, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_throttleNotice = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_align(ui_throttleNotice, LV_ALIGN_CENTER);
    lv_label_set_text(ui_throttleNotice, "Hit the \n  gas!!");
    lv_obj_add_flag(ui_throttleNotice, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui_throttleNotice, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_throttleNotice, &ui_font_tomorrow150, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_brakeNowNotice = lv_label_create(ui_dynoRunGaugeScreen);
    lv_obj_set_align(ui_brakeNowNotice, LV_ALIGN_CENTER);
    lv_label_set_text(ui_brakeNowNotice, "Brake \n now!!");
    lv_obj_add_flag(ui_brakeNowNotice, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_text_color(ui_brakeNowNotice, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_brakeNowNotice, &ui_font_tomorrow150, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_flag(ui_dynoRunRpmGauge, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui_dynoRunRpmGauge, toggleRpmScale, LV_EVENT_CLICKED, NULL);
    lv_obj_add_event_cb(ui_dynoRunGaugeBackButton, ui_event_dynoRunGaugeBackButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_dynoRunChartButton, ui_event_dynoRunChartButton, LV_EVENT_ALL, NULL);
    // Added event for the new switch to control gauges
    lv_obj_add_event_cb(ui_dynoRunRangeSwitch, gaugeSelect, LV_EVENT_ALL, NULL);
}