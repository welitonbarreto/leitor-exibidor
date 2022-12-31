#ifndef _UTILITARIOS_H
#define _UTILITARIOS_H

#include "tipos.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "impressao_constant_pool.h"
#include <ctype.h>


u2 concatena_bytes(u1 msb, u1 lsb);
u4 concatena_duas_half_words(u2 msh, u2 lsh);
u8 concatena_duas_words(u4 msw, u4 lsw);
int nome_u1_igual_string(u1* vetor,char* str,int length);
void limpa_tela();
int le_inteiro();
int menor(int i1, int i2);
void imprime_espacos_vazios(int qtd);
int tamanho_lexicografico_inteiro(int inteiro);
void imprime_linha();
void imprime_numero_em_tabela(char nome_coluna[], int num);
void imprime_utf8_em_tabela(int limite_caracteres, constant constant_pool[], int index);
void imprime_generic_info_from_atribute(attribute_info attr, constant constant_pool[]);
void imprime_class_em_tabela(int limite_caracteres, constant constant_pool[], int index);
int imprime_descricao_mascara_se_pertencer_a_flags(u2 access_flags, u2 mascara, char descricao_mascara[], int flags_ja_encontradas);
int solicita_inteiro();
#endif
