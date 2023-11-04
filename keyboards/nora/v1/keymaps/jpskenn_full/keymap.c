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
#include "keymap_japanese.h"

void rgb_matrix_set_color_user(int, int, int, int, bool);

bool is_led_indicator_enabled = true;

bool is_dm_rec1 = false;
bool is_dm_rec2 = false;

#ifdef AUDIO_ENABLE
    // float song_caps_on[][2] = SONG(CAPS_LOCK_ON_SOUND);
    // float song_caps_off[][2] = SONG(CAPS_LOCK_OFF_SOUND);
    // float song_adjust[][2] = SONG(UNICODE_WINDOWS);
#endif

enum layer_number {
    _BASE1 = 0,
    _BASE2,
    _BASE3,
    _LOWER1,
    _LOWER2,
    _LOWER3,
    _RAISE1,
    _RAISE2,
    _RAISE3,
    _ADJUST,
};

enum custom_keycodes {
  BASE1 = SAFE_RANGE,
  BASE2,
  BASE3,
  ADJUST,
  VERSION,
  IND_TOG,
  GUI_IME,
};

#define SP_LOW1  LT(_LOWER1, KC_SPC)
#define SP_RAI1  LT(_RAISE1, KC_SPC)
#define SP_LOW2  LT(_LOWER2, KC_SPC)
#define SP_RAI2  LT(_RAISE2, KC_SPC)
#define SP_LOW3  LT(_LOWER3, KC_SPC)
#define SP_RAI3  LT(_RAISE3, KC_SPC)
#define SP_ADJ  LT(_ADJUST, KC_SPC)
#define C_ESC   LCTL_T(KC_ESC)
#define BASE1   DF(_BASE1)
#define BASE2   DF(_BASE2)
#define BASE3   DF(_BASE3)
#define ADJUST  MO(_ADJUST)

