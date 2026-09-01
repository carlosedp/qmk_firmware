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
 * Ripple configuration
 *
 * TH85_RIPPLE_* geometry/timing constants now live in config.h
 * (single source of truth shared with rgb_matrix_user.inc).
 * ============================================================ */


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
 * These are intentionally global because rgb_matrix_user.inc
 * is compiled as part of rgb_matrix.c and needs the current
 * ripple radius.
 */
uint16_t th85_ripple_radius = 0;
uint32_t th85_ripple_timer = 0;

/*
 * Forward declarations: defined further down, but needed by
 * housekeeping_task_user() which now calls them (see the comment
 * there for why they moved out of rgb_matrix_indicators_advanced_user).
 */
static void th85_zone_reactive_flash(void);
static void th85_zone_idle_ripple(void);


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

    th85_ripple_radius = 0;
    th85_ripple_timer = g_rgb_timer;

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

            th85_ripple_radius = 0;

            th85_rgb_set_active();
        }
    }

    return true;
}


/* ============================================================
 * Idle detector
 * ============================================================ */

void housekeeping_task_user(void) {

    /*
     * Sync the logo/side zones here, not from
     * rgb_matrix_indicators_advanced_user(). That callback runs from
     * rgb_matrix_task(), which the main loop calls *before*
     * housekeeping_task() -> housekeeping_task_kb() ->
     * Logo_Led_Update()/Side_Led_Update() (see kb_housekeeping_task()
     * in lib/rdmctmzt_common/keyboard_common.c, which runs
     * unconditionally every tick). Setting the ripple/reactive colors
     * before that zone update meant it was immediately painted over
     * in the same tick and never actually visible. Running it here,
     * after housekeeping_task_kb() in the same tick, makes it win.
     */
#if LOGO_LED_ENABLE || SIDE_LED_ENABLE
    if (th85_rgb_idle) {
        th85_zone_idle_ripple();
    } else {
        th85_zone_reactive_flash();
    }
#endif

    if (!rgb_matrix_is_enabled()) {
        return;
    }

    if (!th85_has_activity) {
        return;
    }

    /*
     * One second after the last keyboard event.
     */
    if (
        !th85_rgb_idle &&
        timer_elapsed32(th85_last_activity) >=
            TH85_IDLE_DELAY_MS
    ) {

        th85_rgb_idle = true;

        th85_ripple_radius = 0;
        th85_ripple_timer = g_rgb_timer;

        rgb_matrix_mode_noeeprom(
            RGB_MATRIX_CUSTOM_IDLE_RIPPLE
        );
    }
}


/* ============================================================
 * Helper: set one RGB zone
 * ============================================================ */

static void th85_set_zone_color(
    uint8_t start,
    uint8_t count,
    uint8_t r,
    uint8_t g,
    uint8_t b
) {

    for (uint8_t i = 0; i < count; i++) {

        rgb_matrix_driver_set_color(
            start + i,
            r,
            g,
            b
        );
    }
}


/* ============================================================
 * Helper: convert HSV to RGB with brightness scaling
 * ============================================================ */

static void th85_set_zone_hsv(
    uint8_t start,
    uint8_t count,
    uint8_t hue,
    uint8_t saturation,
    uint8_t brightness
) {

    hsv_t hsv = {
        .h = hue,
        .s = saturation,
        .v = brightness
    };

    rgb_t rgb =
        hsv_to_rgb(hsv);

    th85_set_zone_color(
        start,
        count,
        rgb.r,
        rgb.g,
        rgb.b
    );
}


/* ============================================================
 * Zone reaction while typing
 * ============================================================ */

static void th85_zone_reactive_flash(void) {

    uint32_t elapsed =
        timer_elapsed32(th85_last_keypress);


    if (elapsed >= TH85_REACTION_MS) {
        return;
    }


    /*
     * Brightness fades from maximum to zero.
     */
    uint8_t fade =
        255 -
        (
            (elapsed * 255) /
            TH85_REACTION_MS
        );


#if LOGO_LED_ENABLE

    if (Keyboard_Info.Logo_On_Off) {

        uint8_t brightness =
            (
                (uint16_t)
                Keyboard_Info.Logo_Brightness *
                fade
            ) / 255;

        th85_set_zone_hsv(
            LED_LOGO_INDEX,
            LOGO_LED_COUNT,
            Keyboard_Info.Logo_Hue,
            Keyboard_Info.Logo_Saturation,
            brightness
        );
    }

#endif


#if SIDE_LED_ENABLE

    if (Keyboard_Info.Side_On_Off) {

        uint8_t brightness =
            (
                (uint16_t)
                Keyboard_Info.Side_Brightness *
                fade
            ) / 255;

        th85_set_zone_hsv(
            LED_SIDE_INDEX,
            SIDE_LED_COUNT,
            Keyboard_Info.Side_Hue,
            Keyboard_Info.Side_Saturation,
            brightness
        );
    }

#endif
}


