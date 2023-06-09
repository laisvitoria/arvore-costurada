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
        printf("No nao encontrado %d \n", no.chave);
        return;
    }

    if (no.chave == raiz->item.chave) {
        printf("No encontrado %d\n", no.chave);
        return;
    }

    if (no.chave < raiz->item.chave) {
        if (raiz->esq != NULL && (raiz->esq->costura == NULL || raiz->esq->item.chave >= no.chave)) {
            buscarPreOrdem(raiz->esq, no);
        } else {
            printf("No nao encontrado %d \n", no.chave);
        }
    } else {
        if (raiz->dir != NULL) {
            buscarPreOrdem(raiz->dir, no);
        } else {
            printf("No nao encontrado %d \n", no.chave);
        }
    }
}


//AS BUSCAS IN ORDEM E POS ORDEM NÃO ESTÃO EXIBINDO NADA QUANDO O ITEM NÃO É ENCONTRADO

//É a mesma coisa que percorrer, normal igual a inserir?
void buscarPosOrdem(ARVORE_BINARIA *raiz, ITEM no) { // agora está verificando em pós ordem

    if (raiz == NULL) {
      return;
    } else {
      buscarPosOrdem(raiz->esq, no);
      buscarPosOrdem(raiz->dir, no);
      if (raiz->item.chave == no.chave) {
        printf("no encontrado %d \n", raiz->item.chave);
      }
    }
}

//Buscar In-ordem (em aberto), se conseguir consertar buscarPosOrdem().

void buscarInOrdem(ARVORE_BINARIA *raiz, ITEM no) {
    if (raiz == NULL) {
      return;
    } else {
      buscarInOrdem(raiz->esq, no);
      if (raiz->item.chave == no.chave) {
        printf("no encontrado %d \n", raiz->item.chave);
      }
      buscarInOrdem(raiz->dir, no);
    }
}

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

//ALTERAR item e reorganizar no
ARVORE_BINARIA *alterar(TIPOCHAVE ch, ITEM novoItem, ARVORE_BINARIA *raiz) {
    ARVORE_BINARIA *no = buscaAuxiliarAlterar(ch, raiz);
    if (no != NULL) {
        no->item = novoItem;
        if (no->esq != NULL && no->dir != NULL) {
            // Nó tem ambos os filhos
            ARVORE_BINARIA *antecessor = no->esq;
            while (antecessor->dir != NULL) {
                antecessor = antecessor->dir;
            }
            if (antecessor->costura == NULL) {
                no->dir = antecessor;
                no->costura = antecessor;
            } else {
                no->dir = antecessor->costura;
            }
        } else if (no->esq != NULL) {
            // Nó tem somente filho esquerdo
            ARVORE_BINARIA *antecessor = no->esq;
            while (antecessor->dir != NULL) {
                antecessor = antecessor->dir;
            }
            no->dir = antecessor;
            no->costura = antecessor;
        } else if (no->dir != NULL) {
            // Nó tem somente filho direito
            no->costura = no->dir;
        } else {
            // Nó não tem filhos
            no->costura = NULL;
        }
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

void alterar_e_reordenar(ARVORE_BINARIA *raiz, TIPOCHAVE chave_antiga, TIPOCHAVE chave_nova) {
    // Busca o nó a ser alterado
    ARVORE_BINARIA *no = buscaAuxiliarAlterar(raiz, chave_antiga);
    if (no == NULL) {
        printf("Nó não encontrado\n");
        return;
    }

    // Altera a chave do nó
    no->item.chave = chave_nova;

    // Reordena o nó na árvore costurada
    ARVORE_BINARIA *anterior = NULL;
    ARVORE_BINARIA *atual = raiz;
    while (atual != NULL) {
        if (atual->item.chave > no->item.chave) {
            // Desce para a esquerda
            anterior = atual;
            atual = atual->esq;
        } else if (atual->costura == NULL || atual->costura->item.chave > no->item.chave) {
            // Insere o nó à direita do atual
            no->dir = atual->dir;
            no->costura = atual->costura;
            atual->dir = no;
            atual->costura = no;
            return;
        } else {
            // Segue pela costura
            anterior = atual;
            atual = atual->costura;
        }
    }

    // Caso o nó seja inserido à direita da raiz
    no->dir = NULL;
    no->costura = raiz->costura;
    raiz->costura = no;
}
/*
Recebe como parâmetros a raiz da árvore, a chave antiga do nó a ser alterado e a nova chave.
Utiliza a função buscaAuxiliarAlterar para encontrar o nó a ser alterado. Caso não encontre, exibe uma mensagem de erro e retorna.
Altera a chave do nó para a nova chave recebida como parâmetro.
Começa a busca pelo novo local do nó a partir da raiz da árvore.
Enquanto não chegar ao final da árvore (atual = NULL), realiza a busca:
Se a chave do nó atual for maior que a nova chave, desce para a esquerda.
Se a chave do nó atual for menor que a nova chave e o nó seguinte na costura também for menor que a nova chave, segue pela costura.
Caso contrário, encontra o local onde o nó deve ser inserido. Insere o nó à direita do nó atual, e atualiza as costuras.
Se o nó não foi inserido antes disso, significa que ele deve ser inserido à direita da raiz. Atualiza a costura da raiz para apontar para o novo nó.
*/
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
    printf("\nPre ordem: ");
    percorrerPreOrdem(raiz);
    printf("\nPos ordem: ");
    percorrerPosOrdem(raiz);
    printf("\nIn ordem: ");
    percorrerInOrdem(raiz);

    printf("\n\nBusca Pre Ordem \n");
    itemBuscado.chave = 1;
    buscarPreOrdem(raiz, itemBuscado);
    itemBuscado.chave = 6;
    buscarPreOrdem(raiz, itemBuscado);
    itemBuscado.chave = 8;
    buscarPreOrdem(raiz, itemBuscado);

    printf("\nBusca Pos Ordem \n");
    itemBuscado.chave = 1;
    buscarPosOrdem(raiz, itemBuscado);
    itemBuscado.chave = 6;
    buscarPosOrdem(raiz, itemBuscado);
    itemBuscado.chave = 8;
    buscarPosOrdem(raiz, itemBuscado);

    
    printf("\nBusca In Ordem \n");
    itemBuscado.chave = 1;
    buscarInOrdem(raiz, itemBuscado);
    itemBuscado.chave = 6;
    buscarInOrdem(raiz, itemBuscado);
    itemBuscado.chave = 8;
    buscarInOrdem(raiz, itemBuscado);

    printf("\nAltera Item \n");
    itemBuscado.chave = 9;
    alterar_item(4, itemBuscado, raiz);
    reorganizar_costura(raiz);
    //percorrerPreOrdem(raiz);

    printf("\nRemove No \n");
    removerNo(raiz, 9);
    
    printf("\nInserir em Pre Ordem \n");
    inserirPreOrdem(&raiz, item7);
    percorrerInOrdem(raiz);

    destruirArvore(raiz);
    return 0;
}
