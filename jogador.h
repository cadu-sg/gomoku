#ifndef JOGADOR_H
#define JOGADOR_H

#define TAM_NOME 51

typedef struct {
    char nome[TAM_NOME];
    char peca;
    unsigned int qtd_vitorias;
} Jogador;

Jogador novo_jogador(char peca);
void cadastrar_novos_jogadores(Jogador *jogador1, Jogador *jogador2);
void imprimir_placar(Jogador jogador1, Jogador jogador2);

#endif