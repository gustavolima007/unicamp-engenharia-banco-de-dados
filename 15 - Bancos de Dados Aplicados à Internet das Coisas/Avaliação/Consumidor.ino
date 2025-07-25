/*
 * Projeto 05 - Subscriber (Recupera e mostra os dados do banco)
 * Curso: Bancos de Dados Aplicados à IoT
 * Faculdade de Tecnologia - UNICAMP
 * Equipe:
 * - Gustavo Ferreira Lima
 * - Mateus de Almeida Frigo
 * - Raquel Rasquinho Caetano
 */

#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32_MySQL.h>

// --- Configurações do Display LCD ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Configurações da Rede Wi-Fi ---
#define WIFI_SSID     "Wokwi-GUEST"
#define WIFI_PASSWORD ""

// --- Configurações do Banco de Dados MySQL ---
#define HOST_DB       "jlzem.io"
#define PORTA_DB      3306
#define USER_DB       "u907186638_root"
#define PASS_DB       "Testes_2024"
#define NOME_DB       "u907186638_SmartObject"
#define TABELA        "avaliacao"
#define DISPOSITIVO   "hw22" // Dispositivo a ser monitorado

// --- Instância dos Objetos do Banco ---
ESP32_MySQL_Connection conn((Client *)&client);
ESP32_MySQL_Query query_cons(&conn);
char query[256];

unsigned long ultimaConsulta = 0;

// --- Função para Exibir Mensagens no LCD ---
void mostrar(String l1, String l2) {
  lcd.clear();
  lcd.setCursor(0, 0); lcd.print(l1);
  lcd.setCursor(0, 1); lcd.print(l2);
  delay(1500); // Aumentei um pouco o delay para melhor leitura
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  // --- Mensagens Iniciais com os Nomes da Equipe ---
  mostrar("Fac. Tecnologia", "Unicamp Limeira");
  mostrar("Bancos de Dados", "Aplicados a IoT");
  mostrar("Projeto 05", "# Subscriber #");
  mostrar("Gustavo Ferreira", "Lima");
  mostrar("Mateus de Almeida", "Frigo");
  mostrar("Raquel Rasquinho", "Caetano");

  // --- Conexão Wi-Fi ---
  mostrar("Wi-Fi", "Conectando...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    lcd.print(".");
  }
  mostrar("Wi-Fi OK", "Conectado!");

  // --- Conexão com o Banco de Dados ---
  mostrar("Conectando...", "MySQL");
  if (conn.connect(HOST_DB, PORTA_DB, USER_DB, PASS_DB, NOME_DB)) {
    mostrar("MySQL OK", "Conectado!");
  } else {
    mostrar("ERRO", "Conexao BD");
  }
  delay(2000);
}

void loop() {
  // Executa a cada 30 segundos
  if (millis() - ultimaConsulta >= 30000) {
    ultimaConsulta = millis();

    // --- Monta a Query para buscar o último registro do dispositivo ---
    snprintf(query, sizeof(query),
       "SELECT dispositivo, tempc, gasu, lumiu, distc FROM %s WHERE dispositivo = '%s' ORDER BY codreg DESC LIMIT 1",
       TABELA, DISPOSITIVO);

    Serial.println("Executando SELECT:");
    Serial.println(query);

    // --- Garante que a conexão com o BD está ativa ---
    if (!conn.connected()) {
      Serial.println("Reconectando MySQL...");
      if (!conn.connect(HOST_DB, PORTA_DB, USER_DB, PASS_DB, NOME_DB)) {
        mostrar("ERRO", "Reconectar BD");
        return; // Tenta novamente no próximo ciclo
      }
    }

    // --- Executa a Query e Processa os Dados ---
    if (query_cons.execute(query)) {
      query_cons.get_columns();
      row_values* row = query_cons.get_next_row();

      if (row != NULL) {
        // Converte os valores recebidos
        String dispositivo = String(row->values[0]);
        int tempC   = atoi(row->values[1]);
        int gasU    = atoi(row->values[2]);
        int lumU    = atoi(row->values[3]);
        int distC   = atoi(row->values[4]);
        int distP   = (distC > 0) ? distC / 2.54 : 0; // Converte cm para polegadas

        // Mostra os dados no LCD
        mostrar("Dispositivo:", dispositivo);
        mostrar("Temperatura:", String(tempC) + " C");
        mostrar("Gas:", String(gasU) + " u");
        mostrar("Luz:", String(lumU) + " u");
        mostrar("Distancia:", String(distC) + " cm");
        mostrar("Distancia:", String(distP) + " pol");

      } else {
        Serial.println("Query OK, mas nenhum dado encontrado para o dispositivo.");
        mostrar("Aguardando dado", "p/ " + String(DISPOSITIVO));
      }
    } else {
      Serial.println("Erro ao executar SELECT");
      mostrar("ERRO", "SELECT SQL");
    }
  }
}