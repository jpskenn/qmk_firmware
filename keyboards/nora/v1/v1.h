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

#include "quantum.h"

// Indicator LED
#ifdef RGB_MATRIX_ENABLE

    // LED Index to left & right space keys
    #if RGB_MATRIX_LED_COUNT == 71 // "Full" layout
        #define LED_INDEX_LSPC 64
        #define LED_INDEX_RSPC 68
    #endif

    #if RGB_MATRIX_LED_COUNT == 64 // FW layout
        #define LED_INDEX_LSPC 58
        #define LED_INDEX_RSPC 61
    #endif

    #if RGB_MATRIX_LED_COUNT == 62 // RE layout
        #define LED_INDEX_LSPC 56
        #define LED_INDEX_RSPC 59
    #endif

#endif
