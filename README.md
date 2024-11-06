## Instituição de Ensino: CESAR School

## Disciplina: Programação Imperativa e Funcional - 2024.2

## Membros do Projeto
- Paulo Martins Cavalcanti - [@PauloCVT] (https://github.com/PauloCVT)
- João Pedro Costa de Oliveira - [@JoaoPedro-Costa-Oliveira] (https://github.com/JoaoPedro-Costa-Oliveira)
- Gilvando Guerra Gonçalves - [@gilguerra1] (https://github.com/gilguerra1)
- Diego José Arroxelas - [@Diegoarroxelas] (https://github.com/Diegoarroxelas)


## Descrição da Mecânica do Jogo
O jogo é um clássico shooter estilo arcade, onde o jogador controla um personagem na parte inferior da tela, movendo-se horizontalmente para a esquerda ou para a direita para atirar e derrotar naves inimigas que se aproximam de cima.

Objetivo Principal: O jogador deve eliminar todos os inimigos deixar que os inimigos alcançem a sua posição.

## Mecânicas implementadas
Movimentação do Jogador:

 - O jogador pode se mover horizontalmente para a esquerda e direita usando as teclas 'a' e 'd', respectivamente.
 - A posição do jogador é atualizada com base na leitura do teclado.

Movimentação do inimigo:

- Os inmigos se movem horizontalmente e ao atingir as bordas, invertem a direção do movimento e descem uma linha em direção ao jogador.


## Mecânicas em desenvolvimento
- Caso alguma nave inimiga alcançe a linha do jogador, o jogo termina.
- O jogador atira automaticamente a cada intervalo de tempo, ao atingir um inmigo a frequência dos disparos aumenta