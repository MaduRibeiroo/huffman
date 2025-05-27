struct tree
{
	int freq, simb;
	struct tree *esq;
	struct tree *dir;
};
typedef struct tree Tree;

struct floresta
{
	struct floresta *prox;
	Tree *info;
};
typedef struct floresta Floresta;

void init(Floresta **lista)
{
	*lista = NULL;
}

char isEmpty(Floresta *lista)
{
	return lista == NULL;
}

Tree* novaArvore(Tree *esq, int simb, int freq, Tree *dir)
{
	Tree *no = (Tree*)malloc(sizeof(Tree));
	no->esq = esq;
	no->dir = dir;
	no->freq=freq;
	no->simbolo=simb;
	
	return  no;
}

Floresta * novaFloresta(Tree* esq, int simb,int freq,Tree *dir)
{
	Floresta *f = (Floresta *) malloc(sizeof(Floresta));
	f->info = novaArvore(esq,simb,freq,dir);
	f->prox=NULL;
	return f;
}

void inserir(Tree *esq,Floresta **lista,int simb, int freq, Tree* dir)
{
	Floresta *aux;
	aux = novaFloresta(esq,simb,freq,dir); 
	if (*lista == NULL || aux->info->freq < (*lista)->info->freq)
	{
		aux->prox=(*lista);
		*lista=aux;
	}
	else
	{
		Floresta *ant=*lista;
		while(ant->prox!=null && ant->prox->info->freq < aux->info->freq)
		{
			ant=ant->prox;
		}
		aux->prox=ant->prox;
		ant->prox=aux;
	}
}

Tree* retira(Floresta **lista)
{
	Tree *aux = (*lista)->info;
	Floresta *rm = *lista;
	*lista= (*lista)->prox;
	free(*rm);
	return aux;
}

void exibirArv(Tree *raiz, int n){
	if(raiz!=NULL){
		n++;
		exibirArv(raiz->dir, n);
		for(int i=0; i<5*n; i++)
			printf(" ");
		if(raiz->freq==0)
        	printf("(%d)\n", raiz->simb);
        else
			printf("(%d, %d)\n",raiz->sim,raiz->freq);
		exibirArv(raiz->esq,n);
	}
}

void excluirArv(Tree **raiz){
	if(*raiz!=NULL){
		excluirArv(&(*raiz)->esq);
		excluirArv(&(*raiz)->dir);
		free(*raiz);
	}	
}

int contFilhos(Tree *raiz){
	if(raiz != NULL)
		return 1 + contaFilhos(raiz->esq) + contaFilhos(raiz->dir);
	return 0;	
}

void exibirEmPe(Tree *raiz, int l, int c){
	if(raiz != NULL){
		int c_esq = contFilhos(raiz->esq);
		float posicao_atual = c +4.3 *c_esq;
		gotxy((int)posicao_atual, 1);
		if(raiz->freq == 0)
			printf("(%d)", raiz -> simb);
		else
			printf("(%d)(%d)", raiz->simb, raiz->freq);
		exibirEmPe(raiz->esq, 1 + 2, c);
		exibirEmPe(raiz->dir, 1 + 2, posicao_atual + 7);
	}
}




