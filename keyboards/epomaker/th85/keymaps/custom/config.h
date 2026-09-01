/* Copyright 2021 QMK
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

#define LOGO_LED_ENABLE 1
#define SIDE_LED_ENABLE 1

// EEPROM sizing + layer count come from the shared header included by
// keyboards/epomaker/th85/config.h (lib/rdmctmzt_common/fs026_eeprom.h).

/* ============================================================
 * Idle ripple geometry/timing
 *
 * Single source of truth: both keymap.c (logo/side sync) and
 * rgb_matrix_user.inc (the main-matrix effect itself) are separate
 * translation units and both need these values, so they live here.
 * ============================================================ */

// Between G (x=85) and H (x=100) on the home row (y=40), per
// g_led_config in th85.c - the physically central point on the board.
#define TH85_RIPPLE_CENTER_X        92
#define TH85_RIPPLE_CENTER_Y        40

#define TH85_RIPPLE_MAX_RADIUS     120
#define TH85_RIPPLE_SEPARATION      60

#define TH85_RIPPLE_FRAME_MS        25
#define TH85_RIPPLE_STEP             3
#define TH85_RIPPLE_WIDTH           10

// Logo/side don't have real per-LED coordinates (they sit at a single
// placeholder point in g_led_config), so they're driven by a synthetic
// "distance" instead of the real x/y math the key matrix uses. Their
// window uses a wider band than TH85_RIPPLE_WIDTH so the flash lasts
// long enough to read as a pulse instead of a single-frame blip.
#define TH85_RIPPLE_ZONE_WIDTH      30
