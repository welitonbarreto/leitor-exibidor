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





void imprime_constant_utf_8_info(constant constant_pool[], int posicao) {
	printf("\t\tLength of the bytes array: %d\n", constant_pool[posicao-1].u.Utf8.length);
	printf("\t\tLength of the string: %d\n", constant_pool[posicao-1].u.Utf8.length);
	printf("\t\t String: ");
	imprime_constant_utf_value(constant_pool[posicao-1]);
	printf("\n");
}



void imprime_campo_utf8_entre_colchetes(constant constant_pool[], int index_utf8) {
	constant constant_utf8 = constant_pool[index_utf8-1];
	printf("<");
	imprime_constant_utf_value(constant_utf8);
	printf(">");
}


void imprime_constant_class_info(constant constant_pool[], int posicao){
	int index_utf8 = constant_pool[posicao-1].u.Class.name_index;
	printf("\t\tClass name: cp_info #%d ", index_utf8);
	imprime_campo_utf8_entre_colchetes(constant_pool, index_utf8);
	printf("\n");
} 


void imprime_constant_name_and_type_info(constant constant_pool[], int posicao) {
	int name_index = constant_pool[posicao-1].u.NameAndType.name_index;
	int descriptor_index = constant_pool[posicao-1].u.NameAndType.descriptor_index;
	
	printf("\t\tClass name: cp_info #%d ", name_index);
	imprime_campo_utf8_entre_colchetes(constant_pool, name_index);
	printf("\n");
	printf("\t\tClass name: cp_info #%d ", descriptor_index);
	imprime_campo_utf8_entre_colchetes(constant_pool, descriptor_index);
	printf("\n");
}

void imprime_name_and_type_em_uma_linha(constant constant_pool[], int posicao) {
	int name_index = constant_pool[posicao-1].u.NameAndType.name_index;
	int descriptor_index = constant_pool[posicao-1].u.NameAndType.descriptor_index;
	
	imprime_constant_utf_value(constant_pool[name_index-1]);
	printf(":");
	imprime_constant_utf_value(constant_pool[descriptor_index-1]);
}

void imprime_constant_fieldref_info(constant constant_pool[], int posicao) {
	int index_class = constant_pool[posicao-1].u.Fieldref.class_index;
	int index_name_and_type = constant_pool[posicao-1].u.Fieldref.name_and_type_index;
	
	printf("\t\tName and type: cp_info #%d ", index_class);
	imprime_campo_utf8_entre_colchetes(constant_pool, constant_pool[index_class-1].u.Class.name_index);
	printf("\n");
	printf("\t\tName and type: cp_info #%d <", index_name_and_type);
	imprime_name_and_type_em_uma_linha(constant_pool, index_name_and_type);
	printf(">\n");
}



void imprime_constant_methodref_info(constant constant_pool[], int posicao) {
	int index_class = constant_pool[posicao-1].u.Methodref.class_index;
	int index_name_and_type = constant_pool[posicao-1].u.Methodref.name_and_type_index;
	
	printf("\t\tClass name: cp_info #%d ", index_class);
	imprime_campo_utf8_entre_colchetes(constant_pool, constant_pool[index_class-1].u.Class.name_index);
	printf("\n");
	printf("\t\tName and type: cp_info #%d <", index_name_and_type);
	imprime_name_and_type_em_uma_linha(constant_pool, index_name_and_type);
	printf(">\n");
}

void imprime_constant_interfacemethodref_info(constant constant_pool[], int posicao) {
	int index_class = constant_pool[posicao-1].u.InterfaceMethodRef.class_index;
	int index_name_and_type = constant_pool[posicao-1].u.InterfaceMethodRef.name_and_type_index;
	
	printf("\t\tClass name: cp_info #%d ", index_class);
	imprime_campo_utf8_entre_colchetes(constant_pool, constant_pool[index_class-1].u.Class.name_index);
	printf("\n");
	printf("\t\tName and type: cp_info #%d <", index_name_and_type);
	imprime_name_and_type_em_uma_linha(constant_pool, index_name_and_type);
	printf(">\n");
}

void imprime_constant_long_info(constant constant_pool[], int posicao) {
	u4 low_bytes = constant_pool[posicao-1].u.Long.low_bytes;
	u4 high_bytes = constant_pool[posicao-1].u.Long.high_bytes;
	printf("\t\tHigh Bytes 0x%08x\n", high_bytes);
	printf("\t\tLow Bytes 0x%08x\n", low_bytes);
	printf("\t\tLong: ");
	imprime_constant_long(constant_pool, posicao);
	printf("\n");
}

void imprime_constant_double_info(constant constant_pool[], int posicao) {
	u4 low_bytes = constant_pool[posicao-1].u.Double.low_bytes;
	u4 high_bytes = constant_pool[posicao-1].u.Double.high_bytes;
	printf("\t\tHigh Bytes 0x%08x\n", high_bytes);
	printf("\t\tLow Bytes 0x%08x\n", low_bytes);
	printf("\t\tDouble: ");
	imprime_constant_double(constant_pool, posicao);
	printf("\n");
}

void imprime_constant_integer_info(constant constant_pool[], int posicao) {
	u4 bytes = constant_pool[posicao-1].u.Integer.bytes;
	printf("\t\tBytes 0x%08x\n", bytes);
	printf("\t\tInteger: ");
	imprime_constant_integer(constant_pool, posicao);
	printf("\n");
}