// #define ESC_NUM TD(TD_ESC_NUM)
#define ESC_NUM LT(_BASE3, KC_ESC)
// #define GRV_NUM LT(_NUM, KC_GRV)
// #define S_CAPS   TD(TD_LSFT_CAPS)
// #define SP_LOW  LT(_LOWER, KC_SPC)
// #define SP_RAI  LT(_RAISE, KC_SPC)
// #define SP_ADJ  LT(_ADJUST, KC_SPC)
#define SP_NLOW LT(_NUM_LOWER, KC_SPC)
// #define BS_RAI  LT(_RAISE, KC_BSPC)
// #define SP_NRAI LT(_NUM_LOWER, KC_SPC)
// #define BS_NRAI LT(_NUM_LOWER, KC_BSPC)
// #define SP_SFT  MT(MOD_LSFT, KC_SPC)
// #define C_ESC   LCTL_T(KC_ESC)
// #define C_SPC   LCTL(KC_SPC)
// #define C_SLSH  RCTL_T(KC_SLSH)
#define S_SLSH  RSFT_T(KC_SLSH)
#define S_LEFT  RSFT_T(KC_LEFT)
// #define CT_E    LCTL(KC_E)
// #define CT_A    LCTL(KC_A)
#define C_QUO   LCTL_T(KC_QUOT)
#define A_GRV   LALT(KC_GRV)
#define CA_SPC  LCA(KC_SPC)
// #define LOWER   MO(_LOWER)
// #define ADJUST  MO(_ADJUST)
#define NUM     TG(_BASE3)
// #define HENKAN  LGUI(KC_GRV)
#define GUI_JA  LGUI_T(KC_LNG1)
#define GUI_EN  LGUI_T(KC_LNG2)
#define ALT_JA  LALT_T(KC_LNG1)
#define ALT_EN  LALT_T(KC_LNG2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE1] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        ESC_NUM,KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_GRV, KC_PGDN,KC_PGUP,KC_BSLS,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_EQL,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,KC_MINS,KC_RBRC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        C_ESC,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_SCLN,KC_UP,  KC_QUOT,KC_H,   KC_J,   KC_K,   KC_L,   KC_MINS,KC_ENT,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   DM_PLY1,KC_LEFT,KC_DOWN,KC_RGHT,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          KC_LOPT,    GUI_EN, SP_LOW1,    KC_BSPC,DM_PLY2,    KC_ENT, SP_RAI1,    GUI_JA, KC_ROPT
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
    [_BASE2] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        JP_ZKHK,JP_1,   JP_2,   JP_3,   JP_4,   JP_5,   JP_CIRC,KC_PGDN,KC_PGUP,JP_YEN, JP_6,   JP_7,   JP_8,   JP_9,   JP_0,   JP_MINS,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        KC_TAB,     JP_Q,   JP_W,   JP_E,   JP_R,   JP_T,   JP_SCLN,JP_AT,  JP_LBRC,JP_Y,   JP_U,   JP_I,   JP_O,   JP_P,   KC_BSPC,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        C_ESC,      JP_A,   JP_S,   JP_D,   JP_F,   JP_G,   JP_COLN,KC_UP,  JP_RBRC,JP_H,   JP_J,   JP_K,   JP_L,   JP_MINS,KC_ENT,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        KC_LSFT,KC_LSFT,JP_Z,   JP_X,   JP_C,   JP_V,   JP_B,   KC_LEFT,KC_DOWN,KC_RGHT,JP_N,   JP_M,   JP_COMM,JP_DOT, JP_SLSH,JP_BSLS,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          KC_LWIN,    KC_LALT,SP_LOW2,    KC_BSPC,XXXXXXX,    KC_ENT, SP_RAI2,    A_GRV,  KC_APP
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
    [_BASE3] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_PSLS,KC_PSLS,KC_PAST,KC_PMNS,_______,_______,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_P7,  KC_P8,  KC_P9,  KC_PPLS,_______,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,KC_P4,  KC_P5,  KC_P6,  KC_PPLS,_______,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,KC_P1,  KC_P2,  KC_P3,  _______,_______,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          _______,    _______,SP_LOW3,    _______,_______,    _______,_______,    KC_P0,  KC_PDOT
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
    [_LOWER1] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,_______,_______,KC_F12, KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        KC_ESC,     KC_EXLM,KC_AT,  KC_HASH,KC_DLR, KC_PERC,KC_TILD,_______,KC_PIPE,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,_______,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,KC_GRV, KC_MINS,KC_EQL, KC_LBRC,KC_RBRC,KC_BSLS,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,KC_MUTE,KC_VOLD,KC_VOLU,_______,_______,_______,_______,_______,_______,KC_TILD,KC_UNDS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          _______,    _______,_______,    _______,_______,    _______,ADJUST,     _______,_______
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
    [_LOWER2] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,_______,_______,KC_F12, KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        KC_ESC,     JP_EXLM,JP_DQUO,JP_HASH,JP_DLR, JP_PERC,JP_TILD,_______,JP_PIPE,JP_AMPR,JP_QUOT,JP_LPRN,JP_RPRN,_______,JP_EQL,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,JP_AT,  JP_SCLN,JP_COLN,JP_LBRC,JP_RBRC,JP_BSLS,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,KC_MUTE,KC_VOLD,KC_VOLU,_______,_______,_______,_______,_______,_______,JP_GRV, JP_PLUS,JP_ASTR,JP_LCBR,JP_RCBR,JP_UNDS,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          _______,    _______,_______,    _______,_______,    _______,ADJUST,     _______,_______
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
    [_LOWER3] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_GRV, KC_PGDN,KC_PGUP,KC_BSLS,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_EQL,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        KC_TAB,     KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_LBRC,KC_MINS,KC_RBRC,KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        C_ESC,      KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_SCLN,KC_UP,  KC_QUOT,KC_H,   KC_J,   KC_K,   KC_L,   KC_MINS,KC_ENT,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   DM_PLY1,KC_LEFT,KC_DOWN,KC_RGHT,KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          KC_LOPT,    KC_LCMD,_______,    KC_BSPC,DM_PLY2,    KC_ENT, ADJUST,     GUI_IME,KC_ROPT
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
    [_RAISE1] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,_______,_______,KC_F12, KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        KC_ESC,     KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   _______,_______,_______,KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_DEL,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,_______,_______,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,KC_SCLN,KC_QUOT,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, _______,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END, _______,_______,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          _______,    _______,ADJUST,     KC_F12, _______,    _______,_______,    _______,_______
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
    [_RAISE2] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,_______,_______,KC_F12, KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        KC_ESC,     JP_1,   JP_2,   JP_3,   JP_4,   JP_5,   _______,_______,_______,JP_6,   JP_7,   JP_8,   JP_9,   JP_0,   KC_DEL,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  _______,_______,_______,KC_LEFT,KC_DOWN,KC_UP,  KC_RGHT,JP_SCLN,JP_COLN,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, _______,_______,_______,KC_HOME,KC_PGDN,KC_PGUP,KC_END, _______,_______,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          _______,    _______,ADJUST,     KC_F12, _______,    _______,_______,    _______,_______
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
    [_RAISE3] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,    _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          _______,    _______,ADJUST,    _______,_______,    _______,_______,    _______,_______
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
    [_ADJUST] = LAYOUT_all(
    // |-------------------------------------------------------------------------------------------------------------------------------|
        DM_RSTP,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
        _______,    BASE1,  BASE2,  BASE3,  _______,_______,_______,_______,RGB_SPI,RGB_HUI,RGB_SAI,RGB_VAI,IND_TOG,RGB_RMOD,KC_INS,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        KC_CAPS,    AU_TOGG,MU_TOGG,MU_NEXT,AU_PREV,AU_NEXT,_______,_______,RGB_SPD,RGB_HUD,RGB_SAD,RGB_VAD,RGB_TOG,RGB_MOD,VERSION,
    // |-----------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-----------|
        _______,CK_TOGG,CK_RST, CK_DOWN,CK_UP,  _______,_______,_______,_______,_______,_______,_______,_______,KC_PSCR,KC_SCRL,KC_PAUS,
    // |-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------|
                          _______,    _______,_______,    _______,_______,    _______,_______,    _______,_______
    //                   |-----------+-------+-----------+-------+-----------+-------+-----------+-------+-----------|
    ),
};

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            return false;
        case BASE1: // If "Shift" pressed, Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    set_single_persistent_default_layer(_BASE1);
                    return false;
                }
            }
            return true;
        case BASE2: // If "Shift" pressed, Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    set_single_persistent_default_layer(_BASE2);
                    return false;
                }
            }
            return true;
        case BASE3: // If "Shift" pressed, Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    set_single_persistent_default_layer(_BASE3);
                    return false;
                }
            }
            return true;
        case IND_TOG: // Toggle LED indicator.
            if (record->event.pressed) {
                is_led_indicator_enabled = !is_led_indicator_enabled;
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

#ifdef RGB_MATRIX_ENABLE // RGB Matrix
    // Set "false" to turn off recording indicator.
    void dynamic_macro_record_end_user(int8_t direction) {
        is_dm_rec1 = false;
        is_dm_rec2 = false;
    }
#endif
#ifdef RGBLIGHT_LAYER_BLINK // RGB Lighting & RGB Layer Blink
    // Blink indicator when start / stop recorging.
    void dynamic_macro_record_start_user(void) {
        rgblight_blink_layer_repeat(8, 250, 3);
    }

    void dynamic_macro_record_end_user(int8_t direction) {
        rgblight_blink_layer_repeat(9, 250, 3);
    }
#endif

//------------------------------------------------------------------------------
// RGB Matrix settings
//------------------------------------------------------------------------------
#ifdef RGB_MATRIX_ENABLE

bool void rgb_matrix_indicators_user(void) {
    // Indicator On / Off control
    if(!is_led_indicator_enabled) {
        return false;
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
        case _LOWER1:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_GREEN, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_GREEN, true);
            break;
        case _RAISE1:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_AZURE, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_AZURE, true);
            break;
        case _LOWER2:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_CHARTREUSE, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_CHARTREUSE, true);
            break;
        case _RAISE2:
            rgb_matrix_set_color_user(LED_INDEX_LSPC, HSV_CYAN, true);
            rgb_matrix_set_color_user(LED_INDEX_RSPC, HSV_CYAN, true);
            break;
        // No Indicator for Reserved layers.
        // case _LOWER3:
        // case _RAISE3:
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
