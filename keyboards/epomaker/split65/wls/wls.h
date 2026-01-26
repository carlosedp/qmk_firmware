/* Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
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

#include QMK_KEYBOARD_H

#include "quantum.h"
#include <stdbool.h>
#include "wireless.h"

#define HS_BT_DEF_PIN C14
#define HS_2G4_DEF_PIN C15
#define HS_BT_PIN_STATE 0, 1
#define HS_2G4_PIN_STATE 1, 0
#define HS_USB_PIN_STATE 1, 1

#define HS_GET_MODE_PIN_(pin_bt, pin_2g4) ((((#pin_bt)[0] == 'x') || ((readPin(HS_BT_DEF_PIN) + 0x30) == ((#pin_bt)[0]))) && (((#pin_2g4)[0] == 'x') || ((readPin(HS_2G4_DEF_PIN) + 0x30) == ((#pin_2g4)[0]))))
#define HS_GET_MODE_PIN(state) HS_GET_MODE_PIN_(state)
#define HS_MODEIO_DETECTION_TIME 50
#define HS_LBACK_TIMEOUT (30 * 1000)
#ifndef HS_SLEEP_TIMEOUT
#    define HS_SLEEP_TIMEOUT (1 * 300000) // Default: 5 minutes
#endif

enum modeio_mode { hs_none = 0, hs_usb, hs_bt, hs_2g4, hs_wireless };

extern bool lower_sleep;
bool        hs_rgb_blink_hook(void);
bool        hs_mode_scan(bool update, uint8_t moude, uint8_t lsat_btdev);
bool        hs_modeio_detection(bool update, uint8_t *mode, uint8_t lsat_btdev);
void        hs_rgb_blink_set_timer(uint32_t time);
