#pragma once

#include "Entity.h"

class Player : public Entity {
  public:
    Player(Position pos, char symbol, int initialLives);
  private:
    int score;
    int lives;
};



