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

  Serial.print("Query: ");
  Serial.println(query);

  if ( !query_mem.execute(query) )  {
    Serial.println("Query: Erro.");
    return;
  }

  column_names *cols = query_mem.get_columns();   // Busca as colunas e as exibe.

  Serial.println();

  for (int f = 0; f < cols->num_fields; f++) {
    Serial.print(cols->fields[f]->name);
    if (f < cols->num_fields - 1) {
      Serial.print(",");
    }
  }
  Serial.println("\n--------------------");

  row_values *row = NULL;

  do {

    row = query_mem.get_next_row();   // Le as linhas e as exibe

    if (row != NULL) {
      for (int f = 0; f < cols->num_fields; f++) {
        Serial.print(row->values[f]);
        if (f < cols->num_fields - 1) {
          Serial.print(",");
        }
      }

      Serial.println();
    }

  } while (row != NULL);

  Serial.println();
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

  delay(2000);
}

void loop() {

  Serial.println("\nConexao: Em Andamento ...");

  // conn.connect(end_servidor, porta_servico, "username", "password", "nome_banco")
  if (conn.connect(server, 3306, "seu_username", "sua_senha", "seu_nome_do_banco")) {

    delay(500);

    Serial.println("Conexao: Iniciada.");

    sprintf(query, "SELECT * from sua_tabela where dispositivo = \"%s\" order by rec;", dispositivo);

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
