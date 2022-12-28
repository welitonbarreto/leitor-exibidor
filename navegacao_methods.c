#include "navegacao_methods.h"


void imprime_numero_em_tabela(char nome_coluna[], int num) {
	printf("||%d", num);
	imprime_espacos_vazios(strlen(nome_coluna)-tamanho_lexicografico_inteiro(num));
}

void imprime_utf8_em_tabela(int limite_caracteres, constant constant_pool[], int index) {
	constant utf8_constant = constant_pool[index-1];
	u2 tamanho_utf8 = utf8_constant.u.Utf8.length;

	limite_caracteres = limite_caracteres - (strlen("cp_info # ")+tamanho_lexicografico_inteiro(index));
	printf("||cp_info #%d ", index);
	
	u1* b;
	int mask = 128;

	for (b = utf8_constant.u.Utf8.bytes; b < utf8_constant.u.Utf8.bytes + menor(tamanho_utf8, limite_caracteres-3); b++){
		if ((*b & mask) == 0){ // ou seja, primeiro bit = 0
			printf("%c",*b);
		}	
	}
	
	if(utf8_constant.u.Utf8.length >= limite_caracteres-3){
		printf("...");
	} else {
		imprime_espacos_vazios(limite_caracteres - tamanho_utf8);
	}
}

exception* get_exception_table_from_method_code(method_info metodo, constant constant_pool[]) {
	attribute_info* a;

	for (a = metodo.attributes; a < metodo.attributes + metodo.attributes_count;a++) {

		u1* name = constant_pool[a->attribute_name_index-1].u.Utf8.bytes;
		u2 length = constant_pool[a->attribute_name_index-1].u.Utf8.length;
		
		if (nome_u1_igual_string(name,"Code", length)) {
			return a->info.Code.exception_table;
		}
	}
}

u4 get_quantidade_instrucoes(method_info metodo, constant constant_pool[]) {
	attribute_info* a;

	for (a = metodo.attributes; a < metodo.attributes + metodo.attributes_count;a++) {

		u1* name = constant_pool[a->attribute_name_index-1].u.Utf8.bytes;
		u2 length = constant_pool[a->attribute_name_index-1].u.Utf8.length;
		
		if (nome_u1_igual_string(name,"Code", length)) {
			return a->info.Code.code_length;
		}
	}

}

attribute_info get_attribute_info_from_method(method_info metodo, constant constant_pool[], char nome_attributo[]) {
	attribute_info* a;

	for (a = metodo.attributes; a < metodo.attributes + metodo.attributes_count;a++) {

		u1* name = constant_pool[a->attribute_name_index-1].u.Utf8.bytes;
		u2 length = constant_pool[a->attribute_name_index-1].u.Utf8.length;
		
		if (nome_u1_igual_string(name, nome_attributo, length)) {
			return *a;
		}
	}


}

void imprime_instrucoes_bytecodes(u1* code, u4 code_length, constant constant_pool[]){

	int posicao = 0;
	while(posicao <  code_length) {
		funcao_exibidora** vetor_funcoes = gera_vetor_funcoes_exibidoras();	
		funcao_exibidora* funcao = vetor_funcoes[code[posicao]];
		posicao = funcao(code, posicao, constant_pool);
	}

	printf("\n\n");
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
		printf("\n");
	}
	
}

void imprime_contexto_navegacao_code(attribute_info attr_code, u2 num_attr_code, method_info metodo, u2 num_metodo, constant constant_pool[]) {
	imprime_contexto_navegacao_method(metodo, num_metodo, constant_pool);
	printf("\t\t ");
	imprime_constant_utf_value(constant_pool[attr_code.attribute_name_index-1]);
	printf("\n");

}

void imprime_generic_info_from_atribute(attribute_info attr, constant constant_pool[]) {
	printf("\nGeneric Info\n");
	printf("Attribute name index: cp_info #%d ", attr.attribute_name_index);
	imprime_campo_utf8_entre_colchetes(constant_pool, attr.attribute_name_index);
	printf("\n");
	printf("Atribute length: %d\n", attr.attribute_length);

}