void imprime_constant_float_info(constant constant_pool[], int posicao) {
	u4 bytes = constant_pool[posicao-1].u.Float.bytes;
	printf("\t\tBytes 0x%08x\n", bytes);
	printf("\t\tFloat: ");
	imprime_constant_float(constant_pool, posicao);
	printf("\n");
}


void imprime_constant_string_info(constant constant_pool[], int posicao) {
	int index_utf8 = constant_pool[posicao-1].u.String.string_index;
	printf("\t\tString: cp_info #%d ", index_utf8);
	imprime_campo_utf8_entre_colchetes(constant_pool, index_utf8);
	printf("\n");
}

int eh_posicao_invalida(constant constant_pool[], int posicao){
	u1 tag = constant_pool[posicao-2].tag; 
	if ((tag == CONSTANT_Double) || (tag == CONSTANT_Long)) {
		return 1;
	}

	return 0;
}






void imprime_tela_navegacao_inicial(constant constant_pool[], int constant_pool_count) {
	printf("[2]Constant Pool\n");

	for(int posicao = 1;posicao < constant_pool_count;posicao++) {
		printf("\t(%d)", posicao);
		if(eh_posicao_invalida(constant_pool, posicao)){
			printf("\tlarge numeric continued\n");
			continue;
		}
		switch(constant_pool[posicao-1].tag) {
			case CONSTANT_Class:
				printf("Constant_Class_info\n");
				break; 
			case CONSTANT_Fieldref:
				printf("Constant_Fieldref_info\n");
				break; 
			case CONSTANT_Methodref:
				printf("Constant_Methodref_info\n");
				break;
			case CONSTANT_InterfaceMethodref:
				printf("Constant_InterfaceMethodref_info\n");
				break;
			case CONSTANT_String:
				printf("Constant_String_info\n");
				break;
			case CONSTANT_Integer:
				printf("Constant_Integer_info\n");
				break;
			case CONSTANT_Float:
				printf("Constant_Float_info\n");
				break;
			case CONSTANT_Long:
				printf("Constant_Long_info\n");
				break;
			case CONSTANT_Double:
				printf("Constant_Double_info\n");
				break;
			case CONSTANT_NameAndType:
				printf("Constant_NameAndType_info\n");
				break;	
			case CONSTANT_Utf8:
				printf("Constant_utf_8_info\n");
				break;
			default:
				printf("\n");
				// printf("padrao %d\n",i+1);
				break;
		}
	}

	printf("\n\n\n\t(-1)Voltar\n\n");
}



void imprime_tela_indice_constant_pool(constant constant_pool[],int posicao){
	printf("Constant Pool\n");

	printf("[%d]",posicao);		

		if(eh_posicao_invalida(constant_pool, posicao)){
			printf("\tlarge numeric continued\n");
			return; // Parte a ser modificada
		}

		switch(constant_pool[posicao-1].tag) {
			case CONSTANT_Class:
				printf("\tConstant_Class_info\n");
				imprime_constant_class_info(constant_pool, posicao);
          		break; 
       		case CONSTANT_Fieldref:
				printf("\tConstant_Fieldref_info\n");
				imprime_constant_fieldref_info(constant_pool, posicao);
        		break; 
        	case CONSTANT_Methodref:
				printf("\tConstant_Methodref_info\n");
				imprime_constant_methodref_info(constant_pool, posicao);
        		break;
        	case CONSTANT_InterfaceMethodref:
				printf("\tConstant_InterfaceMethodref_info\n");
				imprime_constant_interfacemethodref_info(constant_pool, posicao);
        		break;
        	case CONSTANT_String:
				printf("\tConstant_String_info\n");
				imprime_constant_string_info(constant_pool, posicao);	
        		break;
        	case CONSTANT_Integer:
				printf("\tConstant_Integer_info\n");
				imprime_constant_integer_info(constant_pool, posicao);
        		break;
        	case CONSTANT_Float:
				printf("\tConstant_Float_info\n");
				imprime_constant_float_info(constant_pool, posicao);
        		break;
        	case CONSTANT_Long:
				printf("\tConstant_Long_info\n");
				imprime_constant_long_info(constant_pool, posicao);
        		break;
        	case CONSTANT_Double:
				printf("\tConstant_Double_info\n");
				imprime_constant_double_info(constant_pool, posicao);
        		break;
        	case CONSTANT_NameAndType:
				printf("\tConstant_NameAndType_info\n");
				imprime_constant_name_and_type_info(constant_pool, posicao);
        		break;	
        	case CONSTANT_Utf8:
				printf("\tConstant_utf_8_info\n");
				imprime_constant_utf_8_info(constant_pool, posicao); 
 				break;
			default:
				printf("\n");
				// printf("padrao %d\n",i+1);
				break;
		}

	printf("\n\n\n\t\t(-1) Voltar\n\n");
}


void navegacao_indice_constant_pool(constant constant_pool[],int posicao) {

	int acao;	
	do {
		limpa_tela();
		imprime_tela_indice_constant_pool(constant_pool, posicao);
		acao = solicita_inteiro();
	} while(acao != -1);
}



void navegacao_do_constant_pool(constant constant_pool[], u2 constant_pool_count) {
	int acao;

	do {
		limpa_tela();
		imprime_tela_navegacao_inicial(constant_pool, constant_pool_count);		
		acao = solicita_inteiro();
		if(acao > 0 && acao < constant_pool_count) {
			navegacao_indice_constant_pool(constant_pool, acao);
		}

	} while(acao != -1);
}

