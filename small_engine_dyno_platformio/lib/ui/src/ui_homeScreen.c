#include "ui.h"

void ui_homeScreen_screen_init(void)
{
    ui_homeScreen = lv_obj_create(NULL);
    lv_obj_set_style_bg_img_src(ui_homeScreen, &ui_img_carbon_fiber3_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- DYNO RUN BUTTON ---
    ui_dynoRunButton = lv_img_create(ui_homeScreen);
    lv_img_set_src(ui_dynoRunButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_dynoRunButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_dynoRunButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_dynoRunButton, -105);
    lv_obj_set_y(ui_dynoRunButton, 195);
    lv_obj_set_align(ui_dynoRunButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_dynoRunButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_dynoRunButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_dynoRunButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dynoRunButtonLabel = lv_label_create(ui_dynoRunButton);
    lv_obj_set_align(ui_dynoRunButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_dynoRunButtonLabel, "Dyno Run");
    lv_obj_set_style_text_font(ui_dynoRunButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- SETTINGS BUTTON ---
    ui_settingsButton = lv_img_create(ui_homeScreen);
    lv_img_set_src(ui_settingsButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_settingsButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_settingsButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_settingsButton, 105);
    lv_obj_set_y(ui_settingsButton, 195);
    lv_obj_set_align(ui_settingsButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_settingsButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_settingsButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_settingsButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_settingsButtonLabel = lv_label_create(ui_settingsButton);
    lv_obj_set_align(ui_settingsButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_settingsButtonLabel, "Settings");
    lv_obj_set_style_text_font(ui_settingsButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- FREESTYLE BUTTON ---
    ui_freestyleButton = lv_img_create(ui_homeScreen);
    lv_img_set_src(ui_freestyleButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_freestyleButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_freestyleButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_freestyleButton, 320);
    lv_obj_set_y(ui_freestyleButton, 195);
    lv_obj_set_align(ui_freestyleButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_freestyleButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_freestyleButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_freestyleButton, 220, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_freestyleButtonLabel = lv_label_create(ui_freestyleButton);
    lv_obj_set_align(ui_freestyleButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_freestyleButtonLabel, "Freestyle");
    lv_obj_set_style_text_font(ui_freestyleButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- CALIBRATE BUTTON ---
    ui_calibrateButton = lv_img_create(ui_homeScreen);
    lv_img_set_src(ui_calibrateButton, &ui_img_green_button_long_png);
    lv_obj_set_width(ui_calibrateButton, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_calibrateButton, LV_SIZE_CONTENT);
    lv_obj_set_x(ui_calibrateButton, -320);
    lv_obj_set_y(ui_calibrateButton, 195);
    lv_obj_set_align(ui_calibrateButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_calibrateButton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_set_style_blend_mode(ui_calibrateButton, LV_BLEND_MODE_ADDITIVE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_calibrateButton, 190, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_calibrateButtonLabel = lv_label_create(ui_calibrateButton);
    lv_obj_set_align(ui_calibrateButtonLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_calibrateButtonLabel, "Calibrate");
    lv_obj_set_style_text_font(ui_calibrateButtonLabel, &ui_font_tomorrow, LV_PART_MAIN | LV_STATE_DEFAULT);

    // --- WARNINGS ---
    ui_calibrationWarning = lv_textarea_create(ui_homeScreen);
    lv_obj_set_width(ui_calibrationWarning, 400);
    lv_obj_set_height(ui_calibrationWarning, 70);
    lv_obj_set_x(ui_calibrationWarning, 0);
    lv_obj_set_y(ui_calibrationWarning, -55);
    lv_obj_set_align(ui_calibrationWarning, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_calibrationWarning,
    "If you are seeing questionable results it might help to calibrate the machine again.");
    lv_obj_set_style_text_font(ui_calibrationWarning, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_calibrationWarning, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_calibrationWarning, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_calibrationWarning, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_calibrationWarning, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_calibrationWarning, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_calibrationWarning, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_calibrationWarning, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_calibrationWarning, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_calibrationWarning, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_opa(ui_calibrationWarning, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_safetyAdvisement = lv_textarea_create(ui_homeScreen);
    lv_obj_set_width(ui_safetyAdvisement, 500);
    lv_obj_set_height(ui_safetyAdvisement, 115);
    lv_obj_set_x(ui_safetyAdvisement, 0);
    lv_obj_set_y(ui_safetyAdvisement, -170);
    lv_obj_set_align(ui_safetyAdvisement, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_safetyAdvisement, 
    "When in operation this thing is potentially dangerous!! We are talking parts moving at high speeds, heat, fire, explosions, demons, and other hazards I haven't even conceived of. Wear appropriate safety gear at all times!!");
    lv_obj_set_style_text_font(ui_safetyAdvisement, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_safetyAdvisement, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_safetyAdvisement, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_safetyAdvisement, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_safetyAdvisement, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_safetyAdvisement, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_safetyAdvisement, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_safetyAdvisement, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_safetyAdvisement, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_safetyAdvisement, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_dumbFriendWarning = lv_textarea_create(ui_homeScreen);
    lv_obj_set_width(ui_dumbFriendWarning, 290);
    lv_obj_set_height(ui_dumbFriendWarning, 90);
    lv_obj_set_x(ui_dumbFriendWarning, 0);
    lv_obj_set_y(ui_dumbFriendWarning, 50);
    lv_obj_set_align(ui_dumbFriendWarning, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_dumbFriendWarning,
    "Tell your stupid friend to stay back, and keep his grubby fingers off of this thing!!");
    lv_obj_set_style_text_font(ui_dumbFriendWarning, &ui_font_tomorrow18, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_dumbFriendWarning, lv_color_hex(0xFF0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_dumbFriendWarning, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_dumbFriendWarning, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_dumbFriendWarning, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_dumbFriendWarning, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_dumbFriendWarning, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_dumbFriendWarning, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_dumbFriendWarning, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_dumbFriendWarning, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_dynoRunButton, ui_event_dynoRunButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_settingsButton, ui_event_settingsButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_freestyleButton, ui_event_freestyleButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_calibrateButton, ui_event_calibrateButton, LV_EVENT_ALL, NULL);
}