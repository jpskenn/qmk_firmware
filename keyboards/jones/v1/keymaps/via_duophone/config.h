#pragma once

// Use 24LC64 EEPROM
#define EEPROM_I2C_24LC64

// Set MAX_ADDR to specify actual EEPROM size.
// If it's not set, EEPROM size will be set ATmega32u4's 1023.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 8191

#define DYNAMIC_KEYMAP_LAYER_COUNT 6 // default:4

#ifdef AUDIO_ENABLE
  #undef AUDIO_PIN
  #define AUDIO_PIN C6
  #define AUDIO_PIN_ALT B6
#endif
