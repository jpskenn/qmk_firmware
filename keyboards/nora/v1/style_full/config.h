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

/* RGB Matrix */
#ifdef RGB_MATRIX_ENABLE
    // LEDs
    // Full: 71
    // FW :  64
    // RE :  62
    #define RGB_MATRIX_LED_COUNT 71

    #define RGB_MATRIX_STARTUP_VAL 40
    #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_COLOR
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_KEYPRESSES

    // LED Index to left & right space keys
    #define LED_INDEX_LSPC 64
    #define LED_INDEX_RSPC 68
#endif
