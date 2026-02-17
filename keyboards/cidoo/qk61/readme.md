# CIDOO QK61

A customizable 61key keyboard.

* Keyboard Maintainer: [CIDOO](https://github.com/CIDOOKeyboard)
* Hardware Supported: CIDOO QK61 PCB with ES32FS026 microcontroller

## Known issues

1. When RGB light is turned off, logo LED doesn't update anymore
    - Workaround is to set RGB light brightness to 0 instead of turning it off

Make example for this keyboard (after setting up your build environment):

    make cidoo/qk61:via

Flashing example for this keyboard:

    make cidoo/qk61:via:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Esc key) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB
