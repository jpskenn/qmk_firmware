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

// time for long press
#define TAPPING_TERM 200

// Comment off to enable settings, ios device friendly.
//#define IOS_DEVICE_ENABLE

#ifdef IOS_DEVICE_ENABLE
    #define  USB_MAX_POWER_CONSUMPTION 100
    #undef RGBLIGHT_LIMIT_VAL
    #define RGBLIGHT_LIMIT_VAL 200
#endif

#ifdef AUDIO_ENABLE
    #define MUSIC_MAP
#endif

#ifdef RGB_DI_PIN
    /* Example settings for Underglow */
    #undef RGBLED_NUM
    #define RGBLED_NUM 7 // Layer Indicator(2) + Rotary Encoder(5) + Under(8)

    #undef RGBLIGHT_LED_MAP
    #define RGBLIGHT_LED_MAP {0, 2, 1, 3, 4, 5, 6} // Left to Right, 2nd LED is used as indicator.
#endif

#define RGBLIGHT_MAX_LAYERS 10

#ifdef MIDI_ENABLE
    /* MIDI Basic for sequencer */
    #define MIDI_BASIC

    #define MIDI_ADVANCED
#endif


#ifdef NKRO_ENABLE
    #define FORCE_NKRO
#endif

#ifdef SEQUENCER_ENABLE
    #define SEQUENCER_STEPS 32  // default: 16
    #define SEQUENCER_TRACKS 8
#endif
