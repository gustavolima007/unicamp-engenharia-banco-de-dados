/*
   Código demonstrativo para a aula de Bancos de Dados aplicados à Internet das Coisas,
   Curso de Engenharia e Administração de Sistemas de Banco de Dados,
   Faculdade de Tecnologia - UNICAMP.
*/ 

#include <WiFi.h>
#include <HTTPClient.h>

// Substituir seu_dispositivo pelo nome que identifica o dispositivo - API LABEL.
// const String url = "http://things.ubidots.com/api/v1.6/devices/seu_dispositivo";

const String url = "http://things.ubidots.com/api/v1.6/devices/dev00";

HTTPClient cliente;

void setup() {

  Serial.begin(115200);
  while (!Serial)    {     }

  WiFi.begin("Wokwi-GUEST", "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }

  Serial.println("-----------------------------------------------");
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("-----------------------------------------------");

  delay(1000);

}

void loop() {

  char payload[80];

  int v1 = analogRead(33);
  int v2 = analogRead(32);
  int v3 = analogRead(35);
  int v4 = analogRead(34);

  Serial.println("");
  Serial.print("A0: ");
  Serial.println(v1);
  Serial.print("A1: ");
  Serial.println(v2);
  Serial.print("A2: ");
  Serial.println(v3);
  Serial.print("A3: ");
  Serial.println(v4);
  Serial.println("");

  //  Substituir sua_variavel pelo nome que identifica a variável desejada - API LABEL.
  // sprintf(payload, "{\"sua_variavel\":%d,\"sua_variavel\":%d,\"sua_variavel\":%d,\"sua_variavel\":%d}", v1, v2, v3, v4);

  sprintf(payload, "{\"a0\":%d,\"a1-1\":%d,\"a2-1\":%d,\"a3-1\":%d}", v1, v2, v3, v4);
  int contentLength  = strlen(payload);

  Serial.println("Requisicao: POST");

  cliente.begin(url);

  cliente.addHeader("Content-Type", "application/json");
  cliente.addHeader("Content-Length", String(contentLength));

  // Substituir seu_token_default pela chave que identifica o seu token - TOKEN default.
  // cliente.addHeader("X-Auth-Token","seu_token_default");

  cliente.addHeader("X-Auth-Token", "BBUS-gEMbL11QN98rZjyduS7wVprax0qc19");

  int statusCode = cliente.POST(payload);
  String response = cliente.getString();

  Serial.print("Status: ");
  Serial.println(statusCode);
  Serial.print("Retorno: ");
  Serial.println(response);
  Serial.println();

  delay(15000);

}
