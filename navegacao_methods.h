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



u1* get_instrucoes_from_method(method_info metodo, constant constant_pool[]);
void imprime_code_from_method(method_info metodo, constant constant_pool[]);
void navegacao_dos_methods(method_info methods[], u2 methods_count, constant constant_pool[]);
void imprime_contexto_navegacao_methods();
void imprime_contexto_navegacao_method(method_info method, u2 num_metodo, constant constant_pool[]);
#endif