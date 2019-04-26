/* * * * * * * * * * * * * * * * * * *
	Aluno: Mateus Morishigue Borges
	NUSP: 9850328
* * * * * * * * * * * * * * * * * * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

//funcao q verifica se uma string contem apenas digitos
int ehNumero(char* string){
	if(string[0] == '\0'){
		return 0;
	}
	int i = 0;
	while(string[i] != '\0'){
		if(isdigit(string[i]) || string[i] == '.'){
			i++;
		}
		else{
			return 0;
		}
	}
	return 1;
}

int main(){
	
	//para printar os acentos certos
	setlocale(LC_ALL,"Portuguese");

	//definicao do registro de cabeçalho
	struct regCab{
			char status;
			int topoPilha;
			char tagCampo1;
			char desCampo1[55];
			char tagCampo2;
			char desCampo2[55];
			char tagCampo3;
			char desCampo3[55];
			char tagCampo4;
			char desCampo4[55];
			char tagCampo5;
			char desCampo5[55];
		};
	
	//pega a entrada
	char entrada[100];

	fgets(entrada,100,stdin);

	//decodificação da entrada
	char func = entrada[0];
	
	char outFile[50] = "arquivoTrab1si.bin", readFile[50], removidoChar, NomeDoCampo[30], valor[30], data[11], tag4, campoVar[30], campoVar2[30], tag5, arroba;
	int i, k, encadeamento, nroInscricao, indVar, indVar2, acessos = 0, numReg = 0, acum = 0, certos = 0, rrn;

	double nota = -1.0;

	for(i = 0; i < 30; i++){
		if(i < 11){
			data[i] = '\0';
		}
		campoVar[i] = '\0';
		campoVar2[i] = '\0';
		readFile[i] = '\0';
		NomeDoCampo[i] = '\0';
		valor[i] = '\0';
	}

	//Funcionalidade 1
	if(func == '1'){
		
		//funcao para gerar uma string readFile
		char *token = strtok(entrada, " ");
		for(i = 0; i < 3; i++){
			if(i == 1 && token){
				strcpy(readFile,token);
			}
			
			token = strtok(NULL," ");
		}

		//loop para tirar o \n da string readFile
		for(i = 0; i < 50; i++){
			if(readFile[i] == '\n'){
				readFile[i] = '\0';
			}
		}

		//verifica se o arquivo readFile existe
		FILE *arqcsv = fopen(readFile,"r");		//abre o arquivo readFile
		if(!arqcsv){							//se nao conseguir abrir, retorna o erro
			printf("Falha no carregamento do arquivo.");	
			return 0;
		}

		//abre o arquivo outFile ("arquivoTrab1si.bin")
		FILE *arqbin = fopen(outFile,"wb");		//abre o arquivo outFile
		if(!arqbin){							//se nao conseguir abrir, retorna o erro
			printf("Falha no carregamento do arquivo.");
			return 0;
		}

		k = 0; //contador usado abaixo
		
		//criar a struct do registro de cabeçalho
		struct regCab cabecalho;

		//atualiza os dados do cabeçalho
		cabecalho.status = '1';
		cabecalho.topoPilha = -1;
		cabecalho.tagCampo1 = '1';
		strcpy(cabecalho.desCampo1,"numero de inscricao do participante do ENEM");
		cabecalho.tagCampo2 = '2';
		strcpy(cabecalho.desCampo2,"nota do participante do ENEM na prova de matematica");
		cabecalho.tagCampo3 = '3';
		strcpy(cabecalho.desCampo3,"data");
		cabecalho.tagCampo4 = '4';
		strcpy(cabecalho.desCampo4,"cidade na qual o participante do ENEM mora");
		cabecalho.tagCampo5 = '5';
		strcpy(cabecalho.desCampo5,"nome da escola de ensino medio");
				
		//criacao do registro de cabeçalho

		fwrite(&cabecalho.status,sizeof(char),1,arqbin);	//escreve o status no primeiro byte
		fwrite(&cabecalho.topoPilha,sizeof(int),1,arqbin);	//escreve o topo da pilha nos quatro bytes seguintes
		fwrite(&cabecalho.tagCampo1,sizeof(char),1,arqbin);	//escreve a tagCampo1 no proximo byte, assim por diante...
		fwrite(&cabecalho.desCampo1,sizeof(char),strlen(cabecalho.desCampo1)+1,arqbin);
		for(k = 0; k < (sizeof(cabecalho.desCampo1) - (strlen(cabecalho.desCampo1)+1)); k++){ //conta quantos @ precisa colocar
			fputs("@",arqbin); //completa com lixo
		}
		fwrite(&cabecalho.tagCampo2,sizeof(char),1,arqbin);
		fwrite(&cabecalho.desCampo2,sizeof(char),strlen(cabecalho.desCampo2)+1,arqbin);
		for(k = 0; k < (sizeof(cabecalho.desCampo2) - (strlen(cabecalho.desCampo2)+1)); k++){ //conta quantos @ precisa colocar
			fputs("@",arqbin); //completa com lixo
		}
		fwrite(&cabecalho.tagCampo3,sizeof(char),1,arqbin);
		fwrite(&cabecalho.desCampo3,sizeof(char),strlen(cabecalho.desCampo3)+1,arqbin);
		for(k = 0; k < (sizeof(cabecalho.desCampo3) - (strlen(cabecalho.desCampo3)+1)); k++){ //conta quantos @ precisa colocar
			fputs("@",arqbin); //completa com lixo
		}
		fwrite(&cabecalho.tagCampo4,sizeof(char),1,arqbin);
		fwrite(&cabecalho.desCampo4,sizeof(char),strlen(cabecalho.desCampo4)+1,arqbin);
		for(k = 0; k < (sizeof(cabecalho.desCampo4) - (strlen(cabecalho.desCampo4)+1)); k++){ //conta quantos @ precisa colocar
			fputs("@",arqbin); //completa com lixo 
		}
		fwrite(&cabecalho.tagCampo5,sizeof(char),1,arqbin);
		fwrite(&cabecalho.desCampo5,sizeof(char),strlen(cabecalho.desCampo5)+1,arqbin);
		for(k = 0; k < (sizeof(cabecalho.desCampo5) - (strlen(cabecalho.desCampo5)+1)); k++){ //conta quantos @ precisa colocar
			fputs("@",arqbin); //completa com lixo 
		}

		//Preenche o restante da página de disco com lixo 
		for(k = 0; k < 15715; k++){ 
			fputs("@",arqbin);
		}
		
		//funcao para ler o arquivo de entrada e separar os campos
		int nroInscricao = 0; 	//variavel que vai ser usada para escrever no arquivo de saida o numero de inscricao
		double nota = -1;		// "           "              "          "             "       a nota
		char data[10];			// "           "              "          "             "       a data
		char cidade[30];		// "           "              "          "             "       a cidade
		char nomeEscola[30];	// "           "              "          "             "       o nome da escola
		
		char buffer[5][30];		//buffer temporario para ler os campos do arquivo de entrada

		//loop para limpar o buffer, a string cidade e a string nomeEscola (encher de \0)
		for(int l = 0; l < 30; l++){
			for(int m = 0; m < 5; m++){
				buffer[m][l] = '\0';
			}	
		cidade[l] = '\0';
		nomeEscola[l] = '\0';
		}
		
		//variaveis para o buffer: campo guarda a quantidade de campos do registro e pos é a posicao na string que será lida
		int campo, pos;

		//acumulador de byte para fazer a conta de quanto lixo resta colocar no final do registro 
		int acumulador;

		//campo encadeamento
		encadeamento = -1;

		//indicadores de tamanho dos campos variaveis
		int indicadorCidade = 0;
		int indicadorEscola = 0;

		//string buffer onde serão armazenados os registros em texto
		char linha[80];

		//string de apoio, só pra ignorar a primeira linha da entrada
		char primeiraLinha[80];

		//esse fgets é só pra ignorar a primeira linha da entrada
		fgets(primeiraLinha,sizeof(primeiraLinha),arqcsv);
		
		//loop para ler linha a linha do arquivo de entrada
		while(fgets(linha,sizeof(linha),arqcsv)){
			//zera a quantidade de campos e a posicao na string lida
			campo = 0;
			pos = 0;

			//zera o acumulador de bytes
			acumulador = 0;

			//loop para ler a linha inteira e separar os campos
			for(i = 0; i < sizeof(linha); i++){
				if(linha[i] == '\n' || linha[i] == '\r'){ 	//percorre char a char do registro até achar o \n
					break;
				}
				if(linha[i] == ','){	//se achar uma virgula, incrementa o numero de campos e reseta a posicao
					campo++;
					pos = 0;
				}
				else {								//se nao achar uma virgula,	
					buffer[campo][pos] = linha[i];	//lê o proximo char do registro e adiciona no buffer do campo e da posicao
					pos++;							//e incrementa a posicao
				}			
			}
			
			//coloca o campo removido ('-') no arquivo de saida
			fputs("-",arqbin);

			//coloca o campo encadeamento (4 bytes com o inteiro -1)
			fwrite(&encadeamento,sizeof(encadeamento),1,arqbin);
			
			//transforma a string buffer[0] (referente ao numero de inscricao) em um int nroInscricao
			nroInscricao = atoi(buffer[0]);

			//coloca o campo nroInscricao (4 bytes com o inteiro nroInscricao)
			fwrite(&nroInscricao,sizeof(nroInscricao),1,arqbin);

			//transforma a string buffer[1] (ref a nota) em um double nota
			nota = atof(buffer[1]);
			if(nota == 0){		//Se a nota for 0, é porque recebeu um campo nulo do atof
				nota = -1;		//Se campo de nota for nulo, nota recebe -1
			}

			//coloca o campo nota (8 bytes com o double nota)
			fwrite(&nota,sizeof(nota),1,arqbin);
			
			//copia a string buffer[2] (ref a data) para uma string data
			strcpy(data,buffer[2]);
			if(data[0] != '\0'){						//se data nao for nula,
				fwrite(&data,sizeof(char),10,arqbin);	//coloca o campo data (10 bytes com a string data)
			}
			//coloca "\0@@@@@@@@@" se a data for nula
			else{										//se for nula, 
				for(int l = 0; l < 10; l++){			//faz um loop de 10 vezes
					if(l == 0){
						fputc('\0',arqbin);
					}
					else{
						fputs("@",arqbin);				//preenchendo com lixo (@)
					}			
				}
			}
			
			//copia a string buffer[3] (ref a cidade) para uma string cidade
			strcpy(cidade,buffer[3]);
			if(cidade[0] != '\0'){										//se a cidade nao for nula,
				indicadorCidade = sizeof(char) + strlen(cidade) + 1;	//o indicador de tamanho do campo da cidade é atualizado,
				fwrite(&indicadorCidade,sizeof(indicadorCidade),1,arqbin);//coloca o campo indicador de tamanho (4 bytes com o int indicadorCidade),
				fputs("4",arqbin);										//coloca a tagCampo4 '4',
				fwrite(&cidade,sizeof(char),strlen(cidade)+1,arqbin);	//coloca o campo cidade
				acumulador = acumulador + indicadorCidade + sizeof(indicadorCidade); //e atualiza o acumulador de bytes usados
			}
			//copia a string buffer[4] (ref a nome da escola) para uma string nomeEscola
			strcpy(nomeEscola,buffer[4]);
			if(nomeEscola[0] != '\0'){									//se o nome da escola nao for nula,
				indicadorEscola = sizeof(char) + strlen(nomeEscola) + 1;//o indicador de tamanho do campo do nomeEscola é atualizado,
				fwrite(&indicadorEscola,sizeof(indicadorEscola),1,arqbin);//coloca o campo indicador de tamanho (4 bytes com o int indicadorEscola),
				fputs("5",arqbin);										//coloca a tagCampo5 '5',
				fwrite(&nomeEscola,sizeof(char),strlen(nomeEscola)+1,arqbin);//coloca o campo nomeEscola
				acumulador = acumulador + indicadorEscola + sizeof(indicadorEscola);//e atualiza o acumulador de bytes usados
			}

			//atualiza o acumulador com 1B (removido) + 4B (encad.) + 4B (nroInsc.) + 8B (nota) + 10B (data)
			acumulador = acumulador + 1 + sizeof(encadeamento) + sizeof(nroInscricao) + sizeof(nota) + 10;
 			
 			//conta quanto lixo precisa colocar no final do registro para completar 80B
			for(int l = 0; l < 80 - acumulador; l++){
				fputs("@",arqbin);
			}

			//loop para limpar o buffer, a string cidade e a string nomeEscola (encher de \0)
			for(int l = 0; l < 30; l++){
				for(int m = 0; m < 5; m++){
					buffer[m][l] = '\0';
				}
				cidade[l] = '\0';
				nomeEscola[l] = '\0';
			}
		} //fecha o while(fgets)
		   	
		//fecha os arquivos
		fclose(arqcsv);
		fclose(arqbin);

		//printar na tela o arquivo binario gerado
		arqbin = fopen(outFile,"rb");
		if(!arqbin){		//se nao conseguir abrir, retorna o erro
			printf("Falha no carregamento do arquivo.");
			return 0;
		}

		printf("%s",outFile);
		
	} //acaba a funcionalidade 1

	//Funcionalidade 2
	else if(func == '2'){
		
		//funcao para gerar uma string readFile
		char *token = strtok(entrada, " ");
		for(i = 0; i < 3; i++){
			if(i == 1 && token){
				strcpy(readFile,token);
			}
			
			token = strtok(NULL," ");
		}

		//loop para tirar o \n da string readFile
		for(i = 0; i < 50; i++){
			if(readFile[i] == '\n'){
				readFile[i] = '\0';
			}
		}

		//abre o arquivo de leitura
		FILE *arqbin = fopen(readFile,"r");	//abre o arquivo readFile
		if(!arqbin){						//se nao conseguir abrir, retorna o erro
			printf("Falha no processamento do arquivo.");	
			return 0;
		}

		//verifica se o arquivo esta com integridade (se o primeiro char eh '0' ou '1')
		fseek(arqbin,0,SEEK_SET);
		fread(&removidoChar,sizeof(char),1,arqbin);
		if(removidoChar == '0'){
			printf("Falha no processamento do arquivo.");
			return 0;
		}

		//seta o ponteiro pro primeiro registro (segunda pagina)
		fseek(arqbin,16000,SEEK_SET);

		//verifica se existem registros na segunda pagina
		if(feof(arqbin)){
			printf("Registro inexistente.");
			return 0;
		}
		acessos++; //incrementa os acessos a disco
		numReg++;
		
		//seta o ponteiro pro começo do buffer
		fseek(arqbin,16000,SEEK_SET);
		
		//limpar os vetores campoVar e campoVar2
		int h = 0;
		for(h = 0; h < 25; h++){			
			campoVar[h] = '\0';
			campoVar2[h] = '\0';
		}

		//loop para percorrer o arquivo
		while(arqbin){

			//incrementa os acessos a disco a cada 200 registros lidos
			if(numReg >= 200){
				numReg = 0;
				acessos++;
			}

			fread(&removidoChar,sizeof(char),1,arqbin);		//le o primeiro byte e coloca em removidoChar			
			fread(&encadeamento,sizeof(int),1,arqbin);		//le os 4 seguintes	e coloca em encadeamento		 			
			fread(&nroInscricao,sizeof(int),1,arqbin);		//le os 4 seguintes e coloca em nroInscricao 			
			printf("%d",nroInscricao);
			fread(&nota,sizeof(double),1,arqbin);			//le os 8 seguintes e coloca em nota
			if(nota != -1.0){
				printf(" %.1f",nota);
			}
			fread(&data,sizeof(char),10,arqbin);			//le os 10 seguintes e coloca em data
			if(data[0] != '\0'){
				printf(" %s",data);
			}
			fread(&indVar,sizeof(int),1,arqbin);			//le os 4 seguintes e coloca em indVar
	
			//checa se indVar nao eh 40404040 (se existe)	
			if(indVar != 1077952576){
				printf(" %d",indVar-2);						//printa o tamanho do campo variavel
				fread(&tag4,sizeof(char),1,arqbin);			//le o char da tag4
				fread(&campoVar,sizeof(char),indVar-1,arqbin);//le o campo variavel
				printf(" %s",campoVar);						//printa o campo variavel
				fread(&indVar,sizeof(int),1,arqbin);		//le os 4 bytes seguintes e coloca em indVar
				//checa se indVar nao eh 40404040 (se existe)
				if(indVar != 1077952576){					
					printf(" %d",indVar-2);					//printa o tamanho do campo variavel
					fread(&tag5,sizeof(char),1,arqbin);		//le o char da tag5
					fread(&campoVar2,sizeof(char),indVar-1,arqbin);//le o campo variavel 2
					printf(" %s",campoVar2);				//printa o campo variavel 2
				}
			}

			//passa lendo o lixo
			fread(&arroba,sizeof(char),1,arqbin);
			while(arroba == '@'){
				fread(&arroba,sizeof(char),1,arqbin);
			}

			//incrementa a quantidade de registros
			numReg++;

			//verifica se o arquivo nao acabou
			if(feof(arqbin)){
				break;
			}
			else{
				fseek(arqbin,-1,SEEK_CUR);
				printf("\n");
			}
				
		} //sai do loop qnd acabar o buffer de texto

		//printa a qtd de acessos a paginas de disco
		printf("\nNúmero de páginas de disco acessadas: %d",acessos);

		//fecha o arquivo
		fclose(arqbin);

	} //acaba funcionalidade 2

	//Funcionalidade 3
	else if(func == '3'){
		//funcao para gerar uma string readFile, NomeDoCampo e valor
		char *token = strtok(entrada, " ");
		for(i = 0; i < 10; i++){
			if(i == 1 && token){
				strcpy(readFile,token);
			}
			else if(i == 2 && token){
				strcpy(NomeDoCampo,token);
			}
			else if(i == 3 && token){
				strcpy(valor,token);
			}
			else if(i > 3 && token){
				strcat(valor," ");
				strcat(valor,token);
			}
			token = strtok(NULL," ");
		}
		//verifica se nao tem nenhum \n nas strings
		for(i = 0; i < 30; i++){
			if(readFile[i] == '\n'){
				readFile[i] = '\0';
			}
			if(NomeDoCampo[i] == '\n'){
				NomeDoCampo[i] = '\0';
			}
			if(valor[i] == '\n'){
				valor[i] = '\0';
			}
		}
		//abre o arquivo de leitura
		FILE *arqbin = fopen(readFile,"r");	//abre o arquivo readFile
		if(!arqbin){						//se nao conseguir abrir, retorna o erro
			printf("Falha no processamento do arquivo.");	
			return 0;
		}	
		//verifica a integridade do arquivo (le o primeiro byte se eh '0')
		fseek(arqbin,0,SEEK_SET);
		fread(&removidoChar,sizeof(char),1,arqbin);
		if(removidoChar == '0'){
			printf("Falha no processamento do arquivo.");
			return 0;
		}
		//le a proxima pagina de disco
		fseek(arqbin,16000,SEEK_SET);
		acessos = acessos + 2; //incrementa o numero de acessos a disco

		//verifica se a entrada nao eh nula
		if(NomeDoCampo[0] != '\0'){
			//ve se o NomeDoCampo eh nroInscricao
			if(strcmp(NomeDoCampo,"nroInscricao") == 0){	
				//enquanto tiver arquivo a ser lido
				while(arqbin){
					//incrementa os acessos a disco a cada 200 registros
					if(numReg >= 200){
						numReg = 0;
						acessos++;
					}
					//verifica se o valor escolhido pelo usuario nao é nulo
					if(valor[0] == '\0'){
						printf("Falha no processamento do arquivo.");
						return 0;
					}
					int valorInt = strtol(valor,NULL,10);		//transforma a string valor em um inteiro
					fseek(arqbin,5,SEEK_CUR);					//pula 5 bytes
					fread(&nroInscricao,sizeof(int),1,arqbin);	//le os 4 seguintes bytes e coloca em nroInscricao
					//caso o numero escolhido pelo usuario for encontrado
					if(valorInt == nroInscricao){				
						fseek(arqbin,-9,SEEK_CUR);				//volta pro começo do registro
						fread(&removidoChar,sizeof(char),1,arqbin);			//le o primeiro byte
						if(removidoChar == '-'){							//verifica se o registro existe ou não
							fread(&encadeamento,sizeof(int),1,arqbin);		//le os 4 seguintes	e coloca em encadeamento		 			
							fread(&nroInscricao,sizeof(int),1,arqbin);		//le os 4 seguintes e coloca em nroInscricao 			
							printf("%d",nroInscricao);						//printa o numero de inscricao
							fread(&nota,sizeof(double),1,arqbin);			//le os 8 seguintes e coloca em nota
							if(nota != -1.0){								//só printa se a nota existir
								printf(" %.1f",nota);
							}
							fread(&data,sizeof(char),10,arqbin);			//le os 10 seguintes e coloca em data
							if(data[0] != '\0'){
								printf(" %s",data);
							}
							fread(&indVar,sizeof(int),1,arqbin);			//le os 4 seguintes e coloca em indVar

							//checa se indVar nao eh 40404040 (se existe ou nao um indicador de tamanho ["@@@@"])			
							if(indVar != 1077952576){						//se nao for @@@@				
								printf(" %d",indVar-2);						//printa o indicador - 2
								fread(&tag4,sizeof(char),1,arqbin);			//le o byte da tag do campo
								fread(&campoVar,sizeof(char),indVar-1,arqbin);//le o campo variavel 1
								printf(" %s",campoVar);						//printa o campo variavel 1
								fread(&indVar,sizeof(int),1,arqbin);		//le os 4 bytes do indicador de tamanho 
								
								//checa se indVar não eh 40404040 (se existe ou nao um indicador de tamanho ["@@@@"])			
								if(indVar != 1077952576){					//se nao for @@@@
									printf(" %d",indVar-2);					//printa o indicador - 2
									fread(&tag5,sizeof(char),1,arqbin);		//le o byte da tag do campo
									fread(&campoVar2,sizeof(char),indVar-1,arqbin);//le o campo variavel 2
									printf(" %s",campoVar2);				//printa o campo variavel 2
								}
							}
						}
						//caso o removidoChar nao for '-', o registro nao existe
						else{ 
							printf("Registro inexistente.");	
							break;
						}

						//printa o numero de paginas de disco acessadas
						printf("\nNúmero de páginas de disco acessadas: %d",acessos);
						break;
					}
					//se o valorInt nao for igual o nroInscricao, entao passa pro proximo registro
					else{
						fseek(arqbin,71,SEEK_CUR);
					}
					//incrementa o numero de registros lidos
					numReg++;

					//char para verificar se nao acabou o arquivo
					char endoffile;
					fread(&endoffile,sizeof(char),1,arqbin);
					//verifica se nao acabou o arquivo
					if(feof(arqbin)){
						printf("Registro inexistente.");
						break;
					}
					//se nao acabou, volta 1 byte
					else{
						fseek(arqbin,-1,SEEK_CUR);
					}

				} //acaba loop while

			}
			//ve se o NomeDoCampo eh nota
			else if(strcmp(NomeDoCampo,"nota") == 0){
				certos = 0; //contador para contar quantas vezes achou algum registro que satisfaça
				//enquanto tiver arquivo a ser lido
				while(arqbin){
					acum = 0; //variavel para contar quantos bytes ja foram percorridos no registro
					//incrementa os acessos a disco a cada 200 registros
					if(numReg >= 200){
						numReg = 0;
						acessos++;
					}
					//verifica se o valor escolhido pelo usuario nao é nulo
					if(valor[0] == '\0'){
						printf("Falha no processamento do arquivo.");
						return 0;
					}
					//verifica se o valor escolhido pelo usuario é um numero
					if(!ehNumero(valor)){
						printf("Falha no processamento do arquivo.");
						return 0;
					}
					double valorFloat = strtod(valor,NULL); 	//transforma a string valor em um double
					fseek(arqbin,9,SEEK_CUR);					//pula 9 bytes
					fread(&nota,sizeof(double),1,arqbin);		//le os 8 bytes seguintes e coloca em nota
					//caso o numero escolhido pelo usuario for encontrado
					if(valorFloat == nota){
						fseek(arqbin,-17,SEEK_CUR);				//volta pro inicio do registro
						fread(&removidoChar,sizeof(char),1,arqbin);			//le o primeiro byte e coloca em removidoChar
						acum ++;	//atualiza o acumulador
						//se o registro nao estiver removido
						if(removidoChar == '-'){					
							fread(&encadeamento,sizeof(int),1,arqbin);		//le os 4 seguintes	e coloca em encadeamento		 			
							fread(&nroInscricao,sizeof(int),1,arqbin);		//le os 4 seguintes e coloca em nroInscricao 			
							printf("%d",nroInscricao);
							fread(&nota,sizeof(double),1,arqbin);			//le os 8 seguintes e coloca em nota
							if(nota != -1.0){			//printa a nota se existir
								printf(" %.1f",nota);
							}
							fread(&data,sizeof(char),10,arqbin);			//le os 10 seguintes e coloca em data
							if(data[0] != '\0'){		//printa a data se existir
								printf(" %s",data);
							}
							acum = acum + 4 + 4 + 8 + 10; 					//atualiza o acumulador
							fread(&indVar,sizeof(int),1,arqbin);			//le os 4 seguintes e coloca em indVar

							//checa se indVar nao eh 40404040 ("@@@@")
							if(indVar != 1077952576){
								printf(" %d",indVar-2);				//printa indVar - 2
								fread(&tag4,sizeof(char),1,arqbin);	//le o proximo byte e coloca em tag4
								fread(&campoVar,sizeof(char),indVar-1,arqbin);//le o campo variavel
								printf(" %s",campoVar);				//printa o campo variavel
								acum = acum + 4 + indVar;			//atualiza o acumulador
								fread(&indVar,sizeof(int),1,arqbin);//le o proximo inteiro
								//checa se o inteiro lido não é lixo
								if(indVar != 1077952576){			
									printf(" %d",indVar-2);			//printa indVar - 2
									fread(&tag5,sizeof(char),1,arqbin);//le o proximo byte e coloca em tag5
									fread(&campoVar2,sizeof(char),indVar-1,arqbin);//le o campo variavel
									printf(" %s",campoVar2);		//printa o campo variavel
									acum = acum + 4 + indVar;		//atualiza o acumulador
								}
							}
							printf("\n");	//pula uma linha
							certos++;		//atualiza a quantidade de registros que bateram
							fseek(arqbin,80-acum,SEEK_CUR);//pula pro proximo registro, usando o acumulador de bytes
						}
						//se o registro estiver removido
						else{
							fseek(arqbin,79,SEEK_CUR);
						}				
					}
					//se o numero escolhido pelo usuario nao for encontrado, pula pro proximo registro
					else{
						fseek(arqbin,63,SEEK_CUR);
					}
					//incrementa o numero de registros lidos
					numReg++;
					//char para verificar se nao acabou o arquivo
					char endoffile;
					fread(&endoffile,sizeof(char),1,arqbin);
					//verifica se nao acabou o arquivo
					if(feof(arqbin)){		//se acabou o arquivo,
						if(certos > 0){		//se tiver achado algum registro correspondente, printa o numero de paginas acessadas
							printf("Número de páginas de disco acessadas: %d",acessos);
							break;
						}
						else{				//se nao tiver achado, entao printa registro inexistente
							printf("Registro inexistente.");
							break;
						}
					}
					//se nao acabou o arquivo, volta 1 byte
					else{
						fseek(arqbin,-1,SEEK_CUR);
					}

				} //acaba loop while

			}
			//ve se o NomeDoCampo eh data
			else if(strcmp(NomeDoCampo,"data") == 0){
				certos = 0; //contador para contar quantas vezes achou algum registro que satisfaça
				//enquanto tiver arquivo a ser lido
				while(arqbin){
					acum = 0; //variavel para contar quantos bytes ja foram percorridos no registro
					//incrementa os acessos a disco a cada 200 registros
					if(numReg == 200){
						numReg = 0;
						acessos++;
					}
					//verifica se o valor escolhido pelo usuario nao é nulo
					if(valor[0] == '\0'){
						printf("Falha no processamento do arquivo.");
						return 0;
					}
					char valorData[11];			//cria uma string para armazenar o valor
					valorData[10] = '\0';		//anula o ultimo byte
					fseek(arqbin,17,SEEK_CUR);	//pula 17 bytes
					fread(&valorData,sizeof(char),10,arqbin);//le a string e coloca em valorData
					//verifica se o valor lido é igual a data dado pelo usuario
					if(strcmp(valorData,valor) == 0){
						fseek(arqbin,-27,SEEK_CUR);	//volta pro começo do registro
						fread(&removidoChar,sizeof(char),1,arqbin);//le o primeiro byte do registro
						acum ++; //incrementa o acumulador
						//se o registro nao estiver removido
						if(removidoChar == '-'){			
							fread(&encadeamento,sizeof(int),1,arqbin);		//le os 4 seguintes	e coloca em encadeamento		 			
							fread(&nroInscricao,sizeof(int),1,arqbin);		//le os 4 seguintes e coloca em nroInscricao 			
							printf("%d",nroInscricao);
							fread(&nota,sizeof(double),1,arqbin);			//le os 8 seguintes e coloca em nota
							if(nota != -1.0){		//printa a nota se existir
								printf(" %.1f",nota);
							}
							fread(&data,sizeof(char),10,arqbin);			//le os 10 seguintes e coloca em data
							if(data[0] != '\0'){	//printa a data se existir
								printf(" %s",data);
							}
							acum = acum + 4 + 4 + 8 + 10; 					//atualiza o acumulador
							fread(&indVar,sizeof(int),1,arqbin);			//le os 4 seguintes e coloca em indVar

							//checa se indVar nao eh 40404040 ("@@@@")
							if(indVar != 1077952576){
								printf(" %d",indVar-2);				//printa indVar - 2
								fread(&tag4,sizeof(char),1,arqbin);	//le o proximo byte e coloca em tag4
								fread(&campoVar,sizeof(char),indVar-1,arqbin);//le o campo variavel
								printf(" %s",campoVar);				//printa o campo variavel
								acum = acum + 4 + indVar;			//atualiza o acumulador
								fread(&indVar,sizeof(int),1,arqbin);//le o proximo inteiro
								//checa se o inteiro lido não é lixo
								if(indVar != 1077952576){			
									printf(" %d",indVar-2);			//printa indVar - 2
									fread(&tag5,sizeof(char),1,arqbin);//le o proximo byte e coloca em tag5
									fread(&campoVar2,sizeof(char),indVar-1,arqbin);//le o campo variavel
									printf(" %s",campoVar2);		//printa o campo variavel
									acum = acum + 4 + indVar;		//atualiza o acumulador
								}
							}
							printf("\n");	//pula uma linha
							certos++;		//atualiza a quantidade de registros que bateram
							fseek(arqbin,80-acum,SEEK_CUR);//pula pro proximo registro, usando o acumulador de bytes
						}
						//se o registro estiver removido
						else{
							fseek(arqbin,79,SEEK_CUR);
						}				
					}
					//se o numero escolhido pelo usuario nao for encontrado, pula pro proximo registro
					else{
						fseek(arqbin,53,SEEK_CUR);
					}
					//incrementa o numero de registros lidos
					numReg++;
					//char para verificar se nao acabou o arquivo
					char endoffile;
					fread(&endoffile,sizeof(char),1,arqbin);
					//verifica se nao acabou o arquivo
					if(feof(arqbin)){		//se acabou o arquivo,
						if(certos > 0){		//se tiver achado algum registro correspondente, printa o numero de paginas acessadas
							printf("Número de páginas de disco acessadas: %d",acessos);
							break;
						}
						else{				//se nao tiver achado, entao printa registro inexistente
							printf("Registro inexistente.");
							break;
						}
					}
					//se nao acabou o arquivo, volta 1 byte
					else{
						fseek(arqbin,-1,SEEK_CUR);
					}

				} //acaba loop while

			}
			//ve se o NomeDoCampo eh cidade
			else if(strcmp(NomeDoCampo,"cidade") == 0){
				certos = 0; //contador para contar quantas vezes achou algum registro que satisfaça
				//enquanto tiver arquivo a ser lido
				while(arqbin){
					acum = 0; //variavel para contar quantos bytes ja foram percorridos no registro
					//incrementa os acessos a disco a cada 200 registros
					if(numReg >= 200){
						numReg = 0;
						acessos++;
					}
					//verifica se o valor escolhido pelo usuario nao é nulo
					if(valor[0] == '\0'){
						printf("Falha no processamento do arquivo.");
						return 0;
					}
					char valorCampo[30];		//cria uma string para armazenar o valor
					valorCampo[29] = '\0';		//anula o ultimo byte
					fseek(arqbin,27,SEEK_CUR);	//pula 27 bytes
					fread(&indVar,sizeof(int),1,arqbin);//le o inteiro e coloca em indVar
					//checa se indVar nao eh 40404040 ("@@@@")
					if(indVar != 1077952576){
						fread(&tag4,sizeof(char),1,arqbin);	//le o proximo byte e coloca em tag4
						//verifica se a tag é de cidade
						if(tag4 == '4'){					
							fread(&valorCampo,sizeof(char),indVar-1,arqbin); //le o campo variavel
							//verifica se o valor lido é igual ao valor dado pelo usuario
							if(strcmp(valorCampo,valor) == 0){	
								fseek(arqbin,-(indVar + 4 + 27),SEEK_CUR);			//volta pro inicio do registro
								fread(&removidoChar,sizeof(char),1,arqbin);			//le o primeiro byte e coloca em removido char
								acum ++;	//incrementa o acumulador
								//se o registro nao estiver removido
								if(removidoChar == '-'){			
									fread(&encadeamento,sizeof(int),1,arqbin);		//le os 4 seguintes	e coloca em encadeamento		 			
									fread(&nroInscricao,sizeof(int),1,arqbin);		//le os 4 seguintes e coloca em nroInscricao 			
									printf("%d",nroInscricao);
									fread(&nota,sizeof(double),1,arqbin);			//le os 8 seguintes e coloca em nota
									if(nota != -1.0){			//printa a nota se existir
										printf(" %.1f",nota);
									}
									fread(&data,sizeof(char),10,arqbin);			//le os 10 seguintes e coloca em data
									if(data[0] != '\0'){		//printa a data se existir
										printf(" %s",data);
									}
									acum = acum + 4 + 4 + 8 + 10; 					//atualiza o acumulador
									fread(&indVar,sizeof(int),1,arqbin);			//le os 4 seguintes e coloca em indVar
									//checa se indVar nao eh 40404040 ("@@@@")
									if(indVar != 1077952576){
										printf(" %d",indVar-2);						//printa indVar - 2
										fread(&tag4,sizeof(char),1,arqbin);			//le o proximo byte e coloca em tag4
										fread(&campoVar,sizeof(char),indVar-1,arqbin);//le o campo variavel
										printf(" %s",campoVar);						//printa o campo variavel
										acum = acum + 4 + indVar;					//atualiza o acumulador
										fread(&indVar2,sizeof(int),1,arqbin);		//le os 4 bytes seguintes e coloca em indVar2
										acum = acum + 4;							//atualiza o acumulador
										//checa se indVar2 nao eh 40404040 ("@@@@")
										if(indVar2 != 1077952576){						
											printf(" %d",indVar2-2);				//printa indVar - 2
											fread(&tag5,sizeof(char),1,arqbin);		//le o proximo byte e coloca em tag5
											fread(&campoVar2,sizeof(char),indVar2-1,arqbin);//le o campo variavel
											printf(" %s",campoVar2);				//printa o campo variavel
											acum = acum + indVar2;					//atualiza o acumulador
										}	
									}
									printf("\n");	//pula a linha
									certos++;		//incrementa a qtd de registros certos
									fseek(arqbin,80-acum,SEEK_CUR);	//pula pro proximo registro usando o acumulador de bytes
								}
								//se o registro estiver removido, passa pro proximo registro
								else{
									fseek(arqbin,79,SEEK_CUR);
								}

							}
							//se nao for igual, passa pro proximo registro
							else{
								fseek(arqbin,80-(indVar+31),SEEK_CUR);
							}

						}
						//caso nao for, passa pro proximo registro
						else{
							fseek(arqbin,48,SEEK_CUR);
						}

					}
					//se indVar for nulo ("@@@@"), pula pro proximo registro
					else{
						fseek(arqbin,49,SEEK_CUR);
					}
					//incrementa o numero de registros lidos
					numReg++;
					//char para verificar se nao acabou o arquivo
					char endoffile;
					fread(&endoffile,sizeof(char),1,arqbin);
					//verifica se nao acabou o arquivo
					if(feof(arqbin)){		//se acabou o arquivo,
						if(certos > 0){		//se tiver achado algum registro correspondente, printa o numero de paginas acessadas
							printf("Número de páginas de disco acessadas: %d",acessos);
							break;
						}
						else{				//se nao tiver achado, entao printa registro inexistente
							printf("Registro inexistente.");
							break;
						}
					}
					//se nao acabou o arquivo, volta 1 byte
					else{
						fseek(arqbin,-1,SEEK_CUR);
					}

				} //acaba loop while
			
			}
			//ve se o NomeDoCampo eh nomeEscola
			else if(strcmp(NomeDoCampo,"nomeEscola") == 0){
				certos = 0; //contador para contar quantas vezes achou algum registro que satisfaça
				//enquanto tiver arquivo a ser lido
				while(arqbin){
					acum = 0; //variavel para contar quantos bytes ja foram percorridos no registro
					//incrementa os acessos a disco a cada 200 registros
					if(numReg == 200){
						numReg = 0;
						acessos++;
					}
					//verifica se o valor escolhido pelo usuario nao é nulo
					if(valor[0] == '\0'){
						printf("Falha no processamento do arquivo.");
						return 0;
					}
					char valorCampo[30];		//cria uma string para armazenar o valor
					valorCampo[29] = '\0';		//anula o ultimo byte
					fseek(arqbin,27,SEEK_CUR);	//pula 27 bytes
					fread(&indVar,sizeof(int),1,arqbin);//le o inteiro e coloca em indVar
					//checa se indVar nao eh 40404040 ("@@@@")
					if(indVar != 1077952576){
						fread(&tag4,sizeof(char),1,arqbin); //le o proximo byte e coloca em tag4
						//verifica se a tag é de cidade
						if(tag4 == '4'){
							fread(&valorCampo,sizeof(char),indVar-1,arqbin);//le o campo variavel
							fread(&indVar2,sizeof(int),1,arqbin); 			//le o proximo int indicador de campo variavel
							//checa se indVar2 nao eh 40404040 ("@@@@")
							if(indVar2 != 1077952576){
								fread(&tag5,sizeof(char),1,arqbin); //le o proximo byte e coloca em tag4
								//verifica se a tag é do nome da escola
								if(tag5 == '5'){
									fread(&valorCampo,sizeof(char),indVar2-1,arqbin);	//le o campo variavel
									//verifica se o valor lido é igual ao valor dado pelo usuario
									if(strcmp(valorCampo,valor) == 0){	
										fseek(arqbin,-(indVar2 + 4 + 4 + 27 + indVar),SEEK_CUR);//volta pro começo do registro
										fread(&removidoChar,sizeof(char),1,arqbin);				//le o primeiro byte e coloca em removido char
										acum ++; //incrementa o acumulador
										//verifica se o registro nao foi removido
										if(removidoChar == '-'){			
											fread(&encadeamento,sizeof(int),1,arqbin);		//le os 4 seguintes	e coloca em encadeamento		 			
											fread(&nroInscricao,sizeof(int),1,arqbin);		//le os 4 seguintes e coloca em nroInscricao 			
											printf("%d",nroInscricao);
											fread(&nota,sizeof(double),1,arqbin);			//le os 8 seguintes e coloca em nota
											if(nota != -1.0){			//printa a nota se existir
												printf(" %.1f",nota);
											}
											fread(&data,sizeof(char),10,arqbin);			//le os 10 seguintes e coloca em data
											if(data[0] != '\0'){		//printa a data se existir
												printf(" %s",data);
											}
											acum = acum + 4 + 4 + 8 + 10; 					//atualiza o acumulador
											fread(&indVar,sizeof(int),1,arqbin);			//le os 4 seguintes e coloca em indVar
											//checa se indVar nao eh 40404040 ("@@@@")
											if(indVar != 1077952576){
												printf(" %d",indVar-2);						//printa indVar - 2
												fread(&tag4,sizeof(char),1,arqbin);			//le o proximo byte e coloca em tag4
												fread(&campoVar,sizeof(char),indVar-1,arqbin);//le o campo variavel
												printf(" %s",campoVar);						//printa o campo variavel
												acum = acum + 4 + indVar;					//atualiza o acumulador
												fread(&indVar2,sizeof(int),1,arqbin);		//le os 4 bytes seguintes e coloca em indVar2
												//checa se indVar2 nao eh 40404040 ("@@@@")
												if(indVar2 != 1077952576){						
													printf(" %d",indVar2-2);				//printa indVar - 2
													fread(&tag5,sizeof(char),1,arqbin);		//le o proximo byte e coloca em tag5
													fread(&campoVar2,sizeof(char),indVar2-1,arqbin);//le o campo variavel
													printf(" %s",campoVar2);				//printa o campo variavel
													acum = acum + 4 + indVar2;					//atualiza o acumulador
												}	
											}
											printf("\n");	//pula a linha
											certos++;		//incrementa a qtd de registros certos
											fseek(arqbin,80-acum,SEEK_CUR);	//pula pro proximo registro usando o acumulador de bytes
										}
										//se o registro estiver removido, passa pro proximo registro
										else{
											fseek(arqbin,79,SEEK_CUR);
										}

									}
									//se nao for igual, passa pro proximo registro
									else{
										fseek(arqbin,80-(indVar+4+27+4+indVar2),SEEK_CUR);
									}

								}
								//se nao tiver tag do nome da escola, passa pro proximo registro
								else{
									fseek(arqbin,80-(indVar+1+32),SEEK_CUR);
								}

							}
							//se indVar2 for nulo ("@@@@"), pula pro proximo registro
							else{
								fseek(arqbin,80-(indVar+31+4),SEEK_CUR);
							}

						}
						//se nao for, verifica se a tag é do nome da escola
						else if(tag4 == '5'){
							fread(&valorCampo,sizeof(char),indVar-1,arqbin); //le o campo variavel
							//verifica se o valor lido é igual ao valor dado pelo usuario
							if(strcmp(valorCampo,valor) == 0){
								fseek(arqbin,-(indVar + 4 + 27),SEEK_CUR);	//volta pro começo do registro
								fread(&removidoChar,sizeof(char),1,arqbin);	//le o primeiro byte e coloca em removido char
								acum ++;	//incrementa o acumulador
								//verifica se o registro nao foi removido
								if(removidoChar == '-'){			
									fread(&encadeamento,sizeof(int),1,arqbin);		//le os 4 seguintes	e coloca em encadeamento		 			
									fread(&nroInscricao,sizeof(int),1,arqbin);		//le os 4 seguintes e coloca em nroInscricao 			
									printf("%d",nroInscricao);
									fread(&nota,sizeof(double),1,arqbin);			//le os 8 seguintes e coloca em nota
									if(nota != -1.0){					//printa a nota se existir
										printf(" %.1f",nota);
									}
									fread(&data,sizeof(char),10,arqbin);			//le os 10 seguintes e coloca em data
									if(data[0] != '\0'){				//printa a data se existir
										printf(" %s",data);
									}
									acum = acum + 4 + 4 + 8 + 10; 					//atualiza o acumulador
									fread(&indVar,sizeof(int),1,arqbin);			//le os 4 seguintes e coloca em indVar
									//checa se indVar nao eh 40404040 ("@@@@")
									if(indVar != 1077952576){
										printf(" %d",indVar-2);						//printa indVar - 2
										fread(&tag4,sizeof(char),1,arqbin);			//le o proximo byte e coloca em tag4
										fread(&campoVar,sizeof(char),indVar-1,arqbin);//le o campo variavel
										printf(" %s",campoVar);						//printa o campo variavel
										acum = acum + 4 + indVar;					//atualiza o acumulador
									}
									printf("\n");	//pula a linha
									certos++;		//incrementa a qtd de registros certos
									fseek(arqbin,80-acum,SEEK_CUR);	//pula pro proximo registro usando o acumulador de bytes
								}
								//se o registro estiver removido, passa pro proximo registro
								else{
									fseek(arqbin,79,SEEK_CUR);
								}

							}
							//se nao for igual, passa pro proximo registro
							else{
								fseek(arqbin,80-(indVar+31),SEEK_CUR);
							}
							
						}
						//se nao for tb, pula pro proximo registro
						else{
							fseek(arqbin,48,SEEK_CUR);
						}

					}
					//se indVar for nulo ("@@@@"), pula pro proximo registro
					else{
						fseek(arqbin,49,SEEK_CUR);
					}
					//incrementa o numero de registros lidos
					numReg++;
					//char para verificar se nao acabou o arquivo
					char endoffile;
					fread(&endoffile,sizeof(char),1,arqbin);
					//verifica se nao acabou o arquivo
					if(feof(arqbin)){		//se acabou o arquivo,
						if(certos > 0){		//se tiver achado algum registro correspondente, printa o numero de paginas acessadas
							printf("Número de páginas de disco acessadas: %d",acessos);
							break;
						}
						else{				//se nao tiver achado, entao printa registro inexistente
							printf("Registro inexistente.");
							break;
						}
					}
					//se nao acabou o arquivo, volta 1 byte
					else{
						fseek(arqbin,-1,SEEK_CUR);
					}

				} //acaba loop while
			}
			//caso nao for nenhum, dá erro
			else{
				printf("Falha no processamento do arquivo.");
			}
		}
		//se a entrada for nula, dá erro
		else{
			printf("Falha no processamento do arquivo.");
		}
		//fecha o arquivo
		fclose(arqbin);

	} //acaba a funcionalidade 3

	//Funcionalidade 4
	else if(func == '4'){
		acessos = 0;
		//funcao para gerar uma string readFile
		char *token = strtok(entrada, " ");
		for(i = 0; i < 3; i++){
			if(i == 1 && token){
				strcpy(readFile,token);
			}
			else if(i == 2 && token){
				strcpy(valor,token);
			}
			token = strtok(NULL," ");
		}

		for(i = 0; i < 30; i++){
			if(readFile[i] == '\n'){
				readFile[i] = '\0';
			}
			if(NomeDoCampo[i] == '\n'){
				NomeDoCampo[i] = '\0';
			}
			if(valor[i] == '\n'){
				valor[i] = '\0';
			}
		}

		//abre o arquivo de leitura
		FILE *arqbin = fopen(readFile,"r");	//abre o arquivo readFile
		if(!arqbin){						//se nao conseguir abrir, retorna o erro
			printf("Falha no processamento do arquivo.");	
			return 0;
		}
		//verifica se o valor que o usuario escolheu é um numero
		if(!ehNumero(valor)){
			printf("Falha no processamento do arquivo11.");
			return 0;
		}
		//verifica se o arquivo esta com integridade (se o primeiro char eh '0' ou '1')
		fseek(arqbin,0,SEEK_SET);
		fread(&removidoChar,sizeof(char),1,arqbin);
		if(removidoChar == '0'){
			printf("Falha no processamento do arquivo.");
			return 0;
		}
		//transforma a string valor em um int rrn
		rrn = strtol(valor,NULL,10);
		//vai pro comeco dos registros
		fseek(arqbin,16000,SEEK_SET);
		acessos++; //incrementa os acessos
		//vai pro rrn escolhido
		fseek(arqbin,80*rrn,SEEK_CUR);
		acessos++; //incrementa os acessos
		//le o primeiro byte
		fread(&removidoChar,sizeof(char),1,arqbin);
		//se o registro nao foi removido
		if(removidoChar == '-'){
			fread(&encadeamento,sizeof(int),1,arqbin);		//le os 4 seguintes	e coloca em encadeamento		 			
			fread(&nroInscricao,sizeof(int),1,arqbin);		//le os 4 seguintes e coloca em nroInscricao 			
			printf("%d",nroInscricao);
			fread(&nota,sizeof(double),1,arqbin);			//le os 8 seguintes e coloca em nota
			if(nota != -1.0){				//printa a nota se existir
				printf(" %.1f",nota);
			}
			fread(&data,sizeof(char),10,arqbin);			//le os 10 seguintes e coloca em data
			if(data[0] != '\0'){			//printa a data se existir
				printf(" %s",data);
			}
			fread(&indVar,sizeof(int),1,arqbin);			//le os 4 seguintes e coloca em indVar
	
			//checa se indVar nao eh 40404040 ("@@@@")
			if(indVar != 1077952576){
				printf(" %d",indVar-2);				//printa indVar - 2
				fread(&tag4,sizeof(char),1,arqbin);	//le o proximo byte e coloca em tag4
				fread(&campoVar,sizeof(char),indVar-1,arqbin);//le o campo variavel
				printf(" %s",campoVar);				//printa o campo variavel
				fread(&indVar,sizeof(int),1,arqbin);//le o proximo inteiro
				//checa se o inteiro lido não é lixo
				if(indVar != 1077952576){			
					printf(" %d",indVar-2);			//printa indVar - 2
					fread(&tag5,sizeof(char),1,arqbin);//le o proximo byte e coloca em tag5
					fread(&campoVar2,sizeof(char),indVar-1,arqbin);//le o campo variavel
					printf(" %s",campoVar2);		//printa o campo variavel
				}
			}
			//printa o numero de paginas de disco acessadas
			printf("\nNúmero de páginas de disco acessadas: %d",acessos);
		}
		//se foi removido
		else{
			printf("Registro inexistente.");
			return 0;
		}	
		//fecha o arquivo
		fclose(arqbin);

	}

	//Caso nao tiver a funcionalidade implementada ainda
	else{
		printf("Funcionalidade %c nao implementada.\n",func);
		return 0;
	}

	return 0;
}