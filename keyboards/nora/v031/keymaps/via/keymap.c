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
    [_BASE1] = LAYOUT(
        KC_ESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   XXXXXXX,  XXXXXXX,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,   KC_EQL,
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  XXXXXXX,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,          KC_BSPC,
        C_ESC,         KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  XXXXXXX,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,       KC_ENT,
        KC_LSFT,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  KC_MUTE,  KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  FUNC,
                                 KC_LOPT,       KC_LCMD,     SP_LOW,     KC_BSPC,  FUNC,     KC_ENT,     SP_RAI,      KC_RGUI,    KC_ROPT
    ),
    [_BASE2] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                 KC_LWIN,       KC_LALT,     _______,    _______,  _______,  _______,    _______,     KC_RALT,    KC_APP
    ),
    [_BASE3] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_BSLS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                 _______,       _______,     _______,    _______,  _______,  _______,    _______,     _______,    _______
    ),
    [_LOWER] = LAYOUT(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______,  _______,  _______,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,       KC_BSLS,
        _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
                                 _______,       _______,     _______,    _______,  _______,  _______,    ADJUST,      _______,    _______
    ),
    [_RAISE] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,  _______,  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,          KC_DEL,
        _______,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,       KC_QUOT,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
                                 _______,       _______,     ADJUST,     KC_F12,   _______,  _______,    _______,     _______,    _______
    ),
    [_FUNC] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                 _______,       _______,     _______,    _______,  _______,  _______,    _______,     _______,    _______
    ),
    [_ADJUST] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       BASE1,    BASE2,    BASE3,    _______,  _______,  _______,  _______,  RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_VAI,  IND_TOG,  RGB_RMOD,      KC_INS,
        KC_CAPS,       AU_TOGG,  MU_TOGG,  MU_NEXT,  AU_PREV,  AU_NEXT,  _______,  _______,  RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,       VERSION,
        _______,  CK_TOGG,  CK_RST,   CK_DOWN,  CK_UP,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,
                                 _______,       _______,     _______,    _______,  _______,  _______,    _______,     _______,    _______
    ),
};

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case BASE1: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE1);
            }
            return false;
        case BASE2: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE2);
            }
            return false;
        case BASE3: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE3);
            }
            return false;
        case IND_TOG: // Toggle LED indicator.
            if (record->event.pressed) {
                is_led_indicator_enabled = !is_led_indicator_enabled;
            }
            return false;
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

//------------------------------------------------------------------------------
// RGB Matrix settings
//------------------------------------------------------------------------------
#ifdef RGB_MATRIX_ENABLE

bool rgb_matrix_indicators_user(void) {
    // Indicator On / Off control
    if(!is_led_indicator_enabled) {
        return false;
    }

    // Layers
    switch(get_highest_layer(layer_state|default_layer_state)) {
        // Disable indicator on BASE1. It's dazzling...
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
        case _ADJUST:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_RED, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_RED, true);
            break;
        default:
            // Do nothing to enable effect / animation color.
            break;
    }

    // CAPS
    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_MAGENTA, true);
    }

    return true;
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
