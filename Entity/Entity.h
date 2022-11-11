#pragma once

#include "Position.h"
#include "Display.h"

class Entity {
  public:
    Entity(Position pos, char symbol);
    Position getPos();
    Position setPos(Position newPos) ;
    virtual void move(Display display, Position newPos);
  protected:
    Position randPos();
    // void draw();
    Position pos;
    const char symbol;
};