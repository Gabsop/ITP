#include <stdio.h>
#include <stdlib.h>
#include "TwoGuys.h"


int main(){
	alocar_memoria();
	
	//Variaveis
	char NomeDoArquivo[30]; 		//Variavel que armazena o nome do arquivo escolhido pelo usu�rio
	char Novonome[30];				//Nome que sera dado ao novo arquivo criado apos as mudancas
	Inicial(NomeDoArquivo);			//Funcao que pede para o usuario o nome do arquivo que ele deseja modificar
	FILE *arquivo;					//Arquivo FILE* para apontar para o arquivo original
	FILE *arquivonovo;				//Arquivo FILE* para apontar para o novo arquivo
	
	//Funcoes
	Verificappm(NomeDoArquivo);		//Funcao que verifica o formato da imagem e converte-a para ppm se ela estiver em outro formato
	atributos ATB;					//Struct que possui as variaveis dos atributos como altura e largura da foto por exemplo
	arquivo = AbrirArquivo('l', NomeDoArquivo);	//Funcao que abre o arquivo dado o modo, ex: leitura, gravacao
	ReceberATB(arquivo, &ATB);					//Funcao que armazena os valores no struct
	MTX imagem[ATB.coluna*ATB.linha];			//Vetor de structs que armazenam por sua vez os valores RBG de cada pixel da imagem
	ReceberRGB(arquivo, ATB, imagem); 	        //Funcao que armazena os valores de cada pixel em um struct dividido em R,G, B 
	FecharArquivo(arquivo);						//Funcao que fecha o arquivo
 	NovoNome(Novonome);							//Funcao que da um novo nome ao arquivo criado apos as mudancas
    arquivonovo = AbrirArquivo('g', Novonome);	//Funcao que abre o arquivo dado o modo, ex: leitura, gravacao
	Escolha_Tratamento(imagem, ATB, arquivonovo, NomeDoArquivo); //Funcao que permite ao usuario escolher o tratamento que deseja fazer na imagem efeitos e redmensionamentos
    FecharArquivo(arquivonovo);					 //Funcao que fecha o arquivo
	return 0;
}