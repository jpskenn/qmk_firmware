/*
Copyright 2024 Takeshi Nishio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "version.h"

// layers
enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// custom key codes
enum custom_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  VERSION,
};

// key code macros
#define BASE1   DF(_BASE)
#define LOWER   MO(_LOWER)
#define RAISE   MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_LCTL,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,
    // |-----------------+---------+---------+  ---------+---------+---------+---------+--------  -+---------+---------+---------------------------|
                          KC_LWIN,  ~KC_LALT, KC_SPC,     LOWER,    XXXXXXX,  RAISE,    KC_SPC,     KC_RALT,  KC_RWIN
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_LOWER] = LAYOUT(
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_TILD,  KC_EXLM,   KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_TILD,  KC_PIPE,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PLUS,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  
    // |-----------------+---------+---------+  ---------+---------+---------+---------+--------  -+---------+---------+---------------------------|
                          _______,  _______,  _______,    _______,  _______,  ADJUST,   _______,    _______,    _______
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_RAISE] = LAYOUT(
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  KC_GRV,   KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,  KC_QUOT,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_VOLD,  KC_VOLU,  KC_LCBR,  KC_RCBR,  KC_PIPE,  _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,
    // |-----------------+---------+---------+  ---------+---------+---------+---------+--------  -+---------+---------+---------------------------|
                          _______,  _______,  _______,    ADJUST,   _______,  _______,  _______,    KC_VOLD,  KC_VOLU
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_ADJUST] = LAYOUT(
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  RGB_RMOD, KC_INS,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,  VERSION,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,
    // |-----------------+---------+---------+  ---------+---------+---------+---------+--------  -+---------+---------+---------------------------|
                          _______,  _______,  _______,    _______,  _______,  _______,  _______,    _______,  _______
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
};


//------------------------------------------------------------------------------
// Handle key codes
//------------------------------------------------------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            return false;
        default:
            break;
    }
    return true;
}
