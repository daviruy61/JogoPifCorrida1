#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int main() {
    int running = 1;
    int x = 10, y = 10; // Posição inicial da mensagem
    int ch; // Armazena o último caractere lido

    // Inicialização das bibliotecas
    screenInit(1); // Inicializa a tela com bordas
    keyboardInit(); // Inicializa o teclado para leitura não bloqueante
    timerInit(100); // Configura o timer para 100 ms

    // Loop principal do jogo
    while (running) {
        screenClear(); // Limpa a tela
        screenGotoxy(x, y); // Move o cursor para a posição (x, y)
        printf("Hello"); // Imprime a mensagem
        screenUpdate(); // Atualiza a tela

        if (keyhit()) { // Verifica se uma tecla foi pressionada
            ch = readch(); // Lê a tecla pressionada
            switch (ch) {
                case 'q': // Sai do jogo
                    running = 0;
                    break;
                case 'w': // Move para cima
                    y = y > 1 ? y - 1 : y;
                    break;
                case 's': // Move para baixo
                    y = y < (MAXY - 1) ? y + 1 : y;
                    break;
                case 'a': // Move para a esquerda
                    x = x > 1 ? x - 1 : x;
                    break;
                case 'd': // Move para a direita
                    x = x < (MAXX - 1) ? x + 1 : x;
                    break;
            }
        }

        if (timerTimeOver()) { // Verifica se o tempo do timer expirou
            // Aqui você pode adicionar qualquer lógica que dependa do tempo
        }
    }

    // Limpeza e saída
    screenDestroy(); // Restaura as configurações de tela originais
    keyboardDestroy(); // Restaura as configurações de teclado originais
    timerDestroy(); // Desativa o timer

    return 0;
}
