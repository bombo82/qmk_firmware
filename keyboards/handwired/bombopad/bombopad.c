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

#include "quantum.h"
#include "bombopad.h"

uint8_t current_layer_bombopad = 0;
bool hold_layer_bombopad = false;
uint16_t hash_timer_bombopad;

void cycle_layers_bombopad(keyrecord_t *record) {
    if (!record->event.pressed) {
        return;
    }
    current_layer_bombopad = (current_layer_bombopad == layer_size_bombopad - 1) ? 0 : current_layer_bombopad + 1;
    layer_move(current_layer_bombopad);
};

void cycle_layers_hold_bombopad(keyrecord_t *record) {
    if(record->event.pressed) {
        hash_timer_bombopad = timer_read();
        layer_on(layer_size_bombopad - 1);
        hold_layer_bombopad = true;
        return;
    } else {
        layer_off(layer_size_bombopad - 1);
        hold_layer_bombopad = false;
        if (timer_elapsed(hash_timer_bombopad) < TAPPING_TERM) {
            current_layer_bombopad = (current_layer_bombopad == layer_size_bombopad - 1) ? 0 : current_layer_bombopad + 1;
            layer_move(current_layer_bombopad);
        }
    }
};

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KB_CYCLE_L:
            cycle_layers_bombopad(record);
            return false;
        case KB_CYCLE_LH:
            cycle_layers_hold_bombopad(record);
            return false;
        default:
            return process_record_user(keycode, record);
    }
};

#ifdef OLED_ENABLE
#include <stdio.h>

// OLED Display Size: 20 x 4
bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }

    oled_write_ln_P(PSTR("   BomboPad v0.3"), false);
    oled_write_ln_P(PSTR("LAYER 0: ALWAYS ON"), false);
    oled_write_P(PSTR("LAYER"), false);
    oled_write(get_u8_str(current_layer_bombopad, ' '), false);
    oled_write_ln_P(PSTR(" ON"), false);
    oled_write_ln_P(hold_layer_bombopad && timer_elapsed(hash_timer_bombopad) > TAPPING_TERM ? PSTR("LAST LAYER HOLD") : PSTR(""), false);

    return false;
};
#endif
