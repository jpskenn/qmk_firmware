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
#include "keymap_japanese.h"

// recording status flags for "Dynamic Macro"
bool is_dm_rec1 = false;
bool is_dm_rec2 = false;

// list of lighting layers
const rgblight_segment_t* const PROGMEM my_rgb_layers[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_low[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_middle[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_high[];
const rgblight_segment_t* const PROGMEM my_rgb_layers_dimmer_max[];

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
    // _LOWER3,
    _RAISE1,
    // _RAISE2,
    // _RAISE3,
    _ADJUST,
};

// custom key codes
enum custom_keycodes {
  BASE1 = SAFE_RANGE,
  BASE2,
  BASE3,
  ADJUST,
  VERSION,
  GUI_IME,
  KEY_WAIT,
  IND_TOG,
};

// key code macros
#define ESC_BASE3 LT(_BASE3, KC_ESC)
#define ZH_BASE3 LT(_BASE3, JP_ZKHK)
#define SP_LOW1  LT(_LOWER1, KC_SPC)
#define SP_RAI1  LT(_RAISE1, KC_SPC)
#define SP_LOW2  LT(_LOWER2, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)

#define SP_SFT  LSFT_T(KC_SPC)
#define BS_SFT  LSFT_T(KC_BSPC)

#define CTL_ESC   LCTL_T(KC_ESC)

#define BASE1   DF(_BASE1)
#define BASE2   DF(_BASE2)
#define NUMERIC TG(_BASE3)

// #define ALT_GRV   LALT(KC_GRV)
#define GUI_LANG1  LGUI_T(KC_LNG1)
#define GUI_LANG2  LGUI_T(KC_LNG2)
#define ALT_LANG1  LALT_T(KC_LNG1)
#define ALT_LANG2  LALT_T(KC_LNG2)

#define MAC_SLP LAG(KC_EJCT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE1] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        ESC_BASE3,KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   KC_BSLS,  KC_MINS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        CTL_ESC,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     DM_PLY1,  XXXXXXX,  DM_PLY2,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        XXXXXXX,  XXXXXXX,  KC_LOPT,    GUI_LANG2,  SP_SFT,         SP_LOW1,  KC_BTN1,  BS_SFT,   SP_RAI1,        GUI_LANG1,  KC_ROPT,    XXXXXXX,  XXXXXXX,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,   _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_BASE2] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        ESC_BASE3,KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   KC_BSLS,  KC_MINS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        CTL_ESC,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     DM_PLY1,  XXXXXXX,  DM_PLY2,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        XXXXXXX,  XXXXXXX,  KC_LWIN,    ALT_LANG2,  SP_SFT,         SP_LOW1,  KC_BTN1,  BS_SFT,   SP_RAI1,        ALT_LANG1,  KC_APP,     XXXXXXX,  XXXXXXX,
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
        KC_ESC,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSLS,  KC_PSLS,  KC_PAST,  KC_PMNS,  KC_PMNS,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  _______,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  _______,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P1,    KC_P2,    KC_P3,    _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,    _______,    _______,        SP_LOW2,  _______,  _______,  _______,        KC_P0,      KC_PDOT,    _______,  _______,
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
        KC_TILD,       KC_EXLM,   KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_TILD,  KC_PIPE,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_PLUS,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  _______,
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
    [_LOWER2] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_GRV,   KC_BSLS,  KC_MINS,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_TAB,        KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        CTL_ESC,       KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     DM_PLY1,  _______,  DM_PLY2,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        XXXXXXX,  XXXXXXX,  KC_LOPT,    GUI_LANG2,  SP_SFT,         _______,  KC_BTN1,  KC_BTN2,  SP_RAI1,        GUI_LANG1,  KC_ROPT,    XXXXXXX,  XXXXXXX,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    // [_LOWER3] = LAYOUT(
    // // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    //     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
    //     _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
    //     _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
    //     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
    //     _______,  _______,  _______,    _______,    _______,        _______,  _______,  _______,  _______,        _______,    _______,    _______,  _______,
    // // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
    //     _______,  _______,                                                    _______,                                                    _______,  _______,
    // // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
    //                                                                 _______,  _______,  _______,
    // // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
    //                                                                           _______
    // // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    // ),
    [_RAISE1] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,   _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_GRV,        KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,       KC_GRV,   KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,  KC_QUOT,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        _______,  KC_VOLD,  KC_VOLU,  KC_LCBR,  KC_RCBR,  KC_PIPE,  _______,  _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  _______,  _______,    _______,    _______,        _______,  _______,  _______,  _______,        KC_VOLD,    KC_VOLU,    _______,  _______,
    // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
                                                                              _______,
    // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
                                                                    _______,  _______,  _______,
    // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
                                                                              _______
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    // [_RAISE2] = LAYOUT(
    // // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    //     KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,   _______,  KC_F12,   KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    // // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
    //     KC_ESC,        JP_1,     JP_2,     JP_3,     JP_4,     JP_5,     _______,  _______,  JP_6,     JP_7,     JP_8,     JP_9,     JP_0,     KC_DEL,
    // // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
    //     _______,       KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F11,   _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,  KC_QUOT,
    // // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
    //     _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F12,   _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,  _______,
    // // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
    //     _______,  _______,  _______,    _______,    _______,        KC_DEL,   _______,  _______,  _______,        _______,    _______,    _______,  _______,
    // // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
    //     _______,  _______,                                                    _______,                                                    _______,  _______,
    // // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
    //                                                                 _______,  _______,  _______,
    // // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
    //                                                                           _______
    // // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    // ),
    // [_RAISE3] = LAYOUT(
    // // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    //     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
    //     _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
    //     _______,       _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
    //     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
    //     _______,  _______,  _______,    _______,    _______,        _______,  _______,  _______,  _______,        _______,    _______,    _______,  _______,
    // // |---------+---------+-----------+-----------+---------------+---------+---------+---------+---------------+-----------+-----------+---------+---------|
    //     _______,  _______,                                                    _______,                                                    _______,  _______,
    // // |---------+---------+-------------------------------------------------+---------+-------------------------------------------------+---------+---------|
    //                                                                 _______,  _______,  _______,
    // // |-----------------------------------------------------------+---------+---------+---------+-----------------------------------------------------------|
    //                                                                           _______
    // // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
    // ),
    [_ADJUST] = LAYOUT(
    // |-----------------------------------------------------------------------------------------------------------------------------------------------------|
        DM_RSTP,  MAC_SLP,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SCRL,  KC_PAUS,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KEY_WAIT,      BASE1,    BASE2,    NUMERIC,  _______,  _______,  _______,  RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_VAI,  IND_TOG,  RGB_RMOD, KC_INS,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_CAPS,       _______,  _______,  _______,  _______,  _______,  _______,  RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,  VERSION,
    // |--------------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+--------------|
        KC_CAPS,  _______,  _______,  _______,  _______,  _______,  DM_REC1,  _______,  DM_REC2,  NUMERIC,  _______,  _______,  _______,  _______,  _______,
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
        // case BASE3: // Change default layer.
        //     if (record->event.pressed) {
        //         if (get_mods() & MOD_MASK_SHIFT) {
        //             // If pressed with "Shift" key, write base layer to EEPROM.
        //             set_single_persistent_default_layer(_BASE3);
        //             return false;
        //         }
        //     }
        //     return true;
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
                _delay_ms(250);
            }
            return false;
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
// Dynamic Macro settings
//------------------------------------------------------------------------------
void dynamic_macro_play_user(int8_t direction) {
    // Revert layer indicator, just after macro played.
    // It returns to base layer. WHY???
    layer_state_set_user(layer_state);
}

#ifdef RGBLIGHT_LAYER_BLINK // RGB Lighting & RGB Layer Blink
    // Blink indicator when start / stop recorging.
    void dynamic_macro_record_start_user(int8_t direction) {
        rgblight_blink_layer_repeat(9, 250, 3);//TODO マクロ記録中、ずっとブリンクならんの？
    }

    void dynamic_macro_record_end_user(int8_t direction) {
        //TODO is_dm_rec1,2を使って、ダイナミックマクロ記録中に、ずっとBlinkさせたりできないか？
        is_dm_rec1 = false;
        is_dm_rec2 = false;
        rgblight_blink_layer_repeat(10, 250, 3);
    }
#endif

//------------------------------------------------------------------------------
// RGB Light settings
//------------------------------------------------------------------------------

// Indicator LED settings
#define ONBOARD_LED_INDICATOR_INDEX 0         // where to start indicator
#define ONBOARD_LED_INDICATOR_COUNT 2         // how many leds used for indicator
#define ONBOARD_LED_INDICATOR_CHANGE_COUNT 1  // how meny leds to change for temporally layer
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
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CHARTREUSE - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_blink1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_MIN}
);

