/* Copyright 2025 Carlos Eduardo de Paula <carlosedp@gmail.com>
 * Copyright 2025 EPOMAKER <https://github.com/Epomaker>
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
 * Copyright 2021 QMK <https://github.com/qmk/qmk_firmware>
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

#include "keyboard_common.h"

#ifndef NO_LED
#    define NO_LED 255
#endif

// ===========================================================================
// Keyboard-specific data
// ===========================================================================

// Battery indicator LED indices (first row)
const uint8_t Led_Batt_Index_Tab[BATTERY_LED_COUNT] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

// ============================================================================
// LED Matrix Configuration (keyboard-specific)
// ============================================================================

// clang-format off
led_config_t g_led_config = {
    // Key Matrix to LED Index (6x16 scan matrix with active keys in first 4 rows/12 cols)
    {
    {0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     NO_LED, NO_LED, NO_LED, NO_LED},
    {12,     13,     14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     NO_LED, NO_LED, NO_LED, NO_LED},
    {24,     25,     26,     27,     28,     29,     30,     31,     32,     33,     34,     35,     NO_LED, NO_LED, NO_LED, NO_LED},
    {36,     37,     38,     39,     40,     NO_LED, 41,     42,     43,     44,     45,     46,     NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}},
    // LED Index to Physical Position
    {
    {0, 10}, {20, 10}, {40, 10}, {60, 10}, {80, 10}, {100, 10}, {120, 10}, {140, 10}, {160, 10}, {180, 10}, {200, 10}, {224, 10},
    {0, 20}, {20, 20}, {40, 20}, {60, 20}, {80, 20}, {100, 20}, {120, 20}, {140, 20}, {160, 20}, {180, 20}, {200, 20}, {224, 20},
    {0, 30}, {20, 30}, {40, 30}, {60, 30}, {80, 30}, {100, 30}, {120, 30}, {140, 30}, {160, 30}, {180, 30}, {200, 30}, {224, 30},
    {0, 40}, {20, 40}, {40, 40}, {60, 40}, {80, 40},            {110, 40}, {140, 40}, {160, 40}, {180, 40}, {200, 40}, {224, 40}},
    // LED Index to Flag
    {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1
    }
};
// clang-format on

// ============================================================================
// MIDI step sequencer (layer 4) — data
// ============================================================================
#ifdef SEQUENCER_ENABLE
#    define SEQUENCER_LAYER 4
// Enter/exit combo: the two bottom corner keys, matched by physical position
// so it works no matter what is mapped on them.
#    define SEQ_CORNER_L_ROW 3
#    define SEQ_CORNER_L_COL 0
#    define SEQ_CORNER_R_ROW 3
#    define SEQ_CORNER_R_COL 11

// BPM added/removed per press of SQ_TMPU / SQ_TMPD.
#    define SEQ_TEMPO_STEP 5

// The 6 tracks send Bitwig Drum Machine's first 6 pads: C1..F1 (MIDI 36-41).
// midi_config.octave is set to 2 in keyboard_post_init so C_1 -> 36.
const uint16_t luma40_seq_track_notes[SEQUENCER_TRACKS] = {
    QK_MIDI_NOTE_C_1,       // 36
    QK_MIDI_NOTE_C_SHARP_1, // 37
    QK_MIDI_NOTE_D_1,       // 38
    QK_MIDI_NOTE_D_SHARP_1, // 39
    QK_MIDI_NOTE_E_1,       // 40
    QK_MIDI_NOTE_F_1,       // 41
};

// RGB LED index for each of the 32 steps (matches the layer-4 layout).
const uint8_t luma40_seq_step_led[SEQUENCER_STEPS] = {
     1,  2,  3,  4,   7,  8,  9, 10,
    13, 14, 15, 16,  19, 20, 21, 22,
    25, 26, 27, 28,  31, 32, 33, 34,
    37, 38, 39, 40,  42, 43, 44, 45,
};
// RGB LED index for each of the 6 track-select keys, and the PLAY (space) key.
const uint8_t luma40_seq_track_led[SEQUENCER_TRACKS] = {5, 6, 17, 18, 29, 30};
#    define SEQ_PLAY_LED 41
// Left + right edge columns ("side bars"): a fixed color instead of the rainbow.
const uint8_t luma40_seq_bar_led[8] = {0, 12, 24, 36, 11, 23, 35, 46};

static bool seq_corner_l = false;
static bool seq_corner_r = false;
#endif

// ============================================================================
// QMK Callback Functions
// ============================================================================

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
#ifdef SEQUENCER_ENABLE
    if (get_highest_layer(layer_state) == SEQUENCER_LAYER) {
        // Which track is selected (first active track); -1 = none.
        int8_t sel = -1;
        for (uint8_t t = 0; t < SEQUENCER_TRACKS; t++) {
            if (is_sequencer_track_active(t)) { sel = t; break; }
        }
        // Steps: soft teal — empty dim, active mid; playhead = warm amber (contrast).
        for (uint8_t s = 0; s < SEQUENCER_STEPS; s++) {
            uint8_t led = luma40_seq_step_led[s];
            if (led < led_min || led >= led_max) continue;
            if (is_sequencer_on() && sequencer_get_current_step() == s) {
                rgb_matrix_set_color(led, 210, 125, 25); // playhead: amber
            } else if (is_sequencer_step_on(s)) {
                rgb_matrix_set_color(led, 34, 110, 118);  // active step: teal
            } else {
                rgb_matrix_set_color(led, 6, 16, 18);     // empty step: dim teal
            }
        }
        // Track-select keys: soft blue — dim (idle), bright (selected).
        for (uint8_t t = 0; t < SEQUENCER_TRACKS; t++) {
            uint8_t led = luma40_seq_track_led[t];
            if (led < led_min || led >= led_max) continue;
            if (t == sel) {
                rgb_matrix_set_color(led, 90, 140, 255); // selected
            } else {
                rgb_matrix_set_color(led, 22, 32, 72);   // idle
            }
        }
        // PLAY (space): same blue as the selector but lower — dim (stopped) / mid (playing).
        if (SEQ_PLAY_LED >= led_min && SEQ_PLAY_LED < led_max) {
            if (is_sequencer_on()) {
                rgb_matrix_set_color(SEQ_PLAY_LED, 55, 90, 175);
            } else {
                rgb_matrix_set_color(SEQ_PLAY_LED, 16, 24, 52);
            }
        }
        // Side bars (left + right edge columns): fixed soft purple, no rainbow.
        for (uint8_t i = 0; i < 8; i++) {
            uint8_t led = luma40_seq_bar_led[i];
            if (led < led_min || led >= led_max) continue;
            rgb_matrix_set_color(led, 50, 22, 80);
        }
        return false;
    }
#endif
    return kb_rgb_matrix_indicators_common(led_min, led_max);
}

void notify_usb_device_state_change_user(struct usb_device_state usb_device_state) {
    kb_notify_usb_device_state_change(usb_device_state);
}

bool led_update_user(led_t led_state) {
    return kb_led_update(led_state);
}

void housekeeping_task_user(void) {
    kb_housekeeping_task();
}

void board_init(void) {
    kb_board_init();
}

void keyboard_post_init_user(void) {
    kb_keyboard_post_init();
#ifdef SEQUENCER_ENABLE
    sequencer_set_track_notes(luma40_seq_track_notes);
    midi_config.octave = 2; // map track notes C_1..F_1 to MIDI 36..41 (Bitwig C1..F1)
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef SEQUENCER_ENABLE
    if (record->event.key.row == SEQ_CORNER_L_ROW && record->event.key.col == SEQ_CORNER_L_COL) {
        seq_corner_l = record->event.pressed;
    }
    if (record->event.key.row == SEQ_CORNER_R_ROW && record->event.key.col == SEQ_CORNER_R_COL) {
        seq_corner_r = record->event.pressed;
    }
    if (seq_corner_l && seq_corner_r) {
        seq_corner_l = false;
        seq_corner_r = false;
        layer_invert(SEQUENCER_LAYER);
        return false;
    }
    // Bigger tempo jumps: SQ_TMPU / SQ_TMPD move by SEQ_TEMPO_STEP BPM per press.
    if (record->event.pressed) {
        if (keycode == QK_SEQUENCER_TEMPO_UP) {
            uint8_t t = sequencer_get_tempo();
            sequencer_set_tempo(t > 255 - SEQ_TEMPO_STEP ? 255 : t + SEQ_TEMPO_STEP);
            return false;
        }
        if (keycode == QK_SEQUENCER_TEMPO_DOWN) {
            uint8_t t = sequencer_get_tempo();
            sequencer_set_tempo(t <= SEQ_TEMPO_STEP ? 1 : t - SEQ_TEMPO_STEP);
            return false;
        }
    }
#endif
    return kb_process_record_common(keycode, record);
}
