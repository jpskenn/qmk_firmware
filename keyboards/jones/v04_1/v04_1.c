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

#include "v04_1.h"

#if defined(AUDIO_ENABLE) && defined(MUSIC_MAP)
//TODO Music-mapを良い感じにする
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(
    0,  24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
      0,  12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24,
      0,  12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23,  24,
    0,  0,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,
    0,  0,  0,  0,     0,     0,  0,     0,  0,  0,  0,  0,  0,
  0,  0,                                                   0,  0
);
#endif

led_config_t g_led_config = {
{
  // Key Matrix to LED Index
    { NO_LED, 2, 2, NO_LED, 0, 2, 2, 2, 0, 0 },
    { 0, NO_LED, 2, NO_LED, 0, 2, 2, 2, 0, 0 },
    { 1, NO_LED, NO_LED, 3, 1, 3, 3, 3, 1, 1 },
    { 1, 3, 3, NO_LED, 1, 3, 3, 3, 1, 1 },
    { NO_LED, 3, 3, NO_LED, NO_LED, 3, 1, 3, 1, 1 },

    { 0, 2, 2, 2, 0, NO_LED, 0, NO_LED, NO_LED, 0 },
    { 0, 2, 2, 2, 0, NO_LED, NO_LED, NO_LED, NO_LED, 0 },
    { 1, 3, 3, 3, 1, NO_LED, NO_LED, NO_LED, NO_LED, 1 },
    { 1, 3, 3, 3, 1, 1, 1, NO_LED, NO_LED, 1 },
    { 1, 3, 3, 3, 1, 3, 3, NO_LED, 1, NO_LED }
}, {
  // LED Index to Physical Position
  { 16, 32 }, { 16,  48 }, { 240,  32 }, { 240,  48 }
}, {
  // LED Index to Flag
  8, 8, 8, 8
}
};
