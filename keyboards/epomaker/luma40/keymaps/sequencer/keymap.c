// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rdmctmzt_common.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_tkl_ansi(
        KC_TAB,  KC_Q,    KC_W,      KC_E,     KC_R,       KC_T,      KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,     KC_BSPC,
        KC_CAPS, KC_A,    KC_S,      KC_D,     KC_F,       KC_G,      KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_ENT,
        KC_LSFT, KC_Z,    KC_X,      KC_C,     KC_V,       KC_B,      KC_N,     KC_M,    KC_COMM, KC_DOT,   KC_UP ,   KC_QUOT,
        MO(2),   KC_LCTL, KC_GRV,    KC_LGUI,  KC_LALT,               KC_SPC,   KC_RGUI, KC_SLSH, KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    [1] = LAYOUT_tkl_ansi(
        KC_TAB,  KC_Q,    KC_W,      KC_E,     KC_R,       KC_T,      KC_Y,     KC_U,    KC_I,    KC_O,     KC_P,     KC_BSPC,
        KC_CAPS, KC_A,    KC_S,      KC_D,     KC_F,       KC_G,      KC_H,     KC_J,    KC_K,    KC_L,     KC_SCLN,  KC_ENT,
        KC_LSFT, KC_Z,    KC_X,      KC_C,     KC_V,       KC_B,      KC_N,     KC_M,    KC_COMM, KC_DOT,   KC_UP ,   KC_QUOT,
        MO(3),   KC_LCTL, KC_GRV,    KC_LALT,  KC_LGUI,               KC_SPC,   KC_RALT, KC_SLSH, KC_LEFT,  KC_DOWN,  KC_RGHT
    ),
    [2] = LAYOUT_tkl_ansi(
        KC_TAB,  MD_BLE1, MD_BLE2,   MD_BLE3,  MD_24G,     RM_NEXT,   TO(1),    TO(0),   KC_LBRC, KC_RBRC,  KC_BSLS,  RM_TOGG,
        KC_ESC,  KC_1,    KC_2,      KC_3,     KC_4,       KC_5,      KC_6,     KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,
        KC_LSFT, KC_INS,  KC_DEL,    KC_HOME,  KC_END,     KC_PGUP,   KC_PGDN,  RM_SATD, RM_HUED, RM_HUEU,  RM_VALU , QK_BAT,
        KC_NO,   KC_DEL,  KC_GRV,    KC_LGUI,  KC_LALT,               EE_CLR,   RM_SATU, KC_EQL,  RM_SPDD,  RM_VALD,  RM_SPDU
    ),
    [3] = LAYOUT_tkl_ansi(
        KC_TAB,  MD_BLE1, MD_BLE2,   MD_BLE3,  MD_24G,     RM_NEXT,   TO(1),    TO(0),   KC_LBRC, KC_RBRC,  KC_BSLS,  RM_TOGG,
        KC_ESC,  KC_1,    KC_2,      KC_3,     KC_4,       KC_5,      KC_6,     KC_7,    KC_8,    KC_9,     KC_0,     KC_MINS,
        KC_LSFT, KC_INS,  KC_DEL,    KC_HOME,  KC_END,     KC_PGUP,   KC_PGDN,  RM_SATD, RM_HUED, RM_HUEU,  RM_VALU , QK_BAT,
        KC_NO,   KC_DEL,  KC_GRV,    KC_LALT,  QK_WLO,                EE_CLR,   RM_SATU, KC_EQL,  RM_SPDD,  RM_VALD,  RM_SPDU
    ),
    // MIDI step sequencer. Toggle this layer with the two bottom corner keys
    // pressed together (handled in luma40.c). Two blocks of 16 steps flank a
    // center column of 6 track selects; PLAY is the spacebar.
    [4] = LAYOUT_tkl_ansi(
        SQ_SALL, SQ_S(0),  SQ_S(1),   SQ_S(2),  SQ_S(3),    SQ_T(0),   SQ_T(1),  SQ_S(4),  SQ_S(5),  SQ_S(6),  SQ_S(7),  SQ_TMPU,
        SQ_SCLR, SQ_S(8),  SQ_S(9),   SQ_S(10), SQ_S(11),   SQ_T(2),   SQ_T(3),  SQ_S(12), SQ_S(13), SQ_S(14), SQ_S(15), SQ_TMPD,
        KC_NO,   SQ_S(16), SQ_S(17),  SQ_S(18), SQ_S(19),   SQ_T(4),   SQ_T(5),  SQ_S(20), SQ_S(21), SQ_S(22), SQ_S(23), SQ_RESU,
        KC_NO,   SQ_S(24), SQ_S(25),  SQ_S(26), SQ_S(27),              SQ_TOGG,  SQ_S(28), SQ_S(29), SQ_S(30), SQ_S(31), SQ_RESD
    )
};
// clang-format on
