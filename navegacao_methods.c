#include "navegacao_methods.h"

u1* get_code_from_method(method_info metodo, constant constant_pool[]) {
	attribute_info* a;

	for (a = metodo.attributes; a < metodo.attributes + metodo.attributes_count;a++) {

		u1* name = constant_pool[a->attribute_name_index-1].u.Utf8.bytes;
		u2 length = constant_pool[a->attribute_name_index-1].u.Utf8.length;
		
		if (nome_u1_igual_string(name,"Code", length)) {
			return a->info.Code.code;
		}
	}

}


u4 get_length_from_method_code(method_info metodo, constant constant_pool[]) {
	attribute_info* a;

	for (a = metodo.attributes; a < metodo.attributes + metodo.attributes_count;a++) {

		u1* name = constant_pool[a->attribute_name_index-1].u.Utf8.bytes;
		u2 length = constant_pool[a->attribute_name_index-1].u.Utf8.length;
		
		if (nome_u1_igual_string(name,"Code", length)) {
			return a->info.Code.code_length;
		}
	}

}



void imprime_code_from_method(method_info metodo, constant constant_pool[]){
	u1* code = get_code_from_method(metodo, constant_pool);
	u4 code_length = get_length_from_method_code(metodo, constant_pool);

	int posicao = 0;
	while(posicao <  code_length) {
		funcao_exibidora** vetor_funcoes = gera_vetor_funcoes_exibidoras();	
		funcao_exibidora* funcao = vetor_funcoes[code[posicao]];
		posicao = funcao(code, posicao, constant_pool);
	}
}












