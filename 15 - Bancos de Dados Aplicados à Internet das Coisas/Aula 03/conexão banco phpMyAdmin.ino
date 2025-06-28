/*
   Código demonstrativo para a aula de Bancos de Dados aplicados à Internet das Coisas,
   Curso de Engenharia e Administração de Sistemas de Banco de Dados,
   Faculdade de Tecnologia - UNICAMP.
*/

#include <WiFi.h>
#include <ESP32_MySQL.h>

char server[] = "testes.jlzem.io";
char query[80];

ESP32_MySQL_Connection conn((Client *)&client);

void runQuery() {

  ESP32_MySQL_Query query_mem = ESP32_MySQL_Query(&conn);

  Serial.print("Query: ");
  Serial.println(query);

  if ( !query_mem.execute(query) )  {
    Serial.println("Query: Erro.");
    return;
  }

  delay(500);

}

void setup() {

  Serial.begin(9600);
  while (!Serial)    {     }

  WiFi.begin("Wokwi-GUEST", "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }

  Serial.println("\n-----------------------------------------------");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("-----------------------------------------------");

  delay(1000);
}

void loop() {

  char nome[50] = "Gustavo_Lima";
  char mensagem[50] = "Olá";

  sprintf(query, "INSERT INTO Mensagens values (\"\",\"%s\",\"%s\");", nome, mensagem);

  // conn.connect(end_servidor, porta_servico, "username", "password", "nome_banco")
  if (conn.connect(server, 3306, "u907186638_testes", "BDIoT_2025", "u907186638_Mensagens")) {

    delay(500);

    Serial.println("Conexao: Iniciada.");

    runQuery();

    Serial.println("Conexao: Encerrada.");

    conn.close();

  } else {

    Serial.println("Conexao: Com problemas.");

  }

  Serial.println("Conexao: Nova em 30 segundos");
  Serial.println();

  delay(30000);

}
