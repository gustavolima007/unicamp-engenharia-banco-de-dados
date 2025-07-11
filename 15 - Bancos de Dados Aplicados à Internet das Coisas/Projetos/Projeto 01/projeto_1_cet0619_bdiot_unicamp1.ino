/*------------------------------------------------------
   Projeto Prático 01
  Estação Coletora de Informações Climáticas (i)
  Componentes:
  	- Raquel Rasquinho Caetano - Turma 17
    - Gustavo Ferreira Lima - Turma 16
    - Mateus de Almeida Frigo - Turma 16
------------------------------------------------------*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
#define PINO_TRIGGER 10  
#define PINO_ECHO    9 

#define PIN_LED_13  13
#define PIN_GAS A2

int polegadas = 0;
int centimetros = 0;

int pino_Led  = 13;
int porta_LDR = A3;

int pino_sensor = 0;

int umidade_calculada = 0;
int valor_sensor_solo = 0;

long readUltrasonicDistance(){
  
  digitalWrite(PINO_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIGGER, HIGH);
  delayMicroseconds(10);  
  digitalWrite(PINO_TRIGGER, LOW);
  
  return pulseIn(PINO_ECHO, HIGH);
  
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  Serial.begin(9600);
  
  pinMode(PINO_TRIGGER, OUTPUT);
  pinMode(PINO_ECHO, INPUT); 
  
  pinMode(PIN_LED_13, OUTPUT);

  Serial.begin(9600);
  
  pinMode(pino_Led, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {
  
  lcd.setCursor(0,0);
  lcd.print("Fac.  Tecnologia");
  lcd.setCursor(0,1);
  lcd.print("Unicamp  Limeira");
 
  delay(1000);

  lcd.clear(); 

  lcd.setCursor(0,0);
  lcd.print("Bancos de Dados ");
  lcd.setCursor(0,1);
  lcd.print("Aplicados a IoT ");
  
  delay(1000);
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Projeto 01");
  lcd.setCursor(0,1);
  lcd.print("---------------");
  
  delay(1000);
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Componentes");
  lcd.setCursor(0,1);
  lcd.print("---------------");
  
  delay(1000);
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Raquel");
  lcd.setCursor(0,1);
  lcd.print("R.Caetano");
  
  delay(1000);
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Gustavo");
  lcd.setCursor(0,1);
  lcd.print("F. Lima");
  
  delay(1000);
  
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Mateus");
  lcd.setCursor(0,1);
  lcd.print("De Almeida Frigo");
  
  delay(1000);
  
  lcd.clear();
  
  delay(1000);
  
  lcd.clear();  
    
  lcd.setCursor(0,0);
  lcd.print("Recuperar Dados");
  lcd.setCursor(0,1);
  lcd.print("  dos Sensores");
  
  delay(200);
  
  lcd.clear();
  
  centimetros = 0.01723 * readUltrasonicDistance();
  polegadas = (centimetros / 2.54); 
      
  lcd.setCursor(0,0);
  lcd.print("DIST : ");
  lcd.print(centimetros);
  lcd.print(" Cm");
  lcd.setCursor(0,1);
  lcd.print("DIST : ");
  lcd.print(polegadas);
  lcd.print(" Pol");  
  
  delay(200);
  
  lcd.clear();
  
  int ValorSensor = analogRead(PIN_GAS) ;
  
  Serial.print(ValorSensor);
  Serial.print(" , ");
  
  int ValorCalculado = map(ValorSensor, 273, 730, 0, 100);
  
  if ( ValorCalculado >= 80 ) {
    digitalWrite(PIN_LED_13,HIGH);
  } else {
    digitalWrite(PIN_LED_13,LOW);
  }
  
  lcd.setCursor(0,0);
  lcd.print("GAS : ");
  lcd.print(ValorSensor);
  lcd.print(" u");
  lcd.setCursor(0,1);
  lcd.print("GAS : ");
  lcd.print(ValorCalculado);
  lcd.print(" %");  
  
  delay(200);
  
  lcd.clear();
  
  int valor_LDR = analogRead(porta_LDR);
  int luminosidade = map(valor_LDR,0,679,0,100);
  
  if ( luminosidade < 51 )  {  
    digitalWrite(pino_Led, HIGH);  
  } else  {  
    digitalWrite(pino_Led, LOW);  
  } 

  lcd.setCursor(0,0);
  lcd.print("LDR : ");
  lcd.print(valor_LDR);
  lcd.print(" u");
  lcd.setCursor(0,1);
  lcd.print("LDR : ");
  lcd.print(luminosidade);
  lcd.print(" %");  
  
  delay(200);
  
  lcd.clear();

  int temp_c = (( 5.0 * analogRead(pino_sensor) / 1024 ) - 0.5) * 100 ; 
  int temp_f = (temp_c * 9) / 5 + 32; 

  lcd.setCursor(0,0);
  lcd.print("TEMP : ");
  lcd.print(temp_c,DEC);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("TEMP : ");
  lcd.print(temp_f,DEC);
  lcd.print(" F");
  
  delay(200);
  
  lcd.clear();
  
  valor_sensor_solo = analogRead(A1);
  umidade_calculada = map(valor_sensor_solo, 0, 876, 0, 100);

  lcd.setCursor(0,0);
  lcd.print("HIDRO : ");
  lcd.print(valor_sensor_solo);
  lcd.print(" u");
  lcd.setCursor(0,1);
  lcd.print("HIDRO : ");
  lcd.print(umidade_calculada);
  lcd.print(" %");
  
  delay(200);
  
  lcd.clear();
}
