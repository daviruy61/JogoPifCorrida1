#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int x = 34, y = 12; // Posições iniciais do texto na tela.
int incX = 1, incY = 1; // Incrementos para mover o texto.

void printHello(int nextX, int nextY); // Função para imprimir "Hello World" na nova posição.
{
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("           ");
    x = nextX;
    y = nextY;
    screenGotoxy(x, y);
    printf("Hello World");
}

void printKey(int ch)  // Função para exibir o código da tecla pressionada.
{
    screenSetColor(YELLOW, DARKGRAY);
    screenGotoxy(35, 22);
    printf("Key code :");

    screenGotoxy(34, 23);
    printf("            ");
    
    if (ch == 27) screenGotoxy(36, 23);
    else screenGotoxy(39, 23);

    printf("%d ", ch);
    while (keyhit())
    {
        printf("%d ", readch());
    }
}

int main() {
    static int ch = 0;

    // Inicialização de módulos
    screenInit(1); // Inicializa a tela e desenha bordas.
    keyboardInit(); // Configura o teclado para entrada não-canônica.
    timerInit(50); // Configura o timer para atualizar a cada 50ms.

    printHello(x, y); // Exibe "Hello World" na posição inicial.
    screenUpdate(); // Atualiza a tela para refletir as mudanças.

    // Loop principal
    while (ch != 10) { // Continua até que 'Enter' (código 10) seja pressionado.
        // Handle user input
        if (keyhit()) { // Verifica se uma tecla foi pressionada.
            ch = readch(); // Lê o código da tecla pressionada.
            printKey(ch); // Exibe o código da tecla.
            screenUpdate(); // Atualiza a tela.
        }

        // Update game state (move elements, verify collision, etc)
        if (timerTimeOver() == 1) { // Verifica se o timer expirou.
            int newX = x + incX; // Calcula a nova posição X.
            int newY = y + incY; // Calcula a nova posição Y.

            // Verifica colisão com as bordas da tela e inverte a direção se necessário.
            if (newX >= (MAXX - strlen("Hello World") - 1) || newX <= MINX+1) incX = -incX;
            if (newY >= MAXY-1 || newY <= MINY+1) incY = -incY;

            printHello(newX, newY); // Move "Hello World" para a nova posição.
            screenUpdate(); // Atualiza a tela.
        }
    }

    // Finalização
    keyboardDestroy(); // Restaura configurações do teclado.
    screenDestroy(); // Limpa e restaura a tela.
    timerDestroy(); // Desativa o timer.

    return 0; // Termina o programa.
}
