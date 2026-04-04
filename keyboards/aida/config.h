#pragma once

#define MASTER_LEFT

#define SERIAL_USART_TX_PIN GP14

/* RGB Lighting */
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF
#define RGBLIGHT_LAYERS_RETAIN_VAL

// 左手側のGPIOを3V3に接続して、擬似的にVBUSを再現。
// PCのコールドブート時に、マスター判定できずに反応がなくなってしまうのを回避
#define USB_VBUS_PIN GP22
