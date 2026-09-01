/* Copyright 2023 Yiancar-Designs
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "rdmctmzt_common.h"


/* ============================================================
 * Automatic RGB configuration
 * ============================================================ */

/*
 * 153 / 255 = 60%.
 */
#define TH85_ACTIVE_RGB_SPEED 153

/*
 * One second without keyboard activity.
 */
#define TH85_IDLE_DELAY_MS 1000


/* ============================================================
 * Logo / side reaction
 * ============================================================ */

/*
 * Duration of the visual reaction after a key press.
 */
#define TH85_REACTION_MS           180


/* ============================================================
 * State
 * ============================================================ */

static uint32_t th85_last_activity = 0;
static uint32_t th85_last_keypress = 0;

static bool th85_rgb_idle = false;
static bool th85_has_activity = false;


/*
 * Timestamp of the last synthetic "keypress" this file injected into
 * G (matrix 3,5) to spawn a new splash ring while idle. See
 * th85_spawn_idle_splash() below.
 */
static uint32_t th85_last_splash = 0;


/* ============================================================
 * Helper: normal typing RGB
 * ============================================================ */

static void th85_rgb_set_active(void) {

    th85_rgb_idle = false;

    rgb_matrix_mode_noeeprom(
        RGB_MATRIX_SOLID_MULTISPLASH
    );

    rgb_matrix_set_speed_noeeprom(
        TH85_ACTIVE_RGB_SPEED
    );
}


/* ============================================================
 * Initialization
 * ============================================================ */

void keyboard_post_init_user(void) {

    th85_last_activity = timer_read32();
    th85_last_keypress = timer_read32();

    th85_rgb_idle = false;
    th85_has_activity = false;

    th85_rgb_set_active();
}


/* ============================================================
 * Keyboard activity
 * ============================================================ */

bool process_record_user(
    uint16_t keycode,
    keyrecord_t *record
) {

    /*
     * Any keyboard event means the user is active.
     *
     * Updating on both press and release means the idle timer
     * does not start while a key is still being held.
     */
    th85_last_activity = timer_read32();

    /*
     * Only key presses trigger the visual reaction.
     */
    if (record->event.pressed) {

        th85_last_keypress = timer_read32();
        th85_has_activity = true;

        /*
         * Stop the idle ripple immediately.
         */
        if (th85_rgb_idle) {
            th85_rgb_set_active();
        }
    }

    return true;
}


/* ============================================================
 * Idle detector
 * ============================================================ */

/*
 * Spawns a new splash ring at G (matrix row 3, col 5 - see th85.c's
 * matrix/g_led_config, this is the physical middle of the board)
 * by injecting a synthetic "key release" the exact same way a real
 * keystroke does (rgb_matrix_handle_key_event() is what
 * quantum/action.c calls on every real key event). This reuses QMK's
 * own stock reactive-splash pipeline (last_hit_buffer,
 * effect_runner_reactive_splash.h) instead of hand-rolled distance
 * math against g_led_config - the previous custom ripple never
 * correctly reached the bottom two rows despite two different
 * distance formulas, so this sidesteps that entirely by using the
 * exact code path real keypresses already use successfully.
 *
 * Whether this call fires as a "press" or "release" is decided by
 * RGB_MATRIX_KEYRELEASES/RGB_MATRIX_KEYPRESSES in config.h - both are
 * defined there, and rgb_matrix_handle_key_event() checks
 * RGB_MATRIX_KEYRELEASES first, so it only records a hit when
 * pressed=false.
 */
static void th85_spawn_idle_splash(void) {
    rgb_matrix_handle_key_event(3, 5, false);
}

#define TH85_IDLE_SPLASH_INTERVAL_MS 1500

void housekeeping_task_user(void) {

    if (!rgb_matrix_is_enabled()) {
        return;
    }

    if (th85_rgb_idle) {
        if (timer_elapsed32(th85_last_splash) >= TH85_IDLE_SPLASH_INTERVAL_MS) {
            th85_last_splash = timer_read32();
            th85_spawn_idle_splash();
        }
        return;
    }

    if (!th85_has_activity) {
        return;
    }

    /*
     * One second after the last keyboard event.
     */
    if (
        timer_elapsed32(th85_last_activity) >=
            TH85_IDLE_DELAY_MS
    ) {

        th85_rgb_idle = true;
        th85_last_splash = timer_read32();

        rgb_matrix_mode_noeeprom(
            RGB_MATRIX_SOLID_SPLASH
        );

        th85_spawn_idle_splash();
    }
}



/* ============================================================
 * RGB indicator callback
 * ============================================================
 *
 * The logo/side sync used to happen here, but this runs too early
 * in the main loop (see the comment on housekeeping_task_user()
 * above, where it now lives) to actually be visible. Nothing else
 * needs this callback right now.
 * ============================================================ */

