#ifndef _BH1750_H_
#define _BH1750_H_

#define BH1750_ADDR 0x23

void BH1750_Init(int address);
int BH1750_Read(int address, unsigned char *buffer);
void bh1750Init();
bool bh1750(unsigned int &value);

#endif // _BH1750_H_
