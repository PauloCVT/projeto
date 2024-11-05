/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int playerX = 34, playerY = 23;

void displayPlayer() {
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(playerX, playerY);
    printf("A");
    screenUpdate();
}

int main() {
    int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    while (1) {
        if (keyhit()) {
            ch = readch();
            if (ch == 'a' && playerX > MINX + 1) {
                playerX--;
            } else if (ch == 'd' && playerX < MAXX - 1) {
                playerX++;
            }
        }

        screenClear();
        displayPlayer();
        screenUpdate();
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}