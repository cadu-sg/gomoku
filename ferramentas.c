#include "ferramentas.h"
#include <stdio.h>
#include <stdlib.h>

void limpar_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int int_aleatorio(int min, int max) {
    return min + (rand() % (max - min + 1));
}

int *novo_vetor(unsigned int tam) {
    return (int *)malloc(tam * sizeof(int));
}
