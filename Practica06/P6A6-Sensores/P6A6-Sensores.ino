/**
 * @author Diego Hernández Delgado (176262)
 * @author Rogelio Torres Olivera
 * @professor Sergio Hernández Sánchez
 * @date 18-10-2022
 * @university ITAM
 * @subject Principios de Mecatrónica
 * @details Integración de sensores de temperatura, humedad, ultrasónico, sharp y multímetro en un circuito conectado
 * a una placa Arduino Mega con el presente código que imprime los valores detectados por los sensores y procesados por 
 * el presente código en el puerto/monitor serial, además, imprime el valor de la luminosidad en el primer renglón de la 
 * pantalla LCD y, finalmente, imprime los mensajes de error que indican ciertas condiciones particulares en el segundo 
 * renglón de la pantalla LCD.
*/


//LIBRERÍAS
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>    //Librería para pantalla LCD
#include "DHT.h"                

//Librería para sensor de luminosidad


//DEFINICIÓN DE PUERTOS
#define outLed 13                 //Led   
#define inVoltVoltimetro A0       //Sensor de voltaje
#define inVoltLuminosidad A1      //Sensor de luminosidad
#define DHTPIN 10                 //Sensor de temperatura
#define DHTTYPE DHT11             //Define luminosidad
#define echoPin 6                 //Puerto de echo, sensor ultrasónico
#define trigPin 7                //Puerto de trigger, sensor ultrasónico
#define inVoltSharp A2            //Sensor Sharp


//DEFINICIÓN DE VARIABLES
int voltimetroValue;
int luminosidadValue;
int temperaturaHumedadValue;
int ultrasonicoValue;
int sharpValue;
//lcd
LiquidCrystal_I2C lcd(0x27,16,2);  //Set the LCD address to 0x27 for a 16 chars and 2 line display
//Voltímetro
int voltVoltimetro;
//Luminosidad
float voltLuminosidad;
float pwmLuminosidad;
//Temperatura-Humedad
float tempC;
DHT dht(DHTPIN, DHTTYPE);
//Ultrasónico
long duracionUltrasonico;
int distanciaUltrasonico;
//Sharp
long voltajeInSharp;
long distanciaSharp;
//Errores
String errorMessage;
int resultadoSensores;



//FUNCIÓN SETUP
void setup() {
  Serial.begin(9600);
  
  //Asignación de la modalidad de los pines
  pinMode(outLed, OUTPUT);
  pinMode(inVoltLuminosidad, INPUT);
  pinMode(inVoltVoltimetro, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(inVoltSharp, INPUT); 
  Serial.println("setup");
  //Inicialización del la pantalla LCD
  lcd.init();    
  lcd.backlight();
  //lcd.setCursor(0,0);
  //lcd.clear();
  Serial.println("lcd");
  //Inicialización de la comunicación con el sensor de humedad
  dht.begin();
  //Inicialización de la comunicación serial
  //Serial.begin(9600);
  //while (!Serial) {  // wait for serial port to connect. Needed for native USB port only
  //  ;
  //}
  //Serial.println("setup");
}



//FUNCIÓN LOOP
void loop() {
  //Invocar funciones auxiliares y guardar sus valores en variables
  voltimetroValue = voltimetro();
  luminosidadValue = luminosidad();
  temperaturaHumedadValue = temperaturaHumedad();
  ultrasonicoValue = ultrasonico();
  sharpValue = sharp();

  //Escribir el valor de la luminosidad en primer renglón del LCD
  lcd.setCursor(0,0);
  lcd.print("                  ");
  lcd.setCursor(0,0);
  lcd.print("L: ");
  lcd.print(String(luminosidadValue));
  lcd.print(" bits");

  //Validación de errores
  resultadoSensores = voltimetroValue + temperaturaHumedadValue + ultrasonicoValue + sharpValue;
  errorMessage = "";
  if(resultadoSensores > 0){     //Si hay al menos un error
    digitalWrite(outLed, HIGH);   //Se enciende el led

    if(resultadoSensores == 1){  //Si solo hay un error se agrega el correspondiente mensaje
      if(voltimetroValue == 1)
        errorMessage= "Low Battery";
      if(temperaturaHumedadValue == 1)
        errorMessage = "Overheating";
      if(ultrasonicoValue == 1)
        errorMessage = "U_Obstacle";
      if(sharpValue == 1)
        errorMessage = "S_Obstacle";
    }else{                          //Si hay más de un error se construye el mensaje (Forma abreviada)
      if(voltimetroValue == 1)
        errorMessage += "Bt-";
      if(temperaturaHumedadValue == 1)
        errorMessage += "Tmp-";
      if(ultrasonicoValue == 1)
        errorMessage += "UObs-";
      if(sharpValue == 1)
        errorMessage += "SObs-";
      errorMessage = errorMessage.substring(0, errorMessage.length()-1);  //Se le quita el último guión del string
    }
  }else{ //Si no hay ningún error, se apaga el led y el mensaje de error está vacío
    digitalWrite(outLed, LOW);
  }
  //Se escribe el mensaje de error en el segundo renglón de LCD
  lcd.setCursor(0,1);
  lcd.print("                  ");
  lcd.setCursor(0,1);
  lcd.print(errorMessage);
}



//FUNCIONES AUXILIARES

int voltimetro(){
  voltVoltimetro = analogRead(inVoltVoltimetro); //*5/1023;

  Serial.print("V: ");
  Serial.print(voltVoltimetro);
  Serial.print(" bits -- ");

  if(voltVoltimetro < 687)  //687 bits ==> 6.4 V
    return 1;
  else
    return 0;
}


float luminosidad(){
  voltLuminosidad = analogRead(inVoltLuminosidad);  
  pwmLuminosidad = map(voltLuminosidad, 0, 1023, 0, 255);

  Serial.print("L: ");
  Serial.print(pwmLuminosidad);
  Serial.print(" bits -- ");
  
  return pwmLuminosidad;
}

int temperaturaHumedad(){
 

    tempC = dht.readTemperature();
    
    Serial.print("T: ");
    Serial.print(tempC);
    Serial.print(" ºC -- ");

    if ( isnan(tempC)  ) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return 1;
    }
  
    if(tempC >= 22)
      return 1;
    else
      return 0;
  
}

int ultrasonico(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracionUltrasonico = pulseIn(echoPin, HIGH);
  distanciaUltrasonico = duracionUltrasonico * 0.0343 / 2;

  Serial.print("DU: ");
  Serial.print(distanciaUltrasonico);
  Serial.print(" cm -- ");

  if(distanciaUltrasonico < 15)
    return 1;
  else
    return 0;
}

int sharp(){
  voltajeInSharp = analogRead(inVoltSharp);
  distanciaSharp = pow( (916.53) / (voltajeInSharp) , 0.623);
  
  Serial.print("DS: ");
  Serial.print(distanciaSharp);
  Serial.println(" cm");

  if(distanciaSharp < 15)
    return 1;
  else
    return 0;
}
