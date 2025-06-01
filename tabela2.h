struct bits{
	unsigned char b7:1; 
	unsigned char b6:1; 
	unsigned char b5:1; 
	unsigned char b4:1; 
	unsigned char b3:1; 
	unsigned char b2:1; 
	unsigned char b1:1; 
	unsigned char b0:1;
};

union byte{
	unsigned char cod;
	struct bits bit;
};typedef union byte Byte;

struct registro{
	int simb;
	char palavra[50], cod[20];
};typedef struct registro Registro;

struct tabela{
	Registro reg;
	int freq;
	struct tabela *prox;
};typedef struct tabela Tabela;

void init(Tabela **tab){
	*tab=NULL;
}

void novaLinha(char palavra[], int simbolo, Tabela**nova){
	*nova = (Tabela*)malloc(sizeof(Tabela));
	(*nova)->prox = NULL;
	(*nova)->reg.simb = simbolo;
	(*nova)->freq = 0;
	strcpy((*nova)->reg.palavra, palavra);	
}


char BuscarPalavra(Tabela *tab,char palavra[],Tabela **aux){
	*aux=tab;
	while(*aux!=NULL && stricmp((*aux)->reg.palavra,palavra))
		*aux=(*aux)->prox;
	if(*aux!=NULL)
		return 1;
	return 0;
}

char buscarSimbolo(Tabela *tab, int simbolo, Tabela**aux){
	*aux = tab;
	while(*aux!=NULL && (*aux)->reg.simb != simbolo)
		*aux = (*aux)->prox;
	if(*aux != NULL)
		return 1;
	return 0;		
}	

void inserirTabela(Tabela **tab, char palavra[]){ //Se a palavra ja estiver na lista ele apenas acidiona frequencia, caso contrário adiciona na lista
	Tabela *aux,*nova;
	if(!BuscarPalavra(*tab,palavra,&aux)){
		novaLinha(palavra,0,&nova);

		aux=*tab;
		if(aux==NULL)
			*tab=nova;
		else{
			while(aux->prox!=NULL)
				aux=aux->prox;
			aux->prox=nova;
		}
		aux=nova;
	}
	aux->freq++;
	
}

void inserirTabelaOrd(Tabela **tab, Registro reg) {//Insere de acordo com frequencia decrescente
    Tabela *aux;
    char existe;

    // Verifica se a palavra já existe
    existe = BuscarPalavra(*tab, reg.palavra, &aux);

    // Se existir, incrementa a frequência
    if (existe == 1)
        aux->freq = aux->freq + 1;
	else{
        Tabela *nova, *atual, *anterior;

        nova = (Tabela*) malloc(sizeof(Tabela));
        nova->reg = reg;
        nova->freq = 1;
        nova->prox = NULL;

        // Lista vazia ou nova frequência maior que o primeiro
        if (*tab == NULL || nova->freq > (*tab)->freq) {
            nova->prox = *tab;
            *tab = nova;
        } else {
            anterior = NULL;
            atual = *tab;

            // Procura a posição correta
            while (atual != NULL && nova->freq <= atual->freq) {
                anterior = atual;
                atual = atual->prox;
            }

            if (anterior != NULL)
                anterior->prox = nova;

            nova->prox = atual;
        }
    }
}




void removeTabela(Tabela **tab, Registro *reg){
	Tabela *aux=*tab;
	*tab=aux->prox;
	*reg=aux->reg;
	free(aux);
}

void excluirTab(Tabela **tab){
	Tabela *aux;
	while(*tab!=NULL){
		aux=*tab;
		*tab=aux->prox;
		free (aux);
	}
}

