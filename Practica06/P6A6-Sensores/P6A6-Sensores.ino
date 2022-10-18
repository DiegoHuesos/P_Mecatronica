#define inVoltVoltimetro A0 

int voltVoltimetro;
bool vltm;

void setup() {
  pinMode(inVoltVoltimetro, INPUT);
  Serial.begin(9600);
}

void loop() {
  voltimetro();
}

bool voltimetro(){
  voltVoltimetro = analogRead(inVoltVoltimetro)*5/1023;
  Serial.print("VoltVoltimetro: " + String(voltVoltimetro));
  if(voltVoltimetro < 6.8)
    return true;
  return false;
}