#include <stdio.h>
#include <stdlib.h>
#include "JVIDA_HJRV_view_menu.h"
#include "../../controller/jogo/JVIDA_HJRV_controller_jogo.h"
#include "../utilidades/JVIDA_HJRV_view_utilidades.h"

int mostrar_Menu(void) {
    char entrada[10];
    char *fim;
    int id;
    int valido;
    
    do
    {
        printf("\n[1] - Nova simulacao\n");
        printf("[2] - Continuar simulacao\n");
        printf("[0] - Sair\n");
	
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
            printf("Saindo do programa...\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
            break;
    }

    return (int)id;
}
