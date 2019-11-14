#!/usr/bin/python

import os
import subprocess
from shutil import copyfile
from time import *
import time
import paho.mqtt.client as mqtt

broker_url = "Your mqtt server name"
broker_port = mqtt port number
user = "your mqtt user name"
password = "your mqtt password"

def on_connect(client, userdata, flags, rc):
   print("Connected With Result Code "+rc)

def on_message(client, userdata, message):
   print("Message Recieved: "+message.payload.decode())
   f = open('/your/file/location/temperature.txt', 'w')
   received = message.payload.decode()
   f.write(str(received))
   f.close()

client = mqtt.Client()
client.username_pw_set(user, password=password)
client.on_connect = on_connect
client.on_message = on_message
client.connect(broker_url, broker_port)
client.subscribe("Topic to subscribe", qos=1)
client.loop_forever()
