#include <stdio.h>
#include <stdlib.h>

typedef int TIPOCHAVE;

typedef enum {NoEsquerdo, NoDireito, NoPai, NoRaiz} DIRECAO;

typedef struct {
    TIPOCHAVE chave;
    // char valor[100];
} ITEM;

typedef struct estrutura {
    ITEM item;
    struct estrutura *esq;
    struct estrutura *dir;
    struct estrutura *pai;
    int bitEsq;
    int bitDir;
} ARVORE_COSTURADA;

ARVORE_COSTURADA *criar_no(TIPOCHAVE chave) {
    ARVORE_COSTURADA *novo_no = (ARVORE_COSTURADA*) malloc(sizeof(ARVORE_COSTURADA));
    novo_no->item.chave = chave;
    novo_no->esq = NULL;
    novo_no->dir = NULL;
    novo_no->pai = NULL;
    novo_no->bitEsq = 1;
    novo_no->bitDir = 1;
    return novo_no;
}

ARVORE_COSTURADA *inserir_no(ARVORE_COSTURADA *raiz, TIPOCHAVE chave) {
    ARVORE_COSTURADA *novo_no = criar_no(chave);

    if (raiz == NULL) {
        novo_no->bitEsq = NoRaiz;
        novo_no->bitDir = NoRaiz;
        return novo_no;
    }

    ARVORE_COSTURADA *atual = raiz;
    ARVORE_COSTURADA *pai_atual = NULL;

    while (1) {
        pai_atual = atual;

        if (chave < atual->item.chave) {
            if (atual->bitEsq == NoEsquerdo) {
                atual = atual->esq;
            } else {
                novo_no->esq = atual->esq;
                atual->esq = novo_no;
                novo_no->pai = pai_atual;
                novo_no->bitEsq = NoEsquerdo;
                novo_no->dir = atual;
                atual->bitEsq = NoEsquerdo;
                return raiz;
            }
        } else {
            if (atual->bitDir == NoDireito) {
                atual = atual->dir;
            } else {
                novo_no->dir = atual->dir;
                atual->dir = novo_no;
                novo_no->pai = pai_atual;
                novo_no->bitDir = NoDireito;
                novo_no->esq = atual;
                atual->bitDir = NoDireito;
                return raiz;
            }
        }
    }
}

ARVORE_COSTURADA *buscar_no(ARVORE_COSTURADA *raiz, TIPOCHAVE chave) {
    ARVORE_COSTURADA *atual = raiz;

    while (atual != NULL) {
        if (atual->item.chave == chave) {
            return atual;
        } else if (chave < atual->item.chave && atual->bitEsq == NoEsquerdo) {
            atual = atual->esq;
        } else if (chave > atual->item.chave && atual->bitDir == NoDireito) {
            atual = atual->dir;
        } else {
            break;
        }
    }

    return NULL;
}

void inserirOrdenado(ARVORE_COSTURADA **raiz, ITEM item) {
    ARVORE_COSTURADA *novoNo = (ARVORE_COSTURADA *) malloc(sizeof(ARVORE_COSTURADA));
    novoNo->item = item;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->pai = NULL;

    if (*raiz == NULL) {
        *raiz = novoNo;
        novoNo->pai = *raiz;
        novoNo->esq = NULL;
        novoNo->dir = NULL;
    } else {
        ARVORE_COSTURADA *atual = *raiz;
        ARVORE_COSTURADA *anterior = NULL;

        while (atual != NULL) {
            anterior = atual;
            if (item.chave < atual->item.chave) {
                if (atual->esq == NULL) {
                    atual->esq = novoNo;
                    novoNo->pai = atual;
                    novoNo->esq = anterior;
                    novoNo->dir = atual;
                    atual->pai = anterior->pai == atual ? novoNo : anterior->pai;
                    break;
                } else {
                    atual = atual->esq;
                }
            } else {
                if (atual->dir == NULL) {
                    atual->dir = novoNo;
                    novoNo->pai = atual;
                    novoNo->dir = anterior;
                    novoNo->esq = atual;
                    anterior->pai = atual->pai == anterior ? novoNo : atual->pai;
                    break;
                } else {
                    atual = atual->dir;
                }
            }
        }
    }
}


void buscarPosOrdem(ARVORE_COSTURADA *raiz) {
    if (raiz != NULL) {
        buscarPosOrdem(raiz->esq);
        buscarPosOrdem(raiz->dir);
        printf("%d ", raiz->item.chave);
    }
}

void buscarPreOrdem(ARVORE_COSTURADA *raiz) {
    if (raiz != NULL) {
        printf("%d ", raiz->item.chave);
        buscarPreOrdem(raiz->esq);
        buscarPreOrdem(raiz->dir);
    }
}

void buscarEmOrdem(ARVORE_COSTURADA *raiz) {
    if (raiz != NULL) {
        buscarEmOrdem(raiz->esq);
        printf("%d ", raiz->item.chave);
        buscarEmOrdem(raiz->dir);
    }
}

