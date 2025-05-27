struct TpTree{
	int frequencia, simbolo;
	struct TpTree *esq, *dir;
};typedef struct TpTree Tree;

//Inicia a arvore
void initT(Tree **raiz){
	*raiz=NULL;
}

void novoNo(Tree **tree){
	*tree=(Tree*)malloc(sizeof(Tree));
	(*tree)->esq = (*tree)->dir = NULL;
	(*tree)->frequencia = NULL;
	(*tree)->simbolo = NULL;
}

void CriaNo(Tree **tree, int freq, int simbolo){
	novoNo(&*tree);
	(*tree)->frequencia = frequencia;
	(*tree)->simbolo = simbolo;
}

void exibirArv(Tree *raiz, int n){
	if(raiz!=NULL){
		n++;
		exibirArv(raiz->dir, n);
		for(int i=0; i<5*n; i++)
			printf(" ");
		if(raiz->frequencia==0)
        	printf("(%d)\n", raiz->simbolo);
        else
			printf("(%d, %d)\n",raiz->simbolo,raiz->frequencia);
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
		if(raiz->frequencia == 0)
			printf("(%d)", raiz -> simbolo);
		else
			printf("(%d)(%d)", raiz->simbolo, raiz->frequencia);
		exibirEmPe(raiz->esq, 1 + 2, c);
		exibirEmPe(raiz->dir, 1 + 2, posicao_atual + 7);
	}
}








