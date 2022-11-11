#pragma once

#include "Display.h"
#include "Entity.h"

class Enemy : public Entity {
  public:
    Enemy(Display display, char symbol, int type);
  private:
    void move();
    const int type;
};