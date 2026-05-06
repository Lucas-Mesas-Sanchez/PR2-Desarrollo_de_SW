from robodk import robolink    # RoboDK API
from robodk import robomath    # Robot toolbox
RDK = robolink.Robolink()

bandeja_vacia = RDK.getParam('Bandeja_Vacia_Flag')
def handle_message(mqttc, topic, payload):

    if topic == "mqtt/pr2/datacenter/g2/ESP32":
        if (payload == "VACIADO_TARJETAS_DEFECTUOSAS"):
            vaciado_tarjetas()
        if (payload == "RELLENADO_TARJETAS"):
            rellenado_tarjetas()
        if (payload == "PARADA_EMERGENCIA"):
            start_stop = RDK.getParam('Start_Stop_Flag')
            if (start_stop == 1):
                RDK.setParam('Start_Stop_Flag',0)
            else:
                RDK.setParam('Start_Stop_Flag',1)
        if (payload == "EMERGENCIA_TEMPERATURA_ELEVADA"):
            RDK.setParam('Start_Stop_Flag',1)
        if (payload == "TEMPERATURA_CORRECTA"):
            RDK.setParam('Start_Stop_Flag',0)
        

def rellenado_tarjetas():
    if (bandeja_vacia == 1):
        tarjeta_buena = RDK.Item('tarj_buena',ITEM_TYPE_OBJECT)
        targ_pos = [ RDK.Item('pick1bueno',ITEM_TYPE_TARGET),
                    RDK.Item('pick2bueno',ITEM_TYPE_TARGET),
                    RDK.Item('pick3bueno',ITEM_TYPE_TARGET),
                    RDK.Item('pick4bueno',ITEM_TYPE_TARGET)]
        for i in range(4):
            tarjeta_buena_copia = tarjeta_buena.Copy()
            tarjeta_buena_copia.setName('tarj:buena_copia')
            tarjeta_buena_copia.setPose(targ_pos[i])
            tarjeta_buena_copia.setVisible(True)

def vaciado_tarjetas():
    items = RDK.ItemList()
    for item in items:
        nombre = item.name()
        if(nombre == "tarjeta_eliminar"):
            item.delete()
