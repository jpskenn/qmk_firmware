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

enum preonic_layers {
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
#define GUI_JA  LGUI_T(KC_LANG1)
#define GUI_EN  LGUI_T(KC_LANG2)
#define ALT_JA  LALT_T(KC_LANG1)
#define ALT_EN  LALT_T(KC_LANG2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_MAC] = LAYOUT_preonic_grid(
    ESC_NUM,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    C_ESC,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    KC_LEFT,  KC_RGHT,  KC_LOPT,  KC_LCMD,  SP_LOW,   SP_LOW,   SP_RAI,   SP_RAI,   GUI_IME,  KC_ROPT,  KC_DOWN,  KC_UP
),
[_WIN] = LAYOUT_preonic_grid(
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  KC_LGUI,  KC_LALT,  _______,  _______,  _______,  _______,  A_GRV,    KC_MENU,  _______,  _______
),
[_NUM] = LAYOUT_preonic_grid(
    KC_ESC,   _______,  _______,  _______,  _______,  _______,  KC_PSLS,  KC_PSLS,  KC_PSLS,  KC_PAST,  KC_PMNS,  KC_EQL,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  KC_BSPC,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P4,    KC_P5,    KC_P6,    XXXXXXX,  KC_ENT,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_P1,    KC_P2,    KC_P3,    XXXXXXX,  _______,
    _______,  _______,  _______,  _______,  SP_NLOW,  SP_NLOW,  _______,  _______,  KC_P0,    KC_PDOT,  XXXXXXX,  XXXXXXX
),
[_LOWER] = LAYOUT_preonic_grid(
    KC_F11,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F12,
    _______,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  KC_INS,
    _______,  _______,  _______,  _______,  _______,  _______,  KC_GRV,   KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,
    _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  KC_TILD,  KC_UNDS,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,
    KC_HOME,  KC_END,   _______,  _______,  _______,  _______,  SP_ADJ,   SP_ADJ,   _______,  _______,  KC_PGDN,  KC_PGUP
),
[_RAISE] = LAYOUT_preonic_grid(
    KC_F11,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F12,
    _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,  KC_QUOT,
    _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_F11,   KC_F12,
    KC_HOME,  KC_END,   _______,  _______,  SP_ADJ,   SP_ADJ,   _______,  _______,  _______,  _______,  KC_PGDN,  KC_PGUP
),
[_NUM_LOWER] = LAYOUT_preonic_grid(
    ESC_NUM,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_EQL,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    C_ESC,    KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
    _______,  _______,  _______,  _______,  _______,  _______,  SP_ADJ,   SP_ADJ,   GUI_IME,  KC_ROPT,  KC_DOWN,  KC_UP
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
