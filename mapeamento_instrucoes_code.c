#include "mapeamento_instrucoes_code.h"




void atribui_funcao_a_opcodes(funcao_exibidora* funcao,funcao_exibidora** vetor_funcoes,int lista_opcodes[], int size_lista) {
	for(int i = 0; i < size_lista;i++){
		int opcode = lista_opcodes[i];
		vetor_funcoes[opcode] = funcao;
	}
}


void preenche_instrucoes_sem_operandos(funcao_exibidora** vetor_funcoes){
	int lista_opcodes[150] = {
		BYTECODE_AALOAD,
		BYTECODE_AASTORE,
		BYTECODE_ACONST_NULL,
		BYTECODE_ALOAD_0,
		BYTECODE_ALOAD_1,
		BYTECODE_ALOAD_2,
		BYTECODE_ALOAD_3,
		BYTECODE_ARETURN,
		BYTECODE_ARRAYLENGTH,
		BYTECODE_ASTORE_0,
		BYTECODE_ASTORE_1,
		BYTECODE_ASTORE_2,
		BYTECODE_ASTORE_3,
		BYTECODE_ATHROW,
		BYTECODE_BALOAD,
		BYTECODE_BASTORE,
		BYTECODE_BREAKPOINT,
		BYTECODE_CALOAD,
		BYTECODE_CASTORE,
		BYTECODE_D2F,
		BYTECODE_D2I,
		BYTECODE_D2L,
		BYTECODE_DADD,
		BYTECODE_DALOAD,
		BYTECODE_DASTORE,
		BYTECODE_DCMPG,
		BYTECODE_DCMPL,
		BYTECODE_DCONST_0,
		BYTECODE_DCONST_1,
		BYTECODE_DDIV,
		BYTECODE_DLOAD_0,
		BYTECODE_DLOAD_1,
		BYTECODE_DLOAD_2,
		BYTECODE_DLOAD_3,
		BYTECODE_DMUL,
		BYTECODE_DNEG,
		BYTECODE_DREM,
		BYTECODE_DRETURN,
		BYTECODE_DSTORE_0,
		BYTECODE_DSTORE_1,
		BYTECODE_DSTORE_2,
		BYTECODE_DSTORE_3,
		BYTECODE_DSUB,
		BYTECODE_DUP,
		BYTECODE_DUP_X1,
		BYTECODE_DUP_X2,
		BYTECODE_DUP2,
		BYTECODE_DUP2_X1,
		BYTECODE_DUP2_X2,
		BYTECODE_F2D,
		BYTECODE_F2I,
		BYTECODE_F2L,
		BYTECODE_FADD,
		BYTECODE_FALOAD,
		BYTECODE_FASTORE,
		BYTECODE_FCMPG,
		BYTECODE_FCMPL,
		BYTECODE_FCONST_0,
		BYTECODE_FCONST_1,
		BYTECODE_FCONST_2,
		BYTECODE_FDIV,
		BYTECODE_FLOAD_0,
		BYTECODE_FLOAD_1,
		BYTECODE_FLOAD_2,
		BYTECODE_FLOAD_3,
		BYTECODE_FMUL,
		BYTECODE_FNEG,
		BYTECODE_FREM,
		BYTECODE_FRETURN,
		BYTECODE_FSTORE_0,
		BYTECODE_FSTORE_1,
		BYTECODE_FSTORE_2,
		BYTECODE_FSTORE_3,
		BYTECODE_FSUB,
		BYTECODE_I2B,
		BYTECODE_I2C,
		BYTECODE_I2D,
		BYTECODE_I2F,
		BYTECODE_I2L,
		BYTECODE_I2S,
		BYTECODE_IADD,
		BYTECODE_IALOAD,
		BYTECODE_IAND,
		BYTECODE_IASTORE,
		BYTECODE_ICONST_M1,
		BYTECODE_ICONST_0,
		BYTECODE_ICONST_1,
		BYTECODE_ICONST_2,
		BYTECODE_ICONST_3,
		BYTECODE_ICONST_4,
		BYTECODE_ICONST_5,
		BYTECODE_IDIV,
		BYTECODE_ILOAD_0,
		BYTECODE_ILOAD_1,
		BYTECODE_ILOAD_2,
		BYTECODE_ILOAD_3,
		BYTECODE_IMPDEP1,
		BYTECODE_IMPDEP2,
		BYTECODE_IMUL,
		BYTECODE_INEG,
		BYTECODE_IOR,
		BYTECODE_IREM,
		BYTECODE_IRETURN,
		BYTECODE_ISHL,
		BYTECODE_ISHR,
		BYTECODE_ISTORE_0,
		BYTECODE_ISTORE_1,
		BYTECODE_ISTORE_2,
		BYTECODE_ISTORE_3,
		BYTECODE_ISUB,
		BYTECODE_IUSHR,
		BYTECODE_IXOR,
		BYTECODE_L2D,
		BYTECODE_L2F,
		BYTECODE_L2I,
		BYTECODE_LADD,
		BYTECODE_LALOAD,
		BYTECODE_LAND,
		BYTECODE_LASTORE,
		BYTECODE_LCMP,
		BYTECODE_LCONST_0,
		BYTECODE_LCONST_1,
		BYTECODE_LDIV,
		BYTECODE_LLOAD_0,
		BYTECODE_LLOAD_1,
		BYTECODE_LLOAD_2,
		BYTECODE_LLOAD_3,
		BYTECODE_LMUL,
		BYTECODE_LNEG,
		BYTECODE_LOR,
		BYTECODE_LREM,
		BYTECODE_LRETURN,
		BYTECODE_LSHL,
		BYTECODE_LSHR,
		BYTECODE_LSTORE_0,
		BYTECODE_LSTORE_1,
		BYTECODE_LSTORE_2,
		BYTECODE_LSTORE_3,
		BYTECODE_LSUB,
		BYTECODE_LUSHR,
		BYTECODE_LXOR,
		BYTECODE_MONITORENTER,
		BYTECODE_MONITOREXIT,
		BYTECODE_NOP,
		BYTECODE_POP,
		BYTECODE_POP2,
		BYTECODE_RETURN,
		BYTECODE_SALOAD,
		BYTECODE_SASTORE,
		BYTECODE_SWAP
	};

	atribui_funcao_a_opcodes(imprime_nome_bytecode, vetor_funcoes, lista_opcodes, 150);
}


