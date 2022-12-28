#include "utilitarios.h"

u2 concatena_bytes(u1 msb, u1 lsb) {
	u2 result = msb;
	result = result << 8 | lsb;
	return result;
}


u4 concatena_duas_half_words(u2 msh, u2 lsh) {
	u4 result = msh;
	result = result << 16 | lsh;
	return result;

}

u8 concatena_duas_words(u4 msw, u4 lsw) {
	u8 result = msw;
	result = result << 32 | lsw;
	return result;
}


int nome_u1_igual_string(u1* vetor,char* str,int length) {
	for(int i = 0;i < length;i++){
		if (vetor[i] != str[i]){
			return 0;
		}
	}

	return 1;
}


void limpa_tela() {
	#ifdef __linux__ 
		system("clear");
	#elif _WIN32
		system("cls");
	#else

	#endif
}


void flush_in() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}


int le_inteiro() {
	int inteiro;

	scanf("%d", &inteiro);
	flush_in();

	return inteiro;
}


int menor(int i1, int i2) {
	if(i1 <= i2) {
		return i1;
	}

	return i2;
}



void imprime_espacos_vazios(int qtd) {
	for(int i = 0; i < qtd;i++){
		printf(" ");
	}
}



int tamanho_lexicografico_inteiro(int inteiro) {
	char buffer_str[10];
	sprintf(buffer_str,"%d", inteiro);

	return strlen(buffer_str);
}

void imprime_linha() {
	printf("----------------------------------------------------------------------------");
}
