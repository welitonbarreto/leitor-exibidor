#include "navegacao_methods.h"



void imprime_descricao_method_flags(u2 access_flags) {
	printf("[");
	int total_flags = 0;
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_PUBLIC, "public", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_PRIVATE, "private", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_PROTECTED, "protected", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_STATIC, "static", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_FINAL, "final", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_SYNCHRONIZED, "synchronized", total_flags);
	//total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_BRIDGE, "bridge", total_flags);
	//total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_VARARGS, "varargs", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_NATIVE, "native", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_ABSTRACT, "abstract", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_STRICT, "strictfp", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, METHOD_MASK_ACC_SYNTHETIC, "synthetic", total_flags);




	printf("]");
}












void imprime_instrucoes_bytecodes(u1* code, u4 code_length, constant constant_pool[]){

	int posicao = 0;
	while(posicao <  code_length) {
		funcao_exibidora** vetor_funcoes = gera_vetor_funcoes_exibidoras();	
		funcao_exibidora* funcao = vetor_funcoes[code[posicao]];
		posicao = funcao(code, posicao, constant_pool);
	}

}

void imprime_exception_table_from_method(exception* exception_table, u2 exception_table_length, constant constant_pool[]) {

	printf("||Nr.  ||Start PC||End PC||Handler PC||Catch Type\n");
	
	int i;

	for(i = 0; i < exception_table_length; i++) {
		exception excecao = exception_table[i];

		imprime_numero_em_tabela("Nr.  ", i);
		imprime_numero_em_tabela("Start PC", excecao.start_pc);
		imprime_numero_em_tabela("END PC", excecao.end_pc);
		imprime_numero_em_tabela("HANDLER PC", excecao.handler_pc);
		printf("||cp_info #%d ", excecao.catch_type);
		imprime_constant_class(constant_pool, excecao.catch_type);
	}
	
}

void imprime_contexto_navegacao_code(attribute_info attr_code, u2 num_attr_code, method_info metodo, u2 num_metodo, constant constant_pool[]) {
	imprime_contexto_navegacao_method(metodo, num_metodo, constant_pool);
	printf("\t\t[%d]", num_attr_code);
	imprime_constant_utf_value(constant_pool[attr_code.attribute_name_index-1]);
	printf("\n");

}


void imprime_contexto_navegacao_local_variable_table(attribute_info attr_local_var, u2 num_attr_local_var, attribute_info attr_code, u2 num_attr_code,
												  method_info metodo_pai, u2 num_metodo, constant constant_pool[])
{
	imprime_contexto_navegacao_code(attr_code, num_attr_code, metodo_pai, num_metodo, constant_pool);
	printf("\t\t\t[%d]", num_attr_local_var);
	imprime_constant_utf_value(constant_pool[attr_local_var.attribute_name_index-1]);
	printf("\n");
}

void imprime_acoes_navegacao_local_variable_table() {
	printf("\n\n\n");
	printf("\t\t\t\t(-1) VOLTAR");
	printf("\n\n\n");
}

void imprime_specific_info_from_local_var_table(local_variable local_variable_table[], u2 local_variable_table_length, constant constant_pool[]) {
	
	printf("\nSpecific Info\n");

	printf("||Nr.  ||Start PC||Length||Index||Name                                              ");
	printf("||Descriptor                                                                                          \n");

	int i;

	for(i = 0; i < local_variable_table_length; i++){
		local_variable l = local_variable_table[i];

		imprime_numero_em_tabela("Nr.  ", i);
		imprime_numero_em_tabela("Start PC", l.start_pc);
		imprime_numero_em_tabela("Length", l.length);
		imprime_numero_em_tabela("Index", l.index);
		imprime_utf8_em_tabela(50, constant_pool, l.name_index);
		imprime_utf8_em_tabela(100, constant_pool, l.descriptor_index);
		printf("\n");
	}

	printf("\n");

}

void imprime_informacoes_local_variable(attribute_info attr_local_var, u2 num_attr_code, constant constant_pool[]) {
	printf("\n");
	imprime_linha();
	imprime_generic_info_from_atribute(attr_local_var, constant_pool);
	imprime_linha();
	imprime_specific_info_from_local_var_table(attr_local_var.info.LocalVariableTable.local_variable_table, 
											   attr_local_var.info.LocalVariableTable.local_variable_table_length,
											   constant_pool);
	imprime_linha();
	imprime_linha();
	printf("\n\n");
}

