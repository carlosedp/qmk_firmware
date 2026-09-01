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

#define TH85_RIPPLE_CENTER_X       112
// Moved down from the vertical middle (40) towards the ZXCV row so the
// ripple's origin feels centered under where your hands rest instead of
// up near the QWERTY row.
#define TH85_RIPPLE_CENTER_Y        50

// The key matrix's coordinate space is only ~50 units tall (y 10..60)
// but ~224 units wide, so a plain circular distance reaches the top/
// bottom edges almost immediately and spends nearly all of its travel
// sweeping left/right. Scaling dy up compensates for that squish so the
// ripple spends comparable time/visible travel going up and down as it
// does going left and right.
#define TH85_RIPPLE_Y_SCALE          3

#define TH85_RIPPLE_MAX_RADIUS     120
#define TH85_RIPPLE_SEPARATION      60

#define TH85_RIPPLE_FRAME_MS        25
#define TH85_RIPPLE_STEP             3
#define TH85_RIPPLE_WIDTH           10
