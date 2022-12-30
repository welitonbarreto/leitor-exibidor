#ifndef _NAVEGACAO_ATTRIBUTES_H_
#define _NAVEGACAO_ATTRIBUTES_H_

#include "utilitarios.h"
#include "tipos.h"
#include "impressao_constant_pool.h"

void navega_nos_attributes(attribute_info attributes[], u2 attributes_count, constant constant_pool[]);
void imprime_contexto_navegacao_attributes() ;

#endif