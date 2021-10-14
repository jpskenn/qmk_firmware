/* Copyright 2021 jpskenn
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

enum layer_number {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT( /* Base */
    KC_P7,              KC_P8,              KC_P9,              KC_PSLS,
    KC_P4,              KC_P5,              KC_P6,              KC_PPLS,
    KC_P1,              KC_P2,              KC_P3,              KC_PENT,
    LT(_LOWER,KC_P0),   KC_PDOT,            DM_PLY1,            LT(_RAISE,DM_PLY2),
    XXXXXXX,  XXXXXXX  // for encoders
  ),

  [_LOWER] = LAYOUT(
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            DM_REC1,            MO(_ADJUST),
    XXXXXXX,            XXXXXXX
  ),

  [_RAISE] = LAYOUT(
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            XXXXXXX,            XXXXXXX,            XXXXXXX,
    MO(_ADJUST),        XXXXXXX,            XXXXXXX,            DM_REC2,
    XXXXXXX,            XXXXXXX
  ),

  [_ADJUST] = LAYOUT(
    RGB_MOD,            RGB_HUI,            RGB_SAI,            RGB_VAI,
    RGB_RMOD,           RGB_HUD,            RGB_SAD,            RGB_VAD,
    RGB_TOG,            RGB_SPI,            XXXXXXX,            XXXXXXX,
    XXXXXXX,            RGB_SPD,            DM_RSTP,            XXXXXXX,
    XXXXXXX,            XXXXXXX
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  }
  return true;
}


//------------------------------------------------------------------------------
// Dynamic Macro settings
//------------------------------------------------------------------------------
bool savedNumLayer = false; // Stored Num layer status

// void dynamic_macro_play_user(int8_t direction) {
//     // Revert layer indicator, just after macro played.
//     // It returns to base layer. WHY???
//     layer_state_set_user(layer_state);
// }

void dynamic_macro_record_start_user(void) {
    // rgblight_blink_layer_repeat(3, 250, 3);
}

void dynamic_macro_record_end_user(int8_t direction) {
    // rgblight_blink_layer_repeat(4, 250, 3);
}



//------------------------------------------------------------------------------
// RGB Matrix settings
//------------------------------------------------------------------------------
#ifdef RGB_MATRIX_ENABLE

// LED matrix definition
// NOTE: We should define this at "keyboard.h".
// led_config_t g_led_config = { {
//     // Key Matrix to LED Index
//     { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, NO_LED, NO_LED }
//     }, {
//     // LED Index to Physical Position
//     { 0,  0 }, {  75,  0 }, { 149,  0 }, { 224, 0 },
//     { 0, 21 }, { 75, 21 }, { 149, 21 }, { 224, 21 },
//     { 0, 43 }, { 75, 43 }, { 149, 43 }, { 224, 43 },
//     { 0, 64 }, { 75, 64 }, { 149, 64 }, { 224, 64 },
//     }, {
//     // LED Index to Flag
//     //
//     // LED_FLAG_NONE        0x00    If this LED has no flags
//     // LED_FLAG_ALL         0xFF    If this LED has all flags
//     // LED_FLAG_MODIFIER    0x01    If the LED is on a modifier key
//     // LED_FLAG_UNDERGLOW   0x02    If the LED is for underglow
//     // LED_FLAG_KEYLIGHT    0x04    If the LED is for key backlight
//     // LED_FLAG_INDICATOR   0x08    If the LED is for keyboard state indication
//     4+8, 4+8, 4+8, 4+8,
//     4, 4, 4, 4,
//     4, 4, 4, 4,
//     4+1, 4+1, 4+1, 4+1,
// } };
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, NO_LED,NO_LED,NO_LED,NO_LED, NO_LED, NO_LED }
    }, {
    // LED Index to Physical Position
    { 0,  0 }, {  75,  0 }, { 149,  0 }, { 224, 0 },
    { 0, 21 }, { 75, 21 }, { 149, 21 }, { 224, 21 },
    { 0, 43 }, { 75, 43 }, { 149, 43 }, { 224, 43 },
    { 0, 64 }, { 75, 64 }, { 149, 64 }, { 224, 64 },
    }, {
    // LED Index to Flag
    //
    // LED_FLAG_NONE        0x00    If this LED has no flags
    // LED_FLAG_ALL         0xFF    If this LED has all flags
    // LED_FLAG_MODIFIER    0x01    If the LED is on a modifier key
    // LED_FLAG_UNDERGLOW   0x02    If the LED is for underglow
    // LED_FLAG_KEYLIGHT    0x04    If the LED is for key backlight
    // LED_FLAG_INDICATOR   0x08    If the LED is for keyboard state indication
    4+8, 4+8, 4+8, 4+8,
    4, 4, 4, 4,
    4, 4, 4, 4,
    2, 2, 2, 2,
} };

// Layer indicator
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    for (uint8_t i = led_min; i <= led_max; i++) {
        if (g_led_config.flags[i] & LED_FLAG_INDICATOR) {
            switch(get_highest_layer(layer_state|default_layer_state)) {
                case _LOWER:
                    rgb_matrix_set_color(i, RGB_CYAN);
                    break;
                case _RAISE:
                    rgb_matrix_set_color(i, RGB_GREEN);
                    break;
                case _ADJUST:
                    rgb_matrix_set_color(i, RGB_RED);
                    break;
                default:
                    break;
            }
        } else if (g_led_config.flags[i] == LED_FLAG_UNDERGLOW) {
            rgb_matrix_set_color(i, RGB_PURPLE);
        }
    }
}

#endif


//------------------------------------------------------------------------------
// RGB Light settings
//------------------------------------------------------------------------------
#ifdef RGBLIGHT_LAYERS

// Indicator LED settings
#define KGSN_LED_INDICATOR_INDEX 0         // where to start indicator
#define KGSN_LED_INDICATOR_COUNT 4         // how many LEDs used for indicator
#define KGSN_LED_INDICATOR_CHANGE_COUNT 4  // how many LEDs to change for temporally layer
#define KGSN_LED_INDICATOR_HALF_CHANGE_COUNT 2  // how many LEDs to change for temporally layer
#define KGSN_LED_DIMMER_LEVEL 150          // brightness dimmer

const rgblight_segment_t PROGMEM my_lower_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {KGSN_LED_INDICATOR_INDEX , KGSN_LED_INDICATOR_HALF_CHANGE_COUNT, HSV_RED - KGSN_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_raise_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {KGSN_LED_INDICATOR_INDEX + 2 , KGSN_LED_INDICATOR_HALF_CHANGE_COUNT, HSV_RED - KGSN_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_adjust_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {KGSN_LED_INDICATOR_INDEX , KGSN_LED_INDICATOR_CHANGE_COUNT, HSV_RED - KGSN_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_blink1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {KGSN_LED_INDICATOR_INDEX , KGSN_LED_INDICATOR_COUNT, HSV_ORANGE - KGSN_LED_DIMMER_LEVEL}
);

const rgblight_segment_t PROGMEM my_blink2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {KGSN_LED_INDICATOR_INDEX , KGSN_LED_INDICATOR_COUNT, HSV_PINK - KGSN_LED_DIMMER_LEVEL}
);

// Define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_lower_layer,
    my_raise_layer,
    my_adjust_layer,
    my_blink1_layer,
    my_blink2_layer
);

// Enabling and disabling lighting layers
layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _ADJUST));

    return state;
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

void matrix_init_user(void) {

    // Turn off Pro Micro's red LED
    DDRD &= ~(1<<5);
    PORTD &= ~(1<<5);

    DDRB &= ~(1<<0);
    PORTB &= ~(1<<0);

}
