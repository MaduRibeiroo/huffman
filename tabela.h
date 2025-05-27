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


Tabela * buscaPalavra(Tabela *t,char palavra[30])
{
	while(t!= NULL && strcmp(t->reg.palavra,palavra)!=0)
		t=t->prox;
	return t;
}




Tabela* criar(int simb,char palavra[30],unsigned char cod)
{
	Tabela *t=(Tabela*) malloc(sizeof(Tabela));
	t->reg->cod.num= cod;
	strcmp(t->reg->palavra,palavra);
	t->reg=simb=simb;
	t->prox=NULL;
}


//FAZER A BUSCA DENTRO DO INSERIR SAVOLDI CARALHO
void inserirTabela(Tabela** t,int *simb,char palavra[30],unsigned char cod)
{
	Tabela* aux=buscaPalavra(*t,palavra);
	if(aux==NULL)
	{
		aux=criarLinhaTabela(simb++,palavra,cod);
		*aux->freq=1;
		*aux->prox=null;
	}
	else
	{
		aux->freq++;
	}
	if(*t == NULL)
	{
		*t=aux;
	}
	else
	{
		if((*t)->freq > aux->freq)
		{
			aux->prox=*t;
		}
		else
		{
			Tabela* pos=*t;
			while(pos->prox!= NULL && pos->prox->freq < aux->freq )
			{
				pos=pos->prox;
			}
			aux->prox = pos->prox;
			pos->prox=aux;
		}
	}
}


//
// MUITO TRABALHO ARRUMAR ESSA POHA DAI EU FIZ NO MEU DIRETO ALI 
 
/*
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
*/

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

//FALTA exibir tabela
