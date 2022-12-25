#include "utilitarios.h"

u2 concatena_bytes(u1 msb, u1 lsb) {
	u2 result = msb;
	result = result << 8 | lsb;
	return result;
}


u4 concatena_duas_half_words(u2 msh, u2 lsh) {
	u4 result = msh;
	result = result << 16 | lsh;
	return result;

}

u8 concatena_duas_words(u4 msw, u4 lsw) {
	u8 result = msw;
	result = result << 32 | lsw;
	return result;
}


int nome_u1_igual_string(u1* vetor,char* str,int length) {
	for(int i = 0;i < length;i++){
		if (vetor[i] != str[i]){
			return 0;
		}
	}

	return 1;
}


