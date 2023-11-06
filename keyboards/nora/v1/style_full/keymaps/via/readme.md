# Keymap for "Nora, Fearless Wings" with VIA support

For `Full layout`, VIA supported basic keymap with external EEPROM.

## Layers

| Layer name | Base layer | Indicator color | Description |
| :-- | :-: | :-- | :-- |
| Base #1 | :white_check_mark: | n/a | JP layout |
| Base #2 | :white_check_mark: | Blue | US layout |
| Base #3 | :white_check_mark: | Yellow | Numeric pad on center. Transparent over Base #1 or Base #2. |
| Lower #1 | | Green | F-keys, Symbols & Audio controls for JP layout |
| Lower #2 | | Chartreuse Green | F-keys, Symbols & Audio controls for US layout |
| Lower #3 | | n/a | (Blank) |
| Raise #1 | | Azure | F-keys, Numbers & Cursor for JP layout |
| Raise #2 | | Cyan | F-keys, Numbers & Cursor for US layout |
| Raise #3 | | n/a | (Blank) |
| Adjust | | Red | Switch default layer, Settings etc. |

NOTE: When CAPS lock is on, left indicator changes to Magenta.

## Integrated Function

- Save default layer to EEPROM.

    Press `DF(0)`, `DF(1)`, `DF(2)` with `Shift` to save default layer to EEPROM.

    ex.
    `Shift + DF(0)` will change default layer to `layer 0` and save its status to EEPROM.

## External EEPROM

I2C connected external EEPROM.

## LED lighting

RGB Matrix

## Rotary encoder

None
