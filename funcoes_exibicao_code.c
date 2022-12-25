#include "funcoes_exibicao_code.h"


char tabela_nomes_instrucoes[256][15] = {"nop","aconst_null","iconst_m1","iconst_0","iconst_1","iconst_2","iconst_3","iconst_4","iconst_5","lconst_0","lconst_1","fconst_0","fconst_1","fconst_2","dconst_0","dconst_1","bipush","sipush","ldc","ldc_w","ldc2_w","iload","lload","fload","dload","aload","iload_0","iload_1","iload_2","iload_3","lload_0","lload_1","lload_2","lload_3","fload_0","fload_1","fload_2","fload_3","dload_0","dload_1","dload_2","dload_3","aload_0","aload_1","aload_2","aload_3","iaload","laload","faload","daload","aaload","baload","caload","saload","istore","lstore","fstore","dstore","astore","istore_0","istore_1","istore_2","istore_3","lstore_0","lstore_1","lstore_2","lstore_3","fstore_0","fstore_1","fstore_2","fstore_3","dstore_0","dstore_1","dstore_2","dstore_3","astore_0","astore_1","astore_2","astore_3","iastore","lastore","fastore","dastore","aastore","bastore","castore","sastore","pop","pop2","dup","dup_x1","dup_x2","dup2","dup2_x1","dup2_x2","swap","iadd","ladd","fadd","dadd","isub","lsub","fsub","dsub","imul","lmul","fmul","dmul","idiv","ldiv","fdiv","ddiv","irem","lrem","frem","drem","ineg","lneg","fneg","dneg","ishl","lshl","ishr","lshr","iushr","lushr","iand","land","ior","lor","ixor","lxor","iinc","i2l","i2f","i2d","l2i","l2f","l2d","f2i","f2l","f2d","d2i","d2l","d2f","i2b","i2c","i2s","lcmp","fcmpl","fcmpg","dcmpl","dcmpg","ifeq","ifne","iflt","ifge","ifgt","ifle","if_icmpeq","if_icmpne","if_icmplt","if_icmpge","if_icmpgt","if_icmple","if_acmpeq","if_acmpne","goto","jsr ","ret ","tableswitch","lookupswitch","ireturn","lreturn","freturn","dreturn","areturn","return","getstatic","putstatic","getfield","putfield","invokevirtual","invokespecial","invokestatic","invokeinterface","invokedynamic","new","newarray","anewarray","arraylength","athrow","checkcast","instanceof","monitorenter","monitorexit","wide","multianewarray","ifnull","ifnonnull","goto_w","jsr_w","breakpoint","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","not-found","impdep1","impdep2"};


int imprime_nome_bytecode(u1* code,int n, constant constant_pool[]){
	printf("%d ",n);
	printf("%s\n",tabela_nomes_instrucoes[code[n]]);
	return n+1;
}


int exibidor_index_local_variable(u1* code, int n, constant constant_pool[]) {
	
	if ((n-1) >= 0 && code[n-1] == BYTECODE_WIDE) {
		int index = concatena_bytes(code[n+1],code[n+2]);
		printf("%d ",n);
		printf("%s %d\n",tabela_nomes_instrucoes[code[n]],index);
		return n+3;
	} else{
		int index = code[n+1];
		printf("%d ",n);
		printf("%s %d\n",tabela_nomes_instrucoes[code[n]],index);
		return n+2;
	}	
}



void imprime_nome_instrucao_e_deslocamento(u1* code, int n, int endereco_relativo){
	int destino = n + endereco_relativo;
	char sinal = endereco_relativo < 0 ? '-': '+';
	
	printf("%d ",n);
	printf("%s %d (%c%d)\n", tabela_nomes_instrucoes[code[n]], destino, sinal, endereco_relativo);

}


int exibidor_desvio_branch_2_bytes(u1* code, int n, constant constant_pool[]){
	u2 aux = concatena_bytes(code[n+1],code[n+2]);
	short endereco_relativo;
	memcpy(&endereco_relativo, &aux, 2);
	imprime_nome_instrucao_e_deslocamento(code, n, endereco_relativo);
	
	return n+3;
}





