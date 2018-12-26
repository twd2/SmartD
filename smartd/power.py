# -*- coding: UTF-8 -*-
import sys
import time
import serial
import smbus
import urllib
import urllib.parse
import urllib.request
import argparse
from smartd import secret

SERVER = 'http://127.0.0.1:8888'
KEY = secret.KEY

DEVICE_BUS = 1
ADDR_POWER = 0x40
ADDR_SOLAR = 0x41
REG_CONFIG = 0x00
REG_SHUNT = 0x01
REG_VOLTAGE = 0x02

R_SHUNT = 0.1 # ohm

def swapbytes(n):
  return ((n & 0xff) << 8) | ((n >> 8) & 0xff)

def signed16(n):
  if n & 0x8000:
    n = n - 65536
  return n

def sample(addr):
  bus = smbus.SMBus(DEVICE_BUS)
  I = signed16(swapbytes(bus.read_word_data(addr, REG_SHUNT))) * 10 / 1e6 / R_SHUNT * 1000
  V = (swapbytes(bus.read_word_data(addr, REG_VOLTAGE)) >> 3) * 4 / 1e3
  return round(V, 3), round(I, 1), round(V * I / 1000.0, 4)

def api(url, **kwargs):
  if kwargs:
    data = urllib.parse.urlencode(kwargs)
    request = urllib.request.Request(url, data.encode())
  else:
    request = urllib.request.Request(url)

  request.add_header('User-Agent', 'client.py/0.1')

  response = urllib.request.urlopen(request)
  return response.read()

def put_data(category, type, value):
  return api(SERVER + '/data/' + category + '/' + type, value=value, key=KEY)

def main():
  while True:
    try:
      V, I, P = sample(ADDR_POWER)
      print('power', V, I, P)
      put_data('power', 'voltage', V)
      put_data('power', 'current', I)
      put_data('power', 'power', P)
      V, I, P = sample(ADDR_SOLAR)
      print('solar', V, I, P)
      put_data('solar', 'voltage', V)
      put_data('solar', 'current', I)
      put_data('solar', 'power', P)
      time.sleep(5)
    except Exception as ex:
      print('error')
      print(ex)

if __name__ == '__main__':
  main()

