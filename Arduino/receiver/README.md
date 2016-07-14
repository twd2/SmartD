# Receiver

Receives and forwards data to serial ports.

## Connection

### Use 315/433MHz

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

- Just connect nRF24L01 with Raspberry Pi (or other single-board PC) using SPI.
- Use Arduino to receive and forward data to a serial port. For the circuit, please see the PCB of `controllers/plant`.

