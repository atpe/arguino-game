#include "Player.h"

Player::Player(Position pos, char symbol, int initialLives)
  : Entity {pos, symbol},
  lives {initialLives}
{

};