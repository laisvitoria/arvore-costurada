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

ARVORE_COSTURADA *inserir(ARVORE_COSTURADA *raiz, ITEM item) {
    ARVORE_COSTURADA *novoNo = criarNo(item);
    ARVORE_COSTURADA *noAtual = raiz;
    ARVORE_COSTURADA *noAnterior = NULL;
    bool encontrouFolha = false;

    if (raiz == NULL) {
        return novoNo;
    }

    while (noAtual != NULL) {
        noAnterior = noAtual;
        if (item.chave < noAtual->item.chave) {
            if (noAtual->costuraEsquerda) {
                novoNo->esq = noAtual->esq;
                noAtual->esq = novoNo;
                noAtual->costuraEsquerda = false;
                encontrouFolha = true;
            } else {
                noAtual = noAtual->esq;
            }
        } else if (item.chave > noAtual->item.chave) {
            if (noAtual->costuraDireita) {
                novoNo->dir = noAtual->dir;
                noAtual->dir = novoNo;
                noAtual->costuraDireita = false;
                encontrouFolha = true;
            } else {
                noAtual = noAtual->dir;
            }
        } else {
            // Chave já existe na árvore, não faz nada
            free(novoNo);
            return raiz;
        }
    }

    if (!encontrouFolha) {
        if (item.chave < noAnterior->item.chave) {
            novoNo->costuraEsquerda = true;
            novoNo->esq = noAnterior->esq;
            noAnterior->esq = novoNo;
        } else {
            novoNo->costuraDireita = true;
            novoNo->dir = noAnterior->dir;
            noAnterior->dir = novoNo;
        }
    }

    return raiz;
}
void percorrerEmOrdem(ARVORE_COSTURADA *raiz) {
    ARVORE_COSTURADA *atual = raiz;
    ARVORE_COSTURADA *anterior = NULL;
    while (atual != NULL) {
        if (!atual->costuraEsquerda) {
            anterior = atual->esq;
            while (!anterior->costuraDireita) {
                anterior = anterior->dir;
            }
            printf("%d ", atual->item.chave);
            atual = anterior->dir;
        } else {
            printf("%d ", atual->item.chave);
            atual = atual->dir;
        }
    }
}

