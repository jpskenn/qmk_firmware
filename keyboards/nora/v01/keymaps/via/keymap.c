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
    _BASE1 = 0,
    _BASE2,
    _BASE3,
    _LOWER,
    _RAISE,
    _FN,
    _ADJUST,
};

// Key Macro
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)
#define BASE1  DF(_BASE1)
#define BASE2  DF(_BASE2)
#define BASE3  DF(_BASE3)
#define FN      MO(_FN)
#define ADJUST  MO(_ADJUST)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE1] = LAYOUT(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_EQL,   KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_PSLS,  KC_PAST,  KC_PMNS,  KC_PPLS,
           KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_BSPC,     KC_P7,    KC_P8,    KC_P9,
           KC_LCTL,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,    KC_ENT,      KC_P4,    KC_P5,    KC_P6,
        KC_LSFT,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_UP,    KC_P1,    KC_P2,    KC_P3,
        XXXXXXX,  XXXXXXX,    KC_LOPT,     KC_LCMD,      SP_LOW,             SP_RAI,         KC_RGUI,    KC_ROPT,     KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_P0,    KC_PDOT
    ),
    [_BASE2] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
           _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,     _______,  _______,  _______,
           _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,     _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,    _______,     _______,      _______,            _______,        _______,     _______,    _______,  _______,  _______,  _______,  _______
    ),
    [_BASE3] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
           _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,     _______,  _______,  _______,
           _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,     _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,    _______,     _______,      _______,            _______,        _______,     _______,    _______,  _______,  _______,  _______,  _______
    ),
    [_LOWER] = LAYOUT(
        FN,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
           KC_ESC,     KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,    KC_INS,      _______,  _______,  _______,
           _______,    _______,  _______,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,     KC_LBRC,     KC_RBRC,  KC_BSLS,  _______,  _______,  _______,
        _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,  _______,  _______,  _______,
        _______,  _______,    _______,     _______,      _______,            ADJUST,         _______,    _______,     _______,  _______,  _______,  _______,  _______
    ),
    [_RAISE] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,
           KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,       KC_DEL,      _______,  _______,  _______,
           _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,    KC_QUOT,     _______,  _______,  _______,
        _______,  _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,  _______,  _______,  _______,
        KC_F11,   KC_F12,     _______,     _______,      ADJUST,              _______,       _______,    _______,     _______,  _______,  _______,  _______,  _______
    ),
    [_FN] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
           _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,     _______,  _______,  _______,
           _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,    _______,     _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,    _______,     _______,      _______,            _______,        _______,     _______,    _______,  _______,  _______,  _______,  _______
    ),
    [_ADJUST] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,
           _______,    BASE1,    BASE2,   BASE3,     _______,  _______,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  RGB_RMOD,   _______,     _______,  _______,  _______,
           _______,    _______,  _______,  _______,  _______,  _______,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,    _______,     _______,  _______,  _______,
        KC_CAPS,  KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,    _______,     _______,      _______,            _______,        _______,    _______,     _______,  _______,  _______,  _______,  _______
    ),
};

//------------------------------------------------------------------------------
// RGB Light settings
//------------------------------------------------------------------------------
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define LED_INDICATOR_INDEX 0         // where to start indicator
#define LED_INDICATOR_COUNT 1         // how many LEDs used for indicator
#define LED_INDICATOR_CHANGE_COUNT 1  // how many LEDs to change for temporally layer

// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, HSV_WHITE}
);
const rgblight_segment_t PROGMEM my_base2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, HSV_BLUE}
);
const rgblight_segment_t PROGMEM my_base3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, HSV_YELLOW}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX + 1 , 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_CHANGE_COUNT, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_CHANGE_COUNT, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_CHANGE_COUNT, HSV_PINK}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_CHANGE_COUNT, HSV_RED}
);

const rgblight_segment_t PROGMEM my_blink_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_CHANGE_COUNT, HSV_OFF}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base1_layer,
    my_base2_layer,
    my_base3_layer,
    my_caps_layer,
    my_lower_layer,
    my_raise_layer,
    my_fn_layer,
    my_adjust_layer
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(4, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(6, layer_state_cmp(state, _FN));
    rgblight_set_layer_state(7, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE1));
    rgblight_set_layer_state(1, layer_state_cmp(state, _BASE2));
    rgblight_set_layer_state(2, layer_state_cmp(state, _BASE3));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);

    return true;
}
#endif

//------------------------------------------------------------------------------
// Keyboard Initialization
//------------------------------------------------------------------------------
void keyboard_post_init_user(void) {

#ifdef RGB_DI_PIN
  #ifdef RGBLIGHT_LAYERS
    // Enable the LED layers.
    rgblight_layers = my_rgb_layers;

    // prevent RGB light overrides layer indicator.
    layer_state_set(default_layer_state);
  #endif
#endif

}
