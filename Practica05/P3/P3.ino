#define MotA 10
#define MotB 11
#define pot A0
#define out 9

int value = 0;
int v = 0;
int cont  = 0;
int pwm = 0;
int vPorcentaje = 0;

void setup() {
  pinMode(pot, INPUT);
  pinMode(out, OUTPUT);
  pinMode(MotA, OUTPUT);
  pinMode(MotB, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  cont++;
  value = analogRead(pot);
  v = map(value, 0, 1023, 0, 500);
  pwm = value/4;

  vPorcentaje = map(value, 0, 1023, 0, 500);
  
  Serial.print("Edo: ");
  Serial.print(cont);
  Serial.print("   VPot: ");
  Serial.print(value);
  Serial.print("   Acción: ");
  Serial.print(value/4);
  Serial.print("   Función:  ");
  
  if(value <= 200){
    levogiro();
    pwm = map(vPorcentaje, 0, 200, 0, 255);
    digitalWrite(out, 255-pwm);
  }

  if(200 < value and value < 300){
    detenido();
    digitalWrite(out, 255-pwm);
  }
  
  if(300 < value and value < 500){
    dextrogiro();
    pwm = map(vPorcentaje, 300, 500, 0, 255);
    digitalWrite(out, pwm);
  }
  
}

void levogiro(){
  digitalWrite(MotA, 1);
  digitalWrite(MotB, 0);
  Serial.println("Levogiro");
}

void dextrogiro(){
  digitalWrite(MotA, 0);
  digitalWrite(MotB, 1);
  Serial.println("Dextrogiro");
}

void detenido(){
  digitalWrite(MotA, 1);
  digitalWrite(MotB, 1);
  Serial.println("Detenido");
}
