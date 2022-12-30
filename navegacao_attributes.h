#ifndef _NAVEGACAO_ATTRIBUTES_H_
#define _NAVEGACAO_ATTRIBUTES_H_

#include "utilitarios.h"
#include "tipos.h"
#include "impressao_constant_pool.h"


#define INNER_CLASS_MASK_ACC_PUBLIC 0x0001
#define INNER_CLASS_MASK_ACC_PRIVATE 0x0002
#define INNER_CLASS_MASK_ACC_PROTECTED 0x0004
#define INNER_CLASS_MASK_ACC_STATIC 0x0008
#define INNER_CLASS_MASK_ACC_FINAL 0x0010
#define INNER_CLASS_MASK_ACC_INTERFACE 0x0200
#define INNER_CLASS_MASK_ACC_ABSTRACT 0x0400



void navega_nos_attributes(attribute_info attributes[], u2 attributes_count, constant constant_pool[]);
void imprime_contexto_navegacao_attributes() ;

#endif