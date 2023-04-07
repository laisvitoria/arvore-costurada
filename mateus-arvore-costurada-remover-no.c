#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef enum {NoEsquerdo, NoDireito, NoPai, NoRaiz} DIRECAO;

typedef struct {
    TIPOCHAVE chave;
} ITEM;

typedef struct estrutura {
    ITEM item;
    struct estrutura *esq;
    struct estrutura *dir;
    struct estrutura *pai;
    DIRECAO direcao;
    struct estrutura *suc; // ponteiro para o sucessor em ordem de percurso
    struct estrutura *pred; // ponteiro para o predecessor em ordem de percurso
} ARVORE_COSTURADA;

ARVORE_COSTURADA* encontraPredecessor(ARVORE_COSTURADA *no) {
    if (no == NULL) {
        return NULL;
    }
    ARVORE_COSTURADA *atual = no->esq;
    while(atual != NULL && atual->dir != NULL) {
        atual = atual->dir;
    }
    return atual;
}

ARVORE_COSTURADA* encontraSucessor(ARVORE_COSTURADA *no) {
    if (no == NULL) {
        return NULL;
    }
    ARVORE_COSTURADA *atual = no->dir;
    while(atual != NULL && atual->esq != NULL) {
        atual = atual->esq;
    }
    return atual;
}

ARVORE_COSTURADA* criarNo(ITEM item) {
    ARVORE_COSTURADA *novo = (ARVORE_COSTURADA*) malloc(sizeof(ARVORE_COSTURADA));
    novo->item = item;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    novo->direcao = NoRaiz;
    novo->suc = NULL;
    novo->pred = NULL;
    return novo;
}



ARVORE_COSTURADA* inserePreOrdem(ARVORE_COSTURADA *raiz, ITEM item, ARVORE_COSTURADA* pai, DIRECAO direcao) {
    if(raiz == NULL) {
        ARVORE_COSTURADA *novo = criarNo(item);
        novo->pai = pai;
        novo->direcao = direcao;
        return novo; // retorna a raiz da árvore
    }
    ARVORE_COSTURADA *atual = raiz;
    while(true) {
        if(item.chave < atual->item.chave) {
            ARVORE_COSTURADA *esquerda = atual->esq;
            if(esquerda == NULL) {
                esquerda = criarNo(item);
                esquerda->pai = atual;
                esquerda->direcao = NoEsquerdo;
                atual->esq = esquerda;
                esquerda->pred = encontraPredecessor(esquerda);
                return raiz; // retorna a raiz da árvore
            }
            atual = esquerda;
        } else {
            ARVORE_COSTURADA *direita = atual->dir;
            if(direita == NULL) {
                direita = criarNo(item);
                direita->pai = atual;
                direita->direcao = NoDireito;
                atual->dir = direita;
                direita->suc = encontraSucessor(direita);
                return raiz; // retorna a raiz da árvore
            }
            atual = direita;
        }
    }
}

ARVORE_COSTURADA* inserePosOrdem(ARVORE_COSTURADA *raiz, ITEM item, ARVORE_COSTURADA* pai, DIRECAO direcao) {
    if (raiz == NULL) {
        ARVORE_COSTURADA *novo = criarNo(item);
        novo->pai = pai;
        novo->direcao = direcao;
        return novo;
    }

    ARVORE_COSTURADA *atual = raiz;
    while (true) {
        if (item.chave > atual->item.chave) {
            ARVORE_COSTURADA *direita = atual->dir;
            if (direita == NULL) {
                direita = criarNo(item);
                direita->pai = atual;
                direita->direcao = NoDireito;
                atual->dir = direita;
                direita->suc = encontraSucessor(direita);
                break;
            }
            atual = direita;
        } else {
            ARVORE_COSTURADA *esquerda = atual->esq;
            if (esquerda == NULL) {
                esquerda = criarNo(item);
                esquerda->pai = atual;
                esquerda->direcao = NoEsquerdo;
                atual->esq = esquerda;
                esquerda->pred = encontraPredecessor(esquerda);
                break;
            }
            atual = esquerda;
        }
    }
    return atual;
}

