#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tabela2.h"

#define TF 1000
struct TpTree
{
    int simbolo;
    struct TpTree *esq, *dir;
};
typedef struct TpTree Tree;

void initT(Tree **raiz)
{
    *raiz = NULL;
}

void novoNo(Tree **tree)
{
    *tree = (Tree*)malloc(sizeof(Tree));
    (*tree)->esq = NULL;
    (*tree)->dir = NULL;
    (*tree)->simbolo = -1;
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

char carregarTabela(Tabela **tab, char nomeArquivo[])
{
    FILE *ptr;
    Registro reg;
    char abriu;

    abriu = 0;
    ptr = fopen(nomeArquivo, "rb");
    if(ptr != NULL)
    {
        abriu = 1;
        while(fread(&reg, sizeof(Registro), 1, ptr) == 1)
            inserirRegistroTabela(&*tab, reg);
        fclose(ptr);
    }
    return abriu;
}

void inserirCodigoArvore(Tree **raiz, char codigo[], int simbolo)
{
    int i;
    Tree *aux;

    if(*raiz == NULL)
        novoNo(&*raiz);

    aux = *raiz;
    for(i = 0; codigo[i] != '\0'; i++)
    {
        if(codigo[i] == '0')
        {
            if(aux->esq == NULL)
                novoNo(&(aux->esq));
            aux = aux->esq;
        }
        else
        {
            if(aux->dir == NULL)
                novoNo(&(aux->dir));
            aux = aux->dir;
        }
    }
    aux->simbolo = simbolo;
}

void montarArvorePorCodigos(Tree **raiz, Tabela *tab)
{
    while(tab != NULL)
    {
        inserirCodigoArvore(&*raiz, tab->reg.cod, tab->reg.simb);
        tab = tab->prox;
    }
}

void concatenarPalavra(char frase[], char palavra[])
{
    int i, j;

    i = strlen(frase);
    j = 0;
    while(palavra[j] != '\0' && i < TF - 1)
    {
        frase[i] = palavra[j];
        i++;
        j++;
    }
    frase[i] = '\0';
}

char decodificarFrase(Tree *raiz, Tabela *tab, char nomeArquivo[], char frase[])
{
    FILE *ptr;
    Byte byteLido;
    Tree *aux;
    Tabela *linha;
    char bits[9], deuCerto;
    int i;

    deuCerto = 0;
    ptr = fopen(nomeArquivo, "rb");
    if(ptr != NULL)
    {
        deuCerto = 1;
        frase[0] = '\0';
        aux = raiz;
        while(fread(&(byteLido.num), sizeof(unsigned char), 1, ptr) == 1 && deuCerto == 1)
        {
            byteParaBits(byteLido, bits);
            i = 0;
            while(i < 8 && deuCerto == 1)
            {
                if(bits[i] == '0')
                    aux = aux->esq;
                else
                    aux = aux->dir;

                if(aux == NULL)
                    deuCerto = 0;
                else
                {
                    if(aux->esq == NULL && aux->dir == NULL)
                    {
                        if(buscarSimbolo(tab, aux->simbolo, &linha) == 1)
                        {
                            concatenarPalavra(frase, linha->reg.palavra);
                            aux = raiz;
                        }
                        else
                            deuCerto = 0;
                    }
                }
                i++;
            }
        }
        fclose(ptr);
    }
    return deuCerto;
}

void executar()
{
    Tabela *tab;
    Tree *raiz;
    char frase[TF];

    initTabela(&tab);
    initT(&raiz);

    if(carregarTabela(&tab, "registro.dat") == 1)
    {
        montarArvorePorCodigos(&raiz, tab);
        if(decodificarFrase(raiz, tab, "codificado.dat", frase) == 1)
        {
            exibirTabela(tab);
            printf("\nFrase decodificada:\n%s\n", frase);
        }
        else
            printf("Nao foi possivel decodificar o arquivo codificado.dat.\n");
    }
    else
        printf("Nao foi possivel abrir o arquivo registro.dat.\n");

    excluirTabela(&tab);
    excluirArvore(&raiz);
}

int main()
{
    executar();
    return 0;
}