bool rgb_matrix_indicators_advanced_user(
    uint8_t led_min,
    uint8_t led_max
) {
    (void)led_min;
    (void)led_max;

    return false;
}


/* ============================================================
 * Keymaps
 * ============================================================ */

// clang-format off

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_F1,      KC_F2,    KC_F3,    KC_F4,    KC_F5,        KC_F6,     KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_DEL,   KC_PSCR,  KC_PAUS, KC_MUTE,
        KC_GRV,   KC_1,       KC_2,     KC_3,     KC_4,     KC_5,         KC_6,      KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,       KC_W,     KC_E,     KC_R,     KC_T,         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,       KC_S,     KC_D,     KC_F,     KC_G,         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,              KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LGUI,    KC_LALT,                      KC_SPC,                                      KC_RALT,  MO(2),    KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [1] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_BRID,    KC_BRIU,  KC_MCTL,  KC_LPAD,  LGUI(KC_SPC), LSG(KC_4), KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_DEL,   KC_PSCR,  KC_PAUS, KC_MUTE,
        KC_GRV,   KC_1,       KC_2,     KC_3,     KC_4,     KC_5,         KC_6,     KC_7,     KC_8,      KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_HOME,  KC_PGUP,
        KC_TAB,   KC_Q,       KC_W,     KC_E,     KC_R,     KC_T,         KC_Y,     KC_U,     KC_I,      KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_END,   KC_PGDN,
        KC_CAPS,  KC_A,       KC_S,     KC_D,     KC_F,     KC_G,         KC_H,      KC_J,     KC_K,      KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        KC_LSFT,              KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,
        KC_LCTL,  KC_LALT,    KC_LGUI,                      KC_SPC,                                      KC_RGUI,  MO(3),    KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [2] = LAYOUT_tkl_ansi(
        KC_ESC,   LGUI(KC_E), KC_WHOM,  KC_CALC,  KC_MAIL,  KC_MSEL,      KC_MSTP,   KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  SIDE_MOD, KC_PSCR,  KC_PAUS, KC_MUTE,
        KC_GRV,   KC_1,       KC_2,     KC_3,     KC_4,     KC_5,         KC_6,      KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   RM_NEXT,  RGB_RTOG, RM_SATU,
        KC_TAB,   MD_BLE1,    MD_BLE2,  MD_BLE3,  MD_24G,   KC_T,         KC_Y,     KC_U,     KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_LBRC,  RM_HUED,  RM_HUEU,  LOGO_MOD, RM_SATD,
        KC_CAPS,  KC_A,       KC_S,     KC_D,     KC_F,     KC_G,         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            QK_BAT,
        KC_LSFT,              KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,            RM_VALU,
        KC_LCTL,  QK_WLO,     KC_LALT,                      EE_CLR,                                      KC_RALT,  KC_NO,    KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT
    ),

    [3] = LAYOUT_tkl_ansi(
        KC_ESC,   KC_F1,      KC_F2,    KC_F3,    KC_F4,    KC_F5,        KC_F6,     KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   SIDE_MOD, KC_PSCR,  KC_PAUS, KC_MUTE,
        KC_GRV,   KC_1,       KC_2,     KC_3,     KC_4,     KC_5,         KC_6,      KC_7,     KC_8,      KC_9,     KC_0,     KC_MINS,  KC_EQL,   RM_NEXT,  RGB_RTOG, RM_SATU,
        KC_TAB,   MD_BLE1,    MD_BLE2,  MD_BLE3,  MD_24G,   KC_T,         KC_Y,     KC_U,     KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_LBRC,  RM_HUED,  RM_HUEU,  LOGO_MOD, RM_SATD,
        KC_CAPS,  KC_A,       KC_S,     KC_D,     KC_F,     KC_G,         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            QK_BAT,
        KC_LSFT,              KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,         KC_N,     KC_M,     KC_COMM, KC_DOT,   KC_SLSH,  KC_RSFT,            RM_VALU,
        KC_LCTL,  KC_LALT,    KC_LGUI,                       EE_CLR,                                      KC_RGUI,  KC_NO,    KC_RCTL,            RM_SPDD,  RM_VALD,  RM_SPDU
    )
};

// clang-format on


#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {

    [0] = {
        ENCODER_CCW_CW(
            KC_AUDIO_VOL_DOWN,
            KC_AUDIO_VOL_UP
        )
    },

    [1] = {
        ENCODER_CCW_CW(
            KC_AUDIO_VOL_DOWN,
            KC_AUDIO_VOL_UP
        )
    },

    [2] = {
        ENCODER_CCW_CW(
            RM_SATD,
            RM_SATU
        )
    },

    [3] = {
        ENCODER_CCW_CW(
            RM_SPDD,
            RM_SPDU
        )
    }
};

#endif