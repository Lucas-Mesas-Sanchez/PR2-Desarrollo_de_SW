from robodk import robolink    # RoboDK API
from robodk import robomath    # Robot toolbox
RDK = robolink.Robolink()

import paho.mqtt.client as mqtt
import RobotController as rc
    
bandeja_llena = RDK.getParam('Bandeja_Llena_Flag')
bandeja_vacia = RDK.getParam('Bandeja_Vacia_Flag')
broker="mqtt.dsic.upv.es"
port=1883
user="giirob"
passwd="UPV2024"
in_topic="mqtt/pr2/datacenter/g2/ESP32"
out_topic ="mqtt/pr2/datacenter/g2/ROBODK"
station_name="G2"



def on_message(mqttc, obj, msg):
    payload = msg.payload.decode('utf-8')
    topic = msg.topic
    qos = msg.qos
    rc.handle_message(mqttc, topic, payload)
def publish_msg():
    if ( bandeja_llena == 1):
        mqtt.pubish(out_topic,"AVISO_MALAS_LLENA")
    if (bandeja_vacia == 1):
        mqtt.pubish(out_topic,"AVISO_NUEVAS_VACIA")


mqttc = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
mqttc.on_message = on_message

mqttc.username_pw_set(username=user, password=passwd)
mqttc.connect(broker, port, 60)
mqttc.subscribe(in_topic, 0)


mqttc.loop_forever()