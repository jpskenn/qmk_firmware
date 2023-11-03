/* Copyright 2023 Takeshi Nishio
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

// list of lighting layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_low[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_middle[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_high[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_max[];

// Data to store EEPROM
typedef union {
    uint32_t raw;
    struct {
        // Layer indicator state
        int8_t indicator_state :4; // Two state: 0 off, 1 on
    };
} user_config_t;

user_config_t user_config;

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

enum custom_keycodes {
  BASE1 = SAFE_RANGE,
  BASE2,
  BASE3,
  ADJUST,
  VERSION,
  IND_TOG,
};

#define BASE1   DF(_BASE1)
#define BASE2   DF(_BASE2)
#define BASE3   DF(_BASE3)
#define LOWER1  MO(_LOWER1)
#define LOWER2  MO(_LOWER2)
#define RAISE1  MO(_RAISE1)
#define RAISE2  MO(_RAISE2)
#define ADJUST  MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE1] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   KC_BSLS,  KC_MINS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_LCTL,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     XXXXXXX,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_ENT,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  XXXXXXX,  XXXXXXX,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        XXXXXXX,  XXXXXXX,  KC_LWIN,    KC_LALT,    KC_SPC,         LOWER1,   XXXXXXX,  RAISE1,   KC_SPC,         KC_RALT,    KC_APP,     XXXXXXX,  XXXXXXX,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_BASE2] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   KC_BSLS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_LCTL,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     XXXXXXX,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_ENT,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_LSFT,  KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     XXXXXXX,  XXXXXXX,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        XXXXXXX,  XXXXXXX,  KC_LWIN,    KC_LALT,    KC_SPC,         LOWER1,   XXXXXXX,  RAISE1,   KC_SPC,         KC_RALT,    KC_APP,     XXXXXXX,  XXXXXXX,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_BASE3] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,    _______,    _______,        _______,  _______,  _______,  _______,        _______,    _______,    _______,  _______,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_LOWER1] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,   _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_ESC,       KC_EXLM,   KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_TILD,  KC_PIPE,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_INS,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,    _______,    _______,        _______,  _______,  ADJUST,   _______,         _______,    _______,    _______,  _______,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_LOWER2] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,    _______,    _______,        _______,  _______,  _______,  _______,        _______,    _______,    _______,  _______,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_RAISE1] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,   _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_ESC,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,   _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,  KC_QUOT,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F12,   _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,    _______,    _______,        ADJUST,   _______,  _______,  _______,        _______,    _______,    _______,  _______,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        ),
    [_RAISE2] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,    _______,    _______,        _______,  _______,  _______,  _______,        _______,    _______,    _______,  _______,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_ADJUST] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,       BASE1,    BASE2,    BASE3,    _______,  _______,  _______,  RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_VAI,  IND_TOG,  RGB_RMOD, _______,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_CAPS,       _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,  VERSION,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,    _______,    _______,        _______,  _______,  _______,  _______,        _______,    _______,    _______,  _______,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
};

//------------------------------------------------------------------------------
// Rotary Encoder with VIA
//------------------------------------------------------------------------------
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][ENCODERS][2] = {
    [_BASE1] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_BASE2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_BASE3] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_LOWER1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_LOWER2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_RAISE1] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_RAISE2] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_ADJUST] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
};
#endif

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            return false;
        case BASE1: // Change default layer.
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // If pressed with "Shift" key, write base layer to EEPROM.
                    set_single_persistent_default_layer(_BASE1);
                    return false;
                }
            }
            return true;
        case BASE2: // Change default layer.
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // If pressed with "Shift" key, write base layer to EEPROM.
                    set_single_persistent_default_layer(_BASE2);
                    return false;
                }
            }
            return true;
        case BASE3: // Change default layer.
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    // If pressed with "Shift" key, write base layer to EEPROM.
                    set_single_persistent_default_layer(_BASE3);
                    return false;
                }
            }
            return true;
        case IND_TOG: // Toggle LED indicator status
            if (record->event.pressed) {
                switch (user_config.indicator_state) {
                    case 0: // off --> on(Brightness High)
                        user_config.indicator_state++;
                        rgblight_layers = my_rgb_layers;
                        break;
                    case 1: // change brightness from High to Slightly
                        user_config.indicator_state++;
                        rgblight_layers = my_rgb_layers_dimmer_low;
                        break;
                    case 2: // change brightness from Slightly to Middle
                        user_config.indicator_state++;
                        rgblight_layers = my_rgb_layers_dimmer_middle;
                        break;
                    case 3: // change brightness from Middle to Low
                        user_config.indicator_state++;
                        rgblight_layers = my_rgb_layers_dimmer_high;
                        break;
                    case 4: // change brightness from Low to Darkest
                        user_config.indicator_state++;
                        rgblight_layers = my_rgb_layers_dimmer_max;
                        break;
                    case 5: // Darkest --> off
                        user_config.indicator_state = 0;
                        rgblight_layers = NULL;
                        rgblight_sethsv_range(HSV_BLACK, 0, 2);
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
// RGB Light settings
//------------------------------------------------------------------------------
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define ONBOARD_LED_INDICATOR_INDEX 0         // Where to start indicator.
#define ONBOARD_LED_INDICATOR_COUNT 2         // How many LEDs used for indicator.
#define ONBOARD_LED_INDICATOR_CHANGE_COUNT 1  // How many LEDs to change for temporally layer.
#define ONBOARD_LED_INDICATOR_DIMMER_MIN 104     // dimmer level minimum(=default), default, high brightness
#define ONBOARD_LED_INDICATOR_DIMMER_LOW 136     // dimmer level low, slightly bright
#define ONBOARD_LED_INDICATOR_DIMMER_MIDDLE 168 // dimmer level middle, moderate
#define ONBOARD_LED_INDICATOR_DIMMER_HIGH 200   // dimmer level high, darker
#define ONBOARD_LED_INDICATOR_DIMMER_MAX 232    // dimmer level max, darkest


// ---------- Brightness: High ---------
// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_WHITE - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_base2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_BLUE - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_base3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_YELLOW - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

// for locking status
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_MAGENTA - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_lower1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_lower2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_raise1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_raise2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_MIN}
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
    my_adjust_layer
);

// ---------- Brightness: Slightly Bright ---------
// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base1_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_WHITE - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_base2_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_BLUE - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_base3_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_YELLOW - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

// for locking status
const rgblight_segment_t PROGMEM my_caps_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_MAGENTA - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_lower1_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_lower2_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_raise1_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_raise2_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_adjust_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_low[] = RGBLIGHT_LAYERS_LIST(
    my_base1_layer_dimmer_low,
    my_base2_layer_dimmer_low,
    my_base3_layer_dimmer_low,
    my_caps_layer_dimmer_low,
    my_scroll_lock_layer_dimmer_low,
    my_lower1_layer_dimmer_low,
    my_lower2_layer_dimmer_low,
    my_raise1_layer_dimmer_low,
    my_raise2_layer_dimmer_low,
    my_adjust_layer_dimmer_low
);

// ---------- Brightness: Middle ---------
// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base1_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_WHITE - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_base2_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_BLUE - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_base3_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_YELLOW - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

// for locking status
const rgblight_segment_t PROGMEM my_caps_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_MAGENTA - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_lower1_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_lower2_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_raise1_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_raise2_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_adjust_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_middle[] = RGBLIGHT_LAYERS_LIST(
    my_base1_layer_dimmer_middle,
    my_base2_layer_dimmer_middle,
    my_base3_layer_dimmer_middle,
    my_caps_layer_dimmer_middle,
    my_scroll_lock_layer_dimmer_middle,
    my_lower1_layer_dimmer_middle,
    my_lower2_layer_dimmer_middle,
    my_raise1_layer_dimmer_middle,
    my_raise2_layer_dimmer_middle,
    my_adjust_layer_dimmer_middle
);

// ---------- Brightness: Low ---------
// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base1_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_WHITE - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_base2_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_BLUE - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_base3_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_YELLOW - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

// for locking status
const rgblight_segment_t PROGMEM my_caps_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_MAGENTA - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_lower1_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_lower2_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_raise1_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_raise2_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_adjust_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_high[] = RGBLIGHT_LAYERS_LIST(
    my_base1_layer_dimmer_high,
    my_base2_layer_dimmer_high,
    my_base3_layer_dimmer_high,
    my_caps_layer_dimmer_high,
    my_scroll_lock_layer_dimmer_high,
    my_lower1_layer_dimmer_high,
    my_lower2_layer_dimmer_high,
    my_raise1_layer_dimmer_high,
    my_raise2_layer_dimmer_high,
    my_adjust_layer_dimmer_high
);

// ---------- Brightness: Darkest ---------
// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base1_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_WHITE - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_base2_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_BLUE - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_base3_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_YELLOW - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

// for locking status
const rgblight_segment_t PROGMEM my_caps_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_MAGENTA - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX + 1 , 1, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_lower1_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_lower2_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_raise1_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_raise2_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_adjust_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_max[] = RGBLIGHT_LAYERS_LIST(
    my_base1_layer_dimmer_max,
    my_base2_layer_dimmer_max,
    my_base3_layer_dimmer_max,
    my_caps_layer_dimmer_max,
    my_scroll_lock_layer_dimmer_max,
    my_lower1_layer_dimmer_max,
    my_lower2_layer_dimmer_max,
    my_raise1_layer_dimmer_max,
    my_raise2_layer_dimmer_max,
    my_adjust_layer_dimmer_max
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
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
#endif

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
            rgblight_layers = my_rgb_layers_dimmer_low;
            break;
        case 3: // Brightness: Middle
            rgblight_layers = my_rgb_layers_dimmer_middle;
            break;
        case 4: // Brightness: Low
            rgblight_layers = my_rgb_layers_dimmer_high;
            break;
        case 5: // Brightness: Darkest
            rgblight_layers = my_rgb_layers_dimmer_max;
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
    user_config.indicator_state = 1; // Layer indicator LED state: 1 = on ( brightness: High)
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
}
