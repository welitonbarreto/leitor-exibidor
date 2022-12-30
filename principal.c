#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "leitura.h"
#include "liberacao_mem.h"
#include "funcoes_exibicao_code.h"
#include "mapeamento_instrucoes_code.h"
#include "utilitarios.h"
#include "navegacao_methods.h"
#include "impressao_interfaces.h"
#include "navegacao_attributes.h"
#include "navegacao_fields.h"




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


void imprime_contexto_principal() {
	printf("[1] General information\n");
	printf("[2] Constant Pool\n");
	printf("[3] Interfaces\n");
	printf("[4] Fields\n");
	printf("[5] Methods\n");
	printf("[6] Attributes\n");
}

int main() {

	ClassFile *cf = le_class_file ("classes/TesteFieldFlags.class");
	int acao;

	do {
		limpa_tela();
		imprime_contexto_principal();
		acao = le_inteiro();

		switch (acao) {
			case(1):
				break;

			case(2):
				navegacao_do_constant_pool(cf->constant_pool, cf->constant_pool_count);
				break;

			case(3):
				break;

			case(4):
				navegacao_dos_fields(cf->fields, cf->fields_count, cf->constant_pool);
				break;
			case(5):
				navegacao_dos_methods(cf->methods, cf->methods_count, cf->constant_pool);
				break;

			case(6):
				navega_nos_attributes(cf->attributes, cf->attributes_count, cf->constant_pool);
				break;
		}
	} while(acao != -1);





	//navegacao_nas_interfaces(cf->interfaces, cf->interfaces_count, cf->constant_pool);
	//
	
	//imprime_code_from_method(metodo, cf->constant_pool);
	//imprime_class_file(cf);
	libera_class_file(cf);
}
