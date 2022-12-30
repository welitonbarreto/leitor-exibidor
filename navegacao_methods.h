#ifndef _NAVEGACAO_METHODS_H_
#define _NAVEGACAO_METHODS_H_

#include "tipos.h"
#include "utilitarios.h"
#include "mapeamento_instrucoes_code.h"
#include "impressao_constant_pool.h"
#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define ACAO_VOLTAR -1
#define ACAO_BYTECODES -2
#define ACAO_EXCEPTION_TABLE -3
#define ACAO_MISC -4



#define METHOD_MASK_ACC_PUBLIC 0x0001
#define METHOD_MASK_ACC_PRIVATE 0x0002
#define METHOD_MASK_ACC_PROTECTED 0x0004
#define METHOD_MASK_ACC_STATIC 0x0008
#define METHOD_MASK_ACC_FINAL 0x0010
#define METHOD_MASK_ACC_SYNCHRONIZED 0x0020
#define METHOD_MASK_ACC_BRIDGE 0x0040
#define METHOD_MASK_ACC_VARARGS 0x0080
#define METHOD_MASK_ACC_NATIVE 0x0100
#define METHOD_MASK_ACC_ABSTRACT 0x0400
#define METHOD_MASK_ACC_STRICT 0x0800
#define METHOD_MASK_ACC_SYNTHETIC 0x1000



void imprime_code_from_method(method_info metodo, constant constant_pool[]);
void navegacao_dos_methods(method_info methods[], u2 methods_count, constant constant_pool[]);
void imprime_contexto_navegacao_methods();
void imprime_contexto_navegacao_method(method_info method, u2 num_metodo, constant constant_pool[]);
#endif