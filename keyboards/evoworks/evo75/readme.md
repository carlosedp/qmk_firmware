# Evoworks evo75

A customizable 75% keyboard with an 81-key ANSI layout, per-key RGB, and independent logo lighting.

- Hardware Supported: evo75 PCB with ES32FS026 microcontroller
- Lighting: 80 key LEDs and 25 logo LEDs

Make example for this keyboard (after setting up your build environment):

    make evoworks/evo75:default

The firmware image is `evoworks_evo75_default.bin`.

Flashing example for this keyboard:

    make evoworks/evo75:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

- **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard.

## Default keymap

- **Fn+Grave**: Select USB.
- **Fn+1 through Fn+3**: Select Bluetooth channels 1–3.
- **Fn+4**: Select 2.4 GHz.
- **Fn+Q**: Toggle the independent logo lighting.
- **Logo animation key** (to the right of Up): Cycle the independent logo lighting effect.
- The Fn layer also provides RGB Matrix controls, battery status, and Win lock. See [the default keymap](keymaps/default/keymap.c) for all assignments.

The supplied [VIA definition](VIA_Mapping_Evo75.json) describes the keyboard layout and lighting controls.
