import paho.mqtt.client as mqtt
from SQLQuery import InsertData
from datetime import datetime

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("ET")

def on_message(client, userdata, msg):
    data = msg.payload.decode().split(" ")
    locationID, temp, hud, lux = data
    time = str(datetime.now())[:19]
    print(f"At location {locationID}: temp={temp}, hud={hud}, lux={lux}")
    InsertData(locationID, temp, hud, lux, time)

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

broker = "test.mosquitto.org"
port = 1883

client.connect(broker, port, 60)
client.loop_forever()
