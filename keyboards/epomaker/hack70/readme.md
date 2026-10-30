# Epomaker Hack70

A 70-key, 65% ortholinear tri-mode (USB / Bluetooth / 2.4GHz) keyboard with a split spacebar and a 3-LED logo.

* Keyboard Maintainer: [EPOMAKER](https://github.com/Epomaker)
* Hardware Supported: Epomaker Hack70 PCB with es32fs026 microcontroller
* Hardware Availability: [Epomaker](https://epomaker.com/products/epomaker-hack70)

Make example for this keyboard (after setting up your build environment):

    make epomaker/hack70:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## VIA

Load [VIA_Mapping_Hack70.json](VIA_Mapping_Hack70.json) in VIA (Settings → Show Design tab → Load) to get the layout, the custom keycodes and the Backlight / Logo lighting menus.

## Bootloader

The Hack70 uses a mass-storage bootloader: once you enter it, the keyboard stops working as a keyboard and shows up as a regular USB flash drive instead.

Enter the bootloader in 2 ways:

* **Bootmagic reset**: With the keyboard **unplugged**, hold down the key at (0,0) in the matrix (Esc) and, while still holding it, plug the keyboard in via USB.
* **Physical reset button**: Briefly press the button on the back of the PCB.

## Flashing

1. Enter the bootloader using either method above. A new USB storage device (drive) will appear on your computer.
2. Copy the firmware file you built — `epomaker_hack70_default.bin` — onto that drive.
3. The keyboard flashes itself and reboots automatically once the file finishes copying; the storage drive disappears and the keyboard comes back as a normal keyboard running the new firmware.
