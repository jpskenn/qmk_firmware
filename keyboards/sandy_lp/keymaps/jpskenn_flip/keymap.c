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
#include "audio.h"

// Audio settings in EEPROM. Enable audio, but not turn ON by default.
// Also see eeconfig_init_user().
extern audio_config_t audio_config;

// PROTOTYPE
void led_counter_reset(void);
void led_counter_update(void);
bool led_counter_hue_update(int *);
void led_counter_turn_on(void);
void led_counter_turn_off(void);

// LED counter
#define LED_COUNTER_DEFAULT_HUE 224
bool is_led_counter_enabled = false;
int led_0_hue = LED_COUNTER_DEFAULT_HUE;
int led_1_hue = LED_COUNTER_DEFAULT_HUE;
int led_2_hue = LED_COUNTER_DEFAULT_HUE;

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
        uint8_t indicator_state :8; // Layer indicator state
        bool is_led_counter_enabled :1; // LED counter enabled
    };
} user_config_t;

user_config_t user_config;

// layers
enum layer_number {
    _BASE = 0,
    _NUM,
    _SYM,
    _FLIP,
    _FLIP_NUM,
    _FLIP_SYM,
    _SPECIAL,
    _ADJUST,
};

// Tap Dance declarations
enum {
    TD_SELECTOR,
};

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    TRIPLE_TAP = 4,
};

typedef struct {
    bool is_press_action;
    int state;
} tap;

// int cur_dance (tap_dance_state_t *state);