int exibidor_desvio_branch_4_bytes(u1* code, int n, constant constant_pool[]) {
	u4 aux = concatena_duas_half_words(concatena_bytes(code[n+1], code[n+2]), concatena_bytes(code[n+3], code[n+4]));
	int endereco_relativo;
	memcpy(&endereco_relativo, &aux, 4);
	imprime_nome_instrucao_e_deslocamento(code, n, endereco_relativo);
	return n+5;
}



int exibidor_bipush(u1* code, int n,constant constant_pool[]){	
	signed char valor;
	memcpy (&valor,&code[n+1], 1);

	printf("%d ",n);
	printf("%s %d\n", tabela_nomes_instrucoes[BYTECODE_BIPUSH], valor);
	return n+2;
}


int exibidor_sipush(u1* code, int n, constant constant_pool[]){	
	short valor;
	u2 bytes = concatena_bytes(code[n+1],code[n+2]);
	memcpy (&valor,&bytes, 2);

	printf("%d ",n);
	printf("%s %d\n", tabela_nomes_instrucoes[BYTECODE_SIPUSH], valor);
	return n+3;
}



int exibidor_ldc(u1* code, int n, constant constant_pool[]) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[BYTECODE_LDC],code[n+1]);	
	printf("<");
	imprime_valor_constant_pool_tamanho_u4(constant_pool, code[n+1]);
	printf(">\n");
	return n+2;
}


int exibidor_ldc_w(u1* code, int n, constant constant_pool[]) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[BYTECODE_LDC_W],concatena_bytes(code[n+1],code[n+2]));	
	printf("<");
	imprime_valor_constant_pool_tamanho_u4(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf(">\n");
	return n+3;
}

int exibidor_ldc2_w(u1* code, int n, constant constant_pool[]) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[BYTECODE_LDC2_W],concatena_bytes(code[n+1],code[n+2]));	
	printf("<");
	imprime_valor_constant_pool_tamanho_u8(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf(">\n");
	return n+3;
}

int exibidor_index_do_constant_pool_com_classe(u1* code, int n, constant constant_pool[]) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[code[n]],concatena_bytes(code[n+1],code[n+2]));
	printf("<");
	imprime_constant_class(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf(">\n");
	return n+3;
}




