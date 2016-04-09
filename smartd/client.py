# -*- coding: UTF-8 -*-
import sys
import time
import serial
import urllib
import urllib.parse
import urllib.request
import argparse

SERIAL = '/dev/ttyUSB0'
SERVER = 'http://127.0.0.1:8888'
KEY = 'c959240243fc2aa96514678f288447b6'

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

type_string = {0b01011110: 'humidity', 0b01011111: 'temperature', 0b01100000: 'tank', 0b01100001: 'light'}
category_string = {1: 'plant', 2: 'plant', 21: 'plant'}

def main():
  while True:
    try:
      tty = serial.Serial(SERIAL, 115200)
      while True:
        line = tty.readline().decode().strip()
        print(line)
        try:
          addr, type, value = line.split(',') # 0: address, 1: type, 2: value
          addr = int(addr)
          type = int(type)
          if type in type_string and addr in category_string:
            put_data(category_string[addr], type_string[type], value)
            print((category_string[addr], type_string[type], value))
          else:
            print('unknown addr or type')
        except Exception as ex:
          print(ex)
      
    except Exception as ex:
      print(ex)

if __name__ == '__main__':
  main()
