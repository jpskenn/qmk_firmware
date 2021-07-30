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
    _2ND,
    _3RD,
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
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   KC_BSLS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,
           KC_TAB,     KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,       KC_BSPC,
           KC_LCTL,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,    KC_ENT,
        KC_LSFT,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_LEFT,  KC_RGHT,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_UP,    KC_SLSH,
        KC_MUTE,  KC_LANG2, KC_LGUI,     KC_LALT,       SP_LOW,        SP_RAI,   KC_BSPC,     SP_RAI,KC_RALT,      KC_RALT,     KC_LEFT,  KC_DOWN,  KC_RGHT,
        KC_VOLD,  KC_VOLU,                                                                                                                KC_VOLD,  KC_VOLU
    ),
    [_2ND] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
           _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,
           _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,     _______,        _______,      _______,  _______,      _______,_______,     _______,    _______,  _______,  _______,
        _______,  _______,                                                                                                                _______,  _______
    ),
    [_3RD] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
           _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,
           _______,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,     _______,        _______,      _______,  _______,      _______,_______,     _______,    _______,  _______,  _______,
        _______,  _______,                                                                                                                _______,  _______
    ),
    [_LOWER] = LAYOUT(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
            KC_ESC,     KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______,  _______,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_INS,
            _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
        _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
        _______,  _______,  _______,     _______,        _______,      _______,  _______,     SP_ADJ,_______,      _______,     _______,  _______,  _______,
        _______,  _______,                                                                                                                _______,  _______
    ),
    [_RAISE] = LAYOUT(
        KC_GRV,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,
            KC_ESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
            _______,    KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,  KC_QUOT,
        _______,  _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_F11,   KC_F12,
        _______,  _______,  _______,     _______,        SP_ADJ,       _______,  _______,      _______,_______,     _______,    _______,  KC_DOWN,  KC_UP,
        _______,  _______,                                                                                                                _______,  _______
    ),
    [_ADJUST] = LAYOUT(
        _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,
            _______,    DF(_BASE),DF(_2ND), DF(_3RD), RESET,    _______,  _______,  _______,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  RGB_RMOD,  _______,
            _______,    AU_TOG,   CK_TOGG,  MU_TOG,   MU_MOD,   _______,  _______,  _______,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,   _______,
        KC_CAPS,  KC_CAPS,  CK_RST,   CK_DOWN,  CK_UP,    MUV_DE,   MUV_IN,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,     _______,        _______,      _______,  _______,      _______,_______,     _______,    _______,  _______,  _______,
        _______,  _______,                                                                                                                _______,  _______
    ),
};

//------------------------------------------------------------------------------
// RGB Light settings
//------------------------------------------------------------------------------
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define JONES_LED_INDICATOR_INDEX 0         // where to start indicator
#define JONES_LED_INDICATOR_COUNT 4         // how many leds used for indicator
#define JONES_LED_INDICATOR_CHANGE_COUNT 1  // how meny leds to change for temporally layer
#define JONES_LED_DIMMER_LEVEL 200          // brightness dimmer

// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_COUNT, HSV_WHITE - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_2nd_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_COUNT, HSV_BLUE - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_3rd_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_COUNT, HSV_YELLOW - JONES_LED_DIMMER_LEVEL}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX + 1 , 1, HSV_MAGENTA - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - JONES_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_CHANGE_COUNT, HSV_RED - JONES_LED_DIMMER_LEVEL}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base_layer,
    my_2nd_layer,
    my_3rd_layer,
    my_caps_layer,
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(4, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(6, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    rgblight_set_layer_state(1, layer_state_cmp(state, _2ND));
    rgblight_set_layer_state(2, layer_state_cmp(state, _3RD));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);

    return true;
}
#endif


//------------------------------------------------------------------------------
// Rotary Encoder
//------------------------------------------------------------------------------
bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;

    // Both encoders hit specific key matrix position when turn knob clockwise or counterclockwise.

    if (index == 0) { // First encoder, Left side : k85, k86
        if (clockwise) {
            key.row = 8;
            key.col = 6;
        } else {
            key.row = 8;
            key.col = 5;
        }
    } else if (index == 1) { // Second encoder, Right side : k95, k96
        if (clockwise) {
            key.row = 9;
            key.col = 6;
        } else {
            key.row = 9;
            key.col = 5;
        }
    }

    uint8_t  layer   = layer_switch_get_layer(key);
    uint16_t keycode = keymap_key_to_keycode(layer, key);

    tap_code16(keycode);

    return true;
}

//------------------------------------------------------------------------------
// Keyboard Initialization
//------------------------------------------------------------------------------
void keyboard_post_init_user(void) {

#ifdef RGBLIGHT_LAYERS
    // Enable the LED layers.
    rgblight_layers = my_rgb_layers;
#endif

#ifdef RGB_DI_PIN
    // disable LED animation
    rgblight_disable();
#endif

#ifdef AUDIO_CLICKY
    // Disable clicky sound on startup for silence.
    clicky_off();
#endif

}
