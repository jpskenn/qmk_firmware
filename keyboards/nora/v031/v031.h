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

#include "quantum.h"

// Indicator LED index
#ifdef RGB_MATRIX_ENABLE

    // Left & Right space keys
    #if RGB_MATRIX_LED_COUNT == 71 // "Full" layout

        #define LED_INDEX_LSPC 58
        #define LED_INDEX_RSPC 62

    #else

        #ifdef ENCODER_ENABLE // "FW + Rotary Encoder" layout

            #define LED_INDEX_LSPC 58
            #define LED_INDEX_RSPC 62

        #else // "Fireless Wings" layout

            #define LED_INDEX_LSPC 58
            #define LED_INDEX_RSPC 61

        #endif
    #endif

    // R4 Inside keys
    #define LED_INDEX_R4_RIGHT_INSIDE 48
    #define LED_INDEX_R4_LEFT_INSIDE 49

#endif
