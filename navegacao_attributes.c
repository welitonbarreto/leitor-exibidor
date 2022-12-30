#include "navegacao_attributes.h"




void imprime_descricao_attribute_flag(u2 access_flags) {
	printf("[");
	int total_flags = 0;
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, INNER_CLASS_MASK_ACC_PUBLIC, "public", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, INNER_CLASS_MASK_ACC_PRIVATE, "private", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, INNER_CLASS_MASK_ACC_PROTECTED, "protected", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, INNER_CLASS_MASK_ACC_STATIC, "static", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, INNER_CLASS_MASK_ACC_FINAL, "final", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, INNER_CLASS_MASK_ACC_INTERFACE, "interface", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, INNER_CLASS_MASK_ACC_ABSTRACT, "abstract", total_flags);

	printf("]");
}






void imprime_contexto_navegacao_attributo(attribute_info attributo, constant constant_pool[]) {
    imprime_contexto_navegacao_attributes();
    
    printf("\t");
	imprime_constant_utf_value(constant_pool[attributo.attribute_name_index-1]);
	printf("\n");
}


void imprime_acoes_navegacao_attributo() {
    printf(("\n\n\n\t\t[-1]Voltar\n"));
}



void navegacao_attribute_not_unknown(attribute_info atributo, constant constant_pool[]) {
    int acao;

    do {
        limpa_tela();
        imprime_contexto_navegacao_attributo(atributo, constant_pool);
        imprime_acoes_navegacao_attributo();
        imprime_generic_info_from_atribute(atributo, constant_pool);
        printf("\n");

        acao = le_inteiro();


    } while(acao != -1);

} 


void imprime_coluna_titulos_inner_class(){
    printf("||Nr.  ");
    printf("||Inner Class");
    imprime_espacos_vazios(45 - strlen("Inner Class"));
    printf("||Outer Class");
    imprime_espacos_vazios(45 - strlen("Outer Class"));
    printf("||Inner Name");
    imprime_espacos_vazios(45 - strlen("Inner Name"));
    printf("||Acess Flags\n");
}




void imprime_specific_info_inner_class(attribute_info atributo, constant constant_pool[]){
    printf("\nSpecific Info\n");
    imprime_coluna_titulos_inner_class();

    int i;

    for(int i = 0; i < atributo.info.InnerClasses.number_of_classes; i++) {
        class c = atributo.info.InnerClasses.classes[i];
        imprime_numero_em_tabela("Nr.  ", i);
        imprime_class_em_tabela(45, constant_pool, c.inner_class_info_index);
        imprime_class_em_tabela(45, constant_pool, c.outer_class_info_index);
        imprime_utf8_em_tabela(45, constant_pool, c.inner_name_index);
        printf("||0x%04x", c.inner_class_access_flags);
        imprime_descricao_attribute_flag(c.inner_class_access_flags); 
        printf("\n");
    }


}

void imprime_informacaoes_navegacao_inner_class(attribute_info atributo, constant constant_pool[]){
    imprime_generic_info_from_atribute(atributo, constant_pool);
    imprime_specific_info_inner_class(atributo, constant_pool);
    printf("\n");
    imprime_linha();
    printf("\n");
}




void navegacao_inner_classes(attribute_info atributo, constant constant_pool[]) {
    int acao;

    do {
        limpa_tela();
        imprime_contexto_navegacao_attributo(atributo, constant_pool);
        imprime_acoes_navegacao_attributo();
        imprime_informacaoes_navegacao_inner_class(atributo, constant_pool);
        printf("\n");

        acao = le_inteiro();


    } while(acao != -1);

}

void imprime_specific_info_source_file(attribute_info atributo, constant constant_pool[]) {
    printf("\nSpecific Info\n");
    printf("Source file name index: cp_info #%d ", atributo.info.SourceFile.sourcefile_index);
    imprime_campo_utf8_entre_colchetes(constant_pool, atributo.info.SourceFile.sourcefile_index);
}


void imprime_info_source_file(attribute_info atributo, constant constant_pool[]) {
    imprime_generic_info_from_atribute(atributo, constant_pool);
    imprime_specific_info_source_file(atributo, constant_pool);
    printf("\n");
    imprime_linha();
    printf("\n");
}


void navegacao_source_file(attribute_info atributo, constant constant_pool[]) {
    int acao;

    do {
        limpa_tela();
        imprime_contexto_navegacao_attributo(atributo, constant_pool);
        imprime_acoes_navegacao_attributo();
        imprime_info_source_file(atributo, constant_pool);

        acao = le_inteiro();


    } while(acao != -1);

}


void imprime_acoes_navegacao_attributes(attribute_info attributes[], u2 attributes_count, constant constant_pool[]) {
	int i;
	for(i = 0; i < attributes_count; i++) {
		printf("\t[%d] ", i);
		imprime_constant_utf_value(constant_pool[attributes[i].attribute_name_index-1]);
		printf("\n");
	}

	printf("\n\n\n\t[-1] Voltar\n");
}



void imprime_contexto_navegacao_attributes() {
    printf("Attributes\n");
}

void navega_nos_attributes(attribute_info attributes[], u2 attributes_count, constant constant_pool[]) {
    int acao;

    do {
        limpa_tela();
        imprime_contexto_navegacao_attributes();
        imprime_acoes_navegacao_attributes(attributes, attributes_count, constant_pool);
        acao = le_inteiro();

		if (acao >= 0 && acao < attributes_count) {
			attribute_info atributo = attributes[acao];
			u1* name = constant_pool[atributo.attribute_name_index-1].u.Utf8.bytes;
			u2 length = constant_pool[atributo.attribute_name_index-1].u.Utf8.length;
	
			if(nome_u1_igual_string(name,"InnerClasses",length)) {
                navegacao_inner_classes(atributo, constant_pool);
			} else if(nome_u1_igual_string(name,"SourceFile",length)) {
                navegacao_source_file(atributo, constant_pool);		
			} else {
                navegacao_attribute_not_unknown(atributo, constant_pool); 
            }
		}
		
    } while(acao != -1);
}




