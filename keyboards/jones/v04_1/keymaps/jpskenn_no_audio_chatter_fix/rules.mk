VIA_ENABLE = yes

EEPROM_DRIVER = i2c

# MOUSEKEY_ENABLE = no // Set "no" to reduce firmware size

DYNAMIC_MACRO_ENABLE = yes

AUDIO_ENABLE = no

# チャタリング防止設定
# https://25keys.com/2022/02/10/debounce/
# config.hにも防止設定を追加している
DEBOUNCE_TYPE = sym_eager_pk
