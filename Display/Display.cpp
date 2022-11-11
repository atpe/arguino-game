#include "Display.h"

#include "LiquidCrystal_I2C.h"

Display::Display(int address, Position max)
{
  Display::screen = LiquidCrystal_I2C(address, max.x, max.y);
  Display::max = max;
};

void Display::renderMove(Position oldPos, Position newPos, char symbol) {
  screen.setCursor(oldPos.x, oldPos.y);
  screen.print(' ');
  screen.setCursor(newPos.x, newPos.y);
  screen.print(symbol);
};

int Display::getMax(char axis) {
  switch (axis)
  {
  case 'x':
    return Display::max.x;
    break;
  case 'y':
    return Display::max.y;
    break;
  default:
    break;
  }
};