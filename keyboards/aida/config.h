#pragma once

#define MASTER_LEFT

#define SERIAL_USART_TX_PIN GP14

/* RGB Lighting */
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_LAYERS_RETAIN_VAL

// 左手側のGPIOを3V3に接続して、擬似的にVBUSを再現。
// PCのコールドブート時に、マスター判定できずに反応がなくなってしまうのを回避
#define USB_VBUS_PIN GP22

/* I2C */
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP20
#define I2C1_SCL_PIN GP21

// リセットボタンをタブルクリックして、ブートローダーに入る
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U // Timeout window in ms in which the double tap can occur.
