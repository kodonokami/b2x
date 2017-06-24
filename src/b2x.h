#ifndef __B2X_H__
#define __B2X_H__

#include <stdio.h>

#define B2X_ARG_PLATFORM 1
#define B2X_ARG_SCRIPT 2
#define B2X_ARG_OUTPUT 3
#define B2X_SIZEMAX 999999
#define B2X_PE "pe.dat"
#define B2X_ELF "elf.dat"
#define B2X_SEPARADOR "kodok"
#define B2X_LINUX 1
#define B2X_WINDOWS 2


long long int b2x_filesize(const char *str){
	long long int tam;
	FILE *arq = fopen(str,"r");
	fseek(arq,0,SEEK_END);
	tam = ftell(arq);
	fclose(arq);
	return tam;
}

void b2x_help(void){
	printf(
	"\ncoder: kodo no kami (discord: kodo#0010)\n"
	"pagina: https://www.facebook.com/forumeof\n"
	"forum: http://eofclub.in/forum\n"
	"discord: https://discordapp.com/invite/cmzeMPv\n\n"
	"sintaxe: <PLATFORM> <SCRIPT> <OUTPUT>\n\n"
	"exemple:\n\n"
	"   b2x.exe windows kodo.bat kodo.exe\n\n"
	"   ./b2x linux kodo.sh kodo.out\n\n"
	);
}

int b2x_getos(void){
	#ifdef __linux__ 
		return 1;
	#else
		return 2;
	#endif
}

#endif
