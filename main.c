#include "armazenamento.h"
#include "ferramentas.h"
#include "jogador.h"
#include "tabuleiro.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void nova_partida(Jogador *jogador1, Jogador *jogador2, char **tabuleiro, int ordem);

int main() {

    srand((unsigned)time(NULL));

    char op;
    Jogo jogo;
    int ordem_anterior = 0;

    printf("Bem vindo ao jogo gomoku\n");
    printf("OBS: Esse jogo nao tem salvamento automatico\n\n");

    // Menu do jogo ao iniciar
    printf("Opcoes do menu:\n"
           "'N' para iniciar uma novo jogo\n"
           "'C' para carregar um jogo salvo\n");
    while (true) {
        scanf(" %c", &op);
        limpar_buffer();
        if (op != 'N' && op != 'n' && op != 'C' && op != 'c')
            printf("Erro! Digite novamente a opcao: ");
        else
            break;
    }

    do {
        if (op == 'N' || op == 'n') {
            // Criar um novo tabuleiro
            int retorno_scanf;
            printf("Digite a ordem do tabuleiro: ");
            while (1) {
                retorno_scanf = scanf("%d", &jogo.ordem);
                if (jogo.ordem < 5 || jogo.ordem > 19 || retorno_scanf <= 0) {
                    printf("Erro! Digite novamente a ordem do tabuleiro: ");
                    limpar_buffer();
                } else
                    break;
            }
            limpar_buffer();
            // Se estamos na primeira partida é preciso alocar o tabuleiro
            if (ordem_anterior == 0)
                jogo.tabuleiro = alocar_tabuleiro(jogo.ordem);
            else {
                if (ordem_anterior != jogo.ordem) {
                    // Senao, precisamos destruir o tabuleiro anterior para alocar um novo se a ordem for diferente
                    destruir_tabuleiro(jogo.tabuleiro, jogo.ordem);
                    jogo.tabuleiro = alocar_tabuleiro(jogo.ordem);
                }
            }
            jogo.tabuleiro = alocar_tabuleiro(jogo.ordem);
            // Cadastrar novos jogadores
            cadastrar_novos_jogadores(&jogo.jogador1, &jogo.jogador2);
            // Iniciar partida com os dados reiniciados
            nova_partida(&jogo.jogador1, &jogo.jogador2, jogo.tabuleiro, jogo.ordem);
            ordem_anterior = jogo.ordem;
        } else if (op == 'P' || op == 'p') {
            if (ordem_anterior == 0) {
                jogo.tabuleiro = alocar_tabuleiro(jogo.ordem);
            }
            // Iniciar partida com os mesmos dados
            nova_partida(&jogo.jogador1, &jogo.jogador2, jogo.tabuleiro, jogo.ordem);
        } else if (op == 'C' || op == 'c') {
            if (existem_saves()) {
                listar_saves();
                jogo = carregar_jogo();
                // Se estamos na primeira partida é preciso alocar o tabuleiro
                if (ordem_anterior == 0)
                    jogo.tabuleiro = alocar_tabuleiro(jogo.ordem);
                else {
                    if (ordem_anterior != jogo.ordem) {
                        // Senao, precisamos destruir o tabuleiro anterior para alocar um novo se a ordem for diferente
                        destruir_tabuleiro(jogo.tabuleiro, jogo.ordem);
                        jogo.tabuleiro = alocar_tabuleiro(jogo.ordem);
                    }
                }
                imprimir_placar(jogo.jogador1, jogo.jogador2);
                ordem_anterior = jogo.ordem;
            } else {
                printf("Nenhum save encontrado\n");
            }
        } else if (op == 'S' || op == 's') {
            salvar_jogo(jogo);
        }

        // Menu do jogo
        printf("Opcoes do menu:\n"
               "'N' para iniciar um novo jogo\n"
               "'C' para carregar um jogo salvo\n"
               "'P' para iniciar uma nova partida nesse jogo\n"
               "'S' para salvar o jogo atual\n"
               "'E' para sair do jogo\n");
        while (true) {
            scanf(" %c", &op);
            limpar_buffer();
            if (op != 'N' && op != 'n' && op != 'C' && op != 'c' && op != 'P' && op != 'p' && op != 'S' && op != 's' && op != 'E' && op != 'e')
                printf("Erro! Digite novamente a opcao: ");
            else
                break;
        }
    } while (op != 'E' && op != 'e');

    destruir_tabuleiro(jogo.tabuleiro, jogo.ordem);
}

void nova_partida(Jogador *jogador1, Jogador *jogador2, char **tabuleiro, int ordem) {

    PlacarCapturas placar_capturas;
    placar_capturas.jogadorP = 0;
    placar_capturas.jogadorB = 0;
    imprimir_tabuleiro(tabuleiro, ordem);

    // Inserir peças alternadamente
    short int vez, resultado;
    if (jogador1->peca == 'P')
        vez = 1;
    else
        vez = 2;
    do {
        if (vez == 1) {
            inserir_peca(tabuleiro, ordem, *jogador1);
            vez = 2;
        } else {
            inserir_peca(tabuleiro, ordem, *jogador2);
            vez = 1;
        }
        capturar_pecas(tabuleiro, ordem, &placar_capturas);
        imprimir_tabuleiro(tabuleiro, ordem);
        imprimir_placar_capturas(placar_capturas, *jogador1, *jogador2);
        if (placar_capturas.jogadorP >= 5) {
            printf("A peca 'P' realizou 5 ou mais capturas!\n");
            resultado = 'P';
        } else if (placar_capturas.jogadorB >= 5) {
            printf("A peca 'B' realizou 5 ou mais capturas!\n");
            resultado = 'B';
        } else
            resultado = avaliar_tabuleiro(tabuleiro, ordem);
    } while (resultado == 'C');

    if (jogador1->peca == resultado) {
        printf("Vitoria de %s\n", jogador1->nome);
        jogador1->qtd_vitorias++;
    } else if (jogador2->peca == resultado) {
        printf("Vitoria de %s\n", jogador2->nome);
        jogador2->qtd_vitorias++;
    } else {
        printf("Empate\n");
    }

    // Alternar as pecas dos jogadores para a proxima partida mudar quem começa primeiro
    char aux;
    aux = jogador1->peca;
    jogador1->peca = jogador2->peca;
    jogador2->peca = aux;

    // Reiniciar tabuleiro
    reiniciar_tabuleiro(tabuleiro, ordem);

    imprimir_placar(*jogador1, *jogador2);
}
