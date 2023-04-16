/* Copyright 2023 Takeshi Nishio
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

/* Dynamic Keymap */
#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 7 // default:4
#endif

/* チャタリング防止設定 */
// 参考： https://25keys.com/2022/02/10/debounce/
// rules.mk にも防止設定を追加している
// #ifdef DEBOUNCE
// #undef DEBOUNCE
// #define DEBOUNCE 80
// #endif

/* Dynamic Macro */
#define DYNAMIC_MACRO_DELAY 20 // Sets the waiting time (ms unit) when sending each key.

/* Mouse Keys */
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_MAX_SPEED 5
#define MOUSEKEY_TIME_TO_MAX 60
