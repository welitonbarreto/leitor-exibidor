#include "liberacao_mem.h"
#include "tipos.h"
#include <stdlib.h>
#include "leitura.h"


void libera_attributes (constant* constantPool, attribute_info* attributes, u2 attributes_count) {
	attribute_info* a;	

	for (a = attributes; a < attributes + attributes_count;a++) {
		u1* name = constantPool[a->attribute_name_index-1].u.Utf8.bytes;
		u2 length = constantPool[a->attribute_name_index-1].u.Utf8.length;

		if (nome_u1_igual_string(name,"Code",length)) {
			free(a->info.Code.code);
			free(a->info.Code.exception_table);
			libera_attributes(constantPool, a->info.Code.attributes, a->info.Code.attributes_count);
		}
		else if (nome_u1_igual_string(name,"Exceptions",length)) {
			free(a->info.Exceptions.exception_index_table);
		}
		else if (nome_u1_igual_string(name,"InnerClasses",length)) {
			free(a->info.InnerClasses.classes);
		}
		else if (nome_u1_igual_string(name,"LineNumberTable",length)) {
			free(a->info.LineNumberTable.line_number_table);
		}
		else if (nome_u1_igual_string(name,"LocalVariableTable",length)) {
			free(a->info.LocalVariableTable.local_variable_table);
		}
	}

	free(attributes);

}


void libera_fields(constant* constantPool, field_info* fields, u2 length) {
	field_info *f;

	for (f = fields; f < fields + length; f++){
		libera_attributes(constantPool, f->attributes, f->attributes_count);
	}
	
	free(fields);
}

void libera_methods(constant* constantPool, method_info* methods, u2 length) {
	method_info *m;

	for (m = methods; m < methods + length; m++){
		libera_attributes(constantPool, m->attributes, m->attributes_count);
	}

	free(methods);
}

void libera_constant_pool(constant* constant_pool, u2 length) {
	constant *cp;
	for (cp = constant_pool; cp < constant_pool + (length-1); cp++)	{
		if (cp->tag == CONSTANT_Utf8) {
			free(cp->u.Utf8.bytes);
		}	
	}

	free(constant_pool);

}


void libera_class_file(ClassFile* cf) {
    free(cf->interfaces);
	libera_fields(cf->constant_pool, cf->fields, cf->fields_count);
	libera_methods(cf->constant_pool, cf->methods, cf->methods_count);
	libera_attributes(cf->constant_pool, cf->attributes, cf->attributes_count);
	libera_constant_pool(cf->constant_pool, cf->constant_pool_count);
	free(cf);
}