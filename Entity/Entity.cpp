#include "Entity.h"

#include "LiquidCrystal_I2C.h"

#include "Display.h"

Entity::Entity(Position pos, char symbol) 
  : pos{ pos }, symbol{ symbol } {

};

void Entity::move(Display display, Position newPos) {
  display.renderMove(pos, newPos, symbol);
  Entity::setPos(newPos);
};

Position Entity::getPos() const {
  return pos;
};

Position Entity::setPos(Position newPos) {
  pos = newPos;
  return pos;
};

Position Entity::randPos() {
   
};

// void Entity::draw() {

// };