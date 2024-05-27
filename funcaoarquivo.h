#ifndef __FUNCAOARQUIVO_H__
#define __FUNCAOARQUIVO_H__

#define MAX_JOGADORES 5
#define TAMANHO_NOME 100

typedef struct {
    char nome[TAMANHO_NOME];
    int pontos;
} Jogador;

void lerPlacar(Jogador placar[]);
void salvarPlacar(Jogador placar[]);
void inserirNoPlacar(Jogador placar[], char nome[], int pontos);

#endif /* __FUNCAOARQUIVO_H__ */