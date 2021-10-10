/* Copyright 2019 e3w2q
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

#pragma once

// place overrides here
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// LEDが足りなくて、本来16個のところ12個しか取り付けていないことの回避策
#ifdef RGBLED_NUM
    #undef RGBLED_NUM
    #define RGBLED_NUM 12
#endif

#ifdef RGBLIGHT_EFFECT_RGB_TEST
    #undef RGBLIGHT_EFFECT_RGB_TEST
#endif

#ifdef RGBLIGHT_LIMIT_VAL
    #undef RGBLIGHT_LIMIT_VAL
    #define RGBLIGHT_LIMIT_VAL 255
#endif

#define RGBLIGHT_DEFAULT_VAL 128

#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE

#define RGBLIGHT_LAYERS
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF // Overriding RGB Lighting on/off status
#define RGBLIGHT_LAYERS_RETAIN_VAL // set Lighting Layer brightness equals to Underglow's value
#define RGBLIGHT_LAYER_BLINK // Enable Blink function
