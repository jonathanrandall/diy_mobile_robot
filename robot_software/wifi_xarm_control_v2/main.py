import sys
import json
import _thread
from machine import Pin, I2C, Timer
import time, gc
from micropython import const

###########

from Oled import OLED_I2C
import utime
oled_flag = True
i2c = I2C(0, scl=Pin(27), sda=Pin(14), freq=100000)
try:
  oled = OLED_I2C(128, 64, i2c)
except OSError:
  print('没有检测到OLED模块')
  oled_flag = False

###################


try:
  import usocket as socket
except:
  import socket
  
from time import sleep

from machine import Pin, I2C
import network

from wifi_stuff import ssid, password
from wifi_stuff import html

import gc
gc.collect()

# ssid = "ssid"
# password = "password"
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)
while not wlan.isconnected():
    pass

ip_configuration = wlan.ifconfig()[0]
# ip_configuration = ip_configuration.decode('utf-8')
print("ip address ", ip_configuration)

if oled_flag:
    oled.fill(0)
    oled.text("RED", 10, 11)
    oled.text(ip_configuration, 10,32)
    oled.show()
# 

########################################

from BusServo import BusServo

bus_servo = BusServo(tx=26, rx=35, tx_en=25, rx_en=12)

def refresh_sevos():
   for i in range(6):
      bus_servo.run(i+1,500)

def create_command_map(obj):
    command_map = {}
    for attribute_name in dir(obj):
        if callable(getattr(obj, attribute_name)) and not attribute_name.startswith("__"):
            command_map[attribute_name] = getattr(obj, attribute_name)
    return command_map

name2bus_method = create_command_map(bus_servo)

def run_webservice():
  # Setup the web server
  addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
  s = socket.socket()
  s.bind(addr)
  s.listen(1)

  print('listening on', addr)
  print('ip_configuration ', 'http://%s' %ip_configuration)
  
  while True:
    try:
      cl, addr = s.accept()
      print('client connected from', addr)
      request = cl.recv(1024)
      request = str(request)
      print('request:', request)     
      
      if 'GET / ' in request:
          response = html
          refresh_sevos()
      elif 'GET /slider?value=' in request:
          info = (request.split('value=')[1].split(' ')[0])
          servo_id = info.split('_')[0]
          servo_id = int(servo_id)
          angle = info.split('_')[1]
          angle = int(angle)

          bus_servo.run(servo_id,angle)
          # servo.write_angle(angle)
          response = "Servo ID set to " + str(servo_id) + " angle is " + str(angle)
          print("repsonse", response)
      elif 'GET /command?' in request:
          # Example request: GET /command?method=run&params=1,90
          command_info = request.split('command?')[1].split(' ')[0]
          command_params = {param.split('=')[0]: param.split('=')[1] for param in command_info.split('&')}
          method_name = command_params.get('method')
          params = command_params.get('params')
          if method_name in name2bus_method:
              try:
                  if params is None:
                    args = dict()
                  else:
                    args = [int(x) if x.isdigit() else x for x in params.split(',')]
                  if method_name == 'set_positions':
                    args = [args[:-1], args[-1]]
                  result = name2bus_method[method_name](*args)
                  response = json.dumps(result)
              except Exception as e:
                  response = "Error executing command: %s" %e 
                  sys.print_exception(e)
                  print('got error for params %s' % params)
                  
          else:
              response = "Invalid Command"
      else:
          response = "Invalid Request"          
      
      respons = 'HTTP/1.1 200 OK\n'
      respons += 'Content-Type: text/html\n'
      respons += 'Connection: keep-alive\n\n'
      respons += response  # Assuming your_content_here is the actual response content

      cl.sendall(respons.encode())
      cl.close()
      # cl.send('HTTP/1.1 200 OK\n')
      # cl.send('Content-Type: text/html\n')
      # cl.sendall('Connection: keep-alive\n\n')
      # cl.sendall(response)
      # cl.close()
    except Exception as e:
      sys.print_exception(e) 

_thread.start_new_thread(run_webservice, ())  