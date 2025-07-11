//Faculdade de Tecnologia da Unicamp Limeira
//CET0619-Banco de Dados Aplicados a IoT
//Projeto Prático 03 - Consumidor
//Raquel Rasquinho Caetano - Turma 17
//Mateus de Almeida Frigo - Turma 16
//Gustavo Ferreira Lima - Turma 16

#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>

// Wi-Fi e MQTT
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);
WiFiClient espClient;
PubSubClient client(espClient);

// Variáveis dos dados recebidos
float tempC = 0, tempF = 0, distCm = 0, distIn = 0, ldrRaw = 0, ldrP = 0, mq2Raw = 0, mq2P = 0;
bool recebeuDados = false;  // Só exibe no LCD após receber algum dado

void exibir(String linha1, String linha2) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(linha1);
  lcd.setCursor(0, 1);
  lcd.print(linha2);
  delay(1000);
}

void callback(char* topic, byte* payload, unsigned int length) {
  char msg[length + 1];
  for (unsigned int i = 0; i < length; i++) {
    msg[i] = (char)payload[i];
  }
  msg[length] = '\0';

  float valor = atof(msg);

  // Atualiza as variáveis conforme o tópico
  if (strcmp(topic, "hw49rrc/tempC") == 0) tempC = valor;
  else if (strcmp(topic, "hw49rrc/tempF") == 0) tempF = valor;
  else if (strcmp(topic, "hw49rrc/distCm") == 0) distCm = valor;
  else if (strcmp(topic, "hw49rrc/distIn") == 0) distIn = valor;
  else if (strcmp(topic, "hw49rrc/ldrRaw") == 0) ldrRaw = valor;
  else if (strcmp(topic, "hw49rrc/ldrP") == 0) ldrP = valor;
  else if (strcmp(topic, "hw49rrc/mq2Raw") == 0) mq2Raw = valor;
  else if (strcmp(topic, "hw49rrc/mq2P") == 0) mq2P = valor;

  recebeuDados = true;
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("Rasquinhohw49sub")) {
      client.subscribe("hw49rrc/tempC");
      client.subscribe("hw49rrc/tempF");
      client.subscribe("hw49rrc/distCm");
      client.subscribe("hw49rrc/distIn");
      client.subscribe("hw49rrc/ldrRaw");
      client.subscribe("hw49rrc/ldrP");
      client.subscribe("hw49rrc/mq2Raw");
      client.subscribe("hw49rrc/mq2P");
    } else {
      delay(1000);
    }
  }
}

void setup() {
  lcd.init();
  lcd.backlight();

  // Mensagens iniciais
  exibir("Fac. Tecnologia", "Unicamp Limeira");
  exibir("Banco de Dados", "Aplicados a IoT");
  exibir("Projeto 03", "----------------");
  exibir("# Consumidor #", "# Subscriber #");
  exibir("Raquel Rasquinho", "Caetano");
  exibir("Mateus de Almeida", "Frigo");
  exibir("Gustavo Ferreira", "Lima");

  exibir("Conectando ao", "Wi-Fi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }
  exibir("Wi-Fi", "Conectado");

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  reconnect();
}

unsigned long ultimaAtualizacao = 0;
const long intervalo = 30000; // 30 segundos

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long agora = millis();
  if (agora - ultimaAtualizacao > intervalo) {
    ultimaAtualizacao = agora;

    if (recebeuDados) {
        exibir("Recuperar dados", "do Broker");
        delay(1000);

        exibir("Luminosidade:", String(ldrRaw, 0) + " u");
        exibir("Luminosidade:", String(ldrP, 1) + " %");
        delay(1000);

        exibir("Temperatura:", String(tempC, 1) + " C");
        exibir("Temperatura:", String(tempF, 1) + " F");
        delay(1000);

        exibir("Gas:", String(mq2Raw, 0) + " u");
        exibir("Gas:", String(mq2P, 1) + " %");
        delay(1000);

        exibir("Distancia:", String(distCm, 1) + " cm");
        exibir("Distancia:", String(distIn, 1) + " pol");
        delay(1000);
    }
  }
}
