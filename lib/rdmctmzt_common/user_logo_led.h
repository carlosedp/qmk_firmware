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

// Logo LED feature flag - define in keyboard's config.h to enable
#ifndef LOGO_LED_ENABLE
#    define LOGO_LED_ENABLE 0
#endif

#if LOGO_LED_ENABLE

// Default Logo LED configuration - override in keyboard's config.h
#    ifndef LED_LOGO_INDEX
#        define LED_LOGO_INDEX 0
#    endif
#    ifndef LOGO_LED_COUNT
#        define LOGO_LED_COUNT 1
#    endif

// Mode aliases (map to shared LED_ZONE_MODE_* constants)
#    define LOGO_MODE_NONE LED_ZONE_MODE_NONE
#    define LOGO_MODE_WAVE LED_ZONE_MODE_WAVE
#    define LOGO_MODE_WAVE1 LED_ZONE_MODE_WAVE1
#    define LOGO_MODE_WAVE2 LED_ZONE_MODE_WAVE2
#    define LOGO_MODE_FIXED_WAVE LED_ZONE_MODE_FIXED_WAVE
#    define LOGO_MODE_WAVE_RGB LED_ZONE_MODE_WAVE_RGB
#    define LOGO_MODE_SPECTRUM LED_ZONE_MODE_SPECTRUM
#    define LOGO_MODE_BREATHE LED_ZONE_MODE_BREATHE
#    define LOGO_MODE_BREATHE_RGB LED_ZONE_MODE_BREATHE_RGB
#    define LOGO_MODE_LIGHT LED_ZONE_MODE_LIGHT

void Logo_Led_Update(void);
bool process_logo_led_keycodes(uint16_t keycode, keyrecord_t *record);
void via_logo_led_command(uint8_t *data, uint8_t length);

#endif // LOGO_LED_ENABLE