void navegacao_local_variable_table(attribute_info attr_local_var, u2 num_attr_local_var, attribute_info attr_code, u2 num_attr_code,
									 method_info metodo_pai, u2 num_metodo, constant constant_pool[])
{

	int acao;

	do {
		limpa_tela();
		imprime_contexto_navegacao_local_variable_table(attr_local_var, num_attr_local_var,
													 attr_code, num_attr_code,
													 metodo_pai, num_metodo, constant_pool);
		imprime_acoes_navegacao_local_variable_table();	
		imprime_informacoes_local_variable(attr_local_var, num_attr_code, constant_pool) ;

		acao = solicita_inteiro();
	}while (acao != ACAO_VOLTAR);
	

}

void imprime_contexto_navegacao_line_number_table(attribute_info attr_local_var, u2 num_attr_local_var, attribute_info attr_code, u2 num_attr_code,
									 method_info metodo_pai, u2 num_metodo, constant constant_pool[]){

	imprime_contexto_navegacao_local_variable_table(attr_local_var, num_attr_local_var,
													 attr_code, num_attr_code,
													 metodo_pai, num_metodo, constant_pool);
}


void imprime_acoes_navegacao_line_number_table() {
	imprime_acoes_navegacao_local_variable_table();	
}

void imprime_specific_info_from_line_number_table(line_number line_number_table[], u2 length, constant constant_pool[]) {

	printf("\nSpecific Info\n");

	printf("||Nr.  ||Start PC||Line Number\n");

	int i;

	for(i = 0; i < length; i++){
		line_number l = line_number_table[i];

		imprime_numero_em_tabela("Nr.  ", i);
		imprime_numero_em_tabela("Start PC", l.start_pc);
		imprime_numero_em_tabela("Line Number", l.line_number);

		printf("\n");
	}

	printf("\n");
}

void imprime_informacoes_line_number_table(attribute_info attr_line_number_tab, constant constant_pool[]) {
	printf("\n");
	imprime_generic_info_from_atribute(attr_line_number_tab, constant_pool);
	imprime_specific_info_from_line_number_table(attr_line_number_tab.info.LineNumberTable.line_number_table, 
											   attr_line_number_tab.info.LineNumberTable.line_number_table_length,
											   constant_pool);
	imprime_linha();
	printf("\n\n");
}



void navegacao_line_number_table(attribute_info attr_line_number_tab, u2 num_attr_line_number, attribute_info attr_code, u2 num_attr_code,
									 method_info metodo_pai, u2 num_metodo, constant constant_pool[])
{

	int acao;

	do {
		limpa_tela();
		imprime_contexto_navegacao_line_number_table(attr_line_number_tab, num_attr_line_number,
													 attr_code, num_attr_code,
													 metodo_pai, num_metodo, constant_pool);
		imprime_acoes_navegacao_line_number_table();
		imprime_informacoes_line_number_table(attr_line_number_tab, constant_pool);
		//imprime_informacoes_local_variable(attr_local_var, num_attr_code, constant_pool) ;

		acao = solicita_inteiro();
	}while (acao != ACAO_VOLTAR);
	

}

void imprime_misc(attribute_info attr_code) {
	printf("Maximum stack size: %d\n", attr_code.info.Code.max_stack);
	printf("Maximum local variables: %d \n", attr_code.info.Code.max_locals);
	printf("Code length: %d", attr_code.info.Code.code_length);
}

void imprime_specific_info_from_code(attribute_info attr_code, constant constant_pool[], int acao) {
	printf("Specific Info");

	if(acao == ACAO_BYTECODES){
		printf(" - BYTECODE\n");
		imprime_instrucoes_bytecodes(attr_code.info.Code.code, attr_code.info.Code.code_length, constant_pool);
	} else if(acao == ACAO_EXCEPTION_TABLE) {
		printf(" - EXCEPTION TABLE\n");
		imprime_exception_table_from_method(attr_code.info.Code.exception_table, attr_code.info.Code.exception_table_length, constant_pool);		
	} else if(acao == ACAO_MISC) {
		printf(" - MISC\n");
		imprime_misc(attr_code);
	}
	printf("\n");
}


void imprime_informacoes_code(attribute_info attr_code, u2 num_attr_code, constant constant_pool[], int acao) {
	printf("\n");
	imprime_generic_info_from_atribute(attr_code, constant_pool);
	printf("\n");
	imprime_specific_info_from_code(attr_code, constant_pool, acao);
	imprime_linha();
	printf("\n\n");
}


