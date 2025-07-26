/*
 * Faculdade de Tecnologia - UNICAMP
 * BDIoT - Bancos de Dados Aplicados à Internet das Coisas
 * Avaliação Regular – (Projeto Prático 05)
 *
 * Objeto: Produtor / Publisher
 * Descrição: Coleta dados de sensores e envia para um banco de dados MySQL.
 *
 * Equipe:
 * - Gustavo Ferreira Lima
 * - Mateus de Almeida Frigo
 * - Raquel Rasquinho Caetano
 */

// Inclusão de Bibliotecas
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32_MySQL.h>
#include <Ultrasonic.h>

// Configurações da Rede Wi-Fi
#define WIFI_SSID     "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// Configurações do Banco de Dados MySQL
#define HOST_DB       "jlzem.io"
#define PORTA_DB      3306
#define USER_DB       "u907186638_root"
#define PASS_DB       "Testes_2024"
#define NOME_DB       "u907186638_SmartObject"
#define TABELA        "avaliacao"
#define DISPOSITIVO   "hw22"

// Mapeamento de Pinos (Hardware)
#define LDR_PIN       32
#define NTC_PIN       33
#define MQ2_PIN       34
#define TRIG_PIN      4
#define ECHO_PIN      2

// Instância dos Objetos
LiquidCrystal_I2C lcd(0x27, 20, 4);
ESP32_MySQL_Connection conn((Client *)&client); // Usa o 'client' definido em ESP32_MySQL.h
ESP32_MySQL_Query query_insert(&conn);
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

// Variáveis Globais
char query[512];
unsigned long ultimaGravacao = 0;
const unsigned long intervalo = 30000; // 30 segundos

// Protótipos de Funções
void exibir(String linha1, String linha2, int delay_ms = 1500);
float getLuminosity(char unit);
float getTemperature(char unit);
float getGas(char unit);
float getDistance(char unit);
void enviarParaBanco(int lum, int lumP, float tempC, float tempF, int gasU, int gasP, int distCm, int distPol);

void setup() {
    // Inicialização dos Pinos
    pinMode(LDR_PIN, INPUT);
    pinMode(NTC_PIN, INPUT);
    pinMode(MQ2_PIN, INPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Inicialização da Comunicação Serial e LCD
    Serial.begin(115200);
    lcd.init();
    lcd.backlight();

    // Mensagens Iniciais
    exibir("Fac. Tecnologia", "Unicamp Limeira");
    exibir("Bancos de Dados", "Aplicados a IoT");
    exibir("Avaliacao", "Projeto 05");
    exibir("# Produtor #", "# Publisher #");
    exibir("Gustavo Ferreira", "Lima");
    exibir("Mateus de Almeida", "Frigo");
    exibir("Raquel Rasquinho", "Caetano");

    // Conexão Wi-Fi
    exibir("Wi-Fi", "Conectando...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(200);
        lcd.print(".");
    }
    exibir("Wi-Fi OK!", WiFi.localIP().toString());

    // Conexão com o Banco de Dados
    exibir("Conectando...", "MySQL");
    if (conn.connect(HOST_DB, PORTA_DB, USER_DB, PASS_DB, NOME_DB)) {
        exibir("MySQL OK", "Conectado!");
    } else {
        exibir("ERRO", "Conexao BD");
    }
}

void loop() {
    unsigned long tempoAtual = millis();

    // Executa a cada 30 segundos
    if (tempoAtual - ultimaGravacao >= intervalo) {
        ultimaGravacao = tempoAtual;

        exibir("Lendo Sensores", "Aguarde...");

        // Leitura dos Sensores
        int lum = (int)round(getLuminosity('u'));
        int lumP = (int)round(getLuminosity('p'));
        float tempC = getTemperature('C');
        float tempF = getTemperature('F');
        int gasU = (int)round(getGas('u'));
        int gasP = (int)round(getGas('p'));
        int distCm = (int)round(getDistance('c'));
        int distPol = (int)round(getDistance('p'));

        // Exibição dos Dados
        exibir("Luminosidade:", String(lum) + " u");
        exibir("Luminosidade:", String(lumP) + " %");
        exibir("Temperatura:", String(tempC) + " C");
        exibir("Temperatura:", String(tempF) + " F");
        exibir("Gas:", String(gasU) + " u");
        exibir("Gas:", String(gasP) + " %");
        exibir("Distancia:", String(distCm) + " cm");
        exibir("Distancia:", String(distPol) + " pol");

        // Envio dos Dados para o Banco
        exibir("Enviando Dados", "para o Servidor...");
        enviarParaBanco(lum, lumP, tempC, tempF, gasU, gasP, distCm, distPol);

        exibir("Nova Leitura em", "30 segundos...");
    }
}

// Função para Exibir Mensagens no LCD
void exibir(String linha1, String linha2, int delay_ms) {
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print(linha1);
    lcd.setCursor(0, 1); lcd.print(linha2);
    delay(delay_ms);
}

// Função para Ler Luminosidade
float getLuminosity(char unit) {
    float rawValue = analogRead(LDR_PIN);
    rawValue = constrain(rawValue, 32, 4095);
    if (unit == 'p') return constrain(map(rawValue, 32, 4095, 100, 0), 0, 100);
    return rawValue; // unit 'u'
}

// Função para Ler Temperatura
float getTemperature(char unit) {
    int rawValue = analogRead(NTC_PIN);
    if (rawValue == 0) rawValue = 1; // Evita divisão por zero
    float R = 10000.0 * (4095.0 / (float)rawValue - 1.0);
    float tempK = 1.0 / (1.0 / 298.15 + (1.0 / 3950.0) * log(R / 10000.0));
    float tempC = tempK - 273.15;
    if (unit == 'F') return (tempC * 9.0 / 5.0) + 32.0;
    return tempC; // unit 'C'
}

// Função para Ler Sensor de Gás
float getGas(char unit) {
    float rawValue = analogRead(MQ2_PIN);
    rawValue = constrain(rawValue, 32, 4095);
    if (unit == 'p') return constrain(map(rawValue, 32, 4095, 0, 100), 0, 100);
    return rawValue; // unit 'u'
}

// Função para Ler Distância
float getDistance(char unit) {
    int distCm = ultrasonic.read();
    if (distCm <= 0 || distCm > 400) distCm = 0;
    if (unit == 'p') return distCm / 2.54;
    return distCm; // unit 'c'
}

// Função para Enviar Dados ao Banco
void enviarParaBanco(int lum, int lumP, float tempC, float tempF, int gasU, int gasP, int distCm, int distPol) {
    if (conn.connect(HOST_DB, PORTA_DB, USER_DB, PASS_DB, NOME_DB)) {
        exibir("MySQL", "Conectado");

        // Monta a Query
        snprintf(query, sizeof(query),
            "INSERT INTO %s (dispositivo, tempc, tempf, distc, distp, lumiu, lumip, gasu, gasp) "
            "VALUES (\"%s\", %.2f, %.2f, %d, %d, %d, %d, %d, %d);",
            TABELA, DISPOSITIVO, tempC, tempF, distCm, distPol, lum, lumP, gasU, gasP);

        Serial.println("QUERY SQL:");
        Serial.println(query);

        // Executa a Query
        if (query_insert.execute(query)) {
            exibir("INSERT OK", "Dados salvos");
        } else {
            exibir("ERRO", "INSERT SQL");
        }
        conn.close();
    } else {
        exibir("ERRO", "Conexao BD");
    }
}