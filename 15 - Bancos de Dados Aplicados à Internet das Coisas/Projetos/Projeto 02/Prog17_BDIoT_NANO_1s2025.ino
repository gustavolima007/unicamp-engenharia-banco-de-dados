/* -----------------------------------------------
  Projeto Prático 02
  Estação Coletora de Informações Climáticas (ii)
  Componentes:
  - Raquel Rasquinho Caetano - Turma 17
  - Gustavo Ferreira Lima - Turma 16
  - Mateus de Almeida Frigo - Turma 16
  -----------------------------------------*/

#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20,16,2);

const byte LINHAS = 4;
const byte COLUNAS = 4;

char LayoutTeclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte PinosLinha[LINHAS] = {A0, A1, 7, 6};

byte PinosColuna[COLUNAS] = {5, 4, 3, 2}; 
  
Keypad teclado = Keypad( makeKeymap(LayoutTeclas), PinosLinha, PinosColuna, LINHAS, COLUNAS );

#define PINO_TRIGGER 10
#define PINO_ECHO     9

#define PIN_LED_13  13
#define PIN_GAS 	  A2

#define PIN_LED_13  13
#define PIN_GAS   	A2

int pino_Led = 13;
int porta_LDR = A3;

int pino_sensor = 0;
const float BETA = 3950;

int polegadas = 0;
int centimetros = 0;

long readUltrasonicDistance() {

  digitalWrite(PINO_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(PINO_TRIGGER, LOW);

  return pulseIn(PINO_ECHO, HIGH);
}

void setup() {
  pinMode(12, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Fac.  Tecnologia");
  lcd.setCursor(0,1);
  lcd.print("Unicamp  Limeira");
 
  delay(1000);
  
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Bancos de Dados");
  lcd.setCursor(0,1);
  lcd.print("Aplicados a IoT");
  
  delay(1000);
  
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Projeto 02");
  lcd.setCursor(0, 1);
  lcd.print("-------------------- ");

  delay(1000);

  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("# Pressione  a #");
  lcd.setCursor(0,1);
  lcd.print("#    Tecla     #");
 
}

void loop() {

  int valor_LDR = analogRead(porta_LDR);
  int luminosidade = map(valor_LDR, 8, 1015, 100, 0);
    
  int temp_c = 1 / (log(1 / (1023. / analogRead(pino_sensor) - 1)) / BETA + 1.0 / 298.15) - 273.15;
  int temp_f = (temp_c * 9) / 5 + 32;

  int ValorSensor = analogRead(PIN_GAS) ;

  centimetros = 0.01723 * readUltrasonicDistance();
  polegadas = (centimetros / 2.54);

  int ValorCalculado = map(ValorSensor, 210, 1010, 0, 100);

  if ( ValorCalculado >= 80 ) {
    digitalWrite(PIN_LED_13, HIGH);
  } else {
    digitalWrite(PIN_LED_13, LOW);
  }

  char tecla = teclado.getKey();
 
  if (tecla == '0'){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Luminosidade: ");
    lcd.setCursor(0, 1);
    lcd.print(valor_LDR);
    lcd.setCursor(7,1);
    lcd.print("u");    

    delay(1000);   
  
    lcd.clear();

    if ( luminosidade < 51 )  {
      digitalWrite(pino_Led, HIGH);
    } else  {
      digitalWrite(pino_Led, LOW);
    }

  } else if (tecla == '1') {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Luminosidade: ");
    lcd.setCursor(0, 1);
    lcd.print(luminosidade);
    lcd.setCursor(7,1);
    lcd.print("%");    

    delay(1000);   
  
    lcd.clear();

    if ( luminosidade < 51 )  {
      digitalWrite(pino_Led, HIGH);
    } else  {
      digitalWrite(pino_Led, LOW);
    }

  } else if (tecla == '2') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura: ");
    lcd.setCursor(0, 1);
    lcd.print(temp_c, DEC);
    lcd.setCursor(7,1);
    lcd.print("C");

    delay(1000);

    lcd.clear();  

  } else if (tecla == '3') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura: ");
    lcd.setCursor(0, 1);
    lcd.print(temp_f, DEC);
    lcd.setCursor(7,1);
    lcd.print("F");

    delay(1000); 

  } else if (tecla == '4') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas: ");
    lcd.setCursor(0, 1);
    lcd.print(ValorSensor);
    lcd.setCursor(7,1);
    lcd.print("u");

    delay(1000); 

  } else if (tecla == '5') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gas: ");
    lcd.setCursor(0, 1);
    lcd.print(ValorCalculado);
    lcd.setCursor(7,1);
    lcd.print("%");

    delay(1000);

  } else if (tecla == '6') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distancia: ");
    lcd.setCursor(0, 1);
    lcd.print(centimetros);
    lcd.setCursor(7,1);
    lcd.print("cm");

    delay(1000);

  } else if (tecla == '7') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distancia: ");
    lcd.setCursor(0, 1);
    lcd.print(polegadas);
    lcd.setCursor(7,1);
    lcd.print("pol");

    delay(1000);

  } else if (tecla == '8'){    
    lcd.clear();
    digitalWrite(12, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Led Verde:");
    lcd.setCursor(0, 1);
    lcd.print("Ativado");

    delay(1000);

  } else if (tecla == '9'){
    lcd.clear();
    digitalWrite(12, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Led Verde:");
    lcd.setCursor(0, 1);
    lcd.print("Desativado");

    delay(1000);

  } else if (tecla == '*'){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Raquel");
    lcd.setCursor(0, 1);
    lcd.print("R. Caetano");

    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Gustavo");
    lcd.setCursor(0, 1);
    lcd.print("F. Lima");

    delay(1000);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Mateus De");
    lcd.setCursor(0, 1);
    lcd.print("Almeida Frigo");

    delay(1000);
  }
    
	lcd.setCursor(0,0);
	lcd.print("# Pressione  a #");
	lcd.setCursor(0,1);
	lcd.print("#    Tecla     #");
 
}
