// Copyright 2024 Epomaker (@Epomaker)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define USB_POWER_EN_PIN                    B1 // USB ENABLE pin
#define LED_POWER_EN_PIN                    A5 // LED ENABLE pin
#define HS_BAT_CABLE_PIN                    A7 // USB insertion detection pin
#define HS_LED_BOOSTING_PIN                 D2 // LED BOOSTING

#define BAT_FULL_PIN                        A15
#define BAT_FULL_STATE                      1

#define HS_RGB_INDICATOR_COUNT              99
#define HS_RGB_BAT_COUNT                    1

/* Status Indicator Lamp */

#define HS_RGB_INDEX_CAPS                   47
#define HS_RGB_INDEX_WIN_LOCK               70
#define HS_RGB_BLINK_INDEX_VAI              5
#define HS_RGB_BLINK_INDEX_VAD              6
#define HS_RGB_BLINK_INDEX_SPI              7
#define HS_RGB_BLINK_INDEX_SPD              26

#define HS_RGB_BLINK_INDEX_WIN              46
#define HS_RGB_BLINK_INDEX_MAC              45

/* UART */
#define SERIAL_DRIVER                       SD1
#define SD1_TX_PIN                          C10
#define SD1_RX_PIN                          C11

/* UART for wireless module */
#define UART_RX_PIN C11
#define UART_RX_PAL_MODE 7
#define UART_TX_PIN C10
#define UART_TX_PAL_MODE 7

/* Encoder */
#define ENCODER_MAP_KEY_DELAY               1

/* SPI */
#define SPI_DRIVER                          SPIDQ
#define SPI_SCK_PIN                         B3
#define SPI_MOSI_PIN                        B5
#define SPI_MISO_PIN                        B4

/* Flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
#define WEAR_LEVELING_LOGICAL_SIZE          (WEAR_LEVELING_BACKING_SIZE / 2)

/* RGB Matrix */
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

/* WS2812 */
#define WS2812_SPI_DRIVER  SPIDM2
#define WS2812_SPI_DIVISOR 32

/* Matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 19

/* Matrix pin configuration */
#define MATRIX_ROW_PINS { A0, A1, A2, A3, A4, C13 }
#define MATRIX_COL_PINS { C0, C1, C2, C3, A6, B10, B11, B12, B13, B14, A10, C6, C7, C8, C9, A8, C4, C5, B0 }

/* rgb_record */
#define RGBREC_CHANNEL_NUM 1
#define ENABLE_RGB_MATRIX_RGBR_PLAY
#define EECONFIG_CONFINFO_USE_SIZE (4 + 16)
#define EECONFIG_RGBREC_USE_SIZE   (RGBREC_CHANNEL_NUM * MATRIX_ROWS * MATRIX_COLS * 2)
#define EECONFIG_USER_DATA_SIZE    (EECONFIG_RGBREC_USE_SIZE + EECONFIG_CONFINFO_USE_SIZE)
#define RGBREC_EECONFIG_ADDR       (uint8_t *)(EECONFIG_USER_DATABLOCK)
#define CONFINFO_EECONFIG_ADDR     (uint32_t *)((uint32_t)RGBREC_EECONFIG_ADDR + (uint32_t)EECONFIG_RGBREC_USE_SIZE)
