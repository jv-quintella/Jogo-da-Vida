#include <stdio.h>
#include <stdlib.h>
#include "JVIDA_HJRV_view_menu.h"
#include "../../controller/jogo/JVIDA_HJRV_controller_jogo.h"
#include "../utilidades/JVIDA_HJRV_view_utilidades.h"
/*
** Exibe o menu principal, le e valida a opcao escolhida.
** Parametros:
**      (nenhum)
** Retorno:
**      a opcao escolhida (0 = sair, 1 = nova simulacao, 2 = continuar);
**      0 tambem em caso de EOF na entrada.
*/
int mostrar_Menu(int opcao) {
    char entrada[10];
    char *fim;
    int id, id2;
    int valido;
    
    switch(opcao){
        case 1:
            do
            {
                printf("\n| MENU\n");
                printf("\n[1] - Nova simulacao\n");
                printf("[2] - Continuar simulacao\n");
                printf("[0] - Sair\n");
                printf("---------------------------\n");
                printf("Digite uma opcao: ");
            
                if (!obter_input(entrada, sizeof entrada)) {
                    return 0;
        		}
            
                id = strtol(entrada, &fim, 10);
            
                valido = (fim != entrada && *fim == '\0' && (id == 0 || id == 1 || id == 2));
            
                if (!valido) {
                    limparTela();
                    printf("Opcao invalida.\n");
                }
            } while (!valido);
        
            return (int)id;
        case 2:
//            do
//            {
                printf("\n| MENU\n");
                printf("\n[1] - Adicionar celula\n");
                printf("[2] - Simular evolucao\n");
                printf("[3] - Limpar mundo\n");
                printf("[0] - Sair\n");
                printf("---------------------------\n");
                printf("Digite uma opcao: ");
            
                if (!obter_input(entrada, sizeof entrada)) {
                    return 0;
        		}
            
                id2 = strtol(entrada, &fim, 10);
            
                valido = (fim != entrada && *fim == '\0' && (id2 == 0 || id2 == 1 || id2 == 2 || id2 == 3));
            
                if (!valido) {
                    return -1;  
                }
//            } while (!valido);
        
            return (int)id2;
    }
}
