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


void initTabela(Tabela **T)
{
	*T=NULL;
}

char isEmpty(Tabela *T)
{
	return T == NULL;
}

// Busca uma palavra na tabela e retorna o ponteiro para o nÃ³, se encontrado.
Tabela * buscaPalavra(Tabela *t,char palavra[30])
{
	while(t!= NULL && strcmp(t->reg.palavra,palavra)!=0)
		t=t->prox;
	return t;
}



// Insere uma nova palavra na tabela, atualizando a frequÃªncia ou criando novo nÃ³ ordenadamente.
Tabela* criarLinhaTabela(int simb,char palavra[30],unsigned char cod)
{
	Tabela *t=(Tabela*) malloc(sizeof(Tabela));
	t->reg.cod.num = cod;
	strcmp(t->reg.palavra,palavra);
	t->reg.simb=simb;
	t->prox=NULL;
	return t;
}


// Insere uma nova palavra na tabela, atualizando a frequÃªncia ou criando novo nÃ³ ordenadamente.
void inserirTabela(Tabela** t,int &simb, char palavra[30], unsigned char cod)
{
	Tabela* aux=buscaPalavra(*t,palavra);
	if(aux==NULL)
	{
		aux=criarLinhaTabela(simb++,palavra,cod);
		aux->freq=1;
		aux->prox=NULL;
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


// Exibe a tabela de símbolos formatada em colunas com bordas na tela, usando caracteres gráficos.
void exibirTab(Tabela *tab, int ci, int li){
	int i, j, vetor[4], aux;
	vetor[0] = ci + 20;
	for(i = 1; i < 4; i++)
		vetor[i] = vetor[i - 1] + 20;
	if(tab->freq == 0)
		vetor[3] = vetor[2];

	gotoxy(ci, li);
	printf("%c", 201); // canto superior esquerdo

	for(i = ci + 1; i < vetor[3]; i++){
		gotoxy(i, li);
		if(i == vetor[0] || i == vetor[1] || i == vetor[2])
			printf("%c", 203); // junção de colunas
		else
			printf("%c", 205); // linha horizontal
	}
	gotoxy(vetor[3], li);
	printf("%c", 187); // canto superior direito

	i = li + 1;

	// cabeçalho
	gotoxy(ci, i);         printf("%c", 186); // borda esquerda
	gotoxy(vetor[0], i);   printf("%c", 186);
	gotoxy(vetor[1], i);   printf("%c", 186);
	gotoxy(vetor[2], i);   printf("%c", 186);
	gotoxy(vetor[3], i);   printf("%c", 186); // borda direita

	aux = strlen("Palavra") / 2;
	gotoxy((ci + vetor[0]) / 2 - aux, i);
	printf("PALAVRA");

	aux = strlen("Simbolo") / 2;
	gotoxy((vetor[0] + vetor[1]) / 2 - aux, i);
	printf("SIMBOLO");

	aux = strlen("Codigo") / 2;
	gotoxy((vetor[1] + vetor[2]) / 2 - aux, i);
	printf("CODIGO");

	if(vetor[2] != vetor[3]){
		aux = strlen("Frequencia") / 2;
		gotoxy((vetor[2] + vetor[3]) / 2 - aux, i);
		printf("FREQUENCIA");
	}

	i++;

	// linha divisória
	gotoxy(ci, i);
	printf("%c", 204); // junção esquerda
	for(j = ci + 1; j < vetor[3]; j++){
		gotoxy(j, i);
		if(j == vetor[0] || j == vetor[1] || j == vetor[2])
			printf("%c", 206); // junção de colunas
		else
			printf("%c", 205); // linha horizontal
	}
	gotoxy(vetor[3], i);
	printf("%c", 185); // junção direita

	// linhas de dados
	while(tab != NULL){
		i++;
		gotoxy(ci, i);         printf("%c", 186); // borda esquerda
		gotoxy(vetor[0], i);   printf("%c", 186);
		gotoxy(vetor[1], i);   printf("%c", 186);
		gotoxy(vetor[2], i);   printf("%c", 186);
		gotoxy(vetor[3], i);   printf("%c", 186); // borda direita

		if(tab->reg.palavra[0] == ' '){
			aux = strlen("'Espaco'") / 2;
			gotoxy((ci + vetor[0]) / 2 - aux, i);
			printf("'Espaco'");
		}
		else{
			aux = strlen(tab->reg.palavra) / 2;
			gotoxy((ci + vetor[0]) / 2 - aux, i);
			printf("%s", tab->reg.palavra);
		}

		gotoxy((vetor[0] + vetor[1]) / 2 - 1, i);
		printf("%d", tab->reg.simb);

		gotoxy((vetor[1] + vetor[2]) / 2 - 1, i);
		printf("%d", tab->reg.cod.num); // usa o campo correto do union

		if(vetor[2] != vetor[3]){
			gotoxy((vetor[2] + vetor[3]) / 2 - 1, i);
			printf("%d", tab->freq);
		}

		i++;
		gotoxy(ci, i);
		printf("%c", 204); // borda esquerda da linha

		for(j = ci + 1; j < vetor[3]; j++){
			gotoxy(j, i);
			if(j == vetor[0] || j == vetor[1] || j == vetor[2])
				printf("%c", 206); // cruzamento
			else
				printf("%c", 205); // linha horizontal
		}
		gotoxy(vetor[3], i);
		printf("%c", 185); // borda direita

		tab = tab->prox;
	}

	// base final da tabela
	gotoxy(ci, i);
	printf("%c", 200); // canto inferior esquerdo
	for(j = ci + 1; j < vetor[3]; j++){
		gotoxy(j, i);
		if(j == vetor[0] || j == vetor[1] || j == vetor[2])
			printf("%c", 202); // divisões de colunas
		else
			printf("%c", 205); // linha horizontal
	}
	gotoxy(vetor[3], i);
	printf("%c", 188); // canto inferior direito
}



//
// MUITO TRABALHO ARRUMAR DAI EU FIZ NO MEU DIRETO ALI 
 
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

// Busca uma entrada na tabela pelo sÃ­mbolo.
char BuscarSimbolo(Tabela *tab,int simb,Tabela **aux){
	*aux=tab;
	while(*aux!=NULL && (*aux)->reg.simb!=simb)
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
