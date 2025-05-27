#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "arvore.h"
#include "tabela.h"
#include "layout.h"
#include "floresta.h"

#define TF 200


char Menu()
{
	int c,l;
	char op;
	do
	{
		LayoutMenu();
		gotoxy(25,3);
		printf("#  #  MENU  #  #");
		c=3;
		l=7;
		gotoxy(c,l);
		printf("[A] - Exibir a frase");
		l+=3;
		gotoxy(c,l);
		printf("[B] - Exibir a lista");
		l+=3;
		gotoxy(c,l);
		printf("[C] - Criar arquivo codificado");
		l+=3;
		gotoxy(c,l);
		printf("[D] - Exibir arvore em pe");
		l+=3;
		gotoxy(c,l);
		printf("[ESC] - Sair");
		l=27;
		gotoxy(c,l);
		printf("OPCAO: ");
		fflush(stdin);
		op=toupper(getche());
	}while(op!='A' && op!='B' && op!='C' && op!='D' && op!=27 );
	return op;
}

Floresta * criaFloresta(Tabela *t)
 {
	Floresta *f;
	initFloresta(&f);
	while(t!=NULL)
	{
		inserirFloresta(NULL,&f,t->reg.simb,t->freq,NULL);
		t=t->prox;
	}
	return f;
 }

Tree * criaArvoreHuffman(Floresta **f)
{
	Tree* dir, *esq;
	while(*f !=NULL)
	{
		esq=retiraFloresta(&*f);
		if(*f !=NULL)
		{
			dir=retiraFloresta(&*f);
		}
		inserirFloresta(esq,&*f,-1,(esq->freq + dir->freq),dir);
	}
	return esq;
}

// CRIAR A FUNCAO PARA FAZER  A BOMBA DO ARQ BINARIO


void gravarFrase(Tabela **tab, int *TL){
    char letra, palavra[30], aux[2];
    int i=0;
    FILE *ptr = fopen("entrada.txt", "r");
    letra = tolower(fgetc(ptr));
    while(!feof(ptr)){
        if(letra == 32 || letra == 44 || letra == 46 || letra == '/0'){//espaco, virgula, ponto, final de linha
            if(i!=0){
                aux[0] = letra;
                aux[1] = '/0';
                inserirTabela(&*tab, tl, aux, cod);

            }
            palavra[i] = '/0';
            inserirTabela(&*tab, tl, palavra, cod);
            i = 0;
        }  
        palavra[i] = letra;
        letra = tolower(fgetc(ptr));
        i++;
    }
    fclose(ptr);
}

void executar(){
    char op;
    Floresta *flo;
    Tabela *tab;
    initTabela(tab);
    init(flo);
    do{
		op=Menu();
		switch(op){
			case 'B':
				system("cls");
				//exibir lista
                exibirArv(raiz,-1);
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'C':
				system("cls");
                //criar arquivo
				printf("A frase decodificada foi:\n %s\n ",frase);
				teste();
				exibirTabela(tab,1,4); //aqui
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
			case 'D':
				system("cls");
                //exibir arvore
				teste();
				exibirTabela(tab,1,4); //aqui
				gotoxy(1,1);
				fflush(stdin);
				getch();
				break;
		}
			
	}while(op!=27);
}

int main(){
    executar();
    return 0;
}
