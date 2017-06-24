#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "b2x.h"

int main(int argc, char **argv, char **envp){
	FILE *executavel, *saida, *script;
	char byt, byt_back, byt_script, linha[1000];
	long long int tam_execu, pos_execu = 0, pos_back, tam_script,
		pos_script = 0;
	int cont_sepa,confirm_sepa = 0, cont_linha, linha_q;
	
	//argumentos invalidos
	if(argc < 4){
		b2x_help();
		return 0;
	}
	
	if(!strcmp(argv[B2X_ARG_PLATFORM],"windows")){
		if(fopen(B2X_PE,"r") == NULL){
			printf("erro: arquivo %s faltando\n",B2X_PE);
			return 0;
		}
	}
	if(!strcmp(argv[B2X_ARG_PLATFORM],"linux")){
		if(fopen(B2X_ELF,"r") == NULL){
			printf("erro: arquivo %s faltando\n",B2X_ELF);
			return 0;
		}
	}
	
	script = fopen(argv[B2X_ARG_SCRIPT],"r");
			
	if(script == NULL){
		printf("erro: script nao existe\n");
		return 0;
	}
	
	tam_script = b2x_filesize(argv[B2X_ARG_SCRIPT]);
	
	if(tam_script >= B2X_SIZEMAX){
		printf("erro: arquivo muito grande!!!\n");
		return 0;
	}

	//batch
	if(!strcmp(argv[B2X_ARG_PLATFORM],"windows")){
		tam_execu = b2x_filesize(B2X_PE);
		executavel = fopen(B2X_PE,"rb");	
	}
	
	//bash
	else if(!strcmp(argv[B2X_ARG_PLATFORM],"linux")){
		tam_execu = b2x_filesize(B2X_ELF);
		executavel = fopen(B2X_ELF,"rb");
	}

	//invalido
	else{
		b2x_help();
		return 0;
	}

	saida = fopen(argv[B2X_ARG_OUTPUT],"wb");
	
	//copia o executavel
	while(pos_execu < tam_execu){
		byt = fgetc(executavel);
		byt_back = byt;
		
		pos_back = ftell(executavel);
		
		cont_sepa = 0;
		while(cont_sepa < 5){
			if(byt == B2X_SEPARADOR[cont_sepa]){
				confirm_sepa += 1;
				byt = fgetc(executavel);
			}
			else{
				confirm_sepa = 0;
				cont_sepa = 0;
				byt = byt_back;
				fseek(executavel,pos_back,SEEK_SET);
				break;
			}
			cont_sepa++;
		}
		if(confirm_sepa == 5){
			fputc('k',saida);
			fputc('o',saida);
			fputc('d',saida);
			fputc('o',saida);
			fputc('k',saida);
			
			//leitura do script
			pos_script = 0;
			while(fgets(linha,1000,script) > 0){
				if(b2x_getos() == B2X_LINUX){
					cont_linha = 0;
					while(cont_linha < strlen(linha)){
						if(linha[cont_linha] == 0xa){
							break;
						}
						else if(linha[cont_linha] == '#'){
							break;
						}
						else{
							linha_q = 0;
							fputc(linha[cont_linha],saida);
							fgetc(executavel);
							pos_execu++;
						}
						
						cont_linha++;
					}
					if(linha_q == 0){
						linha_q = 1;
						if(!strcmp(argv[B2X_ARG_PLATFORM],"linux"))
						{
							fputc(';',saida);
						}
						else{
							fputc('&',saida);
						}
						fgetc(executavel);
						pos_execu++;
					}
					
				}
				else if(b2x_getos() == B2X_WINDOWS){
					cont_linha = 0;
					while(cont_linha < strlen(linha)){
						if(linha[cont_linha] == 0xd){
							break;
						}
						else if(linha[0] == 'r' && linha[1] == 'e' && linha[2] == 'm' && linha[3] == ' '){
							break;
						}
						else{
							linha_q = 0;
							fputc(linha[cont_linha],saida);
							fgetc(executavel);
							pos_execu++;
						}
						
						cont_linha++;
					}
					if(linha_q == 0){
						linha_q = 1;
						if(!strcmp(argv[B2X_ARG_PLATFORM],"linux"))
						{
							fputc(';',saida);
						}
						else{
							fputc('&',saida);
						}
						fgetc(executavel);
						pos_execu++;
					}
				}
			}
			fputc('\0',saida);
			fgetc(executavel);
			pos_execu++;
		}
		
		fputc(byt,saida);
		pos_execu++;
	}
	
	fclose(script);
	fclose(saida);
	fclose(executavel);
	
	return 0;
}
