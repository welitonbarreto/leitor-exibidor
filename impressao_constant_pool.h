#ifndef _IMPRESSAO_CONSTANT_POOL__H_
#define _IMPRESSAO_CONSTANT_POOL__H_

#include "tipos.h"
#include <stdio.h>
#include <string.h>
#include "utilitarios.h"


void imprime_constant_utf_value(constant cp);
void imprime_constant_integer(constant constant_pool[], int index);
void imprime_constant_float(constant constant_pool[], int index);
void imprime_constant_string(constant constant_pool[], int index);
void imprime_constant_long(constant constant_pool[], int index);
void imprime_constant_double(constant constant_pool[], int index); 
void imprime_constant_class(constant constant_pool[], int index);
void imprime_valor_constant_pool_tamanho_u4(constant constant_pool[], int posicao);
void imprime_valor_constant_pool_tamanho_u8(constant constant_pool[], int posicao);
void imprime_constant_method_class_name(constant constant_pool[], int posicao);
void imprime_constant_method_name(constant constant_pool[], int posicao);
void imprime_constant_method_descriptor(constant constant_pool[], int posicao);
void imprime_constant_field_class_name(constant constant_pool[], int posicao); 
void imprime_constant_field_name(constant constant_pool[], int posicao);
void imprime_constant_field_descriptor(constant constant_pool[], int posicao);


#endif