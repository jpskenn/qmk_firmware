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

#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {      0,      2,      4,      6,      8,     10,     12,     14 },
  { NO_LED,     29,     27,     25,     23,     21,     19,     17 },
  { NO_LED,     32,     34,     36,     38,     40,     42,     44 },
  {     60,     58,     56,     54,     52,     50,     48,     46 },
  { NO_LED, NO_LED,     63, NO_LED,     66,     68,     70, NO_LED },
  {      1,      3,      5,      7,      9,     11,     13,     15 },
  {     30,     28,     26,     24,     22,     20,     18,     16 },
  {     31,     33,     35,     37,     39,     41,     43,     45 },
  {     61,     59,     57,     55,     53,     51,     49,     47 },
  { NO_LED,     62,     64,     65,     67,     69, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position
  {15,16}, {30,16}, {45,16}, {60,16}, {75,16}, {90,16}, {105,16}, {119,16}, {134,16}, {149,16}, {164,16}, {179,16}, {194,16}, {209,16}, {224,16}, {239,16},
  {19,32}, {37,32}, {52,32}, {67,32}, {82,32}, {97,32}, {112,32}, {127,32}, {142,32}, {157,32}, {172,32}, {187,32}, {202,32}, {217,32}, {228,32},
  {19,48}, {37,48}, {52,48}, {67,48}, {82,48}, {97,48}, {112,48}, {127,48}, {142,48}, {157,48}, {172,48}, {187,48}, {202,48}, {217,48}, {228,48},
  {15,64}, {30,64}, {45,64}, {60,64}, {75,64}, {90,64}, {105,64}, {119,64}, {134,64}, {149,64}, {164,64}, {179,64}, {194,64}, {209,64}, {224,64}, {239,64},
  {56,80}, {75,80}, {93,80}, {112,80}, {127,80}, {142,80}, {161,80}, {179,80}, {198,80}
}, {
  // LED Index to Flag
  8, 8, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
   1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
          1,  1, 4,  4, 4, 4,  4,  1,  1
} };
#endif
