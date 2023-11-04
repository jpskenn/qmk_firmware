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

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0xB9DD
#define PRODUCT_ID 0xC9D7
#define DEVICE_VER 0x0030
#define MANUFACTURER jpskenn
#define PRODUCT Nora

/* key matrix size */
// Same number for Round-Robin matrix.
#define MATRIX_ROWS 10
#define MATRIX_COLS 8

// Same pins for Round-Robin matrix.
#define MATRIX_ROW_PINS { D3, D2, D7, B7, F1, D5, D4, D6, B4, F0 }
#define MATRIX_COL_PINS { B0, C7, B6, B5, F7, F6, F5, F4 }
#define DIODE_DIRECTION COL2ROW

/* RGBLIGHT */
#define RGB_DI_PIN E6
#ifdef RGB_DI_PIN

  #ifdef RGB_MATRIX_ENABLE
    #define DRIVER_LED_TOTAL 71
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150
    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 8
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES

  #else
    #define RGBLED_NUM 71
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 150 /* The maximum brightness level */
    #define RGBLIGHT_DEFAULT_VAL 127 /* The default brightness level */
    /* Lighting Layers */
    #define RGBLIGHT_LAYERS
    #define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Overriding RGB Lighting on/off status
    #define RGBLIGHT_LAYERS_RETAIN_VAL // Keeps RGB values between lighting layer changes
    #define RGBLIGHT_EFFECT_RGB_TEST
    //   #define RGBLIGHT_ANIMATIONS
    //   #define RGBLIGHT_EFFECT_TWINKLE
  #endif

#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* External EEPROM */
// Use 24LC64 EEPROM
#define EEPROM_I2C_24LC64
// Set MAX_ADDR to specify actual EEPROM size.
// If it's not set, EEPROM size will be set ATmega32u4's 1023.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191
// How many layers to use with VIA / Remap.
#define DYNAMIC_KEYMAP_LAYER_COUNT 7 // default:4
