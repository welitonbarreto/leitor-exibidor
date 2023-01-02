#include "impressao_interfaces.h"



void imprime_acoes_navegacao_interface() {
    printf("\n\n\n\t\t(-1) Voltar\n\n\n");
}

void imprime_informacoes_interface(u2 interface, constant constant_pool[]){
    imprime_linha();
    printf("\nInformacoes da interface\n");
    printf("Interface: cp_info#%d <", interface);
    imprime_constant_class(constant_pool, interface);
    printf(">\n");
    imprime_linha();
}

void imprime_contexto_navegacao_interface(u2 interface, int num_interface, constant constant_pool[]) {
    imprime_contexto_navegacao_nas_interfaces();
    printf("\t[%d]Interface\n", num_interface);
}


void navegacao_interface(u2 interface, int num_interface, constant constant_pool[]){
    int acao;

    do {
        limpa_tela();
        imprime_contexto_navegacao_interface(interface, num_interface, constant_pool);
        imprime_acoes_navegacao_interface();
        imprime_informacoes_interface(interface, constant_pool);
        printf("\n");
        acao = solicita_inteiro();
    } while(acao != -1);
    

}


void imprime_acoes_navegacao_interfaces(u2 interfaces[], u2 interfaces_count, constant constant_pool[]) {    
    int i = 0;

    for(i = 0;i < interfaces_count;i++){
        printf("\t(%d)Interface\n",i);
    }

    printf("\n\n\n\t(-1) Voltar\n\n\n");

}


void imprime_contexto_navegacao_nas_interfaces() {
    printf("[3]Interfaces\n");
}

void navegacao_nas_interfaces(u2 interfaces[], u2 interfaces_count, constant constant_pool[]) {
    int acao;

    do {
        limpa_tela();
        imprime_contexto_navegacao_nas_interfaces();
        imprime_acoes_navegacao_interfaces(interfaces, interfaces_count, constant_pool);
    
        acao = solicita_inteiro();
        
        if(acao >= 0 && acao < interfaces_count) {
			navegacao_interface(interfaces[acao], acao, constant_pool);
	    }
        
    }while(acao != -1);
}