void imprime_contexto_navegacao_local_variable_table(attribute_info attr_local_var, u2 num_attr_local_var, attribute_info attr_code, u2 num_attr_code,
												  method_info metodo_pai, u2 num_metodo, constant constant_pool[])
{
	imprime_contexto_navegacao_code(attr_code, num_attr_code, metodo_pai, num_metodo, constant_pool);
	printf("\t\t\t");
	imprime_constant_utf_value(constant_pool[attr_local_var.attribute_name_index-1]);
	printf("\n");
}

void imprime_acoes_navegacao_local_variable_table() {
	printf("\n\n\n");
	printf("\t\t\t\t[-1] VOLTAR");
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
	printf("\n");
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

		acao = le_inteiro();
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
	imprime_linha();
	imprime_generic_info_from_atribute(attr_line_number_tab, constant_pool);
	
	imprime_linha();
	imprime_specific_info_from_line_number_table(attr_line_number_tab.info.LineNumberTable.line_number_table, 
											   attr_line_number_tab.info.LineNumberTable.line_number_table_length,
											   constant_pool);
	imprime_linha();
	printf("\n");
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

		acao = le_inteiro();
	}while (acao != ACAO_VOLTAR);
	

}

void imprime_misc(attribute_info attr_code) {
	printf("Maximum stack size: %d\n", attr_code.info.Code.max_stack);
	printf("Maximum local variables: %d \n", attr_code.info.Code.max_locals);
	printf("Code length: %d\n", attr_code.info.Code.code_length);
}

void imprime_specific_info_from_code(attribute_info attr_code, constant constant_pool[], int acao) {
	printf("\nSpecific Info");

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

	printf("\n\n");
}


void imprime_informacoes_code(attribute_info attr_code, u2 num_attr_code, constant constant_pool[], int acao) {
	printf("\n");
	imprime_linha();
	imprime_generic_info_from_atribute(attr_code, constant_pool);
	
	imprime_linha();
	imprime_specific_info_from_code(attr_code, constant_pool, acao);
	imprime_linha();
	printf("\n");
}


void imprime_acoes_navegacao_code(attribute_info attributes[], u2 attributes_count, constant constant_pool[]) {
	int i = 0;	
	for(int i = 0; i < attributes_count; i++) {
		printf("\t\t\t[%d] ", i);
		imprime_constant_utf_value(constant_pool[attributes[i].attribute_name_index-1]);
		printf("\n");
	}

	printf("\n\n\n");
	printf("\t\t\t[-1] VOLTAR\n");
	printf("\t\t\t[-2] MOSTRAR BYTECODE\n");
	printf("\t\t\t[-3] MOSTRAR EXCEPTION TABLE\n");
	printf("\t\t\t[-4] MOSTRAR MISC\n");
	printf("\n");
}

