#ifndef _PRINCIPAL_H_
#define _PRINCIPAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tipos.h"
#include "leitura.h"
#include "liberacao_mem.h"
#include "funcoes_exibicao_code.h"
#include "mapeamento_instrucoes_code.h"
#include "utilitarios.h"
#include "navegacao_methods.h"
#include "impressao_constant_pool.h"
#include "impressao_interfaces.h"
#include "navegacao_attributes.h"
#include "navegacao_fields.h"


#define CLASS_MASK_ACC_PUBLIC 0x0001
#define CLASS_MASK_ACC_FINAL 0x0010
#define CLASS_MASK_ACC_SUPER 0x0020
#define CLASS_MASK_ACC_INTERFACE 0x0200
#define CLASS_MASK_ACC_ABSTRACT 0x0400
#define CLASS_MASK_ACC_SYNTHETIC 0x1000
#define CLASS_MASK_ACC_ANNOTATION 0x2000
#define CLASS_MASK_ACC_ENUM 0x4000


#endif