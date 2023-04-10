#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
    // char valor[100];
} ITEM;

typedef struct estrutura ARVORE_COSTURADA;

struct estrutura {
    ITEM item;
    ARVORE_COSTURADA *esq;
    ARVORE_COSTURADA *dir;
    bool costuraEsquerda;
    bool costuraDireita;
};

ARVORE_COSTURADA *criarNo(ITEM item) {
    ARVORE_COSTURADA *no = (ARVORE_COSTURADA *) malloc(sizeof(ARVORE_COSTURADA));
    no->item = item;
    no->esq = NULL;
    no->dir = NULL;
    no->costuraEsquerda = false;
    no->costuraDireita = false;
    return no;
}
