void suscribirseATopics() {
mqtt_subscribe(ESP_IN_TOPIC); //Topic por el que ROBODK envia informacion


}

void alRecibirMensajePorTopic(char* topic, String incomingMessage) {

  // TODO: Controlador que gestiona la recepción de datos

  // A partir de aquí debemos gestionar los mensajes
  //  recibidos por los diferentes topics (canales)
  //

  // Test JSON
  
  // If a message is received on the topic ...
  if (strcmp(topic, ESP_IN_TOPIC) == 0 ) {
    if(msg == "AVISO_MALAS_LLENA") {
      digitalWrite(ledFullMalas,HIGHT);
    }
    if (msg == "AVISO_NUEVAS_VACIA") {
      digitalWrite(ledEmptyMalas,Low);
    }
  }

}

void enviarMensajePorTopic(const char* topic, String outgoingMessage) {

  mqtt_publish(topic, outgoingMessage.c_str());

}





