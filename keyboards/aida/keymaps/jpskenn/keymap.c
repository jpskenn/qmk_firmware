// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "version.h"
#ifdef AUDIO_ENABLE
#include "audio.h"
#endif

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
enum layers {
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
  LCTR_RST,
  LCTR_TOG,
  CNT_RST,
  CNT_TOG,
};

// key code macros
#define Q_BASE2   LT(_BASE2, KC_Q)
#define TAB_F_NUM   LT(_BASE3, KC_TAB)
#define ENT_RAI1    LT(_RAISE1, KC_ENT)
//#define ZH_BASE3    LT(_BASE3, JP_ZKHK)
#define SP_LOW1     LT(_LOWER1, KC_SPC)
#define SP_RAI1     LT(_RAISE1, KC_SPC)
#define SP_LOW2     LT(_LOWER2, KC_SPC)
#define SP_ADJ      LT(_ADJUST, KC_SPC)

#define SPC_SFT      LSFT_T(KC_SPC)
#define BS_SFT      LSFT_T(KC_BSPC)

#define ESC_ALT     LALT_T(KC_ESC)

#define ESC_CTL     LCTL_T(KC_ESC)

#define BASE1       DF(_BASE1)
#define BASE2       DF(_BASE2)
#define TG_NUM      TG(_BASE3)

#define LNG1_GUI   LGUI_T(KC_LNG1)
#define LNG2_GUI   LGUI_T(KC_LNG2)
#define LNG1_CTL   LCTL_T(KC_LNG1)
#define LNG2_CTL   LCTL_T(KC_LNG2)

#define MAC_SLP     LAG(KC_EJCT)
#define MAC_PSCR    LSG(KC_5)
#define WIN_PSCR    LSG(KC_S)

#define OSM_WIN   OSM(KC_LWIN)  // RemapでCtrl + ShiftなOSMとして扱われている。なぜ？


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE1] = LAYOUT(
    //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
           KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                 KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
    //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
           KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                 KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,
    //---------+---------+---------+---------+---------+---------| |---------+---------+---------+---------+---------+---------//
      KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_ESC,     KC_ENT,   KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,
    //-----------------+---------+---------+-----------+---------| |---------+---------+-----------+---------------------------//
                        ESC_ALT,  LNG2_CTL,SPC_SFT,    TAB_F_NUM,  BS_SFT,   ENT_RAI1, LNG1_CTL,  OSM_WIN
),
[_BASE2] = LAYOUT(
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
   //---------+---------+---------+---------+---------+---------| |---------+---------+---------+---------+---------+---------//
     _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,
   //-----------------+---------+---------+-----------+---------| |---------+---------+-----------+---------------------------//
                       _______,  _______,  _______, _______,       _______,  _______,  _______,    _______
),
[_BASE3] = LAYOUT(
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          KC_F10,   KC_F9,    KC_F8,    KC_F7,    _______,              KC_PAST,  KC_P7,    KC_P8,    KC_P9,    KC_PPLS,
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          KC_F11,   KC_F6,    KC_F5,    KC_F4,    _______,              KC_PSLS,  KC_P4,    KC_P5,    KC_P6,    KC_MINS,
   //---------+---------+---------+---------+---------+---------| |---------+---------+---------+---------+---------+---------//
     KC_F12,   KC_F3,    KC_F2,    KC_F1,    _______,  _______,    _______,  KC_TAB,   KC_P1,    KC_P2,    KC_P3,    KC_CALC,
   //-----------------+---------+---------+-----------+---------| |---------+---------+-----------+---------------------------//
                       _______,  _______,  _______,    _______,    _______,  _______,  KC_P0,      KC_PDOT
),
[_LOWER1] = LAYOUT(
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
   //---------+---------+---------+---------+---------+---------| |---------+---------+---------+---------+---------+---------//
     _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,
   //-----------------+---------+---------+-----------+---------| |---------+---------+-----------+---------------------------//
                       _______,  _______,  _______, _______,       _______,  _______,  _______,    _______
),
[_LOWER2] = LAYOUT(
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
   //---------+---------+---------+---------+---------+---------| |---------+---------+---------+---------+---------+---------//
     _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,
   //-----------------+---------+---------+-----------+---------| |---------+---------+-----------+---------------------------//
                       _______,  _______,  _______, _______,       _______,  _______,  _______,    _______
),
[_RAISE1] = LAYOUT(
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                 KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          KC_GRV,   KC_EQL,   KC_LBRC,  KC_RBRC,  KC_BSLS,              KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_SCLN,
   //---------+---------+---------+---------+---------+---------| |---------+---------+---------+---------+---------+---------//
     KC_TILD,  KC_PLUS,  KC_LCBR,  KC_RCBR,  KC_PIPE,  _______,    _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_QUOT,
   //-----------------+---------+---------+-----------+---------| |---------+---------+-----------+---------------------------//
                       _______,  _______,  _______,    _______,    _______,  _______,  KC_VOLD,    KC_VOLU
),
[_RAISE2] = LAYOUT(
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          _______,  _______,  _______,  _______,  _______,              _______,  _______,  _______,  _______,  _______,
   //---------+---------+---------+---------+---------+---------| |---------+---------+---------+---------+---------+---------//
     _______,  _______,  _______,  _______,  _______,  _______,    _______,  _______,  _______,  _______,  _______,  _______,
   //-----------------+---------+---------+-----------+---------| |---------+---------+-----------+---------------------------//
                       _______,  _______,  _______, _______,       _______,  _______,  _______,    _______
),
[_ADJUST] = LAYOUT(
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          BASE1,    BASE2,    TG_NUM,   MAC_SLP,  _______,              UG_HUEU,  UG_SATU,  UG_VALU,  IND_TOG,  UG_NEXT,
   //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
          MU_TOGG,  MU_NEXT,  AU_NEXT,  AU_PREV,  _______,              UG_HUED,  UG_SATD,  UG_VALD,  UG_TOGG,  UG_PREV,
   //---------+---------+---------+---------+---------+---------| |---------+---------+---------+---------+---------+---------//
     AU_TOGG,  CK_TOGG,  CK_DOWN,  CK_UP,    CK_RST,   DM_REC1,    DM_REC2,  TG_NUM,   KC_NUM,   KC_PSCR,  KC_SCRL,  KC_PAUS,
   //-----------------+---------+---------+-----------+---------| |---------+---------+-----------+---------------------------//
                       _______,  _______,  _______, _______,       _______,  _______,  _______,    _______
)
};

