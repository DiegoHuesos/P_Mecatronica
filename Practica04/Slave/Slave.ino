#include <Wire.h>

#define led 13

int dato;

void setup() {
  Wire.begin(0xAF);
  Wire.onReceive(  lectura  );
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println(dato);
  delay(99);
}

void lectura(int howMany){
  dato = Wire.read();
  if(dato == 1){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
}
