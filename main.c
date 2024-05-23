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
void waitSeconds(int seconds);
void clearKeyboardBuffer();
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

    int currentSelection = 1;
    const int maxOptions = 3;

    do {
        screenClear();
        screenGotoxy(10, 5);
        printf("Escolha uma opção:\n");
        for (int i = 1; i <= maxOptions; i++) {
            if (currentSelection == i) {
                screenGotoxy(9, 5 + i);
                printf(">");
            }
            screenGotoxy(10, 5 + i);
            if (i == 1) printf("Iniciar Jogo\n");
            else if (i == 2) printf("Exibir Ranking\n");
            else if (i == 3) printf("Sair\n");
        }
        screenUpdate();

        clearKeyboardBuffer();  // Limpa o buffer antes de ler a nova entrada
        char key = '\0';
        while (!keyhit()) {  // Espera por uma tecla de forma ativa
            // Loop vazio até que uma tecla seja pressionada
        }
        key = readch();

        // Navegação no menu
        if (key == 'w' && currentSelection > 1) currentSelection--;
        else if (key == 's' && currentSelection < maxOptions) currentSelection++;
        else if (key == '\n') {  // Enter para selecionar a opção
            switch (currentSelection) {
                case 1:
                    iniciarJogo();
                    break;
                case 2:
                    exibirRanking();
                    break;
                case 3:
                    goto endProgram;  // Sair do programa
            }
        }
    } while (TRUE);

endProgram:
    screenDestroy();
    keyboardDestroy();
    timerDestroy();
    return 0;
}


void waitSeconds(int seconds) {
    timerInit(seconds * 1000);  // Inicia um timer para o número total de milissegundos
    while (!timerTimeOver()) {
        // Aguarda o timer expirar
    }
}

void clearKeyboardBuffer() {
    while (keyhit()) {
        readch();  // Limpa todos os caracteres pendentes
    }
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