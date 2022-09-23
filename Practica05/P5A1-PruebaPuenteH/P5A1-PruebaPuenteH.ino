#define MotA 10
#define MotB 11

int dato;

void setup() {
  pinMode(MotA, OUTPUT);
  pinMode(MotB, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //Estado 1
  digitalWrite(MotA, 1);
  digitalWrite(MotB, 0);
  Serial.println("Levogiro");
  delay(1000);

  //Estado 2
  digitalWrite(MotA, 0);
  digitalWrite(MotB, 0);
  Serial.println("Freno pasivo");
  delay(1000);

  //Estado 3
  digitalWrite(MotA, 0);
  digitalWrite(MotB, 1);
  Serial.println("Dextrogiro");
  delay(1000);

  //Estado 4
  digitalWrite(MotA, 1);
  digitalWrite(MotB, 1);
  Serial.println("Freno activo");
  delay(1000);
}
