//Mario's Ideas
//Controlling coin acceptor with Arduino
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
//#include <Wire.h>
#include <EEPROM.h>

// variable use to measuer the intervals inbetween impulses
int i = 0;
// Number of impulses detected
int impulsCount = 0;
// Sum of all the coins inseted
float total_amount = 0;

void setup() {
  // pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
  pinMode(4, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Coin Acceptor ");
  lcd.setCursor(0, 1);
  lcd.print("WELCOME ");
  // Interrupt connected to PIN D2 executing IncomingImpuls function when signal goes from HIGH to LOW
  attachInterrupt(0, incomingImpuls, FALLING);
  EEPROM.get(0, total_amount);
  delay(2000);
  lcd.clear();
  delay(200);

}

void incomingImpuls()
{
  impulsCount = impulsCount + 1;
  i = 0;
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("Masukan Coin: ");

  i = i + 1;
  Serial.print("i=");
  Serial.print(i);
  Serial.print(" Impulses:");
  Serial.print(impulsCount);
  Serial.print(" Total:");
  Serial.println(total_amount);

  if (i >= 30 and impulsCount == 1) {
    total_amount = total_amount + 500;
    impulsCount = 0;
    EEPROM.put(0, total_amount);
  }

  if (i >= 30 and impulsCount == 2) {
    total_amount = total_amount + 500;
    impulsCount = 0;
    EEPROM.put(0, total_amount);
  }
  if (i >= 30 and impulsCount == 3) {
    total_amount = total_amount + 1000;
    impulsCount = 0;
    EEPROM.put(0, total_amount);
  }

  if (total_amount == 1000) {
    if (digitalRead(50) == HIGH) {
      impulsCount = 0;
      // Sum of all the coins inseted
      total_amount = 0;
      EEPROM.put(0,  total_amount);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BELI PERMEN");
      delay(4000);
      lcd.clear();
      delay(200);
    }
  }

  
  if (total_amount == 500) {
    if (digitalRead(50) == HIGH) {
      impulsCount = 0;
      // Sum of all the coins inseted
      total_amount = 0;
      EEPROM.put(0,  total_amount);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("BELI SUSU");
      delay(4000);
      lcd.clear();
      delay(200);
    }
  }
  //  if (i >= 30 and impulsCount == 4) {
  //    total_amount = total_amount + 0.2;
  //    impulsCount = 0;
  //    EEPROM.put(0, total_amount);
  //  }
  //  if (i >= 30 and impulsCount == 5) {
  //    total_amount = total_amount + 0.1;
  //    impulsCount = 0;
  //    EEPROM.put(0, total_amount);
  //  }

  //
//    if (digitalRead(50) == LOW) {
//      impulsCount = 0;
//      // Sum of all the coins inseted
//      total_amount = 0;
//      EEPROM.put(0,  total_amount);
//  
//    }


  //  if (total_amount < 10) display.showNumberDecEx(total_amount * 10, 0b10000000, true, 2, 2);
  //  else
  //    display.showNumberDecEx(total_amount * 10, 0b00100000, false, 4, 0);
}
