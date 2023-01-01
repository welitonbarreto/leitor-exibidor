#include "principal.h"


void imprime_descricao_class_flags(u2 access_flags) {
	printf("[");
	int total_flags = 0;
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, CLASS_MASK_ACC_PUBLIC, "public", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, CLASS_MASK_ACC_FINAL, "final", total_flags);
	//total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, CLASS_MASK_ACC_SUPER, "super", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, CLASS_MASK_ACC_INTERFACE, "interface", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, CLASS_MASK_ACC_ABSTRACT, "abstract", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, CLASS_MASK_ACC_SYNTHETIC, "synthetic", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, CLASS_MASK_ACC_ANNOTATION, "annotation", total_flags);
	total_flags =  total_flags + imprime_descricao_mascara_se_pertencer_a_flags(access_flags, CLASS_MASK_ACC_ENUM, "enum", total_flags);


	printf("]");
}



void imprime_class_file(ClassFile *cf) {
	printf("Minor_version: %d\n",cf->minor_version);
	printf("Major_version: %d\n",cf->major_version);
	printf("Constant pool count: %d\n",cf->constant_pool_count);
	printf("Access flags: 0x%04x\n",cf->access_flags);
	printf("This _class: %d\n",cf->this_class);
	printf("super: %d\n",cf->super_class);
	printf("interfaces_count: %d\n",cf->interfaces_count);
	printf("fields_count: %d\n",cf->fields_count);
	printf("methods_count: %d\n",cf->methods_count);
	printf("attributes_count: %d\n",cf->attributes_count);
}



void imprime_acoes_general_information(){
	printf("\n\n\n\t(-1) Voltar\n\n");
}


void imprime_general_information(ClassFile *cf) {
	int acao;

	do {
		limpa_tela();
		printf("[1]General Information\n");
		printf("\tMinor version: %d\n",cf->minor_version);
		printf("\tMajor version: %d\n",cf->major_version);
		printf("\tConstant pool count: %d\n",cf->constant_pool_count);
		printf("\tAccess flags: 0x%04x",cf->access_flags);
		imprime_descricao_class_flags(cf->access_flags);
		printf("\n");
		printf("\tThis class: cp_info #%d ",cf->this_class);
		imprime_constant_class(cf->constant_pool,cf->this_class);
		printf("\n");
		printf("\tSuper: cp_info #%d ",cf->super_class);
		imprime_constant_class(cf->constant_pool,cf->super_class);
		printf("\n");
		printf("\tInterfaces count: %d\n",cf->interfaces_count);
		printf("\tFields count: %d\n",cf->fields_count);
		printf("\tMethods count: %d\n",cf->methods_count);
		printf("\tAttributes count: %d\n",cf->attributes_count);

		imprime_acoes_general_information();

		acao = solicita_inteiro();
	
	}while(acao != -1);
}




void imprime_contexto_principal() {
	printf("(1) General information\n");
	printf("(2) Constant Pool\n");
	printf("(3) Interfaces\n");
	printf("(4) Fields\n");
	printf("(5) Methods\n");
	printf("(6) Attributes\n");
}

void imprime_acoes_contexto_principal() {
	printf("\n");
	printf("(-1) Sair\n");
}

int main(int argc, char *argv[ ]) {
	ClassFile *cf = le_class_file (argv[1]);


	if(cf == NULL) {
		printf("Falha na abertura do arquivo\n");
		printf("Verifique se o nome ou caminho do arquivo está correto\n");
		return 0;
	}


	int acao;

	do {
		limpa_tela();
		imprime_contexto_principal();
		imprime_acoes_contexto_principal();
		printf("\n");
		acao = solicita_inteiro();

		switch (acao) {
			case 1:
				imprime_general_information(cf);
				break;
			case 2:
				navegacao_do_constant_pool(cf->constant_pool, cf->constant_pool_count);
				break;

			case 3:
				navegacao_nas_interfaces(cf->interfaces, cf->interfaces_count, cf->constant_pool);
				break;

			case 4:
				navegacao_dos_fields(cf->fields, cf->fields_count, cf->constant_pool);
				break;
			case 5:
				navegacao_dos_methods(cf->methods, cf->methods_count, cf->constant_pool);
				break;

			case 6:
				navega_nos_attributes(cf->attributes, cf->attributes_count, cf->constant_pool);
				break;
		}
	} while(acao != -1);


	libera_class_file(cf);
}
