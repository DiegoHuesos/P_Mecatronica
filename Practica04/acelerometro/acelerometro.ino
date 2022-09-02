#define x A0
#define y A1
#define z A2

float valX = 0;
float valY = 0;
float valZ = 0;

void setup() {
  //pinMode(led, OUTPUT);
  Serial.begin(9600); //Nos permite comunicarnos entre la computadora y el arduino a esa velocidad de 9600 
}

void loop() {
  valX = analogRead(x);
  valY = analogRead(y);
  valZ = analogRead(z);
  
  Serial.print("X: ");
  Serial.print(valX);
  Serial.print("   Y: ");
  Serial.print(valY);
  Serial.print("   Z: ");
  Serial.println(valZ);
  
  delay(10);
}
