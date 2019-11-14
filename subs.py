#!/usr/bin/python

import os

import subprocess
from shutil import copyfile
from time import *
import time
import paho.mqtt.client as mqtt

broker_url = "farmer.cloudmqtt.com"
broker_port = 14507
user = "gtjboggm"
password = "hXhG1stsPBWE"

def on_connect(client, userdata, flags, rc):
   print("Connected With Result Code "+rc)

def on_message(client, userdata, message):
   print("Message Recieved: "+message.payload.decode())
   f = open('/home/pi/test/temperature.txt', 'w')
   received = message.payload.decode()
   f.write(str(received))
   f.close()

client = mqtt.Client()
client.username_pw_set(user, password=password)
client.on_connect = on_connect
client.on_message = on_message
client.connect(broker_url, broker_port)

client.subscribe("Suadiye Temperature", qos=1)

# client.publish(topic="Suadiye Temperature", payload="TestingPayload", qos=1, retain=False)

client.loop_forever()

