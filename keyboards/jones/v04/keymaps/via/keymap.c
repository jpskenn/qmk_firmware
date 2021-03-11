/* Copyright 2020 Takeshi Nishio
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
    _FUNC,
    _ADJUST,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  AAA = SAFE_RANGE,
};

// Key Macro
// #define ESC_NUM TD(TD_ESC_NUM)
// #define ESC_NUM LT(_NUM, KC_ESC)
// #define S_CAPS   TD(TD_LSFT_CAPS)
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)
// #define BS_RAI  LT(_RAISE, KC_BSPC)
// #define SP_NRAI LT(_NUM_LOWER, KC_SPC)
// #define BS_NRAI LT(_NUM_LOWER, KC_BSPC)
// #define SP_SFT  MT(MOD_LSFT, KC_SPC)
#define C_ESC   LCTL_T(KC_ESC)
// #define C_SPC   LCTL(KC_SPC)
// #define C_SLSH  RCTL_T(KC_SLSH)
#define S_SLSH  RSFT_T(KC_SLSH)
#define S_LEFT  RSFT_T(KC_LEFT)
// #define CT_E    LCTL(KC_E)
// #define CT_A    LCTL(KC_A)
#define C_QUO   LCTL_T(KC_QUOT)
#define ALT_GRV   LALT(KC_GRV)
#define LOWER   MO(_LOWER)
#define ADJUST  MO(_ADJUST)
// #define NUM     TG(_NUM)
// #define HENKAN  LGUI(KC_GRV)
#define GUI_JA  LGUI_T(KC_LANG1)
#define GUI_EN  LGUI_T(KC_LANG2)
#define ALT_JA  LALT_T(KC_LANG1)
#define ALT_EN  LALT_T(KC_LANG2)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_all(
        KC_ESC,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSLS,KC_GRV,
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,    KC_LBRC,KC_RBRC,
        C_ESC,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_MINS,KC_ENT,     KC_UP,  C_QUO,
        KC_LSFT,KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT,S_SLSH, KC_LEFT,KC_DOWN,KC_RGHT,
        XXXXXXX,XXXXXXX,ALT_JA, GUI_EN,        SP_LOW,         SP_RAI,          KC_RGUI,KC_RALT,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX
    ),
    [_LOWER] = LAYOUT_all(
        _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_ESC,     KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,     _______,_______,
        _______,    KC_PSCR, KC_SLCK,KC_PAUS,_______,_______,KC_GRV, KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,KC_BSLS,    KC_HOME,KC_VOLD,
        _______,_______,_______,_______,_______,_______,_______,KC_TILD,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,KC_END, _______,
        _______,_______,KC_APP, _______,        _______,        SP_ADJ,         _______,_______,_______,_______,_______,_______
    ),
    [_RAISE] = LAYOUT_all(
        _______,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_DEL,
        KC_ESC,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_DEL,     _______,_______,
        _______,    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_SCLN,KC_QUOT,    KC_PGUP,_______,
        _______,_______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_HOME,KC_PGDN,KC_PGUP,KC_END, KC_COLN,KC_DQUO,KC_PGDN,_______,
        _______,_______,KC_F11, KC_F12,         SP_ADJ,         _______,        _______,_______,_______,_______,_______,_______
    ),
    [_FUNC] = LAYOUT_all(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,    _______,_______,_______,RESET,  _______,RGB_HUI,RGB_SAI,RGB_VAI,_______,RGB_RMOD,_______,   _______,_______,
        _______,    AU_TOG, CK_TOGG,MU_TOG, MU_MOD, _______,RGB_HUD,RGB_SAD,RGB_VAD,RGB_TOG,RGB_MOD,_______,    _______,_______,
        KC_CAPS,_______,CK_RST, CK_DOWN,CK_UP  ,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,        _______,        _______,        _______,_______,_______,_______,_______,_______
    ),
    [_ADJUST] = LAYOUT_all(
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,_______,
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,    _______,_______,
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
        _______,_______,_______,_______,        _______,        _______,        _______,_______,_______,_______,_______,_______
    )
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         // case MAC: // Change default ayer --> Write to EEPROM
//         //     if (record->event.pressed) {
//         //         set_single_persistent_default_layer(_MAC);
//         //     }
//         //     return false;
//         //     break;
//         // case WIN: // Change default ayer --> Write to EEPROM
//         //     if (record->event.pressed) {
//         //         set_single_persistent_default_layer(_WIN);
//         //     }
//         //     return false;
//         //     break;
//         case M_PSCR: // Mac's advanced screen capture
//             switch(biton32(default_layer_state)) {
//                 case _WIN:
//                     if (record->event.pressed) {
//                         tap_code(KC_PSCR);
//                     }
//                     break;
//                 default:
//                     if (record->event.pressed) {
//                         tap_code16(LSFT(LGUI(KC_5)));
//                     }
//                     break;
//             }
//             return false;
//             break;
//         default:
//             break;
//     }
//     return true;
// }

//------------------------------------------------------------------------------
// RGB Light settings
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define JONES_LED_INDICATOR_INDEX 0         // where to start indicator
#define JONES_LED_INDICATOR_COUNT 2         // how many leds for indicator
#define JONES_LED_INDICATOR_CHANGE_COUNT 1  // how meny leds to change color for temporally layer
#define JONES_LED_DIMMER_LEVEL 220          // brightness dimmer

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
    // rgblight_set_effect_range(4, 8);
}

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    // state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    rgblight_set_layer_state(4, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(7, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);

    return true;
}
#endif


//------------------------------------------------------------------------------
// Rotary Encoder
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder, Right side */
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    if (index == 1) { /* Second encoder, Left side */
        switch(biton32(layer_state)) {
            case _LOWER:
                if (clockwise) {
                    rgblight_decrease_hue();
                } else {
                    rgblight_increase_hue();
                }
                break;
            case _RAISE:
                if (clockwise) {
                    rgblight_decrease_val();
                } else {
                    rgblight_increase_val();
                }
                break;
            case _ADJUST:
                if (clockwise) {
                    rgblight_step_reverse();
                } else {
                    rgblight_step();
                }
                break;
            default:
                if (clockwise) {
                    tap_code(KC_VOLD);
                } else {
                    tap_code(KC_VOLU);
                }
                break;
        }
    }
}
