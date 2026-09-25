/* Copyright 2026 BunnyHorseCat
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

#define MATRIX_UNSELECT_DRIVE_HIGH
#define CORTEX_ENABLE_WFI_IDLE FALSE

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define ONESHOT_TIMEOUT 1000

#ifndef NOP_FUDGE
#define NOP_FUDGE 0.4
#endif

#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 1151
#define EEPROM_SIZE 1152
#define FEE_PAGE_SIZE (0x200)
#define FEE_PAGE_COUNT (8)
#define FEE_PAGE_BASE_ADDRESS (0x1F000)
#define FEE_MCU_FLASH_SIZE (0x1000)
#define EECONFIG_USER_DATA_SIZE 4
#define EECONFIG_KB_DATA_SIZE 1
#define TRANSIENT_EEPROM_SIZE 4096

#define RGB_MATRIX_LED_COUNT 77
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 255
#define RGB_MATRIX_SLEEP

#define RGB_MATRIX_SPD_STEP   16                 // 设置 RGB 矩阵速度步进值
#define RGB_MATRIX_VAL_STEP   16                 // 设置 RGB 矩阵亮度步进值

// BLE configuration for GEONIX REV.2.5 OSS port
#define USER_BLE_ID (0X0116)
#define USER_BLE1_NAME "Geonix R2.5 1"
#define USER_BLE2_NAME "Geonix R2.5 2"
#define USER_BLE3_NAME "Geonix R2.5 3"

/* Battery LED count */
#define BATTERY_LED_COUNT 10

// LED Index Definitions (for keyboard_common library)
// Row 0 (TAB row):  LEDs  0-11 = TAB,Q,W,E,R,T,Y,U,I,O,P,BSPC
// Row 1 (ESC row):  LEDs 12-23 = ESC,A,S,D,F,G,H,J,K,L,SCLN,QUOT
// Row 2 (SFT row):  LEDs 24-35 = LSFT,Z,X,C,V,B,N,M,,,.,UP,ENT
// Row 3 (bot row):  LEDs 36,--,37,38,39,40,41,42,43,44,45,46
//                        MO2,   DEL,CTL,ALT,GUI,SPC,RGUI,/,<,v,>
#define LOGO_LED_ENABLE 1       // Enable Logo LED functionality
#define LED_LOGO_INDEX 48       // Logo LED starting index (48-76 are logo/bottom LEDs)
#define LOGO_LED_COUNT 29       // Number of logo/bottom LEDs
#define LED_CONNECTION_INDEX 11  // BSPC - connection type indicator
#define LED_CAP_INDEX        12  // ESC  - Caps Lock indicator
#define LED_WIN_L_INDEX      40  // LGUI - Win Lock indicator (Win key lights up when locked)
#define LED_BATT_INDEX       36  // MO2  - Battery status indicator
#define LED_BLE_1_INDEX       1  // Q    - BLE channel 1
#define LED_BLE_2_INDEX       2  // W    - BLE channel 2
#define LED_BLE_3_INDEX       3  // E    - BLE channel 3
#define LED_2P4G_INDEX        4  // R    - 2.4G mode
#define LED_USB_INDEX         0  // TAB  - USB mode (matches original REV.2.5 behavior)