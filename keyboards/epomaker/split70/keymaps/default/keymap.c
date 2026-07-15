// Copyright 2024 Epomaker (@Epomaker)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "rgb_record/rgb_record.h"

enum layers {
    _BL = 0,
    _FL,
    _MBL,
    _MFL,
};

#define _______ KC_TRNS

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BL] = LAYOUT(
        KC_MUTE,  QK_GESC,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        MO(_FL),  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        MO(_FL),  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        MO(_FL),  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_DEL,
        MO(_FL),  KC_LCTL,  KC_LALT,  KC_LGUI,            KC_SPC,                                 KC_SPC,             KC_RGUI,  KC_RALT,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_FL] = LAYOUT(
        _______, _______, _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,    KC_F9,      KC_F10,   KC_F11,    KC_F12,   QK_BOOT,
        _______, RM_NEXT,  KC_BT1,    KC_BT2,   KC_BT3,   KC_2G4,   _______,                      KC_PSCR,  KC_SCRL,  KC_PAUSE, _______,    _______,  RM_HUED,   RM_HUEU,  RL_MOD,
        _______, _______,  KC_NO,     TO(_MBL), _______,  _______,  _______,                      KC_HOME,  KC_END,   KC_PGUP,  KC_PGDN,    RM_SATD,  RM_SATU,             KC_END,
        _______, _______,  RM_TOGG,   _______,  _______,  NK_TOGG,  HS_BATQ,            HS_BATQ,  _______,  _______,  _______,  _______,    _______,  _______,   RM_VALU,  KC_INS,
        _______, KC_FILP,  _______,   _______,            KC_BATQ,                                KC_BATQ,           _______,  GU_TOGG,              RM_SPDD,   RM_VALD,  RM_SPDU),

    [_MBL] = LAYOUT(
        KC_MUTE, QK_GESC,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,
        MO(_MFL),KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        MO(_MFL),KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,
        MO(_MFL),KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,               KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_DEL,
        MO(_MFL),KC_LCTL,  KC_LGUI,  KC_LALT,            KC_SPC,                                 KC_SPC,            KC_RALT,  KC_RGUI,            KC_LEFT,  KC_DOWN,  KC_RGHT),

    [_MFL] = LAYOUT(
        _______,  _______, _______,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,              KC_F6,    KC_F7,    KC_F8,   KC_F9,     KC_F10,  KC_F11,    KC_F12,   QK_BOOT,
        _______,  RM_NEXT, KC_BT1,    KC_BT2,   KC_BT3,   KC_2G4,   _______,                      KC_PSCR,  KC_SCRL,  KC_PAUSE, _______, _______, RM_HUED,   RM_HUEU,  RL_MOD,
        _______,  TO(_BL), KC_NO,     _______,  _______,  _______,  _______,                      KC_HOME,  KC_END,   KC_PGUP, KC_PGDN, RM_SATD, RM_SATU,             KC_END,
        _______,  _______, RM_TOGG,   _______,  _______,  _______,  HS_BATQ,            HS_BATQ,  _______,  _______,  _______, _______,   _______, _______, RM_VALU,  KC_INS,
        _______,  KC_FILP, _______,   _______,            KC_BATQ,                                KC_BATQ,            _______, KC_RALT,            RM_SPDD,   RM_VALD,  RM_SPDU),

};


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [1] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [2] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [3] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif
// clang-format on
