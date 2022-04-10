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
    _BASE1 = 0,
    _BASE2,
    _BASE3,
    _LOWER,
    _RAISE,
    _FUNC,
    _RESERVE1,
    _RESERVE2,
    _RESERVE3,
    _ADJUST,
};

enum custom_keycodes {
  BASE1 = SAFE_RANGE,
  BASE2,
  BASE3,
  FUNC,
  ADJUST,
  VERSION,
  IND_TOG,
};

// Key Macro
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)
#define C_ESC   LCTL_T(KC_ESC)
#define BASE1   DF(_BASE1)
#define BASE2   DF(_BASE2)
#define BASE3   DF(_BASE3)
#define FUNC    MO(_FUNC)
#define ADJUST  MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE1] = LAYOUT_fw(
        JP_ZKHK,  JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     JP_CIRC,                      JP_YEN,   JP_6,     JP_7,     JP_8,     JP_9,     JP_0,     JP_MINS,
        KC_TAB,        JP_Q,     JP_W,     JP_E,     JP_R,     JP_T,     JP_AT,              JP_LBRC,  JP_Y,     JP_U,     JP_I,     JP_O,     JP_P,          KC_BSPC,
        C_ESC,         JP_A,     JP_S,     JP_D,     JP_F,     JP_G,     JP_COLN,            JP_RBRC,  JP_H,     JP_J,     JP_K,     JP_L,     JP_MINS,       KC_ENT,
        KC_LSFT,  KC_LSFT,  JP_Z,     JP_X,     JP_C,     JP_V,     JP_B,                         XXXXXXX,  JP_N,     JP_M,     JP_COMM,  JP_DOT,   JP_SLSH,  JP_BSLS,
                                 KC_LWIN,       KC_LALT,     SP_LOW,     KC_BSPC,            KC_ENT,   SP_RAI,      KC_RALT,    KC_APP
    ),
    [_BASE2] = LAYOUT_fw(
        JP_ZKHK,  JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     JP_CIRC,                      JP_YEN,   JP_6,     KC_PSLS,  KC_PAST,  KC_PMNS,  JP_0,     JP_MINS,
        KC_TAB,        JP_Q,     JP_W,     JP_E,     JP_R,     JP_T,     JP_AT,              JP_LBRC,  JP_Y,     KC_P7,    KC_P8,    KC_P9,    KC_PPLS,       KC_BSPC,
        C_ESC,         JP_A,     JP_S,     JP_D,     JP_F,     JP_G,     JP_COLN,            JP_RBRC,  JP_H,     KC_P4,    KC_P5,    KC_P6,    JP_MINS,       KC_ENT,
        KC_LSFT,  KC_LSFT,  JP_Z,     JP_X,     JP_C,     JP_V,     JP_B,                         XXXXXXX,  JP_N,     KC_P1,    KC_P2,    KC_P3,    JP_SLSH,  JP_BSLS,
                                 KC_LWIN,       KC_LALT,     SP_LOW,     KC_BSPC,            KC_ENT,   SP_RAI,      KC_P0,      KC_PDOT
    ),
    [_BASE3] = LAYOUT_fw(
        JP_ZKHK,  JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     JP_CIRC,                      JP_YEN,   JP_6,     JP_7,     JP_8,     JP_9,     JP_0,     KC_MINS,
        KC_TAB,        JP_Q,     JP_W,     JP_E,     JP_R,     JP_T,     JP_AT,              JP_LBRC,  JP_Y,     JP_U,     JP_I,     JP_O,     JP_P,          KC_BSPC,
        C_ESC,         JP_A,     JP_S,     JP_D,     JP_F,     JP_G,     JP_COLN,            JP_RBRC,  JP_H,     JP_J,     JP_K,     JP_L,     JP_MINS,       KC_ENT,
        KC_LSFT,  JP_Z,     JP_X,     JP_C,     JP_V,     JP_B,     XXXXXXX,                      XXXXXXX,  JP_N,     JP_M,     JP_COMM,  JP_DOT,   JP_SLSH,  JP_BSLS,
                                 KC_LWIN,       KC_LALT,     SP_LOW,     KC_BSPC,            KC_ENT,     SP_RAI,      KC_RALT,    KC_APP
    ),
    [_LOWER] = LAYOUT_fw(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,                      KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        JP_EXLM,  JP_DQUO,  JP_HASH,  JP_DLR,   JP_PERC,  JP_TILD,            JP_PIPE,  JP_AMPR,  JP_QUOT,  JP_LPRN,  JP_RPRN,  _______,       JP_EQL,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  JP_AT,    JP_SCLN,  JP_COLN,  JP_LBRC,  JP_RBRC,       KC_BSLS,
        _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,                      _______,  JP_GRV,   JP_PLUS,  JP_ASTR,  JP_LCBR,  JP_RCBR,  KC_PIPE,
                                 _______,       _______,     _______,    _______,            _______,    ADJUST,      _______,    _______
    ),
    [_RAISE] = LAYOUT_fw(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,                      KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     _______,            _______,  JP_6,     JP_7,     JP_8,     JP_9,     JP_0,          KC_DEL,
        _______,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,            _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  JP_SCLN,       JP_COLN,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,                       _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
                                 _______,       _______,     ADJUST,     KC_F12,             _______,    _______,     _______,    _______
    ),
    [_FUNC] = LAYOUT_fw(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                 _______,       _______,     _______,    _______,            _______,    _______,     _______,    _______
    ),
    [_RESERVE1] = LAYOUT_fw(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                 _______,       _______,     _______,    _______,            _______,    _______,     _______,    _______
    ),
    [_RESERVE2] = LAYOUT_fw(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                 _______,       _______,     _______,    _______,            _______,    _______,     _______,    _______
    ),
    [_RESERVE3] = LAYOUT_fw(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                 _______,       _______,     _______,    _______,            _______,    _______,     _______,    _______
    ),
    [_ADJUST] = LAYOUT_fw(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       BASE1,    BASE2,    BASE3,    _______,  _______,  _______,            RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_VAI,  IND_TOG,  RGB_RMOD,      KC_INS,
        KC_CAPS,       AU_TOG,   MU_TOG,   MU_MOD,   MUV_DE,   MUV_IN,   _______,            RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,       VERSION,
        _______,  CK_TOGG,  CK_RST,   CK_DOWN,  CK_UP,    _______,  _______,                      _______,  _______,  _______,  _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,
                                 _______,       _______,     _______,    _______,            _______,    _______,     _______,    _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
        case KC_FN0:
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            return false;
        case KC_FN1: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE1);
            }
            return false;
        case KC_FN2: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE2);
            }
            return false;
        case KC_FN3: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE3);
            }
            return false;
        case IND_TOG: // Toggle LED indicator.
        case KC_FN4:
            if (record->event.pressed) {
                is_led_indicator_enabled = !is_led_indicator_enabled;
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
    switch(get_highest_layer(layer_state|default_layer_state)) {
        // Disable BASE1 indicator. It's dazzling...
        // case _BASE1:
        //     rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_PINK, true);
        //     rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_PINK, true);
        //     break;
        case _BASE2:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_BLUE, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_BLUE, true);
            break;
        case _BASE3:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_YELLOW, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_YELLOW, true);
            break;
        case _LOWER:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_GREEN, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_GREEN, true);
            break;
        case _RAISE:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_CYAN, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_CYAN, true);
            break;
        case _FUNC:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_WHITE, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_WHITE, true);
            break;
        // No Indicator for Reserved layers.
        // case _RESERVE1:
        // case _RESERVE2:
        // case _RESERVE3:
        //     break;
        case _ADJUST:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_RED, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_RED, true);
            break;
        default:
            // No indicator to show effect / animation color.
            break;
    }

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
