#ifndef __SENSECLIMA_H__
#define __SENSECLIMA_H__

#include "MQTTClient.h" // Para o tipo MQTTClient

// Declare a variável como extern para que outros arquivos possam acessá-la
extern MQTTClient mqttClient;

/**
 * @brief Lê o sensor DHT22 e publica a temperatura e a umidade via MQTT.
 */
void SenseClima_PublishDHT22State(void); //(MQTTClient *mqttClient);

#endif // __SENSECLIMA_H__