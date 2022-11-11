#pragma once

#include "Player.h"
#include "Position.h"
#include "Display.h"

static class Game {
  public:
    // Constructor
    Game(const int npcCount, const int maxLives);
    void start();
  private:
    // Variables
    Display display(int address, Position max);
    const int npcCount = {0};
    const int maxLives = {0};
    // Methods
    void checkState();
    void startRound();
    void end();

};