void exibirTab(Tabela *t, int ci, int li){

	int i, j, vet[4],aux;
    vet[0] = ci+20;
    for(i=1;i<4;i++)
    	vet[i]=vet[i-1]+20;
    if(t->freq==0)
    	vet[3]=vet[2];

    // Topo da caixa
    gotoxy(ci, li);
    printf("%c", 201); // Canto superior esquerdo

    for (i = ci + 1; i < vet[3]; i++) {
        gotoxy(i, li);
        if (i == vet[0] || i == vet[1] || i == vet[2] || i == vet[3])
            printf("%c", 203); // Divisões de colunas
        else
            printf("%c", 205); // Linha horizontal
    }

    gotoxy(vet[3], li); 
    printf("%c", 187); // Canto superior direito


    i = li+1;
   
    gotoxy(ci, i);
    printf("%c", 186); // Borda esquerda
    gotoxy(vet[0], i);
    printf("%c", 186); // Divisória
    gotoxy(vet[1], i);
    printf("%c", 186);
	gotoxy(vet[2], i);
    printf("%c", 186); // Divisória
    gotoxy(vet[3], i);
    printf("%c", 186); // Borda direita

    aux=strlen("Palavra")/2;
   	gotoxy((ci+vet[0])/2 -aux, i);
    printf("PALAVRA");

    aux=strlen("simb")/2;
    gotoxy((vet[0]+vet[1])/2 -aux, i);
    printf("SIMBOLO");
    
    aux=strlen("Codigo")/2;
    gotoxy((vet[1]+vet[2])/2 - aux, i);
   	printf("CODIGO");
    
    if(vet[2]!=vet[3]){
    	aux=strlen("Frequencia")/2;
		gotoxy((vet[2]+vet[3])/2 -aux, i);
   		printf("FREQUENCIA");
    }
    
   	
   	

    // Linha divisória inferior
    i++;
    gotoxy(ci, i);
    printf("%c", 204); // Divisão esquerda

    for (j = ci + 1; j < vet[3]; j++) {
        gotoxy(j, i);
        if (j == vet[0] || j == vet[1] || j == vet[2] || j == vet[3])
            printf("%c", 206); // Divisões de colunas
        else
            printf("%c", 205); // Linha horizontal
    }

    gotoxy(vet[3], i);
    printf("%c", 185); // Divisão direita
    
    while (t != NULL) {
        i++;
        gotoxy(ci, i);
        printf("%c", 186); // Borda esquerda
        gotoxy(vet[0], i);
        printf("%c", 186); // Divisória
        gotoxy(vet[1], i);
        printf("%c", 186);
		gotoxy(vet[2], i);
        printf("%c", 186); // Divisória
        gotoxy(vet[3], i);
        printf("%c", 186); // Borda direita

		if(t->reg.palavra[0]==' '){
			aux=strlen("'Espaco'")/2;
       		gotoxy((ci+vet[0])/2 -aux, i);
        	printf("'Espaco'");
		}
		else{
			aux=strlen(t->reg.palavra)/2;
       		gotoxy((ci+vet[0])/2 -aux, i);
        	printf("%s", t->reg.palavra);
		}
        

        
        gotoxy((vet[0]+vet[1])/2 -1, i);
        printf("%d", t->reg.simb);
        aux=strlen(t->reg.cod)/2;
		gotoxy((vet[1]+vet[2])/2 -aux, i);
		printf("%s", t->reg.cod);
       	
       	if(vet[2]!=vet[3]){
		    gotoxy((vet[2]+vet[3])/2 - 1, i);
	       	printf("%d", t->freq);	
    	}
        

        // Linha divisória inferior
        i++;
        gotoxy(ci, i);
        printf("%c", 204); // Divisão esquerda

        for (j = ci + 1; j < vet[3]; j++) {
            gotoxy(j, i);
            if (j == vet[0] || j == vet[1] || j == vet[2] || j == vet[3])
                printf("%c", 206); // Divisões de colunas
            else
                printf("%c", 205); // Linha horizontal
        }

        gotoxy(vet[3], i);
        printf("%c", 185); // Divisão direita

        // Próximo elemento da pilha
        t = t->prox; 
    }

    // Base da caixa
    gotoxy(ci, i);
    printf("%c", 200); // Canto inferior esquerdo

    for (j = ci + 1; j < vet[3]; j++) {
        gotoxy(j, i);
        if (j == vet[0] || j == vet[1] || j == vet[2] || j == vet[3])
            printf("%c", 202); // Divisões de colunas
        else
            printf("%c", 205); // Linha horizontal
    }

    gotoxy(vet[3], i);
    printf("%c", 188); // Canto inferior direito
}

void montarBytes(){//mostrar os bytes armazenados
	FILE * ptr = fopen("codigo.dat","rb");
	Byte b;
	fread(&b.cod,sizeof(char),1,ptr);
	while(!feof(ptr)){
		printf("%d",b.bit.b0);
		printf("%d",b.bit.b1);
		printf("%d",b.bit.b2);
		printf("%d",b.bit.b3);
		printf("%d",b.bit.b4);
		printf("%d",b.bit.b5);
		printf("%d",b.bit.b6);
		printf("%d  ",b.bit.b7);
		fread(&b.cod,sizeof(char),1,ptr);
	}
	fclose(ptr);
}









