// -----------------Type IDs-----------------
// 32bits masks
#define _32_ADDR_MASK       0b11111111000000000000000000000000L
#define _32_TYPE_MASK       0b00000000111111110000000000000000L
#define _32_VALUE_MASK      0b00000000000000001111111111111111L
#define _32_VALUE_H_MASK    0b00000000000000001111111100000000L
#define _32_VALUE_L_MASK    0b00000000000000000000000011111111L

// 24bits masks (Tristate: Low: 00, High: 11, Float: 01, BitError: 10)
#define _24_TYPE_MASK       _32_TYPE_MASK
#define _24_ADDR_MASK       _32_VALUE_H_MASK
#define _24_VALUE_MASK      _32_VALUE_L_MASK

// 32bits digital sensors
#define TYPE_Humidity       0b01011110L // 94
#define TYPE_Temperature    0b01011111L // 95
#define TYPE_Distance       0b01100000L // 96
#define TYPE_Illumination   0b01100001L // 97
#define TYPE_SHumidity      0b01100010L // 98
#define TYPE_Watered        0b01100011L // 99

// 24bits boolean sensors (compatible with PT2262)
#define TYPE_Control        0b01010001L // F F L F

