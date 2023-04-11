
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
    ARVORE_COSTURADA *estruturaEsquerda;
    ARVORE_COSTURADA *estruturaDireita;
    bool costuraEsquerda;
    bool costuraDireita;
};

ARVORE_COSTURADA *criar_no(TIPOCHAVE ch) {
    ARVORE_COSTURADA *novoNo = (ARVORE_COSTURADA *) malloc(sizeof(ARVORE_COSTURADA));
    novoNo->item.chave = ch;
    novoNo->estruturaEsquerda = NULL;
    novoNo->estruturaDireita = NULL;
    novoNo->costuraEsquerda = false;
    novoNo->costuraDireita = false;

    return novoNo;
}

/*
Essa função recebe como parâmetro a chave do novo nó a ser criado, aloca memória para um novo nó da árvore, inicializa seus campos (a chave, os ponteiros para as subárvores esquerda e direita e as flags de costura), e retorna o endereço do novo nó criado.

Assim, basta chamar essa função sempre que for necessário criar um novo nó na sua árvore duplamente costurada.
  */

void inserir(ARVORE_COSTURADA **raiz, TIPOCHAVE ch) {
    ARVORE_COSTURADA *novoNo = criar_no(ch);
    ARVORE_COSTURADA *atual = *raiz;
    ARVORE_COSTURADA *noAnterior = NULL;
    bool achouLugar = false;

    if (*raiz == NULL) {
        *raiz = novoNo;
        return;
    }

    while (atual != NULL) {
        noAnterior = atual;

        if (ch < atual->item.chave) {
            if (!atual->costuraEsquerda) {
                atual = atual->estruturaEsquerda;
            } else {
                novoNo->estruturaEsquerda = atual->estruturaEsquerda;
                atual->estruturaEsquerda = novoNo;
                atual->costuraEsquerda = false;
                achouLugar = true;
                break;
            }
        } else if (ch > atual->item.chave) {
            if (!atual->costuraDireita) {
                atual = atual->estruturaDireita;
            } else {
                novoNo->estruturaDireita = atual->estruturaDireita;
                atual->estruturaDireita = novoNo;
                atual->costuraDireita = false;
                achouLugar = true;
                break;
            }
        } else {
            free(novoNo);
            return;
        }
    }

    if (!achouLugar) {
        if (ch < noAnterior->item.chave) {
            noAnterior->estruturaEsquerda = novoNo;
            novoNo->estruturaDireita = noAnterior;
            novoNo->costuraDireita = true;
        } else {
            noAnterior->estruturaDireita = novoNo;
            novoNo->estruturaEsquerda = noAnterior;
            novoNo->costuraEsquerda = true;
        }
    }
}

/*
Essa função recebe como parâmetro um ponteiro para a raiz da árvore e a chave do novo nó a ser inserido. Ela primeiro cria um novo nó utilizando a função criar_no, e em seguida começa a percorrer a árvore procurando o lugar adequado para inseri-lo.

Caso a árvore esteja vazia, o novo nó é adicionado como raiz. Caso contrário, a função percorre os nós da árvore, utilizando as flags de costura para encontrar o lugar adequado para inserir o novo nó.

Se a chave do novo nó já existe na árvore, a função simplesmente retorna, sem fazer nenhuma alteração.

Se a função chegar a percorrer toda a árvore e não encontrar um lugar adequado para inserir o novo nó, isso significa que o novo nó é o maior ou o menor nó da árvore, e por isso deve ser inserido na posição devida, com a devida costura, ao lado do último nó visitado.
*/
ARVORE_COSTURADA *buscar(ARVORE_COSTURADA *no, TIPOCHAVE ch) {
    while (no != NULL) {
        if (ch == no->item.chave) {
            return no;
        } else if (ch < no->item.chave) {
            if (!no->costuraEsquerda) {
                no = no->estruturaEsquerda;
            } else {
                return NULL;
            }
        } else {
            if (!no->costuraDireita) {
                no = no->estruturaDireita;
            } else {
                return NULL;
            }
        }
    }

    return NULL;
}

/*
Essa função recebe um ponteiro para um nó e a chave a ser buscada na árvore. Ela percorre a árvore seguindo a lógica do código de inserir, comparando a chave buscada com as chaves dos nós da árvore.
  */
void alterar_item(ARVORE_COSTURADA *no, TIPOCHAVE ch, ITEM novoItem) {
    if (no == NULL) {
        return;
    }

    ARVORE_COSTURADA *noBuscado = buscar(no, ch);

    if (noBuscado != NULL) {
        noBuscado->item = novoItem;
    }
}

