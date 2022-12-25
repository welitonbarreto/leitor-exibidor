
#ifndef _MAPEAMENTO_INSTRUCOES_CODE_H_
#define _MAPEAMENTO_INSTRUCOES_CODE_H_

#include "tipos.h"
#include "funcoes_exibicao_code.h"


void atribui_funcao_a_opcodes(funcao_exibidora* funcao,funcao_exibidora** vetor_funcoes,int lista_opcodes[], int size_lista);
void preenche_instrucoes_sem_operandos(funcao_exibidora** vetor_funcoes);
void preenche_instrucoes_desvio(funcao_exibidora** vetor_funcoes);
void preenche_instrucoes_especificas(funcao_exibidora** vetor_funcoes);
void preenche_funcoes_exibidoras(funcao_exibidora** vetor_funcoes);
funcao_exibidora** gera_vetor_funcoes_exibidoras();

#endif