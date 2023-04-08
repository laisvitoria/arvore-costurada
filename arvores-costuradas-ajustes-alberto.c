#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} ITEM;

/* typedef enum {NoEsquerdo, NoDireito, NoPai, NoRaiz} DIRECAO;

//Estrutura de Alberto para árvore binária

typedef struct {
    TIPOCHAVE chave;
//    char valor[100];
} ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *esq;
    struct estrutura *dir;
    struct estrutura *pai;
} ARVORE_BINARIA;
*/

typedef struct estrutura {
    ITEM item;
    struct estrutura *esq;
    struct estrutura *dir;
    struct estrutura *costura; // campo para a costura
} ARVORE_BINARIA;



ARVORE_BINARIA* criarNo(ITEM item) {
    ARVORE_BINARIA *novo = (ARVORE_BINARIA*) malloc(sizeof(ARVORE_BINARIA));
    novo->item = item;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->costura = NULL; // inicializa a costura como NULL
    return novo;
}

void inserir(ARVORE_BINARIA **raiz, ITEM item) {
    ARVORE_BINARIA *novo = criarNo(item);
    ARVORE_BINARIA *atual = *raiz;
    ARVORE_BINARIA *anterior = NULL;
    bool direita = false;
    
    while (atual != NULL) {
        anterior = atual;
        if (item.chave < atual->item.chave) {
            atual = atual->esq;
            direita = false;
        } else {
            atual = atual->dir;
            direita = true;
        }
    }
    
    if (anterior == NULL) { // a árvore está vazia
        *raiz = novo;
    } else if (direita) { // insere à direita do nó anterior
        novo->costura = anterior->costura;
        anterior->costura = novo;
        anterior->dir = novo;
    } else { // insere à esquerda do nó anterior
        novo->costura = anterior;
        novo->dir = anterior;
        anterior->esq = novo;
        if (anterior->costura != NULL && anterior->costura->dir == anterior) {
            anterior->costura->esq = novo;
        }
    }
}

ARVORE_BINARIA* inserirPreOrdem(ARVORE_BINARIA** raiz, ITEM item) {
    ARVORE_BINARIA *novo = criarNo(item);
    novo->costura = NULL; // adicionado

    if (*raiz == NULL) {
        *raiz = novo;
    } else if (item.chave < (*raiz)->item.chave) {
        (*raiz)->esq = inserirPreOrdem(&(*raiz)->esq, item);
        (*raiz)->esq->costura = *raiz;
    } else {
        (*raiz)->dir = inserirPreOrdem(&(*raiz)->dir, item);
        novo->costura = (*raiz)->costura;
        (*raiz)->costura = novo;
    }

    return *raiz;
}

void percorrerPreOrdem(ARVORE_BINARIA *raiz) {
    if (raiz == NULL) {
        return;
    }

    printf("%d ", raiz->item.chave);
    percorrerPreOrdem(raiz->esq);
    percorrerPreOrdem(raiz->dir);
}


void buscarPreOrdem(ARVORE_BINARIA* raiz, ITEM no) {
    if (raiz == NULL) {
        printf("Nó não encontrado %d\n", no.chave);
        return;
    }

    if (no.chave == raiz->item.chave) {
        printf("Nó encontrado %d\n", no.chave);
        return;
    }

    if (no.chave < raiz->item.chave) {
        if (raiz->esq != NULL && (raiz->esq->costura == NULL || raiz->esq->item.chave >= no.chave)) {
            buscarPreOrdem(raiz->esq, no);
        } else {
            printf("Nó não encontrado %d\n", no.chave);
        }
    } else {
        if (raiz->dir != NULL) {
            buscarPreOrdem(raiz->dir, no);
        } else {
            printf("Nó não encontrado %d\n", no.chave);
        }
    }
}

ARVORE_BINARIA* inserirPosOrdem(ARVORE_BINARIA** raiz, ITEM item) {
    ARVORE_BINARIA *novo = criarNo(item);
    novo->costura = NULL; // adicionado

    if (*raiz == NULL) {
        *raiz = novo;
    } else if (item.chave > (*raiz)->item.chave) {
        (*raiz)->dir = inserirPosOrdem(&(*raiz)->dir, item);
        (*raiz)->dir->costura = *raiz;
    } else {
        (*raiz)->esq = inserirPosOrdem(&(*raiz)->esq, item);
        novo->costura = (*raiz)->costura;
        (*raiz)->costura = novo;
        (*raiz)->esq->dir = *raiz;
        if ((*raiz)->costura != NULL && (*raiz)->costura->esq == *raiz) {
            (*raiz)->costura->dir = (*raiz)->esq;
        }
    }

    return *raiz;
}

void buscarPosOrdem(ARVORE_BINARIA* raiz, ITEM no) {
    if (raiz == NULL) {
        printf("Nó não encontrado %d\n", no.chave);
        return;
    }

    buscarPosOrdem(raiz->esq, no);
    buscarPosOrdem(raiz->dir, no);

    if (no.chave == raiz->item.chave) {
        printf("Nó encontrado %d\n", no.chave);
        return;
    }
}

