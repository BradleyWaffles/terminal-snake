#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "input.h"

int main(int argc, char *argv[]) {
    int difficulty = 0; // 0: easy, 1: medium, 2: hard

    // Parse command-line arguments for difficulty level
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-e") == 0) {
            difficulty = 0;
        } else if (strcmp(argv[i], "-m") == 0) {
            difficulty = 1;
        } else if (strcmp(argv[i], "-h") == 0) {
            difficulty = 2;
        }
    }

    initGame(difficulty);

    while (!isGameOver()) {
        processInput();
        updateGame();
        renderGame();
        usleep(getGameSpeed());
    }

    endGameScreen();
    cleanupGame();
    return 0;
}
