#include "Enemy.h"

Enemy::Enemy(Display display, char symbol, int type)
  : Entity {pos, symbol},
  type { type }
{
  const int x = random(1, display.getMax('x'));
  const int y = random(1, display.getMax('y'));
  Position newPos = {x, y};
  display.renderMove(pos, newPos, symbol);
}
