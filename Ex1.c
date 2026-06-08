#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "tabela.h"
#include "floresta.h"

#define TF 5000

char ehLetraNumero(int letra)
{
    char resp;

    resp = 0;
    if(letra >= 'a' && letra <= 'z')
        resp = 1;
    else
    {
        if(letra >= '0' && letra <= '9')
            resp = 1;
    }
    return (resp);
}

char ehEspaco(int letra)
{
    char resp;

    resp = 0;
    if(letra == ' ' || letra == '\n' || letra == '\t' || letra == '\r')
        resp = 1;
    return (resp);
}

void finalizarPalavraTabela(Tabela **tab, int *simb, char palavra[], int *tam, int *podeInserirEspaco)
{
    if(*tam > 0)
    {
        palavra[*tam] = '\0';
        inserirTabela(&*tab, &*simb, palavra);
        *tam = 0;
        *podeInserirEspaco = 1;
    }
}

void lerTextoBase(Tabela **tab, int *simb, char nomeArquivo[])
{
    FILE *ptr;
    int letra, tam, podeInserirEspaco;
    char palavra[MAX_PALAVRA], espaco[2];

    initTabela(&*tab);
    ptr = fopen(nomeArquivo, "r");
    tam = 0;
    podeInserirEspaco = 0;
    espaco[0] = ' ';
    espaco[1] = '\0';

    if(ptr != NULL)
    {
        letra = fgetc(ptr);
        while(letra != EOF)
        {
            letra = tolower(letra);
            if(ehLetraNumero(letra) == 1)
            {
                if(tam < MAX_PALAVRA - 1)
                {
                    palavra[tam] = letra;
                    tam = tam + 1;
                }
            }
            else
            {
                finalizarPalavraTabela(&*tab, &*simb, palavra, &tam, &podeInserirEspaco);
                if(ehEspaco(letra) == 1)
                {
                    if(podeInserirEspaco == 1)
                    {
                        inserirTabela(&*tab, &*simb, espaco);
                        podeInserirEspaco = 0;
                    }
                }
            }
            letra = fgetc(ptr);
        }
        finalizarPalavraTabela(&*tab, &*simb, palavra, &tam, &podeInserirEspaco);
        fclose(ptr);
    }
}

void criarFloresta(Floresta **flo, Tabela *tab)
{
    initFloresta(&*flo);
    while(tab != NULL)
    {
        inserirFloresta(NULL, &*flo, tab->reg.simb, tab->freq, NULL);
        tab = tab->prox;
    }
}

Tree *criarArvoreHuffman(Floresta **flo)
{
    Tree *esq, *dir, *raiz;

    raiz = NULL;
    if(*flo != NULL)
    {
        while((*flo)->prox != NULL)
        {
            esq = retiraFloresta(&*flo);
            dir = retiraFloresta(&*flo);
            inserirFloresta(esq, &*flo, -1, esq->freq + dir->freq, dir);
        }
        raiz = retiraFloresta(&*flo);
    }
    return (raiz);
}

void descobrirCodigos(Tree *raiz, Tabela *tab, char codigo[], int pos)
{
    Tabela *linha;

    if(raiz != NULL)
    {
        if(raiz->esq == NULL && raiz->dir == NULL)
        {
            if(pos == 0)
            {
                codigo[0] = '0';
                codigo[1] = '\0';
            }
            else
                codigo[pos] = '\0';

            linha = buscaSimb(tab, raiz->simb);
            if(linha != NULL)
                strcpy(linha->reg.cod, codigo);
        }
        else
        {
            codigo[pos] = '0';
            descobrirCodigos(raiz->esq, tab, codigo, pos + 1);
            codigo[pos] = '1';
            descobrirCodigos(raiz->dir, tab, codigo, pos + 1);
        }
    }
}

void gravarRegistros(Tabela *tab, char nomeArquivo[])
{
    FILE *ptr;

    ptr = fopen(nomeArquivo, "wb");
    if(ptr != NULL)
    {
        while(tab != NULL)
        {
            fwrite(&(tab->reg), sizeof(Registro), 1, ptr);
            tab = tab->prox;
        }
        fclose(ptr);
    }
}

void colocarBit(Byte *byte, int pos, char bit)
{
    unsigned char valor;

    valor = bit - '0';
    switch(pos)
    {
        case 0:
            byte->bit.b7 = valor;
            break;
        case 1:
            byte->bit.b6 = valor;
            break;
        case 2:
            byte->bit.b5 = valor;
            break;
        case 3:
            byte->bit.b4 = valor;
            break;
        case 4:
            byte->bit.b3 = valor;
            break;
        case 5:
            byte->bit.b2 = valor;
            break;
        case 6:
            byte->bit.b1 = valor;
            break;
        case 7:
            byte->bit.b0 = valor;
            break;
    }
}

