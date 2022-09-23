#define MotA 10
#define MotB 11
#define pot A0

int value = 0;

void setup() {
  pinMode(pot, INPUT);
  pinMode(MotA, OUTPUT);
  pinMode(MotB, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  value = analogRead(pot);
  Serial.print("Pot: ");
  Serial.print(value);
  Serial.print("   --> ");
  
  if(value < 409.2){
    levogiro();
  }

  if(409.2 < value and value < 613.8){
    detenido();
  }
  
  if(613.8 < value and value < 1023){
    dextrogiro();
  }
  
}

void levogiro(){
  digitalWrite(MotA, 1);
  digitalWrite(MotB, 0);
  Serial.println("Levogiro");
  delay(1000);
}

void dextrogiro(){
  digitalWrite(MotA, 0);
  digitalWrite(MotB, 1);
  Serial.println("Dextrogiro");
  delay(1000);
}

void detenido(){
  digitalWrite(MotA, 1);
  digitalWrite(MotB, 1);
  Serial.println("Detenido");
  delay(1000);
}
