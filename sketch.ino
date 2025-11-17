#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>
#include "MPU6050.h"

MPU6050 mpu;

// CONFIG WIFI
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// MQTT
const char* mqtt_server = "broker.hivemq.com";
WiFiClient espClient;
PubSubClient client(espClient);

// PINOS DOS POTENCIOMETROS
#define POT_STRESS 34       // original
#define POT_PRESSAO 35      // novo potenciômetro para detectar sentado

// LIMIAR DE PRESSÃO (ajustar depois olhando no serial)
int limitePressao = 800;

void setup_wifi() {
  delay(100);
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao MQTT...");
    if (client.connect("ESP32-Ergonomia")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Erro: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(); 
  mpu.initialize();

  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Leitura do potenciômetro (stress)
  int potStress = analogRead(POT_STRESS);
  int stressLevel = map(potStress, 0, 4095, 0, 100);

  // Leitura do potenciômetro (pressão = sentado)
  int potPressao = analogRead(POT_PRESSAO);
  bool sentado = potPressao > limitePressao;

  // Debug serial
  Serial.print("Stress: ");
  Serial.print(stressLevel);
  Serial.print(" | Pressão: ");
  Serial.print(potPressao);
  Serial.print(" | Sentado: ");
  Serial.println(sentado ? "SIM" : "NAO");

  // Leitura MPU6050
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float inclinacao = atan2(ax, az) * 57.2958;

  // Cria JSON incluindo "sentado"
  char payload[200];
  sprintf(payload,
          "{\"stress\": %d, \"inclinacao\": %.2f, \"ax\": %d, \"ay\": %d, \"az\": %d, \"sentado\": %s}",
          stressLevel, inclinacao, ax, ay, az, sentado ? "true" : "false");

  // Publica no MQTT
  client.publish("ergonomia/mpu", payload);

  Serial.println("Enviado MQTT: ");
  Serial.println(payload);

  delay(1000);
}
