#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "funcaoarquivo.h"

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