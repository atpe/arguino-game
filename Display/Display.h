#pragma once

#include "LiquidCrystal_I2C.h"

#include "Position.h"

class Display {
  public:
    Display(int address, Position max);
    void renderMove(Position oldPos, Position newPos, char symbol); 
    int getMax(char axis);
  private:
    LiquidCrystal_I2C screen;
    Position max;
};