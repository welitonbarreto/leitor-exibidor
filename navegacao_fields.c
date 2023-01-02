#include "navegacao_fields.h"




void imprime_descricao_field_flag(u2 access_flags) {
	printf("[");
	int total_flags = 0;
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, FIELD_MASK_ACC_PUBLIC,"public", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, FIELD_MASK_ACC_PRIVATE, "private", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, FIELD_MASK_ACC_PROTECTED, "protected", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, FIELD_MASK_ACC_STATIC, "static", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, FIELD_MASK_ACC_FINAL, "final", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, FIELD_MASK_ACC_VOLATILE, "volatile", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, FIELD_MASK_ACC_TRANSIENT, "transient", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, FIELD_MASK_ACC_SYNTHETIC, "synthetic", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, FIELD_MASK_ACC_ENUM, "enum", total_flags);

	printf("]");
}


void imprime_informacoes_navegacao_field(field_info field, u2 num_field, constant constant_pool[]) {
    imprime_linha();
	printf("\nInformacoes do field\n");
	printf("Name: cp_info #%d ", field.name_index);
	imprime_campo_utf8_entre_colchetes(constant_pool,field.name_index);
	printf("\nDescriptor cp_info: #%d ", field.descriptor_index);
	imprime_campo_utf8_entre_colchetes(constant_pool, field.descriptor_index);
	printf("\nAcess Flags: 0x%04x", field.access_flags);
	imprime_descricao_field_flag(field.access_flags);
	printf("\n");
	imprime_linha();
	printf("\n\n");
}


void imprime_contexto_navegacao_field(field_info field, int num_field, constant constant_pool[]) {
    imprime_contexto_navegacao_fields();

	printf("\t[%d]", num_field);
	imprime_constant_utf_value(constant_pool[field.name_index-1]);
	printf("\n");
    
}


void imprime_acoes_navegacao_field(field_info field, constant constant_pool[]) {
    attribute_info* atributos = field.attributes;
	
	int i;
	for(i = 0; i < field.attributes_count; i++) {
		printf("\t\t(%d) ", i);
		imprime_constant_utf_value(constant_pool[atributos[i].attribute_name_index-1]);
		printf("\n");
	}

	printf("\n\n\n\t\t(-1) Voltar\n");
}



void imprime_acao_navegacao_attribute_from_field() {
	printf("\n\n\n\t\t\t(-1) Voltar\n");
}


void imprime_contexto_navegacao_attribute_from_field(attribute_info atributo, int num_attr, field_info field, int num_field, constant constant_pool[]){
	imprime_contexto_navegacao_field(field, num_field, constant_pool);
	printf("\t\t[%d]", num_attr);
	imprime_constant_utf_value(constant_pool[atributo.attribute_name_index-1]);
	printf("\n");
}


void imprime_specific_info_from_constant_value(attribute_info attr, constant constant_pool[]) {
	printf("Specific Information");
	printf("\n");
	printf("Constant value index: cp_info #%d <", attr.info.ConstantValue.constantvalue_index);

	u1 tag = constant_pool[attr.info.ConstantValue.constantvalue_index-1].tag;
	u2 index = attr.info.ConstantValue.constantvalue_index;

	switch(tag) {
		case CONSTANT_String:
			imprime_constant_string(constant_pool, index);
			break;
		case CONSTANT_Integer:
			imprime_constant_integer(constant_pool, index);
			break;
		case CONSTANT_Float:
			imprime_constant_float(constant_pool, index);
			break;
		case CONSTANT_Long:
			imprime_constant_long(constant_pool, index);
			break;
		case CONSTANT_Double:
			imprime_constant_double(constant_pool, index);
			break;
	}


	printf(">\n");
}



void imprime_informacoes_constant_value(attribute_info attr, constant constant_pool[]) {
	printf("\n");
	imprime_generic_info_from_atribute(attr, constant_pool);
	printf("\n");
	imprime_specific_info_from_constant_value(attr, constant_pool);
	imprime_linha();
	printf("\n\n");
}


void navegacao_attribute_constant_value(attribute_info atributo, int num_attr, field_info field, int num_field, constant constant_pool[]){
	int acao;

	do{
		limpa_tela();
		imprime_contexto_navegacao_attribute_from_field(atributo, num_attr, field, num_field, constant_pool);
		imprime_acao_navegacao_attribute_from_field();
		imprime_informacoes_constant_value(atributo,constant_pool);
		acao = solicita_inteiro();
	}while(acao != -1);
}




void navegacao_attribute_from_field_not_found(attribute_info attr, int num_attr, field_info field, int num_field, constant constant_pool[]){
	int acao;

	do{
		limpa_tela();
		imprime_contexto_navegacao_attribute_from_field(attr, num_attr, field, num_field, constant_pool);
		imprime_acao_navegacao_attribute_from_field();
		imprime_generic_info_from_atribute(attr, constant_pool);
		printf("\n\n");
		acao = solicita_inteiro();
	}while(acao != -1);
}



void navegacao_field(field_info field, int num_field, constant constant_pool[]){
    int acao;

    do {
        limpa_tela();
        imprime_contexto_navegacao_field(field, num_field, constant_pool);
        imprime_acoes_navegacao_field(field, constant_pool);
        imprime_informacoes_navegacao_field(field, num_field, constant_pool);
		
		acao = solicita_inteiro();
		if (acao >= 0 && acao < field.attributes_count) {
			attribute_info atributo = field.attributes[acao];
			u1* name = constant_pool[atributo.attribute_name_index-1].u.Utf8.bytes;
			u2 length = constant_pool[atributo.attribute_name_index-1].u.Utf8.length;
	
			if(nome_u1_igual_string(name,"ConstantValue",length)) {
				navegacao_attribute_constant_value(atributo, acao, field, num_field, constant_pool);			
			} else{
				navegacao_attribute_from_field_not_found(atributo, acao, field, num_field, constant_pool);
			}
		}
		

    } while(acao != -1);

}

void imprime_contexto_navegacao_fields() {
    printf("[4]Fields\n");
}




void imprime_acoes_navegacao_fields(field_info fields[], u2 fields_count, constant constant_pool[]) {
    for(int i = 0;i < fields_count;i++) {
		printf("\t(%d)", i);
		imprime_constant_utf_value(constant_pool[fields[i].name_index-1]);
		printf("\n");
	}

	printf("\n\n\n");
	printf("\t(-1) Voltar\n\n");

}







void navegacao_dos_fields(field_info fields[], u2 fields_count, constant constant_pool[]){
    int acao;

    do {
        limpa_tela();
        imprime_contexto_navegacao_fields();
        imprime_acoes_navegacao_fields(fields, fields_count, constant_pool);

        acao = solicita_inteiro();

        if(acao >= 0 && acao < fields_count) {
			navegacao_field(fields[acao], acao, constant_pool);
		}

    } while(acao != -1);
}