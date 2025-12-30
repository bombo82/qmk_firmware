# BomboPad QMK Firmware

BomboPad is an open-source, versatile 12-key macropad featuring dual rotary encoders and display support. Designed with a focus on flexibility, it supports both wired and wireless configurations.

This directory contains the **QMK firmware** implementation for the BomboPad.

## Key Features (v0.3)

The current firmware version supports the following hardware features:

- **12 keys**: Matrix layout 3x4.
- **Dual Rotary Encoders**: Supports EC11 or EVQWGD001 encoders.
- **Display Support**: SSD1306 128x32 OLED.
- **Microcontroller**: Pro Micro (ATmega32U4) or compatible.
- **Bootloader**: Caterina.

## Hardware Availability

For hardware design files, electrical schematics, and PCB layouts, please refer to the **[main BomboPad repository](https://github.com/bombo82/bombopad)**.

## Build Instructions

To build the firmware, ensure you have the QMK CLI installed and configured.

### 1. Default Keymap

To compile the default keymap for version 0.3:

```bash
qmk compile -kb handwired/bombopad/v0_3 -km default
```

### 2. Flashing

To flash the firmware, use the `-f` flag or put the keyboard in bootloader mode (usually by resetting the Pro Micro) and run:

```bash
qmk flash -kb handwired/bombopad/v0_3 -km default
```

The `v0_3` version uses the `caterina` bootloader.

## Development Information

### Global Variables

The core keyboard code (`bombopad.c/h`) declares several variables as `extern` that must be defined in your `keymap.c`:

- `uint8_t layer_size_bombopad`: Defines the total number of layers. **Mandatory** to initialize it for the cycling functions to work correctly.
- `uint8_t current_layer_bombopad`: Tracks the currently active layer.
- `bool hold_layer_bombopad`: Indicates if a layer is being held (used for OLED feedback).
- `uint16_t hash_timer_bombopad`: Timer used to distinguish between tap and hold actions.

**Example initialization in `keymap.c`:**

```c
uint8_t layer_size_bombopad = 4; // If your keymap has 4 layers
```

### Layer Cycling Functions

The firmware provides two main functions to navigate through layers, associated with custom keycodes:

1.  **`cycle_layers_bombopad` (Keycode: `KB_CYCLE_L`)**:
    - Cycles to the next layer on each press.
    - Returns to layer `0` after reaching the last layer (`layer_size_bombopad - 1`).

2.  **`cycle_layers_hold_bombopad` (Keycode: `KB_CYCLE_LH`)**:
    - **Tap**: Cycles to the next layer.
    - **Hold**: Momentarily activates the **last layer** defined in the keymap until released. Useful for a utility layer (e.g., media controls).

#### Usage Example

To use these features, add the keycodes to your layout:

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,
        KC_TAB,  KC_Q,    KC_W,    KC_E,
        KC_LCTL, KC_LSFT, KC_LGUI, KB_CYCLE_LH // Use KB_CYCLE_LH for cycle and hold
    ),
    // ... other layers ...
    [_UTIL] = LAYOUT(
        QK_BOOT, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    )
};
```

### Custom Keycodes

The keyboard header defines `custom_keycodes_kb` starting at `SAFE_RANGE`:

- `KB_CYCLE_L`
- `KB_CYCLE_LH`

Keymaps should define their own custom keycodes starting at `SAFE_RANGE` (if not using the keyboard ones) or after the keyboard's custom keycodes.

### OLED Support

OLED support is enabled by default in `rules.mk` and uses the `ssd1306` driver. Configuration can be found in `config.h`.

To customise the information displayed on the OLED, you need to implement the `oled_task_user` function in your `keymap.c`.

#### Configuration Example

The following example shows how to display the current layer name and a visual representation of the key layout:

```c
bool oled_task_user(void) {
    // Write header
    oled_write_ln_P(PSTR("BomboPad v0.3"), false);

    // Write layer information based on current_layer_bombopad
    oled_write_ln_P(PSTR("LAYER 0: ALWAYS ON"), false);
    switch (current_layer_bombopad) {
        case _BASE:
            oled_write_ln_P(PSTR("Layer: Default"), false);
            break;
        case _UTIL:
            oled_write_ln_P(PSTR("Layer: Utility"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer: Unknown"), false);
    }

    // Optional: display feedback when a layer is being held
    if (hold_layer_bombopad && timer_elapsed(hash_timer_bombopad) > TAPPING_TERM) {
        oled_write_ln_P(PSTR("LAST LAYER HOLD"), false);
    }

    return false;
}
```

## Help & Contributions

Bug reports, suggestions, and contributions are welcome! Please
use [GitHub Issues](https://github.com/bombo82/bombopad/issues)
and [Discussions](https://github.com/bombo82/bombopad/discussions) for any feedback.

## Authors

- **Gianni Bombelli (bombo82)** - [GitHub Profile](https://github.com/bombo82)

## Licenses

Documentation are licensed under GNU Free Documentation License as published by the Free Software Foundation, either
version 1.3 of the License, or (at your option) any later version.

Source code are licensed under GNU General Public License as published by the Free Software Foundation, either version 3
of the License, or (at your option) any later version.

Hardware design and all related things are licensed under CERN Open Hardware Licence as published by the CERN, either
version 2 of the Licence, or (at your option) any later version.

## License Disclaimer

Copyright (C) 2024-2025 Gianni Bombelli <bombo82@giannibombelli.it>

Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover Texts.

You should have received a copy of the GNU Free Documentation License
along with this program. If not, see <https://www.gnu.org/licenses/fdl-1.3.html>.

## Acknowledgements

Special thanks to [Arialdo](https://github.com/arialdomartini) for introducing me to the world of custom mechanical
keyboards.
