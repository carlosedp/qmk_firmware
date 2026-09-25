# Geonix Rev. 2.5

A 40% wireless keyboard supporting BLE, 2.4 GHz, and USB modes. There are two variants, one that has all 1U keys and one with a 2U spacebar.

* Keyboard Maintainer: [BunnyHorseCat](https://github.com/BunnyHorseCat/)
* Hardware Supported: Geonix Rev. 2.5 PCB with ES32 FS026 microcontroller
* Hardware Availability: Geonix Rev. 2.5

Make example for this keyboard (after setting up your build environment):

    make chosfox/geonix_rev25:default

Flashing example for this keyboard:

    make chosfox/geonix_rev25:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset**: Short the Reset (NRST) and Ground (GND) pads on the top of the daughterboard. Both the main MCU and wireless MCU of this keyboard live on the daughterboard.