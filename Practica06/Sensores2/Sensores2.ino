#define outLed 13    //Pin Digital 7 PWM
#define inVolt A0   //Pin digital de lectura 222

int volt = 0;
float luminosidad = 0;
float pwm = 0;

void setup() {
  pinMode(inVolt, INPUT);
  pinMode(outLed, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  luminosidad = analogRead(inVolt);  
  pwm = map(luminosidad, 0, 1023, 0, 255);

  Serial.print("Lum: ");
  Serial.print(luminosidad);
  Serial.print("Pwm: ");
  Serial.println(pwm);
  
  if(pwm < 190){
    analogWrite(outLed, HIGH);
  }else{
    analogWrite(outLed, LOW);
  }
  
  
}
