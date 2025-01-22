/* Copyright 2015-2017 Jack Humbert
 * Updated for VIA 2021 George Wietor
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
#include "muse.h"
#include "version.h"

extern keymap_config_t keymap_config;

enum preonic_layers {
    _BASE = 0,
    _OPT,
    _FUNC,
    _SYM,
    _NUM,
    _NUM_LOWER,
    _ADJUST,
};

enum custom_keycodes {
  BASE = SAFE_RANGE,
  MAC,
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
#define GUI_JA  LGUI_T(KC_LANG1)
#define GUI_EN  LGUI_T(KC_LANG2)
#define ALT_JA  LALT_T(KC_LANG1)
#define ALT_EN  LALT_T(KC_LANG2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base
   * ,-----------------------------------------------------------------------------------.
   * |  C+z |   ;  |   [  |   (  |   <  |   {  |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | KANA |   P  |   K  |   R  |   A  |   F  |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  BS  |   D  |   T  |   H  |   E  |   O  |      |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Y  |   S  |   N  |   I  |   U  |Space |      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * | Ctrl | Alt  | Gui  | Sym  | Num  | OPT  | Ent  |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
    [_BASE] = LAYOUT_preonic_grid(
        LCTL(KC_Z),    KC_SCLN,       KC_LBRC,       KC_LPRN,   KC_LT,     KC_LCBR,    _______,  _______,  _______,  _______,  _______,  _______, \
        KANA,          KC_P,          KC_K,          KC_R,      KC_A,      KC_F,       _______,  _______,  _______,  _______,  _______,  _______, \
        KC_BSPC,       KC_D,          KC_T,          KC_H,      KC_E,      KC_O,       _______,  _______,  _______,  _______,  _______,  _______, \
        OSM(MOD_LSFT), KC_Y,          KC_S,          KC_N,      KC_I,      KC_U,       KC_SPC,   _______,  _______,  _______,  _______,  _______, \
        OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), MO(_SYM),  MO(_NUM),  OPT_TAP_SP, KC_ENT,   _______,  _______,  _______,  _______,  _______  \
    ),
    [_OPT] = LAYOUT_preonic_grid(
        KC_ESC,  KC_COLN,KC_RBRC, KC_RPRN,KC_GT,     KC_RCBR, _______,  _______,  _______,  _______,  _______,  _______, \
        EISU,    KC_J,   KC_M,    KC_B,   KC_QUOT,   KC_TAB,  _______,  _______,  _______,  _______,  _______,  _______, \
        KC_DOT,  KC_V,   KC_C,    KC_L,   KC_Z,      KC_Q,    _______,  _______,  _______,  _______,  _______,  _______, \
        _______, KC_X,   KC_G,    KC_W,   KC_MINUS,  KC_DEL,  KC_ESC,   _______,  _______,  _______,  _______,  _______, \
        _______, _______,_______, KC_COMM,DESKTOP,   _______, _______,  _______,  _______,  _______,  _______,  _______ \
    ),
    [_FUNC] = LAYOUT_preonic_grid(
        RGBRST,RGB_HUI, _______, RESET,   MAC,     WIN,      _______,  _______,  _______,  _______,  _______,  _______, \
        RGB1,  RGB_VAI, KC_F7,   KC_F8,   KC_F9,   _______,  _______,  _______,  _______,  _______,  _______,  _______, \
        RGB2,  RGB_VAD, KC_F4,   KC_F5,   KC_F6,   KC_F12,   _______,  _______,  _______,  _______,  _______,  _______, \
        RGB3,  KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_F11,   _______,  _______,  _______,  _______,  _______,  _______, \
        RGBOFF,_______, _______, _______, _______, _______,  _______,  _______,  _______,  _______,  _______,  _______ \
    ),
    [_SYM] = LAYOUT_preonic_grid(
        KC_INS,  KC_GRV,  _______, KC_PGUP, KC_PGDN, KC_CIRC, _______,  _______,  _______,  _______,  _______,  _______, \
        _______, KC_BSLS, KC_HASH, KC_EQL,  KC_QUES, KC_PERC, _______,  _______,  _______,  _______,  _______,  _______, \
        _______, KC_DLR,  KC_UP,   KC_AT,   KC_EXLM, KC_PIPE, _______,  _______,  _______,  _______,  _______,  _______, \
        KC_CAPS, KC_LEFT, KC_DOWN, KC_RIGHT,KC_UNDS, KC_AMPR, _______,  _______,  _______,  _______,  _______,  _______, \
        _______, _______, KC_PSCR, _______, KC_TILD, _______, _______,  _______,  _______,  _______,  _______,  _______ \
    ),
    [_NUM] = LAYOUT_preonic_grid(
        _______,  _______, OSL(_FUNC), KC_HOME, KC_END,  _______,        _______,  _______,  _______,  _______,  _______,  _______, \
        _______,  KC_ASTR, KC_P7,      KC_P8,   KC_P9,   KC_MINS,        _______,  _______,  _______,  _______,  _______,  _______, \
        KC_PDOT,  KC_SLSH, KC_P4,      KC_P5,   KC_P6,   KC_PLUS,        _______,  _______,  _______,  _______,  _______,  _______, \
        KC_NLCK,  KC_P0,   KC_P1,      KC_P2,   KC_P3,   LCTL(S(KC_F1)), _______,  _______,  _______,  _______,  _______,  _______, \
        _______,  _______, KC_PDOT,    KC_COMM, _______, _______,        _______,  _______,  _______,  _______,  _______,  _______ \
    ),
    [_NUM_LOWER] = LAYOUT_preonic_grid(
        ESC_NUM,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
        KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
        C_ESC,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
        _______,  _______,  _______,  _______,  _______,  _______,  SP_ADJ,   SP_ADJ,   GUI_IME,  KC_ROPT,  _______,  _______
    ),
    [_ADJUST] = LAYOUT_preonic_grid(
        NUM,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PSCR,  KC_SLCK,  KC_PAUS,
        _______,  MAC,      WIN,      _______,  RESET,    _______,  RGB_HUI,  RGB_SAI,  RGB_VAI,  _______,  RGB_RMOD, _______,
        _______,  AU_TOG,   CK_TOGG,  MU_TOG,   MU_MOD,   _______,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,  VERSION,
        KC_CAPS,  CK_RST,   CK_DOWN,  CK_UP,    MUV_DE,   MUV_IN,   NUM,      _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    ),

};

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_MAC);
            }
            return false;
        case WIN: // Change default ayer --> Write to EEPROM
            if (record->event.pressed) {
                set_single_persistent_default_layer(_WIN);
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
// RGB Light settings
//------------------------------------------------------------------------------
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define LED_INDICATOR_INDEX 0         // where to start indicator
#define LED_INDICATOR_COUNT 9         // how many leds used for indicator
#define LED_INDICATOR_TEMP_INDEX 3
#define LED_INDICATOR_CHANGE_COUNT 2  // how meny leds to change for temporally layer
#define LED_DIMMER_LEVEL 0          // brightness dimmer

// for Default layer (= Base layer)mmwn
const rgblight_segment_t PROGMEM my_mac_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, HSV_WHITE - LED_DIMMER_LEVEL}
);
const rgblight_segment_t PROGMEM my_win_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, HSV_BLUE - LED_DIMMER_LEVEL}
);
const rgblight_segment_t PROGMEM my_num_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_INDEX , LED_INDICATOR_COUNT, 0,0,0}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_TEMP_INDEX + 2 , 2, HSV_MAGENTA - LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_TEMP_INDEX, LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_TEMP_INDEX, LED_INDICATOR_CHANGE_COUNT, HSV_CYAN - LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_num_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_TEMP_INDEX, LED_INDICATOR_CHANGE_COUNT, HSV_GREEN - LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {LED_INDICATOR_TEMP_INDEX, LED_INDICATOR_CHANGE_COUNT, HSV_RED - LED_DIMMER_LEVEL}
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
    my_adjust_layer
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(4, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(5, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(6, layer_state_cmp(state, _NUM_LOWER));
    rgblight_set_layer_state(7, layer_state_cmp(state, _ADJUST));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _MAC));
    rgblight_set_layer_state(1, layer_state_cmp(state, _WIN));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(3, led_state.caps_lock);

    return true;
}
#endif

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
    return true;
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case FN_MO13:
    case FN_MO23:
      return false;
    default:
      return true;
  }
}

void keyboard_post_init_user(void) {

#ifdef RGBLIGHT_LAYERS
    // Enable the LED layers.
    rgblight_layers = my_rgb_layers;
#endif

}
