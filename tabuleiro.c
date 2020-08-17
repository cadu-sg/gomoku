#include "tabuleiro.h"
#include "ferramentas.h"
#include "jogador.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

char **alocar_tabuleiro(int ordem) {
    char **tabuleiro = NULL;
    int i, j;
    tabuleiro = (char **)malloc(ordem * sizeof(char *));
    for (i = 0; i < ordem; i++) {
        tabuleiro[i] = (char *)malloc(ordem * sizeof(char));
    }
    for (i = 0; i < ordem; i++) {
        for (j = 0; j < ordem; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
    return tabuleiro;
}

void inserir_peca(char **tabuleiro, int ordem, Jogador jogador) {
    int lin, col, msg;
    printf("Vez de %s (%c)\n", jogador.nome, jogador.peca);
    while (1) {
        printf("Digite a posicao da linha: ");
        while (1) {
            msg = scanf("%d", &lin);
            if (lin >= ordem || msg <= 0) {
                printf("Erro! Digite novamente a posicao da linha: ");
                limpar_buffer();
            } else
                break;
        }
        printf("Digite a posicao da coluna: ");
        while (1) {
            msg = scanf("%d", &col);
            if (col >= ordem || msg <= 0) {
                printf("Erro! Digite novamente a posicao da coluna: ");
                limpar_buffer();
            } else
                break;
        }
        if (tabuleiro[lin][col] != ' ')
            printf("Posicao indisponivel. Tente novamente\n");
        else if (posicao_permitida(tabuleiro, ordem, lin, col, jogador.peca) == false) {

            // Se a formacao é a proibida mas o jogador ja iria ganhar posicionando ali, permite-se que ele posicione ali
            tabuleiro[lin][col] = jogador.peca;
            if (ganhou_linhas_ou_colunas(tabuleiro, ordem, jogador.peca) ||
                ganhou_diagonais_principais(tabuleiro, ordem, jogador.peca) ||
                ganhou_diagonais_secundarias(tabuleiro, ordem, jogador.peca))
                return;
            // Se ele já não fosse ganhar direto posicionando ali na posicao proibida, não se permite que ele posicione ali
            tabuleiro[lin][col] = ' ';
            printf("Posicao nao permitida. Tente novamente\n");
        } else
            break;
    }
    tabuleiro[lin][col] = jogador.peca;
}

bool posicao_permitida(char **tabuleiro, int ordem, int lin, int col, char peca) {
    int i, j;
    tabuleiro[lin][col] = peca;
    int qtd_seguidas;
    bool verificar_formacao = false;

    //   x o o   |   o o x
    //  o        |        o
    // o         |         o
    for (i = 0; i < ordem - 2; i++) {     // Da primeira a antipenultima linha
        for (j = 2; j < ordem - 2; j++) { // Da terceira a antipenultima coluna
            if (tabuleiro[i][j] == peca) {
                if (tabuleiro[i][j + 1] == peca && tabuleiro[i][j + 2] == peca &&
                    tabuleiro[i + 1][j - 1] == peca && tabuleiro[i + 2][j - 2] == peca) {

                    tabuleiro[lin][col] = ' ';
                    return false;
                } else if (tabuleiro[i][j - 1] == peca && tabuleiro[i][j - 2] == peca &&
                           tabuleiro[i + 1][j + 1] == peca && tabuleiro[i + 2][j + 2] == peca) {

                    tabuleiro[lin][col] = ' ';
                    return false;
                }
            }
        }
    }

    // o        |         o
    //  o       |        o
    //   x o o  |   o o x
    for (i = 2; i < ordem; i++) {         // Da terceira a ultima linha
        for (j = 2; j < ordem - 2; j++) { // Da terceira a antipenultima coluna
            if (tabuleiro[i][j] == peca) {
                if (tabuleiro[i][j + 1] == peca && tabuleiro[i][j + 2] == peca &&
                    tabuleiro[i - 1][j - 1] == peca && tabuleiro[i - 2][j - 2] == peca) {

                    tabuleiro[lin][col] = ' ';
                    return false;
                } else if (tabuleiro[i][j - 1] == peca && tabuleiro[i][j - 2] == peca &&
                           tabuleiro[i - 1][j + 1] == peca && tabuleiro[i - 2][j + 2] == peca) {

                    tabuleiro[lin][col] = ' ';
                    return false;
                }
            }
        }
    }

    // o      |      o
    // o      |    o
    // x      |  x
    //   o    |  o
    //     o  |  o
    for (i = 2; i < ordem - 2; i++) {     // Da terceira a antipenultima linha
        for (j = 0; j < ordem - 2; j++) { // Da primeira a antipenultima coluna
            if (tabuleiro[i][j] == peca) {
                if (tabuleiro[i - 1][j] == peca && tabuleiro[i - 2][j] == peca &&
                    tabuleiro[i + 1][j + 1] == peca && tabuleiro[i + 2][j + 2] == peca) {

                    tabuleiro[lin][col] = ' ';
                    return false;
                } else if (tabuleiro[i + 1][j] == peca && tabuleiro[i + 2][j] == peca &&
                           tabuleiro[i - 1][j + 1] == peca && tabuleiro[i - 2][j + 2] == peca) {

                    tabuleiro[lin][col] = ' ';
                    return false;
                }
            }
        }
    }

    //     o  |  o
    //     o  |    o
    //     x  |      x
    //   o    |      o
    // o      |      o
    for (i = 2; i < ordem - 2; i++) { // Da terceira a antipenultima linha
        for (j = 2; j < ordem; j++) { // Da terceira a ultima coluna
            if (tabuleiro[i][j] == peca) {
                if (tabuleiro[i - 1][j] == peca && tabuleiro[i - 2][j] == peca &&
                    tabuleiro[i + 1][j - 1] == peca && tabuleiro[i + 2][j - 2] == peca) {

                    tabuleiro[lin][col] = ' ';
                    return false;
                } else if (tabuleiro[i + 1][j] == peca && tabuleiro[i + 2][j] == peca &&
                           tabuleiro[i - 1][j - 1] == peca && tabuleiro[i - 2][j - 2] == peca) {

                    tabuleiro[lin][col] = ' ';
                    return false;
                }
            }
        }
    }

    return true;
}

void imprimir_tabuleiro(char **tabuleiro, int dimensao) {
    int i, j;
    // Imprime os indices das linhas
    if (dimensao < 9) {
        for (i = 0; i < dimensao; i++)
            printf("%d   ", i);
        printf("\n");
    } else {
        for (i = 0; i < 10; i++)
            printf("%d   ", i);
        for (; i < dimensao; i++)
            printf("%d  ", i);
        printf("\n");
    }
    // Imprime da primeira à penultima linha da matriz
    for (i = 0; i < dimensao - 1; i++) {
        for (j = 0; j < dimensao - 1; j++) {
            printf("%c---", tabuleiro[i][j]);
        }
        printf("%c %d\n", tabuleiro[i][j], i);
        // Imprime o separador de linha abaixo
        for (int k = 0; k < dimensao; k++)
            printf("|   ");
        printf("\n");
    }
    // Imprime a última linha da matriz, que não terá o separador de linha abaixo
    for (j = 0; j < dimensao - 1; j++) {
        printf("%c---", tabuleiro[dimensao - 1][j]);
    }
    printf("%c %d\n", tabuleiro[dimensao - 1][j], i);
}

void reiniciar_tabuleiro(char **tabuleiro, int ordem) {
    short int i, j;
    for (i = 0; i < ordem; i++) {
        for (j = 0; j < ordem; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}

void destruir_tabuleiro(char **tabuleiro, int dimensao) {
    for (int i; i < dimensao; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);
}

bool ganhou_linhas_ou_colunas(char **tabuleiro, int dimensao, char peca) {
    unsigned short int n_pecas_lin = 0, n_pecas_col = 0, i, j;
    for (i = 0; i < dimensao; i++) {
        for (j = 0; j < dimensao; j++) {
            // Linhas
            if (tabuleiro[i][j] == peca) {
                n_pecas_lin++;
                if (n_pecas_lin == 5)
                    return true;
            } else {
                n_pecas_lin = 0;
            }
            // Colunas
            if (tabuleiro[j][i] == peca) {
                n_pecas_col++;
                if (n_pecas_col == 5)
                    return true;
            } else {
                n_pecas_col = 0;
            }
        }
        n_pecas_col = 0;
        n_pecas_lin = 0;
    }
    return false;
}

bool ganhou_diagonais_principais(char **tabuleiro, int ordem, char peca) {
    int i, j, k, qtd_min = 5;
    int n_pecas_abaixo = 0, n_pecas_acima = 0, n_pecas = 0;
    for (k = qtd_min - 1; k < ordem; k++) {
        for (i = ordem - 1 - k, j = 0; i < ordem; i++, j++) {
            if (i == j) {
                // Diagonal principal do meio
                if (tabuleiro[i][j] == peca) {
                    n_pecas++;
                    if (n_pecas == 5)
                        return true;
                } else
                    n_pecas = 0;
            } else {
                // Diagonais principais abaixo
                if (tabuleiro[i][j] == peca) {
                    n_pecas_abaixo++;
                    if (n_pecas_abaixo == 5)
                        return true;
                } else
                    n_pecas_abaixo = 0;
                // Diagonais principais acima
                if (tabuleiro[j][i] == peca) {
                    n_pecas_acima++;
                    if (n_pecas_acima == 5)
                        return true;
                } else
                    n_pecas_acima = 0;
            }
        }
        n_pecas_abaixo = 0;
        n_pecas_acima = 0;
    }
    return false;
}

bool ganhou_diagonais_secundarias(char **tabuleiro, int ordem, char peca) {
    int i, j, k, qtd_min = 5;
    int n_pecas = 0;
    // Iterar diagonais secundárias acima do meio, da esquerda para direita
    for (k = qtd_min - 1; k < ordem - 1; k++) {
        for (i = k, j = 0; i >= 0; i--, j++) {
            if (tabuleiro[i][j] == peca) {
                n_pecas++;
                if (n_pecas == 5)
                    return true;
            } else
                n_pecas = 0;
        }
        n_pecas = 0;
    }
    // Iterar diagonais secundárias abaixo do meio e no meio, da esquerda para direita
    for (k = ordem - 1; k >= qtd_min - 1; k--) {
        for (i = ordem - 1, j = ordem - 1 - k; i >= ordem - 1 - k; i--, j++) {
            if (tabuleiro[i][j] == peca) {
                n_pecas++;
                if (n_pecas == qtd_min)
                    return true;
            } else
                n_pecas = 0;
        }
        n_pecas = 0;
    }
    return false;
}

bool tabuleiro_cheio(char **tabuleiro, int ordem) {
    int i, j;
    for (i = 0; i < ordem; i++) {
        for (j = 0; j < ordem; j++) {
            if (tabuleiro[i][j] == ' ')
                return false;
        }
    }
    return true;
}

char avaliar_tabuleiro(char **tabuleiro, int ordem) {
    if (ganhou_linhas_ou_colunas(tabuleiro, ordem, 'P')) {
        printf("Encontrada linha ou coluna com 5 pecas 'P' consecutivas!\n");
        return 'P';
    } else if (ganhou_diagonais_principais(tabuleiro, ordem, 'P') || ganhou_diagonais_secundarias(tabuleiro, ordem, 'P')) {
        printf("Encontrada diagonal com 5 pecas 'P' consecutivas!\n");
        return 'P';
    } else if (ganhou_linhas_ou_colunas(tabuleiro, ordem, 'B')) {
        printf("Encontrada linha ou coluna com 5 pecas 'B' consecutivas!\n");
        return 'B';
    } else if (ganhou_diagonais_principais(tabuleiro, ordem, 'B') || ganhou_diagonais_secundarias(tabuleiro, ordem, 'B')) {
        printf("Encontrada diagonal com 5 pecas 'B' consecutivas!\n");
        return 'B';
    } else if (tabuleiro_cheio(tabuleiro, ordem)) {
        return 'E'; // Empate
    } else {
        return 'C'; // Continuar partida
    }
}

void capturar_pecas_linhas_colunas(char **tabuleiro, int ordem, PlacarCapturas *placar, char capturador, char capturado) {

    Remocoes remocoes_lin;
    Remocoes remocoes_col;
    int *qtd_capturas;
    if (capturador == 'P') {
        qtd_capturas = &placar->jogadorP;
    } else {
        qtd_capturas = &placar->jogadorB;
    }

    short int i, j, k_lin = 0, k_col = 0;
    bool remover_lin = false, remover_col = false;
    for (i = 0; i < ordem; i++) {
        for (j = 0; j < ordem; j++) {
            // Linhas
            if (tabuleiro[i][j] == capturador && remover_lin == false) {
                remover_lin = true;
            } else if (remover_lin) {
                if (tabuleiro[i][j] == capturado && k_lin < 2) {
                    remocoes_lin.i[k_lin] = i;
                    remocoes_lin.j[k_lin] = j;
                    k_lin++;
                } else if (tabuleiro[i][j] == capturador && k_lin == 2) {
                    for (int c = 0; c < k_lin; c++)
                        tabuleiro[remocoes_lin.i[c]][remocoes_lin.j[c]] = ' ';
                    *qtd_capturas += 1;
                    k_lin = 0;
                } else {
                    remover_lin = false;
                    k_lin = 0;
                }
            }
            // Colunas
            if (tabuleiro[j][i] == capturador && remover_col == false) {
                remover_col = true;
            } else if (remover_col) {
                if (tabuleiro[j][i] == capturado && k_col < 2) {
                    remocoes_col.i[k_col] = j;
                    remocoes_col.j[k_col] = i;
                    k_col++;
                } else if (tabuleiro[j][i] == capturador && k_col == 2) {
                    for (int c = 0; c < k_col; c++)
                        tabuleiro[remocoes_col.i[c]][remocoes_col.j[c]] = ' ';
                    *qtd_capturas += 1;
                    k_col = 0;
                } else {
                    remover_col = false;
                    k_col = 0;
                }
            }
        }
        remover_lin = false;
        k_lin = 0;
        remover_col = false;
        k_col = 0;
    }
}

void capturar_pecas_diagonais_principais(char **tabuleiro, int ordem, PlacarCapturas *placar, char capturador, char capturado) {

    Remocoes remocoes;
    int *qtd_capturas;
    if (capturador == 'P') {
        qtd_capturas = &placar->jogadorP;
    } else {
        qtd_capturas = &placar->jogadorB;
    }
    bool remover = false;
    short int n = 0;

    int i, j, k, qtd_min = 4;
    // Diagonais principais acima do meio, da esquerda para direita
    for (k = qtd_min - 1; k < ordem - 1; k++) {
        for (i = ordem - 1 - k, j = 0; i < ordem; i++, j++) {
            if (tabuleiro[i][j] == capturador && remover == false) {
                remover = true;
            } else if (remover) {
                if (tabuleiro[i][j] == capturado && n < 2) {
                    remocoes.i[n] = i;
                    remocoes.j[n] = j;
                    n++;
                } else if (tabuleiro[i][j] == capturador && n == 2) {
                    for (int c = 0; c < n; c++)
                        tabuleiro[remocoes.i[c]][remocoes.j[c]] = ' ';
                    *qtd_capturas += 1;
                    n = 0;
                } else {
                    remover = false;
                    n = 0;
                }
            }
        }
        remover = false;
        n = 0;
    }

    // Diagonais principais abaixo do meio e no meio, da esquerda para direita
    for (k = ordem - 1; k >= qtd_min - 1; k--) {
        for (i = 0, j = ordem - 1 - k; i <= k; i++, j++) {
            if (tabuleiro[i][j] == capturador && remover == false) {
                remover = true;
            } else if (remover) {
                if (tabuleiro[i][j] == capturado && n < 2) {
                    remocoes.i[n] = i;
                    remocoes.j[n] = j;
                    n++;
                } else if (tabuleiro[i][j] == capturador && n == 2) {
                    for (int c = 0; c < n; c++)
                        tabuleiro[remocoes.i[c]][remocoes.j[c]] = ' ';
                    *qtd_capturas += 1;
                    n = 0;
                } else {
                    remover = false;
                    n = 0;
                }
            }
        }
        remover = false;
        n = 0;
    }
}

void capturar_pecas_diagonais_secundarias(char **tabuleiro, int ordem, PlacarCapturas *placar, char capturador, char capturado) {

    Remocoes remocoes;
    int *qtd_capturas;
    if (capturador == 'P') {
        qtd_capturas = &placar->jogadorP;
    } else {
        qtd_capturas = &placar->jogadorB;
    }
    bool remover = false;
    short int n = 0;

    int i, j, k, qtd_min = 4;
    // Diagonais secundárias acima do meio, da esquerda para direita
    for (k = qtd_min - 1; k < ordem - 1; k++) {
        for (i = k, j = 0; i >= 0; i--, j++) {
            if (tabuleiro[i][j] == capturador && remover == false) {
                remover = true;
            } else if (remover) {
                if (tabuleiro[i][j] == capturado && n < 2) {
                    remocoes.i[n] = i;
                    remocoes.j[n] = j;
                    n++;
                } else if (tabuleiro[i][j] == capturador && n == 2) {
                    for (int c = 0; c < n; c++)
                        tabuleiro[remocoes.i[c]][remocoes.j[c]] = ' ';
                    *qtd_capturas += 1;
                    n = 0;
                } else {
                    remover = false;
                    n = 0;
                }
            }
        }
        remover = false;
        n = 0;
    }
    // Diagonais secundárias abaixo do meio e no meio, da esquerda para direita
    for (k = ordem - 1; k >= qtd_min - 1; k--) {
        for (i = ordem - 1, j = ordem - 1 - k; i >= ordem - 1 - k; i--, j++) {
            if (tabuleiro[i][j] == capturador && remover == false) {
                remover = true;
            } else if (remover) {
                if (tabuleiro[i][j] == capturado && n < 2) {
                    remocoes.i[n] = i;
                    remocoes.j[n] = j;
                    n++;
                } else if (tabuleiro[i][j] == capturador && n == 2) {
                    for (int c = 0; c < n; c++)
                        tabuleiro[remocoes.i[c]][remocoes.j[c]] = ' ';
                    *qtd_capturas += 1;
                    n = 0;
                } else {
                    remover = false;
                    n = 0;
                }
            }
        }
        remover = false;
        n = 0;
    }
}

void capturar_pecas(char **tabuleiro, int ordem, PlacarCapturas *placar) {
    capturar_pecas_linhas_colunas(tabuleiro, ordem, placar, 'P', 'B');
    capturar_pecas_linhas_colunas(tabuleiro, ordem, placar, 'B', 'P');
    capturar_pecas_diagonais_principais(tabuleiro, ordem, placar, 'P', 'B');
    capturar_pecas_diagonais_principais(tabuleiro, ordem, placar, 'B', 'P');
    capturar_pecas_diagonais_secundarias(tabuleiro, ordem, placar, 'P', 'B');
    capturar_pecas_diagonais_secundarias(tabuleiro, ordem, placar, 'B', 'P');
}

void imprimir_placar_capturas(PlacarCapturas placar, Jogador jogador1, Jogador jogador2) {
    if (jogador1.peca == 'P')
        printf("Capturas: %s (%c) %d x %d %s (%c)\n",
               jogador1.nome, jogador1.peca, placar.jogadorP, placar.jogadorB, jogador2.nome, jogador2.peca);
    else
        printf("Capturas: %s (%c) %d x %d %s (%c)\n",
               jogador1.nome, jogador1.peca, placar.jogadorB, placar.jogadorP, jogador2.nome, jogador2.peca);
}