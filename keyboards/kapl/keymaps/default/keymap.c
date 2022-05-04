// Copyright 2022 Alexander Lozyuk (@keyzog)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#define SPC_FN  LT(1,KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐           ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PGUP,             KC_HOME, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤           ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_PGDN,             KC_END,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_EQL,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤           ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_GRV,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC,             KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤           ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_EXLM,             KC_QUES, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //├────────┼────────┼────────┼────────┼────────┼─┬──────┴─┬──────┴─┐       ┌─┴──────┬─┴──────┬─┼────────┼────────┼────────┼────────┼────────┤
     KC_LCTL, KC_LGUI, KC_LALT, MO(2),   SPC_FN,    KC_BSPC, KC_DEL,          KC_ENT,  KC_SPC,    MO(1),   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
  //└────────┴────────┴────────┴────────┴────────┘ └────────┴────────┘       └────────┴────────┘ └────────┴────────┴────────┴────────┴────────┘
  ),

  [1] = LAYOUT( // "FN" Funcional
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐           ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_TRNS,             KC_PSCR, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤           ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, KC_TRNS,             KC_TRNS, KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, KC_F12,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤           ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_HASH, KC_DLR,  KC_LBRC, KC_RBRC, KC_GRV,  KC_TRNS,             KC_TRNS, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_F13,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤           ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_PERC, KC_CIRC, KC_LPRN, KC_RPRN, KC_TILD, KC_TRNS,             KC_TRNS, KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_F14,
  //├────────┼────────┼────────┼────────┼────────┼─┬──────┴─┬──────┴─┐       ┌─┴──────┬─┴──────┬─┼────────┼────────┼────────┼────────┼────────┤
     KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,     KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS,   KC_NO,   KC_P0,   KC_PDOT, KC_PENT, KC_F15
  //└────────┴────────┴────────┴────────┴────────┘ └────────┴────────┘       └────────┴────────┘ └────────┴────────┴────────┴────────┴────────┘
  ),

  [2] = LAYOUT( // "CNT" Control
  //┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐           ┌────────┬────────┬────────┬────────┬────────┬────────┬────────┐
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RESET,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤           ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   RGB_SAI, RGB_SPI, RGB_VAI, RGB_HUI, RGB_MOD, KC_NO,               KC_NO,   KC_VOLU, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤           ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   RGB_SAD, RGB_SPD, RGB_VAD, RGB_HUD, RGB_RMOD, KC_NO,              KC_NO,   KC_VOLD, KC_MPLY, KC_MNXT, KC_MPRV, KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼────────┼────────┤           ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_TOG, RGB_M_P, KC_NO,               KC_NO,   KC_MUTE, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
  //├────────┼────────┼────────┼────────┼────────┼─┬──────┴─┬──────┴─┐       ┌─┴──────┬─┴──────┬─┼────────┼────────┼────────┼────────┼────────┤
     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,     KC_NO,   KC_NO,           KC_NO,   KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
  //└────────┴────────┴────────┴────────┴────────┘ └────────┴────────┘       └────────┴────────┘ └────────┴────────┴────────┴────────┴────────┘
  )
};
