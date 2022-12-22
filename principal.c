#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "leitura.h"
#include "liberacao_mem.h"
#include "globais.h"

typedef int funcao_exibidora(u1* code,int n,int wide);
constant* constantPool;


void imprime_constant_utf_value(constant cp) {
	u1* b;
	int mask = 128;

	for (b = cp.u.Utf8.bytes; b < cp.u.Utf8.bytes + cp.u.Utf8.length; b++){
		if ((*b & mask) == 0){ // ou seja, primeiro bit = 0
			printf("%c",*b);
		}
	}
}


u2 concatena_bytes(u1 msb, u1 lsb) {
	u2 result = msb;
	result = result << 8 | lsb;
	return result;
}

u8 concatena_duas_words(u4 msw, u4 lsw) {
	u8 result = msw;
	result = result << 32 | lsw;
	return result;
}






void imprime_class_file(ClassFile *cf) {
	printf("minor_version: %d\n",cf->minor_version);
	printf("major_version: %d\n",cf->major_version);
	printf("constant_pool_count: %d\n",cf->constant_pool_count);
	printf("access_flags: 0x%04x\n",cf->access_flags);
	printf("this_class: %d\n",cf->this_class);
	printf("super: %d\n",cf->super_class);
	printf("interfaces_count: %d\n",cf->interfaces_count);
	printf("fields_count: %d\n",cf->fields_count);
	printf("methods_count: %d\n",cf->methods_count);
	printf("attributes_count: %d\n",cf->attributes_count);
}


void imprime_constant_integer(constant constant_pool[], int index) {
	int valor;
	memcpy (&valor,&constant_pool[index-1].u.Integer.bytes, 4);

	printf("%d", valor);
}

void imprime_constant_float(constant constant_pool[], int index) {
	float valor;
	memcpy (&valor,&constant_pool[index-1].u.Float.bytes, 4);

	printf("%.4f", valor);
}

void imprime_constant_string(constant constant_pool[], int index) {
	int string_index = constant_pool[index-1].u.String.string_index;
	imprime_constant_utf_value(constant_pool[string_index-1]);
}

void imprime_constant_long(constant constant_pool[], int index) {
	long valor;
	u8 double_word = concatena_duas_words(constant_pool[index-1].u.Long.high_bytes, constant_pool[index-1].u.Long.low_bytes); 
	memcpy (&valor, &double_word, 8);

	printf("%ld", valor);
}

void imprime_constant_double(constant constant_pool[], int index) {
	double valor;

	u8 double_word = concatena_duas_words(constant_pool[index-1].u.Double.high_bytes, constant_pool[index-1].u.Double.low_bytes);
	memcpy (&valor, &double_word, 8);

	printf("%.4f", valor);
}


void imprime_constant_class(constant constant_pool[], int index) {
	if (index == 0) {
		printf("java/lang/Object");
	} else{
		int name_index = constant_pool[index-1].u.Class.name_index;
		imprime_constant_utf_value(constant_pool[name_index-1]);
	}
}

void imprime_valor_constant_pool_tamanho_u4(constant constant_pool[], int posicao) {

	if (constant_pool[posicao-1].tag == CONSTANT_Integer) {
		imprime_constant_integer(constant_pool, posicao);
	} else if  (constant_pool[posicao-1].tag == CONSTANT_Float) {
		imprime_constant_float(constant_pool, posicao);
	} else if  (constant_pool[posicao-1].tag == CONSTANT_String) {
		imprime_constant_string(constant_pool, posicao);
	}
}

void imprime_valor_constant_pool_tamanho_u8(constant constant_pool[], int posicao) {
	if (constant_pool[posicao-1].tag == CONSTANT_Long) {
		imprime_constant_long(constant_pool, posicao);
	} else if (constant_pool[posicao-1].tag == CONSTANT_Double) {
		imprime_constant_double(constant_pool, posicao);
	}

}


void imprime_constant_method_class_name(constant constant_pool[], int posicao) {
	imprime_constant_class(constant_pool, constant_pool[posicao-1].u.Methodref.class_index);
}

void imprime_constant_method_name(constant constant_pool[], int posicao) {
	int name_and_type_index = constant_pool[posicao-1].u.Methodref.name_and_type_index;
	int name_index = constant_pool[name_and_type_index-1].u.NameAndType.name_index;
	
	imprime_constant_utf_value(constant_pool[name_index-1]);
}

