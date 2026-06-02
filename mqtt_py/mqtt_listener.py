import paho.mqtt.client as mqtt
from robodk import robolink    # RoboDK API
from robodk import robomath    # Robot toolbox
import time
RDK = robolink.Robolink()

import robot_controller as rc
    

broker="broker.emqx.io"
port=1883
user=""
passwd=""
in_topic="mqtt/pr2/datacenter/g2/ESP32"
out_topic ="mqtt/pr2/datacenter/g2/ROBODK"
station_name="G2"



def on_message(mqttc, obj, msg):
    payload = msg.payload.decode('utf-8')
    topic = msg.topic
    qos = msg.qos
    rc.handle_message(mqttc, topic, payload)

def mqtt_loop():
    bandeja_llena_prev = None
    bandeja_vacia_prev = None

    while True:
        mqttc.loop(timeout=0.1)  # Procesa mensajes entrantes

        bandeja_llena = RDK.getParam('Bandeja_Llena_Flag')
        bandeja_vacia = RDK.getParam('Bandeja_Vacia_Flag')

        # Solo publica si el flag ha cambiado a 1
        if bandeja_llena == 1 and bandeja_llena_prev != 1:
            print(f"BANDEJA_LLENA: {bandeja_llena}")
            mqttc.publish(out_topic, "AVISO_MALAS_LLENA")

        if bandeja_vacia == 1 and bandeja_vacia_prev != 1:
            print(f"BANDEJA_VACIA: {bandeja_vacia}")
            mqttc.publish(out_topic, "AVISO_NUEVAS_VACIA")

        bandeja_llena_prev = bandeja_llena
        bandeja_vacia_prev = bandeja_vacia

        time.sleep(0.1)  # Polling cada 100ms



mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_message = on_message

mqttc.username_pw_set(username=user, password=passwd)
mqttc.connect(broker, port, 60)
mqttc.subscribe(in_topic, 0)


mqtt_loop()

