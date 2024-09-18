// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// layers
enum layer_number {
    _BASE1 = 0,
    _BASE2,
    _BASE3,
    _LOWER1,
    _LOWER2,
    _RAISE1,
    _ADJUST,
};

// custom key codes
enum custom_keycodes {
  BASE1 = SAFE_RANGE,
  BASE2,
  BASE3,
  ADJUST,
  VERSION,
  GUI_IME,
  KEY_WAIT,
  IND_TOG,
};

// key code macros
#define ESC_BASE3 LT(_BASE3, KC_ESC)
#define ZH_BASE3 LT(_BASE3, JP_ZKHK)
#define SP_LOW1  LT(_LOWER1, KC_SPC)
#define SP_RAI1  LT(_RAISE1, KC_SPC)
#define SP_LOW2  LT(_LOWER2, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)

#define SP_SFT  LSFT_T(KC_SPC)
#define BS_SFT  LSFT_T(KC_BSPC)

#define CTL_ESC   LCTL_T(KC_ESC)

#define BASE1   DF(_BASE1)
#define BASE2   DF(_BASE2)
#define NUMERIC TG(_BASE3)

#define GUI_LANG1  LGUI_T(KC_LNG1)
#define GUI_LANG2  LGUI_T(KC_LNG2)
#define ALT_LANG1  LALT_T(KC_LNG1)
#define ALT_LANG2  LALT_T(KC_LNG2)

#define MAC_SLP LAG(KC_EJCT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE1] = LAYOUT(
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        CTL_ESC,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     DM_PLY1,  XXXXXXX,  DM_PLY2,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
                    KC_LOPT,    GUI_LANG2,  SP_SFT,         SP_LOW1,  KC_BTN1,  BS_SFT,   SP_RAI1,        GUI_LANG1,  KC_ROPT
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    )

};
