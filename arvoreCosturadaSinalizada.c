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
ARVORE_COSTURADA *alterarItem(ARVORE_COSTURADA *raiz, TIPOCHAVE chave, ITEM novoItem) {
    ARVORE_COSTURADA *noAtual = raiz;
    ARVORE_COSTURADA *noAnterior = NULL;

    while (noAtual != NULL) {
        if (chave < noAtual->item.chave) {
            if (noAtual->costuraEsquerda) {
                // Não há filho esquerdo, item não encontrado
                return raiz;
            } else {
                noAnterior = noAtual;
                noAtual = noAtual->esq;
            }
        } else if (chave > noAtual->item.chave) {
            if (noAtual->costuraDireita) {
                // Não há filho direito, item não encontrado
                return raiz;
            } else {
                noAnterior = noAtual;
                noAtual = noAtual->dir;
            }
        } else {
            // Chave encontrada, altera o item e retorna a raiz da árvore
            noAtual->item = novoItem;
            if (noAnterior == NULL) {
                return noAtual;
            } else if (chave < noAnterior->item.chave) {
                // Ajusta a costura esquerda do nó anterior
                if (noAtual->esq == NULL) {
                    noAtual->costuraEsquerda = true;
                    noAtual->esq = noAnterior;
                }
                if (noAnterior->costuraEsquerda) {
                    noAnterior->esq = noAtual;
                }
                noAnterior->costuraEsquerda = false;
                noAnterior->esq = noAtual;
            } else {
                // Ajusta a costura direita do nó anterior
                if (noAtual->dir == NULL) {
                    noAtual->costuraDireita = true;
                    noAtual->dir = noAnterior->dir;
                }
                if (noAnterior->costuraDireita) {
                    noAnterior->dir = noAtual;
                }
                noAnterior->costuraDireita = false;
                noAnterior->dir = noAtual;
            }
            return (noAnterior == NULL) ? noAtual : raiz;
        }
    }

    // Chave não encontrada, não faz nada
    return raiz;
}
void imprimir(ARVORE_COSTURADA *raiz) {
    if (raiz == NULL) {
        return;
    }

    ARVORE_COSTURADA *atual = raiz;

    while (atual != NULL) {
        if (atual->esq == NULL) {
            printf("%d ", atual->item.chave);
            atual = atual->dir;
        } else {
            ARVORE_COSTURADA *predecessor = atual->esq;

            while (predecessor->dir != NULL && predecessor->dir != atual) {
                predecessor = predecessor->dir;
            }

            if (predecessor->dir == NULL) {
                predecessor->dir = atual;
                atual = atual->esq;
            } else {
                predecessor->dir = NULL;
                printf("%d ", atual->item.chave);
                atual = atual->dir;
            }
        }
    }
}
/*
Essa função utiliza o algoritmo de Morris para percorrer a árvore de forma inordenada,
utilizando as costuras esquerda e direita para percorrer os nós em ordem.
A ideia é que, ao chegar em um nó com costura esquerda, o algoritmo encontra o predecessor 
desse nó (o maior elemento da subárvore esquerda) e cria uma costura direita a partir dele para 
voltar ao nó atual posteriormente. 
Quando encontra um nó com costura direita, o algoritmo imprime o valor do nó atual e segue para o nó da direita.
Dessa forma, a função consegue percorrer a árvore em ordem sem utilizar uma pilha ou recursão.
*/

