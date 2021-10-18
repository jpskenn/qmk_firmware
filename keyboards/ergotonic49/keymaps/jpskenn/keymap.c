/* Copyright 2021 hanachi-ap
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _MAC,
    _NUM,
    _LOW,
    _RAI,
    _ADJ,
};

// Custom keycodes
enum custom_keycodes {
  MAC = SAFE_RANGE,
//   WIN,
  GUI_IME,
  VERSION,
};

// Key Macro
#define C_ESC   LCTL_T(KC_ESC)
#define TAB_NUM LT(_NUM, KC_TAB)
#define SP_LOW  LT(_LOW, KC_SPC)
#define SP_RAI  LT(_RAI, KC_SPC)
#define SP_ADJ  LT(_ADJ, KC_SPC)
#define NUM     TG(_NUM)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_MAC]=LAYOUT(   // Base
			TAB_NUM	,	KC_Q	,	KC_W	,	KC_E	,	KC_R	,	KC_T	,							KC_Y	,	KC_U	,	KC_I	,	KC_O	,	KC_P	,	KC_BSPC	,	KC_UP	,
			C_ESC	,	KC_A	,	KC_S	,	KC_D	,	KC_F	,	KC_G	,							KC_H	,	KC_J	,	KC_K	,	KC_L	,	KC_MINS	,	KC_ENT	,	KC_DOWN	,
			KC_LSFT	,	KC_Z	,	KC_X	,	KC_C	,	KC_V	,	KC_B	,	KC_GRV	,	KC_PIPE	,	KC_N	,	KC_M	,	KC_COMM	,	KC_DOT	,	KC_SLSH	,	KC_RSFT	,
	XXXXXXX	,								KC_LOPT	,	KC_LCMD	,	SP_LOW	,	KC_BSPC	,	KC_SPC  ,   KC_ENT	,	SP_RAI	,	GUI_IME	,	KC_LOPT	,
			KC_VOLD	,	KC_VOLU	,								XXXXXXX	,	XXXXXXX	,			XXXXXXX	,	XXXXXXX
),

[_NUM]=LAYOUT(   // Base2:Num
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
	_______	,							_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
),

[_LOW]=LAYOUT(    // Temporally: Lower
			KC_GRV	,	KC_1	,	KC_2	,	KC_3	,	KC_4	,	KC_5	,							KC_6	,	KC_7	,	KC_8	,	KC_9	,	KC_0	,	KC_LBRC	,	KC_RBRC	,
			_______	,	KC_EXLM	,	KC_AT	,	KC_HASH	,	KC_DLR	,	KC_PERC	,							KC_CIRC	,	KC_AMPR	,	KC_ASTR	,	KC_LPRN	,	KC_RPRN	,	KC_PLUS	,	KC_BSLS	,
			_______	,	KC_MUTE	,	KC_VOLD	,	KC_VOLU	,	_______	,	_______	,	_______	,	_______	,	KC_0	,	KC_1	,	KC_2	,	KC_3	,	KC_SLSH	,	_______	,
	_______	,							    _______	,	_______	,	_______	,	_______	,	_______	,	_______	,	SP_ADJ	,	_______	,	_______ ,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
),
[_RAI]=LAYOUT(    // Temporally: Raise
			_______	,	KC_F1	,	KC_F2	,	KC_F3	,	KC_F4	,	KC_F5	,							KC_F6	,	KC_F7	,	KC_F8	,	KC_F9	,	KC_F10	,	KC_DEL	,   KC_F11  ,
			_______	,	KC_F6	,	KC_F7	,	KC_F8	,	KC_F9	,	KC_F10	,							KC_LEFT	,	KC_DOWN	,	KC_UP	,	KC_RGHT	,	KC_SCLN	,	KC_QUOT	,	KC_F12	,
			_______	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	KC_F11	,	KC_F12	,	_______	,	_______	,	KC_HOME	,	KC_PGDN	,	KC_PGUP	,	KC_END	,	_______	,   _______ ,
	_______	,						    	_______	,	_______	,	SP_ADJ	,	KC_DEL	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
),
[_ADJ]=LAYOUT(  // Temporally: Adjust
			DM_RSTP	,	_______	,	_______	,	KC_PSCR	,	KC_SLCK	,	KC_PAUS	,							RGB_HUI	,	RGB_SAI	,	RGB_VAI	,	XXXXXXX	,	RGB_MOD	,	XXXXXXX	,	XXXXXXX	,
			_______	,	_______	,	_______	,	_______	,	_______	,	_______	,							RGB_HUD	,	RGB_SAD	,	RGB_VAD	,	RGB_TOG	,	RGB_RMOD,	VERSION	,	XXXXXXX	,
			KC_CAPS	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	XXXXXXX	,	NUM	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,	XXXXXXX	,
	_______	,							    _______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,	_______	,
			_______	,	_______	,							_______	,	_______	,			_______	,	_______
)


};

uint16_t key_timer;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
            }
            return false;
        case GUI_IME: // Toggle IME, my Mac IME shortcut key dependent.
            if (record->event.pressed) {
                key_timer = timer_read();
                register_code(KC_RGUI);
            } else {
                unregister_code(KC_RGUI);

                if (timer_elapsed(key_timer) < TAPPING_TERM) {
                    if (keymap_config.swap_ralt_rgui) {     // swapped, windows
                        SEND_STRING(SS_LCMD("`")); // NOTE: SS_LCMD will be swapped to SS_LALT by MAGIC
                    } else {                                // mac
                        SEND_STRING(SS_LCMD(SS_LALT(SS_TAP(X_SPC))));
                    }
                }
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
// bool savedNumLayer = false; // Stored Num layer status

// void dynamic_macro_play_user(int8_t direction) {
//     // Revert layer indicator, just after macro played.
//     // It returns to base layer. WHY???
//     layer_state_set_user(layer_state);
// }

// void dynamic_macro_record_start_user(void) {
//     // Before recording clears the layer status,
//     // check Num layer to store its status.
//     if (IS_LAYER_ON(_NUM)) {
//         savedNumLayer = true;
//     }
//     rgblight_blink_layer_repeat(8, 250, 3);
// }

// void dynamic_macro_record_end_user(int8_t direction) {
//     // Restore Num layer status, if it was ON before recording.
//     if (savedNumLayer) {
//         layer_on(_NUM);
//         savedNumLayer = false;
//     }
//     rgblight_blink_layer_repeat(9, 250, 3);
// }


//------------------------------------------------------------------------------
// Rotary Encoder
//------------------------------------------------------------------------------
const uint8_t rt_matrix[][3][2] = {
    {{3,1},{3,2}},
    {{0,6},{1,6}},
    {{0,7},{3,11}},
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;
    int      cw = 0;
    if (clockwise) cw = 1;
    key.row          = rt_matrix[index][cw][0];
    key.col          = rt_matrix[index][cw][1];
    uint8_t  layer   = layer_switch_get_layer(key);
    uint16_t keycode = keymap_key_to_keycode(layer, key);
    tap_code16(keycode);
    return false;
}


//------------------------------------------------------------------------------
// RGB Light
//------------------------------------------------------------------------------
const rgblight_segment_t PROGMEM rgb_caps_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM rgb_lowlock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM rgb_scllock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_SPRINGGREEN}
);

const rgblight_segment_t PROGMEM rgb_low_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_GREEN}
);

const rgblight_segment_t PROGMEM rgb_rai_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_CYAN}
);

const rgblight_segment_t PROGMEM rgb_adj_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_RED}
);

const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    rgb_caps_layer,
    rgb_lowlock_layer,
    rgb_scllock_layer,
    rgb_low_layer,
    rgb_rai_layer,
    rgb_adj_layer
);

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(3, layer_state_cmp(state, _LOW));
    rgblight_set_layer_state(4, layer_state_cmp(state, _RAI));
    rgblight_set_layer_state(5, layer_state_cmp(state, _ADJ));

    return state;
}

bool led_update_user(led_t led_state) {
    // rgblight_set_layer_state(0, led_state.num_lock);
    rgblight_set_layer_state(1, led_state.caps_lock);
    // rgblight_set_layer_state(2, led_state.scroll_lock);

    return true;
}


//------------------------------------------------------------------------------
// Keyboard Initialization
//------------------------------------------------------------------------------
void keyboard_post_init_user(void) {
    rgblight_layers = rgb_layers;
    // rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
    // autoshift_disable();
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
#endif
}
