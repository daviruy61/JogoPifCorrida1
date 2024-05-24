# JOGO DE CORRIDA 2D - PIF

**PASSO A PASSO PARA JOGAR O JOGO DE CORRIDA 2D**

Primeiro é necessário verificar que as bibliotecas e o arquivo main.c que estão presentes no GitHub estão no mesmo arquivo diretório da sua máquina e rodar a seguinte linha de comando:
```
**gcc -o corrida main.c keyboard.c screen.c timer.c**
```
Logo em seguida, digitar essa segunda linha:
```
**./corrida**
```

- INICIANDO O JOGO

1. A Corrida 2D abrirá um painel em que é possível selecionar 3 opções: 1-Iniciar, 2-Ranking e 3-Sair.

2. Se "1-Iniciar" for selecionado, o jogo limpará a tela e mostrará as 5 pistas pelas quais o carro pode transitar.

3. A função do jogador é esquivar-se dos obstáculos na pista pressionando as teclas "W" para mover o carro para cima e "S" para baixo.

4. Enquanto o jogador desvia dos obstáculos, irá acumular "PONTOS".

5. Quando o carro bater em algum obstáculo, o jogo parará imediatamente e exibirá na tela uma mensagem de "GAME OVER" e a sua pontuação, logo depois pedirá para você inserir um nome.

6. Esse nome inserido será armazenado junto com a pontuação dos jogadores.

7. Caso os participantes queiram ver suas colocações, basta ir ao "MENU INICIAL" e selecionar a segunda opção.
- Na segunda opção, estarão os nomes de todos os participantes e suas pontuações por ranking.

8. Para encerrar o Corrida 2D, é necessário que o jogador digite "3" no "MENU INICIAL", e o jogo se fechará automaticamente.
