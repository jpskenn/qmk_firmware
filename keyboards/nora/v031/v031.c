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

#ifdef AUDIO_ENABLE
const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT(
    45 ,46, 47, 48, 49, 59, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
    30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15,
    0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0
);
#endif

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {

#if RGB_MATRIX_LED_COUNT == 71 // "Full" layout
{
  // Key Matrix to LED Index
  {      0,      2,      4,      6,      8,     10,     12,     14 },
  { NO_LED,     29,     27,     25,     23,     21,     19,     17 },
  { NO_LED,     32,     34,     36,     38,     40,     42,     44 },
  {     61,     59,     57,     55,     53,     51,     49,     47 },
  { NO_LED, NO_LED,     63,     65,     66,     68,     70, NO_LED },
  {      1,      3,      5,      7,      9,     11,     13,     15 },
  {     30,     28,     26,     24,     22,     20,     18,     16 },
  {     31,     33,     35,     37,     39,     41,     43,     45 },
  {     60,     58,     56,     54,     52,     50,     48,     46 },
  { NO_LED,     62,     64, NO_LED,     67,     69, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position. NOTE: R2 & R4 are inverted
  {15,16},  {30,16},    {45,16},    {60,16},    {75,16},    {90,16},    {105,16},   {119,16},   {134,16},   {149,16},   {164,16},   {179,16},   {194,16},   {209,16},   {224,16},   {239,16},
        {228,32}, {217,32},   {202,32},   {187,32},   {172,32},   {157,32},   {142,32},   {127,32},   {112,32},   {97,32},    {82,32},    {67,32},    {52,32},    {37,32},    {19,32},
        {19,48},  {37,48},    {52,48},    {67,48},    {82,48},    {97,48},    {112,48},   {127,48},   {142,48},   {157,48},   {172,48},   {187,48},   {202,48},   {217,48},   {228,48},
  {239,64}, {224,64},   {209,64},   {194,64},   {179,64},   {164,64},   {149,64},                           {105,64},   {90,64},    {75,64},    {60,64},    {45,64},    {30,64},    {15,64},
                                    {52,80},    {71,80},    {90,80},    {108,80},         {127,80},         {146,80},   {164,80},   {183,80},   {202,80}
}, {
  // LED Index to Flag
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
   1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
   1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
  1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
          1,  1,  9,  1, 1, 1,  9,  1,  1
}

#else

#ifdef ENCODER_ENABLE // "FW + Rotary Encoder" layout
// NOTE
// DN0031では、RE使用時に、REを配置したことによって未使用となるLEDのスキップジャンパを基板に入れ忘れていた。
// そのため、R3の中央2個のLEDは、
// 実際に基板に取り付けられ、LEDマトリクスにも存在するが、
// 押されるスイッチがないので、反応しないということになる。

{
  // Key Matrix to LED Index
  {      0,      2,      4,      6, NO_LED,      8,     10,     12 },
  { NO_LED,     26,     24,     22, NO_LED,     19,     17,     15 },
  { NO_LED,     29,     31,     33, NO_LED,     36,     38,     40 },
  {     55,     53,     51,     49, NO_LED,     47,     45,     43 },
  { NO_LED, NO_LED,     57,     59,     60,     62,     64, NO_LED },
  {      1,      3,      5, NO_LED,      7,      9,     11,     13 },
  {     27,     25,     23,     21,     20,     18,     16,     14 },
  {     28,     30,     32,     34,     35,     37,     39,     41 },
  {     54,     52,     50, NO_LED,     48,     46,     44,     42 },
  { NO_LED,     56,     58, NO_LED,     61,     63, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position. NOTE: R2 & R4 are inverted
  {15,16},  {30,16},    {45,16},    {60,16},    {75,16},    {90,16},    {105,16},               {149,16},   {164,16},   {179,16},   {194,16},   {209,16},   {224,16},   {239,16},
        {228,32}, {217,32},   {202,32},   {187,32},   {172,32},   {157,32},   {142,32},     {112,32},   {97,32},    {82,32},    {67,32},    {52,32},    {37,32},    {19,32},
        {19,48},  {37,48},    {52,48},    {67,48},    {82,48},    {97,48},    {112,48},     {142,48},   {157,48},   {172,48},   {187,48},   {202,48},   {217,48},   {228,48},
  {239,64}, {224,64},   {209,64},   {194,64},   {179,64},   {164,64},   {149,64},               {105,64},   {90,64},    {75,64},    {60,64},    {45,64},    {30,64},    {15,64},
                                    {52,80},    {71,80},    {90,80},    {108,80},   {127,80},   {146,80},   {164,80},   {183,80},   {202,80}
}, {
  // LED Index to Flag
  1, 4, 4, 4, 4, 4, 4,       4, 4, 4, 4, 4, 4, 1,
   1, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4, 4, 1,
   1, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4, 4, 1,
  1, 4, 4, 4, 4, 4, 4,       4, 4, 4, 4, 4, 4, 1,
          1,  1,  9, 1, 1, 1,  9,  1,  1
}
#else // "Fireless Wings" layout
{
  // Key Matrix to LED Index
  {      0,      2,      4,      6, NO_LED,      8,     10,     12 },
  { NO_LED,     26,     24,     22, NO_LED,     19,     17,     15 },
  { NO_LED,     29,     31,     33, NO_LED,     36,     38,     40 },
  {     55,     53,     51,     49, NO_LED,     47,     45,     43 },
  { NO_LED, NO_LED,     57,     59, NO_LED,     61,     63, NO_LED },
  {      1,      3,      5, NO_LED,      7,      9,     11,     13 },
  {     27,     25,     23,     21,     20,     18,     16,     14 },
  {     28,     30,     32,     34,     35,     37,     39,     41 },
  {     54,     52,     50, NO_LED,     48,     46,     44,     42 },
  { NO_LED,     56,     58, NO_LED,     60,     62, NO_LED, NO_LED }
}, {
  // LED Index to Physical Position. NOTE: R2 & R4 are inverted
  {15,16},  {30,16},    {45,16},    {60,16},    {75,16},    {90,16},    {105,16},               {149,16},   {164,16},   {179,16},   {194,16},   {209,16},   {224,16},   {239,16},
        {228,32}, {217,32},   {202,32},   {187,32},   {172,32},   {157,32},   {142,32},     {112,32},   {97,32},    {82,32},    {67,32},    {52,32},    {37,32},    {19,32},
        {19,48},  {37,48},    {52,48},    {67,48},    {82,48},    {97,48},    {112,48},     {142,48},   {157,48},   {172,48},   {187,48},   {202,48},   {217,48},   {228,48},
  {239,64}, {224,64},   {209,64},   {194,64},   {179,64},   {164,64},   {149,64},               {105,64},   {90,64},    {75,64},    {60,64},    {45,64},    {30,64},    {15,64},
                                    {52,80},    {71,80},    {90,80},    {108,80},               {146,80},   {164,80},   {183,80},   {202,80}
}, {
  // LED Index to Flag
  1, 4, 4, 4, 4, 4, 4,       4, 4, 4, 4, 4, 4, 1,
   1, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4, 4, 1,
   1, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4, 4, 4, 1,
  1, 4, 4, 4, 4, 4, 4,       4, 4, 4, 4, 4, 4, 1,
         1,  1,  9,  1,     1,  9,  1,  1
}
#endif
#endif
};
#endif


#ifdef ENCODER_ENABLE // "FW + Rotary Encoder" layout
//------------------------------------------------------------------------------
// Rotary Encoder with VIA
//------------------------------------------------------------------------------
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[ENCODERS]   = ENCODERS_CCW_KEY;

void encoder_action_unregister(void) {
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = timer_read(),
                .type = KEY_EVENT
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = timer_read(),
        .type = KEY_EVENT
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_kb(void) {
    encoder_action_unregister();
    matrix_scan_user();
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return true;
};
#endif
