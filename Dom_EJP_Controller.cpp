//DOM-EJP-Controller.cpp - Projeto Dominó
//08/09/2025 - Grupo: EJP
//Pedro Chagas Neves de Farias Nascimento
//Joao lucas de lima souza
//Eduarda Gabriele Bispo da Silva

#include <time.h>
#include <stdlib.h>
#include "Dom_EJP_Controller.h"

#include "Dom_EJP_View.cpp"

static void loopPrincipalDoJogo(EstadoJogo* e);
static int realizarPrimeiraJogada(EstadoJogo* e);
static JogadaBot calcularMelhorJogada(const EstadoJogo* e, int jogador);
static int avaliarPeca(Peca p, const EstadoJogo* e, int lado);

static void montarBaralho(EstadoJogo* e) {
    int idx = 0;
    for (int i = 0; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            e->baralho[idx].lado1 = i;
            e->baralho[idx].lado2 = j;
            idx++;
        }
    }
    e->topoBaralho = MAX_PECAS - 1;
}

static void embaralhar(EstadoJogo* e) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < MAX_PECAS; i++) {
        int j = rand() % MAX_PECAS;
        Peca tmp = e->baralho[i];
        e->baralho[i] = e->baralho[j];
        e->baralho[j] = tmp;
    }
}

static int comprar(EstadoJogo* e, int jogador) {
    if (e->topoBaralho < 0) return 0;
    e->maos[jogador][e->qtdMao[jogador]++] = e->baralho[e->topoBaralho--];
    return 1;
}

static void distribuir(EstadoJogo* e) {
    for (int j = 0; j < MAX_JOGADORES; j++) e->qtdMao[j] = 0;
    for (int r = 0; r < MAO_INICIAL; r++) {
        for (int j = 0; j < MAX_JOGADORES; j++) {
            comprar(e, j);
        }
    }
}

static int podeEncaixar(Peca p, int ponta) {
    return (p.lado1 == ponta || p.lado2 == ponta);
}

static Peca girada(Peca p) {
    Peca g;
    g.lado1 = p.lado2;
    g.lado2 = p.lado1;
    return g;
}

static void removerPecaDaMao(EstadoJogo* e, int jogador, int indiceMao) {
    for (int i = indiceMao; i < e->qtdMao[jogador] - 1; i++) {
        e->maos[jogador][i] = e->maos[jogador][i + 1];
    }
    e->qtdMao[jogador]--;
}

static int tentarJogar(EstadoJogo* e, int jogador, int indiceMao, int lado) {
    if (indiceMao < 0 || indiceMao >= e->qtdMao[jogador]) return 0;
    Peca p = e->maos[jogador][indiceMao];
    if (e->qtdMesa == 0) {
        e->mesa[e->qtdMesa++] = p;
        e->pontaEsq = p.lado1;
        e->pontaDir = p.lado2;
    } else if (lado == 0) {
        if (podeEncaixar(p, e->pontaEsq)) {
            if (p.lado2 != e->pontaEsq) p = girada(p);
            for (int k = e->qtdMesa; k > 0; k--) e->mesa[k] = e->mesa[k - 1];
            e->mesa[0] = p;
            e->qtdMesa++;
            e->pontaEsq = p.lado1;
        } else { return 0; }
    } else {
        if (podeEncaixar(p, e->pontaDir)) {
            if (p.lado1 != e->pontaDir) p = girada(p);
            e->mesa[e->qtdMesa++] = p;
            e->pontaDir = p.lado2;
        } else { return 0; }
    }
    removerPecaDaMao(e, jogador, indiceMao);
    return 1;
}

static int haJogadaDisponivel(const EstadoJogo* e, int jogador) {
    if (e->qtdMesa == 0) return e->qtdMao[jogador] > 0;
    for (int i = 0; i < e->qtdMao[jogador]; i++) {
        Peca p = e->maos[jogador][i];
        if (podeEncaixar(p, e->pontaEsq) || podeEncaixar(p, e->pontaDir)) {
            return 1;
        }
    }
    return 0;
}

static int realizarPrimeiraJogada(EstadoJogo* e) {
    int jogadorInicial = -1;
    int indicePeca = -1;
    Peca pecaInicial;
    for (int d = 6; d >= 0; d--) {
        for (int j = 0; j < MAX_JOGADORES; j++) {
            for (int i = 0; i < e->qtdMao[j]; i++) {
                if (e->maos[j][i].lado1 == d && e->maos[j][i].lado2 == d) {
                    jogadorInicial = j;
                    indicePeca = i;
                    pecaInicial = e->maos[j][i];
                    goto fim_busca;
                }
            }
        }
    }
    fim_busca:
    if (jogadorInicial != -1) {
        tentarJogar(e, jogadorInicial, indicePeca, 0);
        mostrarPrimeiraJogada(jogadorInicial, pecaInicial);
        return 1 - jogadorInicial;
    }
    return 0;
}

