
#ifndef _FUNCOES_EXIBICAO_CODE_H_
#define _FUNCOES_EXIBICAO_CODE_H_

#include "tipos.h"
#include <stdio.h>
#include <stdlib.h>
#include "utilitarios.h"
#include "impressao_constant_pool.h"
#include <string.h>




#define BYTECODE_NOP 0x00
#define BYTECODE_ACONST_NULL 0x01
#define BYTECODE_ICONST_M1 0x02
#define BYTECODE_ICONST_0 0x03
#define BYTECODE_ICONST_1 0x04
#define BYTECODE_ICONST_2 0x05
#define BYTECODE_ICONST_3 0x06
#define BYTECODE_ICONST_4 0x07
#define BYTECODE_ICONST_5 0x08
#define BYTECODE_LCONST_0 0x09
#define BYTECODE_LCONST_1 0x0A
#define BYTECODE_FCONST_0 0x0B
#define BYTECODE_FCONST_1 0x0C
#define BYTECODE_FCONST_2 0x0D
#define BYTECODE_DCONST_0 0x0E
#define BYTECODE_DCONST_1 0x0F
#define BYTECODE_BIPUSH 0x10
#define BYTECODE_SIPUSH 0x11
#define BYTECODE_LDC 0x12
#define BYTECODE_LDC_W 0x13
#define BYTECODE_LDC2_W 0x14
#define BYTECODE_ILOAD 0x15
#define BYTECODE_LLOAD 0x16
#define BYTECODE_FLOAD 0x17
#define BYTECODE_DLOAD 0x18
#define BYTECODE_ALOAD 0x19
#define BYTECODE_ILOAD_0 0x1A
#define BYTECODE_ILOAD_1 0x1B
#define BYTECODE_ILOAD_2 0x1C
#define BYTECODE_ILOAD_3 0x1D
#define BYTECODE_LLOAD_0 0x1E
#define BYTECODE_LLOAD_1 0x1F
#define BYTECODE_LLOAD_2 0x20
#define BYTECODE_LLOAD_3 0x21
#define BYTECODE_FLOAD_0 0x22
#define BYTECODE_FLOAD_1 0x23
#define BYTECODE_FLOAD_2 0x24
#define BYTECODE_FLOAD_3 0x25
#define BYTECODE_DLOAD_0 0x26
#define BYTECODE_DLOAD_1 0x27
#define BYTECODE_DLOAD_2 0x28
#define BYTECODE_DLOAD_3 0x29
#define BYTECODE_ALOAD_0 0x2A
#define BYTECODE_ALOAD_1 0x2B
#define BYTECODE_ALOAD_2 0x2C
#define BYTECODE_ALOAD_3 0x2D
#define BYTECODE_IALOAD 0x2E
#define BYTECODE_LALOAD 0x2F
#define BYTECODE_FALOAD 0x30
#define BYTECODE_DALOAD 0x31
#define BYTECODE_AALOAD 0x32
#define BYTECODE_BALOAD 0x33
#define BYTECODE_CALOAD 0x34
#define BYTECODE_SALOAD 0x35
#define BYTECODE_ISTORE 0x36
#define BYTECODE_LSTORE 0x37
#define BYTECODE_FSTORE 0x38
#define BYTECODE_DSTORE 0x39
#define BYTECODE_ASTORE 0x3A
#define BYTECODE_ISTORE_0 0x3B
#define BYTECODE_ISTORE_1 0x3C
#define BYTECODE_ISTORE_2 0x3D
#define BYTECODE_ISTORE_3 0x3E
#define BYTECODE_LSTORE_0 0x3F
#define BYTECODE_LSTORE_1 0x40
#define BYTECODE_LSTORE_2 0x41
#define BYTECODE_LSTORE_3 0x42
#define BYTECODE_FSTORE_0 0x43
#define BYTECODE_FSTORE_1 0x44
#define BYTECODE_FSTORE_2 0x45
#define BYTECODE_FSTORE_3 0x46
#define BYTECODE_DSTORE_0 0x47
#define BYTECODE_DSTORE_1 0x48
#define BYTECODE_DSTORE_2 0x49
#define BYTECODE_DSTORE_3 0x4A
#define BYTECODE_ASTORE_0 0x4B
#define BYTECODE_ASTORE_1 0x4C
#define BYTECODE_ASTORE_2 0x4D
#define BYTECODE_ASTORE_3 0x4E
#define BYTECODE_IASTORE 0x4F
#define BYTECODE_LASTORE 0x50
#define BYTECODE_FASTORE 0x51
#define BYTECODE_DASTORE 0x52
#define BYTECODE_AASTORE 0x53
#define BYTECODE_BASTORE 0x54
#define BYTECODE_CASTORE 0x55
#define BYTECODE_SASTORE 0x56
#define BYTECODE_POP 0x57
#define BYTECODE_POP2 0x58
#define BYTECODE_DUP 0x59
#define BYTECODE_DUP_X1 0x5A
#define BYTECODE_DUP_X2 0x5B
#define BYTECODE_DUP2 0x5C
#define BYTECODE_DUP2_X1 0x5D
#define BYTECODE_DUP2_X2 0x5E
#define BYTECODE_SWAP 0x5F
#define BYTECODE_IADD 0x60
#define BYTECODE_LADD 0x61
#define BYTECODE_FADD 0x62
#define BYTECODE_DADD 0x63
#define BYTECODE_ISUB 0x64
#define BYTECODE_LSUB 0x65
#define BYTECODE_FSUB 0x66
#define BYTECODE_DSUB 0x67
#define BYTECODE_IMUL 0x68
#define BYTECODE_LMUL 0x69
#define BYTECODE_FMUL 0x6A
#define BYTECODE_DMUL 0x6B
#define BYTECODE_IDIV 0x6C
#define BYTECODE_LDIV 0x6D
#define BYTECODE_FDIV 0x6E
#define BYTECODE_DDIV 0x6F
#define BYTECODE_IREM 0x70
#define BYTECODE_LREM 0x71
#define BYTECODE_FREM 0x72
#define BYTECODE_DREM 0x73
#define BYTECODE_INEG 0x74
#define BYTECODE_LNEG 0x75
#define BYTECODE_FNEG 0x76
#define BYTECODE_DNEG 0x77
#define BYTECODE_ISHL 0x78
#define BYTECODE_LSHL 0x79
#define BYTECODE_ISHR 0x7A
#define BYTECODE_LSHR 0x7B
#define BYTECODE_IUSHR 0x7C
#define BYTECODE_LUSHR 0x7D
#define BYTECODE_IAND 0x7E
#define BYTECODE_LAND 0x7F
#define BYTECODE_IOR 0x80
#define BYTECODE_LOR 0x81
#define BYTECODE_IXOR 0x82
#define BYTECODE_LXOR 0x83
#define BYTECODE_IINC 0x84
#define BYTECODE_I2L 0x85
#define BYTECODE_I2F 0x86
#define BYTECODE_I2D 0x87
#define BYTECODE_L2I 0x88
#define BYTECODE_L2F 0x89
#define BYTECODE_L2D 0x8A
#define BYTECODE_F2I 0x8B
#define BYTECODE_F2L 0x8C
#define BYTECODE_F2D 0x8D
#define BYTECODE_D2I 0x8E
#define BYTECODE_D2L 0x8F
#define BYTECODE_D2F 0x90
#define BYTECODE_I2B 0x91
#define BYTECODE_I2C 0x92
#define BYTECODE_I2S 0x93
#define BYTECODE_LCMP 0x94
#define BYTECODE_FCMPL 0x95
#define BYTECODE_FCMPG 0x96
#define BYTECODE_DCMPL 0x97
#define BYTECODE_DCMPG 0x98
#define BYTECODE_IFEQ 0x99
#define BYTECODE_IFNE 0x9A
#define BYTECODE_IFLT 0x9B
#define BYTECODE_IFGE 0x9C
#define BYTECODE_IFGT 0x9D
#define BYTECODE_IFLE 0x9E
#define BYTECODE_IF_ICMPEQ 0x9F
#define BYTECODE_IF_ICMPNE 0xA0
#define BYTECODE_IF_ICMPLT 0xA1
#define BYTECODE_IF_ICMPGE 0xA2
#define BYTECODE_IF_ICMPGT 0xA3
#define BYTECODE_IF_ICMPLE 0xA4
#define BYTECODE_IF_ACMPEQ 0xA5
#define BYTECODE_IF_ACMPNE 0xA6
#define BYTECODE_GOTO 0xA7
#define BYTECODE_JSR  0xA8
#define BYTECODE_RET  0xA9
#define BYTECODE_TABLESWITCH 0xAA
#define BYTECODE_LOOKUPSWITCH 0xAB
#define BYTECODE_IRETURN 0xAC
#define BYTECODE_LRETURN 0xAD
#define BYTECODE_FRETURN 0xAE
#define BYTECODE_DRETURN 0xAF
#define BYTECODE_ARETURN 0xB0
#define BYTECODE_RETURN 0xB1
#define BYTECODE_GETSTATIC 0xB2
#define BYTECODE_PUTSTATIC 0xB3
#define BYTECODE_GETFIELD 0xB4
#define BYTECODE_PUTFIELD 0xB5
#define BYTECODE_INVOKEVIRTUAL 0xB6
#define BYTECODE_INVOKESPECIAL 0xB7
#define BYTECODE_INVOKESTATIC 0xB8
#define BYTECODE_INVOKEINTERFACE 0xB9
#define BYTECODE_INVOKEDYNAMIC 0xBA
#define BYTECODE_NEW 0xBB
#define BYTECODE_NEWARRAY 0xBC
#define BYTECODE_ANEWARRAY 0xBD
#define BYTECODE_ARRAYLENGTH 0xBE
#define BYTECODE_ATHROW 0xBF
#define BYTECODE_CHECKCAST 0xC0
#define BYTECODE_INSTANCEOF 0xC1
#define BYTECODE_MONITORENTER 0xC2
#define BYTECODE_MONITOREXIT 0xC3
#define BYTECODE_WIDE 0xC4
#define BYTECODE_MULTIANEWARRAY 0xC5
#define BYTECODE_IFNULL 0xC6
#define BYTECODE_IFNONNULL 0xC7
#define BYTECODE_GOTO_W 0xC8
#define BYTECODE_JSR_W 0xC9
#define BYTECODE_BREAKPOINT 0xCA
#define BYTECODE_IMPDEP1 0xFE
#define BYTECODE_IMPDEP2 0xFF


