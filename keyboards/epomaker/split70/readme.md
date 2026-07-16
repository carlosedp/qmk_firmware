# Epomaker Split70

- Keyboard Maintainer: [Epomaker](https://github.com/Epomaker)
- Hardware Supported: Epomaker Split70
- Hardware Availability: Epomaker Split70

Make example for this keyboard (after setting up your build environment):

    make epomaker/split70:default

Flashing example for this keyboard:

    make epomaker/split70:default

## Flashing the Firmware

**HOW TO ENTER DFU(FIRMWARE UPDATE)MODE**
A：The Split70 is a split keyboard with two halves — the left half (with the knob) and the right half (with arrow keys).

**Each half must be entered into DFU mode separately.**

● **Left Half (with knob):**

1. Disconnect all cables from the keyboard.
2. Hold ESC and plug in USB-C.
3. "Device Connected" shows on the QMK Toolbox

● **Right Half(with arrow keys):**

1. Disconnect all cables from the keyboard.
2. Remove ALT and FN Keycaps and Flip the toggle switch between them down.
   ![Remove Keys](keys.png)
3. Remove Right Spacebar keycap and switch,short-circuit PCB holes with tweezers,then plug in USB-C.
   ![Short Circuit PCB Holes](short_pins.png)
4. "Device Connected"shows on the QMK Toolbox
5. After flashing,flip ALT/FN toggle back up.

**After flashing this firmware, you can do this by holding the "7" key while plugging the USB cable instead of shorting the holes. Flipping the switch to the down position is still required to flash and return to up position after flashing.
**

● Please reset the keyboard after flashing is completed.

‼️ Notes:
When updating or flashing the keyboard, MAKE SURE ONLY ONE KEYBOARDIS CONNECTED TO THE DEVICE!
When updating or flashing the keyboard, DON'T MOVE THE KEYBOARD or PRESS ANY KEYS!

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).
