/*
   Código demonstrativo para a aula de Bancos de Dados aplicados à Internet das Coisas,
   Curso de Engenharia e Administração de Sistemas de Banco de Dados,
   Faculdade de Tecnologia - UNICAMP.
*/
 
/*
  Estrutura da Tabela

  rec         - int(4)       - Primary Key - Auto_Increment - Not Null
  dispositivo - varchar(10)  - Not Null
  a0          - int(5)       - Not Null
  a1          - int(5)       - Not Null
  a2          - int(5)       - Not Null
  a3          - int(5)       - Not Null
*/

#include <WiFi.h>
#include <ESP32_MySQL.h>

char server[] = "local_hospedagem_sgbd";
char dispositivo[10] = "hwxx";
char query[80];

ESP32_MySQL_Connection conn((Client *)&client);

void runQuery() {

  ESP32_MySQL_Query query_mem = ESP32_MySQL_Query(&conn);

  if ( !query_mem.execute(query) )  {
    Serial.println("\nQuery: Erro \n");
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

  int a0 = 0, a1 = 0, a2 = 0, a3 = 0;

  a0 = analogRead(33);
  a1 = analogRead(32);
  a2 = analogRead(35);
  a3 = analogRead(34);

  sprintf(query, "INSERT INTO sua_tabela values (\"\",\"%s\",%d,%d,%d,%d);", dispositivo, a0, a1, a2, a3);

  // conn.connect(end_servidor, porta_servico, "username", "password", "nome_banco")
  if (conn.connect(server, 3306, "seu_username", "sua_senha", "seu_nome_do_banco")) {

    delay(500);

    runQuery();

    Serial.println();
    Serial.print("Dispositivo: ");
    Serial.println(dispositivo);
    Serial.println("-----------------------------------------------");
    Serial.print("A0: ");
    Serial.println(a0);
    Serial.print("A1: ");
    Serial.println(a1);
    Serial.print("A2: ");
    Serial.println(a2);
    Serial.print("A3: ");
    Serial.println(a3);
    Serial.println();

    conn.close();

  } else {
    Serial.println("Conexao: Apresentou problemas.");
  }

  Serial.println("Conexao: Nova em 60 segundos");

  delay(60000);

}
