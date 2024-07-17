#include <ncurses.h>
#include <stdlib.h>
#include "game.h"

int gameOver;
int width, height;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
int gameSpeed;
enum eDirection dir;
int difficulty;

void initGame(int diff) {
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // so game runs constantly without waiting for user input

    width = 30;
    height = 15;
    gameOver = 0;
    dir = RIGHT;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    difficulty = diff;

    if (difficulty == 0) {
        gameSpeed = 200000; // Easy (50% slower than original 100ms)
    } else if (difficulty == 1) {
        gameSpeed = 200000; // Medium
    } else if (difficulty == 2) {
        gameSpeed = 200000; // Hard
    }
}

void updateGame() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
        default: break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height) {
        gameOver = 1;
    }

    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = 1;
        }
    }

    if (x == fruitX && y == fruitY) {
        score += 10;
        nTail++;
        fruitX = rand() % width;
        fruitY = rand() % height;

        // Increase game speed if the difficulty is medium or hard - default is easy
        if (difficulty == 1) {
            gameSpeed -= 5000; // Medium: Speed up a little
        } else if (difficulty == 2) {
            gameSpeed -= 10000; // Hard: Speed up more
        }

        if (gameSpeed < 50000) { // Limit the minimum game speed - this should be tweaked to make the game more smooth
            gameSpeed = 50000;
        }
    }
}

void renderGame() {
    clear();
    mvprintw(0, 0, "Snake Game - Press 'q' to quit | Difficulty: %s", difficulty == 0 ? "Easy" : (difficulty == 1 ? "Medium" : "Hard"));
    for (int i = 0; i < width + 2; i++)
        mvprintw(1, i, "#");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                mvprintw(i + 2, j, "#");
            if (i == y && j == x)
                mvprintw(i + 2, j, "O");
            else if (i == fruitY && j == fruitX)
                mvprintw(i + 2, j, "@"); // '@' is the fruit!
            else {
                int print = 0;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        mvprintw(i + 2, j, "o");
                        print = 1;
                    }
                }
                if (!print)
                    mvprintw(i + 2, j, " ");
            }
            if (j == width - 1)
                mvprintw(i + 2, j + 1, "#");
        }
    }
    for (int i = 0; i < width + 2; i++)
        mvprintw(height + 2, i, "#");

    mvprintw(height + 4, 0, "Score: %d", score);
    refresh();
}

void endGameScreen() {
    clear();
    mvprintw(height / 2, (width / 2) - 5, "Game Over");
    mvprintw((height / 2) + 1, (width / 2) - 10, "Final Score: %d", score);
    mvprintw((height / 2) + 2, (width / 2) - 15, "Press any key to exit...");
    refresh();
    nodelay(stdscr, FALSE); // Wait for user input
    getch();
}

void cleanupGame() {
    endwin();
}

int isGameOver() {
    return gameOver;
}

int getGameSpeed() {
    return gameSpeed;
}
