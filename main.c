#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRACKS 3
#define TRACK_LENGTH 20

// Protótipos de funções
void initializeGame();
void runGame();
void movePlayer(int direction);
void updateObstacles();
void displayGame(int playerTrack);

int playerTrack = 1;  // Começa na pista do meio (0 = superior, 1 = meio, 2 = inferior)
char track[MAX_TRACKS][TRACK_LENGTH + 1];  // 3 pistas, cada uma com TRACK_LENGTH posições

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
    for (int i = 0; i < MAX_TRACKS; i++) {
        // Definindo a borda superior
        for (int j = 0; j < TRACK_LENGTH; j++) {
            track[i][j] = (j % 2 == 0) ? '=' : ' ';
        }
        track[i][TRACK_LENGTH] = '\0';  // Terminador de string
    }
    // Definindo as linhas internas
    for (int j = 0; j < TRACK_LENGTH; j++) {
        track[1][j] = (j % 2 == 0) ? '-' : ' ';  // Linha intermediária
    }
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
            } else if (key == 's' && playerTrack < MAX_TRACKS - 1) {
                movePlayer(1);
            }
        }

        if (timerTimeOver()) {
            updateObstacles();
        }

        screenUpdate();
        timerUpdateTimer(100);  // Reinicia o timer para 100ms
    } while (key != 'q');  // Pressione 'q' para sair
}

void movePlayer(int direction) {
    playerTrack += direction;
}

void updateObstacles() {
    for (int i = 0; i < MAX_TRACKS; i++) {
        memmove(&track[i][0], &track[i][1], TRACK_LENGTH - 1);  // Move tudo para a esquerda
        track[i][TRACK_LENGTH - 1] = (rand() % 10 < 2) ? '#' : track[i][TRACK_LENGTH - 2];  // Adiciona obstáculos aleatoriamente
    }
}

void displayGame(int playerTrack) {
    for (int i = 0; i < MAX_TRACKS; i++) {
        screenGotoxy(10, 5 + i * 2);  // Ajustado para ter espaço entre as pistas
        printf("%s", track[i]);
        fflush(stdout);  // Força a descarga do buffer após cada linha ser impressa
    }
    // Posiciona o jogador entre as linhas
    screenGotoxy(10, 6 + playerTrack * 2);
    printf(">");
    fflush(stdout);
}