//DOM-EJP-Model.h - Projeto Dominó
//08/09/2025 - Grupo: EJP
//Pedro Chagas Neves de Farias Nascimento
//Joao lucas de lima souza
//Eduarda Gabriele Bispo da Silva

#ifndef DOM_EJP_MODEL_H
#define DOM_EJP_MODEL_H

#define MAX_PECAS 28
#define MAX_JOGADORES 2
#define MAO_INICIAL 7

typedef struct {
    int lado1;
    int lado2;
} Peca;

typedef struct {
    Peca baralho[MAX_PECAS];
    int topoBaralho;
    Peca mesa[MAX_PECAS];
    int qtdMesa;
    int pontaEsq;
    int pontaDir;
    Peca maos[MAX_JOGADORES][MAX_PECAS];
    int qtdMao[MAX_JOGADORES];
    int jogadorAtual;
    int passesConsecutivos;
    int modoJogo;
} EstadoJogo;

typedef struct {
    int indicePeca;
    int lado;
    int prioridade;
} JogadaBot;

#endif
