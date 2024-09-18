# sandy_lp

![sandy_lp]()

`SandyLP` is a 40% keyboard with symmetrical row staggered layout and key height optimization.

Layered PCB will make height differences for each key, to cover the lack of optimization to physical key layout in two dimensions that only adjust x-y plane.

* Keyboard Maintainer: [jpskenn](https://github.com/jpskenn)
* Hardware Supported: The PCBs
* Hardware Availability: [SandyLP@GitHub](https://github.com/jpskenn/SandyLP)

Make example for this keyboard (after setting up your build environment):

    make sandy_lp:default

Flashing example for this keyboard:

    make sandy_lp:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 3 ways:

* **Bootmagic reset**: Hold down the key at (0,0) in the matrix (usually the top left key or Escape) and plug in the keyboard
* **Physical reset button**: Briefly press the button on the back of the PCB - some may have pads you must short instead
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
