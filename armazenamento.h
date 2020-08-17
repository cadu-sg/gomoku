#ifndef ARMAZENAMENTO_H
#define ARMAZENAMENTO_H

#include "jogador.h"
#include <stdbool.h>

typedef struct {
    Jogador jogador1;
    Jogador jogador2;
    int ordem;
    char **tabuleiro;
} Jogo;

void salvar_jogo(Jogo jogo);
Jogo carregar_jogo();
void listar_saves();
bool existem_saves();

#endif
