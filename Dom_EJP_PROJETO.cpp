//DOM-EJP-PROJETO.cpp - Projeto Dominó
//08/09/2025 - Grupo: EJP
//Pedro Chagas Neves de Farias Nascimento
//Joao lucas de lima souza
//Eduarda Gabriele Bispo da Silva

#include "Dom_EJP_Model.h"
#include "Dom_EJP_Controller.h"
#include <windows.h>

#include "Dom_EJP_Model.cpp"
#include "Dom_EJP_Controller.cpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    limparTela();
    int opcao = 0;
    do {
        mostrarMenuPrincipal();
        opcao = obterOpcaoMenu();

        switch (opcao) {
            case 1:
                limparTela();
                iniciarPartida();
                break;
            case 2:
                limparTela();
                carregarEContinuarPartida();
                break;
            case 3:
                limparTela();
                mostrarRegras();
                break;
            case 4:
                mostrarMensagem("Saindo...");
                break;
            default:
                mostrarMensagem("Opcao invalida!");
                break;
        }
        if (opcao != 4) pausarTela();
        limparTela();
    } while (opcao != 4);
    return 0;
}
