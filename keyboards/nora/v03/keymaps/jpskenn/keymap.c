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
#include "version.h"

#ifdef AUDIO_ENABLE
    // float song_caps_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
    // float song_caps_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);
    // float song_adjust[][2] = SONG(UNICODE_WINDOWS);
#endif

// Defines names for use in layer keycodes and the keymap
enum layer_number {
    _MAC = 0,
    _WIN,
    _NUM,
    _LOWER,
    _RAISE,
    _NUM_LOWER,
    _ADJUST,
};

enum custom_keycodes {
  MAC = SAFE_RANGE,
  WIN,
  GUI_IME,
  VERSION,
};

// Key Macro
// #define ESC_NUM TD(TD_ESC_NUM)
#define ESC_NUM LT(_NUM, KC_ESC)
// #define GRV_NUM LT(_NUM, KC_GRV)
// #define S_CAPS   TD(TD_LSFT_CAPS)
#define SP_LOW  LT(_LOWER, KC_SPC)
#define SP_RAI  LT(_RAISE, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)
#define SP_NLOW LT(_NUM_LOWER, KC_SPC)
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
#define A_GRV   LALT(KC_GRV)
#define CA_SPC  LCA(KC_SPC)
#define LOWER   MO(_LOWER)
#define ADJUST  MO(_ADJUST)
#define NUM     TG(_NUM)
// #define HENKAN  LGUI(KC_GRV)
#define GUI_JA  LGUI_T(KC_LNG1)
#define GUI_EN  LGUI_T(KC_LNG2)
#define ALT_JA  LALT_T(KC_LNG1)
#define ALT_EN  LALT_T(KC_LNG2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_MAC] = LAYOUT(
        ESC_NUM,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   XXXXXXX,  XXXXXXX,  KC_BSLS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  XXXXXXX,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,          KC_BSPC,
        C_ESC,         KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  XXXXXXX,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,       KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     DM_PLY1,  XXXXXXX,  XXXXXXX,  DM_PLY2,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                 KC_LOPT,       KC_LCMD,     SP_LOW,     KC_BSPC,  KC_ESC,   KC_ENT,     SP_RAI,      GUI_IME,    KC_ROPT
    ),
    [_WIN] = LAYOUT(
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                 KC_LWIN,       KC_LALT,     _______,    _______,  _______,  _______,    _______,     A_GRV,      KC_APP
    ),
    [_NUM] = LAYOUT(
        KC_ESC,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSLS,  KC_PSLS,  KC_PSLS,  KC_PAST,  KC_PMNS,  _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,       _______,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P4,    KC_P5,    KC_P6,    XXXXXXX,       _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P1,    KC_P2,    KC_P3,    XXXXXXX,  _______,
                                 _______,       _______,     SP_NLOW,    _______,  _______,  _______,    _______,     KC_P0,      KC_PDOT
    ),
    [_LOWER] = LAYOUT(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______,  _______,  _______,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,       _______,
        _______,       _______,  KC_MS_L,  KC_MS_D,  KC_MS_U,  KC_MS_R,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,       KC_BSLS,
        _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  KC_BTN1,  KC_BTN2,  _______,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
                                 _______,       _______,     _______,    _______,  _______,  _______,    _______,     _______,    _______
    ),
    [_RAISE] = LAYOUT(
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
        KC_ESC,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,  _______,  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,          KC_DEL,
        _______,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,       KC_QUOT,
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
                                 _______,       _______,     _______,    KC_F12,   _______,  _______,    _______,     _______,    _______
    ),
    [_NUM_LOWER] = LAYOUT(
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   XXXXXXX,  XXXXXXX,  KC_BSLS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  XXXXXXX,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,          KC_BSPC,
        C_ESC,         KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  XXXXXXX,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,       KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     DM_PLY1,  XXXXXXX,  XXXXXXX,  DM_PLY2,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                 KC_LOPT,       KC_LCMD,     _______,    KC_BSPC,  KC_ESC,   KC_ENT,     _______,     GUI_IME,    KC_ROPT
    ),
    [_ADJUST] = LAYOUT(
        DM_RSTP,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        DM_RSTP,       MAC,      WIN,      NUM,      _______,  _______,  _______,  _______,  _______,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  RGB_RMOD,      KC_INS,
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,       VERSION,
        KC_CAPS,  _______,  _______,  _______,  _______,  _______,  DM_REC1,  _______,  _______,  DM_REC2,  NUM,      _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,
                                 _______,       _______,     _______,    _______,  _______,  _______,    _______,     _______,    _______
    ),
};

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_MAC);
                rgblight_blink_layer_repeat(0, 400, 5);
            }
            return false;
        case WIN: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WIN);
                rgblight_blink_layer_repeat(1, 400, 5);
            }
            return false;
        case GUI_IME: // Toggle IME, my Mac IME shortcut key dependent.
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_RGUI);
            } else {
                unregister_code(KC_RGUI);

                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    SEND_STRING(SS_LCMD(SS_LALT(SS_TAP(X_SPC))));
                }
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
// Dynamic Macro settings
//------------------------------------------------------------------------------
void dynamic_macro_play_user(int8_t direction) {
    // Revert layer indicator, just after macro played.
    // It returns to base layer. WHY???
    layer_state_set_user(layer_state);
}

#ifndef RGB_MATRIX_ENABLE
    void dynamic_macro_record_start_user(void) {
        rgblight_blink_layer_repeat(8, 250, 3);
    }

    void dynamic_macro_record_end_user(int8_t direction) {
        rgblight_blink_layer_repeat(9, 250, 3);
    }
#endif

//------------------------------------------------------------------------------
// RGB Light settings
//------------------------------------------------------------------------------
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define LED_INDICATOR_INDEX 0         // where to start indicator
#define LED_INDICATOR_COUNT 1         // how many LEDs used for indicator
#define LED_INDICATOR_CHANGE_COUNT 1  // how many LEDs to change for temporally layer
// #define LED_DIMMER_LEVEL 150          // brightness dimmer

// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_mac_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, HSV_WHITE}
);
const rgblight_segment_t PROGMEM my_win_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, HSV_BLUE}
);
const rgblight_segment_t PROGMEM my_num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
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

const rgblight_segment_t PROGMEM my_num_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_CHANGE_COUNT, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_CHANGE_COUNT, HSV_RED}
);

const rgblight_segment_t PROGMEM my_blink1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM my_blink2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, HSV_PINK}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_mac_layer,
    my_win_layer,
    my_num_layer,
    my_caps_layer,
    my_lower_layer,
    my_raise_layer,
    my_num_lower_layer,
    my_adjust_layer,
    my_blink1_layer,
    my_blink2_layer
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    // Set the layer status
    // _LOWERと_NUM_LOWERは同時に押されないので、別々に判定する
    if (state != update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST)) {
        state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    } else {
        state = update_tri_layer_state(state, _NUM_LOWER, _RAISE, _ADJUST);
    }

    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(4, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(6, layer_state_cmp(state, _NUM_LOWER));
    rgblight_set_layer_state(7, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    // rgblight_set_layer_state(0, layer_state_cmp(state, _MAC));
    // rgblight_set_layer_state(1, layer_state_cmp(state, _WIN));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));

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

#ifdef RGBLIGHT_LAYERS
    // Enable the LED layers.
    rgblight_layers = my_rgb_layers;

    // prevent RGB light overrides layer indicator.
    layer_state_set(default_layer_state);
#endif

}
