Trabalho Prático PDS II
-
Este código é o nosso trabalho final da disciplina PDS II.

O principal objetivo desse trabalho prático foi implementar um sistema no qual é possível jogar os jogos reversi e lig4.

Este trabalho foi uma ótima oportunidade para colocar em prática os principais conceitos aprendidos na disciplina como, tipos abstratos de dados, classes, herança, polimorfismo, encapsulamento, entre outros.


Fizemos aquilo que foi solicitado pelo projeto:
- Lig4;
- Reversi.

Além disso, fizemos os seguintes adicionais:
- Campo Minado (Minesweeper);
- Jogo da Cobrinha (Snake);
- Display gráfico para o Reversi;
- Algoritmo para sugerir jogadas no Reversi e no Lig4;
- Arquivo com histórico de vitórias e derrotas de cada jogador.

Para cumprir com esses objetivos, a primeira parte foi dividir o grupo de modo que cada um tivesse sua função. Cada um ficou responsável por testar sua parte.
- Rafael: Reversi + Interface Gráfica
- Ulisses: Lig4
- Luis: Minesweeper + Makefile
- Yuri: Snake
- Caio: Algoritmo para Lig4 e Cartão CRC
- Ulisses e Rafael: Juntar as branches e criar o menu

Todos os jogos ficaram são derivados de uma classe abstrata chamada Game. O tabuleiro "Board" é um vetor de vetores de int, inicializado com zeros.

Reversi e Lig4:
-
Nos jogos Reversi e Lig4, fazer uma jogada consiste em alterar uma posição "0" no tabuleiro para "1" ou para "2", caso seja jogador 1 ou 2 que fez a jogada respectivamente.

A cada jogada, deve-se checar se o jogo acabou.
  - Se acabou, deve-se encerrar a partida, alterar o histórico dos jogadores e mostrar o vencedor;
  - Caso contrário, deve-se verificar quais são as novas jogadas válidas e passar o turno para o outro jogador.

Esse processo se repete até acabar o jogo.

  Algoritmo para Lig4:
  -
  
  Caso o usuário queira usar o algoritmo para sugerir jogadas, ele deve chamar a função "Suggest_play_lig4".
  
  Ao chamar a função, um dos parâmetros usados é um inteiro "n" que serve como número de jogadas que a função testa.
  
  Essa função funciona da seguinte forma:
  - Testa: Existe alguma forma de ganhar o jogo na jogada atual?
    - Se sim, sugere a jogada que ganha o jogo
    - Se não, testa: Existe alguma jogada que, independende de qual seja a jogada seguinte do oponente, é possível garantir a vitória em n-1 jogadas (chama a função novamente)?
      - Se sim, sugere a jogada que garante isso.
      - Se não, sugere uma jogada de uma lista de jogadas estatísticamente mais fortes.


Minesweeper
-
Regras: Revele casas onde não há bomba para vencer.
Os números das casas contam quantas bombas existem em casas adjacentes.
As bombas são aleatoriatoriamente posicionadas e há bandeiras para organizar e revelar casas com mais eficiência.
A cada jogada, deve-se receber do usuário um input entre revelar uma casa ou colocar uma bandeira na casa.

  Se ele quiser revelar uma casa, deve-se:
  - Checar se a casa possui uma bomba.
      - Se possuir, o jogador perde (fim de jogo);
      - Caso contrário, revela um inteiro equivalente ao número de bombas vizinhas à casa escolhida.
  
  Se ele quiser colocar uma bandeira, deve-se:
  - Colocar ou retirar uma bandeira na casa escolhida (Casas com bandeira não podem ser reveladas).
    
O jogador vence o jogo se todas as casas sem bomba forem reveladas.
O jogo continua até existir vitória ou derrota.

Snake
-
O jogador deve controlar uma cobrinha com as setas do teclado.

O jogo acaba quando a cobrinha bate em si mesma ou na parede.

A cobra aumenta de tamanho sempre que come uma "bolinha".

O objetivo do jogo é ficar com a cobra do maior tamanho possível antes de morrer.