// custom key codes
enum custom_keycodes {
    VERSION = SAFE_RANGE,
    KEY_WAIT,
    IND_TOG,
    CNT_RST,
    CNT_TOG,
  };

  // key code macros
  #define FLIP      MO(_FLIP)
  #define FLIP_NUM  MO(_FLIP_NUM)
  #define FLIP_SYM  MO(_FLIP_SYM)

  #define SPC_SYM   LT(_SYM, KC_SPC)
  #define TAB_NUM   LT(_NUM, KC_TAB)
  #define BS_NUM    LT(_NUM, KC_BSPC)
  #define SPC_F_SYM LT(_FLIP_SYM, KC_SPC)
  #define BS_F_NUM  LT(_FLIP_NUM, KC_BSPC)
  #define TAB_F_NUM LT(_FLIP_NUM, KC_TAB)

  #define TG_NUM    TG(_NUM)

  #define SPC_SFT   LSFT_T(KC_SPC)
  #define ENT_SFT   LSFT_T(KC_ENT)

  #define CTL_ESC   LCTL_T(KC_ESC)
  #define CTL_Z     LCTL_T(KC_Z)
  #define CTL_X     LCTL_T(KC_X)
  #define CTL_C     LCTL_T(KC_C)
  #define CTL_V     LCTL_T(KC_V)

  #define CMD_LNG1     LGUI_T(KC_LNG1)
  #define CMD_LNG2     LGUI_T(KC_LNG2)
  #define CTL_LNG1     LCTL_T(KC_LNG1)
  #define CTL_LNG2     LCTL_T(KC_LNG2)

  #define OSM_WIN   OSM(KC_LWIN)  // RemapでCtrl + ShiftなOSMとして扱われている。なぜ？
  #define OSM_CTL   OSM(KC_LCTL)
  #define OSM_ALT   OSM(KC_LALT)
  #define OSM_SFT   OSM(KC_LSFT)

  #define MAC_SLP     LAG(KC_EJCT)

  #define MAC_PSCR    LSG(KC_5)
  #define WIN_PSCR    LSG(KC_S)

  #define SELECTOR    TD(TD_SELECTOR)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        TAB_NUM,  KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     XXXXXXX,  MAC_PSCR, KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     BS_NUM,
    //  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,  KC_RBRC,  KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        CTL_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     XXXXXXX,  WIN_PSCR, KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  ENT_SFT,
    //  CTL_ESC,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_SCLN,  KC_QUOT,  KC_H,     KC_J,     KC_K,     KC_L,     KC_MINS,  KC_ENT,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     SELECTOR, KC_ESC,   SELECTOR, KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          KC_LOPT,  CTL_LNG2, SPC_SFT,    FLIP,     KC_MUTE,  FLIP,     SPC_SYM,    CTL_LNG1, OSM_WIN
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_NUM] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  KC_F10,   KC_F9,    KC_F8,    KC_F7,    _______,  _______,   _______, KC_PAST,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        _______,  KC_F11,   KC_F6,    KC_F5,    KC_F4,    _______,  _______,  _______,  KC_PSLS,  KC_P4,    KC_P5,    KC_P6,    KC_PMNS,  _______,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_F12,   KC_F3,    KC_F2,    KC_F1,    _______,  _______,  _______,  DM_PLY2,  KC_PEQL,  KC_P1,    KC_P2,    KC_P3,    KC_CALC,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          _______,  _______,  _______,    FLIP_NUM, _______,  FLIP_NUM, _______,    KC_P0,    KC_PDOT
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_SYM] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        TG_NUM,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     _______,  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        OSM_CTL,  KC_GRV,   KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,  KC_QUOT,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_TILD,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,  _______,  _______,  DM_PLY2,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   _______,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          OSM_ALT,  OSM_CTL,  OSM_SFT,    FLIP_SYM, _______,  FLIP_SYM,  _______,   OSM_CTL,  OSM_WIN
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_FLIP] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        BS_F_NUM, KC_P,     KC_O,     KC_I,     KC_U,     KC_Y,     MAC_PSCR, XXXXXXX,  KC_T,     KC_R,     KC_E,     KC_W,     KC_Q,     TAB_F_NUM,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        ENT_SFT,  KC_MINS,  KC_L,     KC_K,     KC_J,     KC_H,     WIN_PSCR, _______,  KC_G,     KC_F,     KC_D,     KC_S,     KC_A,     CTL_ESC,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_SLSH,  KC_DOT,   KC_COMM,  KC_M,     KC_N,     _______,  _______,  _______,  KC_B,     KC_V,     KC_C,     KC_X,     KC_Z,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          OSM_WIN,  CTL_LNG1, SPC_F_SYM,  _______,  _______,  _______,  SPC_SFT,    CTL_LNG2, OSM_ALT
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_FLIP_NUM] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        KC_BSPC,  KC_PPLS,  KC_P9,    KC_P8,    KC_P7,    KC_PAST,  _______,  _______,  _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_TAB,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        ENT_SFT,  KC_PMNS,  KC_P6,    KC_P5,    KC_P4,    KC_PSLS,  _______,  _______,  _______,  KC_F4,    KC_F5,    KC_F6,    KC_F11,   CTL_ESC,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             KC_CALC,  KC_P3,    KC_P2,    KC_P1,    KC_PEQL,  _______,  _______,  _______,  _______,  KC_F1,    KC_F2,    KC_F3,    KC_F12,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          KC_PDOT,  KC_P0,    SPC_F_SYM,  _______,  _______,  _______,  SPC_SFT,    OSM_CTL,  OSM_ALT
    // |-------------------------------------------------------------------------------------------------------------------------------------------|

    ),
    [_FLIP_SYM] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        KC_DEL,   KC_0,     KC_9,     KC_8,     KC_7,     KC_6,     _______,  _______,  KC_5,     KC_4,     KC_3,     KC_2,     KC_1,     KC_TAB,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_QUOT,  KC_SCLN,  KC_RGHT,  KC_UP,    KC_DOWN,  KC_LEFT,  _______,  _______,  KC_BSLS,  KC_RBRC,  KC_LBRC,  KC_EQL,   KC_GRV,   OSM_CTL,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             _______,  KC_END,   KC_PGUP,  KC_PGDN,  KC_HOME,  _______,  _______,  _______,  KC_PIPE,  KC_RCBR,  KC_LCBR,  KC_PLUS,  KC_TILD,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          OSM_WIN,  OSM_CTL,  _______,    _______,  _______,  _______,  OSM_SFT,    OSM_CTL,  OSM_ALT
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_SPECIAL] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        OSM_CTL,  CTL_Z,    CTL_X,    CTL_C,    CTL_V,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |----+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+----|
             CTL_Z,    CTL_X,    CTL_C,    CTL_V,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    // |-----------------+---------+---------+-----------+---------+---------+---------+-----------+---------+---------+---------------------------|
                          OSM_ALT,  OSM_CTL,  OSM_SFT,    _______,  _______,  _______,  _______,    OSM_CTL,  OSM_WIN
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
    ),
    [_ADJUST] = LAYOUT(
    // |-------------------------------------------------------------------------------------------------------------------------------------------|
        KEY_WAIT, _______,  _______,  _______,  MAC_SLP,  _______,  CNT_RST,  RGB_SPI,  RGB_HUI,  RGB_SAI,  RGB_VAI,  IND_TOG,  RGB_RMOD, KC_INS,
    // |---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------|
        KC_CAPS,  MU_TOGG,  MU_NEXT,  AU_NEXT,  AU_PREV,  _______,  CNT_TOG,  RGB_SPD,  RGB_HUD,  RGB_SAD,  RGB_VAD,  RGB_TOG,  RGB_MOD,  VERSION,
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
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NUM] = { ENCODER_CCW_CW(_______, _______) },
    [_SYM] = { ENCODER_CCW_CW(_______, _______) },
    [_FLIP] = { ENCODER_CCW_CW(_______, _______) },
    [_FLIP_NUM] = { ENCODER_CCW_CW(_______, _______) },
    [_FLIP_SYM] = { ENCODER_CCW_CW(_______, _______) },
    [_SPECIAL] = { ENCODER_CCW_CW(_______, _______) },
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
    if (is_led_counter_enabled && record->event.pressed) {
        led_counter_update(); // 何かキーが押されたら、LEDカウンタを更新。
    }
    switch (keycode) {
        case CNT_TOG: // Turn ON/OFF LED counter. While ON, Effect range is restricted.
            if (record->event.pressed) {
                if(is_led_counter_enabled) { // on --> off
                    led_counter_turn_off();
                } else { // off --> on
                    led_counter_turn_on();
                }

                // Write to EEPROM
                user_config.is_led_counter_enabled = is_led_counter_enabled;
                eeconfig_update_user(user_config.raw);
            }
            return false;
        case CNT_RST: // Reset LED counter to Zero.
            if (record->event.pressed) {
                led_counter_reset();
            }
            return false;
        case VERSION: // Output firmware info.
            if (record->event.pressed) {
                SEND_STRING (QMK_KEYBOARD ":" QMK_KEYMAP " @ " QMK_VERSION " | " QMK_BUILDDATE);
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
// Tap-Hold
//------------------------------------------------------------------------------
// per key settings for HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CMD_LNG1:
        case CMD_LNG2:
        case CTL_LNG1:
        case CTL_LNG2:
        case CTL_ESC:
        case SPC_SFT:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

//------------------------------------------------------------------------------
// Tap Dance
//------------------------------------------------------------------------------
// Tap Danceのインスタンスを初期化
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};

// Tap Danceの状態を決定する関数
int cur_dance (tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    }
    else if (state->count == 2) {
        return DOUBLE_TAP;
    }
    else if (state->count == 3) {
        return TRIPLE_TAP;
    }
    else return 6; //magic number. At some point this method will expand to work for more presses
}

