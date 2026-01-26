# EPOMAKER Split65

* Keyboard Maintainer: [EPOMAKER](https://github.com/Epomaker)
* Hardware Supported: EPOMAKER Split65
* Hardware Availability: EPOMAKER Split65

Clone this repo:

    git clone https://github.com/carlosedp/qmk_firmware.git

Make example for this keyboard (after setting up your build environment):

    qmk compile -kb epomaker/split65 -km via

Flashing example for this keyboard:

    qmk flash -kb epomaker/split65 -km via

Or use QMK Toolbox.


## Flashing Instructions

To reset **both sides** of the keyboard into bootloader mode, do the following:

**Left Side:**

* Hold the Escape key while connecting the USB cable (it might erase persistent settings)
* Flash the firmware using QMK Toolbox or command line when DFU mode is detected.

**Right Side:**

* Move the switch behind of the RShift key (you should remove the keycap) to the lower position.
* Remove both the Space keycap and switch. Insert a tweezer or paper clip shorting the two holes beside the central switch hole while connecting the USB cable to the right half. The DFU pads are behind the switch position.
* After flashing this firmware, you can do this by holding the "7" key while plugging the USB cable instead of shorting the holes. Changing the switch to the down position is still required.
* **NOTE**: Don't forget making switch back up! It won't work unless the switch is in the up position.
  ![Howto](https://github.com/gwangyi/Split65/raw/main/howto.jpg)

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
