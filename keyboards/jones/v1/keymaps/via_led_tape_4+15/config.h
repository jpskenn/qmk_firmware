#pragma once

//------------------------------------------------------------------------------
// External EEPROM
//------------------------------------------------------------------------------

// Use 24LC64 EEPROM
#define EEPROM_I2C_24LC64

// Set MAX_ADDR to specify actual EEPROM size.
// If it's not set, EEPROM size will be set ATmega32u4's 1023.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191

// How many layers to use with VIA / Remap.
#define DYNAMIC_KEYMAP_LAYER_COUNT 6 // default:4


//------------------------------------------------------------------------------
// RGB Lighting
//------------------------------------------------------------------------------

// Using Underglow LEDs(RGB Lighting)
#ifdef RGB_DI_PIN
  #undef RGBLED_NUM
  #define RGBLED_NUM 19 // Left(2) + Right(2) + LED Strip(15*) *:60LEDs/1m

  // LED Animations
  #define RGBLIGHT_EFFECT_BREATHING
  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
  #define RGBLIGHT_EFFECT_KNIGHT
  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
  #define RGBLIGHT_EFFECT_TWINKLE
#endif

//------------------------------------------------------------------------------
// Audio
//------------------------------------------------------------------------------

// Disable "Music Mode" to reduce firmware size.
#ifdef AUDIO_ENABLE
  #define NO_MUSIC_MODE
  #undef MUSIC_MAP
#endif
