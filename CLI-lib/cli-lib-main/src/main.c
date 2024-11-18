

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAX_ENEMIES 7
#define MAX_SHOTS 5
#define SHOT_INTERVAL 10 
#define esquerda 97
#define direita 100

int playerX = 34, playerY = 23;
int score = 0; 
int gameOver = 0;    
int shotCounter = 0;

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



void printMenu() {

    screenClear();  
    screenSetColor(LIGHTRED, DARKGRAY);
    screenGotoxy(25, 5);
    printf("C.E.S.A.R Cosmic Shield");

    screenGotoxy(25, 7);
    printf("1. Iniciar jogo");
    screenGotoxy(25, 8);
    printf("2. Como jogar");
    screenGotoxy(25, 9);
    printf("3. Sair");
    screenGotoxy(25, 12);
    printf("Escolha uma opção (1-3): ");
    screenUpdate();
}


void showInstructions() {
    screenClear();
    screenGotoxy(10, 5);
    printf("Instruções:");
    screenGotoxy(10, 6);
    printf("- Utilize A e D para se movimentar horizontalmente.");
    screenGotoxy(10, 7);
    printf("- Elimine todos os inimigos antes que eles te alcancem!");
    screenGotoxy(10, 8);
    printf("- Pressione ESC para sair do jogo.");
    screenGotoxy(10, 10);
    printf("Pressione qualquer tecla para voltar ao menu.");
    screenUpdate();
    while (!keyhit()) {}
}



void displayGameOverMessage(int win) {
    screenClear();
    screenGotoxy(25, 10);
    if (win) {
        printf("Vitória!");
    } else {
        printf("Fim de Jogo! Você Perdeu!");
    }
    screenGotoxy(25, 12);
    printf("Pontuação: %d pontos ", score);
    screenGotoxy(25, 14);
    printf("Pressione ESC para voltar ao menu.");
    screenUpdate();
    while (readch() != 27) { }
}

void initEnemies() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].x = 10 + i * 10;
        enemies[i].y = 5;
        enemies[i].active = 1;
        enemies[i].direction = 1;
    }
}

void initShots() {
    for (int i = 0; i < MAX_SHOTS; i++) {
        shots[i].active = 0;
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
        if (enemies[i].y >= playerY) {
            gameOver = 1;
            displayGameOverMessage(0);  
            return;
        }
    }
}

void displayShots() {
    screenSetColor(WHITE, DARKGRAY);
    for (int i = 0; i < MAX_SHOTS; i++) {
        if (shots[i].active) {
            screenGotoxy(shots[i].x, shots[i].y);
            printf("|");
        }
    }
}

void updateShots() {
    for (int i = 0; i < MAX_SHOTS; i++) {
        if (shots[i].active) {
            shots[i].y--;
            if (shots[i].y <= MINY) {
                shots[i].active = 0;
            }
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

void checkCollisions() {
    for (int i = 0; i < MAX_SHOTS; i++) {
        if (shots[i].active) {
            for (int j = 0; j < MAX_ENEMIES; j++) {
                if (enemies[j].active && shots[i].x == enemies[j].x && shots[i].y == enemies[j].y) {
                    enemies[j].active = 0;
                    shots[i].active = 0;
                    score += 100;  
                }
            }
        }
    }
}

int allEnemiesDefeated() {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].active) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char playerName[20];
    int ch = 0;
    int menuActive = 1; 
    screenInit(1);
    keyboardInit();
    timerInit(50);

    do {
        if (menuActive) {
            printMenu();  
            menuActive = 0;  
        }

        if (keyhit()) {
            ch = readch();
            if (ch == '1') {
                screenClear();               
                initEnemies();
                initShots();
                score = 0;
                gameOver = 0;

                

                while (!gameOver) {
                    if (keyhit()) {
                        ch = readch();
                        if (ch == esquerda && playerX > MINX + 1) {
                            playerX--;
                        } else if (ch == direita && playerX < MAXX - 1) {
                            playerX++;
                        }
                    }

                    if (shotCounter >= SHOT_INTERVAL) {
                        for (int i = 0; i < MAX_SHOTS; i++) {
                            if (!shots[i].active) {
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

                menuActive = 1; 
            } else if (ch == '2') {
                showInstructions();
                menuActive = 1;
            } else if (ch == '3') {
                break;
            }
        }
    } while (ch != '4');

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}
