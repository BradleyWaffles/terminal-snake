#ifndef GAME_H
#define GAME_H

// Define directions
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };

void initGame(int difficulty);
void updateGame();
void renderGame();
void cleanupGame();
int isGameOver();
int getGameSpeed();
void endGameScreen();

#endif // GAME_H
