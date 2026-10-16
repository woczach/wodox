# wodox

*A 56-key split columnar keyboard with per-key RGB, two Waveshare RP2040-Matrix halves connected via TRRS*

* Keyboard Maintainer: [woczach](https://github.com/woczach)
* Hardware Supported: wodox PCB v1.0 (reversible), 2x Waveshare RP2040-Matrix
* Hardware Availability: this repo

Make example for this keyboard (after setting up your build environment):

    make wodox:default

Flashing example for this keyboard:

    make wodox:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Flashing

Flash the **same .uf2 file to both halves**. The half connected to USB is the master and acts as the **left half** — plug USB into the left half.

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the BOOT button on the RP2040-Matrix module
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available

## Hardware notes

* Matrix per half: 4 rows x 7 cols (28 keys), COL2ROW
* Rows: GP5, GP6, GP7, GP8; Cols: GP3, GP1, GP4, GP10, GP11, GP12, GP13
* Split serial (TRRS ring1): GP0
* Per-key WS2812 data: GP9 (28 LEDs per half)
* Vial firmware: `make wodox:vial` (requires [vial-qmk](https://github.com/vial-kb/vial-qmk))
