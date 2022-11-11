#include "Goal.h"

#include "Display.h"

Goal::Goal(Position pos, char symbol, int reward)
  : Entity{pos, symbol},
  reward{reward}
{
  
};