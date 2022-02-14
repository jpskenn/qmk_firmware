# Keymap for "Nora, Fearless Wings" with VIA support

VIA supported basic keymap with external EEPROM.

## Layers

| Layer name | Base layer | Indicator color | Description |
| :-- | :-: | :-- | :-- |
| Base #1 | Yes | n/a<br>(RGB Matrix effect color) | US layout with Mac modifier |
| Base #2 | Yes | Blue | US layout with Windows modifier |
| Base #3 | Yes | Yellow | "SemiErgo" layout with Mac modifier |
| Lower | No | Green | F-keys, Symbols & Audio |
| Raise | No | Cyan | F-keys, Numbers & Cursor |
| Func | No | White | (Blank) |
| Adjust | No | Red | Switch default layer, Settings etc. |

## Integrated Function

Use `KC_FNx` keycodes to call integrated function.

| Key | Description |
| :-- | :-- |
| `KC_FN0` | :information_source: Output build version of firmware as string. |
| `KC_FN1` | Change default layer to "Base #1".<br>:floppy_disk: Save layer to EEPROM. |
| `KC_FN2` | Change default layer to "Base #2".<br>:floppy_disk: Save layer to EEPROM. |
| `KC_FN3` | Change default layer to "Base #3".<br>:floppy_disk: Save layer to EEPROM. |
| `KC_FN4` | Toggle layer indicator.<br>Enjoy full RGB Matrix effects :smiley: |

## External EEPROM

I2C connected external EEPROM.

## LED lighting

RGB Matrix

## Rotary encoder

None

## Audio

Disabled
