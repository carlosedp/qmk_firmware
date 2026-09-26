/* Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
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

// ===========================================================================
// Keyboard-specific data
// ===========================================================================

// Battery indicator LED indices (number row, keys 1 through =)
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

// ============================================================================
// LED Matrix Configuration (keyboard-specific)
// ============================================================================
//
// All 101 LEDs are key backlights; the board has no logo or underglow strip.
// LED 17 is wired to the unpopulated (5,8) matrix slot that sits under the
// rotary knob, so it is lit by effects but never by a key press.

// clang-format off
led_config_t g_led_config = { {
    {     0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13,     32,     51},
    {    18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,     31, NO_LED, NO_LED},
    {    37,     38,     39,     40,     41,     42,     43,     44,     45,     46,     47,     48,     49,     50, NO_LED, NO_LED},
    {    56,     57,     58,     59,     60,     61,     62,     63,     64,     65,     66,     67, NO_LED,     68, NO_LED,     69},
    {    73, NO_LED,     74,     75,     76,     77,     78,     79,     80,     81,     82,     83, NO_LED,     84,     85,     86},
    {    89,     90,     91, NO_LED,     14,     92,     15,     16,     17,     93,     94, NO_LED, NO_LED,     95,     96,     97},
    {    33,     34,     35,     36,     52,     53,     54,     70,     71,     72,     55,     87,     88,     98,     99,    100}
}, {
    {  5,  5}, { 27,  5}, { 38,  5}, { 49,  5}, { 60,  5}, { 76,  5}, { 87,  5}, { 98,  5}, {109,  5}, {126,  5}, {137,  5}, {148,  5}, {158,  5}, {172,  5}, {186,  5}, {197,  5}, {208,  5}, {219,  5},
    {  5, 16}, { 16, 16}, { 27, 16}, { 38, 16}, { 49, 16}, { 60, 16}, { 71, 16}, { 82, 16}, { 93, 16}, {104, 16}, {115, 16}, {126, 16}, {137, 16}, {153, 16}, {172, 16}, {186, 16}, {197, 16}, {208, 16}, {219, 16},
    {  8, 27}, { 22, 27}, { 33, 27}, { 44, 27}, { 55, 27}, { 66, 27}, { 76, 27}, { 87, 27}, { 98, 27}, {109, 27}, {120, 27}, {131, 27}, {142, 27}, {156, 27}, {172, 27}, {186, 27}, {197, 27}, {208, 27}, {219, 32},
    { 10, 37}, { 25, 37}, { 36, 37}, { 46, 37}, { 57, 37}, { 68, 37}, { 79, 37}, { 90, 37}, {101, 37}, {112, 37}, {123, 37}, {134, 37}, {152, 37}, {172, 37}, {186, 37}, {197, 37}, {208, 37},
    { 12, 48}, { 30, 48}, { 41, 48}, { 52, 48}, { 63, 48}, { 74, 48}, { 85, 48}, { 96, 48}, {107, 48}, {117, 48}, {128, 48}, {143, 48}, {158, 48}, {186, 48}, {197, 48}, {208, 48},
    {  7, 59}, { 20, 59}, { 34, 59}, { 75, 59}, {116, 59}, {130, 59}, {148, 59}, {158, 59}, {169, 59}, {191, 59}, {208, 59}, {219, 53}
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
} };
// clang-format on

// ============================================================================
// QMK Callback Functions - Delegate to common implementations
// ============================================================================

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    return kb_rgb_matrix_indicators_common(led_min, led_max);
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
    return kb_process_record_common(keycode, record);
}