void reorganizar(ARVORE_COSTURADA **raiz) {
    ARVORE_COSTURADA *atual = *raiz;
    ARVORE_COSTURADA *mais_a_esquerda = NULL;

    while (atual != NULL) {
        while (atual->estruturaEsquerda != NULL && !atual->costuraEsquerda) {
            atual = atual->estruturaEsquerda;
        }

        mais_a_esquerda = atual;

        while (mais_a_esquerda->estruturaDireita != NULL && mais_a_esquerda->costuraDireita) {
            mais_a_esquerda = mais_a_esquerda->estruturaDireita;
        }

        atual = atual->estruturaDireita;

        if (mais_a_esquerda->estruturaDireita == NULL) {
            mais_a_esquerda->costuraDireita = true;
            mais_a_esquerda->estruturaDireita = atual;
        }
    }
}
/*
A função `alterar_item` recebe um ponteiro para o nó a ser alterado, a chave do item a ser alterado e o novo item. Ela busca o nó com a chave correspondente na árvore e, caso o encontre, atualiza o item com o novo valor.

A função `reorganizar` faz a reorganização da árvore duplamente costurada, garantindo que todos os nós estejam corretamente costurados. Ela percorre a árvore da esquerda para a direita e encontra o nó mais à esquerda e o nó sucessor ao seu lado direito. Em seguida, ela vai para o próximo nó e repete o processo.

Ao encontrar o nó mais à esquerda, ela verifica se esse nó já está costurado com o seu sucessor à direita. Se não estiver, ela realiza a costura e continua percorrendo a árvore.
*/
void imprimir_arvore(ARVORE_COSTURADA *no) {
    if (no == NULL) {
        return;
    }

    // Encontrar o nó mais à esquerda da sub-árvore
    ARVORE_COSTURADA *mais_a_esquerda = no;

    while (mais_a_esquerda->estruturaEsquerda != NULL && !mais_a_esquerda->costuraEsquerda) {
        mais_a_esquerda = mais_a_esquerda->estruturaEsquerda;
    }

    // Imprimir os nós da sub-árvore a partir do nó mais à esquerda
    while (mais_a_esquerda != NULL) {
        printf("%d ", mais_a_esquerda->item.chave);

        if (mais_a_esquerda->costuraDireita) {
            mais_a_esquerda = mais_a_esquerda->estruturaDireita;
        } else {
            mais_a_esquerda = mais_a_esquerda->estruturaDireita;

            while (mais_a_esquerda != NULL && !mais_a_esquerda->costuraEsquerda) {
                mais_a_esquerda = mais_a_esquerda->estruturaEsquerda;
            }
        }
    }
}

/*
A função `imprimir_arvore` percorre a árvore a partir do nó mais à esquerda. Para isso, ela faz uma busca pelo nó mais à esquerda da sub-árvore atual, avançando sempre para a esquerda e seguindo as costuras. Em seguida, ela imprime todos os nós da sub-árvore a partir desse nó, avançando sempre para a direita e, quando necessário, seguindo as costuras. A função é recursiva, portanto, ela é chamada para cada sub-árvore esquerda e direita da árvore original. A impressão é feita em ordem crescente das chaves dos itens da árvore.
*/

