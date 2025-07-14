#include "senseclima.h"
#include "HT_DHT22.h"
#include "HT_MQTT_Api.h"
#include <stdio.h>
#include <string.h>

// Declaração externa da variável global mqttClient definida em HT_Fsm.c
extern MQTTClient mqttClient;

void SenseClima_PublishDHT22State(void) {   //(MQTTClient *mqttClient);
    float temperature;  // Declaração da variável temperature
    float humidity;     // Declaração da variável humidity
    int dht_status = DHT22_Read(&temperature, &humidity);
    if (dht_status == 0) {
        char temp_payload[16];
        char hum_payload[16];

        // WORKAROUND: Converte float para string manualmente
        int temp_int_x10 = (int)(temperature * 10);
        int hum_int_x10 = (int)(humidity * 10);

        // Formata a string como "parte_inteira.parte_decimal"
        snprintf(temp_payload, sizeof(temp_payload), "%d.%d", temp_int_x10 / 10, temp_int_x10 % 10);
        snprintf(hum_payload, sizeof(hum_payload), "%d.%d", hum_int_x10 / 10, hum_int_x10 % 10);

        // Usa a variável global mqttClient
        HT_MQTT_Publish(&mqttClient, "hana/externo/senseclima/sensor03/temperature", (uint8_t *)temp_payload, strlen(temp_payload), QOS0, 0, 0, 0);
        HT_MQTT_Publish(&mqttClient, "hana/externo/senseclima/sensor03/humidity", (uint8_t *)hum_payload, strlen(hum_payload), QOS0, 0, 0, 0);
        printf("DHT22 published: temp=%s, hum=%s\n", temp_payload, hum_payload);
    } else {
        printf("Erro ao ler DHT22 (codigo: %d)\n", dht_status);
    }
}