void gravarBit(FILE *ptr, Byte *byte, int *posByte, char bit, char sequencia[], int *qtdBits)
{
    colocarBit(&*byte, *posByte, bit);
    if(*qtdBits < TF - 1)
    {
        sequencia[*qtdBits] = bit;
        sequencia[*qtdBits + 1] = '\0';
    }
    *qtdBits = *qtdBits + 1;
    *posByte = *posByte + 1;
    if(*posByte == 8)
    {
        fwrite(&(byte->num), sizeof(unsigned char), 1, ptr);
        byte->num = 0;
        *posByte = 0;
    }
}

void gravarCodigoPalavra(Tabela *tab, char palavra[], FILE *ptr, Byte *byte, int *posByte, char sequencia[], int *qtdBits)
{
    Tabela *linha;
    int i;

    linha = buscaPalavra(tab, palavra);
    if(linha != NULL)
    {
        i = 0;
        while(linha->reg.cod[i] != '\0')
        {
            gravarBit(ptr, &*byte, &*posByte, linha->reg.cod[i], sequencia, &*qtdBits);
            i = i + 1;
        }
    }
}

void finalizarPalavraCodificada(Tabela *tab, char palavra[], int *tam, FILE *ptr, Byte *byte, int *posByte, char sequencia[], int *qtdBits, int *podeInserirEspaco)
{
    if(*tam > 0)
    {
        palavra[*tam] = '\0';
        gravarCodigoPalavra(tab, palavra, ptr, &*byte, &*posByte, sequencia, &*qtdBits);
        *tam = 0;
        *podeInserirEspaco = 1;
    }
}

int codificarFrase(Tabela *tab, char frase[], char nomeArquivo[], char sequencia[])
{
    FILE *ptr;
    Byte byte;
    int i, tam, posByte, qtdBits, podeInserirEspaco, letra;
    char palavra[MAX_PALAVRA], espaco[2];

    qtdBits = -1;
    ptr = fopen(nomeArquivo, "wb");
    if(ptr != NULL)
    {
        byte.num = 0;
        posByte = 0;
        qtdBits = 0;
        tam = 0;
        i = 0;
        podeInserirEspaco = 0;
        sequencia[0] = '\0';
        espaco[0] = ' ';
        espaco[1] = '\0';

        while(frase[i] != '\0')
        {
            letra = tolower(frase[i]);
            if(ehLetraNumero(letra) == 1)
            {
                if(tam < MAX_PALAVRA - 1)
                {
                    palavra[tam] = letra;
                    tam = tam + 1;
                }
            }
            else
            {
                finalizarPalavraCodificada(tab, palavra, &tam, ptr, &byte, &posByte, sequencia, &qtdBits, &podeInserirEspaco);
                if(ehEspaco(letra) == 1)
                {
                    if(podeInserirEspaco == 1)
                    {
                        gravarCodigoPalavra(tab, espaco, ptr, &byte, &posByte, sequencia, &qtdBits);
                        podeInserirEspaco = 0;
                    }
                }
            }
            i = i + 1;
        }
        finalizarPalavraCodificada(tab, palavra, &tam, ptr, &byte, &posByte, sequencia, &qtdBits, &podeInserirEspaco);
        if(posByte > 0)
            fwrite(&(byte.num), sizeof(unsigned char), 1, ptr);
        fclose(ptr);
    }
    return (qtdBits);
}

void executar()
{
    Tabela *tab;
    Floresta *flo;
    Tree *arv;
    int simb, qtdBits;
    char codigo[MAX_CODIGO], sequencia[TF];
    char fraseCodificar[] = "buscar e tentar e errar";

    simb = 0;
    lerTextoBase(&tab, &simb, "entradinha.txt");
    printf("Texto base lido de entradinha.txt\n");

    criarFloresta(&flo, tab);
    exibirFlo(flo);

    arv = criarArvoreHuffman(&flo);
    descobrirCodigos(arv, tab, codigo, 0);

    exibirTabela(tab);
    printf("\n* * * ARVORE DE HUFFMAN * * *\n");
    exibirArvH(arv, 0);

    gravarRegistros(tab, "registro.dat");
    qtdBits = codificarFrase(tab, fraseCodificar, "codificado.dat", sequencia);

    printf("\nFrase usada para codificar:\n%s\n", fraseCodificar);
    printf("\nSequencia de bits gravada em codificado.dat:\n%s\n", sequencia);
    printf("Total de bits validos: %d\n", qtdBits);

    excluirTabela(&tab);
    excluirArvore(&arv);
}

int main()
{
    executar();
    return (0);
}
