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

#if LOGO_LED_ENABLE || SIDE_LED_ENABLE

// ============================================================================
// Helpers
// ============================================================================

void led_zone_set_color(led_zone_t *zone, uint8_t r, uint8_t g, uint8_t b) {
    for (uint8_t i = 0; i < zone->led_count; i++) {
        rgb_matrix_driver_set_color(zone->led_start + i, r, g, b);
    }
}

// ============================================================================
// Effects (static — internal to this translation unit)
// ============================================================================

static void zone_effect_solid(led_zone_t *zone) {
    if (!(*zone->on_off)) {
        led_zone_set_color(zone, 0, 0, 0);
        return;
    }
    HSV hsv = {*zone->hue, *zone->saturation, *zone->brightness};
    RGB rgb = hsv_to_rgb(hsv);
    led_zone_set_color(zone, rgb.r, rgb.g, rgb.b);
}

static void zone_effect_breathe(led_zone_t *zone) {
    if (!(*zone->on_off)) {
        led_zone_set_color(zone, 0, 0, 0);
        return;
    }
    uint8_t spd    = (*zone->speed + 1) * 10;
    uint8_t breath = Led_Wave_Pwm_Tab[(zone->_step * spd / 10) % 128];
    uint8_t scaled = (breath * (*zone->brightness)) / 255;
    HSV     hsv    = {*zone->hue, *zone->saturation, scaled};
    RGB     rgb    = hsv_to_rgb(hsv);
    led_zone_set_color(zone, rgb.r, rgb.g, rgb.b);
}

static void zone_effect_breathe_rgb(led_zone_t *zone) {
    if (!(*zone->on_off)) {
        led_zone_set_color(zone, 0, 0, 0);
        return;
    }
    uint8_t spd    = (*zone->speed + 1) * 10;
    uint8_t breath = Led_Wave_Pwm_Tab[(zone->_step * spd / 10) % 128];
    uint8_t scaled = (breath * (*zone->brightness)) / 255;
    uint8_t hue    = (zone->_step * spd / 5) % 256;
    HSV     hsv    = {hue, *zone->saturation, scaled};
    RGB     rgb    = hsv_to_rgb(hsv);
    led_zone_set_color(zone, rgb.r, rgb.g, rgb.b);
}

static void zone_effect_spectrum(led_zone_t *zone) {
    if (!(*zone->on_off)) {
        led_zone_set_color(zone, 0, 0, 0);
        return;
    }
    uint8_t spd = (*zone->speed + 1) * 5;
    uint8_t hue = (zone->_step * spd / 5) % 256;
    HSV     hsv = {hue, *zone->saturation, *zone->brightness};
    RGB     rgb = hsv_to_rgb(hsv);
    led_zone_set_color(zone, rgb.r, rgb.g, rgb.b);
}

static void zone_effect_wave(led_zone_t *zone) {
    if (!(*zone->on_off)) {
        led_zone_set_color(zone, 0, 0, 0);
        return;
    }
    uint8_t spd = (*zone->speed + 1) * 10;
    for (uint8_t i = 0; i < zone->led_count; i++) {
        uint8_t off    = (zone->_step * spd / 10 + i * 25) % 128;
        uint8_t scaled = (Led_Wave_Pwm_Tab[off] * (*zone->brightness)) / 255;
        HSV     hsv    = {*zone->hue, *zone->saturation, scaled};
        RGB     rgb    = hsv_to_rgb(hsv);
        rgb_matrix_driver_set_color(zone->led_start + i, rgb.r, rgb.g, rgb.b);
    }
}

static void zone_effect_wave_rgb(led_zone_t *zone) {
    if (!(*zone->on_off)) {
        led_zone_set_color(zone, 0, 0, 0);
        return;
    }
    uint8_t spd = (*zone->speed + 1) * 10;
    for (uint8_t i = 0; i < zone->led_count; i++) {
        uint8_t off    = (zone->_step * spd / 10 + i * 25) % 128;
        uint8_t scaled = (Led_Wave_Pwm_Tab[off] * (*zone->brightness)) / 255;
        uint8_t hue    = (zone->_step * spd / 10 + i * 50) % 256;
        HSV     hsv    = {hue, *zone->saturation, scaled};
        RGB     rgb    = hsv_to_rgb(hsv);
        rgb_matrix_driver_set_color(zone->led_start + i, rgb.r, rgb.g, rgb.b);
    }
}

