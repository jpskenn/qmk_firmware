/*
Copyright 2024 Takeshi Nishio

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "version.h"

// recording status flags for "Dynamic Macro"
bool is_dm_rec1 = false;
bool is_dm_rec2 = false;

// list of lighting layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_left_only[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_right_only[];

// Indicator LED settings
#define ONBOARD_LED_INDEX_FIRST 0        // First LED position
#define ONBOARD_LED_INDEX_SECOND 1      // Second LED position
#define ONBOARD_LED_INDEX_THIRD 2       // Third LED position
#define ONBOARD_LED_COUNT_FULL 6        // Number of ALL LEDs, left + right
#define ONBOARD_LED_COUNT_PER_SIDE 3    // Number of LEDs per side

// data to store EEPROM
typedef union {
    uint32_t raw;
    struct {
        // Layer indicator state
        int8_t indicator_state :4;
    };
} user_config_t;

user_config_t user_config;

// layers
enum layer_number {
    _BASE1 = 0,
    _BASE2,
    _BASE3,
    _LOWER1,
    _LOWER2,
    _RAISE1,
    _RAISE2,
    _ADJUST,
};

// custom key codes
enum custom_keycodes {
  BASE1 = SAFE_RANGE,
  BASE2,
  BASE3,
  ADJUST,
  VERSION,
  KEY_WAIT,
  IND_TOG,
};

// key code macros
#define TAB_BASE3   LT(_BASE3, KC_TAB)
#define ZH_BASE3    LT(_BASE3, JP_ZKHK)
#define SP_LOW1     LT(_LOWER1, KC_SPC)
#define SP_RAI1     LT(_RAISE1, KC_SPC)
#define SP_LOW2     LT(_LOWER2, KC_SPC)
#define SP_ADJ      LT(_ADJUST, KC_SPC)

#define SP_SFT      LSFT_T(KC_SPC)
#define BS_SFT      LSFT_T(KC_BSPC)

#define CTL_ESC     LCTL_T(KC_ESC)

#define BASE1       DF(_BASE1)
#define BASE2       DF(_BASE2)
#define BASE3       DF(_BASE3)

#define CMD_LANG1   LGUI_T(KC_LNG1)
#define CMD_LANG2   LGUI_T(KC_LNG2)
#define CTL_LANG1   LCTL_T(KC_LNG1)
#define CTL_LANG2   LCTL_T(KC_LNG2)

#define MAC_SLP     LAG(KC_EJCT)
#define MAC_PSCR    LSG(KC_5)
#define WIN_PSCR    LSG(KC_S)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE1] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        TAB_BASE3,KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        CTL_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     DM_PLY1,  KC_ESC,   DM_PLY2,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          KC_LOPT,  CMD_LANG2,SP_SFT,     SP_LOW1,  KC_MUTE,  BS_SFT,   SP_RAI1,    CMD_LANG1,KC_ROPT
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_BASE2] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |-----------------+---------+---------+  ---------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          _______,  _______,  _______,    _______,  _______,  _______,  _______,    _______,  _______
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_BASE3] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PAST,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSLS,  KC_P4,    KC_P5,    KC_P6,    KC_MINS,  _______,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_EQL,   KC_P1,    KC_P2,    KC_P3,    KC_CALC,
    // |-----------------+---------+---------+  ---------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          _______,  _______,  _______,    _______,  _______,  _______,  _______,    KC_P0,      KC_PDOT
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_LOWER1] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,   KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_INS,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          _______,  _______,  _______,    _______,  _______,  _______,  MO(_ADJUST),_______,    _______
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_LOWER2] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                         _______,  _______,  _______,    _______,  _______,  _______,  _______,    _______,  _______
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_RAISE1] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_MINS,  KC_EQL,   KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  KC_GRV,   KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_UNDS,  KC_PLUS,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,  KC_QUOT,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_TILD,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,  _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,
    // |-----------------+---------+---------+  ---------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          _______,  _______,  _______,    MO(_ADJUST),_______,  _______,  _______,    KC_VOLD,  KC_VOLU
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_RAISE2] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                         _______,  _______,  _______,    _______,  _______,  _______,  _______,    _______,  _______
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_ADJUST] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        KEY_WAIT, BASE1,    BASE2,    BASE3,  _______,  MAC_SLP,    _______,  RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_VAI,  IND_TOG,  RGB_RMOD, _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_CAPS,  MU_TOGG,  MU_NEXT,  AU_NEXT,  AU_PREV,  _______,  _______,  RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,  VERSION,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             AU_TOGG,  CK_TOGG,  CK_DOWN,  CK_UP,    CK_RST,   DM_REC1,  DM_RSTP,  DM_REC2,  _______,  KC_NUM,  KC_PSCR,  KC_SCRL,  KC_PAUS,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          _______,  _______,  _______,    _______,  _______,  _______,  _______,    _______,  _______
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
};

//------------------------------------------------------------------------------
// Rotary Encoder with VIA
//------------------------------------------------------------------------------
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_BASE2] = { ENCODER_CCW_CW(_______, _______) },
    [_BASE3] = { ENCODER_CCW_CW(_______, _______) },
    [_LOWER1] = { ENCODER_CCW_CW(_______, _______) },
    [_LOWER2] = { ENCODER_CCW_CW(_______, _______) },
    [_RAISE1] = { ENCODER_CCW_CW(_______, _______) },
    [_RAISE2] = { ENCODER_CCW_CW(_______, _______) },
    [_ADJUST] = { ENCODER_CCW_CW(_______, _______) },
};
#endif

//------------------------------------------------------------------------------
// Audio
//------------------------------------------------------------------------------
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
    22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
     9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21,
     0,  1,  2,  3,  4,  5,  6,  7,  8
);

//------------------------------------------------------------------------------
// Handle key codes
//------------------------------------------------------------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            return false;
        case BASE1: // Change default layer & write default layer to EEPROM.
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE1);
            }
            return false;
        case BASE2: // Change default layer & write default layer to EEPROM.
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE2);
            }
            return false;
        case BASE3: // Change default layer. If pressed with "Shift", write default layer to EEPROM.
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    set_single_persistent_default_layer(_BASE3);
                    return false;
                }
            }
            return true;
        case DM_REC1: // Toggle recording status
            if (record->event.pressed) {
                is_dm_rec1 = true;
            }
            return true; // continue processing
        case DM_REC2: // Toggle recording status
            if (record->event.pressed) {
                is_dm_rec2 = true;
            }
            return true; // continue processing
        case KEY_WAIT: // Just wait specific time. Nice to use with Dynamic Macro.
            if (record->event.pressed) {
                wait_ms(250);
            }
            return false;
        case IND_TOG: // Toggle LED indicator status
            if (record->event.pressed) {
                switch (user_config.indicator_state) {
                    case 0: // off --> on(Both side)
                        user_config.indicator_state++;
                        rgblight_layers = my_rgb_layers;
                        break;
                    case 1: // both side --> left only
                        user_config.indicator_state++;
                        rgblight_layers = my_rgb_layers_left_only;
                        break;
                    case 2: // left only --> right only
                        user_config.indicator_state++;
                        rgblight_layers = my_rgb_layers_right_only;
                        break;
                    case 3: // right only --> off
                        user_config.indicator_state = 0;
                        rgblight_layers = NULL;
                        rgblight_sethsv_range(HSV_BLACK, ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_FULL);
                        break;
                }
                eeconfig_update_user(user_config.raw); // Write the new status to EEPROM
            }
            return false;
        default:
            break;
    }
    return true;
}

//------------------------------------------------------------------------------
// Dynamic Macro
//------------------------------------------------------------------------------
bool dynamic_macro_play_user(int8_t direction) {
    // Revert layer indicator, just after macro played.
    // It returns to base layer. WHY???
    layer_state_set_user(layer_state);
    return true;
}

#ifdef RGBLIGHT_LAYER_BLINK // RGB Lighting & RGB Layer Blink
    // Blink indicator when start / stop recorging.
    bool dynamic_macro_record_start_user(int8_t direction) {
        rgblight_blink_layer_repeat(9, 250, 3);//TODO マクロ記録中、ずっとブリンクならんの？
        return true;
    }

    bool dynamic_macro_record_end_user(int8_t direction) {
        //TODO is_dm_rec1,2を使って、ダイナミックマクロ記録中に、ずっとBlinkさせたりできないか？
        is_dm_rec1 = false;
        is_dm_rec2 = false;
        rgblight_blink_layer_repeat(10, 250, 3);
        return true;
    }
#endif

//------------------------------------------------------------------------------
// RGB Light
//------------------------------------------------------------------------------

// ---------- Both side ---------
// for Base layer: All
const rgblight_segment_t PROGMEM my_base1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_FULL, HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_base2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_FULL, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_base3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_FULL, HSV_YELLOW}
);

// for locking status: change Third
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD, 1, HSV_MAGENTA},
    {ONBOARD_LED_INDEX_THIRD + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD, 1, HSV_RED},
    {ONBOARD_LED_INDEX_THIRD + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_RED}
);

// for temporal(lower, raise) layer: change Second
const rgblight_segment_t PROGMEM my_lower1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_GREEN},
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_lower2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_CHARTREUSE},
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_raise1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_CYAN},
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_raise2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_PURPLE},
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_RED},
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_RED}
);

// Blink: All
const rgblight_segment_t PROGMEM my_blink1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_FULL, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM my_blink2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_FULL, HSV_PINK}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_base1_layer,
    my_base2_layer,
    my_base3_layer,
    my_caps_layer,
    my_scroll_lock_layer,
    my_lower1_layer,
    my_lower2_layer,
    my_raise1_layer,
    my_raise2_layer,
    my_adjust_layer,
    my_blink1_layer,
    my_blink2_layer
);

// ---------- Left side only ---------
// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base1_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_PER_SIDE, HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_base2_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_PER_SIDE, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_base3_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_PER_SIDE, HSV_YELLOW}
);

// for locking status
const rgblight_segment_t PROGMEM my_caps_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD, 1, HSV_RED}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_lower1_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_lower2_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_raise1_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_raise2_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_adjust_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND, 1, HSV_RED}
);

// Blink: all
const rgblight_segment_t PROGMEM my_blink1_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_PER_SIDE, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM my_blink2_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_PER_SIDE, HSV_PINK}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers_left_only[] = RGBLIGHT_LAYERS_LIST(
    my_base1_layer_left_only,
    my_base2_layer_left_only,
    my_base3_layer_left_only,
    my_caps_layer_left_only,
    my_scroll_lock_layer_left_only,
    my_lower1_layer_left_only,
    my_lower2_layer_left_only,
    my_raise1_layer_left_only,
    my_raise2_layer_left_only,
    my_adjust_layer_left_only,
    my_blink1_layer_left_only,
    my_blink2_layer_left_only
);

// ---------- Right side only ---------
// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base1_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, ONBOARD_LED_COUNT_PER_SIDE, HSV_WHITE}
);

const rgblight_segment_t PROGMEM my_base2_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, ONBOARD_LED_COUNT_PER_SIDE, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_base3_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, ONBOARD_LED_COUNT_PER_SIDE, HSV_YELLOW}
);

// for locking status
const rgblight_segment_t PROGMEM my_caps_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_RED}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_lower1_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_lower2_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_raise1_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_raise2_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_PURPLE}
);

const rgblight_segment_t PROGMEM my_adjust_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_SECOND + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM my_blink1_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, ONBOARD_LED_COUNT_PER_SIDE, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM my_blink2_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, ONBOARD_LED_COUNT_PER_SIDE, HSV_PINK}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers_right_only[] = RGBLIGHT_LAYERS_LIST(
    my_base1_layer_right_only,
    my_base2_layer_right_only,
    my_base3_layer_right_only,
    my_caps_layer_right_only,
    my_scroll_lock_layer_right_only,
    my_lower1_layer_right_only,
    my_lower2_layer_right_only,
    my_raise1_layer_right_only,
    my_raise2_layer_right_only,
    my_adjust_layer_right_only,
    my_blink1_layer_right_only,
    my_blink2_layer_right_only
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    // NOTE:
    // jpskenn個人としては快適な入力のため「update_tri_layer」を使用しているが、
    // この一般向けファームウェアでは、キーマップを後から自由に書き換えさせることを目的としているため、
    // mo(n)の移動先をtransparentにしなかった場合、「update_tri_layer」と衝突してレイヤー移動できなくなる可能性がある。
    // その状態を回避するため、快適性よりも安定性を重視して、「update_tri_layer」は使用しないこととする。
    // Set the layer status
    // if (state != update_tri_layer_state(state, _LOWER1, _RAISE1, _ADJUST)) {
    //     state = update_tri_layer_state(state, _LOWER1, _RAISE1, _ADJUST);
    // } else {
    //     state = update_tri_layer_state(state, _LOWER2, _RAISE1, _ADJUST);
    // }

    rgblight_set_layer_state(5, layer_state_cmp(state, _LOWER1));
    rgblight_set_layer_state(6, layer_state_cmp(state, _LOWER2));
    rgblight_set_layer_state(7, layer_state_cmp(state, _RAISE1));
    rgblight_set_layer_state(8, layer_state_cmp(state, _RAISE2));
    rgblight_set_layer_state(9, layer_state_cmp(state, _ADJUST));

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
    rgblight_set_layer_state(4, led_state.scroll_lock);

    return true;
}

// ------------------------------------------------------------------------------
// Keyboard Initialization
// ------------------------------------------------------------------------------
void keyboard_post_init_user(void) {
    // Read the user config from EEPROM
    user_config.raw = eeconfig_read_user();

    // Enable the LED layers as stored state
    switch (user_config.indicator_state) {
        case 0: // off
            rgblight_layers = NULL;
            rgblight_sethsv_range(HSV_BLACK, 0, 2);
            break;
        case 1: // Brightness: High
            rgblight_layers = my_rgb_layers;
            break;
        case 2: // Brightness: Slightly
            rgblight_layers = my_rgb_layers_left_only;
            break;
        case 3: // Brightness: Middle
            rgblight_layers = my_rgb_layers_right_only;
            break;
        default:
            rgblight_layers = NULL;
            rgblight_sethsv_range(HSV_BLACK, 0, 2);
            break;
    }

    // prevent RGB light overrides layer indicator.
    layer_state_set(default_layer_state);
}

// ------------------------------------------------------------------------------
// EEPROM Initialization, EEPROM is getting reset!
// ------------------------------------------------------------------------------
void eeconfig_init_user(void) {
    // write user configuration to EEPROM
    user_config.raw = 0;
    user_config.indicator_state = 1; // Layer indicator LED state: 0 = on(brightness = high)
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
}
