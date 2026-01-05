#include "ui.h"

void ui_dynoRunScreen_screen_init(void)
{
    ui_dynoRunScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_img_src(ui_dynoRunScreen, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- START BUTTON ---
    ui_dynoStartButton = lv_img_create(ui_dynoRunScreen);
    lv_img_set_src(ui_dynoStartButton, &ui_img_red_button_long_png);
    lv_obj_set_width(ui_dynoStartButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoStartButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoStartButton, -320);
    lv_obj_set_y(ui_dynoStartButton, 195);
    lv_obj_set_align(ui_dynoStartButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_dynoStartButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_dynoStartButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_dynoStartButton, 190, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoStartButtonLabel = lv_label_create(ui_dynoStartButton);
    lv_obj_set_align(ui_dynoStartButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoStartButtonLabel, "Start!!");
    lv_obj_set_style_text_font(ui_dynoStartButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- HOME BUTTON ---
    ui_dynoStartHomeButton = lv_img_create(ui_dynoRunScreen);
    lv_img_set_src(ui_dynoStartHomeButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_dynoStartHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoStartHomeButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoStartHomeButton, 320);
    lv_obj_set_y(ui_dynoStartHomeButton, 195);
    lv_obj_set_align(ui_dynoStartHomeButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_dynoStartHomeButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_dynoStartHomeButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_dynoStartHomeButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoStartHomeButtonLabel = lv_label_create(ui_dynoStartHomeButton);
    lv_obj_set_align(ui_dynoStartHomeButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoStartHomeButtonLabel, "Home");
    lv_obj_set_style_text_font(ui_dynoStartHomeButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- DIRECTIONS TEXT AREA ---
    ui_dynoRunDirections = lv_textarea_create(ui_dynoRunScreen);
    lv_obj_set_width(ui_dynoRunDirections, 622);
    lv_obj_set_height(ui_dynoRunDirections, 225);
    lv_obj_set_x(ui_dynoRunDirections, 0);
    lv_obj_set_y(ui_dynoRunDirections, -80);
    lv_obj_set_align(ui_dynoRunDirections, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_dynoRunDirections,
    "Here you will make a 10 second dyno run that will in turn produce a graph of your engine's horsepower and torque over its RPM range. In order to begin the run press the \"Start!!\" button. As soon as you press the start button smoothly but quickly throttle the engine up to max RPM. Once at max RPM for your engine begin to apply the brake. Apply the brake smoothly and slowly, aiming to bring the engine's RPM down linearly over the 10 seconds from full RPM to just around 1000 RPM. It is going to take you several attempts to get the feel for it. You WILL fail, get over it.");
    
    // Styling for text area
    lv_obj_set_style_text_font(ui_dynoRunDirections, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_dynoRunDirections, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_dynoRunDirections, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_dynoRunDirections, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_dynoRunDirections, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_dynoRunDirections, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    
    // Events
    lv_obj_add_event_cb(ui_dynoStartButton, ui_event_dynoStartButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_dynoStartHomeButton, ui_event_dynoStartHomeButton, LV_EVENT_ALL, NULL);
}