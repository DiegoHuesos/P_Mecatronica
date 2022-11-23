/**
 * @author Diego Hernández Delgado 
 * @author Sebastián González Hacker
 * @author Rogelio Torres Olivera
 * @author Santiago Moreno 
 * @professor Sergio Hernández Sánchez
 * @date 18-11-2022
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
#define inVoltLuminosidad_L A1      //Sensor de luminosidad
#define inVoltLuminosidad_R A2      //Sensor de luminosidad
#define inVoltLuminosidad_F A3      //Sensor de luminosidad
#define inVoltLuminosidad_B A4      //Sensor de luminosidad
#define DHTPIN 10                 //Sensor de temperatura
#define DHTTYPE DHT11             //Define luminosidad
#define echoPin1 53                 //Puerto de echo, sensor ultrasónico
#define trigPin1 51                //Puerto de trigger, sensor ultrasónico
#define echoPin2 49                 //Puerto de echo, sensor ultrasónico
#define trigPin2 47                //Puerto de trigger, sensor ultrasónico
#define inVoltSharp1 A8            //Sensor Sharp1
#define inVoltSharp2 A9            //Sensor Sharp2

//DEFINICIÓN DE VARIABLES
//lcd
LiquidCrystal_I2C lcd(0x27,16,2);  //Set the LCD address to 0x27 for a 16 chars and 2 line display
//Voltímetro
int voltaje;
int battery;
//Luminosidad
float voltLuminosidad_L;
float voltLuminosidad_R;
float voltLuminosidad_F;
float voltLuminosidad_B;
float pwmLuminosidad_L;
float pwmLuminosidad_R;
float pwmLuminosidad_F;
float pwmLuminosidad_B;
float L_LDR;
float R_LDR;
float F_LDR;
float B_LDR;
float light_dif;
//Temperatura-Humedad
float tempC;
DHT dht(DHTPIN, DHTTYPE);
//Ultrasónico
long duracionUltrasonico;
int US_Sensor1;
int US_Sensor2;

//Sharp
long voltajeInSharp1;
long L_Sensor;
long voltajeInSharp2;
long R_Sensor;




//FUNCIÓN SETUP
void setup() {
  Serial.begin(9600);
  Serial.println("setup");

  //Asignación de la modalidad de los pines
  pinMode(outLed, OUTPUT);
  pinMode(inVoltLuminosidad_L, INPUT);
  pinMode(inVoltLuminosidad_R, INPUT);
  pinMode(inVoltLuminosidad_F, INPUT);
  pinMode(inVoltLuminosidad_B, INPUT);
  pinMode(inVoltVoltimetro, INPUT);
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT); 
  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT); 
  pinMode(inVoltSharp1, INPUT); 
  pinMode(inVoltSharp2, INPUT); 

  //Inicialización del la pantalla LCD
  lcd.init();    
  lcd.backlight();
  //lcd.setCursor(0,0);
  //lcd.clear();
  Serial.println("lcd");
  //Inicialización de la comunicación con el sensor de humedad
  dht.begin();
}



//FUNCIÓN LOOP
void loop() {
  voltageSensor();
  lightSensor();
  temperatureSensor();
  distanceSensor();
  LCD_print();
}


//FUNCIONES AUXILIARES

void voltageSensor(){
  voltaje = analogRead(inVoltVoltimetro); //*5/1023;
  Serial.print("V: ");
  Serial.print(voltaje*5/1023);
  Serial.print(" v -- ");
  if(voltaje < 687)  //687 bits ==> 6.4 V
    battery = 0;
  else
    battery = 1;
}


void lightSensor(){
  voltLuminosidad_L = analogRead(inVoltLuminosidad_L);  
  pwmLuminosidad_L = map(voltLuminosidad_L, 0, 1023, 0, 255);
  L_LDR = map(voltLuminosidad_L, 0, 1023, 0, 255);

  voltLuminosidad_R = analogRead(inVoltLuminosidad_R);  
  pwmLuminosidad_R = map(voltLuminosidad_R, 0, 1023, 0, 255);
  R_LDR = map(voltLuminosidad_R, 0, 1023, 0, 255);

  voltLuminosidad_F = analogRead(inVoltLuminosidad_F);  
  pwmLuminosidad_F = map(voltLuminosidad_F, 0, 1023, 0, 255);
  F_LDR = map(voltLuminosidad_F, 0, 1023, 0, 255);

  voltLuminosidad_B = analogRead(inVoltLuminosidad_B);  
  pwmLuminosidad_B = map(voltLuminosidad_B, 0, 1023, 0, 255);
  B_LDR = map(voltLuminosidad_B, 0, 1023, 0, 255);

  light_dif = R_LDR - L_LDR;

  Serial.print("");
  Serial.print("L_L: ");
  Serial.print(pwmLuminosidad_L);
  Serial.print(" b -- ");
  
  Serial.print("L_R: ");
  Serial.print(pwmLuminosidad_R);
  Serial.print(" b -- ");
  
  Serial.print("L_F: ");
  Serial.print(pwmLuminosidad_F);
  Serial.print(" b -- ");

  Serial.print("L_B: ");
  Serial.print(pwmLuminosidad_B);
  Serial.println(" b -- ");
}

int temperatureSensor(){
    tempC = dht.readTemperature();
    
    Serial.print("T: ");
    Serial.print(tempC);
    Serial.print(" ºC -- ");

    if ( isnan(tempC)  ) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return 1;
    }  
}

int distanceSensor(){
  // Ultrasonico 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duracionUltrasonico = pulseIn(echoPin1, HIGH);
  US_Sensor1 = duracionUltrasonico * 0.0343 / 2;
  Serial.println("");
  Serial.print("DU1: ");
  Serial.print(US_Sensor1);

  // Ultrasonico 26
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duracionUltrasonico = pulseIn(echoPin2, HIGH);
  US_Sensor2 = duracionUltrasonico * 0.0343 / 2;
  Serial.print("  -- DU2: ");
  Serial.print(US_Sensor2);
  
  // SHARP 1 - L
  voltajeInSharp1 = analogRead(inVoltSharp1);
  L_Sensor = pow( (916.53) / (voltajeInSharp1) , 0.623);
  //L_Sensor = pow(voltajeInSharp1/758.73,-1/.486);
  
  Serial.print("  -- DS1: ");
  Serial.print(L_Sensor);
  Serial.print(" cm");

  // SHARP 2 - R
  voltajeInSharp2 = analogRead(inVoltSharp2);
  R_Sensor = pow( (916.53) / (voltajeInSharp2) , 0.623);
  //R_Sensor = pow(voltajeInSharp2/758.73,-1/.486);
  
  Serial.print("  -- DS2: ");
  Serial.print(R_Sensor);
  Serial.println(" cm");
}

void LCD_print(){
  //Escribir el valor de la luminosidad en primer renglón del LCD
  lcd.setCursor(0,0);
  lcd.print("                  ");
  lcd.setCursor(0,0);
  lcd.print("LD: ");
  lcd.print(String(light_dif));
  lcd.print(" bits");

  
  if(voltaje > 357){
    lcd.setCursor(0,1);
    lcd.print("                  ");
    lcd.setCursor(0,1);
    lcd.print("VoltErr: ");
    lcd.print(voltaje*5/1023);
    lcd.print(" v");
  }
  
}
