// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// A 5th layer holds the sequencer panel (the stock keymap uses 4).
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

// MIDI is required by the sequencer: basic note on/off + advanced octave control.
#define MIDI_BASIC
#define MIDI_ADVANCED

// 32-step, 6-track drum sequencer.
#define SEQUENCER_STEPS 32
#define SEQUENCER_TRACKS 6
