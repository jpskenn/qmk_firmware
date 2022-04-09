# Keymap for "Nora, Fearless Wings" with VIA support

For `Full layout`, VIA supported basic keymap with external EEPROM.

## Layers

| Layer name | Base layer | Indicator color | Description |
| :-- | :-: | :-- | :-- |
| Base #1 | Yes | n/a | JP layout with Windows modifier, symbols and cursor on center |
| Base #2 | Yes | Blue | JP layout with Windows modifier, numeric pad on center |
| Base #3 | Yes | Yellow | JP "[SemiErgo](https://github.com/mtei/SemiErgo_Layout)" layout with Windows modifier |
| Lower | No | Green | F-keys, Symbols & Audio control |
| Raise | No | Cyan | F-keys, Numbers & Cursor |
| Func | No | White | (Blank) |
| Reserve #1 | No | N/A | (Blank) |
| Reserve #2 | No | N/A | (Blank) |
| Reserve #3 | No | N/A | (Blank) |
| Adjust | No | Red | Switch default layer, Settings etc. |

NOTE: When CAPS on, left indicator changes to Magenta.

## Integrated Function

Use `KC_FNx` keycodes to call integrated function.

| Key | Description |
| :-- | :-- |
| `KC_FN0` | :information_source: Output firmware build version as string. |
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
