#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void alterar(ARVORE_COSTURADA **arvore, TIPOCHAVE chave, ITEM novoItem);
void reorganizar(ARVORE_COSTURADA **arvore);


typedef int TIPOCHAVE;

typedef struct {
    TIPOCHAVE chave;
    // char valor[100];
} ITEM;

typedef struct estrutura ARVORE_COSTURADA;

struct estrutura {
    ITEM item;
    ARVORE_COSTURADA *estruturaEsquerda;
    ARVORE_COSTURADA *estruturaDireita;
    bool costuraEsquerda;
    bool costuraDireita;
};

ARVORE_COSTURADA* criarArvore(ITEM item) {
    ARVORE_COSTURADA *novaArvore = (ARVORE_COSTURADA*) malloc(sizeof(ARVORE_COSTURADA));
    novaArvore->item = item;
    novaArvore->estruturaEsquerda = NULL;
    novaArvore->estruturaDireita = NULL;
    novaArvore->costuraEsquerda = false;
    novaArvore->costuraDireita = false;
    return novaArvore;
}

void inserir(ARVORE_COSTURADA **arvore, ITEM item) {
    if (*arvore == NULL) {
        *arvore = criarArvore(item);
    } else if (item.chave < (*arvore)->item.chave) {
        if ((*arvore)->costuraEsquerda == true) {
            ARVORE_COSTURADA *novaArvore = criarArvore(item);
            novaArvore->estruturaEsquerda = (*arvore)->estruturaEsquerda;
            novaArvore->costuraEsquerda = true;
            (*arvore)->estruturaEsquerda = novaArvore;
            (*arvore)->costuraEsquerda = false;
        } else {
            inserir(&((*arvore)->estruturaEsquerda), item);
        }
    } else {
        if ((*arvore)->costuraDireita == true) {
            ARVORE_COSTURADA *novaArvore = criarArvore(item);
            novaArvore->estruturaDireita = (*arvore)->estruturaDireita;
            novaArvore->costuraDireita = true;
            (*arvore)->estruturaDireita = novaArvore;
            (*arvore)->costuraDireita = false;
        } else {
            inserir(&((*arvore)->estruturaDireita), item);
        }
    }
}

void imprimir(ARVORE_COSTURADA *arvore) {
    ARVORE_COSTURADA *atual = arvore;
    while (atual->costuraEsquerda == false) {
        atual = atual->estruturaEsquerda;
    }
    while (atual != NULL) {
        printf("%d ", atual->item.chave);
        if (atual->costuraDireita == true) {
            atual = atual->estruturaDireita;
        } else {
            atual = atual->estruturaDireita;
            while (atual != NULL && atual->costuraEsquerda == false) {
                atual = atual->estruturaEsquerda;
            }
        }
    }
}
void alterar(ARVORE_COSTURADA **arvore, TIPOCHAVE chave, ITEM novoItem) {
    if (*arvore == NULL) {
        printf("Erro: elemento não encontrado.\n");
        return;
    } else if ((*arvore)->item.chave == chave) {
        (*arvore)->item = novoItem;
        return;
    } else if (chave < (*arvore)->item.chave) {
        if ((*arvore)->costuraEsquerda == true) {
            printf("Erro: elemento não encontrado.\n");
            return;
        } else {
            alterar(&((*arvore)->estruturaEsquerda), chave, novoItem);
        }
    } else {
        if ((*arvore)->costuraDireita == true) {
            printf("Erro: elemento não encontrado.\n");
            return;
        } else {
            alterar(&((*arvore)->estruturaDireita), chave, novoItem);
        }
    }
}

void reorganizar(ARVORE_COSTURADA **arvore) {
    ARVORE_COSTURADA *atual = *arvore;
    ARVORE_COSTURADA *anterior = NULL;
    ARVORE_COSTURADA *proximo = NULL;
    bool achouPrimeiro = false;
    while (atual != NULL) {
        if (achouPrimeiro == false && atual->costuraEsquerda == false) {
            achouPrimeiro = true;
        }
        if (atual->costuraEsquerda == true) {
            proximo = atual->estruturaEsquerda;
            atual->estruturaEsquerda = anterior;
        } else {
            proximo = atual->estruturaEsquerda;
            while (proximo != NULL && proximo->costuraDireita == false) {
                proximo = proximo->estruturaDireita;
            }
            if (proximo == NULL) {
                proximo = atual->estruturaDireita;
            }
            atual->estruturaDireita = anterior;
        }
        anterior = atual;
        atual = proximo;
    }
    *arvore = anterior;
}