/* ============================================================
 * Zone ripple while idle
 * ============================================================ */

static uint8_t th85_zone_ring_brightness(
    uint16_t distance,
    uint16_t radius
) {

    int16_t difference =
        (int16_t)distance -
        (int16_t)radius;

    if (difference < 0) {
        difference = -difference;
    }

    if (difference >= TH85_RIPPLE_WIDTH) {
        return 0;
    }

    return (
        uint8_t
    )(
        255 -
        (
            ((uint16_t)difference * 255) /
            TH85_RIPPLE_WIDTH
        )
    );
}


/*
 * Draw logo and side strip so they remain synchronized with
 * the exact same two ripple radii as the keyboard.
 */
static void th85_zone_idle_ripple(void) {


    /*
     * --------------------------------------------------------
     * LOGO
     * --------------------------------------------------------
     *
     * The logo is physically around the center of the board,
     * so it responds when a wave passes the center region.
     */
#if LOGO_LED_ENABLE

    uint8_t logo_brightness_1 =
        th85_zone_ring_brightness(
            18,
            th85_ripple_radius
        );


    uint16_t logo_radius_2 =
        th85_ripple_radius +
        TH85_RIPPLE_SEPARATION;


    if (logo_radius_2 > TH85_RIPPLE_MAX_RADIUS) {
        logo_radius_2 -= TH85_RIPPLE_MAX_RADIUS;
    }


    uint8_t logo_brightness_2 =
        th85_zone_ring_brightness(
            18,
            logo_radius_2
        );


    uint8_t logo_brightness =
        logo_brightness_1 >
            logo_brightness_2
            ? logo_brightness_1
            : logo_brightness_2;


    if (!Keyboard_Info.Logo_On_Off) {

        th85_set_zone_color(
            LED_LOGO_INDEX,
            LOGO_LED_COUNT,
            0,
            0,
            0
        );

    } else {

        uint8_t brightness =
            (
                (uint16_t)
                Keyboard_Info.Logo_Brightness *
                logo_brightness
            ) / 255;

        th85_set_zone_hsv(
            LED_LOGO_INDEX,
            LOGO_LED_COUNT,
            Keyboard_Info.Logo_Hue,
            Keyboard_Info.Logo_Saturation,
            brightness
        );
    }

#endif


    /*
     * --------------------------------------------------------
     * SIDE STRIP
     * --------------------------------------------------------
     *
     * The 38 LEDs are treated as two mirrored sides:
     *
     *   0..18   = left side
     *   19..37  = right side
     *
     * The center LEDs react first and the outer LEDs later,
     * producing a visual echo of the keyboard ripple.
     */
#if SIDE_LED_ENABLE

    if (!Keyboard_Info.Side_On_Off) {

        th85_set_zone_color(
            LED_SIDE_INDEX,
            SIDE_LED_COUNT,
            0,
            0,
            0
        );

    } else {

        hsv_t hsv = {
            .h = Keyboard_Info.Side_Hue,
            .s = Keyboard_Info.Side_Saturation,
            .v = Keyboard_Info.Side_Brightness
        };


        for (uint8_t i = 0; i < SIDE_LED_COUNT; i++) {

            uint8_t local_position;

            if (i < 19) {
                local_position = i;
            } else {
                local_position = i - 19;
            }


            /*
             * Center of each side = position 9.
             *
             * Convert this into a distance roughly matching
             * the keyboard coordinate system.
             */
            uint16_t side_distance =
                18 +
                (
                    (
                        local_position > 9
                            ? local_position - 9
                            : 9 - local_position
                    ) * 5
                );


            uint8_t brightness_1 =
                th85_zone_ring_brightness(
                    side_distance,
                    th85_ripple_radius
                );


            uint16_t radius_2 =
                th85_ripple_radius +
                TH85_RIPPLE_SEPARATION;


            if (radius_2 > TH85_RIPPLE_MAX_RADIUS) {
                radius_2 -= TH85_RIPPLE_MAX_RADIUS;
            }


            uint8_t brightness_2 =
                th85_zone_ring_brightness(
                    side_distance,
                    radius_2
                );


            uint8_t brightness =
                brightness_1 >
                    brightness_2
                    ? brightness_1
                    : brightness_2;


            hsv.v =
                (
                    (uint16_t)
                    Keyboard_Info.Side_Brightness *
                    brightness
                ) / 255;


            rgb_t rgb =
                hsv_to_rgb(hsv);


            rgb_matrix_driver_set_color(
                LED_SIDE_INDEX + i,
                rgb.r,
                rgb.g,
                rgb.b
            );
        }
    }

#endif
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