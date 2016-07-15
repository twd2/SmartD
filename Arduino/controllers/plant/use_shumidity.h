#if !defined(USE_SHUMIDITY) && defined(SHUMIDITY_VAL)
#define USE_SHUMIDITY

void initSHumidity()
{
  pinMode(SHUMIDITY_VAL, INPUT);
}

int doSHumidity()
{
  return analogRead(SHUMIDITY_VAL);
}

#endif
