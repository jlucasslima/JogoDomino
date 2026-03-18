//DOM-EJP-View.cpp - Projeto Dominó
//08/09/2025 - Grupo: EJP
//Pedro Chagas Neves de Farias Nascimento
//Joao lucas de lima souza
//Eduarda Gabriele Bispo da Silva

#include <stdio.h>
#include <stdlib.h>
#include "Dom_EJP_View.h"

void limparTela() {
    system("cls");
}

void pausarTela() {
    printf("\nPressione Enter para continuar...");
    fflush(stdin);
    getchar();
}

void mostrarMenuPrincipal() {
    printf("===== DOMINO =====\n");
    printf("1 - Iniciar nova partida\n");
    printf("2 - Carregar partida salva\n");
    printf("3 - Ver Regras\n");
    printf("4 - Sair\n");
}

void mostrarMenuModo() {
    printf("===== MODO DE JOGO =====\n");
    printf("1 - Jogador vs Jogador\n");
    printf("2 - Jogador vs Computador\n");
}

void mostrarRegras() {
    printf("\n===== REGRAS DO JOGO =====\n");
    printf("1. Cada jogador comeca com 7 pecas.\n");
    printf("2. O jogador com a maior peca dupla (6-6, 5-5, etc.) comeca o jogo.\n");
    printf("3. Em sua vez, o jogador deve colocar uma peca que combine com uma das extremidades da mesa.\n");
    printf("4. Se um jogador nao tiver uma peca que combine, ele deve comprar do monte ate encontrar uma.\n");
    printf("5. Se o monte estiver vazio e o jogador nao puder jogar, ele passa a vez.\n");
    printf("6. O jogo termina quando um jogador fica sem pecas ou quando o jogo fica 'travado' (ninguem pode jogar).\n");
}

void mostrarPeca(Peca p) {
    printf("[%d|%d]", p.lado1, p.lado2);
}

void mostrarMao(Peca* mao, int qtd, int jogador) {
    if (jogador == 0) {
        printf("\nSua Mao (Jogador %d):\n", jogador + 1);
    } else {
        printf("\nMao do Computador (Jogador %d):\n", jogador + 1);
    }
    for (int i = 0; i < qtd; i++) {
        printf(" %d:", i + 1);
        mostrarPeca(mao[i]);
    }
    if (qtd == 0) printf(" (sem pecas)");
    printf("\n");
}

void mostrarMaoOculta(int qtd, int jogador) {
    if (jogador == 0) {
        printf("\nMao do Oponente (Jogador %d): %d pecas\n", jogador + 1, qtd);
    } else {
        printf("\nMao do Computador (Jogador %d): %d pecas\n", jogador + 1, qtd);
    }
}

void mostrarMesa(const EstadoJogo* e) {
    printf("\n==================== MESA ====================\n ");
    if (e->qtdMesa == 0) {
        printf("(vazia)");
    } else {
        printf("E:%d ", e->pontaEsq);
        for (int i = 0; i < e->qtdMesa; i++) {
            mostrarPeca(e->mesa[i]);
            printf(" ");
        }
        printf("D:%d", e->pontaDir);
    }
    printf("\n==============================================\n");
}

void mostrarVezDoJogador(int jogador) {
    if (jogador == 0) {
        printf("\n--- Sua Vez (Jogador %d) ---\n", jogador + 1);
    } else {
        printf("\n--- Vez do Computador (Jogador %d) ---\n", jogador + 1);
    }
}

void mostrarVencedor(int jogador) {
    if (jogador == 0) {
        printf("\nVoce venceu! (sem pecas)\n");
    } else {
        printf("\nComputador venceu! (sem pecas)\n");
    }
}

void mostrarMensagem(const char* msg) {
    printf("%s\n", msg);
}

void mostrarMensagemJogoTravado() {
    printf("\nJogo travou (bloqueado). Fim de jogo.\n");
}

void mostrarMensagemSemJogadaComCompra() {
    printf("Sem jogadas disponiveis. Voce deve comprar uma peca (digite 0).\n");
}

void mostrarMensagemSemJogadaSemCompra() {
    printf("Sem jogadas e sem pecas para comprar. Passando a vez.\n");
}

void mostrarPrimeiraJogada(int jogador, Peca p){
    if (jogador == 0) {
        printf("\nVoce inicia com a maior dupla: ");
    } else {
        printf("\nComputador inicia com a maior dupla: ");
    }
    mostrarPeca(p);
    printf("\n");
}

void mostrarJogadaBot(int indicePeca, Peca peca, int lado) {
    printf("Computador jogou a peca %d: ", indicePeca + 1);
    mostrarPeca(peca);
    if (lado == 0) {
        printf(" na esquerda\n");
    } else {
        printf(" na direita\n");
    }
}

int obterEscolhaDoJogador(int qtdPecas) {
    int escolha = -1;
    printf("\n--- OPCOES DE JOGADA ---\n");
    printf("Escolha uma peca de 1 a %d para jogar.\n", qtdPecas);
    printf("----------------------------------------\n");
    printf(" 0 - Comprar uma peca do monte\n");
    printf("99 - Salvar a partida e Sair\n");
    printf("88 - Abandonar a partida (Sair sem Salvar)\n");
    printf("----------------------------------------\n");
    printf("Sua escolha: ");
    
    scanf("%d", &escolha);
    return escolha;
}

int obterLadoParaJogar() {
    int lado = -1;
    printf("Jogar na (0) esquerda ou (1) direita? ");
    scanf("%d", &lado);
    if (lado != 0 && lado != 1) return -1;
    return lado;
}

int obterOpcaoMenu() {
    int opcao = 0;
    printf("Escolha: ");
    scanf("%d", &opcao);
    return opcao;
}

int obterModoJogo() {
    int modo = 0;
    printf("Escolha: ");
    scanf("%d", &modo);
    return modo;
}
