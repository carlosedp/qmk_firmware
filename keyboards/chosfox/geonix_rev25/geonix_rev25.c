/* Copyright 2025 bofhgit
 * Copyright 2026 BunnyHorseCat
 * Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
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
#include "action_util.h"
#include "report.h"

#ifndef NO_LED
#    define NO_LED 255
#endif

// Battery indicator LEDs: top row (TAB through BSPC)
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// clang-format off
/*****************rgb矩阵驱动初始化********************/
led_config_t g_led_config = { {
	{ 0        , 1        , 2        , 3        , 4        , 5        , 6        , 7        , 8        , 9        , 10       , 11       },
        { 12       , 13       , 14       , 15       , 16       , 17       , 18       , 19       , 20       , 21       , 22       , 23       }, 
	{ 24       , 25       , 26       , 27       , 28       , 29       , 30       , 31       , 32       , 33       , 34       , 35       }, 
	{ 36       , 42       , 37       , 38       , 39       , 40       , 41       , 43       , 44       , 45       , 46       , 47       }
},{
    // 背光灯
    { 0,  10},  { 20, 10},  { 40, 10},  { 60, 10}, { 80, 10}, { 100, 10}, { 120, 10}, { 140, 10}, { 160, 10}, { 180, 10}, { 200, 10}, { 224, 10}, 
    { 0,  20},  { 20, 20},  { 40, 20},  { 60, 20}, { 80, 20}, { 100, 20}, { 120, 20}, { 140, 20}, { 160, 20}, { 180, 20}, { 200, 20}, { 224, 20}, 
    { 0,  30},  { 20, 30},  { 40, 30},  { 60, 30}, { 80, 30}, { 100, 30}, { 120, 30}, { 140, 30}, { 160, 30}, { 180, 30}, { 200, 30}, { 224, 30}, 
    { 0,  40},  { 20, 40},  { 40, 40},  { 60, 40}, { 80, 40}, { 100, 40}, { 120, 40}, { 140, 40}, { 160, 40}, { 180, 40}, { 200, 40}, { 224, 40},

    { 255,65},  { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65},  { 255,65}, { 255,65},
    { 255,65},  { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65},  { 255,65}, { 255,65},
    { 255,65},  { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65}, { 255,65},  { 255,65}
}, {
    // 背光灯
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  
    1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,

    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0
} };

// clang-format on

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    return kb_rgb_matrix_indicators_common(led_min, led_max);
}

void notify_usb_device_state_change_user(struct usb_device_state usb_device_state) {
    kb_notify_usb_device_state_change(usb_device_state);
}

bool led_update_user(led_t led_state) {
    return kb_led_update(led_state);
}

void housekeeping_task_user(void) {
    kb_housekeeping_task();
}

void board_init(void) {
    kb_board_init();
}

void keyboard_post_init_user(void) {
    kb_keyboard_post_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#if LOGO_LED_ENABLE
    // Process logo LED keycodes - returns true if handled
    process_logo_led_keycodes(keycode, record);
#endif
    return kb_process_record_common(keycode, record);
}

#if defined(VIA_ENABLE) && defined(LOGO_LED_ENABLE)
// VIA custom channel IDs for Logo LED
enum via_logo_led_value {
    id_logo_brightness = 1,
    id_logo_effect = 2,
    id_logo_effect_speed = 3,
    id_logo_color = 4,
};

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
    uint8_t *value_id   = &(data[2]);
    uint8_t *value_data = &(data[3]);

    // Only handle channel 1 (Logo LED), let other channels pass through
    if (*channel_id != 1) {
        return;
    }

    if (*command_id == id_custom_set_value) {
        switch (*value_id) {
            case id_logo_brightness:
                Keyboard_Info.Logo_Brightness = value_data[0];
                Save_Flash_Set();
                break;
            case id_logo_effect:
                Keyboard_Info.Logo_Mode = value_data[0];
                Save_Flash_Set();
                break;
            case id_logo_effect_speed:
                Keyboard_Info.Logo_Speed = value_data[0];
                Save_Flash_Set();
                break;
            case id_logo_color:
                Keyboard_Info.Logo_Hue = value_data[0];
                Keyboard_Info.Logo_Saturation = value_data[1];
                Save_Flash_Set();
                break;
        }
    } else if (*command_id == id_custom_get_value) {
        switch (*value_id) {
            case id_logo_brightness:
                value_data[0] = Keyboard_Info.Logo_Brightness;
                break;
            case id_logo_effect:
                value_data[0] = Keyboard_Info.Logo_Mode;
                break;
            case id_logo_effect_speed:
                value_data[0] = Keyboard_Info.Logo_Speed;
                break;
            case id_logo_color:
                value_data[0] = Keyboard_Info.Logo_Hue;
                value_data[1] = Keyboard_Info.Logo_Saturation;
                break;
        }
    }
}
#endif

// ============================================================================
// Compatibility shims for patched core files
// This repo's action_util.c/h call these instead of host_keyboard_send()
// and del_key() directly. The open-source library installs its own host
// driver, so routing through host_keyboard_send() is correct here.
// ============================================================================

// has_anykey() checks nkro_report->bits when NKRO is enabled, but
// add_key_to_report() places keys in keyboard_report->keys first. Check
// both so OSM clears correctly regardless of NKRO state.
static bool any_key_in_report(void) {
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report->keys[i]) return true;
    }
#ifdef NKRO_ENABLE
    for (uint8_t i = 0; i < NKRO_REPORT_BITS; i++) {
        if (nkro_report->bits[i]) return true;
    }
#endif
    return false;
}

// Compute mods the same way the original send_6kro_report/send_nkro_report do:
// include oneshot mods, then clear them once a regular key is held.
static uint8_t compute_mods_for_report(void) {
    uint8_t mods = get_mods() | get_weak_mods();
    uint8_t osm  = get_oneshot_mods();
    if (osm) {
        if (has_oneshot_mods_timed_out()) {
            clear_oneshot_mods();
        } else {
            mods |= osm;
            if (any_key_in_report()) {
                clear_oneshot_mods();
            }
        }
    }
    return mods;
}

void User_send_nkro_report(void) {
    keyboard_report->mods = compute_mods_for_report();
    host_keyboard_send(keyboard_report);
}

void User_send_6kro_report(void) {
    keyboard_report->mods = compute_mods_for_report();
    host_keyboard_send(keyboard_report);
}
