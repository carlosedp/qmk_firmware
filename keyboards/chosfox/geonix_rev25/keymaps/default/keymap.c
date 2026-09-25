/* Copyright 2025 bofhgit
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
#include QMK_KEYBOARD_H
#include "rdmctmzt_common.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Layer 0: Mac QWERTY
    [0] = LAYOUT_tkl_ansi(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT,
        MO(2),   KC_DEL,  KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_SPC,  KC_RGUI, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // Layer 1: Win QWERTY
    [1] = LAYOUT_tkl_ansi(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT,
        MO(3),   KC_DEL,  KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC,  KC_RGUI, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    // Layer 2: Mac Fn
    [2] = LAYOUT_tkl_ansi(
        MD_USB,  MD_BLE1, MD_BLE2, MD_BLE3, MD_24G,  RM_NEXT, TO(1),   TO(0),   KC_LBRC, KC_RBRC, KC_BSLS, RM_TOGG,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_LSFT, KC_INS,  KC_DEL,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_M,    KC_COMM, KC_DOT,  RM_VALU, MW_CH,
        KC_NO,   DBG_SW,  QK_BAT,  KC_NO,   KC_LGUI, EE_CLR,  KC_NO,   KC_RGUI, KC_EQL,  RM_SPDD, RM_VALD, RM_SPDU
    ),
    // Layer 3: Win Fn
    [3] = LAYOUT_tkl_ansi(
        MD_USB,  MD_BLE1, MD_BLE2, MD_BLE3, MD_24G,  RM_NEXT, TO(1),   TO(0),   KC_LBRC, KC_RBRC, KC_BSLS, RM_TOGG,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_LSFT, KC_INS,  KC_DEL,  KC_HOME, KC_END,  KC_PGUP, KC_PGDN, KC_M,    KC_COMM, KC_DOT,  RM_VALU, MW_CH,
        KC_NO,   DBG_SW,  QK_BAT,  KC_NO,   KC_LALT, EE_CLR,  KC_NO,   KC_RGUI, KC_EQL,  RM_SPDD, RM_VALD, RM_SPDU
    )
};