void imprime_constant_method_descriptor(constant constant_pool[], int posicao){
	int name_and_type_index = constant_pool[posicao-1].u.Methodref.name_and_type_index;
	int descriptor_index = constant_pool[name_and_type_index-1].u.NameAndType.descriptor_index;

	imprime_constant_utf_value(constant_pool[descriptor_index-1]);
}


void imprime_constant_field_class_name(constant constant_pool[], int posicao) {
	imprime_constant_class(constant_pool, constant_pool[posicao-1].u.Fieldref.class_index);
}

void imprime_constant_field_name(constant constant_pool[], int posicao) {
	int name_and_type_index = constant_pool[posicao-1].u.Fieldref.name_and_type_index;
	int name_index = constant_pool[name_and_type_index-1].u.NameAndType.name_index;
	
	imprime_constant_utf_value(constant_pool[name_index-1]);
}

void imprime_constant_field_descriptor(constant constant_pool[], int posicao){
	int name_and_type_index = constant_pool[posicao-1].u.Fieldref.name_and_type_index;
	int descriptor_index = constant_pool[name_and_type_index-1].u.NameAndType.descriptor_index;

	imprime_constant_utf_value(constant_pool[descriptor_index-1]);
}




u1* get_code(method_info metodo, constant constant_pool[]) {
	attribute_info* a;

	for (a = metodo.attributes; a < metodo.attributes + metodo.attributes_count;a++) {

		u1* name = constant_pool[a->attribute_name_index-1].u.Utf8.bytes;
		u2 length = constant_pool[a->attribute_name_index-1].u.Utf8.length;
		
		if (nome_u1_igual_string(name,"Code", length)) {
			return a->info.Code.code;
		}
	}

}


void atribui_funcao_a_opcodes(funcao_exibidora* funcao,funcao_exibidora** vetor_funcoes,int lista_opcodes[], int size_lista) {
	for(int i = 0; i < size_lista;i++){
		int opcode = lista_opcodes[i];
		vetor_funcoes[opcode] = funcao;
	}
}


int imprime_nome_bytecode(u1* code,int n,int wide){
	printf("%d ",n);
	printf("%s\n",tabela_nomes_instrucoes[code[n]]);
	return n+1;
}


