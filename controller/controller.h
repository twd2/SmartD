#include <math.h> 

#define DEBUG    1

#define ADDRESS        1L
#define SnoozingTimeMS   30L * 1000L
//#define DUST_VAL A0
//#define DUST_LED 5
#define SHUMIDITY_VAL A0
#define DISTANCE_TRIG 8
#define DISTANCE_ECHO 7
//#define DHT11_BUS A1
//#define DHT22_BUS A1
//#define DS18B20_BUS 2
#define WIRELESS_TXD 12
#define BH1750_ADDR  0x23
//#define LCD_CS A3
//#define LCD_RST A2
//#define LCD_AO A0
#define RELAY_TRIG 6

#define ADDR_MASK  0b11111111000000000000000000000000L
#define TYPE_MASK  0b00000000111111110000000000000000L
#define VALUE_MASK 0b00000000000000001111111111111111L

#define TYPE_Temperature  0b01011111L
#define TYPE_Humidity     0b01011110L
#define TYPE_Distance     0b01100000L
#define TYPE_Illumination 0b01100001L
#define TYPE_SHumidity    0b01100010L
#define TYPE_Watered      0b01100011L

double lasttemp = 25.0;

#include "utils.h"
#include "use_wireless.h"
#include "use_dht11.h"
#include "use_dht22.h"
#include "use_distance.h"
#include "use_ds18b20.h"
#include "use_bh1750.h"
#include "use_shumidity.h"
#include "watering.h"

#if defined(USE_DHT11) && defined(USE_DHT22)
  #error cannot both dht11 dht22
#endif
