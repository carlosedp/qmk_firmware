/* Copyright 2024 Finalkey
 * Copyright 2024 LiWenLiu <https://github.com/LiuLiuQMK>
 * Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
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

#include "rdmctmzt_common.h"

#if LOGO_LED_ENABLE

static led_zone_t logo_zone = {
    .on_off       = &Keyboard_Info.Logo_On_Off,
    .mode         = &Keyboard_Info.Logo_Mode,
    .hue          = &Keyboard_Info.Logo_Hue,
    .saturation   = &Keyboard_Info.Logo_Saturation,
    .brightness   = &Keyboard_Info.Logo_Brightness,
    .speed        = &Keyboard_Info.Logo_Speed,
    .led_start    = LED_LOGO_INDEX,
    .led_count    = LOGO_LED_COUNT,
    .via_channel  = 2,
    .keycode_base = LOGO_TOG,
};

void Logo_Led_Update(void) {
    led_zone_update(&logo_zone);
}
bool process_logo_led_keycodes(uint16_t keycode, keyrecord_t *record) {
    return process_led_zone_keycodes(&logo_zone, keycode, record);
}
void via_logo_led_command(uint8_t *data, uint8_t length) {
    via_led_zone_command(&logo_zone, data, length);
}

#endif // LOGO_LED_ENABLE