void preenche_instrucoes_sem_operandos(funcao_exibidora** vetor_funcoes){
	int lista_opcodes[150] = {
		BYTECODE_AALOAD,
		BYTECODE_AASTORE,
		BYTECODE_ACONST_NULL,
		BYTECODE_ALOAD_0,
		BYTECODE_ALOAD_1,
		BYTECODE_ALOAD_2,
		BYTECODE_ALOAD_3,
		BYTECODE_ARETURN,
		BYTECODE_ARRAYLENGTH,
		BYTECODE_ASTORE_0,
		BYTECODE_ASTORE_1,
		BYTECODE_ASTORE_2,
		BYTECODE_ASTORE_3,
		BYTECODE_ATHROW,
		BYTECODE_BALOAD,
		BYTECODE_BASTORE,
		BYTECODE_BREAKPOINT,
		BYTECODE_CALOAD,
		BYTECODE_CASTORE,
		BYTECODE_D2F,
		BYTECODE_D2I,
		BYTECODE_D2L,
		BYTECODE_DADD,
		BYTECODE_DALOAD,
		BYTECODE_DASTORE,
		BYTECODE_DCMPG,
		BYTECODE_DCMPL,
		BYTECODE_DCONST_0,
		BYTECODE_DCONST_1,
		BYTECODE_DDIV,
		BYTECODE_DLOAD_0,
		BYTECODE_DLOAD_1,
		BYTECODE_DLOAD_2,
		BYTECODE_DLOAD_3,
		BYTECODE_DMUL,
		BYTECODE_DNEG,
		BYTECODE_DREM,
		BYTECODE_DRETURN,
		BYTECODE_DSTORE_0,
		BYTECODE_DSTORE_1,
		BYTECODE_DSTORE_2,
		BYTECODE_DSTORE_3,
		BYTECODE_DSUB,
		BYTECODE_DUP,
		BYTECODE_DUP_X1,
		BYTECODE_DUP_X2,
		BYTECODE_DUP2,
		BYTECODE_DUP2_X1,
		BYTECODE_DUP2_X2,
		BYTECODE_F2D,
		BYTECODE_F2I,
		BYTECODE_F2L,
		BYTECODE_FADD,
		BYTECODE_FALOAD,
		BYTECODE_FASTORE,
		BYTECODE_FCMPG,
		BYTECODE_FCMPL,
		BYTECODE_FCONST_0,
		BYTECODE_FCONST_1,
		BYTECODE_FCONST_2,
		BYTECODE_FDIV,
		BYTECODE_FLOAD_0,
		BYTECODE_FLOAD_1,
		BYTECODE_FLOAD_2,
		BYTECODE_FLOAD_3,
		BYTECODE_FMUL,
		BYTECODE_FNEG,
		BYTECODE_FREM,
		BYTECODE_FRETURN,
		BYTECODE_FSTORE_0,
		BYTECODE_FSTORE_1,
		BYTECODE_FSTORE_2,
		BYTECODE_FSTORE_3,
		BYTECODE_FSUB,
		BYTECODE_I2B,
		BYTECODE_I2C,
		BYTECODE_I2D,
		BYTECODE_I2F,
		BYTECODE_I2L,
		BYTECODE_I2S,
		BYTECODE_IADD,
		BYTECODE_IALOAD,
		BYTECODE_IAND,
		BYTECODE_IASTORE,
		BYTECODE_ICONST_M1,
		BYTECODE_ICONST_0,
		BYTECODE_ICONST_1,
		BYTECODE_ICONST_2,
		BYTECODE_ICONST_3,
		BYTECODE_ICONST_4,
		BYTECODE_ICONST_5,
		BYTECODE_IDIV,
		BYTECODE_ILOAD_0,
		BYTECODE_ILOAD_1,
		BYTECODE_ILOAD_2,
		BYTECODE_ILOAD_3,
		BYTECODE_IMPDEP1,
		BYTECODE_IMPDEP2,
		BYTECODE_IMUL,
		BYTECODE_INEG,
		BYTECODE_IOR,
		BYTECODE_IREM,
		BYTECODE_IRETURN,
		BYTECODE_ISHL,
		BYTECODE_ISHR,
		BYTECODE_ISTORE_0,
		BYTECODE_ISTORE_1,
		BYTECODE_ISTORE_2,
		BYTECODE_ISTORE_3,
		BYTECODE_ISUB,
		BYTECODE_IUSHR,
		BYTECODE_IXOR,
		BYTECODE_L2D,
		BYTECODE_L2F,
		BYTECODE_L2I,
		BYTECODE_LADD,
		BYTECODE_LALOAD,
		BYTECODE_LAND,
		BYTECODE_LASTORE,
		BYTECODE_LCMP,
		BYTECODE_LCONST_0,
		BYTECODE_LCONST_1,
		BYTECODE_LDIV,
		BYTECODE_LLOAD_0,
		BYTECODE_LLOAD_1,
		BYTECODE_LLOAD_2,
		BYTECODE_LLOAD_3,
		BYTECODE_LMUL,
		BYTECODE_LNEG,
		BYTECODE_LOR,
		BYTECODE_LREM,
		BYTECODE_LRETURN,
		BYTECODE_LSHL,
		BYTECODE_LSHR,
		BYTECODE_LSTORE_0,
		BYTECODE_LSTORE_1,
		BYTECODE_LSTORE_2,
		BYTECODE_LSTORE_3,
		BYTECODE_LSUB,
		BYTECODE_LUSHR,
		BYTECODE_LXOR,
		BYTECODE_MONITORENTER,
		BYTECODE_MONITOREXIT,
		BYTECODE_NOP,
		BYTECODE_POP,
		BYTECODE_POP2,
		BYTECODE_RETURN,
		BYTECODE_SALOAD,
		BYTECODE_SASTORE,
		BYTECODE_SWAP
	};

	atribui_funcao_a_opcodes(imprime_nome_bytecode, vetor_funcoes, lista_opcodes, 150);
}

int exibidor_index_local_variable(u1* code, int n, int wide) {
	int index = code[n+1];
	
	if (wide) {
		index = concatena_bytes(code[n+1],code[n+2]);
	}

	printf("%d ",n);
	printf("%s %d\n",tabela_nomes_instrucoes[code[n]],index);

	return n+3;
}

