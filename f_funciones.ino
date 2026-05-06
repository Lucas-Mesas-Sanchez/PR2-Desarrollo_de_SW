uint8_t ledStatus = 0;
bool ultimoEstadoBtnRellenar = HIGH;
bool ultimoEstadoBtnVaciar   = HIGH;
bool ultimoEstadoEmergencia  = HIGH;


void comprobarTemperatura() {
  int lectura = analogRead(pinSensor);
  static bool estado_anterior = false; //Variable para que envie mensajes solo cuando haya un cambio
  if (lectura > 2500 && estado_anterior == false) {
    digitalWrite(ledTemp, HIGH);
    enviarMensajePorTopic(ESP_OUT_TOPIC, "EMERGENCIA_TEMPERATURA_ELEVADA");
    estado_anterior = true;
  } else if(lectura <= 2500 && estado_anterior = true){
    enviarMensajePorTopic(ESP_OUT_TOPIC, "TEMPERATURA_CORRECTA");
    digitalWrite(ledTemp, LOW);
    estado_anterior = false;
  }
}

void comprobarLogistica() {
  bool estadoRellenar = digitalRead(btnRellenar);
  bool estadoVaciar   = digitalRead(btnVaciar);

  if (estadoRellenar == LOW && ultimoEstadoBtnRellenar == HIGH) {
    enviarMensajePorTopic(ESP_OUT_TOPIC, "RELLENADO_TARJETAS");
    digitalWrite(ledEmptyNuevas, LOW);
  }

  if (estadoVaciar == LOW && ultimoEstadoBtnVaciar == HIGH) {
    enviarMensajePorTopic(ESP_OUT_TOPIC, "VACIADO_TARJETAS_DEFECTUOSAS");
    digitalWrite(ledFullMalas, LOW);
  }

  ultimoEstadoBtnRellenar = estadoRellenar;
  ultimoEstadoBtnVaciar   = estadoVaciar;
}

void comprobarEmergencia() {
  bool estado = digitalRead(btnEmergencia);

  if (estado == LOW && ultimoEstadoEmergencia == HIGH) {
    enviarMensajePorTopic(ESP_OUT_TOPIC,"PARADA_EMERGENCIA");
  }

  ultimoEstadoEmergencia = estado;
}



