#include "bh1750.h"

#include <Arduino.h>
#include <Wire.h>

void BH1750_Init(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x10); // 1lux reolution 120ms, continuously
  Wire.endTransmission();
}

int BH1750_Read(int address, byte *buffer)
{
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);

  int i = 0;
  while (Wire.available())
  {
    buffer[i] = Wire.read();
    ++i;
  }
  Wire.endTransmission();
  return i;
}

void bh1750Init()
{
  Wire.begin();
}

bool bh1750(unsigned int &value)
{
  byte buffer[2];
  value = 0;
  BH1750_Init(BH1750_ADDR);
  delay(200);
  if (BH1750_Read(BH1750_ADDR, buffer) == 2)
  {
    value = (((unsigned int)(buffer[0]) << 8) | buffer[1]) / 1.2;
    return true;
  }
  return false;
}
