/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAX_ENEMIES 5
#define direita 100
#define esquerda 97
#define MAX_SHOTS 5
#define SHOT_INTERVAL 10

int playerX = 34, playerY = 23; 
int score = 0;
int gameOver = 0;

typedef struct {
    int x, y;
    int active;
    int direction; 
} Enemy;

typedef struct {
    int x, y;
    int active;
} Shot;

Enemy enemies[MAX_ENEMIES];
Shot shots[MAX_SHOTS];

int shotCounter = 0;

void GameOverMensagem(int vitoria) {
    screenClear();
    screenGotoxy(25, 10);
    if (vitoria) {
        printf("Voce Venceu!");
    } else {
        printf("Game Over! Voce perdeu!");
    }
    
}

void initEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].x = 10 + i * 10;
        enemies[i].y = 5;
        enemies[i].active = 1;
        enemies[i].direction = 1; 
    }
}

void displayPlayer() {
    screenSetColor(GREEN, DARKGRAY);
    screenGotoxy(playerX, playerY);
    printf("A"); 
}

void displayEnemies() {
    screenSetColor(RED, DARKGRAY);
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            screenGotoxy(enemies[i].x, enemies[i].y);
            printf("W");
        }
        if(enemies[i].y >= playerY){
            gameOver = 1;
            GameOverMensagem(0);
            return;
        }
    }
}

void updateEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            enemies[i].x += enemies[i].direction;

            if (enemies[i].x >= MAXX - 1 || enemies[i].x <= MINX + 1) {
                enemies[i].direction = -enemies[i].direction; 
                enemies[i].y++; 
            }
        }
    }
}

void initShots(){
    for(int i = 0; i < MAX_SHOTS; i++){
        shots[i].active = 0;
    }
}
void displayShots(){
    screenSetColor(WHITE, DARKGRAY);
    for(int i = 0; i < MAX_SHOTS; i++){
        if (shots[i].active){
            screenGotoxy(shots[i].x, shots[i].y);
            printf("|");
        }
    }
}

void updateShots(){
    for(int i = 0; i < MAX_SHOTS; i++){
        if(shots[i].active){
            shots[i].y--;
            if(shots[i].y <= MINY){
                shots[i].active = 0;
            }
        }
    }
}

int main() {   
    int ch = 0;
    gameOver = 0;

    screenInit(1);
    keyboardInit();
    timerInit(50);
    initEnemies();
    displayPlayer();
    displayEnemies();
    initShots();
    displayShots();
    updateShots();
    screenUpdate();

    while (!gameOver) {
        if (keyhit()) {
            ch = readch();
            if (ch == esquerda && playerX > MINX + 1) {
                playerX--; 
            } else if (ch == direita && playerX < MAXX - 1) {
                playerX++; 
            }
        }
        
        if (shotCounter >= SHOT_INTERVAL){
            for(int i = 0; i < MAX_SHOTS; i++){
                if(!shots[i].active){
                    shots[i].x = playerX;
                    shots[i].y = playerY - 1;
                    shots[i].active = 1;
                    break;
                }
            }
            shotCounter = 0;
        }
        shotCounter++;

        if (timerTimeOver() == 1) {
                        updateShots();
                        updateEnemies();
                        checkCollisions();

                        screenClear();
                        displayPlayer();
                        displayEnemies();
                        displayShots();
                        screenGotoxy(2, 2);
                        printf("Pontuação: %d ", score);
                        screenUpdate();

                        if (allEnemiesDefeated()) {
                            gameOver = 1;
                            
                            displayGameOverMessage(1);  
                            
                        }
                    }
                }

   
    keyboardDestroy();
    screenDestroy();

    return 0;
}
