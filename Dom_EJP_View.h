//DOM-EJP-View.h - Projeto Dominó
//08/09/2025 - Grupo: EJP
//Pedro Chagas Neves de Farias Nascimento
//Joao lucas de lima souza
//Eduarda Gabriele Bispo da Silva

#ifndef DOM_EJP_VIEW_H
#define DOM_EJP_VIEW_H

#include "Dom_EJP_Model.h"

void limparTela();
void pausarTela();
void mostrarMenuPrincipal();
void mostrarMenuModo();
void mostrarRegras();
void mostrarPeca(Peca p);
void mostrarMao(Peca* mao, int qtd, int jogador);
void mostrarMaoOculta(int qtd, int jogador);
void mostrarMesa(const EstadoJogo* e);
void mostrarVezDoJogador(int jogador);
void mostrarVencedor(int jogador);
void mostrarMensagem(const char* msg);
void mostrarMensagemJogoTravado();
void mostrarMensagemSemJogadaComCompra();
void mostrarMensagemSemJogadaSemCompra();
void mostrarPrimeiraJogada(int jogador, Peca p);
void mostrarJogadaBot(int indicePeca, Peca peca, int lado);
int obterEscolhaDoJogador(int qtdPecas);
int obterLadoParaJogar();
int obterOpcaoMenu();
int obterModoJogo();

#endif
