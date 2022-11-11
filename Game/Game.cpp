#include "Game.h"
#include "Enemy.h"
#include "Position.h"


// Constructor
Game::Game(const int npcCount, const int maxLives) {
  Position maxPos = {20, 4};
  display(0x27, maxPos);
  // Initialise enemy entities
  for (int i=0; i=npcCount; i++) {
    // Init with null position
    const Enemy enemy = Enemy('X', 0);
  }
}

void Game::start() {
  
}