int exibidor_metodo(u1* code, int n, constant constant_pool[]) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[code[n]],concatena_bytes(code[n+1],code[n+2]));
	printf("<");
	imprime_constant_method_class_name(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf(".");
	imprime_constant_method_name(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf(" : ");
	imprime_constant_method_descriptor(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf(">\n");
	return n+3;
}

int exibidor_field(u1* code, int n, constant constant_pool[]) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[code[n]],concatena_bytes(code[n+1],code[n+2]));
	printf("<");
	imprime_constant_field_class_name(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf(".");
	imprime_constant_field_name(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf(" : ");
	imprime_constant_field_descriptor(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf(">\n");
	return n+3;
}

void imprime_type_array(u1 type){
	switch(type) {
		case ARRAY_TYPE_BOOLEAN:
			printf("(boolean)");
			break;
		case ARRAY_TYPE_FLOAT:
			printf("(float)");
			break;
		case ARRAY_TYPE_INT:
			printf("(int)");
			break;
		case ARRAY_TYPE_LONG:
			printf("(long)");
			break;
		case ARRAY_TYPE_DOUBLE:
			printf("(double)");
			break;
		case ARRAY_TYPE_SHORT:
			printf("(short)");
			break;
		case ARRAY_TYPE_CHAR:
			printf("(char)");
			break;
		case ARRAY_TYPE_BYTE:
			printf("(byte)");
			break;
	}
}

int exibidor_newarray(u1* code,int n, constant constant_pool[]) {
	u1 num_type = code[n+1];
	printf("%d ",n);
	printf("%s %d ", tabela_nomes_instrucoes[code[n]], num_type);
	imprime_type_array(num_type);
	printf("\n");
	return n+2;
}



int exibidor_multianewarray(u1* code,int n, constant constant_pool[]) {
	int dimensao = code[n+3];
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[code[n]],concatena_bytes(code[n+1],code[n+2]));
	printf("<");
	imprime_constant_class(constant_pool, concatena_bytes(code[n+1],code[n+2]));
	printf("> dim %d\n", dimensao);
	return n+4;
}


void exibidor_iinc_wide(u1* code, int n) {
	u2 index = concatena_bytes(code[n+1],code[n+2]);
	short inc_short;
	u2 aux = concatena_bytes(code[n+3],code[n+4]);
	memcpy(&inc_short, &aux, 2);

	printf("%d ",n);
	printf("%s %d by %d\n", tabela_nomes_instrucoes[code[n]], index, inc_short);
}

void exibidor_iinc_normal(u1* code,int n) {
	u1 index = code[n+1];
	signed char inc_signed_byte;
	u1 aux = code[n+2];
	memcpy(&inc_signed_byte, &aux, 1);

	printf("%d ",n);
	printf("%s %d by %d\n", tabela_nomes_instrucoes[code[n]], index, inc_signed_byte);
}


int exibidor_iinc(u1* code, int n, constant constant_pool[]) {

	if((n-1) >= 0 && code[n-1] == BYTECODE_WIDE) {
		exibidor_iinc_wide(code, n);
		return n+5;
	} else{
		exibidor_iinc_normal(code, n);
		return n+3;
	}
}



int le_inteiro_from_code(u1* code, int x){

	//printf("%d  esse eh x\n", x);
	int valor = 0;
	u4 aux = concatena_duas_half_words(concatena_bytes(code[x], code[x+1]), concatena_bytes(code[x+2], code[x+3]));
	memcpy(&valor, &aux, 4);
	return valor;
}



void imprime_off_sets_do_tableswitch(u1*code, int posicao_offsets, int low, int high, int inicio_switch){
	int posicao_atual = posicao_offsets;
	int i = 0;
	

	for(i = low; i < high+1; i++) {
		int offset = le_inteiro_from_code(code, posicao_atual);
		char sinal = offset < 0 ? '-': '+';
		printf("%d: %d  (%c%d) \n", i, inicio_switch + offset, sinal, abs(offset));
		posicao_atual = posicao_atual + 4;
	}

}

void imprime_default_do_switch(int padrao, int inicio){
	char sinalSoma = padrao+inicio < 0 ? '-': '+';
	char sinalPadrao = padrao < 0 ? '-': '+';
	printf("default: %c%d (%c%d)\n", sinalSoma, abs(padrao+inicio), sinalPadrao, abs(padrao));
}


int exibidor_tableswitch(u1* code, int n, constant constant_pool[]) {
	int k = 4 - (n % 4);    // numero de bytes  de preenchimento
	int padrao = le_inteiro_from_code(code,n+k);
	int low = le_inteiro_from_code(code,n+k+4);
	
	int high = le_inteiro_from_code(code,n+k+8);
	int inicio_offsets = n+k+12;


	printf("%d ",n);
	printf("%s %d to %d:\n", tabela_nomes_instrucoes[code[n]],low, high);
	imprime_off_sets_do_tableswitch(code, inicio_offsets, low, high, n);
	imprime_default_do_switch(padrao,n);
	return inicio_offsets + (high - low + 1)*4;
}

void imprime_off_sets_do_lookupswitch(u1*code, int posicao_offsets, int quantidade, int inicio_switch){
	int posicao_atual = posicao_offsets;
	int i = 0;

	for(int i = 0;i < quantidade;i++) {
		int match = le_inteiro_from_code(code,posicao_atual);
		int offset = le_inteiro_from_code(code,posicao_atual+4);
		char sinal = offset < 0 ? '-': '+';
		printf("%d: %d  (%c%d) \n", match, inicio_switch + offset, sinal, abs(offset));

		posicao_atual = posicao_atual + 8;
	}
}

int exibidor_lookupswitch(u1* code, int n, constant constant_pool[]) {
	int k = 4 - (n % 4);    // numero de bytes  de preenchimento 
	int padrao = le_inteiro_from_code(code,n+k);
	int num_pares = le_inteiro_from_code(code,n+k+4);
	int inicio_offsets = n+k+8;

	printf("%d ",n);
	printf("%s %d:\n", tabela_nomes_instrucoes[code[n]],num_pares);
	imprime_off_sets_do_lookupswitch(code, inicio_offsets, num_pares, n);
	imprime_default_do_switch(padrao, n);
	return inicio_offsets + num_pares*8;
}






