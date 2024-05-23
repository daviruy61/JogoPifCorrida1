#include "screen.h"
#include "keyboard.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int Boolean;
typedef char Info;

struct node {
    Info info;
    struct node* prox;
};

typedef struct node Node;
typedef struct node* Lista;

// Protótipos de funções
void lst_init(Lista* refLista);
Boolean lst_addLast(Lista* refLista, Info dado);
void lst_removeFirst(Lista* refLista);
Boolean lst_isEmpty(Lista lista);
void iniciarJogo();
void exibirRanking();
void imprimirPista(Lista faixa1, Lista faixa2, Lista faixa3, int pont);
void caminhar(Lista faixa);

int main() {
    screenInit(1);
    keyboardInit();
    timerInit(100);

    int choice;
    do {
        screenClear();
        screenGotoxy(10, 5);
        printf("1 - Iniciar Jogo\n2 - Exibir Ranking\n0 - Sair\n");
        screenUpdate();

        // Espera por uma tecla de forma ativa
        while (!keyhit()) {
            // Apenas loop até que uma tecla seja pressionada.
            // Aqui você poderia opcionalmente adicionar um timer para atualizar a tela ou outra lógica não bloqueante
        }
        choice = readch() - '0'; // Lê a escolha do usuário e converte para int

        switch (choice) {
            case 1:
                iniciarJogo();
                break;
            case 2:
                exibirRanking();
                break;
            case 0:
                break;
        }
    } while (choice != 0);

    screenDestroy();
    keyboardDestroy();
    timerDestroy();
    return 0;
}

void lst_init(Lista* refLista) {
    *refLista = NULL;
}

Boolean lst_addLast(Lista* refLista, Info dado) {
    Node* novo = malloc(sizeof(Node));
    if (novo == NULL) {
        return FALSE;
    }
    novo->info = dado;
    novo->prox = NULL;

    if (*refLista == NULL) {
        *refLista = novo;
    } else {
        Node* temp = *refLista;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
    return TRUE;
}

void lst_removeFirst(Lista* refLista) {
    if (*refLista != NULL) {
        Node* temp = *refLista;
        *refLista = (*refLista)->prox;
        free(temp);
    }
}

Boolean lst_isEmpty(Lista lista) {
    return (lista == NULL) ? TRUE : FALSE;
}

void iniciarJogo() {
    Lista pista1 = NULL, pista2 = NULL, pista3 = NULL;
    lst_init(&pista1);
    lst_init(&pista2);
    lst_init(&pista3);

    // Adicione mais lógica de jogo aqui

    while (!lst_isEmpty(pista1)) { // Exemplo de condição de loop
        imprimirPista(pista1, pista2, pista3, 0);
        lst_removeFirst(&pista1); // Simulando movimento
    }
}

void exibirRanking() {
    printf("Ranking não implementado ainda.\n");
}

void imprimirPista(Lista faixa1, Lista faixa2, Lista faixa3, int pont) {
    caminhar(faixa1);
    caminhar(faixa2);
    caminhar(faixa3);
    printf("Pontuação: %d\n", pont);
}

void caminhar(Lista faixa) {
    while (faixa != NULL) {
        printf("%c", faixa->info);
        faixa = faixa->prox;
    }
    printf("\n");
}
