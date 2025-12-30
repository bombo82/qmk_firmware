/*
 * BomboPad is an open-source, versatile 12-key macropad featuring dual rotary encoders and display support.
 * Designed with a focus on flexibility, it supports both wired and wireless configurations.
 * Copyright (C) 2024-2025 Gianni Bombelli <bombo82@giannibombelli.it>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not,
 * see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */

#include QMK_KEYBOARD_H

/*
 * keycode equivalence between GNU/Linux and macOS
 * |-----------------------------------|
 * |   Linux   |   macOS   |   alias   |
 * |-----------|-----------|-----------|
 * |  KC_LALT  |  KC_LOPT  |           |
 * |-----------|-----------|-----------|
 * |  KC_RALT  |  KC_ROPT  |  KC_ALGR  |
 * |-----------|-----------|-----------|
 * |  KC_LGUI  |  KC_LCMD  |           |
 * |-----------|-----------|-----------|
 * |  KC_RGUI  |  KC_RCMD  |           |
 * |-----------------------------------|
 */

typedef enum layer_names {
    _BASE = 0
} layer_names;
uint8_t layer_size_bombopad = 1;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_7,           KC_8,           KC_9,           KC_KB_MUTE,
        KC_4,           KC_5,           KC_6,           LGUI(KC_KB_MUTE),
        KC_1,           KC_2,           KC_3,           KB_CYCLE_LH
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(KC_KB_VOLUME_UP, KC_KB_VOLUME_DOWN),     ENCODER_CCW_CW(LGUI(KC_KB_VOLUME_UP), LGUI(KC_KB_VOLUME_DOWN)) }
};
#endif
