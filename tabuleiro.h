#ifndef TABULEIRO_H
#define TABULEIRO_H

#include "jogador.h"
#include <stdbool.h>

char **alocar_tabuleiro(int ordem);
void reiniciar_tabuleiro(char **tabuleiro, int ordem);
void imprimir_tabuleiro(char **tabuleiro, int dimensao);
void inserir_peca(char **tabuleiro, int ordem, Jogador jogador);
void destruir_tabuleiro(char **tabuleiro, int dimensao);

bool ganhou_linhas_ou_colunas(char **tabuleiro, int dimensao, char peca);
bool ganhou_diagonais_principais(char **tabuleiro, int ordem, char peca);
bool ganhou_diagonais_secundarias(char **tabuleiro, int ordem, char peca);
bool tabuleiro_cheio(char **tabuleiro, int ordem);
char avaliar_tabuleiro(char **tabuleiro, int ordem);

typedef struct {
    int i[2];
    int j[2];
} Remocoes;

typedef struct {
    int jogadorP;
    int jogadorB;
} PlacarCapturas;

void capturar_pecas_linhas_colunas(char **tabuleiro, int ordem, PlacarCapturas *placar, char capturador, char capturado);
void capturar_pecas_diagonais_principais(char **tabuleiro, int ordem, PlacarCapturas *placar, char capturador, char capturado);
void capturar_pecas_diagonais_secundarias(char **tabuleiro, int ordem, PlacarCapturas *placar, char capturador, char capturado);
void imprimir_placar_capturas(PlacarCapturas placar, Jogador jogador1, Jogador jogador2);
void capturar_pecas(char **tabuleiro, int ordem, PlacarCapturas *placar);
bool posicao_permitida(char **tabuleiro, int ordem, int lin, int col, char peca);

#endif