// Tap Danceが終了したときに呼び出される関数
void x_finished_1 (tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);

    switch (xtap_state.state) {
        case SINGLE_TAP:
            layer_move(2);
            break;
        case SINGLE_HOLD:
            layer_on(1);
            break;
        case DOUBLE_TAP:
            layer_move(3);
            break;
        case TRIPLE_TAP:
            layer_clear();
            break;
    }
}

// Tap Danceがリセットされたときに呼び出される関数
void x_reset_1 (tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            layer_off(1);
            break;
        case DOUBLE_TAP:
            break;
        case TRIPLE_TAP:
            break;
    }

    xtap_state.state = 0;
}

// Tap Danceのアクションを定義
tap_dance_action_t tap_dance_actions[] = {
    [TD_SELECTOR] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_1, x_reset_1),
};

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
// RGB Light: LED Counter
//------------------------------------------------------------------------------
void led_counter_turn_on() {
    is_led_counter_enabled = true;
    rgblight_set_effect_range(0, 0);
    led_counter_reset();
}

void led_counter_turn_off() {
    is_led_counter_enabled = false;
    rgblight_set_effect_range(0, 6);
}

void led_counter_reset() {
    rgblight_sethsv_range(LED_COUNTER_DEFAULT_HUE, 255, rgblight_get_val(), 0, 6);
    led_0_hue = LED_COUNTER_DEFAULT_HUE;
    led_1_hue = LED_COUNTER_DEFAULT_HUE;
    led_2_hue = LED_COUNTER_DEFAULT_HUE;
}

