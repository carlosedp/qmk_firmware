// Copyright 2024 Epomaker (@Epomaker)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define USB_POWER_EN_PIN                    B1 // USB ENABLE pin
#define LED_POWER_EN_PIN                    A5 // LED ENABLE pin
#define LED_POWER_EN2_PIN                    A8 // LED ENABLE pin
#define HS_BAT_CABLE_PIN                    A7 // USB insertion detection pin

#define BAT_FULL_PIN                        A15
#define BAT_FULL_STATE                      1

#define MATRIX_ROWS                         10
#define MATRIX_COLS                         9

#define HS_RGB_INDICATOR_COUNT              99
#define HS_RGB_BAT_COUNT                    1

#define MD_BT1_NAME                         "Split70-1"
#define MD_BT2_NAME                         "Split70-2"
#define MD_BT3_NAME                         "Split70-3"
#define MD_DONGLE_PRODUCT                   "Epomaker Split70"

/* Device Connection RGB Indicator Light Index And Color */
#define HS_RGB_BLINK_INDEX_BT1              14
#define HS_RGB_BLINK_INDEX_BT2              13
#define HS_RGB_BLINK_INDEX_BT3              12
#define HS_RGB_BLINK_INDEX_2G4              11

#define HS_LBACK_COLOR_BT1                  RGB_BLUE
#define HS_LBACK_COLOR_BT2                  RGB_BLUE
#define HS_LBACK_COLOR_BT3                  RGB_BLUE
#define HS_LBACK_COLOR_2G4                  RGB_GREEN
#define HS_LBACK_COLOR_USB                  RGB_WHITE

#define HS_PAIR_COLOR_BT1                   RGB_BLUE
#define HS_PAIR_COLOR_BT2                   RGB_BLUE
#define HS_PAIR_COLOR_BT3                   RGB_BLUE
#define HS_PAIR_COLOR_2G4                   RGB_GREEN
#define HS_PAIR_COLOR_USB                   RGB_WHITE

/* Battery */
#define BATTERY_CAPACITY_LOW                15
#define BATTERY_CAPACITY_STOP               0
#define RGB_MATRIX_BAT_INDEX_MAP            {5, 6, 7, 8, 9, 39, 40, 41, 42, 43}

/* Status Indicator Lamp */
#define HS_MATRIX_BLINK_INDEX_BAT           33
#define HS_RGB_INDEX_CAPS                   18
#define HS_RGB_INDEX_WIN_LOCK               73

#define HS_RGB_BLINK_INDEX_WIN              19
#define HS_RGB_BLINK_INDEX_MAC              20

/* UART */
#define SERIAL_DRIVER                       SD3
#define SD1_TX_PIN                          C10
#define SD1_RX_PIN                          C11
#define UART_DRIVER                         SD3
#define UART_TX_PIN                         C10
#define UART_RX_PIN                         C11
#define UART_TX_PAL_MODE                    7
#define UART_RX_PAL_MODE                    7

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

/*serial usart config for split communication*/
#define SERIAL_USART_DRIVER SD1
#define SERIAL_USART_TX_PIN A9
#define SERIAL_USART_RX_PIN A10
#define SERIAL_USART_TX_PAL_MODE 7
#define SERIAL_USART_RX_PAL_MODE 7
#define SERIAL_USART_CONFIG {115200, 3, 0, 0, 0};
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_MMS
#define SPLIT_HAND_PIN B9
/* rgb_record */
#define ENABLE_RGB_MATRIX_RGBR_PLAY
#define RGBREC_CHANNEL_NUM         4
#define EECONFIG_CONFINFO_USE_SIZE (4 + 16)
#define EECONFIG_RGBREC_USE_SIZE   (RGBREC_CHANNEL_NUM * MATRIX_ROWS * MATRIX_COLS * 2)
#define EECONFIG_USER_DATA_SIZE    (EECONFIG_RGBREC_USE_SIZE + EECONFIG_CONFINFO_USE_SIZE)
#define RGBREC_EECONFIG_OFFSET     0
#define CONFINFO_EECONFIG_OFFSET   (RGBREC_EECONFIG_OFFSET + (uint32_t)EECONFIG_RGBREC_USE_SIZE)
