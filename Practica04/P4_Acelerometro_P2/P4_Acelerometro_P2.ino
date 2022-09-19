#define x A0
#define y A1
#define z A2

float valX = 0;
float valY = 0;
float valZ = 0;

float Xg = 0;
float Yg = 0;
float Zg = 0;

float x_min = 272.0;
float x_max = 414.0;
float y_min = 272.0;
float y_max = 414.0;
float z_min = 272.0;
float z_max = 414.0;

float alphaR = 0.0;
float betaR = 0.0;
float alphaG = 0.0;
float betaG = 0.0;

void setup() {
  Serial.begin(9600); //Nos permite comunicarnos entre la computadora y el arduino a esa velocidad de 9600 
}

void loop() {
  valX = analogRead(x);
  valY = analogRead(y);
  valZ = analogRead(z);

  Xg = map(valX, x_min, x_max, -100, 100);
  Xg = -Xg /100;
  Yg = map(valY, y_min, y_max, -100, 100);
  Yg = Yg /100;
  Zg = map(valZ, z_min, z_max, -100, 100);
  Zg = Zg /100;

  alphaR = -atan(Yg / sqrt( pow(Xg,2) + pow(Zg,2) ));
  betaR = atan(Xg / sqrt( pow(Yg,2) + pow(Zg,2) ));

  alphaG = alphaR * 180 / PI;
  betaG = betaR * 180 / PI;

  /*
  Serial.print("X: ");
  Serial.print(valX);
  Serial.print("   Y: ");
  Serial.print(valY);
  Serial.print("   Z: ");
  Serial.println(valZ);
  
  Serial.print("Xg: ");
  Serial.print(Xg);
  Serial.print("   Yg: ");
  Serial.print(Yg);
  Serial.print("   Zg: ");
  Serial.print(Zg);
  */
  Serial.print("   ALPHA: ");
  Serial.print(alphaG);
  Serial.print("   BETA: ");
  Serial.println(betaG);

  //Serial.println("");
  
  delay(100);
}
