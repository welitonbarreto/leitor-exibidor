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

	while(scanf("%d", &inteiro) != 1) {
		flush_in();
	}

	flush_in();

	return inteiro;
}


int solicita_inteiro(){
	printf("Digite o numero da acao: \n");

	return le_inteiro();
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
	printf("---------------------------------------------------------------------------------------------");
}



void imprime_numero_em_tabela(char nome_coluna[], int num) {
	printf("||%d", num);
	imprime_espacos_vazios(strlen(nome_coluna)-tamanho_lexicografico_inteiro(num));
}



void imprime_utf8_com_limite_caracteres(int limite_caracteres, constant constant_pool[], int index) {
	constant utf8_constant = constant_pool[index-1];
	u2 tamanho_utf8 = utf8_constant.u.Utf8.length;

	u1* b;
	int mask = 128;

	for (b = utf8_constant.u.Utf8.bytes; b < utf8_constant.u.Utf8.bytes + menor(tamanho_utf8, limite_caracteres-3); b++){
		if ((*b & mask) == 0){ // ou seja, primeiro bit = 0
			printf("%c",*b);
		}	
	}
	

	if(utf8_constant.u.Utf8.length > limite_caracteres-3){
		printf("...");
	} else {
		imprime_espacos_vazios(limite_caracteres - tamanho_utf8);
	}
}


void imprime_class_em_tabela(int limite_caracteres, constant constant_pool[], int index) {
	limite_caracteres = limite_caracteres - (strlen("cp_info # ")+tamanho_lexicografico_inteiro(index));
	printf("||cp_info #%d ", index);
	imprime_utf8_com_limite_caracteres(limite_caracteres, constant_pool, constant_pool[index-1].u.Class.name_index);
}

void imprime_utf8_em_tabela(int limite_caracteres, constant constant_pool[], int index) {
	limite_caracteres = limite_caracteres - (strlen("cp_info # ")+tamanho_lexicografico_inteiro(index));
	printf("||cp_info #%d ", index);

	imprime_utf8_com_limite_caracteres(limite_caracteres, constant_pool, index);

}



void imprime_generic_info_from_atribute(attribute_info attr, constant constant_pool[]) {
	imprime_linha();
	printf("\nGeneric Info\n");
	printf("Attribute name index: cp_info #%d ", attr.attribute_name_index);
	imprime_campo_utf8_entre_colchetes(constant_pool, attr.attribute_name_index);
	printf("\n");
	printf("Atribute length: %d\n", attr.attribute_length);
	imprime_linha();
}


int imprime_descricao_mascara_se_pertencer_a_flags(u2 access_flags, u2 mascara, char descricao_mascara[], int flags_ja_encontradas){
	if((access_flags & mascara) == mascara) {
		printf("%s%s", (flags_ja_encontradas > 0) ? " " :"",descricao_mascara);
		return 1;
	}

	return 0;
}