void preenche_instrucoes_index_local_variable(funcao_exibidora** vetor_funcoes) {

	int lista_opcodes[11] = {
		BYTECODE_ALOAD,
		BYTECODE_ASTORE,
		BYTECODE_DLOAD,
		BYTECODE_DSTORE,
		BYTECODE_FLOAD,
		BYTECODE_FSTORE,
		BYTECODE_ILOAD,
		BYTECODE_ISTORE,
		BYTECODE_LLOAD,
		BYTECODE_LSTORE,
		BYTECODE_RET
	};

	atribui_funcao_a_opcodes(exibidor_index_local_variable, vetor_funcoes, lista_opcodes, 11);
}




void preenche_instrucoes_desvio(funcao_exibidora** vetor_funcoes) {
	int lista_opcodes_branch_2_bytes[18] = {
		BYTECODE_GOTO,
		BYTECODE_IF_ACMPEQ,
		BYTECODE_IF_ACMPNE,
		BYTECODE_IF_ICMPEQ,
		BYTECODE_IF_ICMPGE,
		BYTECODE_IF_ICMPGT,
		BYTECODE_IF_ICMPLE,
		BYTECODE_IF_ICMPLT,
		BYTECODE_IF_ICMPNE,
		BYTECODE_IFEQ,
		BYTECODE_IFGE,
		BYTECODE_IFGT,
		BYTECODE_IFLE,
		BYTECODE_IFLT,
		BYTECODE_IFNE,
		BYTECODE_IFNONNULL,
		BYTECODE_IFNULL,
		BYTECODE_JSR
	};

	int lista_opcodes_branch_4_bytes[2] = {BYTECODE_GOTO_W, BYTECODE_JSR_W};

	atribui_funcao_a_opcodes(exibidor_desvio_branch_2_bytes, vetor_funcoes, lista_opcodes_branch_2_bytes, 18);
	atribui_funcao_a_opcodes(exibidor_desvio_branch_4_bytes, vetor_funcoes, lista_opcodes_branch_4_bytes, 2);
}



void preenche_instrucoes_especificas(funcao_exibidora** vetor_funcoes) {
	vetor_funcoes[BYTECODE_BIPUSH] = exibidor_bipush;
	vetor_funcoes[BYTECODE_SIPUSH] = exibidor_sipush;
	vetor_funcoes[BYTECODE_LDC] = exibidor_ldc;
	vetor_funcoes[BYTECODE_LDC_W] = exibidor_ldc_w;
	vetor_funcoes[BYTECODE_LDC2_W] = exibidor_ldc2_w;
	vetor_funcoes[BYTECODE_NEW] = exibidor_index_do_constant_pool_com_classe;
	vetor_funcoes[BYTECODE_INSTANCEOF] = exibidor_index_do_constant_pool_com_classe;
	vetor_funcoes[BYTECODE_CHECKCAST] = exibidor_index_do_constant_pool_com_classe;

	vetor_funcoes[BYTECODE_INVOKESPECIAL] = exibidor_metodo;
	vetor_funcoes[BYTECODE_INVOKESTATIC] = exibidor_metodo;
	vetor_funcoes[BYTECODE_INVOKEVIRTUAL] = exibidor_metodo;
	vetor_funcoes[BYTECODE_INVOKEDYNAMIC] = exibidor_metodo;
	vetor_funcoes[BYTECODE_INVOKEINTERFACE] = exibidor_metodo;


	vetor_funcoes[BYTECODE_GETFIELD] = exibidor_field;
	vetor_funcoes[BYTECODE_GETSTATIC] = exibidor_field;
	vetor_funcoes[BYTECODE_PUTFIELD] = exibidor_field;
	vetor_funcoes[BYTECODE_PUTSTATIC] = exibidor_field;


	vetor_funcoes[BYTECODE_NEWARRAY] = exibidor_newarray;
	vetor_funcoes[BYTECODE_ANEWARRAY] = exibidor_index_do_constant_pool_com_classe;;
	vetor_funcoes[BYTECODE_MULTIANEWARRAY] = exibidor_multianewarray;

	vetor_funcoes[BYTECODE_WIDE] = imprime_nome_bytecode;
	vetor_funcoes[BYTECODE_IINC] = exibidor_iinc;


	vetor_funcoes[BYTECODE_TABLESWITCH] = exibidor_tableswitch;
	vetor_funcoes[BYTECODE_LOOKUPSWITCH] = exibidor_lookupswitch;

}




void preenche_funcoes_exibidoras(funcao_exibidora** vetor_funcoes) {
	preenche_instrucoes_sem_operandos(vetor_funcoes);
	preenche_instrucoes_index_local_variable(vetor_funcoes);
	preenche_instrucoes_desvio(vetor_funcoes);
	preenche_instrucoes_especificas(vetor_funcoes);


}


funcao_exibidora** gera_vetor_funcoes_exibidoras() {
	
	funcao_exibidora** vetor_funcoes = malloc(sizeof(funcao_exibidora*)*256);

	preenche_funcoes_exibidoras(vetor_funcoes);

	return vetor_funcoes;
}