// ============================================================================
// Public API
// ============================================================================

void led_zone_update(led_zone_t *zone) {
    if (timer_elapsed(zone->_timer) > 20) {
        zone->_timer = timer_read();
        zone->_step++;
    }
    switch (*zone->mode) {
        case LED_ZONE_MODE_NONE:
            led_zone_set_color(zone, 0, 0, 0);
            break;
        case LED_ZONE_MODE_WAVE:
        case LED_ZONE_MODE_WAVE1:
        case LED_ZONE_MODE_WAVE2:
        case LED_ZONE_MODE_FIXED_WAVE:
            zone_effect_wave(zone);
            break;
        case LED_ZONE_MODE_WAVE_RGB:
            zone_effect_wave_rgb(zone);
            break;
        case LED_ZONE_MODE_SPECTRUM:
            zone_effect_spectrum(zone);
            break;
        case LED_ZONE_MODE_BREATHE:
            zone_effect_breathe(zone);
            break;
        case LED_ZONE_MODE_BREATHE_RGB:
            zone_effect_breathe_rgb(zone);
            break;
        case LED_ZONE_MODE_LIGHT:
        default:
            zone_effect_solid(zone);
            break;
    }
}

bool process_led_zone_keycodes(led_zone_t *zone, uint16_t keycode, keyrecord_t *record) {
    if (keycode < zone->keycode_base || keycode > (uint16_t)(zone->keycode_base + 10)) {
        return false;
    }
    if (record->event.pressed) {
        return true; // consume on press, act on release
    }
    uint8_t offset = (uint8_t)(keycode - zone->keycode_base);
    switch (offset) {
        case 0: // TOG
            *zone->on_off = !(*zone->on_off);
            break;
        case 1: // MOD
            (*zone->mode)++;
            if (*zone->mode > 9) *zone->mode = 0;
            break;
        case 2: // RMOD
            if (*zone->mode == 0)
                *zone->mode = 9;
            else
                (*zone->mode)--;
            break;
        case 3: // HUI
            *zone->hue += 8;
            break;
        case 4: // HUD
            *zone->hue -= 8;
            break;
        case 5: // SAI
            *zone->saturation = (*zone->saturation <= 247) ? (*zone->saturation + 8) : 255;
            break;
        case 6: // SAD
            *zone->saturation = (*zone->saturation >= 8) ? (*zone->saturation - 8) : 0;
            break;
        case 7: // VAI
            *zone->brightness = (*zone->brightness <= 247) ? (*zone->brightness + 8) : 255;
            break;
        case 8: // VAD
            *zone->brightness = (*zone->brightness >= 8) ? (*zone->brightness - 8) : 0;
            break;
        case 9: // SPI
            if (*zone->speed < 4) (*zone->speed)++;
            break;
        case 10: // SPD
            if (*zone->speed > 0) (*zone->speed)--;
            break;
    }
    Save_Flash_Set();
    return true;
}

void via_led_zone_command(led_zone_t *zone, uint8_t *data, uint8_t length) {
    uint8_t *command_id = &(data[0]);
    uint8_t *channel_id = &(data[1]);
    uint8_t *value_id   = &(data[2]);
    uint8_t *value_data = &(data[3]);

    if (*channel_id != zone->via_channel) return;

    switch (*command_id) {
        case 0x07: // id_custom_set_value
            switch (*value_id) {
                case 1:
                    *zone->brightness = value_data[0];
                    break;
                case 2:
                    *zone->mode   = value_data[0];
                    *zone->on_off = (value_data[0] > 0) ? 1 : 0;
                    break;
                case 3:
                    *zone->speed = value_data[0];
                    break;
                case 4:
                    *zone->hue        = value_data[0];
                    *zone->saturation = value_data[1];
                    break;
            }
            Save_Flash_Set();
            break;
        case 0x08: // id_custom_get_value
            switch (*value_id) {
                case 1:
                    value_data[0] = *zone->brightness;
                    break;
                case 2:
                    value_data[0] = (*zone->on_off) ? *zone->mode : 0;
                    break;
                case 3:
                    value_data[0] = *zone->speed;
                    break;
                case 4:
                    value_data[0] = *zone->hue;
                    value_data[1] = *zone->saturation;
                    break;
            }
            break;
        case 0x09: // id_custom_save
            Save_Flash_Set();
            break;
    }
}

#endif // LOGO_LED_ENABLE || SIDE_LED_ENABLE
