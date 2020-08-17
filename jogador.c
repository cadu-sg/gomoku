#include "jogador.h"
#include "ferramentas.h"
#include <stdio.h>
#include <string.h>

Jogador novo_jogador(char peca) {
    Jogador jogador;
    // Nome
    printf("Nome do jogador %c (maximo 50 caracteres): ", peca);
    fgets(jogador.nome, TAM_NOME, stdin);
    jogador.nome[strlen(jogador.nome) - 1] = '\0'; // Retirar o \n do final da string
    // Cor
    jogador.peca = peca;
    // Quantidade de vitorias
    jogador.qtd_vitorias = 0;
    return jogador;
}

void cadastrar_novos_jogadores(Jogador *jogador1, Jogador *jogador2) {

    printf("Nome do jogador 1 (maximo 50 caracteres): ");
    fgets(jogador1->nome, TAM_NOME, stdin);
    jogador1->nome[strlen(jogador1->nome) - 1] = '\0'; // Retirar o \n do final da string

    printf("Nome do jogador 2 (maximo 50 caracteres): ");
    fgets(jogador2->nome, TAM_NOME, stdin);
    jogador2->nome[strlen(jogador2->nome) - 1] = '\0';

    if (int_aleatorio(1, 2) == 1) {
        jogador1->peca = 'P';
        jogador2->peca = 'B';
    } else {
        jogador1->peca = 'B';
        jogador2->peca = 'P';
    }
    jogador1->qtd_vitorias = 0;
    jogador2->qtd_vitorias = 0;
}

void imprimir_placar(Jogador jogador1, Jogador jogador2) {
    printf("Placar: %s %d x %d %s\n", jogador1.nome, jogador1.qtd_vitorias, jogador2.qtd_vitorias, jogador2.nome);
}