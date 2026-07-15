// Copyright 2024 Su (@isuua)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "wireless.h"
#include "util.h"

#ifndef LPWR_UART_WAKEUP_DISABLE
#    include "uart.h"
#endif

#define MATRIX_SPLIT_IS_MASTER()       true

#if defined(MATRIX_ROW_PINS_RIGHT) && defined(MATRIX_COL_PINS_RIGHT)
    #define LP_MATRIX_ROWS                 MATRIX_ROWS/2
    #    undef MATRIX_SPLIT_IS_MASTER
    #    define MATRIX_SPLIT_IS_MASTER() is_keyboard_master()
#else
    #define LP_MATRIX_ROWS                 MATRIX_ROWS
#endif

#define LP_MATRIX_COLS                 MATRIX_COLS

static ioline_t row_pins[LP_MATRIX_ROWS] = MATRIX_ROW_PINS;
static ioline_t col_pins[LP_MATRIX_COLS] = MATRIX_COL_PINS;

#if defined(MATRIX_ROW_PINS_RIGHT) && defined(MATRIX_COL_PINS_RIGHT)
static ioline_t row_pins_r[LP_MATRIX_ROWS] = MATRIX_ROW_PINS_RIGHT;
static ioline_t col_pins_r[LP_MATRIX_COLS] = MATRIX_COL_PINS_RIGHT;
#endif

#if PAL_USE_CALLBACKS != TRUE
#    error PAL_USE_CALLBACKS must be set to TRUE!
#endif

#if !((DIODE_DIRECTION == ROW2COL) || (DIODE_DIRECTION == COL2ROW))
#    error DIODE_DIRECTION must be one of COL2ROW or ROW2COL!
#endif

// clang-format off
static const uint32_t pre_lp_code[] = {553863175u, 554459777u, 1208378049u, 4026624001u, 688390415u, 554227969u, 3204472833u, 1198571264u, 1073807360u, 1073808388u};
#define PRE_LP() ((void (*)(void))((unsigned int)(pre_lp_code) | 0x01))()

static const uint32_t post_lp_code[] = {553863177u, 554459777u, 1208509121u, 51443856u, 4026550535u, 1745485839u, 3489677954u, 536895496u, 673389632u, 1198578684u, 1073807360u, 536866816u, 1073808388u};
#define POST_LP() ((void (*)(void))((unsigned int)(post_lp_code) | 0x01))()
// clang-format on

extern void __early_init(void);
extern void matrix_init_pins(void);

void palcallback_cb(uint8_t line) __attribute__((weak));
void palcallback_cb(uint8_t line) {}

void palcallback(void *arg) {
    uint8_t line = (uint32_t)arg & 0xFF;

    switch (line) {
#ifndef LPWR_UART_WAKEUP_DISABLE
        case PAL_PAD(UART_RX_PIN): {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_UART);
        } break;
#endif
        case(18):{
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_USB);
        }break;
        default: {
            lpwr_set_sleep_wakeupcd(LPWR_WAKEUP_MATRIX);
        } break;
    }

    palcallback_cb(line);

    irqDeinit();
    EXTI->PR = 0xFFFFFFFF;
}

void pal_events_init(void) {

    for (uint8_t i = 0; i < 16; i++) {
        _pal_events[i].cb  = palcallback;
        _pal_events[i].arg = (void *)(uint32_t)i;
    }
}

void lpwr_exti_init_hook(void) __attribute__((weak));
void lpwr_exti_init_hook(void) {}

