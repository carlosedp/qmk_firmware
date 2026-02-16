/* Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
 * Copyright 2021 QMK <https://github.com/qmk/qmk_firmware>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keyboard_common.h"

#ifndef NO_LED
#    define NO_LED 255
#endif

// ===========================================================================
// Keyboard-specific data
// ===========================================================================
// Battery indicator LED indices (first row)
#ifndef BATTERY_LED_ARRAY
#    define BATTERY_LED_ARRAY {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}
#endif
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = BATTERY_LED_ARRAY;


// ============================================================================
// LED Matrix Configuration (keyboard-specific)
// ============================================================================

// clang-format off
led_config_t g_led_config = {
    // Key Matrix to LED Index (6x16 scan matrix with active keys in first 4 rows/12 cols)
    {
    {0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     NO_LED, NO_LED, NO_LED, NO_LED},
    {12,     13,     14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     NO_LED, NO_LED, NO_LED, NO_LED},
    {24,     25,     26,     27,     28,     29,     30,     31,     32,     33,     34,     35,     NO_LED, NO_LED, NO_LED, NO_LED},
    {36,     37,     38,     39,     40,     NO_LED, 41,     42,     43,     44,     45,     46,     NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}},
    // LED Index to Physical Position
    {
    {0, 10}, {20, 10}, {40, 10}, {60, 10}, {80, 10}, {100, 10}, {120, 10}, {140, 10}, {160, 10}, {180, 10}, {200, 10}, {224, 10},
    {0, 20}, {20, 20}, {40, 20}, {60, 20}, {80, 20}, {100, 20}, {120, 20}, {140, 20}, {160, 20}, {180, 20}, {200, 20}, {224, 20},
    {0, 30}, {20, 30}, {40, 30}, {60, 30}, {80, 30}, {100, 30}, {120, 30}, {140, 30}, {160, 30}, {180, 30}, {200, 30}, {224, 30},
    {0, 40}, {20, 40}, {40, 40}, {60, 40}, {80, 40},            {110, 40}, {140, 40}, {160, 40}, {180, 40}, {200, 40}, {224, 40}},
    // LED Index to Flag
    {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1
    }
};
// clang-format on

// ============================================================================
// RM_TOGG "fake off" — keep RGB matrix enabled for indicator callbacks
// ============================================================================
//
// QMK skips rgb_matrix_indicators_advanced_kb() when effect == 0, which
// happens when rgb_matrix_config.enable is false (i.e. after RM_TOGG off).
// The stock firmware's blob drives indicators independently, but the
// open-source library relies on QMK's callback.
//
// Fix: intercept RM_TOGG to toggle a flag instead of truly disabling RGB.
// When the flag is set, the indicator callback blacks out all LEDs before
// the library draws its indicators.  The effect is also switched to
// RGB_MATRIX_SOLID_COLOR (the cheapest possible mode) to minimize CPU
// and DMA overhead while the LEDs appear off.  The previous effect mode
// is saved and restored when the user toggles back on.  On boot, if
// EEPROM already has RGB disabled, force-enable and start in fake-off.
//
// Both the fake-off flag and saved mode are persisted in QMK's KB-level
// eeconfig datablock (EECONFIG_KB_DATA_SIZE = 1) so the state survives
// power cycles and sleep/wake.

// Persisted via QMK's KB-level eeconfig datablock (EECONFIG_KB_DATA_SIZE = 1).
typedef union {
    uint8_t raw;
    struct {
        bool    rgb_effects_off : 1;
        uint8_t rgb_saved_mode  : 7;  // 0-127 covers all RGB_MATRIX_* modes
    };
} kb_config_t;

static kb_config_t kb_config;

// ============================================================================
// QMK Callback Functions - Delegate to common implementations
// ============================================================================

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    // In fake-off mode: black out every LED the effect just painted,
    // then let the library draw indicators on top.
    if (kb_config.rgb_effects_off) {
        for (uint8_t i = led_min; i < led_max; i++) {
            kb_led_off(i);
        }
    }
    if (!kb_rgb_matrix_indicators_common(led_min, led_max)) {
        return false;
    }
    return rgb_matrix_indicators_advanced_user(led_min, led_max);
}

void notify_usb_device_state_change_kb(struct usb_device_state usb_device_state) {
    kb_notify_usb_device_state_change(usb_device_state);
    notify_usb_device_state_change_user(usb_device_state);
}

bool led_update_kb(led_t led_state) {
    if (!kb_led_update(led_state)) {
        return false;
    }
    return led_update_user(led_state);
}

void housekeeping_task_kb(void) {
    kb_housekeeping_task();
    housekeeping_task_user();
}

void board_init(void) {
    kb_board_init();
}

void eeconfig_init_kb(void) {
    // Called on EEPROM reset (EE_CLR).  Zero the KB datablock so RGB
    // starts with effects ON and no stale saved mode.
    kb_config.raw = 0;
    eeconfig_update_kb_datablock(&kb_config, 0, sizeof(kb_config));
    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    kb_keyboard_post_init();

    // Restore persisted fake-off state from KB datablock.
    eeconfig_read_kb_datablock(&kb_config, 0, sizeof(kb_config));

    if (kb_config.rgb_effects_off) {
        // User toggled LEDs off before last power-down — resume fake-off.
        if (!rgb_matrix_is_enabled()) {
            rgb_matrix_enable_noeeprom();
        }
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    } else if (!rgb_matrix_is_enabled()) {
        // Legacy: EEPROM has RGB truly disabled (from before fake-off fix).
        // Force-enable so indicators work, and start in fake-off.
        rgb_matrix_enable_noeeprom();
        kb_config.rgb_effects_off = true;
        kb_config.rgb_saved_mode  = RGB_MATRIX_SOLID_COLOR;
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        eeconfig_update_kb_datablock(&kb_config, 0, sizeof(kb_config));
    }

    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Intercept RM_TOGG: toggle fake-off flag instead of truly disabling
    // RGB, so the indicator callback keeps firing.
    // IMPORTANT: must block BOTH press AND release — QMK's process_rgb_matrix
    // triggers on key release by default (not press), so letting the release
    // through would call rgb_matrix_toggle() and truly disable the matrix.
    if (keycode == RM_TOGG) {
        if (record->event.pressed) {
            kb_config.rgb_effects_off = !kb_config.rgb_effects_off;
            if (kb_config.rgb_effects_off) {
                // Save current mode, switch to cheapest effect to reduce
                // CPU and DMA overhead while LEDs appear off.
                kb_config.rgb_saved_mode = rgb_matrix_get_mode();
                rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            } else {
                // Restore the user's previous effect mode.
                rgb_matrix_mode_noeeprom(kb_config.rgb_saved_mode);
            }
            eeconfig_update_kb_datablock(&kb_config, 0, sizeof(kb_config));
        }
        return false;  // Consumed — don't pass to library or QMK
    }
    if (!kb_process_record_common(keycode, record)) {
        return false;
    }
    return process_record_user(keycode, record);
}