// LAYOUT TEMPLATE
//    //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
//           ,  ,  ,  ,  ,              ,  ,  ,  ,  ,
//    //----+---------+---------+---------+---------+---------+----| |----+---------+---------+---------+---------+---------+----//
//           ,  ,  ,  ,  ,              ,  ,  ,  ,  ,
//    //---------+---------+---------+---------+---------+---------| |---------+---------+---------+---------+---------+---------//
//      ,  ,  ,  ,  ,  ,    ,  ,  ,  ,  ,  ,
//    //-----------------+---------+---------+-----------+---------| |---------+---------+-----------+---------------------------//
//                        ,  ,  , ,       ,  ,  ,

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
        31, 32, 33, 34, 35,     36, 37, 38, 39, 40,
        21, 22, 23, 24, 25,     26, 27, 28, 29, 30,
     9, 10, 11, 12, 13, 14,     15, 16, 17, 18, 19, 20,
             0,  1,  2,  3,      4,  5,  6,  7,  8
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
// Chordal Hold Handedness
//------------------------------------------------------------------------------
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R','R','R','R','R','R','R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L', 'R','R','R','R','R','R','R',
          'L', 'L', 'L', 'L', 'L', 'L', '*','R','R','R','R','R','R',
                    '*', '*', '*', '*', '*','*','*','*','*'
        );

//------------------------------------------------------------------------------
// Tap-Hold
//------------------------------------------------------------------------------
// per key settings for HOLD_ON_OTHER_KEY_PRESS_PER_KEY
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LNG1_GUI:
        case LNG2_GUI:
        case LNG1_CTL:
        case LNG2_CTL:
        case ESC_CTL:
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
static tap xtap_state_l = {
    .is_press_action = true,
    .state = 0
};