const rgblight_segment_t PROGMEM my_blink2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_MIN}
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
    my_raise_layer,
    my_adjust_layer,
    my_blink1_layer,
    my_blink2_layer
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
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CHARTREUSE - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_raise_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_adjust_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_blink1_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_LOW}
);

const rgblight_segment_t PROGMEM my_blink2_layer_dimmer_low[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_LOW}
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
    my_raise_layer_dimmer_low,
    my_adjust_layer_dimmer_low,
    my_blink1_layer_dimmer_low,
    my_blink2_layer_dimmer_low
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
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CHARTREUSE - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_raise_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_adjust_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_blink1_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
);

const rgblight_segment_t PROGMEM my_blink2_layer_dimmer_middle[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_MIDDLE}
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
    my_raise_layer_dimmer_middle,
    my_adjust_layer_dimmer_middle,
    my_blink1_layer_dimmer_middle,
    my_blink2_layer_dimmer_middle
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
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CHARTREUSE - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_raise_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_adjust_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_blink1_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
);

const rgblight_segment_t PROGMEM my_blink2_layer_dimmer_high[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_HIGH}
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
    my_raise_layer_dimmer_high,
    my_adjust_layer_dimmer_high,
    my_blink1_layer_dimmer_high,
    my_blink2_layer_dimmer_high
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
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CHARTREUSE - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_raise_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_adjust_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_CHANGE_COUNT, HSV_RED - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_blink1_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_ORANGE - ONBOARD_LED_INDICATOR_DIMMER_MAX}
);

