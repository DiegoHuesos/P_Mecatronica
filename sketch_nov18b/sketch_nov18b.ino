#define LED 13

int estado;
int light_dif;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  switch(estado){
    case 0:
      Serial.println("Estado 0");
      estado = 1;
      break;
      
    case 1:
      Serial.println("Estado 1");
      digitalWrite(LED, LOW);
      lightSensor();
      if( abs(light_dif) < 30 ){
        estado = 2; 
      }else{
        estado = 0;
      }
      break;
      
    case 2:
      Serial.println("Estado 2");
      digitalWrite(LED, HIGH);
      delay(1000);
      break;
  }
}

void lightSensor(){
  light_dif = 20;
  
}