static tap xtap_state_r = {
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
        if (!state->pressed) return DOUBLE_TAP;
        else return DOUBLE_HOLD;
    }
    else if (state->count == 3) {
        if (!state->pressed) return TRIPLE_TAP;
        return TRIPLE_HOLD;
    }
    else return 9; //magic number. At some point this method will expand to work for more presses
}

// Tap Danceが終了したときに呼び出される関数
void x_finished_l (tap_dance_state_t *state, void *user_data) {
    xtap_state_l.state = cur_dance(state);

    switch (xtap_state_l.state) {
        case SINGLE_TAP:
            layer_clear();
            break;
        case SINGLE_HOLD:
            layer_on(_SPECIAL);
            break;
        case DOUBLE_TAP:
            layer_move(_NUM);
            break;
        case DOUBLE_HOLD:
            layer_on(_NUM);
            break;
        case TRIPLE_TAP:
            layer_move(_SYM);
            break;
        case TRIPLE_HOLD:
            layer_on(_SYM);
            break;
    }
}

void x_finished_r (tap_dance_state_t *state, void *user_data) {
    xtap_state_r.state = cur_dance(state);

    switch (xtap_state_r.state) {
        case SINGLE_TAP:
            layer_clear();
            break;
        case SINGLE_HOLD:
            layer_on(_SPECIAL);
            break;
        case DOUBLE_TAP:
            layer_move(_NUM);
            break;
        case DOUBLE_HOLD:
            layer_on(_NUM);
            break;
        case TRIPLE_TAP:
            layer_move(_SYM);
            break;
        case TRIPLE_HOLD:
            layer_on(_SYM);
            break;
    }
}

// Tap Danceがリセットされたときに呼び出される関数
void x_reset_l (tap_dance_state_t *state, void *user_data) {
    switch (xtap_state_l.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            layer_off(_SPECIAL);
            break;
        case DOUBLE_TAP:
            break;
        case DOUBLE_HOLD:
            layer_off(_NUM);
            break;
        case TRIPLE_TAP:
            break;
        case TRIPLE_HOLD:
            layer_off(_SYM);
            break;
    }

    xtap_state_l.state = 0;
}

void x_reset_r (tap_dance_state_t *state, void *user_data) {
    switch (xtap_state_r.state) {
        case SINGLE_TAP:
            break;
        case SINGLE_HOLD:
            layer_off(_SPECIAL);
            break;
        case DOUBLE_TAP:
            break;
        case DOUBLE_HOLD:
            layer_off(_NUM);
            break;
        case TRIPLE_TAP:
            break;
        case TRIPLE_HOLD:
            layer_off(_SYM);
            break;
    }

    xtap_state_r.state = 0;
}

// Tap Danceのアクションを定義
tap_dance_action_t tap_dance_actions[] = {
    [TD_SELECTOR_L] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_l, x_reset_l),
    [TD_SELECTOR_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_r, x_reset_r),
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
// 0   BASE
// 0.1 Caps lock
// 0.2 Scroll lock
// 1   num
// 2   sym
// 3   FLIP
// 4   FLIP num
// 5   FLIP sym
// 6   Special
// 7   Adjust

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
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_CYAN},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_CHARTREUSE},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_temp3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 3, HSV_BLUE},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 3, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_temp4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_CYAN},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_CHARTREUSE},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_temp6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 3, HSV_GOLD},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 3, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_temp7_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 3, HSV_RED},
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 3, HSV_RED}
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
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp2_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 1, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_temp3_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 3, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_temp4_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp5_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 2, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_temp6_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 3, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_temp7_layer_left_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST, 3, HSV_RED}
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
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp2_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 1, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_temp3_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 3, HSV_BLUE}
);

const rgblight_segment_t PROGMEM my_temp4_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_CYAN}
);

const rgblight_segment_t PROGMEM my_temp5_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 2, HSV_CHARTREUSE}
);

const rgblight_segment_t PROGMEM my_temp6_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 3, HSV_GOLD}
);

const rgblight_segment_t PROGMEM my_temp7_layer_right_only[] = RGBLIGHT_LAYER_SEGMENTS(
    {ONBOARD_LED_INDEX_FIRST + ONBOARD_LED_COUNT_PER_SIDE, 3, HSV_RED}
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
