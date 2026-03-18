# Projeto Domino

## Descricao do Projeto
Implementacao de um jogo classico de Domino desenvolvido em C/C++ para execucao em console. O software adota a arquitetura MVC (Model-View-Controller) para manter uma separacao rigida entre a interface do usuario, a estruturacao dos dados e a logica de regras do jogo. 

## Modos de Jogo
* **Jogador vs Jogador:** Partida local onde dois usuarios se revezam no mesmo terminal. As maos sao ocultadas durante a transicao de turnos.
* **Jogador vs Computador:** Partida contra uma Inteligencia Artificial (IA) integrada. A IA utiliza um algoritmo heuristico para avaliar, pontuar e decidir a jogada mais vantajosa matematicamente.

## Funcionalidades Principais
* **Gerenciamento de Estado:** Possibilidade de salvar o progresso da partida em um arquivo binario (`domino.dat`) a qualquer momento e carrega-lo em execucoes futuras do programa.
* **Sistema de Regras Completo:** * Identificacao automatica do jogador com a maior peca dupla para a jogada inaugural.
  * Sistema dinamico de validacao de pontas (esquerda e direita) da mesa.
  * Logica de compra de pecas do monte (cemiterio) quando nao ha jogadas disponiveis na mao.
  * Condicoes de vitoria por descarte total das pecas ou encerramento por partida "travada" (quando ninguem possui pecas compativeis e o monte esvazia).

## Estrutura da Arquitetura (MVC)
* **Model (`Dom_EJP_Model.h/cpp`):** Define as estruturas de dados (`Peca`, `EstadoJogo`, `JogadaBot`). Centraliza o estado do baralho, as maos dos jogadores, as pontas da mesa e o controle de turnos.
* **View (`Dom_EJP_View.h/cpp`):** Responsavel por toda a interacao com o usuario. Renderiza os menus, exibe o estado visual da mesa e das maos, e coleta os inputs para as jogadas e escolhas de direcao.
* **Controller (`Dom_EJP_Controller.h/cpp`):** Coracao do sistema. Gerencia o loop de gameplay, distribui as pecas de forma pseudoaleatoria, valida as regras de encaixe, avalia o algoritmo do Bot e executa as operacoes de I/O para o salvamento de arquivos.

## Como Compilar e Executar
O projeto pode ser compilado utilizando o GCC ou MinGW. No terminal, navegue ate o diretorio raiz contendo os codigos-fonte e execute:

```bash
g++ Dom_EJP_PROJETO.cpp -o domino
