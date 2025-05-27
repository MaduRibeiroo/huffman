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
