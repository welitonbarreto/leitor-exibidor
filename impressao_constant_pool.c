#include "impressao_constant_pool.h"


void imprime_constant_utf_value(constant cp) {
	u1* b;
	int mask = 128;

	for (b = cp.u.Utf8.bytes; b < cp.u.Utf8.bytes + cp.u.Utf8.length; b++){
		if ((*b & mask) == 0){ // ou seja, primeiro bit = 0
			printf("%c",*b);
		}
	}
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