void led_counter_update() {
    // LED色を更新し、LED色が一周した場合のみ次のLED色を更新する。
    if(led_counter_hue_update(&led_0_hue)) {
        if(led_counter_hue_update(&led_1_hue)) {
            led_counter_hue_update(&led_2_hue);
        }
    }

    // LED色を表示（左右3個ずつペア）
    rgblight_sethsv_at(led_0_hue, 255, rgblight_get_val(), 0);
    rgblight_sethsv_at(led_1_hue, 255, rgblight_get_val(), 1);
    rgblight_sethsv_at(led_2_hue, 255, rgblight_get_val(), 2);

    rgblight_sethsv_at(led_0_hue, 255, rgblight_get_val(), 3);
    rgblight_sethsv_at(led_1_hue, 255, rgblight_get_val(), 4);
    rgblight_sethsv_at(led_2_hue, 255, rgblight_get_val(), 5);
}

bool led_counter_hue_update(int *led_hue) {
    *led_hue += 32;
    if(*led_hue < 255) {
        return false;
    } else { // 255を超えてhueが一周したら、0にリセット。
        *led_hue = 0;
        return true;
    }
}

//------------------------------------------------------------------------------
// RGB Light: Lighting Layers
//------------------------------------------------------------------------------

// layer information
// 0   base
// 0.1 Caps lock
// 0.2 Scroll lock
// 1   temp1    special
// 2   temp2    temp for Base
// 3   temp3    temp for Base
// 4   temp4    FLIP
// 5   temp5    temp for FLIP
// 6   temp6    temp for FLIP
// 7   temp7    Adjust

// ---------- Both side ---------
// for Base layer: All
const rgblight_segment_t PROGMEM my_base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_FULL, HSV_WHITE}
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
const rgblight_segment_t PROGMEM my_temp1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_GREEN},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_temp2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_CYAN},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_YELLOW},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_temp4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_GREEN},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_temp5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_CYAN},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_YELLOW},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_temp7_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_RED},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_RED}
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
    my_base_layer,
    my_caps_layer,
    my_scroll_lock_layer,
    my_temp1_layer,
    my_temp2_layer,
    my_temp3_layer,
    my_temp4_layer,
    my_temp5_layer,
    my_temp6_layer,
    my_temp7_layer,
    my_blink1_layer,
    my_blink2_layer
);

// ---------- Left side only ---------
// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, ONBOARD_LED_COUNT_PER_SIDE, HSV_WHITE}
);

// for locking status
const rgblight_segment_t PROGMEM my_caps_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD, 1, HSV_RED}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_temp1_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_temp2_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp3_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_temp4_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_temp5_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp6_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_temp7_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_RED}
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
    my_base_layer_left_only,
    my_caps_layer_left_only,
    my_scroll_lock_layer_left_only,
    my_temp1_layer_left_only,
    my_temp2_layer_left_only,
    my_temp3_layer_left_only,
    my_temp4_layer_left_only,
    my_temp5_layer_left_only,
    my_temp6_layer_left_only,
    my_temp7_layer_left_only,
    my_blink1_layer_left_only,
    my_blink2_layer_left_only
);

