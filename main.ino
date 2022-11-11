#include "Arduino.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Game.h>

void setup() {
  lcd.init();
  lcd.backlight();

  Wire.begin();
  Serial.begin(9600);

  Game game();
}

void loop() {

}