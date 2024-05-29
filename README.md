# JOGO DE CORRIDA 2D - PIF

## PASSO A PASSO PARA JOGAR O JOGO DE CORRIDA MAKEFILE


Para executar o Corrida virtual 2D, siga estas etapas:

1. Clone este repositório em sua máquina:
   ```
   git clone https://github.com/daviruy61/JogoPifCorrida1.git
   ```
3. Compile o programa:
   ```
   gcc -o corrida main.c keyboard.c screen.c timer.c
   ```
5. Rode o programa:
   ```
   ./corrida
   ```
## INICIANDO O JOGO

1. A Corrida 2D abrirá um painel em que o jogador poderá navegar por 4 opções: Iniciar, Placar, Escolha de personagem ou Sair.

2. Se "Iniciar" for selecionado, o jogo limpará a tela e mostrará as 5 pistas pelas quais o carro pode transitar.

3. A função do jogador é esquivar-se dos obstáculos na pista pressionando as teclas "W" ou "UP" para mover o carro para cima e "S" ou "DOWN" para baixo.

4. Enquanto o jogador desvia dos obstáculos, irá acumular pontos.

5. Quando o carro bater em algum obstáculo, o jogo parará imediatamente e exibirá na tela uma mensagem:
Game Over! Você colidiu com um obstáculo. 
Você fez X pontos! 
Digite seu nome:

6. Seu nome será inserido e armazenado junto com a pontuação dos jogadores.

7. Caso os participantes queiram ver suas colocações, basta ir ao Menu principal e selecionar a opção exibir placar.
- Nesta opção, estarão os nomes dos jogadores com as 5 melhores colocações e suas pontuações.

8. Para encerrar o Corrida 2D, é necessário que o jogador aperte 'q' no Menu Principal, e o jogo se fechará automaticamente.


## CONTRIBUINTES

<ul>
  <li>
    <a href="https://github.com/daviruy61">Davi Gomes</a> -
    dgfra@cesar.school 📩
  </li>
  <li>
    <a href="https://github.com/marceloh090">Marcelo Henrique</a> -
    mhbp@cesar.school 📩
  </li>
  <li>
    <a href="https://github.com/dekenner">Gabriel Ken</a> -
    gkci@cesar.school 📩
  </li>
</ul>

<table>
  <tr>
    <td align="center">
      <a href="https://github.com/daviruy61">
        <img src="https://avatars3.githubusercontent.com/daviruy61" width="100px;" alt="Foto de Davi"/><br>
        <sub>
          <b>Davi Gomes</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/marceloh090">
        <img src="https://avatars.githubusercontent.com/marceloh090" width="100px;" alt="Foto de Marcelo"/><br>
        <sub>
          <b>Marcelo Henrique</b>
        </sub>
      </a>
    </td>
    <td align="center">
      <a href="https://github.com/dekenner">
        <img src="https://avatars.githubusercontent.com/dekenner" width="100px;" alt="Foto de Gabriel"/><br>
        <sub>
          <b>Gabriel Ken</b>
        </sub>
      </a>
    </td>
  </tr>
</table>