void imprime_acoes_navegacao_code(attribute_info attributes[], u2 attributes_count, constant constant_pool[]) {
	int i = 0;	
	for(int i = 0; i < attributes_count; i++) {
		printf("\t\t\t(%d) ", i);
		imprime_constant_utf_value(constant_pool[attributes[i].attribute_name_index-1]);
		printf("\n");
	}

	printf("\n\n\n");
	printf("\t\t\t(-1) VOLTAR\n");
	printf("\t\t\t(-2) MOSTRAR BYTECODE\n");
	printf("\t\t\t(-3) MOSTRAR EXCEPTION TABLE\n");
	printf("\t\t\t(-4) MOSTRAR MISC\n");
	printf("\n");
}

void navegacao_code(attribute_info attr_code, u2 num_attr_code, method_info metodo_pai, u2 num_metodo, constant constant_pool[]){
	int acao;

	do {
		limpa_tela();
		imprime_contexto_navegacao_code(attr_code, num_attr_code, metodo_pai, num_metodo, constant_pool);
		imprime_acoes_navegacao_code(attr_code.info.Code.attributes, attr_code.info.Code.attributes_count, constant_pool);
		imprime_informacoes_code(attr_code, num_attr_code, constant_pool, acao);
		acao = solicita_inteiro();
		
		if(acao >= 0 && acao < attr_code.info.Code.attributes_count) {
			attribute_info atributo = attr_code.info.Code.attributes[acao];
			u1* name = constant_pool[atributo.attribute_name_index-1].u.Utf8.bytes;
			u2 length = constant_pool[atributo.attribute_name_index-1].u.Utf8.length;
	
			if(nome_u1_igual_string(name,"LocalVariableTable",length)) {
				navegacao_local_variable_table(atributo, acao,
												attr_code, num_attr_code,
												metodo_pai, num_metodo, constant_pool);

			} else if(nome_u1_igual_string(name,"LineNumberTable",length)) {
				navegacao_line_number_table(atributo, acao,
												attr_code, num_attr_code,
												metodo_pai, num_metodo, constant_pool);
							
			}
		}


	}while(acao != ACAO_VOLTAR);
}

void imprime_informacoes_method(method_info method, u2 num_metodo, constant constant_pool[]) {
	printf("\n");
	imprime_linha();
	printf("\nInformações do metodo\n");
	printf("Name: cp_info #%d ", method.name_index);
	imprime_campo_utf8_entre_colchetes(constant_pool,method.name_index);
	printf("\nDescriptor cp_info: #%d ", method.descriptor_index);
	imprime_campo_utf8_entre_colchetes(constant_pool, method.descriptor_index);
	printf("\nAcess Flags: 0x%04x", method.access_flags);
	imprime_descricao_method_flags(method.access_flags);
	printf("\n");
	imprime_linha();
	printf("\n\n");
}

void imprime_acoes_navegacao_method(method_info method, constant constant_pool[]) {
	attribute_info* atributos = method.attributes;
	
	int i;
	for(i = 0; i < method.attributes_count; i++) {
		//u2 name_index = method.attributes[1];
		printf("\t\t(%d)", i);
		imprime_constant_utf_value(constant_pool[atributos[i].attribute_name_index-1]);
		printf("\n");
	}

	printf("\n\n\n\t\t(-1) Voltar\n");
}



void imprime_contexto_navegacao_method(method_info method, u2 num_metodo, constant constant_pool[]) {
	imprime_contexto_navegacao_methods();
	printf("\t[%d]", num_metodo);
	imprime_constant_utf_value(constant_pool[method.name_index-1]);
	printf("\n");
}

void imprime_contexto_navegacao_exceptions(attribute_info attr_exceptions, u2 num_attr, 
											method_info metodo_pai, u2 num_metodo, constant constant_pool[])
{
	imprime_contexto_navegacao_code(attr_exceptions, num_attr, metodo_pai, num_metodo, constant_pool);									
}

void imprime_acoes_navegacao_exceptions() {
	printf("\n\n\n");
	printf("\t\t\t(-1) Voltar\n");
}


void imprime_specific_info_from_exceptions(u2* exception_index_table, u2 length, constant constant_pool[]) {
	
	printf("||Nr.  ||Exception          ||Verbose\n");

	for(int i = 0; i < length; i++) {
		imprime_numero_em_tabela("Nr.  ", i);
		printf("||cp info #%d", exception_index_table[i]);
		imprime_espacos_vazios(10-tamanho_lexicografico_inteiro(exception_index_table[i]));
		printf("||");
		imprime_constant_class(constant_pool, exception_index_table[i]);
		printf("\n");
	}

}