void preenche_instrucoes_index_local_variable(funcao_exibidora** vetor_funcoes) {

	int lista_opcodes[11] = {
		BYTECODE_ALOAD,
		BYTECODE_ASTORE,
		BYTECODE_DLOAD,
		BYTECODE_DSTORE,
		BYTECODE_FLOAD,
		BYTECODE_FSTORE,
		BYTECODE_ILOAD,
		BYTECODE_ISTORE,
		BYTECODE_LLOAD,
		BYTECODE_LSTORE,
		BYTECODE_RET
	};

	atribui_funcao_a_opcodes(exibidor_index_local_variable, vetor_funcoes, lista_opcodes, 11);
}

int exibidor_desvio(u1* code, int n, int wide){
	u2 endereco_relativo_bytes = concatena_bytes(code[n+1],code[n+2]);
	short endereco_relativo;
	memcpy(&endereco_relativo, &endereco_relativo_bytes, 2);
	
	int destino = n + endereco_relativo;

	char sinal = endereco_relativo < 0 ? '-': '+';
	printf("%d ",n);
	printf("%s %d (%c%d)\n", tabela_nomes_instrucoes[code[n]], destino, sinal, endereco_relativo);

	return n+3;
}

void preenche_instrucoes_desvio(funcao_exibidora** vetor_funcoes) {
	int lista_opcodes[18] = {
		BYTECODE_GOTO,
		BYTECODE_IF_ACMPEQ,
		BYTECODE_IF_ACMPNE,
		BYTECODE_IF_ICMPEQ,
		BYTECODE_IF_ICMPGE,
		BYTECODE_IF_ICMPGT,
		BYTECODE_IF_ICMPLE,
		BYTECODE_IF_ICMPLT,
		BYTECODE_IF_ICMPNE,
		BYTECODE_IFEQ,
		BYTECODE_IFGE,
		BYTECODE_IFGT,
		BYTECODE_IFLE,
		BYTECODE_IFLT,
		BYTECODE_IFNE,
		BYTECODE_IFNONNULL,
		BYTECODE_IFNULL,
		BYTECODE_JSR
	};

	atribui_funcao_a_opcodes(exibidor_desvio, vetor_funcoes, lista_opcodes, 18);

}


int exibidor_bipush(u1* code, int n, int wide){	
	signed char valor;
	memcpy (&valor,&code[n+1], 1);

	printf("%d ",n);
	printf("%s %d\n", tabela_nomes_instrucoes[BYTECODE_BIPUSH], valor);
	return n+2;
}


int exibidor_sipush(u1* code, int n, int wide){	
	short valor;
	u2 bytes = concatena_bytes(code[n+1],code[n+2]);
	memcpy (&valor,&bytes, 2);

	printf("%d ",n);
	printf("%s %d\n", tabela_nomes_instrucoes[BYTECODE_SIPUSH], valor);
	return n+3;
}



int exibidor_ldc(u1* code, int n, int wide) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[BYTECODE_LDC],code[n+1]);	
	printf("<");
	imprime_valor_constant_pool_tamanho_u4(constantPool, code[n+1]);
	printf(">\n");
	return n+2;
}


int exibidor_ldc_w(u1* code, int n, int wide) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[BYTECODE_LDC_W],concatena_bytes(code[n+1],code[n+2]));	
	printf("<");
	imprime_valor_constant_pool_tamanho_u4(constantPool, concatena_bytes(code[n+1],code[n+2]));
	printf(">\n");
	return n+3;
}

int exibidor_ldc2_w(u1* code, int n, int wide) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[BYTECODE_LDC2_W],concatena_bytes(code[n+1],code[n+2]));	
	printf("<");
	imprime_valor_constant_pool_tamanho_u8(constantPool, concatena_bytes(code[n+1],code[n+2]));
	printf(">\n");
	return n+3;
}

int exibidor_index_do_constant_pool_com_classe(u1* code, int n, int wide) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[code[n]],concatena_bytes(code[n+1],code[n+2]));
	printf("<");
	imprime_constant_class(constantPool, concatena_bytes(code[n+1],code[n+2]));
	printf(">\n");
	return n+3;
}

int exibidor_metodo(u1* code, int n, int wide) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[code[n]],concatena_bytes(code[n+1],code[n+2]));
	printf("<");
	imprime_constant_method_class_name(constantPool, concatena_bytes(code[n+1],code[n+2]));
	printf(".");
	imprime_constant_method_name(constantPool, concatena_bytes(code[n+1],code[n+2]));
	printf(" : ");
	imprime_constant_method_descriptor(constantPool, concatena_bytes(code[n+1],code[n+2]));
	printf(">\n");
	return n+3;
}

