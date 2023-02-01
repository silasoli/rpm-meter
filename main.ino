#include <LiquidCrystal.h>
float value = 0;
float rev = 0;
int rpm, count = 0;
int oldtime = 0;
int time;

LiquidCrystal lcd(8, 7, 6, 5, 4, 3);

void isr() {
  rev++;
  count++;
}

void setup()
{

  Serial.begin(9600);
  lcd.begin(16, 2);
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);
}

void loop() {
  delay(1000);
  detachInterrupt(2);
  time = millis() - oldtime;
  rpm = (rev / time) * 60000;
  oldtime = millis();
  rev = 0;
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);
  Serial.println(rpm);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("RPM:");
  lcd.setCursor(4, 4);
  lcd.print(rpm);

}