void percorrerPosOrdem(ARVORE_BINARIA *raiz) {
    if (raiz == NULL) {
        return;
    }

    percorrerPosOrdem(raiz->esq);
    percorrerPosOrdem(raiz->dir);
    printf("%d ", raiz->item.chave);
}

void destruirArvore(ARVORE_BINARIA *raiz) {
    if (raiz == NULL) {
        return;
    }
    // Aplica o percorrimento pós-ordem
    destruirArvore(raiz->esq);
    destruirArvore(raiz->dir);
    // Remove a costura dos nós do lado direito da árvore
    if (raiz->costura != NULL && raiz->dir != NULL) {
        raiz->costura->esq = NULL;
    }
    free(raiz);
}
//////////////////////////////////////////////// COMPILAR /////////////////////////////////
ARVORE_BINARIA *busca(TIPOCHAVE ch, ARVORE_BINARIA *raiz) {
    if (raiz == NULL || raiz->item.chave == ch) {
        return raiz;
    }
    if (ch < raiz->item.chave) {
        return busca(ch, raiz->esq);
    }
    return busca(ch, raiz->dir);
}
//realiza uma busca normar e retorna a chave se achou
ARVORE_BINARIA *alterar_item(TIPOCHAVE ch, ITEM novo_item, ARVORE_BINARIA *raiz) {
    ARVORE_BINARIA *no = busca(ch, raiz);
    if (no != NULL) {
        no->item = novo_item;
    }
    return raiz;
}
// altera o item de acordo com o resultado da busca
ARVORE_BINARIA *reorganizar_costura(ARVORE_BINARIA *raiz) {
    ARVORE_BINARIA *p = raiz;
    while (p != NULL) {
        if (p->esq != NULL) {
            ARVORE_BINARIA *q = p->esq;
            while (q->dir != NULL) {
                q = q->dir;
            }
            q->costura = p;
        }
        p = p->dir;
    }
    return raiz;
}
// reorganiza as costuras da arvore para não ficar nada desorganizado



int main() {
    ARVORE_BINARIA *raiz = NULL;

    int numeros[] = {2, 4, 6, 8, 10};
    int num_numeros = sizeof(numeros) / sizeof(numeros[0]);
    ITEM itemBuscado;

    for (int i = 0; i < num_numeros; i++) {
        ITEM item;
        item.chave = numeros[i];
        inserirPreOrdem(&raiz, item);
    }
    ITEM item7 = { 14 };
    ITEM novo_item = { 5 };
    percorrerPreOrdem(raiz);
    printf("\n");
    itemBuscado.chave = 1;
    buscarPreOrdem(raiz, itemBuscado);
    itemBuscado.chave = 6;
    buscarPreOrdem(raiz, itemBuscado);
    itemBuscado.chave = 8;
    buscarPreOrdem(raiz, itemBuscado);

    destruirArvore(raiz);
    return 0;
}
/*
int main() {
    ARVORE_BINARIA *raiz = NULL;

    int numeros[] = {2, 4, 6, 8, 10};
    int num_numeros = sizeof(numeros) / sizeof(numeros[0]);
    ITEM itemBuscado;

    for (int i = 0; i < num_numeros; i++) {
        ITEM item;
        item.chave = numeros[i];
        inserirPreOrdem(&raiz, item);
    }

    percorrerPreOrdem(raiz);
    printf("\n");
    itemBuscado.chave = 1;
    buscarPreOrdem(raiz, itemBuscado);
    itemBuscado.chave = 6;
    buscarPreOrdem(raiz, itemBuscado);
    itemBuscado.chave = 8;
    buscarPreOrdem(raiz, itemBuscado);

    destruirArvore(raiz);
    return 0;
}
*/

/*
Insere Pre Ordem é igual a inserir, por que isso já é uma árvore binária.


//inserePreOrdem
ARVORE_BINARIA* inserePreOrdem(ARVORE_BINARIA* raiz, ITEM item) {
    if (raiz == NULL) {
        return criarNo(item);
    }
    
    if (item.chave < raiz->item.chave) {
        raiz->esq = inserePreOrdem(raiz->esq, item);
        raiz->esq->costura = raiz;
    } else {
        raiz->dir = inserePreOrdem(raiz->dir, item);
        raiz->dir->costura = raiz->costura;
    }
    
    return raiz;
}


//Inserir

void inserir(ARVORE_BINARIA **raiz, ITEM item) {
    ARVORE_BINARIA *novo = criarNo(item);
    ARVORE_BINARIA *atual = *raiz;
    ARVORE_BINARIA *anterior = NULL;
    bool direita = false;
    
    while (atual != NULL) {
        anterior = atual;
        if (item.chave < atual->item.chave) {
            atual = atual->esq;
            direita = false;
        } else {
            atual = atual->dir;
            direita = true;
        }
    }
    
    if (anterior == NULL) { // a árvore está vazia
        *raiz = novo;
    } else if (direita) { // insere à direita do nó anterior
        novo->costura = anterior->costura;
        anterior->costura = novo;
        anterior->dir = novo;
    } else { // insere à esquerda do nó anterior
        novo->costura = anterior;
        novo->dir = anterior;
        anterior->esq = novo;
        if (anterior->costura != NULL && anterior->costura->dir == anterior) {
            anterior->costura->esq = novo;
        }
    }
}

*/
