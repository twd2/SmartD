# Plant

Automatic sprinkler.

## Connection

See PCB and `*.h`.

## Configuration

In `plant.h`, comment `#include`s that you don't need.

See `*.h` and configure pins and/or addresses for each sensor or executer.

## Dependencies

- [RCSwitch (twd2 modified)](https://github.com/twd2/RCSwitch) (strongly recommanded)
- [DHTlib](http://playground.arduino.cc/Main/DHTLib) (required if and only if DHT11 or DHT22 is installed.)
- [OneWire](http://playground.arduino.cc/Learning/OneWire) (required if and only if DS18B20 is installed.)
- [DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library) (required if and only if DS18B20 is installed.)
- Wire (required if and only if I2C devices like BH1750 are installed.)

## Materials

**Choosing soil moisture sensor:** I found there are two kinds of soil moisture sensors. One called A is cheap (about 4 RMB) and it measures soil moisture by measuring the resistance between two electrode. It can be easily corroded and its lifetime is quite short (less than 3 months). The other one called B is more expensive (about 300 RMB) and the seller said it measures the capacitance. The seller also said its lifetime is about 3 years, but I haven't tested because I don't have enough time. It also integrates temperature sensor. You may choose any one according to your own situation.

Don't forget to uncomment `#define SOIL_SENSOR_TYPE_A 1` and comment `#define SOIL_SENSOR_TYPE_B 1` in `soil.h` when you choose to use A.

**Choosing wireless module:** nRF24L01 support is not implemented yet, so please use 315/433MHz RF instead :-).

- PCB (about 10 RMB each)
- Arduino Nano (FT232R and CH340G are both compatible) (about 15 RMB each for CH340G or about 24 RMB each for FT232R)
- Distance sensor HC-SR04 (about 5 RMB each)
- Soil moisture sensor, described above.
- Illumination sensor BH1750FVI (about 9.5 RMB each)
- Relay module (about 3.5 RMB each)
- 315/433MHz RF transmitter (about 2.3 RMB each, and *don't forget receiver*)
- 2.4GHz RF module nRF24L01 (about 4 RMB each)
- Capacitors 104P (0.1 uF) * (3 if nRF24L01 is installed, otherwise 2) (< 0.1 RMB totally)
- Resistors 100K * 2 (if uses B), 4.7K * 2 (< 0.1 RMB totally)
- Lots of DuPont pins (about 1 RMB totally)
- Some DuPont cables (about 2 RMB totally)
- Pump and tubes (about 90 RMB totally)

**Typical cost:** 141.3 RMB (A, Arduino Nano with CH340G, 315MHz RF), 437.3 RMB (B, Arduino Nano with CH340G, 315MHz RF)
