#if !defined(USE_BH1750) && defined(BH1750_ADDR)
#define USE_BH1750

#include <Wire.h>

byte bh1750_buff[2];


void BH1750_Init(int address) 
{
  Wire.beginTransmission(address);
  Wire.write(0x10);//1lx reolution 120ms
  Wire.endTransmission();
}

int BH1750_Read(int address) 
{
  int i = 0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while (Wire.available()) 
  {
    bh1750_buff[i] = Wire.read();  // receive one byte
    i++;
  }
  Wire.endTransmission();  
  return i;
}

void initBH1750()
{
  Wire.begin();
}

int doBH1750()
{
  unsigned int value = 0;
  BH1750_Init(BH1750_ADDR);
  delay(200);
  if (BH1750_Read(BH1750_ADDR))
  {
    value = ((bh1750_buff[0] << 8) | bh1750_buff[1]) / 1.2;
  }
  return value;
}

#endif
