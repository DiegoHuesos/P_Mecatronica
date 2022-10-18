#define echoPin 9
#define trigPin 10
#define led 8

long duracion;
int distancia;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(led, OUTPUT); 
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracion = pulseIn(echoPin, HIGH);

  distancia = duracion * 0.0343 / 2;

  if(distancia < 15){
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");
}
