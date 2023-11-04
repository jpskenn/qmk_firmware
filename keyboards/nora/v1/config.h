/*
Copyright 2022 Takeshi Nishio

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
#define MATRIX_ROW_PINS { D3, D2, D7, B7, F1, D5, D4, D6, B4, F0 }
#define MATRIX_COL_PINS { B0, C7, B6, B5, F7, F6, F5, F4 }
#define DIODE_DIRECTION COL2ROW

/* Rotary Encoder */
#ifdef ENCODER_ENABLE
// Encoder triggers specific key matrix position,
// when turn knob clockwise or counterclockwise.
// This is handy to assign key codes by VIA.

// Number of endoder
#define ENCODERS 1

// Mappings of encoder rotation to key position in key matrix.
// --> k97, k47
#define ENCODERS_CW_KEY  { { 7, 9 } }
#define ENCODERS_CCW_KEY { { 7, 4 } }

#endif

/* Audio */
#ifdef AUDIO_ENABLE
#define AUDIO_PIN C6
#define AUDIO_CLICKY
#endif

/* RGB LED */
#ifdef RGB_MATRIX_ENABLE
  /* RGB Matrix */

  // LEDs
  // Full: 71(default)
  // FW :  64
  // RE :  62
  #define DRIVER_LED_TOTAL 71

  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 128
  #define RGB_MATRIX_STARTUP_VAL 40
  #define RGB_MATRIX_HUE_STEP 4
  #define RGB_MATRIX_SAT_STEP 8
  #define RGB_MATRIX_VAL_STEP 8
  #define RGB_MATRIX_SPD_STEP 8

  #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
  #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
  #define RGB_MATRIX_KEYPRESSES

  // --- Effects ---
  #define ENABLE_RGB_MATRIX_ALPHAS_MODS
  #define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
  #define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_BREATHING
  #define ENABLE_RGB_MATRIX_BAND_VAL
  #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
  #define ENABLE_RGB_MATRIX_CYCLE_ALL
  #define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
  #define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
  #define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
  #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
  #define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
  #define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
  #define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
  #define ENABLE_RGB_MATRIX_DUAL_BEACON
  #define ENABLE_RGB_MATRIX_RAINBOW_BEACON
  #define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
  #define ENABLE_RGB_MATRIX_RAINDROPS
  #define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
  #define ENABLE_RGB_MATRIX_HUE_BREATHING
  #define ENABLE_RGB_MATRIX_PIXEL_RAIN
  #define ENABLE_RGB_MATRIX_PIXEL_FLOW
  #define ENABLE_RGB_MATRIX_PIXEL_FRACTAL

  // enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
  // #define ENABLE_RGB_MATRIX_TYPING_HEATMAP // Heatmap is not shown correctly with this keyboard's dual-row matrix.
  #define ENABLE_RGB_MATRIX_DIGITAL_RAIN

  // enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
  #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
  #define ENABLE_RGB_MATRIX_SPLASH
  #define ENABLE_RGB_MATRIX_MULTISPLASH
  #define ENABLE_RGB_MATRIX_SOLID_SPLASH
  #define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif

/* External EEPROM */
// Use 24LC64 type EEPROM
#define EEPROM_I2C_24LC64
// Set MAX_ADDR to specify actual EEPROM size.
// NOTE: If it's not set, the size will be set to 1023 by default.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191
// How many layers to use with VIA / Remap.
#define DYNAMIC_KEYMAP_LAYER_COUNT 10 // default:4
