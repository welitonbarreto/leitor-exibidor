#include "impressao_interfaces.h"

















void navegacao_nas_interfaces(u2 interfaces[], u2 interfaces_count, constant constant_pool[]) {
    int posicao;
	scanf("%d", &posicao);


    int class_index = interfaces[posicao];
    
    printf("Interfaces: cp_info#%d <", class_index);
    imprime_constant_class(constant_pool,class_index);
    printf(">\n");


}