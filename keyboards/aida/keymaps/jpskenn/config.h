/*
Copyright 2024 Takeshi Nishio

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

// /* Dynamic Keymap */
// #define DYNAMIC_KEYMAP_LAYER_COUNT 8 // default:4

/* Audio */
#define AUDIO_PIN GP19
#define AUDIO_PWM_DRIVER PWMD1
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define AUDIO_INIT_DELAY
#define AUDIO_CLICKY
#define MUSIC_MAP
#define AUDIO_VOICES
#define AUDIO_ENABLE_TONE_MULTIPLEXING
#define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10

// /* Tap-Hold */
// #define HOLD_ON_OTHER_KEY_PRESS
// #define CHORDAL_HOLD
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

/* I2C */
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP20
#define I2C1_SCL_PIN GP21

/* Haptic Feedback */
// LRA settings
#define DRV2605L_FB_ERM_LRA 1
#define DRV2605L_FB_BRAKEFACTOR 3 /* For 1x:0, 2x:1, 3x:2, 4x:3, 6x:4, 8x:5, 16x:6, Disable Braking:7 */
#define DRV2605L_FB_LOOPGAIN 1 /* For  Low:0, Medium:1, High:2, Very High:3 */

/* Please refer to your datasheet for the optimal setting for your specific motor. */
#define DRV2605L_RATED_VOLTAGE 1.8
#define DRV2605L_V_PEAK 1.85
#define DRV2605L_V_RMS 1.8
#define DRV2605L_F_LRA 210 /* resonance freq */

#define DRV2605L_GREETING 10
