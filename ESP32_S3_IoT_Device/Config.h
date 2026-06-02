#include <Arduino.h>

// COMM BAUDS
#define BAUDS 115200

#define LOGGER_ENABLED            // Comentar para deshabilitar el logger por consola serie

#define LOG_LEVEL TRACE           // nivells en c_logger: TRACE, DEBUG, INFO, WARN, ERROR, FATAL, NONE

// DEVICE
//#define DEVICE_ESP_ID             "54CE0361421"   // ESP32 ID
#define DEVICE_GIIROB_PR2_ID      "00" //"giirobpr2_00"

// WIFI
#define NET_SSID                  "iPhone"
#define NET_PASSWD                "12345678"

// MQTT
#define MQTT_SERVER_IP            "broker.emqx.io"
#define MQTT_SERVER_PORT          1883
//#define MQTT_USERNAME             ""    // Descomentar esta línea (y la siguiente) para que se conecte al broker MQTT usando usuario y contraseña
//#define MQTT_PASSWORD             ""

#define ESP_IN_TOPIC              "mqtt/pr2/datacenter/g2/ROBODK"    // Topic por el que roboDk envia informacion
#define ESP_OUT_TOPIC              "mqtt/pr2/datacenter/g2/ESP32"    // Topic por el que la Esp32 envia informacion


// IO
#define pinSensor                 34 // Sensor de temperatura real
#define ledTemp                   2  // Led que indica si la temperatura es muy elevada o no
#define btnRellenar               4  // Boton que rellena la bandeja de la simulación
#define btnVaciar                 5  // Boton que vacia la bandeja de la simulación 
#define btnEmergencia             13 // Boton de emergencia que para la simulación
#define ledEmptyNuevas            18 // Led que indica si la bandeja de la simulación está vacía
#define ledFullMalas              17 // Led que indica si la bandeja de la simulación está vacía


#define BUFSIZE 10

struct mensaje {
  char topic[64];
  char msg[64];
  mensaje(const char* t, const char* m) {
    memset(this, 0, sizeof(*this));
    strncpy(topic, t, sizeof(topic) - 1);
    strncpy(msg,   m, sizeof(msg)   - 1);
  }
  mensaje() { memset(this, 0, sizeof(*this)); }
};

struct buffer_circular{
  mensaje buffer[BUFSIZE];
  int bufIN, bufOUT, cont;
  SemaphoreHandle_t mutex;
};

buffer_circular g_mqtt_buffer_in;
buffer_circular g_mqtt_buffer_out;
