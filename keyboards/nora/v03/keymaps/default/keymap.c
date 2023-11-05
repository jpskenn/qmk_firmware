/* Copyright 2021 Takeshi Nishio
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

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

// Key Macro
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   XXXXXXX,  XXXXXXX,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  XXXXXXX,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,          KC_BSPC,
        KC_LCTL,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  XXXXXXX,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,       KC_ENT,
        KC_LSFT,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  KC_MUTE,  KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  XXXXXXX,
                                 KC_LOPT,       KC_LCMD,     SP_LOW,     KC_BSPC,  XXXXXXX,   KC_ENT,     SP_RAI,      KC_RGUI,    KC_ROPT
    ),
    [_LOWER] = LAYOUT(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______,  _______,  _______,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,       KC_BSLS,
        _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
                                 _______,       _______,     _______,    _______,  _______,  _______,    MO(_ADJUST),      _______,    _______
    ),
    [_RAISE] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,  _______,  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,          KC_DEL,
        _______,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,       KC_QUOT,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
                                 _______,       _______,     MO(_ADJUST),     KC_F12,   _______,  _______,    _______,     _______,    _______
    ),
    [_ADJUST] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  RGB_RMOD,      KC_INS,
        KC_CAPS,       AU_TOGG,  MU_TOGG,  MU_NEXT,  AU_PREV,  AU_NEXT,  _______,  _______,  RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,       _______,
        _______,  CK_TOGG,  CK_RST,   CK_DOWN,  CK_UP,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,
                                 _______,       _______,     _______,    _______,  _______,  _______,    _______,     _______,    _______
    ),
};
