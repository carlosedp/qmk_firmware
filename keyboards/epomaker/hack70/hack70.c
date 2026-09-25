/* Copyright 2026 Epomaker
 * Copyright 2026 Epomaker <https://github.com/Epomaker>
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

// Battery indicator LED indices (number row, 1-0)
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// clang-format off
led_config_t g_led_config = { {
    {      0, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    {     28,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,     13, NO_LED, NO_LED },
    {     14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27, NO_LED, NO_LED },
    {     29,     30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40, NO_LED,     42,     41,     55 },
    {     43,     44,     45,     46,     47,     48,     49,     50,     51,     52,     53,     54, NO_LED,     56,     57, NO_LED },
    {     58,     59,     60,     61, NO_LED,     62, NO_LED, NO_LED, NO_LED,     63,     64,     65,     66,     67,     68,     69 },
}, {
    {  7,  6}, { 22,  6}, { 37,  6}, { 52,  6}, { 67,  6}, { 82,  6}, { 97,  6}, {112,  6}, {127,  6}, {142,  6}, {157,  6}, {172,  6}, {187,  6}, {209,  6},
    {  7, 19}, { 22, 19}, { 37, 19}, { 52, 19}, { 67, 19}, { 82, 19}, { 97, 19}, {112, 19}, {127, 19}, {142, 19}, {157, 19}, {172, 19}, {187, 19}, {202, 19}, {217, 19},
    {  7, 32}, { 22, 32}, { 37, 32}, { 52, 32}, { 67, 32}, { 82, 32}, { 97, 32}, {112, 32}, {127, 32}, {142, 32}, {157, 32}, {172, 32}, {187, 32}, {209, 32},
    {  7, 45}, { 22, 45}, { 37, 45}, { 52, 45}, { 67, 45}, { 82, 45}, { 97, 45}, {112, 45}, {127, 45}, {142, 45}, {157, 45}, {172, 45}, {187, 45}, {202, 45}, {217, 45},
    {  7, 58}, { 22, 58}, { 37, 58}, { 52, 58}, { 77, 58}, {114, 58}, {142, 58}, {157, 58}, {172, 58}, {187, 58}, {202, 58}, {217, 58},
    // Logo LEDs
    {112, 64}, {112, 64}, {112, 64}
}, {
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1,
    1, 1, 1, 1, 4, 4, 1, 1, 1, 1, 1, 1,
    // Logo LEDs
    0, 0, 0
} };
// clang-format on

// ============================================================================
// QMK Callback Functions - Delegate to common implementations
// ============================================================================

// These are keyboard-level (_kb) hooks rather than _user so that keymaps can
// still provide their own _user overrides without colliding with them here.
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    kb_rgb_matrix_indicators_common(led_min, led_max);
    return rgb_matrix_indicators_advanced_user(led_min, led_max);
}

void notify_usb_device_state_change_kb(struct usb_device_state usb_device_state) {
    kb_notify_usb_device_state_change(usb_device_state);
    notify_usb_device_state_change_user(usb_device_state);
}

bool led_update_kb(led_t led_state) {
    kb_led_update(led_state);
    return led_update_user(led_state);
}

void housekeeping_task_kb(void) {
    kb_housekeeping_task();
}

void board_init(void) {
    kb_board_init();
}

void keyboard_post_init_kb(void) {
    kb_keyboard_post_init();
    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
#if LOGO_LED_ENABLE
    process_logo_led_keycodes(keycode, record);
#endif
    if (!kb_process_record_common(keycode, record)) {
        return false;
    }
    return process_record_user(keycode, record);
}

#if defined(VIA_ENABLE) && LOGO_LED_ENABLE
// VIA custom channel 2 drives the Logo LED zone (see via_led_zone_command in
// user_led_zone.c): value_id 1=brightness, 2=effect, 3=speed, 4=hue+sat.
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *channel_id = &(data[1]);

    if (*channel_id == 2) {
        via_logo_led_command(data, length);
    }
}
#endif
