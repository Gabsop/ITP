#include "TwoGuys.h"

void Inicial(char *NomeDoArquivo){
	printf("\nBem-vindo(a) a plataforma de tratamento de imagem TwoGuys\n");
	printf("Inicialmente, insira o nome do arquivo que voce deseja modificar\n");
	scanf("%s", NomeDoArquivo);
}
char Verificappm(char *NomeDoArquivo){
	//Variaveis
	int i,j; //Variaveis contadoras
	int png; //Contador do png
	int jpg; // Contador do jpg
	int bmp; // Contador do bmp
	int ppm; // Contador do ppm
	char NomeAntigo[30]; // Nome da foto antes da conversao
	char Comando[100]; // Variavel que armazena os comandos do terminal
	//Variaveis que serao utilizadas para comparar o final do nome da imagem e descobrir seu formato
	char final_png[4] = "png";
	char final_jpg[4] = "jpg";
	char final_bmp[4] = "bmp";
	char final_ppm[4] = "ppm";

	//Funcoes
	strcpy(NomeAntigo, NomeDoArquivo); //Copia o nome do arquivo original e armazena na variavel NomeAntigo
	
	char *p  = strrchr(NomeDoArquivo, '.'); // Verifica o que esta escrito depois do ponto no nome do arquivo
	*p++; // Pula o ponto

	// Compara o que esta escrito depois do ponto no nome da imagem com as variaveis contendo os finais (png, jpg, ppm)
	// Se as strings forem iguais, a funcao retorna zero
	png = strcmp(final_png,p);
	jpg = strcmp(final_jpg,p);
	bmp = strcmp(final_bmp,p);
	ppm = strcmp(final_ppm,p);
	
	// Compara se a funcao retornou zero
	if(png == 0){
		printf("É png\n");
		printf("\nDetectamos que sua imagem está em formato 'png'\n");
		printf("Nosso sistema trabalha com imagens no formato 'ppm'\n");
		printf("Por isso estamos convertendo a imagem para ppm por você!\n");
		printf("Digite o nome da sua nova imagem em 'ppm': ");
		scanf("%s", NomeDoArquivo);
		sprintf(Comando,"convert %s -compress none %s", NomeAntigo, NomeDoArquivo); // Armazena o comando com as variaveis para ser executado no terminal
		system(Comando); // Funcao que executa o comando de conversao no terminal
	}
	if(jpg == 0){
		printf("\nDetectamos que sua imagem está em formato 'jpg'\n");
		printf("Nosso sistema trabalha com imagens no formato 'ppm'\n");
		printf("Por isso estamos convertendo a imagem para ppm por você!\n");
		printf("Digite o nome da sua nova imagem em 'ppm': ");
		scanf("%s", NomeDoArquivo);
		sprintf(Comando,"convert %s -compress none %s", NomeAntigo, NomeDoArquivo); // Armazena o comando com as variaveis para ser executado no terminal
		system(Comando); // Funcao que executa o comando de conversao no terminal
	}
	if(bmp == 0){
		printf("\nDetectamos que sua imagem está em formato 'bmp'\n");
		printf("Nosso sistema trabalha com imagens no formato 'ppm'\n");
		printf("Por isso estamos convertendo a imagem para ppm por você!\n");
		printf("Digite o nome da sua nova imagem em 'ppm': ");
		scanf("%s", NomeDoArquivo);
		sprintf(Comando,"convert %s -compress none %s", NomeAntigo, NomeDoArquivo); // Armazena o comando com as variaveis para ser executado no terminal
		system(Comando); // Funcao que executa o comando de conversao no terminal
	}
}
FILE* AbrirArquivo(char modo, char caminho[30]){
	//Variaveis
	FILE *arquivo;
	
	//Funcoes
	// Abre o arquivo no modo escolhido
	switch(modo){
		case 'g':
			arquivo = fopen(caminho,"wt"); 
			break;
		case 'l':
			arquivo = fopen(caminho, "r");
			break;
		case 'a':
			arquivo = fopen(caminho,"a");
			break;
	}
	//Verifica se o que foi digitado pelo usuario corresponde a um arquivo com o mesmo nome
	if(arquivo == NULL){ // Se nao corresponde, fecha o programa
		printf("Erro ao abrir o arquivo");
		exit(0);
	}
	return arquivo; // Retorna o arquivo aberto
}
void ReceberATB(FILE *arquivo, atributos *ATB){
	// Variaveis
	char hash[50]; // Armazena o comentario
	char sla[100];
	int aux;
	fgets(ATB->code, 3, arquivo);
	fscanf(arquivo, "%s", hash);
	if(hash[0] == '#'){
		fgets(sla, 100, arquivo);
		fscanf(arquivo, "%d", &ATB->coluna);
	} else {
		aux = atoi(hash);
		ATB->coluna = aux;
	}
	
	fscanf(arquivo, "%d", &ATB->linha);
	fscanf(arquivo, "%d", &ATB->max);
}
void ReceberRGB(FILE *arquivo, atributos ATB, MTX *imagem){
	//Variaveis
	int i;
	//Funcoes
	for(i = 0; i<ATB.coluna*ATB.linha; i++){ // For que percorre todos os pixeis da imagem
		// Le e armazena cada cor de cada pixel no struct
		fscanf(arquivo,"%d", &imagem[i].R);
		fscanf(arquivo,"%d", &imagem[i].G);
		fscanf(arquivo,"%d", &imagem[i].B);
	}
}
void NovoNome(char Novonome[30]){
	printf("\nDigite o novo nome do arquivo: ");
    scanf("%s", Novonome);
}
void Escolha_Tratamento(MTX *imagem, atributos ATB, FILE *arquivonovo, char *NomeDoArquivo){
	// Variaveis
	int Escolha, i, media;
	char efeito;
	system("clear");
	// Funcoes
	printf("Nossa plataforma possui diversas formas de tratamento de imagem\n");
	printf("Escolha a que voce desejar digitando o número da opção.\n1)Alterar os atributos da imagem\n2)Adicionar um efeito a imagem\n");
	scanf("%d", &Escolha);
	system("clear");
	switch(Escolha){
		case REDM:
			printf("O que você deseja fazer? Digite a letra correspondente ao que voce deseja\nA)Ampliar\nB)Reduzir\nC)Rotacionar\n");
			scanf("%s", &efeito);
			if(efeito == 'A'){
				Ampliar(arquivonovo, ATB, imagem);
			}else if(efeito == 'B'){
				Reduzir(arquivonovo, ATB, imagem);
			}else if(efeito == 'C'){
				Girar(arquivonovo, ATB, imagem);
			}else{
				printf("Opcao Invalida\n");
				Escolha_Tratamento(imagem, ATB, arquivonovo, NomeDoArquivo);
			}
			break;
		case EFECT:
			printf("O que você deseja fazer? Digite a letra correspondente ao que voce deseja\nA)Escala de cinza\nB)Nitidez\nC)Desfocar\nD)Deteccao de bordas\n ------ EXTRAS ------\nE)Negativo\nF)ChromaKey\nG)Hue\nH)Brilho(Exposição)\nJ)Gauss\nK)Saturacao\nL)Espelho\nM)Destacar Relevo\nN)Detectar Objeto\n");
			scanf("%s", &efeito);
			if(efeito == 'A'){
				i=0;
				Deixar_cinza(imagem, ATB.coluna*ATB.linha, arquivonovo, i, media);
				Finalizar_FOTO(arquivonovo, ATB, imagem);
			}else if(efeito == 'B'){
				Nitidez(imagem, ATB);
				Finalizar_FOTO(arquivonovo, ATB, imagem);
			}else if(efeito == 'C'){
				Desfocar(imagem, ATB);
				Finalizar_FOTO(arquivonovo, ATB, imagem);
			}else if(efeito == 'D'){
				 DetectarBordas(imagem, ATB);
				 Finalizar_FOTO(arquivonovo, ATB, imagem);
			}else if(efeito == 'E'){
				Negativo(imagem, ATB, arquivonovo);
			}else if(efeito == 'F'){
				ChromaKey(ATB, imagem, arquivonovo);		
			}else if(efeito == 'G'){
				HUE(imagem, ATB);	
				Finalizar_FOTO(arquivonovo, ATB, imagem);
			}else if(efeito == 'H'){
				 Brilho(imagem, ATB);
				 Finalizar_FOTO(arquivonovo, ATB, imagem);
			}else if(efeito == 'J'){
				Gauss(imagem, ATB);
				Finalizar_FOTO(arquivonovo, ATB, imagem);
			}else if(efeito == 'K'){
				Saturacao(imagem, ATB);
				Finalizar_FOTO(arquivonovo, ATB, imagem);
			} else if(efeito == 'L'){
				Espelho(imagem, ATB, arquivonovo);
			} else if(efeito == 'M'){
				Destacar_Relevo(imagem, ATB);
				Finalizar_FOTO(arquivonovo, ATB, imagem);
			} else if(efeito == 'N'){
				Detectar_Objeto(imagem, ATB);
				Finalizar_FOTO(arquivonovo, ATB, imagem);
			}else{
				printf("opcao invalida\n");
				Escolha_Tratamento(imagem, ATB, arquivonovo, NomeDoArquivo);
				break;
			}
	}
}
void Pixelizar(MTX *imagem, atributos ATB){
	int linha,coluna;
	linha = ATB.linha;
	coluna = ATB.coluna;
	int i,j,aux;
	MTX matriz[linha][coluna];
	int mascaraR;
	int mascaraG;
	int mascaraB;
	MTX media;

	for(i=0;i<ATB.linha;i++){
		aux++;
		for(j=0;j<ATB.coluna;j++){
			if(aux = j){
				matriz[i][j] = imagem[i+aux];
			}
			matriz[i][j] = imagem[i+j];
		}
	}

	for(i = 1; i < ATB.linha; i += 2){
		for(j = 1; j < ATB.coluna; j += 2){
			media.R = (matriz[i - 1][j - 1].R + matriz[i - 1][j].R + matriz[i][j - 1].R + matriz[i][j].R) / 4;
			media.G = (matriz[i - 1][j - 1].G + matriz[i - 1][j].G + matriz[i][j - 1].G + matriz[i][j].G) / 4;
			media.B = (matriz[i - 1][j - 1].B + matriz[i - 1][j].B + matriz[i][j - 1].B + matriz[i][j].B) / 4;
			
			matriz[i - 1][j - 1] = media;
			matriz[i - 1][j] = media;
			matriz[i][j - 1] = media;
			matriz[i][j] = media;
		}
}

	for(i=0;i<ATB.linha;i++){
		for(j=0;j<ATB.coluna;j++){
			imagem[i] = matriz[i][j];
		}
	}
}
void Gauss(MTX *imagem, atributos ATB){
	int i;
	int mascaraR, mascaraB, mascaraG;
	for(i=0;i<(ATB.linha * ATB.coluna)-9;i++){
		mascaraR = ((1*imagem[i].R + 2*imagem[i+1].R + 1*imagem[i+2].R + 2*imagem[i+3].R + 4*imagem[i+4].R + 2*imagem[i+5].R + 1*imagem[i+6].R + 2*imagem[i+7].R + 1*imagem[i+8].R)/16);
		mascaraG = ((1*imagem[i].G + 2*imagem[i+1].G + 1*imagem[i+2].G + 2*imagem[i+3].G + 4*imagem[i+4].G + 2*imagem[i+5].G + 1*imagem[i+6].G + 2*imagem[i+7].G + 1*imagem[i+8].G)/16);
		mascaraB = ((1*imagem[i].B + 2*imagem[i+1].B + 1*imagem[i+2].B + 2*imagem[i+3].B + 4*imagem[i+4].B + 2*imagem[i+5].B + 1*imagem[i+6].B + 2*imagem[i+7].B + 1*imagem[i+8].B)/16);	
		imagem[i].R = mascaraR;
	    imagem[i].G = mascaraG; 	
		imagem[i].B = mascaraB; 

	}
}
void Deixar_cinza(MTX *imagem, int tamanho, FILE* arquivo, int i, int media){
	media = (imagem[i].R + imagem[i].G + imagem[i].B)/3; // Faz a media entre as tres cores (Vermelho, verde e azul)
	// Substitui os valores de cada cor de cada pixel pela media
	imagem[i].R = media;
	imagem[i].G = media;
	imagem[i].B = media;
	
	if(i < tamanho){ // Enquanto o i nao chegar no fim da imagem a funcao e chamada novamente
		Deixar_cinza(imagem, tamanho, arquivo, i += 1, media);
	}
}
void Ampliar(FILE *arquivonovo, atributos ATB, MTX *imagem){
	int contador=0, j, i, duplicont;
	fprintf(arquivonovo, "%s\n", ATB.code);
	fprintf(arquivonovo, "%d ", 2*ATB.coluna);
	fprintf(arquivonovo, "%d\n", 2*ATB.linha);
	fprintf(arquivonovo, "%d\n", ATB.max);
	for(i = 0; i<ATB.linha*ATB.coluna; i++){
		contador++;
		if(contador == ATB.coluna){
			fprintf(arquivonovo, "\n");
			contador = 0;
			duplicont=0;
			for(j = i-ATB.coluna; duplicont<ATB.coluna; j++){
				fprintf(arquivonovo,"%d ", imagem[j].R);
				fprintf(arquivonovo,"%d ", imagem[j].G);
				fprintf(arquivonovo,"%d ", imagem[j].B);
				fprintf(arquivonovo,"%d ", imagem[j].R);
				fprintf(arquivonovo,"%d ", imagem[j].G);
				fprintf(arquivonovo,"%d ", imagem[j].B);

				duplicont++;
			}
				fprintf(arquivonovo, "\n");
		}
		fprintf(arquivonovo,"%d ", imagem[i].R);
		fprintf(arquivonovo,"%d ", imagem[i].G);
		fprintf(arquivonovo,"%d ", imagem[i].B);
		fprintf(arquivonovo,"%d ", imagem[i].R);
		fprintf(arquivonovo,"%d ", imagem[i].G);
		fprintf(arquivonovo,"%d ", imagem[i].B);

	}
}
void Nitidez(MTX *imagem, atributos ATB){
	int i;
	int mascaraR, mascaraB, mascaraG;
	for(i=0;i<(ATB.linha * ATB.coluna)-9;i++){
		mascaraR = (0*imagem[i].R + -1*imagem[i+1].R + 0*imagem[i+2].R + -1*imagem[i+3].R + 5*imagem[i+4].R + -1*imagem[i+5].R + 0*imagem[i+6].R + -1*imagem[i+7].R + 0*imagem[i+8].R);
		mascaraG = (0*imagem[i].G + -1*imagem[i+1].G + 0*imagem[i+2].G + -1*imagem[i+3].G + 5*imagem[i+4].G + -1*imagem[i+5].G + 0*imagem[i+6].G + -1*imagem[i+7].G + 0*imagem[i+8].G);
		mascaraB = (0*imagem[i].B + -1*imagem[i+1].B + 0*imagem[i+2].B + -1*imagem[i+3].B + 5*imagem[i+4].B + -1*imagem[i+5].B + 0*imagem[i+6].B + -1*imagem[i+7].B + 0*imagem[i+8].B);	
		imagem[i].R = mascaraR;
	    imagem[i].G = mascaraG; 	
		imagem[i].B = mascaraB; 

	}
}
void DetectarBordas(MTX *imagem, atributos ATB){
	int i;
	int mascaraR, mascaraB, mascaraG;
	int intensidade;
	int volta = 1;
	
	while(volta !=0){
	printf("Digite a intensidade da Detecção(1, 2 ou 3):  ");
	scanf("%d", &intensidade);
		switch(intensidade){
			case 1:
			for(i=9;i<(ATB.linha * ATB.coluna);i++){
				mascaraR = (1*imagem[i].R + 0*imagem[i-1].R + -1*imagem[i-2].R + 0*imagem[i-3].R + 0*imagem[i-4].R + 0*imagem[i-5].R + -1*imagem[i-6].R + 0*imagem[i-7].R + 1*imagem[i-8].R);
				mascaraG = (1*imagem[i].G + 0*imagem[i-1].G + -1*imagem[i-2].G + 0*imagem[i-3].G + 0*imagem[i-4].G + 0*imagem[i-5].G + -1*imagem[i-6].G + 0*imagem[i-7].G + 1*imagem[i-8].G);
				mascaraB = (1*imagem[i].B + 0*imagem[i-1].B + -1*imagem[i-2].B + 0*imagem[i-3].B + 0*imagem[i-4].B + 0*imagem[i-5].B + -1*imagem[i-6].B + 0*imagem[i-7].B + 1*imagem[i-8].B);	
				imagem[i-8].R = mascaraR;
			    imagem[i-8].G = mascaraG; 	
				imagem[i-8].B = mascaraB;
			}
			volta = 0;
			break;
			
			case 2:
			for(i=9;i<(ATB.linha * ATB.coluna);i++){
				mascaraR = (0*imagem[i].R + 1*imagem[i-1].R + 0*imagem[i-2].R + 1*imagem[i-3].R + -4*imagem[i-4].R + 1*imagem[i-5].R + 0*imagem[i-6].R + 1*imagem[i-7].R + 0*imagem[i-8].R);
				mascaraG = (0*imagem[i].G + 1*imagem[i-1].G + 0*imagem[i-2].G + 1*imagem[i-3].G + -4*imagem[i-4].G + 1*imagem[i-5].G + 0*imagem[i-6].G + 1*imagem[i-7].G + 0*imagem[i-8].G);
				mascaraB = (0*imagem[i].B + 1*imagem[i-1].B + 0*imagem[i-2].B + 1*imagem[i-3].B + -4*imagem[i-4].B + 1*imagem[i-5].B + 0*imagem[i-6].B + 1*imagem[i-7].B + 0*imagem[i-8].B);	
				imagem[i-8].R = mascaraR;
			    imagem[i-8].G = mascaraG; 	
				imagem[i-8].B = mascaraB;
			}
			volta = 0;
			break;

			case 3:		
			for(i=9;i<(ATB.linha * ATB.coluna);i++){
				mascaraR = (-1*imagem[i].R + -1*imagem[i-1].R + -1*imagem[i-2].R + -1*imagem[i-3].R + 8*imagem[i-4].R + -1*imagem[i-5].R + -1*imagem[i-6].R + -1*imagem[i-7].R + -1*imagem[i-8].R);
				mascaraG = (-1*imagem[i].G + -1*imagem[i-1].G + -1*imagem[i-2].G + -1*imagem[i-3].G + 8*imagem[i-4].G + -1*imagem[i-5].G + -1*imagem[i-6].G + -1*imagem[i-7].G + -1*imagem[i-8].G);
				mascaraB = (-1*imagem[i].B + -1*imagem[i-1].B + -1*imagem[i-2].B + -1*imagem[i-3].B + 8*imagem[i-4].B + -1*imagem[i-5].B + -1*imagem[i-6].B + -1*imagem[i-7].B + -1*imagem[i-8].B);	
				imagem[i-8].R = mascaraR;
			    imagem[i-8].G = mascaraG; 	
				imagem[i-8].B = mascaraB;
			}
			volta = 0;
			break;

			default:
			printf("Opção Inválida!\n");
			volta = 1;
			break;
		}
	}
}
void Desfocar(MTX *imagem, atributos ATB){
	int i;
	int mascaraR, mascaraB, mascaraG;
	for(i=0;i<(ATB.linha * ATB.coluna)-9;i++){
		mascaraR = (imagem[i].R + imagem[i+1].R + imagem[i+2].R + imagem[i+3].R + imagem[i+4].R + imagem[i+5].R + imagem[i+6].R + imagem[i+7].R + imagem[i+8].R)/9;
		mascaraG = (imagem[i].G + imagem[i+1].G + imagem[i+2].G + imagem[i+3].G + imagem[i+4].G + imagem[i+5].G + imagem[i+6].G + imagem[i+7].G + imagem[i+8].G)/9;
		mascaraB = (imagem[i].B + imagem[i+1].B + imagem[i+2].B + imagem[i+3].B + imagem[i+4].B + imagem[i+5].B + imagem[i+6].B + imagem[i+7].B + imagem[i+8].B)/9;	
		imagem[i].R = mascaraR;
	    imagem[i].G = mascaraG; 	
		imagem[i].B = mascaraB; 

	}
}
void Reduzir(FILE *arquivonovo, atributos ATB, MTX *imagem){
	int i;
	fprintf(arquivonovo, "%s\n", ATB.code);
	fprintf(arquivonovo, "%d ", (ATB.coluna/2));
	fprintf(arquivonovo, "%d\n", (ATB.linha/2));
	fprintf(arquivonovo, "%d\n", ATB.max);
	for(i=0;i<ATB.linha*ATB.coluna; i++, i++){
		fprintf(arquivonovo,"%d ", imagem[i].R);
		fprintf(arquivonovo,"%d ", imagem[i].G);
		fprintf(arquivonovo,"%d ", imagem[i].B);
		
		if(i%(ATB.coluna) == 0 && i != 0){
			i+=ATB.coluna;
		}
	}
}
void Girar(FILE *arquivonovo, atributos ATB, MTX *imagem){
	MTX *vetor;
	vetor = malloc((3*(ATB.coluna*ATB.linha))*sizeof(int));
	int i, j;
	int qtd;
	unsigned long int k;
	printf("Selecione a quantidadae de rotação(90, 180 ou 270 graus): ");
	scanf("%d", &qtd);
	if(qtd == 90){
		for(k=0;k<ATB.coluna*ATB.linha;k++){ 
				vetor[k].R = imagem[k].R;
				vetor[k].G = imagem[k].G;
				vetor[k].B = imagem[k].B;
			
		}
		k=0;
		for(i=0;i<ATB.linha;i++){
			for(j=0;j<ATB.coluna;j++){  
			imagem[(j*ATB.linha)+(ATB.linha - i - 1)].R = vetor[(ATB.coluna*i)+j].R;
			imagem[(j*ATB.linha)+(ATB.linha - i - 1)].G= vetor[(ATB.coluna*i)+j].G;	
			imagem[(j*ATB.linha)+(ATB.linha - i - 1)].B = vetor[(ATB.coluna*i)+j].B;
			}
		}
		fprintf(arquivonovo, "%s\n", ATB.code);
		fprintf(arquivonovo, "%d ", ATB.linha);
		fprintf(arquivonovo, "%d\n", ATB.coluna);
		fprintf(arquivonovo, "%d\n", ATB.max);
		for(i=0;i<ATB.coluna*ATB.linha;i++){
			if (imagem[i].R<0){
				imagem[i].R =0; 
			}

			if(imagem[i].G<0){
				imagem[i].G= 0;
			}

			if(imagem[i].B<0){
				imagem[i].B = 0;
			}		

			fprintf(arquivonovo, "%d\n", imagem[i].R);
			fprintf(arquivonovo, "%d\n", imagem[i].G);
			fprintf(arquivonovo, "%d\n", imagem[i].B);
		}
	}

	if(qtd == 180){
		for(k=0;k<ATB.coluna*ATB.linha;k++){ 
				vetor[k].R = imagem[k].R;
				vetor[k].G = imagem[k].G;
				vetor[k].B = imagem[k].B;
			
		}
		k=0;
		for(i=ATB.coluna*ATB.linha-1;i>=0;i--){ 
				imagem[k].R = vetor[i].R;
				imagem[k].G = vetor[i].G;
				imagem[k].B = vetor[i].B;
			k++;
		}
		fprintf(arquivonovo, "%s\n", ATB.code);
		fprintf(arquivonovo, "%d ", ATB.coluna);
		fprintf(arquivonovo, "%d\n", ATB.linha);
		fprintf(arquivonovo, "%d\n", ATB.max);
		for(i=0;i<ATB.coluna*ATB.linha;i++){
			if (imagem[i].R<0){
				imagem[i].R =0; 
			}

			if(imagem[i].G<0){
				imagem[i].G= 0;
			}

			if(imagem[i].B<0){
				imagem[i].B = 0;
			}		

			fprintf(arquivonovo, "%d\n", imagem[i].R);
			fprintf(arquivonovo, "%d\n", imagem[i].G);
			fprintf(arquivonovo, "%d\n", imagem[i].B);
		}
	}
	if(qtd == 270){
		for(k=0;k<ATB.coluna*ATB.linha;k++){ 
				vetor[k].R = imagem[k].R;
				vetor[k].G = imagem[k].G;
				vetor[k].B = imagem[k].B;
		}
		for(i=ATB.linha-1;i>=0;i--){
			for(j=ATB.coluna-1;j>=0;j--){  
			imagem[(j*ATB.linha)+(ATB.linha - i - 1)].R = vetor[(ATB.coluna*i)+j].R;
			imagem[(j*ATB.linha)+(ATB.linha - i - 1)].G= vetor[(ATB.coluna*i)+j].G;	
			imagem[(j*ATB.linha)+(ATB.linha - i - 1)].B = vetor[(ATB.coluna*i)+j].B;
			}
		}
		fprintf(arquivonovo, "%s\n", ATB.code);
		fprintf(arquivonovo, "%d ", ATB.linha);
		fprintf(arquivonovo, "%d\n", ATB.coluna);
		fprintf(arquivonovo, "%d\n", ATB.max);
		for(i=ATB.coluna*ATB.linha;i>=0;i--){
			if (imagem[i].R<0){
				imagem[i].R =0; 
			}

			if(imagem[i].G<0){
				imagem[i].G= 0;
			}

			if(imagem[i].B<0){
				imagem[i].B = 0;
			}		

			fprintf(arquivonovo, "%d\n", imagem[i].R);
			fprintf(arquivonovo, "%d\n", imagem[i].G);
			fprintf(arquivonovo, "%d\n", imagem[i].B);
		}
	}
	free(vetor);
}
void Finalizar_FOTO(FILE *arquivonovo, atributos ATB, MTX *imagem){
	// Variaveis
	int i;
	
	// Funcoes
	fprintf(arquivonovo, "%s\n", ATB.code);
	fprintf(arquivonovo, "%d ", ATB.coluna);
	fprintf(arquivonovo, "%d\n", ATB.linha);
	fprintf(arquivonovo, "%d\n", ATB.max);
	for(i=0;i<ATB.coluna*ATB.linha;i++){ // For que percorre todos o pixels da imagem
		// Se o valor da cor for menor que zero substitui o valor por zero
		if (imagem[i].R<0){
			imagem[i].R =0; 
		}

		if(imagem[i].G<0){
			imagem[i].G= 0;
		}

		if(imagem[i].B<0){
			imagem[i].B = 0;
		}

		// Armazena os valores RGB na nova imagem
		fprintf(arquivonovo, "%d\n", imagem[i].R);
		fprintf(arquivonovo, "%d\n", imagem[i].G);
		fprintf(arquivonovo, "%d\n", imagem[i].B);
	}	


}
void FecharArquivo(FILE *arquivo){
	fclose(arquivo); // Fecha o arquivo selecionado
}

