#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PALAVRA 40
#define MAX_CODIGO 100

struct bits
{
    unsigned char b7:1;
    unsigned char b6:1;
    unsigned char b5:1;
    unsigned char b4:1;
    unsigned char b3:1;
    unsigned char b2:1;
    unsigned char b1:1;
    unsigned char b0:1;
};

union byte
{
    unsigned char num;
    struct bits bit;
};
typedef union byte Byte;

struct registro
{
    int simb;
    char palavra[MAX_PALAVRA];
    char cod[MAX_CODIGO];
};
typedef struct registro Registro;

struct tabela
{
    Registro reg;
    int freq;
    struct tabela *prox;
};
typedef struct tabela Tabela;

void initTabela(Tabela **tab)
{
    *tab = NULL;
}

Tabela *buscaPalavra(Tabela *tab, char palavra[])
{
    while(tab != NULL && strcmp(tab->reg.palavra, palavra) != 0)
        tab = tab->prox;
    return tab;
}

Tabela *buscaSimb(Tabela *tab, int simb)
{
    while(tab != NULL && tab->reg.simb != simb)
        tab = tab->prox;
    return tab;
}

Tabela *criarLinhaTabela(int simb, char palavra[])
{
    Tabela *nova;

    nova = (Tabela*)malloc(sizeof(Tabela));
    nova->reg.simb = simb;
    strcpy(nova->reg.palavra, palavra);
    strcpy(nova->reg.cod, "");
    nova->freq = 1;
    nova->prox = NULL;
    return nova;
}

void inserirTabela(Tabela **tab, int *simb, char palavra[])
{
    Tabela *aux, *nova;

    aux = buscaPalavra(*tab, palavra);
    if(aux == NULL)
    {
        nova = criarLinhaTabela(*simb, palavra);
        *simb = *simb + 1;
        if(*tab == NULL)
            *tab = nova;
        else
        {
            aux = *tab;
            while(aux->prox != NULL)
                aux = aux->prox;
            aux->prox = nova;
        }
    }
    else
        aux->freq = aux->freq + 1;
}

void exibirTabela(Tabela *tab)
{
    printf("\n* * * TABELA DE REGISTROS * * *\n");
    printf("Freq.\tSimb.\tPalavra\t\tCodigo\n");
    while(tab != NULL)
    {
        printf("%d\t%d\t", tab->freq, tab->reg.simb);
        if(tab->reg.palavra[0] == ' ')
            printf("[espaco]\t");
        else
            printf("[%s]\t\t", tab->reg.palavra);
        printf("%s\n", tab->reg.cod);
        tab = tab->prox;
    }
}

void excluirTabela(Tabela **tab)
{
    Tabela *aux;

    while(*tab != NULL)
    {
        aux = *tab;
        *tab = aux->prox;
        free(aux);
    }
}
