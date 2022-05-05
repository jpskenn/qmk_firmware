#pragma once

// Change LED count.
// #ifdef RGB_DI_PIN
//     #undef RGBLED_NUM
//     #define RGBLED_NUM 4 // Left(2) + Right(2)
// #endif

// Disable music mode to reduce firmware size.
// +2.3kb
// #ifdef AUDIO_ENABLE
//   #undef MUSIC_MAP
//   #define NO_MUSIC_MODE
//   #define SONG_CAPS_ON SONG(CAPS_LOCK_ON_SOUND)
//   #define SONG_CAPS_OFF SONG(CAPS_LOCK_OFF_SOUND)
// #endif

// Disable unused encoder pad to reduce firmware size.
// Override keyboard's config.h : Left encoder only
// +0.3kb
// #undef ENCODERS_PAD_A
// #undef ENCODERS_PAD_B
// #define ENCODERS_PAD_A { F5 }
// #define ENCODERS_PAD_B { F4 }

#define RGBLIGHT_LAYER_BLINK
#define RGBLIGHT_MAX_LAYERS 10 // Blinkで2レイヤー追加すると、デフォルトの8レイヤーを超えてしまうため、ここで定義

#define RGBLIGHT_LAYERS_RETAIN_VAL // set Lighting Layer brightness equals to Underglow's value

// Use 24LC64 EEPROM
#define EEPROM_I2C_24LC64

// Set MAX_ADDR to specify actual EEPROM size.
// If it's not set, EEPROM size will be set ATmega32u4's 1023.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 7 // default:4
#endif

//------------------------------------------------------------------------------
// Rotary Encoder
//------------------------------------------------------------------------------
// Encoder triggers specific key matrix position,
// when turn knob clockwise or counterclockwise.
// This is handy to assign key codes by VIA.

// Number of endoder
#define ENCODERS 2

// Mappings of encoder rotation to key position in key matrix.
// First encoder,  Left side  : k85, k86
// Second encoder, Right side : k95, k96
#define ENCODERS_CW_KEY  { { 6, 8 }, { 6, 9 } }
#define ENCODERS_CCW_KEY { { 5, 8 }, { 5, 9 } }
