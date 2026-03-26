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

#pragma once

#include "user_led_zone.h"

// Side LED feature flag - define in keyboard's config.h to enable
#ifndef SIDE_LED_ENABLE
#    define SIDE_LED_ENABLE 0
#endif

#if SIDE_LED_ENABLE

// Default Side LED configuration - can be overridden in keyboard's config.h
#    ifndef LED_SIDE_INDEX
#        define LED_SIDE_INDEX 0
#    endif

#    ifndef SIDE_LED_COUNT
#        define SIDE_LED_COUNT 1
#    endif

// Side LED effect mode aliases
#    define SIDE_MODE_NONE LED_ZONE_MODE_NONE
#    define SIDE_MODE_WAVE LED_ZONE_MODE_WAVE
#    define SIDE_MODE_WAVE1 LED_ZONE_MODE_WAVE1
#    define SIDE_MODE_WAVE2 LED_ZONE_MODE_WAVE2
#    define SIDE_MODE_FIXED_WAVE LED_ZONE_MODE_FIXED_WAVE
#    define SIDE_MODE_WAVE_RGB LED_ZONE_MODE_WAVE_RGB
#    define SIDE_MODE_SPECTRUM LED_ZONE_MODE_SPECTRUM
#    define SIDE_MODE_BREATHE LED_ZONE_MODE_BREATHE
#    define SIDE_MODE_BREATHE_RGB LED_ZONE_MODE_BREATHE_RGB
#    define SIDE_MODE_LIGHT LED_ZONE_MODE_LIGHT

void Side_Led_Update(void);
bool process_side_led_keycodes(uint16_t keycode, keyrecord_t *record);
void via_side_led_command(uint8_t *data, uint8_t length);

#endif // SIDE_LED_ENABLE
