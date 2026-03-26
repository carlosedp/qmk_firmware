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

#include "quantum.h"

// Shared LED zone effect mode constants (used by both logo and side zones)
#define LED_ZONE_MODE_NONE 0
#define LED_ZONE_MODE_WAVE 1
#define LED_ZONE_MODE_WAVE1 2
#define LED_ZONE_MODE_WAVE2 3
#define LED_ZONE_MODE_FIXED_WAVE 4
#define LED_ZONE_MODE_WAVE_RGB 5
#define LED_ZONE_MODE_SPECTRUM 6
#define LED_ZONE_MODE_BREATHE 7
#define LED_ZONE_MODE_BREATHE_RGB 8
#define LED_ZONE_MODE_LIGHT 9

// LED zone configuration and state.
// Pointers reference fields in Keyboard_Info (addresses are link-time constants).
// _timer and _step are internal animation state; initialize to zero.
typedef struct {
    uint8_t *on_off;       // on/off flag
    uint8_t *mode;         // effect mode (LED_ZONE_MODE_*)
    uint8_t *hue;          // hue (0-255)
    uint8_t *saturation;   // saturation (0-255)
    uint8_t *brightness;   // brightness (0-255)
    uint8_t *speed;        // effect speed (0-4)
    uint8_t  led_start;    // first LED index in the RGB matrix
    uint8_t  led_count;    // number of LEDs in this zone
    uint8_t  via_channel;  // VIA channel ID for this zone
    uint16_t keycode_base; // TOG keycode; MOD/RMOD/HUI/.../SPD follow consecutively
    uint16_t _timer;       // animation timer (internal)
    uint8_t  _step;        // animation step counter (internal)
} led_zone_t;

// Set all LEDs in the zone to a solid RGB colour
void led_zone_set_color(led_zone_t *zone, uint8_t r, uint8_t g, uint8_t b);

// Drive the zone's current effect; call periodically (e.g. from housekeeping_task)
void led_zone_update(led_zone_t *zone);

// Handle zone keycodes (TOG/MOD/RMOD/HUI/HUD/SAI/SAD/VAI/VAD/SPI/SPD).
// Returns true if the keycode belonged to this zone.
bool process_led_zone_keycodes(led_zone_t *zone, uint16_t keycode, keyrecord_t *record);

// VIA custom value handler — routes set/get/save for the zone's via_channel
void via_led_zone_command(led_zone_t *zone, uint8_t *data, uint8_t length);
