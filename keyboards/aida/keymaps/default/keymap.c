// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include QMK_KEYBOARD_H

enum layers {
    _BASE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT(

    // ───── 1行目（5 + 5）─────
    KC_Q, KC_W, KC_E, KC_R, KC_T,        KC_Y, KC_U, KC_I, KC_O, KC_P,

    // ───── 2行目（5 + 5）─────
    KC_A, KC_S, KC_D, KC_F, KC_G,        KC_H, KC_J, KC_K, KC_L, KC_SCLN,

    // ───── 3行目（6 + 6）─────
    KC_Z, KC_X, KC_C, KC_V, KC_B, KC_ESC,   KC_ENT, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,

    // ───── 4行目（4 + 4）─────
    KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,   KC_BSPC, KC_RALT, KC_RGUI, KC_RCTL
)

};
