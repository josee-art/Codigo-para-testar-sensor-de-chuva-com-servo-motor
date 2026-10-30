#include <Servo.h> 

#define SinalA A0
#define ACUMULADOR_MAX 50
int acumulador = 0;
int pinoServo = 9;
bool estadoChuvaAnterior = false;

Servo meuServo; 

const int POS_ABERTO = 0;
const int POS_FECHADO = 90;   

void setup() {
  pinMode(SinalA, INPUT);
  Serial.begin(9600);  
  meuServo.attach(pinoServo);
  meuServo.write(POS_FECHADO); 
  delay(1000); 
}

void loop() {
  int ValorAnalog = analogRead(SinalA);

  if (ValorAnalog < 510) {
    if (acumulador < ACUMULADOR_MAX) acumulador += 1;
  } else {
    if (acumulador > 0) acumulador -= 5;
    if (acumulador < 0) acumulador = 0;
  }

  bool estaChovendo = estadoChuvaAnterior;
  if (acumulador >= 10) estaChovendo = true; 
  else if (acumulador == 0) estaChovendo = false;
  
  if (estaChovendo != estadoChuvaAnterior) {
    if (estaChovendo) {
      Serial.println("Está chovendo!");
      meuServo.write(POS_ABERTO);
    } else {
      Serial.println("Não está chovendo!");
      meuServo.write(POS_FECHADO);
    }
    estadoChuvaAnterior = estaChovendo;
  }

  Serial.println(ValorAnalog);

  delay(500);
}