const rgblight_segment_t PROGMEM my_blink2_layer_dimmer_max[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDICATOR_INDEX , ONBOARD_LED_INDICATOR_COUNT, HSV_PINK - ONBOARD_LED_INDICATOR_DIMMER_MAX}
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
    my_raise_layer_dimmer_max,
    my_adjust_layer_dimmer_max,
    my_blink1_layer_dimmer_max,
    my_blink2_layer_dimmer_max
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    // Set the layer status
    if (state != update_tri_layer_state(state, _LOWER1, _RAISE1, _ADJUST)) {
        state = update_tri_layer_state(state, _LOWER1, _RAISE1, _ADJUST);
    } else {
        state = update_tri_layer_state(state, _LOWER2, _RAISE1, _ADJUST);
    }

    rgblight_set_layer_state(2, layer_state_cmp(state, _BASE3));
    rgblight_set_layer_state(5, layer_state_cmp(state, _LOWER1));
    rgblight_set_layer_state(6, layer_state_cmp(state, _LOWER2));
    // rgblight_set_layer_state(4, layer_state_cmp(state, _LOWER3));
    rgblight_set_layer_state(7, layer_state_cmp(state, _RAISE1));
    // rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE2));
    // rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE3));
    rgblight_set_layer_state(8, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE1));
    rgblight_set_layer_state(1, layer_state_cmp(state, _BASE2));
    rgblight_set_layer_state(2, layer_state_cmp(state, _BASE3));//光らない。テンポラリはOK

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
    user_config.indicator_state = 1; // Layer indicator LED state: 0 = on(brightness = high)
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now
}
