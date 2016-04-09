#include <RCSwitch.h>

#define RXD 0
#define LED_PIN 13

//-----------------Type ID for 315MHz-----------------
//32bits mask
#define _32_ADDR_MASK       0b11111111000000000000000000000000L
#define _32_TYPE_MASK       0b00000000111111110000000000000000L
#define _32_VALUE_MASK      0b00000000000000001111111111111111L
#define _32_VALUE_H_MASK    0b00000000000000001111111100000000L
#define _32_VALUE_L_MASK    0b00000000000000000000000011111111L

//24bits mask (Tristate: Low: 00 High: 11 Float: 01 BitError: 10)
#define _24_TYPE_MASK       _32_TYPE_MASK
#define _24_ADDR_MASK       _32_VALUE_H_MASK
#define _24_VALUE_MASK      _32_VALUE_L_MASK

//Digital Sensors
//32bits
#define TYPE_Temperature    0b01011111L
#define TYPE_Humidity       0b01011110L
#define TYPE_Distance       0b01100000L
#define TYPE_Illumination   0b01100001L

//Boolean Sensors
//24bits
#define TYPE_Magnet         0b01010101L //F F F F
#define TYPE_Button         0b01010100L //F F F L
#define TYPE_Infrared       0b01010111L //F F F H
#define TYPE_Control        0b01010001L //F F L F