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

// Change LED count.
// #ifdef RGB_DI_PIN
//     #undef RGBLED_NUM
//     #define RGBLED_NUM 4 // Left(2) + Right(2)
// #endif

// #define RGBLIGHT_LAYER_BLINK
// #define RGBLIGHT_MAX_LAYERS 10 // Blinkで2レイヤー追加すると、デフォルトの8レイヤーを超えてしまうため、ここで定義

// This "may" reduce firmware size.
// #undef LOCKING_SUPPORT_ENABLE
// #undef LOCKING_RESYNC_ENABLE
// #define NO_ACTION_ONESHOT
// #define LAYER_STATE_8BIT // limit layers up to 8
