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

// Change LED count to actually installed.
#undef RGBLED_NUM
#define RGBLED_NUM 2

#define RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_MAX_LAYERS 10 // Blinkで2レイヤー追加すると、デフォルトの8レイヤーを超えてしまうため、ここで定義
