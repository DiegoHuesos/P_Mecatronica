#define outLed 7    //Pin Digital 7 PWM
#define inVolt A0   //Pin digital de lectura 222

int volt = 0;

void setup() {
  pinMode(inVolt, INPUT);
  pinMode(outLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  volt = analogRead(inVolt)*5/1023;
  Serial.println(volt);
  
  if(volt < 3.2){
    digitalWrite(outLed, HIGH);
  }

  if(3.2 < volt and volt < 4.2){
    digitalWrite(outLed, HIGH);
    delay(50);
    digitalWrite(outLed, LOW);
    delay(50);
  }
  
}