void lpwr_exti_init(void) {

    pal_events_init();

#if DIODE_DIRECTION == ROW2COL
    if (MATRIX_SPLIT_IS_MASTER()){
    for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); i++) {
        if (col_pins[i] != NO_PIN) {
            gpio_set_pin_output_open_drain(col_pins[i]);
            gpio_write_pin_low(col_pins[i]);
        }
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(row_pins); i++) {
        if (row_pins[i] != NO_PIN) {
            gpio_set_pin_input_high(row_pins[i]);
            waitInputPinDelay();
            palEnableLineEvent(row_pins[i], PAL_EVENT_MODE_FALLING_EDGE);
        }
    }
    } else {
        for (uint8_t i = 0; i < ARRAY_SIZE(col_pins_r); i++) {
            if (col_pins_r[i] != NO_PIN) {
                gpio_set_pin_output_open_drain(col_pins_r[i]);
                gpio_write_pin_low(col_pins_r[i]);
            }
        }

        for (uint8_t i = 0; i < ARRAY_SIZE(row_pins_r); i++) {
            if (row_pins_r[i] != NO_PIN) {
                gpio_set_pin_input_high(row_pins_r[i]);
                waitInputPinDelay();
                palEnableLineEvent(row_pins_r[i], PAL_EVENT_MODE_FALLING_EDGE);
            }
        }
    }
#elif DIODE_DIRECTION == COL2ROW
    for (uint8_t i = 0; i < ARRAY_SIZE(row_pins); i++) {
        if (row_pins[i] != NO_PIN) {
            gpio_set_pin_output_open_drain(row_pins[i]);
            gpio_write_pin_low(row_pins[i]);
        }
    }

    for (uint8_t i = 0; i < ARRAY_SIZE(col_pins); i++) {
        if (col_pins[i] != NO_PIN) {
            gpio_set_pin_input_high(col_pins[i]);
            waitInputPinDelay();
            palEnableLineEvent(col_pins[i], PAL_EVENT_MODE_FALLING_EDGE);
        }
    }
#endif

// Disabled UART_RX_PIN wake - prevents wireless module communication from waking device
// This fixes the issue where the 30-minute deep sleep command wakes the device
// #ifndef LPWR_UART_WAKEUP_DISABLE
//     extern bool lower_sleep;
//     if (!lower_sleep){
//     setPinInput(UART_RX_PIN);
//     waitInputPinDelay();
//     palEnableLineEvent(UART_RX_PIN, PAL_EVENT_MODE_BOTH_EDGES);
//     }
// #endif

#ifdef SPLIT_KEYBOARD
    gpio_set_pin_input(SERIAL_USART_RX_PIN);
    waitInputPinDelay();
    palEnableLineEvent(SERIAL_USART_RX_PIN, PAL_EVENT_MODE_BOTH_EDGES);
#endif

    palEnableLineEvent(A12,PAL_EVENT_MODE_RISING_EDGE);
    nvicEnableVector(USBP_WKUP_IRQn,6);
    lpwr_exti_init_hook();

    /* IRQ subsystem initialization.*/
    irqInit();
}

void lpwr_clock_enable_user(void) __attribute__((weak));
void lpwr_clock_enable_user(void) {}