int imprime_nome_bytecode(u1* code,int n, constant constant_pool[]);
int exibidor_index_local_variable(u1* code, int n, constant constant_pool[]);
void preenche_instrucoes_index_local_variable(funcao_exibidora** vetor_funcoes);
void imprime_nome_instrucao_e_deslocamento(u1* code, int n, int endereco_relativo);
int exibidor_desvio_branch_2_bytes(u1* code, int n, constant constant_pool[]);
int exibidor_desvio_branch_4_bytes(u1* code, int n, constant constant_pool[]);

int exibidor_bipush(u1* code, int n,constant constant_pool[]);
int exibidor_sipush(u1* code, int n, constant constant_pool[]);
int exibidor_ldc(u1* code, int n, constant constant_pool[]);
int exibidor_ldc_w(u1* code, int n, constant constant_pool[]);
int exibidor_ldc2_w(u1* code, int n, constant constant_pool[]);
int exibidor_index_do_constant_pool_com_classe(u1* code, int n, constant constant_pool[]);
int exibidor_metodo(u1* code, int n, constant constant_pool[]);
int exibidor_field(u1* code, int n, constant constant_pool[]);
void imprime_type_array(u1 type);
int exibidor_newarray(u1* code,int n, constant constant_pool[]);
int exibidor_multianewarray(u1* code,int n, constant constant_pool[]);
void exibidor_iinc_wide(u1* code, int n);
void exibidor_iinc_normal(u1* code,int n);
int exibidor_iinc(u1* code, int n, constant constant_pool[]);
int le_inteiro_from_code(u1* code, int x);
void imprime_off_sets_do_tableswitch(u1*code, int posicao_offsets, int low, int high, int inicio_switch);
void imprime_default_do_switch(int padrao, int inicio);
int exibidor_tableswitch(u1* code, int n, constant constant_pool[]);
void imprime_off_sets_do_lookupswitch(u1*code, int posicao_offsets, int quantidade, int inicio_switch);
int exibidor_lookupswitch(u1* code, int n, constant constant_pool[]);

#endif