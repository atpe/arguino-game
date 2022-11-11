/** INPUTS
*/
const int decY = A0; // BTN - Increases player's y-value
const int incY = A1; // BTN - Increases player's x-value
const int incX = A2; // BTN - Decreases player's x-value

/** OUTPUTS
*/
const int led1 = 5;   // LED - Indicates 1st life
const int led2 = 6;   // LED - Indicates 2nd life
const int led3 = 7;   // LED - Indicates 3rd life
const int RegSel = 8; // LCD - Selects display register
const int Enable = 9; // LCD - Enables display
const int Data4 = 10; // LCD - 5th data pin
const int Data5 = 11; // LCD - 6th data pin
const int Data6 = 12; // LCD - 7th data pin
const int Data7 = 13; // LCD - 8th data pin

/** DISPLAY
*/
const int maxX = 16; // Maximum x-value
const int maxY = 2;  // Maximum y-value

#include <LiquidCrystal.h> // Include LCD library
LiquidCrystal screen(      // Initialise display with output pins
    RegSel,
    Enable,
    Data4,
    Data5,
    Data6,
    Data7);

/** AT (SET CURSOR)
  *  Function to set cursor with better readability
  */
void at(int x, int y)
{
  screen.setCursor(x, y);
}

/** PLAYER VARIABLES
*/
// const char p = 'A';     // Place holder for player
// int pX;                 // Resting x-value
// int pY;                 // Resting y-value
// int _pX;                // Moving x-value
// int _pY;                // Moving y-value
// const int defLives = 3; // Default number of lives
// int actLives;
// int playerIntent; // Input callback variable
//                   //    0: Checking for input
//                   //    1: Moving right
//                   //   -1: Moving left
//                   //    2: Moving up/down
// int score;

// /** ENEMY VARIABLES
// */
// const char e = 'X'; // Place holder for player
// int eX;             // Resting x-value
// int eY;             // Resting y-value
// int _eX;            // Moving x-value
// int _eY;            // Moving y-value
// int enemyIntent;

/** GOAL VARIABLES 
*/
const char g = '-';
int gX;
int gY;
const int maxScore;

/** INPUT VARIABLES
*/
bool increaseY = LOW;     // Moving up/down
bool increaseX = LOW;     // Moving right
bool decreaseX = LOW;     // Moving left
const int pollRate = 200; // Rate to poll buttons in milliseconds

/** SHOW LIVES
*  Function to light bulbs corresponding to remaining lives
*/
void showLives()
{
  switch (actLives)
  {
  case 3:
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    break;
  case 2:
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    break;
  case 1:
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    break;
  default:
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    break;
  }
}

/** START MOVE
*  Function to start a move
*/
void startMove()
{
  pX = _pX; // Overwrite player's old x-value
  pY = _pY; // OVerwrite player's old y-value

  eX = _eX; // Overwrite enemy's old x-value
  eY = _eY; // Overwrite enemy's old y-value

  playerIntent = 0; // Reset check value for next move
}

/** START GOAL
*  Function to set the goal's position
*/
void startGoal()
{
  while (
      checkMatch(gX, gY, pX, pY) ||
      checkMatch(gX, gY, eX, eY))
  {
    gX = random(0, maxX);
    gY = random(0, maxY);
  }
}

/** START ROUND
*  Function to start a round
*/
void startRound()
{
  randomSeed(analogRead(A5)); // Seed the random number generator, so no two games are the same

  showLives(); // Light LEDs

  _pX = 0; // Init player x-value
  _pY = 0; // Init player y-value

  _eX = random(5, 16); // Init enemy resting x-value (random)
  _eY = random(0, 2);  // Init enemy resting y-value (random)

  startGoal();
  startMove();
  drawCharacters();
}

/** START GAME
*  Function to start a game
*/
void startGame()
{
  score = 0;
  actLives = defLives;
  startRound();
}

/** CHECK MATCH
*  Function to validate overlapping characters
*/
bool checkMatch(
    int x1,
    int y1,
    int x2,
    int y2)
{
  if (
      x1 == x2 &&
      y1 == y2)
  {
    return true;
  }
  else
  {
    return false;
  }
}

/** CHECK KILL
*  Function to validate if enemy has captured player
*/
void checkKill()
{
  if ( // Check new and old positions for intersects
      checkMatch(eX, eY, pX, pY) ||
      checkMatch(eX, eY, _pX, _pY))
  {
    screen.clear();
    if (actLives > 1)
    {             // Check for end-game
      showKill(); // Show kill
    }
    else
    {
      endGame(); // End game
    }
  }
}

/** CHECK GOAL
*  Function to validate if player has captured goal
*/
void checkGoal()
{
  if (
      checkMatch(gX, gY, _pX, _pY))
  {
    score++;
    startGoal();
  }
}

/** CHECK INTENT
*  Function to check for input
*  As this is syncronous, the pins must be
*   repeatedly read until a HIGH pin value
*   is read which breaks the loop in the
*   parent function
*/
void checkIntent()
{
  if ( // Moving right
      increaseY == HIGH &&
      increaseX == LOW &&
      decreaseX == HIGH)
  {
    increaseX = HIGH;
    playerIntent = 1;
  }
  else if ( // Moving left
      increaseY == HIGH &&
      increaseX == HIGH &&
      decreaseX == LOW)
  {
    decreaseX = HIGH;
    playerIntent = -1;
  }
  else if ( // Moving up/down
      increaseY == LOW &&
      increaseX == HIGH &&
      decreaseX == HIGH)
  {
    increaseY = HIGH;
    playerIntent = 2;
  }
  else
  { // Checking for input
    playerIntent = 0;
  }
}