void alocar_memoria(){	
	const rlim_t kStackSize = 128L * 1024L * 1024L;
	struct rlimit rl;
	int resultado;

  resultado = getrlimit(RLIMIT_STACK, &rl);
  if (resultado == 0)
  {
      if (rl.rlim_cur < kStackSize){
          rl.rlim_cur = kStackSize;
          resultado = setrlimit(RLIMIT_STACK, &rl);  
     }
 }
}

//EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS EXTRAS



void Negativo(MTX *imagem,atributos ATB, FILE *arquivonovo){
	int i;
	fprintf(arquivonovo, "%s\n", ATB.code);
	fprintf(arquivonovo, "%d ", ATB.coluna);
	fprintf(arquivonovo, "%d\n", ATB.linha);
	fprintf(arquivonovo, "%d\n", ATB.max);
	for(i=0;i<ATB.coluna*ATB.linha;i++){
		if (imagem[i].R<0){
			imagem[i].R =0; 
		}

		if(imagem[i].G<0){
			imagem[i].G= 0;
		}

		if(imagem[i].B<0){
			imagem[i].B = 0;
		}

		fprintf(arquivonovo, "%d\n", imagem[i].R^255);
		fprintf(arquivonovo, "%d\n", imagem[i].G^255);
		fprintf(arquivonovo, "%d\n", imagem[i].B^255);
	}
}


