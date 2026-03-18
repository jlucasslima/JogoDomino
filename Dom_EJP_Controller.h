//DOM-EJP-Controller.h - Projeto Dominó
//08/09/2025 - Grupo: EJP
//Pedro Chagas Neves de Farias Nascimento
//Joao lucas de lima souza
//Eduarda Gabriele Bispo da Silva

#ifndef DOM_EJP_CONTROLLER_H
#define DOM_EJP_CONTROLLER_H

#include "Dom_EJP_Model.h"
#include "Dom_EJP_View.h"

void iniciarPartida();
void carregarEContinuarPartida(); 
void salvarEstado(const EstadoJogo* e);
int carregarEstado(EstadoJogo* e);

#endif
