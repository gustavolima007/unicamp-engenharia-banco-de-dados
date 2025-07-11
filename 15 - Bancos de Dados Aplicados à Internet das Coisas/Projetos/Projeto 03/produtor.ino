//Faculdade de Tecnologia da Unicamp Limeira
//CET0619-Banco de Dados Aplicados a IoT
//Projeto Prático 03 - Produtor
//Raquel Rasquinho Caetano - Turma 17
//Mateus de Almeida Frigo - Turma 16
//Gustavo Ferreira Lima - Turma 16

#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

// Wi-Fi e MQTT
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;
const char* mqtt_client_id = "Rasquinhohw49";

// Pinos dos sensores
#define LDR_PIN 32
#define NTC_PIN 33
#define MQ2_PIN 34
#define TRIG_PIN 4
#define ECHO_PIN 2

LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis dos sensores
float temperatureC, temperatureF, distanceCm, distanceIn, ldrValue, ldrPercent, mq2Value, mq2Percent;

void setup() {
  Serial.begin(115200); // Habilita o Serial Monitor

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  lcd.init();
  lcd.backlight();

  // Sequência inicial
  exibir("Fac. Tecnologia", "Unicamp Limeira");
  exibir("Banco de Dados", "Aplicados a IoT");
  exibir("Projeto 03", "----------------");
  exibir("# Produtor #", "# Publisher #");
  exibir("Raquel Rasquinho", "Caetano");
  exibir("Mateus de Almeida", "Frigo");
  exibir("Gustavo Ferreira", "Lima");

  conectarWiFi();
  conectarMQTT();
}

void loop() {
  exibir("Recuperar", "Dados dos Sensores");

  readSensors();
  displayData();
  publishData();

  exibir("Enviar Dados", "ao Broker");
  delay(30000);
}

// Exibição no LCD
void exibir(String linha1, String linha2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linha1);
  lcd.setCursor(0, 1);
  lcd.print(linha2);
  delay(1000);
}

// Conexão Wi-Fi
void conectarWiFi() {
  exibir("Conectando ao", "Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
  exibir("Wi-Fi", "Conectado");
  delay(1000);
}

// Conexão MQTT
void conectarMQTT() {
  client.setServer(mqtt_server, mqtt_port);
  while (!client.connected()) {
    if (client.connect(mqtt_client_id)) {
      exibir("MQTT", "Conectado");
    } else {
      exibir("Falha MQTT", "Reconectando...");
      delay(1000);
    }
  }
}

// Leitura dos sensores
void readSensors() {
  ldrValue = analogRead(LDR_PIN);
  ldrPercent = (ldrValue / 4095.0) * 100.0;

  float ntcRaw = analogRead(NTC_PIN);
  float resistance = 10000.0 * (4095.0 / ntcRaw - 1.0);
  temperatureC = 1.0 / (1.0 / 298.15 + (1.0 / 3950.0) * log(resistance / 10000.0)) - 273.15;
  temperatureF = temperatureC * 9.0 / 5.0 + 32.0;

  mq2Value = analogRead(MQ2_PIN);
  mq2Percent = (mq2Value / 4095.0) * 100.0;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  distanceCm = duration * 0.034 / 2;
  distanceIn = distanceCm / 2.54;
}

// Exibição dos sensores no LCD
void displayData() {
  exibir("Luminosidade LDR", String(ldrValue, 0) + " u");
  exibir("Luminosidade LDR", String(ldrPercent, 1) + " %");
  exibir("Temperatura NTC", String(temperatureC, 1) + " C");
  exibir("Temperatura NTC", String(temperatureF, 1) + " F");
  exibir("Gas MQ2", String(mq2Value, 0) + " u");
  exibir("Gas MQ2", String(mq2Percent, 1) + " %");
  exibir("Distancia SR04", String(distanceCm, 1) + " cm");
  exibir("Distancia SR04", String(distanceIn, 1) + " pol");
}

// Publicação dos sensores (em tópicos separados)
void publishData() {
  if (client.connected()) {
    char buffer[20];

    // Temperatura
    dtostrf(temperatureC, 6, 2, buffer);
    client.publish("hw49rrc/tempC", buffer, true);
    delay(1000);

    dtostrf(temperatureF, 6, 2, buffer);
    client.publish("hw49rrc/tempF", buffer, true);
    delay(1000);

    // Distância
    dtostrf(distanceCm, 6, 2, buffer);
    client.publish("hw49rrc/distCm", buffer, true);
    delay(1000);

    dtostrf(distanceIn, 6, 2, buffer);
    client.publish("hw49rrc/distIn", buffer, true);
    delay(1000);

    // Luminosidade
    dtostrf(ldrValue, 6, 2, buffer);
    client.publish("hw49rrc/ldrRaw", buffer, true);
    delay(1000);

    dtostrf(ldrPercent, 6, 2, buffer);
    client.publish("hw49rrc/ldrP", buffer, true);
    delay(1000);

    // MQ2
    dtostrf(mq2Value, 6, 2, buffer);
    client.publish("hw49rrc/mq2Raw", buffer, true);
    delay(1000);

    dtostrf(mq2Percent, 6, 2, buffer);
    client.publish("hw49rrc/mq2P", buffer, true);
    delay(1000);
  }
}
