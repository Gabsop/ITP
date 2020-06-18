//Bibliotecas utilizadas
#include <stdio.h> 
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>

typedef struct imagem_em_vetor{ //struct que contém os valores RGB de cada pixel da imagem
	int R;
	int G;
	int B;
}MTX;
typedef struct atributos_image{//struct que contém os atributos da imagem tais como altura, largura, etc...
	char code[3];
	char hash[2];
	int coluna;
	int linha;
	int max;
}atributos;
enum Tipo_de_Tratamento {REDM = 1, EFECT};  //Enum para classificar o tipo de tratamento se será de redimensionamento ou adição de algum efeito

void alocar_memoria();	//função que alocará memoria máxima do programa maior que a default
void Inicial(char *NomeDoArquivo); //Funcao que pede para o usuario o nome do arquivo que ele deseja modificar
char Verificappm(char *NomeDoArquivo); //Funcao que verifica o formato da imagem e converte-a para ppm se ela estiver em outro formato
FILE* AbrirArquivo(char modo, char caminho[30]); //Funcao que abre o arquivo dado o modo, ex: leitura, gravacao
void ReceberATB(FILE *arquivo, atributos *ATB); //Funcao que armazena os valores no struct
void ReceberRGB(FILE *arquivo, atributos ATB, MTX *imagem);//Funcao que armazena os valores de cada pixel em um struct dividido em R,G, B 
void NovoNome(char Novonome[30]); //Funcao que da um novo nome ao arquivo criado apos as mudancas
void FecharArquivo(FILE *arquivo); //função que fecha o arquivo
void Finalizar_FOTO(FILE *arquivonovo, atributos ATB, MTX *imagem); //Imprime os atributos e os pixeis em RGB no arquivo novo

void Escolha_Tratamento(MTX *imagem, atributos ATB, FILE *arquivonovo, char *NomeDoArquivo); //Funcao que permite ao usuario escolher o tratamento que deseja fazer na imagem efeitos e redmensionamentos

void Deixar_cinza(MTX *imagem, int tamanho, FILE* arquivo, int i, int media);  //Função que adiciona o efeito escala de cinza na imagem
void Nitidez(MTX *imagem, atributos ATB); //Função que adiciona o efeito sharpening(nitidez) na imagem
void Desfocar(MTX *imagem, atributos ATB);//Função que adiciona o efeito blurring(desfoque) na imagem
void DetectarBordas(MTX *imagem, atributos ATB); ////Função que enfatiza as bordas em relação do resto da imagem

void Girar(FILE *arquivonovo, atributos ATB, MTX *imagem); //Função que rotaciona a imagem
void Reduzir(FILE *arquivonovo, atributos ATB, MTX *imagem); //Função que reduz o tamanho da imagem
void Ampliar(FILE *arquivonovo, atributos ATB, MTX *imagem); //funçao que amplia a imagem

// EXTRAS  EXTRAS  EXTRAS  EXTRAS  EXTRAS  EXTRAS  EXTRAS  EXTRAS  EXTRAS  EXTRAS  EXTRAS 

void ChromaKey(atributos ATB, MTX *imagem, FILE *arquivonovo); //Aplica o efeito chroma KEy

void Negativo(MTX *imagem, atributos ATB, FILE *arquivonovo); //Aplica o efeito NEGATIVO

void HUE(MTX *imagem,atributos ATB);

void Espelho(MTX *imagem,atributos ATB, FILE *arquivonovo);

void Brilho(MTX *imagem,atributos ATB);

void Saturacao(MTX *imagem,atributos ATB);

void Gauss(MTX *imagem, atributos ATB);

void Destacar_Relevo(MTX *imagem,atributos ATB);

void Detectar_Objeto(MTX *imagem,atributos ATB);