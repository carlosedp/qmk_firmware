# Epomaker TH85

A customizable 85key keyboard.

![Epomaker TH85](https://raw.githubusercontent.com/Linyer-qwq/image/main/Epomaker TH85.jpg)

* Keyboard Maintainer: [LiWenLiu](https://github.com/LiuLiuQMK)
* Hardware Supported: Epomaker TH85 PCB with es32fs026 microcontroller

Make example for this keyboard (after setting up your build environment):

    make epomaker/th85:default

Flashing example for this keyboard:

    make epomaker/th85:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

The TH85 uses a mass-storage bootloader: once you enter it, the keyboard stops working as a keyboard and shows up as a regular USB flash drive instead.

Enter the bootloader in 2 ways:

* **Bootmagic reset**: With the keyboard **unplugged**, hold down the key at (0,0) in the matrix (Esc) and, while still holding it, plug the keyboard in via USB.
* **Physical reset button**: Briefly press the button on the back of the PCB.

## Flashing

1. Enter the bootloader using either method above. A new USB storage device (drive) will appear on your computer.
2. Copy the firmware file you built — `epomaker_th85_default.bin` or `epomaker_th85_custom.bin` — onto that drive (drag-and-drop or copy/paste, same as any USB flash drive).
3. The keyboard flashes itself and reboots automatically once the file finishes copying; the storage drive disappears and the keyboard comes back as a normal keyboard running the new firmware.
4. No manual "safely eject" step is required — just wait for the copy to finish and the drive to disappear on its own.
