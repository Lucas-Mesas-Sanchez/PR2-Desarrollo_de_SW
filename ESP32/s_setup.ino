buffer_circular g_mqtt_buffer_in;
buffer_circular g_mqtt_buffer_out;
void on_setup() {

gpio_init();
xTaskCreate(MQTTcrtl,"Control de MQTT",10000,&mqtt_buffer_out,1,NULL);
xTaskCreate(TEMPcrtl,"Control de Temperatura",10000,&mqtt_buffer_out,1,NULL);
xTaskCreate(BANDEJAcrlt,"Control de leds de Bandeja",10000,&mqtt_buffer_in,1,NULL);
xTaskCreate(EMERGENCIAcrlt,"Control de la seta de emerngia",10000,&mqtt_buffer_out,5,NULL);

}
