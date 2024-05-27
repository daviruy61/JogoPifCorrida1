#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PISTAS 6
#define DISTANCIA_PISTA 60

void initializeGame();
void runGame();
void movePlayer(int direction);
void updateObstacles();
void displayGame(int playerTrack);
void displayMenu();
void changeCharacter();
char getPlayerInput();

int score = 0; //pontuação inicial
int probabilidadeobstaculo = 6; // probabilidade inicial de aparecer um obstaculo é 6
int incrementardificuldade = 0; // variavel pro score não bugar
int playerTrack = 2;  // Começa entre track[2] e track[3](meio)
char simbolojogador = '>';  // carro
char track[PISTAS][DISTANCIA_PISTA];  // para aumentar/diminuir numero de pistas e tamanho mude o PISTAS e a quantidade de caracteres nos arrays track
char obstacles[PISTAS][DISTANCIA_PISTA];  // Matriz separada para obstáculos

int main() {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    char choice;
    do {
        displayMenu();
        choice = getPlayerInput();

        switch (choice) {
            case '1':
                initializeGame();
                runGame();
                break;
            case '2':
                changeCharacter();
                break;
        }
    } while (choice != 'q');

    screenDestroy();
    keyboardDestroy();
    timerDestroy();

    return 0;
}

void displayMenu() {
    screenClear();
    screenGotoxy(10, 5);
    printf("1) Iniciar Jogo");
    screenGotoxy(10, 7);
    printf("2) Trocar de Personagem");
    screenGotoxy(10, 9);
    printf("Pressione 'q' para sair");
    screenUpdate();
}

char getPlayerInput() {
    char key;
    do {
        while (!keyhit()) {
            usleep(100000); // Aguarda até uma tecla ser pressionada
        }
        key = readch();
    } while (key != '1' && key != '2' && key != 'q');
    return key;
}

void changeCharacter() {
    screenClear();
    screenGotoxy(10, 5);
    printf("Escolha um personagem:");
    screenGotoxy(10, 7);
    printf("1) B");
    screenGotoxy(10, 9);
    printf("2) 3");
    screenGotoxy(10, 11);
    printf("3) >");
    screenUpdate();

    char key;
    do {
        while (!keyhit()) {
            usleep(100000); // Aguarda até uma tecla ser pressionada
        }
        key = readch();
        switch (key) {
            case '1':
                simbolojogador = 'B';
                break;
            case '2':
                simbolojogador = '3';
                break;
            case '3':
                simbolojogador = '>';
                break;
        }
    } while (key != '1' && key != '2' && key != '3');
}

void initializeGame() {
    // Inicializa as pistas
    strcpy(track[0], "=========================================");
    strcpy(track[1], "-----------------------------------------"); 
    strcpy(track[2], "-----------------------------------------"); 
    strcpy(track[3], "-----------------------------------------"); 
    strcpy(track[4], "-----------------------------------------");
    strcpy(track[5], "=========================================");
    // Inicializa obstáculos
    memset(obstacles, ' ', sizeof(obstacles));  // Limpa a matriz de obstáculos
}

void runGame() {
    char key;
    int colisao = 0; // Define se houve colisão ou não
    do {
        screenClear();
        displayGame(playerTrack); //Exibe o jogo

        if (keyhit()) {
            key = readch();
            if ((key == 'w' || key == 'W') && playerTrack > 0) {
                movePlayer(-1);
            } else if ((key == 's' || key == 'S') && playerTrack < PISTAS - 2) {
                movePlayer(1);
            }
        }
        if (score % 100 == 0 && score != 0 && score > incrementardificuldade) {
            probabilidadeobstaculo++;  // Aumenta a chance de geração de obstáculos em 1%
            incrementardificuldade = score;
        }

        if (timerTimeOver()) {
            updateObstacles();   //Atualiza os obstáculos (ignorado por agora)
            score++;  // Incrementa a pontuação
            screenUpdate();
            timerUpdateTimer(100);  // Reinicia o temporizador para 100 milissegundos
        }
        // Verifica se há colisão entre o jogador e um obstáculo
        if (obstacles[playerTrack][0] == '#' || obstacles[playerTrack][0] == '@' || obstacles[playerTrack][0] == '%' || obstacles[playerTrack][0] == '&') {  // Verificar se a posição do jogador é igual ao de um obstaculo
            colisao = 1;  // Marca o jogo como terminado
            printf("\nGame Over! Você colidiu com um obstáculo.\n");
            score = 0;
            probabilidadeobstaculo = 6;
            break;  // Sai do loop do jogo
        }

        screenUpdate();
    } while (key != 'q');
      score = 0;
      probabilidadeobstaculo = 6;
}



void movePlayer(int direction) {
    playerTrack += direction;  // Ajuste para que o jogador se mova apenas entre as linhas
}

void updateObstacles() {
    int linhabase = 4;
    int espaçamentoobstaculo = 2;
    int posicaoinicial = 39; // Posição dentro da matriz de obstáculos que reflete screenGotoxy(50, ...)
    // Mover obstáculos para a esquerda
    for (int i = 0; i < PISTAS - 1; i++) {
        for (int j = 1; j < DISTANCIA_PISTA; j++) {
            obstacles[i][j-1] = obstacles[i][j];
            obstacles[i][j] = ' ';
        }
    }

    // Gerar novos obstáculos aleatoriamente na última coluna com diferentes tipos
    char obstaculos[] = {'#', '@', '%', '&'};
    for (int i = 0; i < PISTAS - 1; i++) {
        if (rand() % 100 < probabilidadeobstaculo) {
            int randobstaculo = rand() % 4; // Gera um número entre 0 e 3 para escolher o obstáculo
            obstacles[i][posicaoinicial] = obstaculos[randobstaculo];
        }
    }
}




void displayGame(int playerTrack) {
    int linhabasepista = 3; // linha das pistas
    int linhabaserua = 4; //linha do jogador e dos obstaculos
    int espacamento = 2; // espaçamento
    for (int i = 0; i < PISTAS; i++) {
        screenGotoxy(12, linhabasepista + i * espacamento); //gotoxy x=colunas e y=linhas
        for (int j = 0; j < DISTANCIA_PISTA ; j++) {
            char currentObstacle = obstacles[i][j];
            if (currentObstacle == '#' || currentObstacle == '@' || currentObstacle == '%' || currentObstacle == '&') {
                screenGotoxy(13 + j, linhabaserua + i * espacamento); // Posiciona os obstaculos na tela
                printf("%c", currentObstacle);
            }
        }
        
        screenGotoxy(12, linhabasepista + i * espacamento); // imprimir as pistas
        printf("%s", track[i]);
    }

    screenGotoxy(12, linhabasepista + PISTAS * espacamento + 2);  // Posição abaixo das pistas
    printf("Score: %d", score);  // Exibe a pontuação
    //printf (" dificuldade: %d", probabilidadeobstaculo); // teste
    
    // Posiciona o jogador entre as linhas, não diretamente sobre elas
    screenGotoxy(13, linhabaserua + playerTrack * espacamento);
    printf("%c", simbolojogador);
}