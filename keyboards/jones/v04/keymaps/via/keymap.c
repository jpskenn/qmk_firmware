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

// #ifdef AUDIO_ENABLE
//     float song_caps_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
//     float song_caps_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);
//     float song_adjust[][2] = SONG(UNICODE_WINDOWS);
// #endif

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
#define C_ESC   LCTL_T(KC_ESC)
#define S_SLSH  RSFT_T(KC_SLSH)
#define S_LEFT  RSFT_T(KC_LEFT)
#define C_QUO   LCTL_T(KC_QUOT)
#define ALT_GRV   LALT(KC_GRV)
#define LOWER   MO(_LOWER)
#define ADJUST  MO(_ADJUST)
#define GUI_JA  LGUI_T(KC_LANG1)
#define GUI_EN  LGUI_T(KC_LANG2)
#define ALT_JA  LALT_T(KC_LANG1)
#define ALT_EN  LALT_T(KC_LANG2)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
            KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,
                KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,KC_RBRC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_BSPC,
                KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   XXXXXXX,KC_QUOT,KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_ENT,
            KC_LSFT,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_B,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
            KC_MUTE,  KC_LALT,  KC_LGUI,  KC_SPC,   KC_SPC, KC_SPC, KC_SPC, KC_SPC,KC_RGUI,XXXXXXX,KC_LANG1,KC_LEFT,KC_DOWN,KC_RGHT,
        KC_VOLD,KC_VOLU,                                                                                                KC_PGDN,KC_PGUP
    ),
    [_LOWER] = LAYOUT(
            KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,
                KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,KC_RBRC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_BSPC,
                KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   XXXXXXX,KC_QUOT,KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_ENT,
            KC_LSFT,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_B,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
            KC_MUTE,  KC_LALT,  KC_LGUI,  KC_SPC,   KC_SPC, KC_SPC, KC_SPC, KC_SPC,KC_RGUI,XXXXXXX,KC_LANG1,KC_LEFT,KC_DOWN,KC_RGHT,
        KC_VOLD,KC_VOLU,                                                                                                KC_PGDN,KC_PGUP
    ),
    [_RAISE] = LAYOUT(
            KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,
                KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,KC_RBRC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_BSPC,
                KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   XXXXXXX,KC_QUOT,KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_ENT,
            KC_LSFT,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_B,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
            KC_MUTE,  KC_LALT,  KC_LGUI,  KC_SPC,   KC_SPC, KC_SPC, KC_SPC, KC_SPC,KC_RGUI,XXXXXXX,KC_LANG1,KC_LEFT,KC_DOWN,KC_RGHT,
        KC_VOLD,KC_VOLU,                                                                                                KC_PGDN,KC_PGUP
    ),
    [_ADJUST] = LAYOUT(
            KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,
                KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,KC_RBRC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,     KC_BSPC,
                KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   XXXXXXX,KC_QUOT,KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_ENT,
            KC_LSFT,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_B,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
            KC_MUTE,  KC_LALT,  KC_LGUI,  KC_SPC,   KC_SPC, KC_SPC, KC_SPC, KC_SPC,KC_RGUI,XXXXXXX,KC_LANG1,KC_LEFT,KC_DOWN,KC_RGHT,
        KC_VOLD,KC_VOLU,                                                                                                KC_PGDN,KC_PGUP
    )
};

//------------------------------------------------------------------------------
// RGB Light settings
//------------------------------------------------------------------------------
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define JONES_LED_INDICATOR_INDEX 0         // where to start indicator
#define JONES_LED_INDICATOR_COUNT 2         // how many leds used for indicator
#define JONES_LED_INDICATOR_CHANGE_COUNT 1  // how meny leds to change color for temporally layer
#define JONES_LED_DIMMER_LEVEL 200          // brightness dimmer

// for Default layer (= Base layer)mmwn
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {JONES_LED_INDICATOR_INDEX , JONES_LED_INDICATOR_COUNT, HSV_WHITE - JONES_LED_DIMMER_LEVEL}
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
    my_caps_layer,
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(4, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);

    return true;
}
#endif


//------------------------------------------------------------------------------
// Rotary Encoder
//------------------------------------------------------------------------------
bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;

    /*
        To provide Dynamic keymap by "VIA" for rotary encoders,
        both encoders hit specific key matrix position when turn clockwise or counterclockwise.
        First encoder(Left):   k85, k86
        Second encoder(Right): k95, k96
    */
    if (index == 0) { /* First encoder, Left side */
        if (clockwise) {
            key.row = 8;
            key.col = 6;
        } else {
            key.row = 8;
            key.col = 5;
        }
    }
    if (index == 1) { /* Second encoder, Right side */
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
