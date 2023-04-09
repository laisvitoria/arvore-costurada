# Sobre o código

No primeiro código feito, o professor pediu para diminuirmos o número de ponteiros alocados, podemos visualizar o código aqui: [Primeiro Código](https://github.com/laisvitoria/arvore-costurada/blob/main/lais-arvore-costurada-busca-no.c)

Para reduzir a complexidade. eu fiz [esse código](https://github.com/laisvitoria/arvore-costurada/blob/main/arvores-costuradas-ajustes-alberto.c): que contém, basicamente, a mesma estrutura de uma árvore binária, que o próprio professor fez, e usa os ponteiros livres para costurar a árvore binária.

A estrutura de árvores costuradas de alberto é essa:

/*
typedef int TIPOCHAVE;

typedef enum {NoEsquerdo, NoDireito, NoPai, NoRaiz} DIRECAO;

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

Portanto, está bem semelhante.

# Sobre as funções

Os números que estamos trabalhando são 2 4 6 8 10

Números pré-ordem: 2 4 6 8 10
Números pós-ordem: 10 8 6 4 2
Números in-ordem: **não sei, precisa conferir**

Eu já inseri as funções relacionadas a adição em pré-ordem e a pós ordem, quando se trata de inserir, buscar, e percorrer a lista com os números que foram definidos, para que eles sejam impressos.

Vale notar que por ser uma árvore binária, a lógica por trás da função **insere()** e da função **inserePreOrdem()** é a mesma, tendo em vista que pré-ordem é a ordem normal de inserção em uma árvore binária.

Contudo, gostaria que dessem uma atenção especial a função **inserePósOrdem()**, tendo em vista que, na minha cabeça, com a entrada 2 4 6 8 10, a inserção na pós-ordem deveria ser 10 8 6 4 2. Essa é a saída que obtenho, mas não sei se tá certo.

@Lais eu adaptei um pouco a parte de **busca()** e ela funciona normalmente na função **inserePreOrdem()** mas ela dá uma bugada na função **inserePosOrdem()** com a repetição de alguns valores.

A gente ainda precisa fazer a função **insereInOrdem()** que ainda não fizemos.

@Mateus fez a função remover, mas não tá adaptada para o novo código, precisa ser adaptada e precisamos conferir se o ajuste de ponteiros na árvore binária e nas costuas es~tao corretos.

@Todos a gente ainda não fez uma função alterar, mas provavelmente ela será uma derivação da função buscar, que @Lais fez, então acho que provavelmente será mais tranquilo.

@Todos precisamos colocar todas essas funções para rodar no main simultaneamente.



#### Checklist do Código:

- [x]  Iniciar estrutura de dados → Ariel 24/03
- [x]  Inicializar a árvore → Ariel 24/03
- [x]  Inserção Nó na árvore → Sérgio 31/03
- [x]  Buscar um nó → Laís 31/03
- [x]  Refatorar o código para diminuir o número de ponteiros -> Ariel 07/04
- [x] Remoção de um nó da árvore → Mateus 31/03 
- [x] Inserção  do pré-ordem 07/04  -> Ariel 07/04
- [x] inserção  do pós-ordem 07/04  -> Ariel 07/04
- [ ] Inserção in-ordem
- [ ] Buscar pré-ordem
- [ ] Tirar bug da função de busca
- [ ] Remover
- [ ] Alterar
- [x] Adaptação do pós ordem código refatorado  -> Ariel 07/04
- [x] Adaptação do pré-ordem pro códdigo refatorado  -> Ariel 07/04
- [ ] Inserir todas as funções prontas no main()
- [x]  Destruir a arvore → Ariel 24/03



# Sobre explicações do modelo de código para alberto

Falar as diferenças do código antigo para o código novo (ocupar espaço)

# Sobre como funciona as costuras:

Agora temos apenas um espaço referente a costura, que costura cada nó. a referênncia "costura" na estrutura de dados é equivalente a linha pontilhada na imagem que tá no wpp

Essas estruturas de dados definem uma árvore binária com costura (threaded binary tree). A estrutura ITEM representa o elemento a ser armazenado na árvore binária. A estrutura ARVORE_BINARIA é a própria árvore binária, composta por um ITEM e três ponteiros: esq, dir e costura. Os ponteiros esq e dir apontam para os filhos esquerdo e direito do nó, enquanto que o ponteiro costura é usado para realizar a costura da árvore binária, permitindo percorrer a árvore de forma mais eficiente. A costura consiste em ligar um nó a seu sucessor (ou predecessor) na ordem de percorrimento da árvore, formando uma espécie de lista encadeada a partir da árvore.
