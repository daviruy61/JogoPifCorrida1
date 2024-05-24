#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRACKS 4
#define TRACK_LENGTH 20

void initializeGame();
void runGame();
void movePlayer(int direction);
void updateObstacles();
void displayGame(int playerTrack);

int playerTrack = 1;  // Começa entre track[0] e track[1]
char track[MAX_TRACKS][TRACK_LENGTH + 1];  // 4 pistas

int main() {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    initializeGame();
    runGame();

    screenDestroy();
    keyboardDestroy();
    timerDestroy();

    return 0;
}

void initializeGame() {
    strcpy(track[0], "===================="); // Linha superior
    strcpy(track[1], "--------------------"); // Primeira linha interna
    strcpy(track[2], "--------------------"); // Segunda linha interna
    strcpy(track[3], "===================="); // Linha inferior
}

void runGame() {
    char key;
    do {
        screenClear();
        displayGame(playerTrack);

        if (keyhit()) {
            key = readch();
            if (key == 'w' && playerTrack > 0) {
                movePlayer(-1);
            } else if (key == 's' && playerTrack < 2) {
                movePlayer(1);
            }
        }

        if (timerTimeOver()) {
            updateObstacles();
        }

        screenUpdate();
        timerUpdateTimer(100);
    } while (key != 'q');
}

void movePlayer(int direction) {
    playerTrack += direction;  // Ajuste para que o jogador se mova apenas entre as linhas
}

void updateObstacles() {
    for (int i = 0; i < MAX_TRACKS; i++) {
        memmove(&track[i][0], &track[i][1], TRACK_LENGTH - 1);
        track[i][TRACK_LENGTH - 1] = (rand() % 10 < 2) ? '#' : track[i][TRACK_LENGTH - 2];
    }
}

void displayGame(int playerTrack) {
    int baseLine = 5; // Base line for display
    int lineSpacing = 2; // Line spacing for better visibility
    for (int i = 0; i < MAX_TRACKS; i++) {
        screenGotoxy(10, baseLine + i * lineSpacing); //gotoxy x=colunas e y=linhas
        printf("%s", track[i]);
        fflush(stdout);
    }
    // Posiciona o jogador entre as linhas, não diretamente sobre elas
    screenGotoxy(10, baseLine + (playerTrack * lineSpacing) + 1);
    printf(">");
    fflush(stdout);
}