ARVORE_COSTURADA *remover(ARVORE_COSTURADA *raiz, int chave) {
    ARVORE_COSTURADA *no_remover = buscar(raiz, chave);

    if (no_remover == NULL) {
        return raiz;
    }

    if (no_remover->bitEsq == 0 && no_remover->bitDir == 0) {
        if (no_remover->pai == NULL) {
            free(no_remover);
            return NULL;
        }

        ARVORE_COSTURADA *no_pai = no_remover->pai;

        if (no_pai->esq == no_remover) {
            no_pai->esq = NULL;
            no_pai->bitEsq = 0;
        } else {
            no_pai->dir = NULL;
            no_pai->bitDir = 0;
        }

        free(no_remover);
        return raiz;
    }

    if (no_remover->bitEsq == 0) {
        if (no_remover->pai == NULL) {
            ARVORE_COSTURADA *nova_raiz = no_remover->dir;
            nova_raiz->pai = NULL;
            nova_raiz->bitEsq = no_remover->bitEsq;
            free(no_remover);
            return nova_raiz;
        }

        ARVORE_COSTURADA *no_pai = no_remover->pai;

        if (no_pai->esq == no_remover) {
            no_pai->esq = no_remover->dir;
            no_remover->dir->pai = no_pai;
            no_pai->bitEsq = no_remover->bitDir;
        } else {
            no_pai->dir = no_remover->dir;
            no_remover->dir->pai = no_pai;
            no_pai->bitDir = no_remover->bitDir;
        }

        free(no_remover);
        return raiz;
    }

    if (no_remover->bitDir == 0) {
        if (no_remover->pai == NULL) {
            ARVORE_COSTURADA *nova_raiz = no_remover->esq;
            nova_raiz->pai = NULL;
            nova_raiz->bitDir = no_remover->bitDir;
            free(no_remover);
            return nova_raiz;
        }

        ARVORE_COSTURADA *no_pai = no_remover->pai;

        if (no_pai->esq == no_remover) {
            no_pai->esq = no_remover->esq;
            no_remover->esq->pai = no_pai;
            no_pai->bitEsq = no_remover->bitEsq;
        } else {
            no_pai->dir = no_remover->esq;
            no_remover->esq->pai = no_pai;
            no_pai->bitDir = no_remover->bitEsq;
        }

        free(no_remover);
        return raiz;
    }

    ARVORE_COSTURADA *no_substituto = no_remover->dir;
    while (no_substituto->esq != NULL) {
        no_substituto = no_substituto->esq;
    }

    no_remover->item = no_substituto->item;
    raiz = remover(raiz, no_substituto->item.chave);

    return raiz;
}
void imprimir(ARVORE_COSTURADA *raiz) {
    if (raiz == NULL) {
        return;
    }

    ARVORE_COSTURADA *atual = raiz;

    while (atual->bitEsq == 1) {
        atual = atual->esq;
    }

    while (atual != NULL) {
        printf("%d ", atual->item.chave);

        if (atual->bitDir == 1) {
            atual = atual->dir;

            while (atual->bitEsq == 1) {
                atual = atual->esq;
            }
        } else {
            atual = atual->dir;

            while (atual != NULL && atual->bitEsq == 0) {
                atual = atual->dir;
            }

            if (atual != NULL) {
                atual = atual->esq;

                while (atual->bitEsq == 1) {
                    atual = atual->esq;
                }
            }
        }
    }

    printf("\n");
}
int main (){
 ARVORE_COSTURADA *raiz = NULL;
    raiz = inserir_no(raiz, 10);
    raiz = inserir_no(raiz, 20);
    raiz = inserir_no(raiz, 40);
    raiz = inserir_no(raiz, 30);
    raiz = inserir_no(raiz, 50);
    raiz = inserir_no(raiz, 60);
    raiz = inserir_no(raiz, 90);
    raiz = inserir_no(raiz, 70);
    raiz = inserir_no(raiz, 80);

    printf("Arvore em ordem: ");
    imprimir(raiz);
    printf("\n");

    ARVORE_COSTURADA *no_encontrado = buscar_no(raiz, 40);
    if (no_encontrado != NULL) {
        printf("No encontrado: %d\n", no_encontrado->item.chave);
    } else {
        printf("No nao encontrado\n");
    }

    ARVORE_COSTURADA *no = remover(raiz, 80);
    if (no_encontrado != NULL) {
        printf("No encontrado e removido: %d\n", no_encontrado->item.chave);
    } else {
        printf("No nao encontrado\n");
    }
    free (no);
    printf("Arvore em ordem: ");
    imprimir(raiz);
    printf("\n");

    printf("Buscar Arvore Em-ordem");
    buscarEmOrdem(raiz);

     printf("Buscar Arvore Pre-ordem");
    buscarPreOrdem(raiz);

    printf("Buscar Arvore Pos-ordem");
    buscarPosOrdem(raiz);

    ARVORE_COSTURADA *no = remover(raiz, 70);
    free (no);
    ARVORE_COSTURADA *no = remover(raiz, 90);
    free (no);
    ARVORE_COSTURADA *no = remover(raiz, 60);
    free (no);
    ARVORE_COSTURADA *no = remover(raiz, 50);
    free (no);
    ARVORE_COSTURADA *no = remover(raiz, 30);
    free (no);
    ARVORE_COSTURADA *no = remover(raiz, 40);
    free (no);
    ARVORE_COSTURADA *no = remover(raiz, 20);
    free (no);
    ARVORE_COSTURADA *no = remover(raiz, 10);
    free (no);


    raiz = inserirOrdenado(*raiz, 10);
    raiz = inserirOrdenado(*raiz, 20);
    raiz = inserirOrdenado(*raiz, 40);
    raiz = inserirOrdenado(*raiz, 30);
    raiz = inserirOrdenado(*raiz, 50);
    raiz = inserirOrdenado(*raiz, 60);
    raiz = inserirOrdenado(*raiz, 90);
    raiz = inserirOrdenado(*raiz, 70);
    raiz = inserirOrdenado(*raiz, 80);

    printf("Buscar Arvore Em-ordem");
    buscarEmOrdem(raiz);

     printf("Buscar Arvore Pre-ordem");
    buscarPreOrdem(raiz);

    printf("Buscar Arvore Pos-ordem");
    buscarPosOrdem(raiz);

return 0;
}
