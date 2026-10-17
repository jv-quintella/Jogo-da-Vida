//JVIDA_HJRV_View - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <stdio.h>
#include "../../controller/jogo/JVIDA_HJRV_controller_jogo.h"
#include "../utilidades/JVIDA_HJRV_view_utilidades.h"

/*
** Exibe o menu principal do Jogo da Vida e trata a escolha do usuario.
** Parametros:
**      id - escolha do usuario para navegar no menu
*/

int mostrar_Menu(int id) {

    printf("\n[1] - Nova simulacao\n");
    printf("[2] - Continuar simulacao\n");
    printf("[0] - Sair\n");

    //obter_input(&id, sizeof id);

    switch(id) {
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
}
