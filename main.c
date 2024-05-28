#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define up 65
#define down 66
#define PISTAS 6
#define DISTANCIA_PISTA 165
#define MAX_JOGADORES 5
#define TAMANHO_NOME 100

// struct para placar
typedef struct {
    char nome[TAMANHO_NOME];
    int pontos;
} Jogador;

//funções
void displayMenu();
char getPlayerInput();
void changeCharacter();
void initializeGame();
void runGame();
void updateObstacles();
void displayGame(int playerLugar);
void lerPlacar(Jogador placar[]);
void salvarPlacar(Jogador placar[]);
void inserirNoPlacar(Jogador placar[], char nome[], int pontos);
void exibirPlacar();

//variaveis globais
int score = 0; //pontuação inicial
int probabilidadeobstaculo = 4; // probabilidade inicial de aparecer um obstaculo é 5
int incrementardificuldade = 0; // variavel pro score não bugar
int playerLugar = 2;  // Começa entre pista[2] e pista[3](meio)
char *simbolojogador = "🚓";  // carro
char **pista; //ponteiro de ponteiro para pistas // para aumentar/diminuir numero de pistas e tamanho mude o PISTAS e a quantidade de caracteres nos arrays pista
char obstacles[PISTAS][DISTANCIA_PISTA];  // Matriz separada para obstáculos


int main() {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    //alocaçao dinamica das pistas
    pista = (char **)malloc(PISTAS * sizeof(char *));
    for (int i = 0; i < PISTAS; i++) {
        pista[i] = (char *)malloc(DISTANCIA_PISTA * sizeof(char));
    }

    char escolhadousuario;
    do {
        displayMenu();
        escolhadousuario = getPlayerInput();

        switch (escolhadousuario) {
            case '1':
                initializeGame();
                runGame();
                break;
            case '2':
                changeCharacter();
                break;
            case '3':
                exibirPlacar();
                break;
        }
    } while (escolhadousuario != 'q');

    //liberar memoria da pista
    for (int i = 0; i < PISTAS; i++) {
        free(pista[i]);
    }
    free(pista);

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
    printf("3) Exibir placar");
    screenGotoxy(10, 11);
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
    } while (key != '1' && key != '2' && key != '3' && key != 'q');
    return key;
}


void changeCharacter() {
    screenClear();
    screenGotoxy(10, 5);
    printf("Escolha um personagem:");
    screenGotoxy(10, 7);
    printf("1) 🐎");
    screenGotoxy(10, 9);
    printf("2) ⏩");
    screenGotoxy(10, 11);
    printf("3) 🚓");
    screenUpdate();

    char key;
    do {
        while (!keyhit()) {
            usleep(100000); // Aguarda até uma tecla ser pressionada
        }
        key = readch();
        switch (key) {
            case '1':
                simbolojogador = "🐎";
                break;
            case '2':
                simbolojogador = "⏩";
                break;
            case '3':
                simbolojogador = "🚓";
                break;
        }
    } while (key != '1' && key != '2' && key != '3');
}


void initializeGame() {
    screenClear();
    // Inicializa as pistas
    strcpy(pista[0], "🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰");
    strcpy(pista[1], "➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖"); 
    strcpy(pista[2], "➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖"); 
    strcpy(pista[3], "➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖"); 
    strcpy(pista[4], "➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖");
    strcpy(pista[5], "🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰🟰");
    // Inicializa obstáculos
    memset(obstacles, ' ', sizeof(obstacles));  // Limpa a matriz de obstáculos
}


