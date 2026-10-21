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
int mostrar_Menu(void) {
    char entrada[10];
    char *fim;
    int id;
    int valido;
    int opcao;

    switch(opcao)
    {
        case 1: //primeiro menu
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
        
            switch (id) {
                case 1:
                    iniciar_simulacao();
                    break;
                case 2:
                    // Implementar a funcao de continuar simulacao
                    break;
                case 0:
                    printf("\nSaindo do programa...\n");
                    break;
                default:
                    printf("Opcao invalida. Tente novamente.\n");
                    break;
            }
            return (int)id;
            break;
        case 2: //menu interno da simulaçao

            break;
        case 3: //menu de evoluções

            break;
    }
    

}
