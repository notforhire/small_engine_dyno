#include "ui.h"

void ui_settingsScreen_screen_init(void)
{
    ui_settingsScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_img_src(ui_settingsScreen, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsInstructions = lv_textarea_create(ui_settingsScreen);
    lv_obj_set_width(ui_settingsInstructions, 400);
    lv_obj_set_height(ui_settingsInstructions, 250);
    lv_obj_set_x(ui_settingsInstructions, 130);
    lv_obj_set_y(ui_settingsInstructions, -60);
    lv_obj_set_align(ui_settingsInstructions, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_settingsInstructions,
    "Welcome to the Pit Row Dyno!! Let's get tuning!! If you are spinning the shaft at any ratio other than 1:1 enter that here, along with a number of magnets for RPM other than 1. Set the Global Max RPM to just slightly higher than your engine's max, and press the calibrate button to calibrate the machine.");    
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


    ui_settingsHomeButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_settingsHomeButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_settingsHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_settingsHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_settingsHomeButton, 320);
    lv_obj_set_y(ui_settingsHomeButton, 195);
    lv_obj_set_align(ui_settingsHomeButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_settingsHomeButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_settingsHomeButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsHomeButtonLabel = lv_label_create(ui_settingsHomeButton);
    lv_obj_set_align(ui_settingsHomeButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_settingsHomeButtonLabel, "Home");
    lv_obj_set_style_text_font(ui_settingsHomeButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsChartButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_settingsChartButton, &ui_img_gray_button_long_png);
    lv_obj_set_width(ui_settingsChartButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_settingsChartButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_settingsChartButton, -320);
    lv_obj_set_y(ui_settingsChartButton, 195);
    lv_obj_set_align(ui_settingsChartButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_settingsChartButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_settingsChartButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_settingsChartButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsChartButtonLabel = lv_label_create(ui_settingsChartButton);
    lv_obj_set_align(ui_settingsChartButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_settingsChartButtonLabel, "Chart");
    lv_obj_set_style_text_font(ui_settingsChartButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_continueButton = lv_img_create(ui_settingsScreen);
    lv_img_set_src(ui_continueButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_continueButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_continueButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_continueButton, 0);
    lv_obj_set_y(ui_continueButton, 195);
    lv_obj_set_align(ui_continueButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_continueButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_continueButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_continueButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_continueButtonLabel = lv_label_create(ui_continueButton);
    lv_obj_set_align(ui_continueButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_continueButtonLabel, "Calibrate");
    lv_obj_set_style_text_font(ui_continueButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_maxRpmTitle = lv_label_create(ui_settingsScreen);
    lv_obj_set_align(ui_maxRpmTitle, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_maxRpmTitle, -220); // Left Side
    lv_obj_set_y(ui_maxRpmTitle, -210); // Top
    lv_label_set_text(ui_maxRpmTitle, "Global Max RPM");
    lv_obj_set_style_text_font(ui_maxRpmTitle, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_maxRpmLabel = lv_label_create(ui_settingsScreen);
    lv_obj_set_align(ui_maxRpmLabel, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_maxRpmLabel, -220); // Left Side
    lv_obj_set_y(ui_maxRpmLabel, -180); // Below Title
    lv_label_set_text(ui_maxRpmLabel, "7500 RPM"); 
    lv_obj_set_style_text_font(ui_maxRpmLabel, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_maxRpmLabel, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_maxRpmSlider = lv_slider_create(ui_settingsScreen);
    lv_slider_set_range(ui_maxRpmSlider, 2000, 20000);
    lv_slider_set_value(ui_maxRpmSlider, 7500, LV_ANIM_OFF);
    lv_obj_set_width(ui_maxRpmSlider, 250); // Small size
    lv_obj_set_height(ui_maxRpmSlider, 20);
    lv_obj_set_x(ui_maxRpmSlider, -220); // Left Side
    lv_obj_set_y(ui_maxRpmSlider, -145); // Below Label
    lv_obj_set_align(ui_maxRpmSlider, LV_ALIGN_CENTER);
    
    // Slider Style
    lv_obj_set_style_bg_color(ui_maxRpmSlider, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_maxRpmSlider, lv_color_hex(0xFF0000), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_maxRpmSlider, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui_maxRpmSlider, 5, LV_PART_KNOB | LV_STATE_DEFAULT); 

    ui_finalDriveLabel = lv_label_create(ui_settingsScreen);
    lv_obj_set_align(ui_finalDriveLabel, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_finalDriveLabel, -220); // Left Side
    lv_obj_set_y(ui_finalDriveLabel, -90);  // Below Slider
    lv_label_set_text(ui_finalDriveLabel, "Final Drive Ratio");
    lv_obj_set_style_text_font(ui_finalDriveLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_finalDriveTextArea = lv_textarea_create(ui_settingsScreen);
    lv_obj_set_width(ui_finalDriveTextArea, 120);
    lv_obj_set_height(ui_finalDriveTextArea, 50);
    lv_obj_set_x(ui_finalDriveTextArea, -220); // Left Side
    lv_obj_set_y(ui_finalDriveTextArea, -30);  // Below Label
    lv_obj_set_align(ui_finalDriveTextArea, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_finalDriveTextArea, "1.00");
    lv_textarea_set_placeholder_text(ui_finalDriveTextArea, "1.00");
    lv_textarea_set_one_line(ui_finalDriveTextArea, true);
    lv_obj_set_style_text_font(ui_finalDriveTextArea, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Style
    lv_obj_set_style_bg_color(ui_finalDriveTextArea, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_finalDriveTextArea, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_finalDriveTextArea, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_finalDriveTextArea, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_finalDriveTextArea, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_finalDriveTextArea, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_finalDriveTextArea, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_finalDriveTextArea, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_finalDriveTextArea, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_finalDriveTextArea, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_finalDriveTextArea, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_finalDriveTextArea, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_finalDriveTextArea, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_finalDriveTextArea, final_drive_update, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(ui_finalDriveTextArea, final_drive_update, LV_EVENT_READY, NULL);

    ui_magnetCountLabel = lv_label_create(ui_settingsScreen);
    lv_obj_set_align(ui_magnetCountLabel, LV_ALIGN_CENTER);
    lv_obj_set_x(ui_magnetCountLabel, -220); // Left Side
    lv_obj_set_y(ui_magnetCountLabel, 30);   // Below FD Box
    lv_label_set_text(ui_magnetCountLabel, "Magnet Count");
    lv_obj_set_style_text_font(ui_magnetCountLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_magnetCountTextArea = lv_textarea_create(ui_settingsScreen);
    lv_obj_set_width(ui_magnetCountTextArea, 120);
    lv_obj_set_height(ui_magnetCountTextArea, 50);
    lv_obj_set_x(ui_magnetCountTextArea, -220); // Left Side
    lv_obj_set_y(ui_magnetCountTextArea, 90);   // Below Label
    lv_obj_set_align(ui_magnetCountTextArea, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_magnetCountTextArea, "1");
    lv_textarea_set_placeholder_text(ui_magnetCountTextArea, "1");
    lv_textarea_set_one_line(ui_magnetCountTextArea, true);
    lv_obj_set_style_text_font(ui_magnetCountTextArea, &ui_font_tomorrow28, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Style
    lv_obj_set_style_bg_color(ui_magnetCountTextArea, lv_color_hex(0x282828), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_magnetCountTextArea, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_magnetCountTextArea, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_magnetCountTextArea, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_magnetCountTextArea, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_magnetCountTextArea, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_magnetCountTextArea, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_magnetCountTextArea, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_magnetCountTextArea, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_magnetCountTextArea, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_magnetCountTextArea, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_magnetCountTextArea, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_magnetCountTextArea, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_magnetCountTextArea, magnet_count_update, LV_EVENT_FOCUSED, NULL);
    lv_obj_add_event_cb(ui_magnetCountTextArea, magnet_count_update, LV_EVENT_READY, NULL);

    // --- KEYBOARD ---
    ui_settingsKeyboard = lv_keyboard_create(ui_settingsScreen);
    lv_keyboard_set_mode(ui_settingsKeyboard, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_set_width(ui_settingsKeyboard, 240); // Portrait Width
    lv_obj_set_height(ui_settingsKeyboard, 320); 
    lv_obj_set_align(ui_settingsKeyboard, LV_ALIGN_RIGHT_MID); // RIGHT side
    lv_obj_set_x(ui_settingsKeyboard, -20); // Padding
    lv_obj_add_flag(ui_settingsKeyboard, LV_OBJ_FLAG_HIDDEN);
    
    // Keyboard Styling
    lv_obj_set_style_bg_color(ui_settingsKeyboard, lv_color_hex(0x181818), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsKeyboard, 240, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_settingsKeyboard, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_settingsKeyboard, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_settingsKeyboard, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_settingsKeyboard, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_settingsKeyboard, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Key Styling
    lv_obj_set_style_bg_color(ui_settingsKeyboard, lv_color_hex(0x000000), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_settingsKeyboard, 255, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_settingsKeyboard, lv_color_hex(0x333333), LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_settingsKeyboard, 1, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_settingsKeyboard, 5, LV_PART_ITEMS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_settingsKeyboard, lv_color_hex(0xFFFFFF), LV_PART_ITEMS | LV_STATE_DEFAULT);
    
    lv_obj_set_style_bg_color(ui_settingsKeyboard, lv_color_hex(0xFF0000), LV_PART_ITEMS | LV_STATE_PRESSED);

    lv_obj_add_event_cb(ui_settingsKeyboard, ui_event_keyboard, LV_EVENT_ALL, NULL);

    // --- EVENTS ---
    lv_obj_add_event_cb(ui_settingsHomeButton, ui_event_settingsHomeButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_settingsChartButton, ui_event_settingsChartButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_continueButton, ui_event_continueButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_maxRpmSlider, slider_set_max_rpm, LV_EVENT_VALUE_CHANGED, NULL); 
}