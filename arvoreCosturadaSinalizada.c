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
            if (noAnterior->esq != NULL) {
                noAnterior->esq->dir = novoNo;
            }
            noAnterior->esq = novoNo;
        } else {
            novoNo->costuraDireita = true;
            novoNo->dir = noAnterior->dir;
            if (noAnterior->dir != NULL) {
                noAnterior->dir->esq = novoNo;
            }
            noAnterior->dir = novoNo;
        }
    }

    return raiz;
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

            // Ajusta a costura esquerda do nó anterior, se necessário
            if (noAtual->esq == NULL && !noAtual->costuraEsquerda && noAnterior != NULL && chave < noAnterior->item.chave) {
                noAnterior->costuraEsquerda = true;
                noAnterior->esq = noAtual->esq;
            }

            // Ajusta a costura direita do nó anterior, se necessário
            if (noAtual->dir == NULL && !noAtual->costuraDireita && noAnterior != NULL && chave > noAnterior->item.chave) {
                noAnterior->costuraDireita = true;
                noAnterior->dir = noAtual->dir;
            }

            return raiz;
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

ARVORE_COSTURADA *remover(ARVORE_COSTURADA *raiz, TIPOCHAVE chave) {
    ARVORE_COSTURADA *noAtual = raiz;
    ARVORE_COSTURADA *noAnterior = NULL;

    // Localiza o nó a ser removido
    while (noAtual != NULL && noAtual->item.chave != chave) {
        noAnterior = noAtual;
        if (chave < noAtual->item.chave) {
            if (noAtual->costuraEsquerda) {
                // Não há filho esquerdo, item não encontrado
                return raiz;
            } else {
                noAtual = noAtual->esq;
            }
        } else {
            if (noAtual->costuraDireita) {
                // Não há filho direito, item não encontrado
                return raiz;
            } else {
                noAtual = noAtual->dir;
            }
        }
    }

    // Verifica se o nó foi encontrado
    if (noAtual == NULL) {
        return raiz;
    }

    // Caso 1: o nó a ser removido é uma folha
    if (noAtual->esq == NULL && noAtual->dir == NULL) {
        if (noAnterior == NULL) {
            // O nó a ser removido é a raiz da árvore
            free(noAtual);
            return NULL;
        }
        if (noAtual == noAnterior->esq) {
            // O nó a ser removido é o filho esquerdo do nó anterior
            noAnterior->costuraEsquerda = true;
            noAnterior->esq = noAtual->esq;
        } else {
            // O nó a ser removido é o filho direito do nó anterior
            noAnterior->costuraDireita = true;
            noAnterior->dir = noAtual->dir;
        }
        free(noAtual);
        return raiz;
    }

    // Caso 2: o nó a ser removido tem apenas um filho
    if (noAtual->esq == NULL || noAtual->dir == NULL) {
        ARVORE_COSTURADA *filho = (noAtual->esq != NULL) ? noAtual->esq : noAtual->dir;
        if (noAnterior == NULL) {
            // O nó a ser removido é a raiz da árvore
            free(noAtual);
            return filho;
        }
        if (noAtual == noAnterior->esq) {
            // O nó a ser removido é o filho esquerdo do nó anterior
            noAnterior->esq = filho;
        } else {
            // O nó a ser removido é o filho direito do nó anterior
            noAnterior->dir = filho;
        }
        free(noAtual);
        return raiz;
    }

    // Caso 3: o nó a ser removido tem dois filhos
    ARVORE_COSTURADA *sucessor = noAtual->dir;
    while (!sucessor->costuraEsquerda) {
        sucessor = sucessor->esq;
    }
    noAtual->item = sucessor->item;
    raiz = remover(raiz, sucessor->item.chave);
    return raiz;
}


void destruir(ARVORE_COSTURADA *raiz) {
    if (raiz != NULL) {
        destruir(raiz->esq);
        destruir(raiz->dir);
        free(raiz);
    }
}

int main() {
    ARVORE_COSTURADA *raiz = NULL;

    ITEM item1;
    item1.chave = 10;
    raiz = inserir(raiz, item1);

    ITEM item2;
    item2.chave = 5;
    raiz = inserir(raiz, item2);

    ITEM item3;
    item3.chave = 20;
    raiz = inserir(raiz, item3);

    printf("Árvore em ordem: ");
    imprimir(raiz);
    printf("\n");

    printf("Alteração do Item: ");
    ITEM novoItem;
    novoItem.chave = 9;
    raiz = alterarItem(raiz, 5, novoItem);
    printf("\n");
/*
    
    printf("Árvore em ordem após alteração: ");
    percorrerEmOrdem(&raiz);
    printf("\n");

    printf("Remoção de um item: ");
    ITEM novoItem;
    novoItem.chave = 5;
    remover(raiz, novoItem);
  
    printf("Destruição");
    destruir(raiz);
   */
    printf("Árvore em ordem: ");
    imprimir(raiz);
    printf("\n");

    printf("Remoção de um item: ");
    ITEM novoItemRemover;
    novoItemRemover.chave = 9;
    remover(raiz, novoItemRemover.chave);
    printf("\n");

    printf("Árvore em ordem pós-remoção: ");
    imprimir(raiz);
    printf("\n");

    return 0;
}
