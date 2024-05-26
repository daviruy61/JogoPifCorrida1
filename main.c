#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PISTAS 6
#define DISTANCIA_PISTA 40

void initializeGame();
void runGame();
void movePlayer(int direction);
void updateObstacles();
void displayGame(int playerTrack);

int score = 0; //pontuação inicial
int playerTrack = 2;  // Começa entre track[2] e track[3](meio)
char track[PISTAS][DISTANCIA_PISTA + 1];  // para aumentar/diminuir numero de pistas e tamanho mude o PISTAS e a quantidade de caracteres nos arrays track

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
    strcpy(track[0], "========================================"); // pistas
    strcpy(track[1], "----------------------------------------"); 
    strcpy(track[2], "----------------------------------------"); 
    strcpy(track[3], "----------------------------------------"); 
    strcpy(track[4], "----------------------------------------");
    strcpy(track[5], "========================================");
}

void runGame() {
    char key;
    do {
        screenClear();
        displayGame(playerTrack); //exibe o jogo

        if (keyhit()) {
            key = readch();
            if ((key == 'w' || key == 'W') && playerTrack > 0) {
                movePlayer(-1);
            } else if ((key == 's' || key == 'S') && playerTrack < PISTAS - 2) {
                movePlayer(1);
            }
        }

        if (timerTimeOver()) {
            updateObstacles();   //Atualiza os obstáculos (ignorado por agora)
            score++;  // Incrementa a pontuação
            timerUpdateTimer(100);  // Reinicia o temporizador para 100 milissegundos
        }

        screenUpdate();
    } while (key != 'q');
}



void movePlayer(int direction) {
    playerTrack += direction;  // Ajuste para que o jogador se mova apenas entre as linhas
}

void updateObstacles() {
    for (int i = 1; i < PISTAS - 1; i++) { // Ainda evita a primeira e última linha de borda
        memmove(&track[i][0], &track[i][1], DISTANCIA_PISTA - 1);
        // Não mais gerando obstáculos aqui, mantendo o foco em outras lógicas de atualização
    }
}



void displayGame(int playerTrack) {
    int baseLine = 3; // Base line for display
    int lineSpacing = 2; // Line spacing for better visibility
    for (int i = 0; i < PISTAS; i++) {
        screenGotoxy(12, baseLine + i * lineSpacing); //gotoxy x=colunas e y=linhas
        printf("%s", track[i]);
        fflush(stdout);
    }
    
    // Gera obstáculos
    for (int i = 0; i < PISTAS - 1; i++) { // Subtrai 1 para evitar a última linha
        if (rand() % 10 < 2) { // Aproximadamente 20% de chance de um obstáculo aparecer
            screenGotoxy(12 + DISTANCIA_PISTA - 2, (baseLine + i * lineSpacing) + 1);
            printf("#");
        }
    }

    screenGotoxy(12, baseLine + PISTAS * lineSpacing + 2);  // Posição abaixo das pistas
    printf("Score: %d", score);  // Exibe a pontuação
    fflush(stdout);
    
    // Posiciona o jogador entre as linhas, não diretamente sobre elas
    screenGotoxy(12, baseLine + (playerTrack * lineSpacing) + 1 );
    printf(">");
    fflush(stdout);
}