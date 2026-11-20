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

#pragma once

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define MATRIX_UNSELECT_DRIVE_HIGH
#define CORTEX_ENABLE_WFI_IDLE FALSE

/* Ensure we jump to bootloader if the RESET keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#define DEBOUNCE 5

#ifndef NOP_FUDGE
#    define NOP_FUDGE 0.4
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

#define RGB_MATRIX_LED_COUNT 105
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#define RGB_MATRIX_SLEEP

// BLE configuration for EVO75
#define USER_BLE_ID (0X2090) // EVO75 BLE ID
#define USER_BLE1_NAME "EVO75 BT1"
#define USER_BLE2_NAME "EVO75 BT2"
#define USER_BLE3_NAME "EVO75 BT3"

// LED Index Definitions for keyboard_common library
#define LED_CONNECTION_INDEX 0 // Connection type indicator (BLE/2.4G/USB)
#define LED_CAP_INDEX 44       // provisional EVO75 map
#define LED_WIN_L_INDEX 72     // provisional EVO75 map
#define LED_BATT_INDEX 77      // provisional EVO75 map
#define LED_BLE_1_INDEX 15     // '1' key position
#define LED_BLE_2_INDEX 16     // '2' key position
#define LED_BLE_3_INDEX 17     // '3' key position
#define LED_2P4G_INDEX 18      // '4' key position
#define LED_USB_INDEX 19       // '5' key position

#define LED_LOGO_INDEX 80 // The key LEDs use indices 0-79; logo begins at 80.
#define LOGO_LED_COUNT 25
#define LOGO_LED_ENABLE 1
#define BATTERY_LED_COUNT 10
