/* Copyright 2021 Takeshi Nishio
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

// Change number of LEDs for "RE layout".
#ifdef WS2812_DI_PIN
    #ifdef RGB_MATRIX_ENABLE
        #undef RGB_MATRIX_LED_COUNT
        #define RGB_MATRIX_LED_COUNT 65
    #else
        #undef RGBLED_NUM
        #define RGBLED_NUM 65
    #endif
#endif

#ifdef RGB_MATRIX_ENABLE
    #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#endif
