#include "ui.h"

void ui_settingsScreen_screen_init(void)
{
    ui_settingsScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_img_src(ui_settingsScreen, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_continueButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_continueButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_continueButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_continueButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_continueButton, 150);
    lv_obj_set_y(ui_continueButton, 195);
    lv_obj_set_align(ui_continueButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_continueButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_continueButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_continueButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_continueButtonLabel = lv_label_create(ui_continueButton);
    lv_obj_set_width(ui_continueButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_continueButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_continueButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_continueButtonLabel, "Calibrate");
    lv_obj_set_style_text_font(ui_continueButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rpmRangeSwitch = lv_switch_create(ui_settingsScreen);
    lv_obj_set_width(ui_rpmRangeSwitch, 139);
    lv_obj_set_height(ui_rpmRangeSwitch, 50);
    lv_obj_set_x(ui_rpmRangeSwitch, -250);
    lv_obj_set_y(ui_rpmRangeSwitch, 195);
    lv_obj_set_align(ui_rpmRangeSwitch, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(ui_rpmRangeSwitch, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rpmRangeSwitch, 190, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rpmRangeSwitch, lv_color_hex(0x282828), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rpmRangeSwitch, 190, LV_PART_INDICATOR | LV_STATE_DEFAULT);

    //0-10 ft/lb buttons (first)
    ui_firstGreenButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_firstGreenButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_firstGreenButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_firstGreenButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_firstGreenButton, -320);
    lv_obj_set_y(ui_firstGreenButton, -195);
    lv_obj_set_align(ui_firstGreenButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_firstGreenButton, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_blend_mode(ui_firstGreenButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_firstGreenButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_firstGreenButtonLabel = lv_label_create(ui_firstGreenButton);
    lv_obj_set_width(ui_firstGreenButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_firstGreenButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_firstGreenButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_firstGreenButtonLabel, "0-10");
    lv_obj_set_style_text_font(ui_firstGreenButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_firstWhiteButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_firstWhiteButton, &ui_img_gray_button_long_png);
    lv_obj_set_width(ui_firstWhiteButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_firstWhiteButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_firstWhiteButton, -320);
    lv_obj_set_y(ui_firstWhiteButton, -195);
    lv_obj_set_align(ui_firstWhiteButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_firstWhiteButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_firstWhiteButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_firstWhiteButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_firstWhiteButtonLabel = lv_label_create(ui_firstWhiteButton);
    lv_obj_set_width(ui_firstWhiteButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_firstWhiteButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_firstWhiteButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_firstWhiteButtonLabel, "0-10");
    lv_obj_set_style_text_font(ui_firstWhiteButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

        //0-20 ft/lb buttons (second)
    ui_secondGreenButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_secondGreenButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_secondGreenButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_secondGreenButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_secondGreenButton, -320);
    lv_obj_set_y(ui_secondGreenButton, -100);
    lv_obj_set_align(ui_secondGreenButton, LV_ALIGN_CENTER);
    lv_obj_set_style_blend_mode(ui_secondGreenButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_secondGreenButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_secondGreenButtonLabel = lv_label_create(ui_secondGreenButton);
    lv_obj_set_width(ui_secondGreenButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_secondGreenButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_secondGreenButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_secondGreenButtonLabel, "0-20");
    lv_obj_set_style_text_font(ui_secondGreenButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_secondWhiteButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_secondWhiteButton, &ui_img_gray_button_long_png);
    lv_obj_set_width(ui_secondWhiteButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_secondWhiteButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_secondWhiteButton, -320);
    lv_obj_set_y(ui_secondWhiteButton, -100);
    lv_obj_set_align(ui_secondWhiteButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_secondWhiteButton, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_blend_mode(ui_secondWhiteButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_secondWhiteButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_secondWhiteButtonLabel = lv_label_create(ui_secondWhiteButton);
    lv_obj_set_width(ui_secondWhiteButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_secondWhiteButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_secondWhiteButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_secondWhiteButtonLabel, "0-20");
    lv_obj_set_style_text_font(ui_secondWhiteButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    //0-30 ft/lb buttons (third)
    ui_thirdGreenButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_thirdGreenButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_thirdGreenButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_thirdGreenButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_thirdGreenButton, -320);
    lv_obj_set_y(ui_thirdGreenButton, -5);
    lv_obj_set_align(ui_thirdGreenButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_thirdGreenButton, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_blend_mode(ui_thirdGreenButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_thirdGreenButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_thirdGreenButtonLabel = lv_label_create(ui_thirdGreenButton);
    lv_obj_set_width(ui_thirdGreenButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_thirdGreenButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_thirdGreenButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_thirdGreenButtonLabel, "0-30");
    lv_obj_set_style_text_font(ui_thirdGreenButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_thirdWhiteButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_thirdWhiteButton, &ui_img_gray_button_long_png);
    lv_obj_set_width(ui_thirdWhiteButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_thirdWhiteButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_thirdWhiteButton, -320);
    lv_obj_set_y(ui_thirdWhiteButton, -5);
    lv_obj_set_align(ui_thirdWhiteButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_thirdWhiteButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_thirdWhiteButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_thirdWhiteButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_thirdWhiteButtonLabel = lv_label_create(ui_thirdWhiteButton);
    lv_obj_set_width(ui_thirdWhiteButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_thirdWhiteButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_thirdWhiteButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_thirdWhiteButtonLabel, "0-30");
    lv_obj_set_style_text_font(ui_thirdWhiteButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    //0-40 ft/lb buttons (fourth)
    ui_fourthGreenButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_fourthGreenButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_fourthGreenButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_fourthGreenButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_fourthGreenButton, -320);
    lv_obj_set_y(ui_fourthGreenButton, 90);
    lv_obj_set_align(ui_fourthGreenButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_fourthGreenButton, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_style_blend_mode(ui_fourthGreenButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_fourthGreenButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_fourthGreenButtonLabel = lv_label_create(ui_fourthGreenButton);
    lv_obj_set_width(ui_fourthGreenButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_fourthGreenButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_fourthGreenButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_fourthGreenButtonLabel, "0-40");
    lv_obj_set_style_text_font(ui_fourthGreenButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_fourthWhiteButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_fourthWhiteButton, &ui_img_gray_button_long_png);
    lv_obj_set_width(ui_fourthWhiteButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_fourthWhiteButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_fourthWhiteButton, -320);
    lv_obj_set_y(ui_fourthWhiteButton, 90);
    lv_obj_set_align(ui_fourthWhiteButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_fourthWhiteButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_fourthWhiteButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_fourthWhiteButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_fourthWhiteButtonLabel = lv_label_create(ui_fourthWhiteButton);
    lv_obj_set_width(ui_fourthWhiteButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_fourthWhiteButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_fourthWhiteButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_fourthWhiteButtonLabel, "0-40");
    lv_obj_set_style_text_font(ui_fourthWhiteButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsInstructions = lv_textarea_create(ui_settingsScreen);
    lv_obj_set_width(ui_settingsInstructions, 600);
    lv_obj_set_height(ui_settingsInstructions, 380);
    lv_obj_set_x(ui_settingsInstructions, 85);
    lv_obj_set_y(ui_settingsInstructions, -45);
    lv_obj_set_align(ui_settingsInstructions, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_settingsInstructions,
    "None of the settings options on this screen alter the actual function of the machine in any way. They are provided only to scale the graph, making it more readable and helpful. On the left side of the screen are four options for the expected torque and horsepower of the engine being tested. If you choose a range lower than your engine's output you will likely get points outside of the visible area of the graph. Choosing an excessively high power range will produce a graph that looks more flat than reality. The switch on this page will scale the RPM portion of the graph. The low setting is for engines operating at up to 5,000 RPM, and the high setting goes up to 10,000 RPM. If you find, after graphing, that you chose poorly you can select another power range, and return to the graph. If you have to change the RPM range it will not chart the current data to the rescaled graph, you will have to run it again. You may have to go through some trial and error to find the settings most preferable to you.");    
    lv_obj_set_style_text_font(ui_settingsInstructions, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_settingsInstructions, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_settingsInstructions, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_settingsInstructions, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_settingsInstructions, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_settingsInstructions, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_settingsInstructions, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_settingsInstructions, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_settingsInstructions, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_settingsInstructions, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_settingsInstructions, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rpmHighLabel = lv_label_create(ui_settingsScreen);
    lv_obj_set_width(ui_rpmHighLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_rpmHighLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_rpmHighLabel, -150);
    lv_obj_set_y(ui_rpmHighLabel, 195);
    lv_obj_set_align(ui_rpmHighLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_rpmHighLabel, "High");
    lv_obj_set_style_text_font(ui_rpmHighLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rpmLowLabel = lv_label_create(ui_settingsScreen);
    lv_obj_set_width(ui_rpmLowLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_rpmLowLabel, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_rpmLowLabel, -350);
    lv_obj_set_y(ui_rpmLowLabel, 195);
    lv_obj_set_align(ui_rpmLowLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_rpmLowLabel, "Low");
    lv_obj_set_style_text_font(ui_rpmLowLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsHomeButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_settingsHomeButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_settingsHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_settingsHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_settingsHomeButton, 320);
    lv_obj_set_y(ui_settingsHomeButton, 195);
    lv_obj_set_align(ui_settingsHomeButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_settingsHomeButton, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_settingsHomeButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_settingsHomeButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsHomeButtonLabel = lv_label_create(ui_settingsHomeButton);
    lv_obj_set_width(ui_settingsHomeButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_settingsHomeButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_settingsHomeButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_settingsHomeButtonLabel, "Home");
    lv_obj_set_style_text_font(ui_settingsHomeButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsChartButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_settingsChartButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_settingsChartButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_settingsChartButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_settingsChartButton, -20);
    lv_obj_set_y(ui_settingsChartButton, 195);
    lv_obj_set_align(ui_settingsChartButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_settingsChartButton, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_settingsChartButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_settingsChartButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsChartButtonLabel = lv_label_create(ui_settingsChartButton);
    lv_obj_set_width(ui_settingsChartButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_settingsChartButtonLabel, LV_SIZE_CONTENT);
    lv_obj_set_align(ui_settingsChartButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_settingsChartButtonLabel, "Chart");
    lv_obj_set_style_text_font(ui_settingsChartButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_continueButton, ui_event_continueButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_rpmRangeSwitch, ui_event_rpmRangeSwitch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_firstWhiteButton, ui_event_firstWhiteButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_secondWhiteButton, ui_event_secondWhiteButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_thirdWhiteButton, ui_event_thirdWhiteButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_fourthWhiteButton, ui_event_fourthWhiteButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_settingsHomeButton, ui_event_settingsHomeButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_settingsChartButton, ui_event_settingsChartButton, LV_EVENT_ALL, NULL);
}