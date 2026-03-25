/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
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

/* Define less important options */

/*
 * Feature disable options
 * These options are also useful to firmware size reduction.
 */

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

#define RGB_MATRIX_LED_COUNT 130
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 180
#define RGB_MATRIX_SLEEP
#define RGB_MATRIX_BACKLIGHT_COUNT 84

// BLE configuration for TH85
#define USER_BLE_ID (0X00A5) // TH85 BLE ID
#define USER_BLE1_NAME "TH85-1"
#define USER_BLE2_NAME "TH85-2"
#define USER_BLE3_NAME "TH85-3"

// Logo LED
#define LOGO_LED_ENABLE 1 // Enable Logo LED functionality
#define LED_LOGO_INDEX 84 // Logo LED starting index
#define LOGO_LED_COUNT 8  // Number of logo LEDs

// Side LED
#define SIDE_LED_ENABLE 1 // Enable Side LED functionality
#define LED_SIDE_INDEX 92 // Side LED starting index (after 84 key + 8 logo)
#define SIDE_LED_COUNT 38 // Number of side LEDs

// LED Index Definitions for keyboard_common library
#define LED_CONNECTION_INDEX 84 // Connection type indicator (underglow LED)
#define LED_CAP_INDEX 48        // Caps Lock indicator (Caps key position)
#define LED_WIN_L_INDEX 75      // Win Lock indicator (Left Win/GUI key position)
#define LED_BATT_INDEX 85       // Battery status indicator (underglow LED)
#define LED_BLE_1_INDEX 33      // 'Q' key position for BLE 1
#define LED_BLE_2_INDEX 34      // 'W' key position for BLE 2
#define LED_BLE_3_INDEX 35      // 'E' key position for BLE 3
#define LED_2P4G_INDEX 36       // 'R' key position for 2.4G
#define LED_USB_INDEX 37        // 'T' key position for USB