static int avaliarPeca(Peca p, const EstadoJogo* e, int lado) {
    int pontuacao = 0;
    
    if (p.lado1 == p.lado2) {
        pontuacao += 15;
    }
    
    int soma = p.lado1 + p.lado2;
    if (soma >= 10) pontuacao += 8;
    else if (soma >= 7) pontuacao += 5;
    else if (soma >= 4) pontuacao += 2;
    
    int numeroFrequente = (p.lado1 + p.lado2) / 2;
    if (numeroFrequente >= 4) pontuacao += 3;
    
    if (lado == 0) {
        int novaEsquerda = (p.lado2 == e->pontaEsq) ? p.lado1 : p.lado2;
        if (novaEsquerda == e->pontaDir) pontuacao += 20;
        if (novaEsquerda == 0 || novaEsquerda == 6) pontuacao += 5;
    } else {
        int novaDireita = (p.lado1 == e->pontaDir) ? p.lado2 : p.lado1;
        if (novaDireita == e->pontaEsq) pontuacao += 20;
        if (novaDireita == 0 || novaDireita == 6) pontuacao += 5;
    }
    
    pontuacao += rand() % 8;
    
    return pontuacao;
}

static JogadaBot calcularMelhorJogada(const EstadoJogo* e, int jogador) {
    JogadaBot melhorJogada = {-1, 0, -1};
    
    for (int i = 0; i < e->qtdMao[jogador]; i++) {
        Peca p = e->maos[jogador][i];
        
        if (e->qtdMesa == 0) {
            melhorJogada.indicePeca = i;
            melhorJogada.lado = 0;
            melhorJogada.prioridade = avaliarPeca(p, e, 0);
            return melhorJogada;
        }
        
        int podeEsq = podeEncaixar(p, e->pontaEsq);
        int podeDir = podeEncaixar(p, e->pontaDir);
        
        if (podeEsq) {
            int prioridade = avaliarPeca(p, e, 0);
            if (prioridade > melhorJogada.prioridade) {
                melhorJogada.indicePeca = i;
                melhorJogada.lado = 0;
                melhorJogada.prioridade = prioridade;
            }
        }
        
        if (podeDir) {
            int prioridade = avaliarPeca(p, e, 1);
            if (prioridade > melhorJogada.prioridade) {
                melhorJogada.indicePeca = i;
                melhorJogada.lado = 1;
                melhorJogada.prioridade = prioridade;
            }
        }
    }
    
    return melhorJogada;
}

void salvarEstado(const EstadoJogo* e) {
    FILE *f = fopen("domino.dat", "wb");
    if (f == NULL) {
        mostrarMensagem("Erro ao abrir arquivo para salvar.");
        return;
    }
    if (fwrite(e, sizeof(EstadoJogo), 1, f) != 1) {
        mostrarMensagem("Erro ao salvar estado do jogo.");
    } else {
        mostrarMensagem("Estado do jogo salvo com sucesso!");
    }
    fclose(f);
}

int carregarEstado(EstadoJogo* e) {
    FILE *f = fopen("domino.dat", "rb");
    if (f == NULL) {
        mostrarMensagem("Nenhum jogo salvo encontrado.");
        return 0;
    }
    if (fread(e, sizeof(EstadoJogo), 1, f) != 1) {
        mostrarMensagem("Erro ao carregar estado do jogo.");
        fclose(f);
        return 0;
    }
    fclose(f);
    mostrarMensagem("Jogo carregado com sucesso!");
    return 1;
}

void iniciarPartida() {
    EstadoJogo e;
    
    mostrarMenuModo();
    int modo = obterModoJogo();
    while (modo != 1 && modo != 2) {
        mostrarMensagem("Opcao invalida! Escolha 1 ou 2.");
        pausarTela();
        limparTela();
        mostrarMenuModo();
        modo = obterModoJogo();
    }
    
    e.modoJogo = modo;
    montarBaralho(&e);
    embaralhar(&e);
    e.qtdMesa = 0;
    e.pontaEsq = -1;
    e.pontaDir = -1;
    distribuir(&e);
    e.jogadorAtual = realizarPrimeiraJogada(&e);
    e.passesConsecutivos = 0;
    pausarTela();
    loopPrincipalDoJogo(&e);
}

void carregarEContinuarPartida() {
    EstadoJogo e;
    if (carregarEstado(&e)) {
        pausarTela();
        loopPrincipalDoJogo(&e);
    } else {
        pausarTela();
    }
}

