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

#define ESQUERDA 97          // Código para A
#define DIREITA 100         // Código para D

int playerX = 34, playerY = 23;

//Função que exibe o jogador na tela, trocando a cor para verde e o player sera mostrado nos valores do x,y
void MostrarPlayer() {
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(playerX, playerY);
    printf("A");
}


int main() {
    int ch = 0;
    if(keyhit()){
        ch = readch();
            if (ch == ESQUERDA && playerX > MINX + 1) {
                playerX--;
                }
            else if (ch == DIREITA && playerX < MAXX - 1) {
                playerX++;
                }
        }
    

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
