/* Copyright 2021 jpskenn
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT( /* Base */
    KC_P7,              KC_P8,              KC_P9,              KC_PSLS,
    KC_P4,              KC_P5,              KC_P6,              KC_PPLS,
    KC_P1,              KC_P2,              KC_P3,              KC_PENT,
    LT(_LOWER,KC_P0),   KC_PDOT,            DM_PLY1,            LT(_RAISE,DM_PLY2),
    XXXXXXX,  XXXXXXX  // for encoders
  ),

  [_LOWER] = LAYOUT(
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            DM_REC1,            MO(_ADJUST),
    XXXXXXX,            XXXXXXX
  ),

  [_RAISE] = LAYOUT(
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    MO(_ADJUST),        XXXXXXX,            XXXXXXX,            DM_REC2,
    XXXXXXX,            XXXXXXX
  ),

  [_ADJUST] = LAYOUT(
    RGB_MOD,            RGB_HUI,            RGB_SAI,            RGB_VAI,
    RGB_RMOD,           RGB_HUD,            RGB_SAD,            RGB_VAD,
    RGB_TOG,            RGB_SPI,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            RGB_SPD,            DM_RSTP,            XXXXXXX,
    XXXXXXX,            XXXXXXX
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  }
  return true;
}



