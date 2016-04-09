#ifndef UTILS_H
#define UTILS_H

void toBinary(unsigned long v, char *r, int bitLen)
{
  r[bitLen]='\0';
  for (int i = 0; i < bitLen; ++i)
  {
    r[i] = ((v & (1L << (bitLen - i - 1))) > 0) ? '1' : '0';
  }
}

#endif