void runGame() {
    char key;
    char nomejogador[21];
    Jogador placar[MAX_JOGADORES]; // Array de jogadores para o placar

    lerPlacar(placar); // Carrega o placar existente do arquivo
    screenHideCursor();

    do {
        displayGame(playerLugar); // Exibe o jogo

        if (keyhit()) {
            key = readch();
            if ((key == 'w' || key == 'W' || key == up) && playerLugar > 0) {
                playerLugar--;
            } else if ((key == 's' || key == 'S' || key == down) && playerLugar < PISTAS - 2) {
                playerLugar++;
            }
        }
        if (score % 100 == 0 && score != 0 && score > incrementardificuldade) {
            probabilidadeobstaculo++;  // Aumenta a chance de geração de obstáculos em 1%
            incrementardificuldade = score;
        }

        if (timerTimeOver()) {
            updateObstacles();   // Atualiza os obstáculos
            score++;  // Incrementa a pontuação
            screenUpdate();
            timerUpdateTimer(100);  // Reinicia o temporizador para 100 milissegundos
        }

        // Verifica se há colisão entre o jogador e um obstáculo
        if (obstacles[playerLugar][0] == '#' || obstacles[playerLugar][0] == '@' || obstacles[playerLugar][0] == '%' || obstacles[playerLugar][0] == '&') {
            screenClear();
            printf("\nGame Over! Você colidiu com um obstáculo.\n");
            sleep(2);
            keyboardDestroy();
            screenShowCursor();
            printf("você fez %d pontos!", score);
            printf("\nDigite seu nome: ");
            scanf("%20s", nomejogador);

            // Insere o jogador no placar se for elegível
            inserirNoPlacar(placar, nomejogador, score);
            salvarPlacar(placar); // Salva o placar atualizado no arquivo

            printf("Placar atualizado.\n");
            sleep(2); // Mostra a mensagem por 2 segundos

            score = 0;
            probabilidadeobstaculo = 4;
            break; // Sai do loop do jogo
        }

        screenUpdate();
    } while (key != 'q');

    // Reseta o jogo
    score = 0;
    probabilidadeobstaculo = 4;
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


void displayGame(int playerLugar) {
    int linhabasepista = 3; // linha das pistas
    int linhabaserua = 4; //linha do jogador e dos obstaculos
    int espacamento = 2; // espaçamento
    
    // Desenha as pistas
    for (int i = 0; i < PISTAS; i++) {
        screenGotoxy(12, linhabasepista + i * espacamento);
        printf("%s", pista[i]);
    }

    // Atualiza os obstáculos
    for (int i = 0; i < PISTAS; i++) {
        for (int j = 0; j < DISTANCIA_PISTA; j++) {
            screenGotoxy(13 + j, linhabaserua + i * espacamento); // Posiciona os obstáculos na tela
            printf("%c", obstacles[i][j]);  // Desenha o obstáculo
        }
    }

    // Desenha o jogador na nova posição
    screenGotoxy(13, linhabaserua + playerLugar * espacamento);
    printf("%s", simbolojogador);

    // Atualiza a tela
    screenUpdate();

    //score
    screenGotoxy(12, linhabasepista + PISTAS * espacamento + 2);  // Posição abaixo das pistas
    printf("Score: %d", score);  // Exibe a pontuação
}


void lerPlacar(Jogador placar[]) {
    FILE *arquivo = fopen("placar.txt", "r");
    if (arquivo == NULL) {
        for (int i = 0; i < MAX_JOGADORES; i++) {
            sprintf(placar[i].nome, "-");
            placar[i].pontos = 0;
        }
    } else {
        for (int i = 0; i < MAX_JOGADORES; i++) {
            fscanf(arquivo, "%*d - %99s %d", placar[i].nome, &placar[i].pontos);
            if (placar[i].pontos == 0) strcpy(placar[i].nome, "-");
        }
        fclose(arquivo);
    }
}


void salvarPlacar(Jogador placar[]) {
    FILE *arquivo = fopen("placar.txt", "w");
    for (int i = 0; i < MAX_JOGADORES; i++) {
        fprintf(arquivo, "%d - %s %d\n", i + 1, placar[i].nome, placar[i].pontos);
    }
    fclose(arquivo);
}


void inserirNoPlacar(Jogador placar[], char nome[], int pontos) {
    int posicao = MAX_JOGADORES;
    for (int i = MAX_JOGADORES - 1; i >= 0; i--) {
        if (pontos > placar[i].pontos) {
            posicao = i;
        } else {
            break;
        }
    }

    if (posicao < MAX_JOGADORES) {
        for (int i = MAX_JOGADORES - 1; i > posicao; i--) {
            strcpy(placar[i].nome, placar[i - 1].nome);
            placar[i].pontos = placar[i - 1].pontos;
        }
        strcpy(placar[posicao].nome, nome);
        placar[posicao].pontos = pontos;
    }
}


void exibirPlacar() {
    Jogador placar[MAX_JOGADORES];
    lerPlacar(placar); // Carrega o placar do arquivo

    screenClear(); // Limpa a tela antes de exibir o placar
    screenGotoxy(10, 3);
    printf("Placar Atual:");
    screenGotoxy(10, 5);

    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (placar[i].pontos != 0) { // Mostra apenas entradas válidas
            screenGotoxy(10, 6 + i);
            printf("%d - %s: %d pontos\n", i + 1, placar[i].nome, placar[i].pontos);
        }
    }

    screenGotoxy(10, 12);
    printf("Pressione qualquer tecla para voltar ao menu...");
    screenUpdate(); // Atualiza a tela

    // Aguarda o usuário pressionar qualquer tecla antes de retornar ao menu
    while (!keyhit()) {
        usleep(100000);
    }
    readch(); // Lê a tecla para limpar o buffer de entrada
}
