
void on_setup() {
g_mqtt_buffer_in.mutex = xSemaphoreCreateMutex();
g_mqtt_buffer_out.mutex = xSemaphoreCreateMutex();

gpio_init();
xTaskCreatePinnedToCore(MQTTcrtl,"Control de MQTT",4096,&g_mqtt_buffer_out,1,NULL,0);
xTaskCreatePinnedToCore(TEMPcrtl,"Control de Temperatura",2048,&g_mqtt_buffer_out,1,NULL,1);
xTaskCreatePinnedToCore(BANDEJAcrtl,"Control de leds de Bandeja",2048,&g_mqtt_buffer_in,1,NULL,1);
xTaskCreatePinnedToCore(EMERGENCIAcrtl,"Control de la seta de emerngia",4096,&g_mqtt_buffer_out,5,NULL,1);

}