void lpwr_clock_enable(void) {

    __early_init();

    PWR->ANAKEY1 = 0x03;
    PWR->ANAKEY2 = 0x0C;
    ANCTL->USBPCR &= ~(ANCTL_USBPCR_DMSTEN | ANCTL_USBPCR_DPSTEN);
    /* Locks write to ANCTL registers */
    PWR->ANAKEY1 = 0x00;
    PWR->ANAKEY2 = 0x00;

    /* Enable SFM clock */
    RCC->AHBENR1 |= RCC_AHBENR1_CRCSFMEN;

    /* Enable USB peripheral clock */
    RCC->AHBENR1 |= RCC_AHBENR1_USBEN;

    /* Configure USB FIFO clock source */
    RCC->USBFIFOCLKSRC = RCC_USBFIFOCLKSRC_USBCLK;

    /* Enable USB FIFO clock */
    RCC->USBFIFOCLKENR = RCC_USBFIFOCLKENR_CLKEN;

    /* Configure and enable USBCLK */
#        if (WB32_USBPRE == WB32_USBPRE_DIV1P5)
    RCC->USBCLKENR = RCC_USBCLKENR_CLKEN;
    RCC->USBPRE    = RCC_USBPRE_SRCEN;
    RCC->USBPRE |= RCC_USBPRE_RATIO_1_5;
    RCC->USBPRE |= RCC_USBPRE_DIVEN;
#        elif (WB32_USBPRE == WB32_USBPRE_DIV1)
    RCC->USBCLKENR = RCC_USBCLKENR_CLKEN;
    RCC->USBPRE    = RCC_USBPRE_SRCEN;
    RCC->USBPRE |= 0x00;
#        elif (WB32_USBPRE == WB32_USBPRE_DIV2)
    RCC->USBCLKENR = RCC_USBCLKENR_CLKEN;
    RCC->USBPRE    = RCC_USBPRE_SRCEN;
    RCC->USBPRE |= RCC_USBPRE_RATIO_2;
    RCC->USBPRE |= RCC_USBPRE_DIVEN;
#        elif (WB32_USBPRE == WB32_USBPRE_DIV3)
    RCC->USBCLKENR = RCC_USBCLKENR_CLKEN;
    RCC->USBPRE    = RCC_USBPRE_SRCEN;
    RCC->USBPRE |= RCC_USBPRE_RATIO_3;
    RCC->USBPRE |= RCC_USBPRE_DIVEN;
#endif
    rccEnableEXTI();

#if WB32_SERIAL_USE_UART1
    rccEnableUART1();
#endif
#if WB32_SERIAL_USE_UART2
    rccEnableUART2();
#endif
#if WB32_SERIAL_USE_UART3
    rccEnableUART3();
#endif
#if WB32_SPI_USE_QSPI
    rccEnableQSPI();
#endif
#if WB32_SPI_USE_SPIM2
    rccEnableSPIM2();
#endif
#if WB32_I2C_USE_I2C1
    rccEnableI2C1();
#endif
#if WB32_I2C_USE_I2C2
    rccEnableI2C2();
#endif

#if WB32_GPT_USE_TIM1 || WB32_ICU_USE_TIM1 || WB32_PWM_USE_TIM1
    rccEnableTIM1();
#endif
#if WB32_ST_USE_TIM2 || WB32_GPT_USE_TIM2 || WB32_ICU_USE_TIM2 || WB32_PWM_USE_TIM2
    rccEnableTIM2();
#endif
#if WB32_ST_USE_TIM3 || WB32_GPT_USE_TIM3 || WB32_ICU_USE_TIM3 || WB32_PWM_USE_TIM3
    rccEnableTIM3();
#endif
#if WB32_ST_USE_TIM4 || WB32_GPT_USE_TIM4 || WB32_ICU_USE_TIM4 || WB32_PWM_USE_TIM4
    rccEnableTIM4();
#endif

#ifndef LPWR_UART_WAKEUP_DISABLE
    palSetLineMode(UART_RX_PIN, PAL_MODE_ALTERNATE(UART_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
#endif

#ifdef SPLIT_KEYBOARD
    palSetLineMode(SERIAL_USART_TX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_TX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
    palSetLineMode(SERIAL_USART_RX_PIN, PAL_MODE_ALTERNATE(SERIAL_USART_RX_PAL_MODE) | PAL_OUTPUT_TYPE_PUSHPULL | PAL_OUTPUT_SPEED_HIGHEST);
#endif

    lpwr_clock_enable_user();
}

void wb32_stop_mode(void) {

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;

    /* Prevent the chip from being unable to enter stop mode due to pending interrupts */
#if 1
    EXTI->PR = 0x7FFFF;
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 32; j++) {
             /*
             * Recommended by AI to prevent instant/false wakeups
             */
            if (NVIC->ISPR[i] & (0x01UL << j)) {
                NVIC->ICPR[i] = (0x01UL << j);
            }
        }
    }
    SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk; // Clear Systick IRQ Pending
#endif

    /* Clear all bits except DBP and FCLKSD bit */
    PWR->CR0 &= 0x09U;

    // STOP LP4 MODE S32KON
    PWR->CR0 |= 0x3B004U;
    PWR->CFGR = 0x3B3;

    PRE_LP();

    /* Set SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

    /* Request Wait For Interrupt */
    __WFI();

    POST_LP();

    /* Clear SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (~SCB_SCR_SLEEPDEEP_Msk);

    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
}

void mcu_stop_mode(void) {

    wb32_stop_mode();
}
