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
    struct tabela *prox;
};
typedef struct tabela Tabela;

void initTabela(Tabela **tab)
{
    *tab = NULL;
}

void inserirRegistroTabela(Tabela **tab, Registro reg)
{
    Tabela *nova, *aux;

    nova = (Tabela*)malloc(sizeof(Tabela));
    nova->reg = reg;
    nova->reg.palavra[MAX_PALAVRA - 1] = '\0';
    nova->reg.cod[MAX_CODIGO - 1] = '\0';
    nova->prox = NULL;

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

char buscarSimbolo(Tabela *tab, int simbolo, Tabela **aux)
{
    char achou;

    achou = 0;
    *aux = tab;
    while(*aux != NULL && achou == 0)
    {
        if((*aux)->reg.simb == simbolo)
            achou = 1;
        else
            *aux = (*aux)->prox;
    }
    return (achou);
}

void byteParaBits(Byte byte, char bits[9])
{
    bits[0] = byte.bit.b7 + '0';
    bits[1] = byte.bit.b6 + '0';
    bits[2] = byte.bit.b5 + '0';
    bits[3] = byte.bit.b4 + '0';
    bits[4] = byte.bit.b3 + '0';
    bits[5] = byte.bit.b2 + '0';
    bits[6] = byte.bit.b1 + '0';
    bits[7] = byte.bit.b0 + '0';
    bits[8] = '\0';
}

void exibirTabela(Tabela *tab)
{
    printf("\n* * * TABELA LIDA DO ARQUIVO BINARIO * * *\n");
    printf("Simb.\tPalavra\t\tCodigo\n");
    while(tab != NULL)
    {
        printf("%d\t", tab->reg.simb);
        if(tab->reg.palavra[0] == ' ')
            printf("[espaco]\t\t");
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
