#include <RCSwitch.h>

#include "receiver.h"

RCSwitch mySwitch = RCSwitch();

bool check24bit(unsigned long data)
{
  while (data > 0)
  {
    if ((data & 0b11) == 0b10)
    {
      return false;
    }
    data >>= 2;
  }
  return true;
}

bool check32bit(unsigned long data)
{
  // not implemented
  return true;
}

bool checkSensor(unsigned long addr)
{
  static unsigned long _lastAddr = -1;
  static unsigned long _lastRecvTime = -1;
  if (_lastAddr == addr && millis() < _lastRecvTime)
  {
    return false;
  }
  _lastAddr = addr;
  _lastRecvTime = millis() + 500;
  return true;
}

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
  mySwitch.enableReceive(digitalPinToInterrupt(RXD_PIN));
}

template <typename T>
void sendData(unsigned long addr, unsigned long type, const T value);

template <typename T>
void sendData(unsigned long addr, unsigned long type, const T value)
{
  Serial.print(addr);
  Serial.print(",");
  Serial.print(type);
  Serial.print(",");
  Serial.print(value);
  Serial.println();
}

void loop()
{
  mySwitch.enableReceive(digitalPinToInterrupt(RXD_PIN));
  if (mySwitch.available())
  {
    unsigned long raw = mySwitch.getReceivedValue();
    unsigned long addr, type, id, value;
    
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    
    if (raw == 0)
    {
      // unknown encoding
    }
    else if (mySwitch.getReceivedBitlength() == 32 && check32bit(raw))
    {
      addr = (raw & _32_ADDR_MASK) >> 24;
      type = (raw & _32_TYPE_MASK) >> 16;
      id = (raw & (_32_ADDR_MASK | _32_TYPE_MASK)) >> 16;
      value = raw & _32_VALUE_MASK;
      switch (type)
      {
      case TYPE_Humidity:
      case TYPE_Distance:
      case TYPE_Temperature:
      case TYPE_Moisture:
      {
        if (!checkSensor(id))
        {
          break;
        }
        // Fixed point numbers.
        sendData(addr, type, ((double)((int)value)) / 100.0);
        break;
      }
      case TYPE_Watered:
      case TYPE_Illumination:
      {
        if (!checkSensor(id))
        {
          break;
        }
        // Integer numbers.
        sendData(addr, type, value);
        break;
      }
      default:
        // drop
        break;
      }
    }
    else if (mySwitch.getReceivedBitlength() == 24 && check24bit(raw))
    {
      addr = (raw & _24_ADDR_MASK) >> 8;
      type = (raw & _24_TYPE_MASK) >> 16;
      id = (raw & (_24_TYPE_MASK | _24_ADDR_MASK)) >> 8;
      value = raw & _24_VALUE_MASK;
      switch (type)
      {
      case TYPE_Control:
      {
        if (!checkSensor(id))
        {
          break;
        }
        char mystr[10] = {0};
        mystr[0] = '\0';
        if (value & 0b11000000)
        {
          strcat(mystr, "2;"); // B
        }
        if (value & 0b00110000)
        {
          strcat(mystr, "3;"); // C
        }
        if (value & 0b00001100)
        {
          strcat(mystr, "1;"); // A
        }
        if (value & 0b00000011)
        {
          strcat(mystr, "4;"); // D
        }
        if (strlen(mystr) > 0)
        {
          mystr[strlen(mystr) - 1] = '\0'; // remove last ';'
        }
        sendData(addr, type, mystr);
        break;
      }
      default:
      {
        if (!checkSensor(raw))
        {
          break;
        }
        sendData(raw, type, (unsigned long)1);
        break;
      }
      }
    }
    else
    {
      // Bit length mismatch or check failed.
    }
  }
  mySwitch.resetAvailable();
}

