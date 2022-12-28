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



int main() {

	ClassFile *cf = le_class_file ("classes/TesteDeprecated.class");
	//navegacao_nas_interfaces(cf->interfaces, cf->interfaces_count, cf->constant_pool);
	//navegacao_do_constant_pool(cf->constant_pool, cf->constant_pool_count);
	navegacao_dos_methods(cf->methods, cf->methods_count, cf->constant_pool);
	//imprime_code_from_method(metodo, cf->constant_pool);
	//imprime_class_file(cf);
	libera_class_file(cf);
}