void ChromaKey(atributos ATB, MTX *imagem, FILE *arquivonovo){
	int i, j, k, linha, coluna, lix, cont;
	char lixo[4];
	char background[30]; 		//Variavel que armazena o nome do arquivo
	char combinacao[30];	
	printf("digite o nome do arquivo de fundo: ");
	scanf("%s", background); //Nome que sera dado ao novo arquivo criado apos as mudancas
	FILE *arquivo2;					//Arquivo FILE* para apontar para o arquivo original
	Verificappm(background);		//Funcao que verifica o formato da imagem e converte-a para ppm se ela estiver em outro formato
	arquivo2 = AbrirArquivo('l', background);	//Funcao que abre o arquivo dado o modo, ex: leitura, gravacao				//Funcao que armazena os valores no struct
	fscanf(arquivo2, "%s\n", lixo);
	fscanf(arquivo2, "%d ", &coluna);
	fscanf(arquivo2, "%d\n", &linha);
	fscanf(arquivo2, "%d\n", &lix);
	MTX back[linha*coluna];
	int lixocolunaR, lixocolunaB, lixocolunaG;
	for(i = 0; i<=ATB.linha; i++){
		for(j=0;j<=coluna;j++){
			if(j>ATB.coluna){
				fscanf(arquivo2,"%d", &lixocolunaR);
				fscanf(arquivo2,"%d", &lixocolunaG);
				fscanf(arquivo2,"%d", &lixocolunaB);
			}else{	
				fscanf(arquivo2,"%d", &back[k].R);
				fscanf(arquivo2,"%d", &back[k].G);
				fscanf(arquivo2,"%d", &back[k].B);	
				k++;
			}
		}
	}
    FecharArquivo(arquivo2);				
		//VERIFICAR BACKGROUND
 	fprintf(arquivonovo, "%s\n", ATB.code);
	fprintf(arquivonovo, "%d ", ATB.coluna);
	fprintf(arquivonovo, "%d\n", ATB.linha);
	fprintf(arquivonovo, "%d\n", ATB.max);
	k=0;
	for(i=0;i<ATB.coluna*ATB.linha;i++){
		if((imagem[i].R <= 60)&& (imagem[i].G >= 200) && (imagem[i].B <= 200)){
			fprintf(arquivonovo, "%d\n", back[i].R);
			fprintf(arquivonovo, "%d\n", back[i].G);
			fprintf(arquivonovo, "%d\n", back[i].B);
		}else{
			fprintf(arquivonovo, "%d\n", imagem[i].R);
			fprintf(arquivonovo, "%d\n", imagem[i].G);
			fprintf(arquivonovo, "%d\n", imagem[i].B);
		}
	}
		
}
void HUE(MTX *imagem,atributos ATB){
	int i, R, G, B;
	printf("Qual a cor do HUE desejado? Insira o valor em RGB: ");
	scanf("%d %d %d", &R, &G, &B);
	for(i=0;i<ATB.linha*ATB.coluna; i++){
		imagem[i].R = (imagem[i].R + R)/2;
		imagem[i].G = (imagem[i].G + G)/2;
		imagem[i].B = (imagem[i].B + B)/2;
		
	}
}
void Espelho(MTX *imagem,atributos ATB, FILE *arquivonovo){
	int k=0, i , j, g;
	fprintf(arquivonovo, "%s\n", ATB.code);
	fprintf(arquivonovo, "%d ", ATB.coluna);
	fprintf(arquivonovo, "%d\n", ATB.linha);
	fprintf(arquivonovo, "%d\n", ATB.max);



	for(i = 0, k = 0; i < ATB.coluna*ATB.linha; i++, k++){
		fprintf(arquivonovo, "%d\n", imagem[i].R);
		fprintf(arquivonovo, "%d\n", imagem[i].G);
		fprintf(arquivonovo, "%d\n", imagem[i].B);
		if(k == (ATB.coluna/2) && k != 0){
			for(j = i; j > i - (ATB.coluna/2); j--, k--){
				fprintf(arquivonovo, "%d\n", imagem[j].R);
				fprintf(arquivonovo, "%d\n", imagem[j].G);
				fprintf(arquivonovo, "%d\n", imagem[j].B);
			}
			i += ATB.coluna/2;		
		}
	}
	
}

