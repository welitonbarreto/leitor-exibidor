#ifndef _LIBERACAO_MEM_H_
#define _LIBERACAO_MEM_H_


#include "tipos.h"

void libera_attributes (constant* constantPool, attribute_info* attributes, u2 attributes_count);
void libera_fields(constant* constantPool, field_info* fields, u2 length);
void libera_methods(constant* constantPool, method_info* methods, u2 length);
void libera_constant_pool(constant* constant_pool, u2 length);
void libera_class_file(ClassFile* cf);


#endif
