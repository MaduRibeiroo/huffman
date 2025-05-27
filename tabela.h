#include<string.h>

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
 struct bits bi;
 unsigned char num;
};

struct registro{
	int simb;
	char palavra[30];
	union byte cod;
};
typedef struct registro Registro;

struct tabela{
	Registro reg;
	int freq;
	struct tabela *prox;
};
typedef struct tabela Tabela;


void init(Tabela **T)
{
	*T=NULL;
}

char isEmpty(Tabela *T)
{
	return T == NULL;
}

Tabela* criar(int simb,char palavra[30],unsigned char cod,int *tl)
{
	Tabela *t=(Tabela*) malloc(sizeof(Tabela));
	t->reg->cod.num= cod;
	strcmp(t->reg->palavra,palavra);
	t->reg=simb=tl;
	t->prox=NULL;
}

void inserir(Tabela** t,int simb,char palavra[30],unsigned char cod,int freq,int *tl)
{
	Tabela* aux=criar(simb,palavra,cod,tl);
	*aux->freq=freq;
	*aux->prox=null;
	tl++;
	if(*t == NULL)
	{
		*t=aux;
	}
	else
	{
		Tabela* pos=*t;
		while(pos->prox!=null)
		{
			pos=pos->prox;
		}
		pos->prox=aux;
	}
}

void inserirTabelaOrdenado(Tabela **tab, Registro reg){
	Tabela *aux, *ant, *nova;
	nova = (Tabela*)malloc(sizeof(Tabela));
	nova -> prox = NULL;
	nova -> reg = reg;
	if(*tab==NULL)
		*tab = nova;
	else{
		if(tab.freq>(*tab)->reg.freq){
			nova->prox = *tab;
			*tab = nova;
		}
		else{
			ant = aux = *tab;
			while(aux!=NULL && reg.freq<=aux->reg.freq){
				ant =aux;
				aux = aux->prox;
			}
			ant->prox = nova;
			nova->prox = aux;
		}
	}
}

char BuscarSimbolo(Tabela *tab,int simb,Tabela **aux){
	*aux=tab;
	while(*aux!=NULL && (*aux)->reg.simbolo!=simb)
		*aux = (*aux)->prox;
	if(*aux!=NULL)
		return 1;
	return 0;
}

void excluirTab(Tabela **tab){
	Tabela *aux;
	while(*tab!=NULL){
		aux = *tab;
		*tab = aux->prox;
		free (aux);
	}
}

//FALTA FAZER O EXIBIR TABELA 
