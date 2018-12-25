# -*- coding: UTF-8 -*-
import sys
import time
import serial
import urllib
import urllib.parse
import urllib.request
import argparse
from smartd import secret

SERIAL = '/dev/ttyUSB0'
SERVER = 'http://127.0.0.1:8888'
KEY = secret.KEY

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

type_string = {0b01011110: 'humidity', 0b01011111: 'temperature', 0b01100000: 'distance',
               0b01100001: 'illumination', 0b01100010: 'moisture', 0b01100011: 'watered'}
category_string = {1: 'plant', 2: 'plant', 21: 'env'}

def main():
  while True:
    try:
      tty = serial.Serial(SERIAL, 115200)
      while True:
        line = tty.readline().decode().strip()
        print(line)
        try:
          addr, type, value = line.split(',')
          addr = int(addr)
          type = int(type)
          if type in type_string and addr in category_string:
            print(put_data(category_string[addr], type_string[type], value))
            print((category_string[addr], type_string[type], value))
          else:
            print('unknown addr or type')
        except Exception as ex:
          print('error')
          print(ex)
      
    except Exception as ex:
      print('error')
      print(ex)

if __name__ == '__main__':
  main()

