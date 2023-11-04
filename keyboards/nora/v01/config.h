/*
Copyright 2021 Takeshi Nishio

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

// Same pins for Round-Robin matrix.
#define MATRIX_ROW_PINS { F1, B7, D2, F6, F7, B0, F4, F5, C7, B6 }
#define MATRIX_COL_PINS { F0, D3, D5, D4, D6, D7, B4, B5 }
#define DIODE_DIRECTION COL2ROW

/* RGBLIGHT */
  #define RGBLED_NUM 16
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 240 /* The maximum brightness level */
  #define RGBLIGHT_DEFAULT_VAL 127 /* The default brightness level */
  /* Lighting Layers */
  #define RGBLIGHT_LAYERS
  #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Overriding RGB Lighting on/off status
  #define RGBLIGHT_LAYERS_RETAIN_VAL // Keeps RGB values between lighting layer changes
  #define RGBLIGHT_ANIMATIONS
  #define RGBLIGHT_EFFECT_TWINKLE

/* External EEPROM & Dynamic keymap */
// Use 24LC64 EEPROM
#define EEPROM_I2C_24LC64
// Set MAX_ADDR to specify actual EEPROM size.
// If it's not set, EEPROM size will be set ATmega32u4's 1023.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191
// How many layers to use with VIA / Remap.
#define DYNAMIC_KEYMAP_LAYER_COUNT 7 // default:4
