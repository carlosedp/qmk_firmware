# EPOMAKER Split65

* Keyboard Maintainer: [EPOMAKER](https://github.com/Epomaker)
* Hardware Supported: EPOMAKER Split65
* Hardware Availability: EPOMAKER Split65

Put this repo in the `keyboards/epomaker` directory.

    git clone https://github.com/gwangyi/Split65 $(qmk env QMK_HOME)/keyboards/epomaker/split65

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb epomaker/split65 -km via
        
Flashing example for this keyboard:

    qmk flash -kb epomaker/split65 -km via

To reset the board into bootloader mode, do one of the following:

* Hold the Escape key while connecting the USB cable to the left half (it might erase persistent settings)
* Move the switch behind of RShift key (you should remove the keycap) lower position. Remove both the RSpace keycap and switch. Poke two holes just beside of the big hole with a tweezer or paper clip while connecting the USB cable to the right half.
  - After flashing this firmware, you can do this by holding Right arrow key instead of poking the holes.
  - **NOTE**: Don't forget making switch back! It won't work unless the switch is in the correct place.
  ![Howto](https://github.com/gwangyi/Split65/raw/main/howto.jpg)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard.
  Note that Escape key of this keyboard (EPOMAKER Split65) has (1, 0) matrix key.
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

