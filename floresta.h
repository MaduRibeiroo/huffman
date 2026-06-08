struct tree
{
    int freq, simb;
    struct tree *esq;
    struct tree *dir;
};
typedef struct tree Tree;

struct floresta
{
    Tree *info;
    struct floresta *prox;
};
typedef struct floresta Floresta;

void initFloresta(Floresta **lista)
{
    *lista = NULL;
}

Tree *novaArvore(Tree *esq, int simb, int freq, Tree *dir)
{
    Tree *no;

    no = (Tree*)malloc(sizeof(Tree));
    no->esq = esq;
    no->dir = dir;
    no->freq = freq;
    no->simb = simb;
    return no;
}

Floresta *novaFloresta(Tree *esq, int simb, int freq, Tree *dir)
{
    Floresta *nova;

    nova = (Floresta*)malloc(sizeof(Floresta));
    nova->info = novaArvore(esq, simb, freq, dir);
    nova->prox = NULL;
    return nova;
}

void inserirFloresta(Tree *esq, Floresta **lista, int simb, int freq, Tree *dir)
{
    Floresta *nova, *aux;

    nova = novaFloresta(esq, simb, freq, dir);
    if(*lista == NULL || nova->info->freq < (*lista)->info->freq)
    {
        nova->prox = *lista;
        *lista = nova;
    }
    else
    {
        aux = *lista;
        while(aux->prox != NULL && aux->prox->info->freq <= nova->info->freq)
            aux = aux->prox;
        nova->prox = aux->prox;
        aux->prox = nova;
    }
}

Tree *retiraFloresta(Floresta **lista)
{
    Floresta *remover;
    Tree *arv;

    remover = *lista;
    arv = remover->info;
    *lista = remover->prox;
    free(remover);
    return arv;
}

void exibirNo(Tree *no)
{
    printf("[%d]\t[%d]\n", no->freq, no->simb);
}

void exibirFlo(Floresta *lista)
{
    printf("\n* * * LISTA ENCADEADA ORDENADA * * *\n");
    printf("Freq.\tSimb.\n");
    while(lista != NULL)
    {
        exibirNo(lista->info);
        lista = lista->prox;
    }
}

void exibirArvH(Tree *raiz, int nivel)
{
    int i;

    if(raiz != NULL)
    {
        exibirArvH(raiz->dir, nivel + 1);
        for(i = 0; i < nivel * 5; i++)
            printf(" ");
        if(raiz->simb == -1)
            printf("(%d)\n", raiz->freq);
        else
            printf("(S%d,F%d)\n", raiz->simb, raiz->freq);
        exibirArvH(raiz->esq, nivel + 1);
    }
}

void excluirArvore(Tree **raiz)
{
    if(*raiz != NULL)
    {
        excluirArvore(&((*raiz)->esq));
        excluirArvore(&((*raiz)->dir));
        free(*raiz);
        *raiz = NULL;
    }
}
