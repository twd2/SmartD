# Receiver

Receives and forwards data to serial ports.

## Connection

### Use 315/433MHz RF

```
+------------+      +----------+
|         +5V|------|VCC       |
|         GND|------|GND       |
|          D2|<-----|DATA      |
|            |      |       ANT|---T
|            |      +----------+
|            |          RXB8
|            |      +---+
|         USB|<---->|USB|
+------------+      +---+
 Arduino Nano       PC/Raspberry Pi
```

### Use nRF24L01

- Just connect nRF24L01 with Raspberry Pi (or other computer) using SPI.
- Use Arduino to receive and forward data to a serial port. For the circuit, please see the part of  nRF24L01 of the PCB document in `controllers/plant/pcb`.


## Configuration

In `receiver.h`, configure pins.

## Dependencies

- [RCSwitch(twd2 modified)](https://github.com/twd2/RCSwitch) (required if and only if uses 315/433MHz RF)