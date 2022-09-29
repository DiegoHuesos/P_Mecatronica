#include <Wire.h>
#define MotA 10
#define MotB 11
#define pot A10
#define sal 9

float pote, potencia, salida;

void setup() {
  pinMode(MotA,OUTPUT);
  pinMode(MotB,OUTPUT);
  pinMode(sal, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  pote=analogRead(pot);
  potencia = map(pote,0, 1023, 0, 5);
  
  if(potencia>=3 && potencia<= 5){
    Dextrogiro();
    salida = map(pote,615,1023,0,255);
    }else{
      if(potencia>=2){
        salida = 0;
        Detenido();
        }else{
          salida = map(pote,410,0,0,255);
          Levogiro();
        }
      }
   
   analogWrite(sal, salida);
   Serial.println(salida);
   Serial.println(potencia);
}

void Levogiro(){
  digitalWrite(MotA, HIGH);
  digitalWrite(MotB, LOW);
  Serial.print("Levogiro ");
}

void Detenido(){
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, LOW);
  Serial.print("Detenido");
}

void Dextrogiro(){
  digitalWrite(MotA, LOW);
  digitalWrite(MotB, HIGH);
  Serial.print("Dextrogiro ");
  delay(253);
}
