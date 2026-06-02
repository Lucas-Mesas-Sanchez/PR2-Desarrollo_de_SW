from robodk import robolink    # RoboDK API
from robodk import robomath    # Robot toolbox
RDK = robolink.Robolink()
frame_cajabuena = RDK.Item('frame_cajabuena', robolink.ITEM_TYPE_FRAME)

def handle_message(mqttc, topic, payload):
    if topic == "mqtt/pr2/datacenter/g2/ESP32":
        if (payload == "VACIADO_TARJETAS_DEFECTUOSAS"):
            vaciado_tarjetas()
        if (payload == "RELLENADO_TARJETAS"):
            rellenado_tarjetas()
        if (payload == "PARADA_EMERGENCIA"):
            RDK.setParam('Start_Stop_Flag', 1)
            jorge = RDK.Item('jorge', robolink.ITEM_TYPE_ROBOT)
            juan = RDK.Item('juan', robolink.ITEM_TYPE_ROBOT)
            jorge.Stop()
            juan.Stop()
        if (payload == "EMERGENCIA_TEMPERATURA_ELEVADA"):
            RDK.setParam('Start_Stop_Flag',1)
        if (payload == "TEMPERATURA_CORRECTA"):
            RDK.setParam('Start_Stop_Flag',0)
        

def rellenado_tarjetas():
    RDK.setParam('Bandeja_Vacia_Flag', 1)  # fuerza el flag
    bandeja_vacia = RDK.getParam('Bandeja_Vacia_Flag')
    if (bandeja_vacia == 1):
        tarjeta_buena = RDK.Item('tarj_buena',robolink.ITEM_TYPE_OBJECT)
        for i in range(4):
            RDK.Copy(tarjeta_buena)
            tarjeta_buena_copia = RDK.Paste(frame_cajabuena)
            tarjeta_buena_copia.setName('tarj_buena' + str(i + 1))
            tarjeta_buena_copia.setPose(robomath.xyzrpw_2_pose([37.5, (35 + (i * 100)), 230, -90, 0, 0]))
            tarjeta_buena_copia.setVisible(True)
        RDK.setParam('Bandeja_Vacia_Flag', 0)

def vaciado_tarjetas():
    
    bandeja_llena = RDK.getParam('Bandeja_Llena_Flag')
    items = RDK.ItemList()
    for item in items:
        nombre = item.Name()
        if(nombre == "tarjeta_eliminar"):
            item.Delete()
    RDK.setParam('Bandeja_Llena_Flag', 0)

       

