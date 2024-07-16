#include <ncurses.h>
#include "input.h"
#include "game.h"

extern enum eDirection dir;

void processInput() {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            if (dir != RIGHT) dir = LEFT;
            break;
        case KEY_RIGHT:
            if (dir != LEFT) dir = RIGHT;
            break;
        case KEY_UP:
            if (dir != DOWN) dir = UP;
            break;
        case KEY_DOWN:
            if (dir != UP) dir = DOWN;
            break;
        case 'q':
            dir = STOP;
            break;
    }
}
