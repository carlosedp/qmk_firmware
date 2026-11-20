/* EVO75-specific matrix-to-LED map */
#include "keyboard_common.h"

#ifndef NO_LED
#    define NO_LED 255
#endif

const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

/* Key LEDs use chain indices 0-79; logo starts at 80. */
led_config_t g_led_config = {
    {
        {  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, NO_LED, NO_LED, NO_LED },
        { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, NO_LED, NO_LED },
        { 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 13, 28 },
        { 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, NO_LED, 56, 43, 57 },
        { 58, NO_LED, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, NO_LED, 69, 70, NO_LED },
        { 71, 72, 73, NO_LED, NO_LED, 74, NO_LED, NO_LED, NO_LED, NO_LED, 75, NO_LED, 76, 77, 78, 79 },
    },
    {
        {   0,  8 }, {  25,  8 }, {  40,  8 }, {  54,  8 }, {  69,  8 }, {  87,  8 }, { 101,  8 }, { 116,  8 }, { 130,  8 }, { 148,  8 }, { 163,  8 }, { 177,  8 }, { 191,  8 }, { 217,  8 },
        {   0, 21 }, {  14, 21 }, {  29, 21 }, {  43, 21 }, {  58, 21 }, {  72, 21 }, {  87, 21 }, { 101, 21 }, { 116, 21 }, { 130, 21 }, { 145, 21 }, { 159, 21 }, { 173, 21 }, { 188, 21 }, { 217, 21 },
        {   0, 32 }, {  22, 32 }, {  36, 32 }, {  51, 32 }, {  65, 32 }, {  79, 32 }, {  94, 32 }, { 108, 32 }, { 123, 32 }, { 137, 32 }, { 152, 32 }, { 166, 32 }, { 181, 32 }, { 195, 32 }, { 217, 32 },
        {   0, 43 }, {  25, 43 }, {  40, 43 }, {  54, 43 }, {  69, 43 }, {  83, 43 }, {  98, 43 }, { 112, 43 }, { 126, 43 }, { 141, 43 }, { 155, 43 }, { 170, 43 }, { 184, 43 }, { 217, 43 },
        {   0, 53 }, {  33, 53 }, {  47, 53 }, {  61, 53 }, {  76, 53 }, {  90, 53 }, { 105, 53 }, { 119, 53 }, { 134, 53 }, { 148, 53 }, { 163, 53 }, { 177, 53 }, { 202, 53 },
        {   0, 64 }, {  18, 64 }, {  36, 64 }, {  95, 64 }, { 145, 64 }, { 163, 64 }, { 188, 64 }, { 202, 64 }, { 217, 64 },
        /* Logo LEDs */
        /* Top right vertical strip, starting from the bottom and going up */
        { 201, 0 },  { 201, 1 },  { 201, 2 },  { 201, 3 },  { 201, 4 },  { 201, 5 },  { 201, 6 },
        /* Top left vertical strip, starting from the bottom and going up */
        { 16, 0 },   { 16, 1 },   { 16, 2 },   { 16, 3 },   { 16, 4 },   { 16, 5 },   { 16, 6 },
        /* Ring around the evo button, starting from the leftmost LED and moving counterclockwise */
        { 212, 49 }, { 214, 51 }, { 217, 53 }, { 220, 51 }, { 222, 49 }, { 220, 47 }, { 217, 45 }, { 214, 47 },
        /* Vertical strip next to the evo logo, starting from the bottom and going up */
        { 224, 51 }, { 224, 49 }, { 224, 47 },
    },
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        /* Logo LEDs are controlled by the shared logo zone, not matrix effects. */
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0,
    },
};

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    kb_rgb_matrix_indicators_common(led_min, led_max);
    return false;
}

void notify_usb_device_state_change_kb(struct usb_device_state usb_device_state) {
    kb_notify_usb_device_state_change(usb_device_state);
    notify_usb_device_state_change_user(usb_device_state);
}

bool led_update_kb(led_t led_state) {
    if (!led_update_user(led_state)) {
        return false;
    }
    return kb_led_update(led_state);
}

#if LOGO_LED_ENABLE
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    via_logo_led_command(data, length);
}
#endif

void housekeeping_task_kb(void) {
    kb_housekeeping_task();
    housekeeping_task_user();
}

void board_init(void) {
    kb_board_init();
}

void keyboard_post_init_kb(void) {
    kb_keyboard_post_init();
    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }

#if LOGO_LED_ENABLE
    switch (keycode) {
        case LOGO_TOG:
        case LOGO_MOD:
        case LOGO_RMOD:
        case LOGO_HUI:
        case LOGO_HUD:
        case LOGO_SAI:
        case LOGO_SAD:
        case LOGO_VAI:
        case LOGO_VAD:
        case LOGO_SPI:
        case LOGO_SPD:
            process_logo_led_keycodes(keycode, record);
            return false;
    }
#endif
    return kb_process_record_common(keycode, record);
}