ARVORE_COSTURADA* removerNo(ARVORE_COSTURADA *raiz, TIPOCHAVE chave) {
    if (raiz == NULL) {
        return NULL;
    }

    // procurar o nó a ser removido
    ARVORE_COSTURADA *atual = raiz;
    while (atual != NULL && atual->item.chave != chave) {
        if (chave < atual->item.chave) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }

    if (atual == NULL) {
        // o nó não foi encontrado
        return raiz;
    }

    if (atual->esq == NULL && atual->dir == NULL) {
        // caso 1: nó sem filhos
        if (atual->pai != NULL) {
            if (atual->direcao == NoEsquerdo) {
                atual->pai->esq = NULL;
            } else {
                atual->pai->dir = NULL;
            }
        } else {
            // o nó a ser removido é a raiz da árvore
            raiz = NULL;
        }
        free(atual);
    } else if (atual->esq == NULL || atual->dir == NULL) {
        // caso 2: nó com um filho
        ARVORE_COSTURADA *filho = atual->esq != NULL ? atual->esq : atual->dir;
        if (atual->pai != NULL) {
            if (atual->direcao == NoEsquerdo) {
                atual->pai->esq = filho;
            } else {
                atual->pai->dir = filho;
            }
            filho->pai = atual->pai;
            filho->direcao = atual->direcao;
        } else {
            // o nó a ser removido é a raiz da árvore
            raiz = filho;
            filho->pai = NULL;
            filho->direcao = NoRaiz;
        }
        free(atual);
    } else {
        // caso 3: nó com dois filhos
        ARVORE_COSTURADA *sucessor = encontraSucessor(atual);
        atual->item = sucessor->item;
        removerNo(raiz, sucessor->item.chave);
    }

    return raiz;
}

void destruir(ARVORE_COSTURADA *raiz) {
    if(raiz != NULL) {
        destruir(raiz->esq);
        destruir(raiz->dir);
        free(raiz);
    }
}

void percorrerPreOrdem(ARVORE_COSTURADA *raiz) {
    if (raiz == NULL) {
        return;
    }

    printf("%d ", raiz->item.chave);
    percorrerPreOrdem(raiz->esq);
    percorrerPreOrdem(raiz->dir);
}

void percorrerPosOrdem(ARVORE_COSTURADA *raiz) {
    if (raiz == NULL) {
        return;
    }

    percorrerPosOrdem(raiz->esq);
    percorrerPosOrdem(raiz->dir);
    printf("%d ", raiz->item.chave);
}

void buscarPreOrdem(ARVORE_COSTURADA *raiz, ITEM no) {
    if (raiz == NULL) {
      printf("No nao encontrado %d \n", no);
      return;
    }
    if (no.chave == raiz->item.chave) {
      printf("No encontrado %d \n", no.chave);
      return raiz->item.chave;
    }
    if(no.chave < raiz->item.chave){
      buscarPreOrdem(raiz->esq, no);
    } else {
      buscarPreOrdem(raiz->dir, no);
    }
}


int main() {
    ARVORE_COSTURADA *raiz = NULL;

    int numeros[] = {2, 4, 6, 8, 10};
    int num_numeros = sizeof(numeros) / sizeof(numeros[0]);
    ITEM itemBuscado;

    for (int i = 0; i < num_numeros; i++) {
        ITEM item;
        item.chave = numeros[i];
        raiz = inserePreOrdem(raiz, item, NULL, NoRaiz);
    }

    percorrerPreOrdem(raiz);
    printf("\n");
    itemBuscado.chave = 1;
    buscarPreOrdem(raiz, itemBuscado);
    itemBuscado.chave = 6;
    buscarPreOrdem(raiz, itemBuscado);
    itemBuscado.chave = 8;
    buscarPreOrdem(raiz, itemBuscado);

    destruir(raiz);
    return 0;
}
