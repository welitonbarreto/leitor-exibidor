#ifndef _NAVEGACAO_METHODS_H_
#define _NAVEGACAO_METHODS_H_

#include "tipos.h"
#include "utilitarios.h"
#include "mapeamento_instrucoes_code.h"

u1* get_code_from_method(method_info metodo, constant constant_pool[]);
u4 get_length_from_method_code(method_info metodo, constant constant_pool[]);
void imprime_code_from_method(method_info metodo, constant constant_pool[]);

#endif