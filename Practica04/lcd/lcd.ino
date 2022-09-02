#include <LiquidCrystal.h>

bool flag = true;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {
  lcd.begin(16,2);
}

void loop() {
  lcd.setCursor(15,0);
  lcd.print("Rogelio");
  lcd.setCursor(15,1);
  lcd.print("Diego");
  if(flag){
    for (int positionCounter = 0; positionCounter <15; positionCounter++) {
      // scroll one position left:
      lcd.scrollDisplayLeft();
      // wait a bit:
      delay(150);
    }
    flag = false;
  }
  
}