void Brilho(MTX *imagem,atributos ATB){
	int i, R, G, B;
	
	for(i=0;i<ATB.linha*ATB.coluna; i++){
			imagem[i].R += imagem[i].R/2;
			imagem[i].G += imagem[i].G/2;
			imagem[i].B += imagem[i].B/2;
		
		if(imagem[i].R>ATB.max){
			imagem[i].R = ATB.max;
		}
		if(imagem[i].G>ATB.max){
			imagem[i].G = ATB.max;
		}
		if(imagem[i].B>ATB.max){
			imagem[i].B = ATB.max;
		}

	}
}
void Saturacao(MTX *imagem,atributos ATB){
	int i, R, G, B;
	
	for(i=0;i<ATB.linha*ATB.coluna; i++){
		if(imagem[i].R>= ATB.max/2){
			imagem[i].R = (imagem[i].R + ATB.max)/2;
		}
		if(imagem[i].G>= ATB.max/2){
			imagem[i].G = (imagem[i].G + ATB.max)/2;
		}
		if(imagem[i].B>= ATB.max/2){
			imagem[i].B = (imagem[i].B + ATB.max)/2;
		}
		
		if(imagem[i].R>ATB.max){
			imagem[i].R = ATB.max;
		}
		if(imagem[i].G>ATB.max){
			imagem[i].G = ATB.max;
		}
		if(imagem[i].B>ATB.max){
			imagem[i].B = ATB.max;
		}

	}
}

