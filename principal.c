#include <stdio.h>
#include <stdlib.h>
#include "tipos.h"
#include "leitura.h"
#include "liberacao_mem.h"

void imprime_constant_utf_value(constant cp) {
	u1* b;
	int mask = 128;

	for (b = cp.u.Utf8.bytes; b < cp.u.Utf8.bytes + cp.u.Utf8.length; b++){
		if ((*b & mask) == 0){ // ou seja, primeiro bit = 0
			printf("%c",*b);
		}
	}

	printf("\n");
}


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
	ClassFile *cf = le_class_file ("teste.class");
	imprime_class_file(cf);
	libera_class_file(cf);
}