void imprime_informacoes_exceptions(attribute_info attr_except, u2 num_attr_except, constant constant_pool[]) {
	printf("\n");
	imprime_generic_info_from_atribute(attr_except, constant_pool);
	printf("\n");
	imprime_specific_info_from_exceptions(attr_except.info.Exceptions.exception_index_table,
										 attr_except.info.Exceptions.number_of_exceptions, constant_pool);
	imprime_linha();
	printf("\n\n");
}


void navegacao_exceptions(attribute_info attr_exceptions, u2 num_attr, method_info metodo_pai, u2 num_metodo, constant constant_pool[]){
	int acao;

	do {
		limpa_tela();
		imprime_contexto_navegacao_exceptions(attr_exceptions, num_attr, metodo_pai, num_metodo, constant_pool);		
		imprime_acoes_navegacao_exceptions();
		imprime_informacoes_exceptions(attr_exceptions, num_attr, constant_pool);
		acao = solicita_inteiro();
		
	}while(acao != ACAO_VOLTAR);
}

void imprime_contexto_navegacao_not_found_attribute_from_method(attribute_info attr, u2 num_attr,
											  method_info metodo_pai, u2 num_metodo, constant constant_pool[])
{
	imprime_contexto_navegacao_method(metodo_pai, num_metodo, constant_pool);
	printf("\t\t[%d]", num_attr);
	imprime_constant_utf_value(constant_pool[attr.attribute_name_index-1]);
	printf("\n");
}


void navegacao_not_found_attribute_from_method(attribute_info attr, u2 num_attr,
											  method_info metodo_pai, u2 num_metodo, constant constant_pool[]) {
	int acao;

	do {
		limpa_tela();	
		imprime_contexto_navegacao_not_found_attribute_from_method(attr, num_attr, metodo_pai, num_metodo, constant_pool);
		printf("\n\n\n\t\t\t(-1) Voltar\n\n\n");
		imprime_generic_info_from_atribute(attr, constant_pool);
		printf("\n\n");
		acao = solicita_inteiro();
		
	}while(acao != ACAO_VOLTAR);

}

void navegacao_dos_method(method_info method,u2 num_metodo,constant constant_pool[]) {
	int acao;
	
	do {
		limpa_tela();
		imprime_contexto_navegacao_method(method, num_metodo, constant_pool);
		imprime_acoes_navegacao_method(method, constant_pool);	
		imprime_informacoes_method(method, num_metodo, constant_pool);

		acao = solicita_inteiro();

		if (acao >= 0 && acao < method.attributes_count) {
			attribute_info atributo = method.attributes[acao];
			u1* name = constant_pool[atributo.attribute_name_index-1].u.Utf8.bytes;
			u2 length = constant_pool[atributo.attribute_name_index-1].u.Utf8.length;
	
			if(nome_u1_igual_string(name,"Code",length)) {
				navegacao_code(atributo, acao, method, num_metodo, constant_pool);
			} else if(nome_u1_igual_string(name,"Exceptions",length)) {
				navegacao_exceptions(atributo, acao, method, num_metodo, constant_pool);			
			} else{
				navegacao_not_found_attribute_from_method(atributo, acao, method, num_metodo, constant_pool);
			}
		}
		

	}while(acao != -1);
}

void imprime_contexto_navegacao_methods() {
	printf("[5]Methods\n");
}

void imprime_acoes(method_info methods[], u2 methods_count, constant constant_pool[]) {

	for(int i = 0;i < methods_count;i++) {
		printf("\t(%d)", i);
		imprime_constant_utf_value(constant_pool[methods[i].name_index-1]);
		printf("\n");
	}

	printf("\n");
	printf("\t(-1) Voltar\n\n");	
}

void navegacao_dos_methods(method_info methods[], u2 methods_count, constant constant_pool[]) {
	
	int acao;

	do{
		limpa_tela();
		imprime_contexto_navegacao_methods();
		imprime_acoes(methods, methods_count, constant_pool);

		acao = solicita_inteiro();
		
		if(acao >= 0 && acao < methods_count) {
			navegacao_dos_method(methods[acao], acao, constant_pool);
		}

	}while(acao != -1);
}