void deletar_no(ARVORE_COSTURADA **raiz, TIPOCHAVE ch) {
    ARVORE_COSTURADA *no = buscar(*raiz, ch);

    if (no == NULL) {
        return;
    }

    // Caso 1: nó não tem filhos
    if (no->estruturaEsquerda == NULL && no->estruturaDireita == NULL) {
        if (no == *raiz) {
            *raiz = NULL;
        } else if (no->costuraEsquerda && no->costuraDireita) { // nó tem costuras nos dois lados
            ARVORE_COSTURADA *anterior = no->estruturaEsquerda;
            anterior->costuraDireita = no->costuraDireita;
            anterior->estruturaDireita = no->estruturaDireita;
            no->estruturaDireita->estruturaEsquerda = anterior;

            if (no->estruturaDireita->costuraEsquerda) {
                no->estruturaDireita->estruturaEsquerda = anterior;
            }

            free(no);
        } else if (no->costuraEsquerda) { // nó tem costura na esquerda
            ARVORE_COSTURADA *anterior = no->estruturaEsquerda;
            anterior->costuraDireita = no->costuraDireita;
            anterior->estruturaDireita = no->estruturaDireita;
            no->estruturaDireita->estruturaEsquerda = anterior;

            if (no == no->estruturaEsquerda->estruturaDireita) {
                no->estruturaEsquerda->costuraDireita = no->costuraDireita;
            } else {
                no->estruturaEsquerda->estruturaDireita = no->estruturaDireita;
                no->estruturaDireita->costuraEsquerda = true;
            }

            free(no);
        } else { // nó tem costura na direita
            ARVORE_COSTURADA *anterior = no->estruturaDireita;
            anterior->costuraEsquerda = no->costuraEsquerda;
            anterior->estruturaEsquerda = no->estruturaEsquerda;
            no->estruturaEsquerda->estruturaDireita = anterior;

            if (no == no->estruturaDireita->estruturaEsquerda) {
                no->estruturaDireita->costuraEsquerda = no->costuraEsquerda;
            } else {
                no->estruturaDireita->estruturaEsquerda = no->estruturaEsquerda;
                no->estruturaEsquerda->costuraDireita = true;
            }

            free(no);
        }
    } else if (no->estruturaEsquerda == NULL) { // Caso 2: nó tem apenas um filho à direita
        if (no == *raiz) {
            *raiz = no->estruturaDireita;
            (*raiz)->estruturaEsquerda = NULL;
        } else if (no->costuraEsquerda) {
            ARVORE_COSTURADA *anterior = no->estruturaEsquerda;
            anterior->estruturaDireita = no->estruturaDireita;
            anterior->costuraDireita = true;
            no->estruturaDireita->estruturaEsquerda = anterior;
            free(no);
        } else {
            no->estruturaEsquerda->estruturaDireita = no->estruturaDireita;
            no->estruturaDireita->estruturaEsquerda = no->estruturaEsquerda;
            free(no);
        }
} else if (no->estruturaDireita == NULL) { // Caso 3: nó tem apenas um filho à esquerda
        if (no == *raiz) {
            *raiz = no->estruturaEsquerda;
            (*raiz)->estruturaDireita = NULL;
        } else if (no->costuraDireita) {
            ARVORE_COSTURADA *anterior = no->estruturaDireita;
            anterior->estruturaEsquerda = no->estruturaEsquerda;
            anterior->costuraEsquerda = true;
            no->estruturaEsquerda->estruturaDireita = anterior;
            free(no);
        } else {
            no->estruturaDireita->estruturaEsquerda = no->estruturaEsquerda;
            no->estruturaEsquerda->estruturaDireita = no->estruturaDireita;
            free(no);
        }
    } else { // Caso 4: nó tem dois filhos
        ARVORE_COSTURADA *anterior = no->estruturaEsquerda;

        while (anterior->estruturaDireita != NULL && !anterior->costuraDireita) {
            anterior = anterior->estruturaDireita;
        }

        no->item = anterior->item;

        deletar_no(&anterior, anterior->item.chave); // chamar a função recursivamente para deletar o nó anterior
    }
}
/*
A função `deletar_no` possui quatro casos diferentes, de acordo com o número de filhos do nó a ser deletado. O primeiro caso é o do nó sem filhos, em que é necessário verificar se o nó a ser deletado é a raiz ou não, e se tem costuras à esquerda e/ou à direita. Nos demais casos, é necessário ajustar as costuras da árvore quando um nó é deletado.
  */
void destruir_arvore(ARVORE_COSTURADA **raiz) {
    ARVORE_COSTURADA *atual = *raiz;
    ARVORE_COSTURADA *mais_a_esquerda = NULL;

    // Encontrar o nó mais à esquerda da raiz e percorrer a árvore a partir dele em ordem
    while (atual != NULL) {
        while (atual->estruturaEsquerda != NULL && !atual->costuraEsquerda) {
            atual = atual->estruturaEsquerda;
        }

        mais_a_esquerda = atual;

        while (mais_a_esquerda->estruturaDireita != NULL && mais_a_esquerda->costuraDireita) {
            ARVORE_COSTURADA *noAnterior = mais_a_esquerda;
            mais_a_esquerda = mais_a_esquerda->estruturaDireita;
            free(noAnterior);
        }

        ARVORE_COSTURADA *noAnterior = mais_a_esquerda;
        atual = atual->estruturaDireita;

        if (mais_a_esquerda->estruturaDireita == NULL) {
            free(noAnterior);
        }
    }

    *raiz = NULL;
}

/*
A função `destruir_arvore` percorre a árvore em ordem, começando pelo nó mais à esquerda da raiz. Para isso, é necessário encontrar esse nó e, a partir dele, percorrer a árvore seguindo as costuras. A cada nó percorrido, é verificado se ele tem um filho à direita e, caso tenha, é necessário deletar os nós da sub-árvore que se encontra à direita. Depois disso, é possível deletar o nó atual.
  */
int main() {
    ARVORE_COSTURADA *raiz = NULL;

    // inserir nós na árvore
    inserir(&raiz, 50);
    inserir(&raiz, 20);
    inserir(&raiz, 60);
    inserir(&raiz, 10);
    inserir(&raiz, 30);

    // imprimir a árvore
    imprimir_arvore(raiz);

    // buscar um nó na árvore
    ARVORE_COSTURADA *noBuscado = buscar(raiz, 20);
    if (noBuscado != NULL) {
        printf("Nó encontrado! Chave: %d\n", noBuscado->item.chave);
    } else {
        printf("Nó não encontrado!\n");
    }

    // alterar um item em um nó da árvore
    alterar_item(raiz, 20, (ITEM) { 20 });

    // imprimir a árvore novamente
    imprimir_arvore(raiz);

    // deletar um nó da árvore
    deletar_no(&raiz, 20);

    // imprimir a árvore novamente
    imprimir_arvore(raiz);

    // destruir a árvore
    destruir_arvore(&raiz);

    return 0;
}