void navegacao_code(attribute_info attr_code, u2 num_attr_code, method_info metodo_pai, u2 num_metodo, constant constant_pool[]){
	int acao;

	do {
		limpa_tela();
		imprime_contexto_navegacao_code(attr_code, num_attr_code, metodo_pai, num_metodo, constant_pool);
		imprime_acoes_navegacao_code(attr_code.info.Code.attributes, attr_code.info.Code.attributes_count, constant_pool);
		imprime_informacoes_code(attr_code, num_attr_code, constant_pool, acao);
		printf("Insira um valor válido\n");
		acao = le_inteiro();
		
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
	printf("\nAcess Flags: 0x%04x\n", method.access_flags);
	imprime_linha();
	printf("\n\n\n");
}

void imprime_acoes_navegacao_method(method_info method, constant constant_pool[]) {
	attribute_info* atributos = method.attributes;
	
	int i;
	for(i = 0; i < method.attributes_count; i++) {
		//u2 name_index = method.attributes[1];
		printf("\t\t[%d] ", i);
		imprime_constant_utf_value(constant_pool[atributos[i].attribute_name_index-1]);
		printf("\n");
	}

	printf("\n\n\n\t\t[-1] Voltar\n");
}



void imprime_contexto_navegacao_method(method_info method, u2 num_metodo, constant constant_pool[]) {
	imprime_contexto_navegacao_methods();
	//printf("\t[%d]", num_metodo);
	printf("\t");
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
	printf("\t\t\t[-1] VOLTAR\n");
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
	imprime_linha();
	imprime_generic_info_from_atribute(attr_except, constant_pool);
	
	imprime_linha();
	printf("\n");
	imprime_specific_info_from_exceptions(attr_except.info.Exceptions.exception_index_table,
										 attr_except.info.Exceptions.number_of_exceptions, constant_pool);
	imprime_linha();
	printf("\n");
}


void navegacao_exceptions(attribute_info attr_exceptions, u2 num_attr, method_info metodo_pai, u2 num_metodo, constant constant_pool[]){
	int acao;

	do {
		limpa_tela();
		imprime_contexto_navegacao_exceptions(attr_exceptions, num_attr, metodo_pai, num_metodo, constant_pool);		
		imprime_acoes_navegacao_exceptions();
		imprime_informacoes_exceptions(attr_exceptions, num_attr, constant_pool);
		printf("Insira um valor válido\n");
		acao = le_inteiro();
		
	}while(acao != ACAO_VOLTAR);
}

void imprime_contexto_navegacao_attribute_from_method_not_found(attribute_info attr, u2 num_attr,
											  method_info metodo_pai, u2 num_metodo, constant constant_pool[])
{
	imprime_contexto_navegacao_method(metodo_pai, num_metodo, constant_pool);
	printf("\t\t");
	imprime_constant_utf_value(constant_pool[attr.attribute_name_index-1]);
	printf("\n");
}


void navegacao_attribute_from_method_not_found(attribute_info attr, u2 num_attr,
											  method_info metodo_pai, u2 num_metodo, constant constant_pool[]) {
	int acao;

	do {
		limpa_tela();	
		imprime_contexto_navegacao_attribute_from_method_not_found(attr, num_attr, metodo_pai, num_metodo, constant_pool);
		printf("\n\n\n\t\t[-1] Voltar\n");
		printf("Insira um valor válido\n");
		acao = le_inteiro();
		
	}while(acao != ACAO_VOLTAR);

}

void navegacao_dos_method(method_info method,u2 num_metodo,constant constant_pool[]) {
	int acao;
	
	do {
		limpa_tela();
		imprime_contexto_navegacao_method(method, num_metodo, constant_pool);
		imprime_acoes_navegacao_method(method, constant_pool);	
		imprime_informacoes_method(method, num_metodo, constant_pool);

		acao = le_inteiro();

		if (acao >= 0 && acao < method.attributes_count) {
			attribute_info atributo = method.attributes[acao];
			u1* name = constant_pool[atributo.attribute_name_index-1].u.Utf8.bytes;
			u2 length = constant_pool[atributo.attribute_name_index-1].u.Utf8.length;
	
			if(nome_u1_igual_string(name,"Code",length)) {
				navegacao_code(atributo, acao, method, num_metodo, constant_pool);
			} else if(nome_u1_igual_string(name,"Exceptions",length)) {
				navegacao_exceptions(atributo, acao, method, num_metodo, constant_pool);			
			} else{
				navegacao_attribute_from_method_not_found(atributo, acao, method, num_metodo, constant_pool);
			}
		}
		

	}while(acao != -1);
}

void imprime_contexto_navegacao_methods() {
	printf("Methods\n");
}

void imprime_acoes(method_info methods[], u2 methods_count, constant constant_pool[]) {

	for(int i = 0;i < methods_count;i++) {
		printf("\t[%d]", i);
		imprime_constant_utf_value(constant_pool[methods[i].name_index-1]);
		printf("\n");
	}

	printf("\n");
	printf("\t[-1] Sair\n");	
}

void navegacao_dos_methods(method_info methods[], u2 methods_count, constant constant_pool[]) {
	
	int acao;

	do{
		limpa_tela();
		imprime_contexto_navegacao_methods();
		imprime_acoes(methods, methods_count, constant_pool);

		acao = le_inteiro();
		
		if(acao >= 0 && acao < methods_count) {
			navegacao_dos_method(methods[acao], acao, constant_pool);
		}

	}while(acao != -1);
}