int exibidor_field(u1* code, int n, int wide) {
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[code[n]],concatena_bytes(code[n+1],code[n+2]));
	printf("<");
	imprime_constant_field_class_name(constantPool, concatena_bytes(code[n+1],code[n+2]));
	printf(".");
	imprime_constant_field_name(constantPool, concatena_bytes(code[n+1],code[n+2]));
	printf(" : ");
	imprime_constant_field_descriptor(constantPool, concatena_bytes(code[n+1],code[n+2]));
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

int exibidor_newarray(u1* code,int n, int wide) {
	u1 num_type = code[n+1];
	printf("%d ",n);
	printf("%s %d ", tabela_nomes_instrucoes[code[n]], num_type);
	imprime_type_array(num_type);
	printf("\n");
	return n+2;
}





int exibidor_multianewarray(u1* code,int n, int wide) {
	int dimensao = code[n+3];
	printf("%d ",n);
	printf("%s #%d ", tabela_nomes_instrucoes[code[n]],concatena_bytes(code[n+1],code[n+2]));
	printf("<");
	imprime_constant_class(constantPool, concatena_bytes(code[n+1],code[n+2]));
	printf("> dim %d\n", dimensao);
	return n+4;
}



void preenche_instrucoes_especificas(funcao_exibidora** vetor_funcoes) {
	vetor_funcoes[BYTECODE_BIPUSH] = exibidor_bipush;
	vetor_funcoes[BYTECODE_SIPUSH] = exibidor_sipush;
	vetor_funcoes[BYTECODE_LDC] = exibidor_ldc;
	vetor_funcoes[BYTECODE_LDC_W] = exibidor_ldc_w;
	vetor_funcoes[BYTECODE_LDC2_W] = exibidor_ldc2_w;
	vetor_funcoes[BYTECODE_NEW] = exibidor_index_do_constant_pool_com_classe;
	vetor_funcoes[BYTECODE_INSTANCEOF] = exibidor_index_do_constant_pool_com_classe;

	vetor_funcoes[BYTECODE_INVOKESPECIAL] = exibidor_metodo;
	vetor_funcoes[BYTECODE_INVOKESTATIC] = exibidor_metodo;
	vetor_funcoes[BYTECODE_INVOKEVIRTUAL] = exibidor_metodo;

	vetor_funcoes[BYTECODE_GETFIELD] = exibidor_field;
	vetor_funcoes[BYTECODE_GETSTATIC] = exibidor_field;
	vetor_funcoes[BYTECODE_PUTFIELD] = exibidor_field;
	vetor_funcoes[BYTECODE_PUTSTATIC] = exibidor_field;


	vetor_funcoes[BYTECODE_NEWARRAY] = exibidor_newarray;
	vetor_funcoes[BYTECODE_ANEWARRAY] = exibidor_index_do_constant_pool_com_classe;;
	vetor_funcoes[BYTECODE_MULTIANEWARRAY] = exibidor_multianewarray;

}




void preenche_funcoes_exibidoras(funcao_exibidora** vetor_funcoes) {
	preenche_instrucoes_sem_operandos(vetor_funcoes);
	preenche_instrucoes_index_local_variable(vetor_funcoes);
	preenche_instrucoes_desvio(vetor_funcoes);
	preenche_instrucoes_especificas(vetor_funcoes);


}


funcao_exibidora** gera_vetor_funcoes_exibidoras() {
	
	funcao_exibidora** vetor_funcoes = malloc(sizeof(funcao_exibidora*)*256);

	preenche_funcoes_exibidoras(vetor_funcoes);



	return vetor_funcoes;
}



int main() {

	ClassFile *cf = le_class_file ("classes/tiposLongDouble.class");

	method_info* array_metodos = cf->methods;
	method_info metodo = array_metodos[3];
	u1* code = get_code(metodo,cf->constant_pool);
	constantPool = cf->constant_pool;

	int pos_acessada = 0;
	funcao_exibidora** vetor_funcoes = gera_vetor_funcoes_exibidoras();	
	funcao_exibidora* funcao = vetor_funcoes[code[pos_acessada]];

	funcao(code,pos_acessada,0);

	//imprime_class_file(cf);
	libera_class_file(cf);
}
