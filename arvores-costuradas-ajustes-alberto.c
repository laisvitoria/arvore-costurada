#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
} ITEM;


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

//Ver comm alberto se essa função de inserir tá certa

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



//É a mesma coisa que percorrer, normal igual a inserir?


void buscarPosOrdem(ARVORE_BINARIA* raiz, ITEM no) { //está percorrendo apenas em pré-ordem, precisa alterar o caminhamento na função
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

//Buscar In-ordem (em aberto), se conseguir consertar buscarPosOrdem().

// Percorrer em ordem
void percorrerInOrdem(ARVORE_BINARIA *raiz) { //se colocar um numero impar no meio, a ordem muda
    if (raiz == NULL) {
        return;
    }

    percorrerInOrdem(raiz->esq);
    printf("%d ", raiz->item.chave);
    percorrerInOrdem(raiz->dir);
}


void percorrerPosOrdem(ARVORE_BINARIA *raiz) {
    if (raiz == NULL) {
        return;
    }

    percorrerPosOrdem(raiz->esq);
    percorrerPosOrdem(raiz->dir);
    printf("%d ", raiz->item.chave);
}

void percorrerPreOrdem(ARVORE_BINARIA *raiz) {
    if (raiz == NULL) {
        return;
    }

    printf("%d ", raiz->item.chave);
    percorrerPreOrdem(raiz->esq);
    percorrerPreOrdem(raiz->dir);
}

//REMOVER

ARVORE_BINARIA* removerNo(ARVORE_BINARIA* raiz, TIPOCHAVE chave) {
    if (raiz == NULL) {
        return NULL;
    }

    ARVORE_BINARIA *atual = raiz;
    ARVORE_BINARIA *anterior = NULL;
    bool direita = false;

    // Busca o nó a ser removido e armazena o seu nó pai e a direção da qual está sendo acessado (esquerda ou direita)
    while (atual != NULL && atual->item.chave != chave) {
        anterior = atual;
        if (chave < atual->item.chave) {
            atual = atual->esq;
            direita = false;
        } else {
            atual = atual->dir;
            direita = true;
        }
    }

    if (atual == NULL) {
        // Nó não encontrado
        return raiz;
    }

    if (atual->esq == NULL && atual->dir == NULL) {
        // Caso 1: nó sem filhos
        if (anterior != NULL) {
            // O nó a ser removido não é a raiz
            if (!direita) { // se o nó estiver à esquerda do pai
                anterior->esq = atual->esq;
                anterior->costura = atual->costura;
            } else { // se o nó estiver à direita do pai
                anterior->dir = atual->dir;
            }
        } else {
            // O nó a ser removido é a raiz
            raiz = NULL;
        }
        free(atual);
    } else if (atual->esq == NULL || atual->dir == NULL) {
        // Caso 2: nó com um filho
        ARVORE_BINARIA *filho = atual->esq != NULL ? atual->esq : atual->dir;
        if (anterior != NULL) {
            // O nó a ser removido não é a raiz
            if (!direita) { // se o nó estiver à esquerda do pai
                anterior->esq = filho;
                anterior->costura = atual->costura;
            } else { // se o nó estiver à direita do pai
                anterior->dir = filho;
            }
        } else {
            // O nó a ser removido é a raiz
            raiz = filho;
        }
        free(atual);
    } else {
        // Caso 3: nó com dois filhos
        ARVORE_BINARIA *sucessor = atual->dir;
        while (sucessor->esq != NULL) {
            sucessor = sucessor->esq;
        }
        atual->item = sucessor->item;
        removerNo(raiz, sucessor->item.chave);
    }

    return raiz;
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
//////////////////////////////////////////////// COMPILAR-SERGIO/////////////////////////////////
ARVORE_BINARIA *buscaAuxiliarAlterar(TIPOCHAVE ch, ARVORE_BINARIA *raiz) {
    if (raiz == NULL || raiz->item.chave == ch) {
        return raiz;
    }
    if (ch < raiz->item.chave) {
        return buscaAuxiliarAlterar(ch, raiz->esq);
    }
    return buscaAuxiliarAlterar(ch, raiz->dir);
}

//realiza uma busca normar e retorna a chave se achou
ARVORE_BINARIA *alterar_item(TIPOCHAVE ch, ITEM novo_item, ARVORE_BINARIA *raiz) {
    ARVORE_BINARIA *no = buscaAuxiliarAlterar(ch, raiz);
    if (no != NULL) {
      no->item = novo_item;
      printf("%i \n", no -> item.chave);
    
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
    itemBuscado.chave = 9;
    alterar_item(4, itemBuscado, raiz);
    reorganizar_costura(raiz);
    //percorrerPreOrdem(raiz);
    removerNo(raiz, 9);
    inserirPreOrdem(&raiz, item7);
    percorrerInOrdem(raiz);

  

    destruirArvore(raiz);
    return 0;
}