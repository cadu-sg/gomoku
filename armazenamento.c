#include "armazenamento.h"
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void salvar_jogo(Jogo jogo) {
    // Abrir o arquivo
    FILE *file = fopen("./saves/jogo.save", "w");
    if (file == NULL) {
        printf("Houve um erro ao salvar o jogo\n");
        return;
    }

    // Gravar os dados dos jogadores
    if (fprintf(file, "%s\n%c\n%d\n%s\n%c\n%d\n%d\n",
                jogo.jogador1.nome, jogo.jogador1.peca, jogo.jogador1.qtd_vitorias,
                jogo.jogador2.nome, jogo.jogador2.peca, jogo.jogador2.qtd_vitorias,
                jogo.ordem) < 0) {
        printf("Houve um erro ao salvar o jogo\n");
        fclose(file);
        return;
    };

    // Fechar o arquivo
    fclose(file);
}

bool existem_saves() {
    DIR *d = opendir("saves");
    if (d) {
        // O diretório saves existe
        struct dirent *dir;
        // Mas há saves ali?
        while ((dir = readdir(d)) != NULL) {
            char *ext = strrchr(dir->d_name, '.');
            if (strcmp(ext, ".save") == 0) {
                closedir(d);
                return true;
            }
        }
        closedir(d);
        return false;
    } else if (ENOENT == errno) {
        // A pasta saves não existe
        return false;
    } else {
        // opendir() falhou
        return false;
    }
}

void listar_saves() {
    DIR *d = opendir("./saves/");
    struct dirent *dir;
    if (d) {
        printf("Saves:\n");
        while ((dir = readdir(d)) != NULL) {
            // Obtém a extensão do arquivo
            char *ext = strrchr(dir->d_name, '.');
            // Imprimir se for igual a .save
            if (strcmp(ext, ".save") == 0)
                printf("%s\n", dir->d_name);
        }
        closedir(d);
        printf("\n");
    }
}

Jogo carregar_jogo() {

    Jogo jogo;

    // Abrir o arquivo
    FILE *file = fopen("./saves/jogo.save", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
    }

    // Gravar os dados dos jogadores
    if (fscanf(file, "%s\n%c\n%d\n%s\n%c\n%d\n%d\n",
               jogo.jogador1.nome, &jogo.jogador1.peca, &jogo.jogador1.qtd_vitorias,
               jogo.jogador2.nome, &jogo.jogador2.peca, &jogo.jogador2.qtd_vitorias,
               &jogo.ordem) < 0) {
        printf("Houve um erro ao gravar no arquivo\n");
    };

    // Fechar o arquivo
    fclose(file);

    return jogo;
}