// ---------- Right side only ---------
// for Default layer (= Base layer)
const rgblight_segment_t PROGMEM my_base_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, ONBOARD_LED_COUNT_PER_SIDE, HSV_WHITE}
);

// for locking status
const rgblight_segment_t PROGMEM my_caps_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_MAGENTA}
);

const rgblight_segment_t PROGMEM my_scroll_lock_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_THIRD + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_RED}
);

// for temporal layer
const rgblight_segment_t PROGMEM my_temp1_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_temp2_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp3_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_temp4_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_GREEN}
);

const rgblight_segment_t PROGMEM my_temp5_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp6_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_YELLOW}
);

const rgblight_segment_t PROGMEM my_temp7_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM my_blink1_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, ONBOARD_LED_COUNT_PER_SIDE, HSV_ORANGE}
);

const rgblight_segment_t PROGMEM my_blink2_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, ONBOARD_LED_COUNT_PER_SIDE, HSV_PINK}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers_right_only[] = RGBLIGHT_LAYERS_LIST(
    my_base_layer_right_only,
    my_caps_layer_right_only,
    my_scroll_lock_layer_right_only,
    my_temp1_layer_right_only,
    my_temp2_layer_right_only,
    my_temp3_layer_right_only,
    my_temp4_layer_right_only,
    my_temp5_layer_right_only,
    my_temp6_layer_right_only,
    my_temp7_layer_right_only,
    my_blink1_layer_right_only,
    my_blink2_layer_right_only
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(3, layer_state_cmp(state, 1));
    rgblight_set_layer_state(4, layer_state_cmp(state, 2));
    rgblight_set_layer_state(5, layer_state_cmp(state, 3));
    rgblight_set_layer_state(6, layer_state_cmp(state, 4));
    rgblight_set_layer_state(7, layer_state_cmp(state, 5));
    rgblight_set_layer_state(8, layer_state_cmp(state, 6));
    rgblight_set_layer_state(9, layer_state_cmp(state, 7));

    return state;
}

// Enabling and disabling lighting layers for default layer
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));

    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    rgblight_set_layer_state(2, led_state.scroll_lock);

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
        case 1: // Bothside
            rgblight_layers = my_rgb_layers;
            break;
        case 2: // Left only
            rgblight_layers = my_rgb_layers_left_only;
            break;
        case 3: // Right only
            rgblight_layers = my_rgb_layers_right_only;
            break;
        default:
            rgblight_layers = NULL;
            rgblight_sethsv_range(HSV_BLACK, 0, 2);
            break;
    }

    // Restore LED conter enabled / disabled
    if (user_config.is_led_counter_enabled) {
        led_counter_turn_on();
    } else {
        led_counter_turn_off();
    }

    // prevent RGB light overrides layer indicator.
    layer_state_set(default_layer_state);
}

// ------------------------------------------------------------------------------
// EEPROM Initialization, EEPROM is getting reset!
// ------------------------------------------------------------------------------
void eeconfig_init_user(void) {
    // user configuration
    user_config.raw = 0;
    user_config.indicator_state = 1; // Layer indicator LED state: 1 = Both side
    user_config.is_led_counter_enabled = false; // LED counter enabled: false
    eeconfig_update_user(user_config.raw); // Write default value to EEPROM now

    // Audio settings
    audio_config.raw = eeconfig_read_audio();
    audio_config.valid = true; // これをtrueにしておかないと、audio.cで初期化されていないと判断され、ここでの設定内容が上書きされてしまう。
    audio_config.enable = false; // Audio機能の初期状態はOFF。ファームウェア開発中に書き換えするたびにピロピロ鳴ってうるさいので、落ち着いたら自分でONにする運用。
    audio_config.clicky_enable = true;
    eeconfig_update_audio(audio_config.raw);
}
