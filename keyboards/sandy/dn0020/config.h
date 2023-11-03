/*
Copyright 2023 Takeshi Nishio

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

#pragma once

// Encoder triggers specific key matrix position,
// when turn knob clockwise or counterclockwise.
// This is handy to assign key codes by VIA.

// Number of encoder
#define ENCODERS 2

/* RGB LED */
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_DEFAULT_VAL 80
    /*== Lighting Layers ==*/
    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Overriding RGB Lighting on/off status
    #define RGBLIGHT_LAYERS_RETAIN_VAL // set layer brightness to RGB Light's value (as returned by rgblight_get_val())
    #define RGBLIGHT_LAYER_BLINK // Enable Blink function
    #define RGBLIGHT_MAX_LAYERS 11 // Default 8.

/* External EEPROM for Dynamic keymap (VIA / Remap) */
// Use 24LC64 type EEPROM
#define EEPROM_I2C_24LC64
// Set MAX_ADDR to specify actual EEPROM size.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191
// How many layers to use with VIA / Remap.
#define DYNAMIC_KEYMAP_LAYER_COUNT 8 // default:4

//NOTE
// ProMicroへテスト書き込みする際は、
// EEPROMサイズが足りないので、レイヤー2個で、とりあえず動作確認だけする
//   - rules.mkのEEPROMドライバをコメントアウトする
//   - 下の2行のコメント外す
//#define DYNAMIC_KEYMAP_LAYER_COUNT 2 // default:4
//#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 1023
