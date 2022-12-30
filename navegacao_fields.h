#ifndef _NAVEGACAO_FIELDS_H_
#define _NAVEGACAO_FIELDS_H_

#include "utilitarios.h"
#include "tipos.h"


#define FIELD_MASK_ACC_PUBLIC 0x0001
#define FIELD_MASK_ACC_PRIVATE 0x0002
#define FIELD_MASK_ACC_PROTECTED 0x0004
#define FIELD_MASK_ACC_STATIC 0x0008
#define FIELD_MASK_ACC_FINAL 0x0010
#define FIELD_MASK_ACC_VOLATILE 0x0040
#define FIELD_MASK_ACC_TRANSIENT 0x0080
#define FIELD_MASK_ACC_SYNTHETIC 0x1000
#define FIELD_MASK_ACC_ENUM 0x4000


void navegacao_dos_fields(field_info fields[], u2 fields_count, constant constant_pool[]);
void imprime_contexto_navegacao_fields();




#endif



