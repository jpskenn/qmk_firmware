/* Copyright 2022 Takeshi Nishio
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
#include "version.h"
#include "keymap_jp.h"

void rgb_matrix_set_color_user(int, int, int, int, bool);

bool is_led_indicator_enabled = true;

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _US = 0,
    _US_ALT,
    _US_LOW,
    _US_RAI,
    _US_FN,
    _JP,
    _JP_ALT,
    _JP_LOW,
    _JP_RAI,
    _JP_FN,
    _ADJUST,
};

enum custom_keycodes {
  US = SAFE_RANGE,
  US_ALT,
  JP,
  JP_ALT,
  ADJUST,
  VERSION,
  IND_TOG,
};

// Key Macro
#define SP_U_LO  LT(_US_LOW, KC_SPC)
#define SP_U_RA  LT(_US_RAI, KC_SPC)
#define SP_U_FN  LT(_US_FN, KC_SPC)
#define SP_J_LO  LT(_JP_LOW, KC_SPC)
#define SP_J_RA  LT(_JP_RAI, KC_SPC)
#define SP_J_FN  LT(_JP_FN, KC_SPC)
// #define SP_ADJ  LT(_ADJUST, KC_SPC)
#define C_ESC   LCTL_T(KC_ESC)
#define US   DF(_US)
#define US_ALT   TG(_US_ALT)
#define JP   DF(_JP)
#define JP_ALT   TG(_JP_ALT)

// #define FUNC    MO(_FUNC)
#define ADJUST  MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_US] = LAYOUT_fw(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,                       KC_BSLS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,            KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,          KC_BSPC,
        C_ESC,         KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,            KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,       KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     DM_PLY1,                      DM_PLY2,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                 KC_LWIN,       KC_LALT,     SP_U_LO,    KC_BSPC,            KC_ENT,   SP_U_RA,     KC_RALT,    KC_APP
    ),
    [_US_ALT] = LAYOUT_fw(
        KC_ESC,   _______,  _______,  _______,  _______,  _______,  _______,                      _______,  KC_PSLS,  KC_PSLS,  KC_PSLS,  KC_PAST,  KC_PMNS,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  KC_P4,    KC_P5,    KC_P6,    XXXXXXX,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  KC_P1,    KC_P2,    KC_P3,    XXXXXXX,  _______,
                                 _______,       _______,     SP_U_FN,    _______,            _______,    _______,     KC_P0,      KC_PDOT
    ),
    [_US_LOW] = LAYOUT_fw(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,                      KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______,            _______,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,       KC_BSLS,
        _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,                      _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
                                 _______,       _______,     _______,    _______,            _______,    ADJUST,      _______,    _______
    ),
    [_US_RAI] = LAYOUT_fw(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,                      KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,            _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,          KC_DEL,
        _______,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,            _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,       KC_QUOT,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,                       _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
                                 _______,       _______,     ADJUST,     KC_F12,             _______,    _______,     _______,    _______
    ),
    [_US_FN] = LAYOUT_fw(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,                        KC_BSLS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,            KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,          KC_BSPC,
        C_ESC,         KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,            KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,       KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     DM_PLY1,                      DM_PLY2,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                 KC_LOPT,       KC_LCMD,     _______,    KC_BSPC,            KC_ENT,     ADJUST,     KC_RCMD,    KC_ROPT
    ),
    [_JP] = LAYOUT_fw(
        JP_ZKHK,  JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     JP_CIRC,                      JP_YEN,   JP_6,     JP_7,     JP_8,     JP_9,     JP_0,     JP_MINS,
        KC_TAB,        JP_Q,     JP_W,     JP_E,     JP_R,     JP_T,     JP_AT,              JP_LBRC,  JP_Y,     JP_U,     JP_I,     JP_O,     JP_P,          KC_BSPC,
        C_ESC,         JP_A,     JP_S,     JP_D,     JP_F,     JP_G,     JP_COLN,            JP_RBRC,  JP_H,     JP_J,     JP_K,     JP_L,     JP_MINS,       KC_ENT,
        KC_LSFT,  KC_LSFT,  JP_Z,     JP_X,     JP_C,     JP_V,     JP_B,                         KC_RGHT,  JP_N,     JP_M,     JP_COMM,  JP_DOT,   JP_SLSH,  JP_BSLS,
                                 KC_LWIN,       KC_LALT,     SP_J_LO,    KC_BSPC,            KC_ENT,   SP_J_RA,     KC_RALT,    KC_APP
    ),
    [_US_ALT] = LAYOUT_fw(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  KC_PSLS,  KC_PSLS,  KC_PSLS,  KC_PAST,  KC_PMNS,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  KC_P4,    KC_P5,    KC_P6,    XXXXXXX,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  KC_P1,    KC_P2,    KC_P3,    XXXXXXX,  _______,
                                 _______,       _______,     SP_J_FN,    _______,            _______,    _______,     KC_P0,      KC_PDOT
    ),
    [_JP_LOW] = LAYOUT_fw(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,                      KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        JP_EXLM,  JP_DQUO,  JP_HASH,  JP_DLR,   JP_PERC,  JP_TILD,            JP_PIPE,  JP_AMPR,  JP_QUOT,  JP_LPRN,  JP_RPRN,  _______,       JP_EQL,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  JP_AT,    JP_SCLN,  JP_COLN,  JP_LBRC,  JP_RBRC,       KC_BSLS,
        _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,                      _______,  JP_GRV,   JP_PLUS,  JP_ASTR,  JP_LCBR,  JP_RCBR,  KC_PIPE,
                                 _______,       _______,     _______,    _______,            _______,    ADJUST,      _______,    _______
    ),
    [_JP_RAI] = LAYOUT_fw(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,                      KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     _______,            _______,  JP_6,     JP_7,     JP_8,     JP_9,     JP_0,          KC_DEL,
        _______,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,            _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  JP_SCLN,       JP_COLN,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,                       _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
                                 _______,       _______,     ADJUST,     KC_F12,             _______,    _______,     _______,    _______
    ),
    [_JP_FN] = LAYOUT_fw(
        JP_ZKHK,  JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     JP_CIRC,                      JP_YEN,   JP_6,     JP_7,     JP_8,     JP_9,     JP_0,     JP_MINS,
        KC_TAB,        JP_Q,     JP_W,     JP_E,     JP_R,     JP_T,     JP_AT,              JP_LBRC,  JP_Y,     JP_U,     JP_I,     JP_O,     JP_P,          KC_BSPC,
        C_ESC,         JP_A,     JP_S,     JP_D,     JP_F,     JP_G,     JP_COLN,            JP_RBRC,  JP_H,     JP_J,     JP_K,     JP_L,     JP_MINS,       KC_ENT,
        KC_LSFT,  KC_LSFT,  JP_Z,     JP_X,     JP_C,     JP_V,     JP_B,                         KC_RGHT,  JP_N,     JP_M,     JP_COMM,  JP_DOT,   JP_SLSH,  JP_BSLS,
                                 KC_LWIN,       KC_LALT,     _______,    KC_BSPC,            KC_ENT,   ADJUST,     KC_RALT,    KC_APP
    ),
    [_ADJUST] = LAYOUT_fw(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       US,       JP,       _______,  _______,  _______,  _______,            RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_VAI,  IND_TOG,  RGB_RMOD,      KC_INS,
        KC_CAPS,       AU_TOG,   MU_TOG,   MU_MOD,   MUV_DE,   MUV_IN,   _______,            RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,       VERSION,
        _______,  CK_TOGG,  CK_RST,   CK_DOWN,  CK_UP,    _______,  _______,                      _______,  _______,  _______,  _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,
                                 _______,       _______,     _______,    _______,            _______,    _______,     _______,    _______
    ),
};

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // case BASE1: // Change default ayer --> Write to EEPROM
        // case KC_FN1:
        //     if (record->event.pressed) {
        //         set_single_persistent_default_layer(_BASE1);
        //     }
        //     return false;
        // case BASE2: // Change default ayer --> Write to EEPROM
        // case KC_FN2:
        //     if (record->event.pressed) {
        //         set_single_persistent_default_layer(_BASE2);
        //     }
        //     return false;
        // case BASE3: // Change default ayer --> Write to EEPROM
        // case KC_FN3:
        //     if (record->event.pressed) {
        //         set_single_persistent_default_layer(_BASE3);
        //     }
        //     return false;
        case IND_TOG: // Toggle LED indicator.
        case KC_FN4:
            if (record->event.pressed) {
                is_led_indicator_enabled = !is_led_indicator_enabled;
            }
            return false;
        case VERSION: // Output firmware info.
        case KC_FN0:
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            return false;
        default:
            break;
    }
    return true;
}

//------------------------------------------------------------------------------
// RGB Matrix settings
//------------------------------------------------------------------------------
#ifdef RGB_MATRIX_ENABLE

void rgb_matrix_indicators_user(void) {
    // Indicator On / Off control
    if(!is_led_indicator_enabled) {
        return;
    }

    // Layers
    // switch(get_highest_layer(layer_state|default_layer_state)) {
    //     // Disable BASE1 indicator. It's dazzling...
    //     // case _BASE1:
    //     //     rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_PINK, true);
    //     //     rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_PINK, true);
    //     //     break;
    //     case _BASE2:
    //         rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_BLUE, true);
    //         rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_BLUE, true);
    //         break;
    //     case _BASE3:
    //         rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_YELLOW, true);
    //         rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_YELLOW, true);
    //         break;
    //     case _LOWER:
    //         rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_GREEN, true);
    //         rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_GREEN, true);
    //         break;
    //     case _RAISE:
    //         rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_CYAN, true);
    //         rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_CYAN, true);
    //         break;
    //     case _FUNC:
    //         rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_WHITE, true);
    //         rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_WHITE, true);
    //         break;
    //     case _ADJUST:
    //         rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_RED, true);
    //         rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_RED, true);
    //         break;
    //     default:
    //         // Do nothing to enable effect / animation color.
    //         break;
    // }

    // CAPS
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_MAGENTA, true);
    }
}

void rgb_matrix_set_color_user(int index, int h, int s, int v, bool is_adjust_brightness) {
    HSV hsv = { h, s, v };

    if (is_adjust_brightness) {
        if (hsv.v > rgb_matrix_get_val()) {
            // Adjust brightness to current value
            hsv.v = rgb_matrix_get_val();
        }
    }

    RGB rgb = hsv_to_rgb(hsv);
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}
#endif

//------------------------------------------------------------------------------
// Keyboard Initialization
//------------------------------------------------------------------------------
void keyboard_post_init_user(void) {
}
