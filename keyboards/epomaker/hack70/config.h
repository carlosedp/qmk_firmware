/* Copyright 2026 Epomaker
 * Copyright 2026 Epomaker <https://github.com/Epomaker>
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

/*
 * Feature disable options
 * These options are also useful to firmware size reduction.
 */

#define MATRIX_UNSELECT_DRIVE_HIGH
#define CORTEX_ENABLE_WFI_IDLE FALSE

/* Ensure we jump to bootloader if the RESET keycode was pressed */
#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

#ifndef NOP_FUDGE
#    define NOP_FUDGE 0.4
#endif

// Shared EEPROM sizing + layer count for all Epomaker FS026 boards
#include "fs026_eeprom.h"
#define FEE_PAGE_SIZE (0x200)
#define FEE_PAGE_COUNT (8)
#define FEE_PAGE_BASE_ADDRESS (0x1F000)
#define FEE_MCU_FLASH_SIZE (0x1000)
#define EECONFIG_USER_DATA_SIZE 4
#define EECONFIG_KB_DATA_SIZE 1
#define TRANSIENT_EEPROM_SIZE 4096

#define RGB_MATRIX_LED_COUNT 73 // 70 keys + 3 logo LEDs
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_SLEEP

// One-shot Shift: tap three times to lock Shift (vendor firmware V0105)
#define ONESHOT_TAP_TOGGLE 3

// BLE configuration for Hack70
#define USER_BLE_ID (0X206A) // Hack70 BLE ID (matches vendor firmware)
#define USER_BLE1_NAME "Hack70-1"
#define USER_BLE2_NAME "Hack70-2"
#define USER_BLE3_NAME "Hack70-3"

// Logo LED
#define LOGO_LED_ENABLE 1 // Enable Logo LED functionality
#define LED_LOGO_INDEX 70 // Logo LED starting index (after the 70 keys)
#define LOGO_LED_COUNT 3  // Number of logo LEDs

// Battery indicator: 10 LEDs over the number row (1-0)
#define BATTERY_LED_COUNT 10

// LED Index Definitions for keyboard_common library
#define LED_CONNECTION_INDEX 70 // Connection type indicator (first logo LED)
#define LED_CAP_INDEX 29        // Caps Lock indicator (Caps key position)
#define LED_WIN_L_INDEX 60      // Win Lock indicator (Left Win/GUI key position)
#define LED_BATT_INDEX 59       // Battery status indicator (Fn key position)
#define LED_BLE_1_INDEX 15      // 'Q' key position for BLE 1
#define LED_BLE_2_INDEX 16      // 'W' key position for BLE 2
#define LED_BLE_3_INDEX 17      // 'E' key position for BLE 3
#define LED_2P4G_INDEX 18       // 'R' key position for 2.4G
#define LED_USB_INDEX 19        // 'T' key position for USB