void Destacar_Relevo(MTX *imagem,atributos ATB){
	int mascaraR, mascaraB, mascaraG, i;
	for(i=0;i<(ATB.linha * ATB.coluna)-9;i++){
		mascaraR = (-2*imagem[i].R + -1*imagem[i+1].R + 0*imagem[i+2].R + -1*imagem[i+3].R + 1*imagem[i+4].R + 1*imagem[i+5].R + 0*imagem[i+6].R + 1*imagem[i+7].R + 2*imagem[i+8].R);
		mascaraG = (-2*imagem[i].G + -1*imagem[i+1].G + 0*imagem[i+2].G + -1*imagem[i+3].G + 1*imagem[i+4].G + 1*imagem[i+5].G + 0*imagem[i+6].G + 1*imagem[i+7].G + 2*imagem[i+8].G);
		mascaraB = (-2*imagem[i].B + -1*imagem[i+1].B + 0*imagem[i+2].B + -1*imagem[i+3].B + 1*imagem[i+4].B + 1*imagem[i+5].B + 0*imagem[i+6].B + 1*imagem[i+7].B + 2*imagem[i+8].B);
		imagem[i].R = mascaraR;
	    imagem[i].G = mascaraG; 	
		imagem[i].B = mascaraB; 
	}
}
void Detectar_Objeto(MTX *imagem,atributos ATB){
	int mascaraR, mascaraB, mascaraG, i;
	for(i=0;i<(ATB.linha * ATB.coluna)-9;i++){
		mascaraR = (-1*imagem[i].R + 0*imagem[i+1].R + 0*imagem[i+2].R + 0*imagem[i+3].R + 1*imagem[i+4].R + 0*imagem[i+5].R + 0*imagem[i+6].R + 0*imagem[i+7].R + 0*imagem[i+8].R);
		mascaraG = (-1*imagem[i].G + 0*imagem[i+1].G + 0*imagem[i+2].G + 0*imagem[i+3].G + 1*imagem[i+4].G + 0*imagem[i+5].G + 0*imagem[i+6].G + 0*imagem[i+7].G + 0*imagem[i+8].G);
		mascaraB = (-1*imagem[i].B + 0*imagem[i+1].B + 0*imagem[i+2].B + 0*imagem[i+3].B + 1*imagem[i+4].B + 0*imagem[i+5].B + 0*imagem[i+6].B + 0*imagem[i+7].B + 0*imagem[i+8].B);
		imagem[i].R = mascaraR;
	    imagem[i].G = mascaraG; 	
		imagem[i].B = mascaraB; 
	}
}