/** SET INTENT
*  Function to give the enemy a basic 'chaser' personality
*/
void setIntent()
{
  enemyIntent = random(-1, 3);
  //   int randA = random(0, 2); // Random 0/1 value
  //   int randB;                // Declare int for scope
  //   if (randA == 0)
  //   {                       // 50% chance
  //     randB = random(0, 2); // Random 0/1 value
  //   }
  //   if (
  //       eY != pY && // Not on same row as player
  //       randB == 0  // 50% chance
  //   )
  //   {
  //     enemyIntent = 2 - randA; // Set intent to 2/1
  //   }
  //   else if (
  //       eY != pY && // Not on same row as player
  //       randB == 1  // 50% chance
  //   )
  //   {
  //     enemyIntent = 2 - randA * 3; // Set intent to 2/-1
  //   }
  //   else if (
  //       eX < pX // Left of player
  //   )
  //   {
  //     enemyIntent = 1 - randA; // Set intent to 1/0
  //   }
  //   else if (
  //       eX > pX // Right of player
  //   )
  //   {
  //     enemyIntent = -1 + randA; // Set intent to -1/0
  //   }
}

/** MOVE ON INTENT
*  Function to generate new coordinates based on intent
*/
void moveOnIntent(
    int intent,
    int x,
    int y,
    int _x,
    int _y)
{
  switch (intent)
  {
  case -1: // Moving left
    if (x > 0)
    { // Allow continuous wrap-around
      _x = x - 1;
    }
    else
    {
      _x = maxX - 1;
    }
    break;
  case 1: // Moving right
    if (x < maxX - 1)
    { // Allow continuous wrap-around
      _x = x + 1;
    }
    else
    {
      _x = 0;
    }
    break;
  case 2: // Moving up/down
    _y = abs(y - 1); // Allow continuous wrap-around
    break;
  default: // Should never be called
    break; // ...but break anyway
  }
}

/** WAIT ON INPUT
*  Function to poll the input pins for button presses
*/
void waitOnInput()
{
  while (playerIntent == 0)
  { // Checking for input loop
    increaseY = digitalRead(incY);
    increaseX = digitalRead(incX);
    decreaseX = digitalRead(decY);
    checkIntent();   // Re-evaluate check value
    delay(pollRate); // Small delay - stops button presses carrying over
  }
}

/** SHOW KILL
*  Function to show the end of the round
*/
void showKill()
{
  at(4, 0); // Print "You have died!"
  screen.print("YOU HAVE");
  at(6, 1);
  screen.print("DIED");

  actLives = actLives - 1; // Decrease lives remaining
  delay(1000);             // Hold text
  showLives();             // Update LEDs
  delay(1000);
  screen.clear();

  at(2, 0); // Print "You have X life/lives remaining!"
  screen.print("YOU HAVE ");
  at(12, 0);
  screen.print(actLives);
  at(2, 1);
  if (actLives != 1)
  { // Catch singular vs plural
    screen.print("LIVES LEFT!");
  }
  else
  {
    screen.print("LIFE LEFT!!");
  }

  delay(3000); // Hold screen
  screen.clear();

  startRound(); // Start new round
}

/** FILL LINE
*  Function to fill diplay line with characters
*/
void fillLine(int del)
{ // Cover the screen with enemy characters
  for (int i = 0; i < 16; i++)
  {
    screen.print(e);
    delay(del); // Adjustable delay between prints
  }
}

/** FILL SCREEN
*  Function to fill whole display with characters
*/
void fillScreen(int del, int sustain)
{
  at(0, 0); // Print enemy character over whole screen
  fillLine(del);
  at(maxX - 1, maxY - 1);
  screen.rightToLeft();
  fillLine(del);
  screen.leftToRight();
  delay(sustain); // Adjustable hold time
  screen.clear();
  delay(sustain);
}

/** END GAME
*  Function to show the end of the game
*/
void endGame()
{
  fillScreen(100, 500);
  for (int i = 0; i < 5; i++)
  {
    fillScreen(0, 250);
  }
  startGame(); // Start new round
}

/** MOVE PLAYER
*  Function to wait for input and appropriately assign new coordinates
*/
void movePlayer()
{
  waitOnInput();
  moveOnIntent(playerIntent, pX, pY, _pX, _pY);
}

/** MOVE ENEMY
*  Function to assign coordinates of the enemy character
*/
void moveEnemy()
{
  setIntent(); // Re-evaluate intent
  moveOnIntent(enemyIntent, pX, pY, _pX, _pY);
}

/** DRAW CHARACTER
*  Function to write a caracter to the screen
* 
*  @param x the x-coordinate
*  @param y the y coordinate
*  @param c the character to print
*/
void drawChar(int x, int y, char c)
{
  at(x, y);        // Move cursor
  screen.print(c); // Print character
}

/** DRAW CHARACTERS
*  Function to draw characters based on updated coordinates
*/
void drawCharacters()
{
  drawChar(pX, pY, ' '); // Clear player
  drawChar(eX, eY, ' '); // Clear enemy
  drawChar(_pX, _pY, p); // Print player
  drawChar(_eX, _eY, e); // Print enemy
  drawChar(gX, gY, g);   // Print goal
}

/** SETUP
*/
void setup()
{
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  pinMode(decY, INPUT_PULLUP);
  pinMode(incX, INPUT_PULLUP);
  pinMode(incY, INPUT_PULLUP);

  screen.begin(maxX, maxY); // Start screen
  startGame();
}

/** MAIN LOOP
*/
void loop()
{
  // checkKill();
  // checkGoal();
  startMove();
  movePlayer();
  // moveEnemy();
  drawCharacters();
}
