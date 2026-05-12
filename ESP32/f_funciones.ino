struct Button
{
  const uint8_t PIN;
  bool pressed;
};

Button boton_rellenar = {btnRellenar,false};
Button boton_vaciar = {btnVaciar,false};
Button boton_emergencia = {btnEmergencia,false};
void IRAM_ATTR isr_rellenar()
{
  boton_rellenar.pressed = true;
}

void IRAM_ATTR isr_vaciar()
{
  boton_vaciar.pressed = true;
}

void IRAM_ATTR isr_emergencia()
{
  boton_emergencia.pressed = true;
}


void MQTTcrtl(void* param)
{
    buffer_circular* buff_mqtt_in = (buffer_circular*) param;
    TickType_t xLastWakeTime;
    xLastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    mensaje tmp;
    if (get_item(&tmp,buff_mqtt_in) != -1)
    {
      enviarMensajePorTopic(tmp.topic,tmp.msg);
    }
    vTaskDelayUntil( &xLastWakeTime, ( 250 / portTICK_PERIOD_MS );
  }
    
}

void TEMPcrtl(void param*)
{
  buffer_circular* buff_mqtt_out = (buffer_circular*) param;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    int lectura = analogRead(pinSensor);
    static bool estado_anterior = false; //Variable para que envie mensajes solo cuando haya un cambio
    if (lectura > 2500 && estado_anterior == false) 
    {
      digitalWrite(ledTemp, HIGH);
      put_item({ESP_OUT_TOPIC,"EMERGENCIA_TEMPERATURA_ELEVADA"},buff_mqtt_out);
      estado_anterior = true;
    } else if(lectura <= 2500 && estado_anterior = true)
    {
      put_item({ESP_OUT_TOPIC,"EMERGENCIA_TEMPERATURA_ELEVADA"},buff_mqtt_out);
      digitalWrite(ledTemp, LOW);
      estado_anterior = false;
    }
    vTaskDelayUntil( &xLastWakeTime, ( 250 / portTICK_PERIOD_MS );
  }
}

void BANDEJAcrtl(void *param)
{
  buffer_circular* buff_mqtt_in = (buffer_circular*) param;
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  for (;;)
  {
    mensaje tmp;
    if (get_item(&tmp,buff_mqtt_in) != -1)
    {
      String smsg = String(tmp.msg); 
      if(smsg == "AVISO_MALAS_LLENA") {
      digitalWrite(ledFullMalas,HIGHT);
    }
      if (smsg == "AVISO_NUEVAS_VACIA")
      {
        digitalWrite(ledEmptyMalas,HIGTH);
      }
    }
    
    if (boton_rellenar.pressed)
    {
      put_item({ESP_OUT_TOPIC,"RELLENADO_TARJETAS"},&g_mqtt_buffer_out);
      digitalWrite(ledEmptyNuevas, LOW);
      boton_rellenar.pressed = false;
    }
    if (boton_vaciar.pressed)
    {
      put_item({ESP_OUT_TOPIC,"VACIADO_TARJETAS"},&g_mqtt_buffer_out);
      digitalWrite(ledFullMalas, LOW);
      boton_vaciar.pressed = false;
    }
    vTaskDelayUntil( &xLastWakeTime, ( 250 / portTICK_PERIOD_MS );
  }
  
}

void EMERGENCIAcrtl() 
{
  if (boton_emergencia.pressed) 
  {
    put_item({ESP_OUT_TOPIC,"PARADA_EMERGENCIA"});
    boton_emergencia.pressed = false;
  }

  ultimoEstadoEmergencia = estado;
}

void gpio_init() 
{
    pinMode(pinSensor, INPUT);
    pinMode(ledTemp, OUTPUT);
    pinMode(ledEmptyNuevas, OUTPUT);
    pinMode(ledFullMalas, OUTPUT);

    pinMode(btnRellenar, INPUT_PULLUP);
    pinMode(btnVaciar, INPUT_PULLUP);
    pinMode(btnEmergencia, INPUT_PULLUP);

    digitalWrite(ledTemp, LOW);
    digitalWrite(ledEmptyNuevas, LOW);
    digitalWrite(ledFullMalas, LOW);
}

