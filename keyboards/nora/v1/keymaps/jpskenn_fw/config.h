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

#undef RGB_MATRIX_LED_COUNT
#define RGB_MATRIX_LED_COUNT 64

#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE

// LED index for DM_RECx indicator
// NOTE: LED on R4 is connected from right to left. So, the index is inverted.
#define LED_INDEX_R4_LEFT_INSIDE 49
#define LED_INDEX_R4_RIGHT_INSIDE 48