static void loopPrincipalDoJogo(EstadoJogo* e) {
    while (1) {
        limparTela();
        mostrarMesa(e);
        
        if (e->modoJogo == 2) {
            if (e->jogadorAtual == 0) {
                mostrarMaoOculta(e->qtdMao[1], 1);
                mostrarMao(e->maos[0], e->qtdMao[0], 0);
            } else {
                mostrarMao(e->maos[0], e->qtdMao[0], 0);
                mostrarMaoOculta(e->qtdMao[1], 1);
            }
        } else {
            mostrarMaoOculta(e->qtdMao[1 - e->jogadorAtual], 1 - e->jogadorAtual);
            mostrarMao(e->maos[e->jogadorAtual], e->qtdMao[e->jogadorAtual], e->jogadorAtual);
        }
        
        if (e->qtdMao[e->jogadorAtual] == 0) {
            mostrarVencedor(e->jogadorAtual);
            break;
        }
        
        mostrarVezDoJogador(e->jogadorAtual);
        
        if (!haJogadaDisponivel(e, e->jogadorAtual)) {
            if (e->topoBaralho >= 0) {
                if (e->modoJogo == 2 && e->jogadorAtual == 1) {
                    mostrarMensagem("Computador nao tem jogadas disponiveis e vai comprar.");
                    comprar(e, e->jogadorAtual);
                    pausarTela();
                    continue;
                } else {
                    mostrarMensagemSemJogadaComCompra();
                }
            } else {
                if (e->modoJogo == 2 && e->jogadorAtual == 1) {
                    mostrarMensagem("Computador nao pode jogar e passa a vez.");
                } else {
                    mostrarMensagemSemJogadaSemCompra();
                }
                e->passesConsecutivos++;
                if (e->passesConsecutivos >= MAX_JOGADORES) {
                    mostrarMensagemJogoTravado();
                    break;
                }
                e->jogadorAtual = 1 - e->jogadorAtual;
                pausarTela();
                continue;
            }
        } else {
            e->passesConsecutivos = 0;
        }
        
        if (e->modoJogo == 2 && e->jogadorAtual == 1) {
            JogadaBot jogada = calcularMelhorJogada(e, 1);
            if (jogada.indicePeca != -1) {
                Peca pecaJogada = e->maos[1][jogada.indicePeca];
                if (tentarJogar(e, 1, jogada.indicePeca, jogada.lado)) {
                    mostrarJogadaBot(jogada.indicePeca, pecaJogada, jogada.lado);
                    e->jogadorAtual = 0;
                } else {
                    mostrarMensagem("Erro na jogada do computador.");
                }
            } else {
                mostrarMensagem("Computador nao pode jogar e passa a vez.");
                e->jogadorAtual = 0;
                e->passesConsecutivos++;
            }
            pausarTela();
            continue;
        }
        
        int escolha = obterEscolhaDoJogador(e->qtdMao[e->jogadorAtual]);
        
        if (escolha == 99) {
            salvarEstado(e);
            mostrarMensagem("Jogo salvo. Retornando ao menu principal.");
            pausarTela();
            break;
        }
        if (escolha == 88) {
            mostrarMensagem("Partida abandonada. Retornando ao menu principal.");
            pausarTela();
            break;
        }

        if (escolha == 0) {
            if (comprar(e, e->jogadorAtual)) {
                mostrarMensagem("Voce comprou uma peca.");
            } else {
                mostrarMensagem("Nao ha mais pecas para comprar. Passando a vez.");
                e->jogadorAtual = 1 - e->jogadorAtual;
                e->passesConsecutivos++;
            }
            pausarTela();
            continue;
        }
        int idx = escolha - 1;
        if (idx < 0 || idx >= e->qtdMao[e->jogadorAtual]) {
            mostrarMensagem("Opcao invalida. Tente de novo.");
            pausarTela();
            continue;
        }
        int lado = 1;
        if (e->qtdMesa > 0) {
            Peca p = e->maos[e->jogadorAtual][idx];
            int podeEsq = podeEncaixar(p, e->pontaEsq);
            int podeDir = podeEncaixar(p, e->pontaDir);
            if (podeEsq && !podeDir) {
                lado = 0;
            } else if (!podeEsq && podeDir) {
                lado = 1;
            } else if (podeEsq && podeDir) {
                lado = obterLadoParaJogar();
                if (lado == -1) {
                    mostrarMensagem("Lado invalido. Tente de novo.");
                    pausarTela();
                    continue;
                }
            }
        }
        if (tentarJogar(e, e->jogadorAtual, idx, lado)) {
            mostrarMensagem("Jogada realizada com sucesso.");
            e->jogadorAtual = 1 - e->jogadorAtual;
        } else {
            mostrarMensagem("Jogada invalida. A peca nao encaixa nesse lado.");
        }
        pausarTela();
    }
}
