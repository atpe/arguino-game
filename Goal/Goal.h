#pragma once

#include "Entity.h"
#include "Position.h"

class Goal : public Entity {
  public:
    Goal(Position pos, char symbol, int reward);
    virtual void move();
  private:
    const int reward;
};