void remover(ARVORE_COSTURADA **arvore, TIPOCHAVE chave) {
    if (*arvore == NULL) {
        printf("Chave nao encontrada na arvore!\n");
        return;
    }
    if (chave < (*arvore)->item.chave) {
        remover(&((*arvore)->estruturaEsquerda), chave);
    } else if (chave > (*arvore)->item.chave) {
        remover(&((*arvore)->estruturaDireita), chave);
    } else {
        if ((*arvore)->estruturaEsquerda == NULL && (*arvore)->estruturaDireita == NULL) { // nó sem filhos
            free(*arvore);
            *arvore = NULL;
        } else if ((*arvore)->estruturaEsquerda == NULL) { // nó com apenas um filho à direita
            ARVORE_COSTURADA *temp = *arvore;
            *arvore = (*arvore)->estruturaDireita;
            if (temp->costuraEsquerda == true) {
                (*arvore)->estruturaEsquerda = temp->estruturaEsquerda;
                (*arvore)->costuraEsquerda = true;
            }
            free(temp);
        } else if ((*arvore)->estruturaDireita == NULL) { // nó com apenas um filho à esquerda
            ARVORE_COSTURADA *temp = *arvore;
            *arvore = (*arvore)->estruturaEsquerda;
            if (temp->costuraDireita == true) {
                (*arvore)->estruturaDireita = temp->estruturaDireita;
                (*arvore)->costuraDireita = true;
            }
            free(temp);
        } else { // nó com dois filhos
            ARVORE_COSTURADA *temp = (*arvore)->estruturaDireita;
            while (temp->estruturaEsquerda != NULL) {
                temp = temp->estruturaEsquerda;
            }
            (*arvore)->item = temp->item;
            remover(&((*arvore)->estruturaDireita), temp->item.chave);
        }
    }
}
/*
Esta função utiliza o algoritmo padrão de remoção de um nó de uma árvore binária de busca. 
Quando um nó é removido, a função reorganiza a árvore para manter as propriedades da árvore duplamente amarrada. 
Se o nó removido tiver apenas um filho à direita ou à esquerda, o filho restante é ligado ao pai do nó removido, 
substituindo o nó removido na árvore. Se o nó removido tiver dois filhos,
a função encontra o sucessor do nó (o menor valor na subárvore à direita) e substitui o nó removido pelo sucessor na árvore,
depois remove o sucessor da subárvore à direita.

É importante notar que, ao remover um nó, é necessário verificar se o nó possui uma ligação costurada à esquerda ou à direita.
Se o nó removido possuir uma ligação costurada, é necessário atualizar a ligação costurada no novo nó que o substitui,
de modo que a árvore continue sendo duplamente encadeada.
*/

void destruirArvore(ARVORE_COSTURADA **arvore) {
    if (*arvore != NULL) {
        destruirArvore(&((*arvore)->estruturaEsquerda));
        destruirArvore(&((*arvore)->estruturaDireita));
        free(*arvore);
        *arvore = NULL;
    }
}
/*
A função acima percorre recursivamente a árvore em pós-ordem, ou seja, primeiro destrói os nós filhos esquerdos,
depois os nós filhos direitos e por último o nó raiz.
A função libera a memória alocada para cada nó da árvore e, ao final, atualiza o ponteiro da raiz para NULL 
para indicar que a árvore foi destruída.
*/

int main() {
    ITEM item1 = { 10 };
    ITEM item2 = { 7 };
    ITEM item3 = { 12 };
    ITEM item4 = { 5 };
    ITEM item5 = { 8 };
    ITEM item6 = { 11 };
    ITEM item7 = { 15 };

    ARVORE_COSTURADA *arvore = NULL;

    inserir(&arvore, item1);
    inserir(&arvore, item2);
    inserir(&arvore, item3);
    inserir(&arvore, item4);
    inserir(&arvore, item5);
    inserir(&arvore, item6);
    inserir(&arvore, item7);

    printf("Árvore original:\n");
    imprimir(arvore);
    printf("\n");

    alterar(&arvore, 5, item2);
    printf("Árvore após alteração:\n");
    imprimir(arvore);
    printf("\n");

    return 0;
}
