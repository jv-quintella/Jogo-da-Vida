//JVIDA_HJRV_View - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <stdio.h>
#include <stdlib.h>
#include "JVIDA_HJRV_view_menu.h"
#include "../../controller/jogo/JVIDA_HJRV_controller_jogo.h"
#include "../utilidades/JVIDA_HJRV_view_utilidades.h"
/*
** Exibe o menu correspondente ao identificador informado, le e valida a opcao escolhida.
** Menus disponiveis: 1 (principal), 2 (simulacao) e 3 (configuracoes).
** Se a opcao digitada for invalida, exibe uma mensagem de erro e repete a leitura.
** Parametros:
**      opcao - identificador do menu a ser exibido (1 = principal, 2 = simulacao, 3 = configuracoes)
** Retorno:
**      a opcao escolhida dentro do menu exibido (0 sempre significa sair ou voltar);
**      0 tambem em caso de EOF na entrada; -1 se o identificador do menu for desconhecido.
*/
int mostrar_Menu(int opcao) {
    char entrada[10];
    char *fim;
    long id;
    int maximo;
    int valido;

    do
    {
        switch(opcao){
            case 1:
                printf("\n| MENU\n");
                printf("\n[1] - Nova simulacao\n");
                printf("[2] - Continuar simulacao\n");
                printf("[0] - Sair\n");
                maximo = 2;
                break;
            case 2:
                printf("\n| MENU DA SIMULACAO\n");
                printf("\n[1] - Adicionar/excluir celulas\n");
                printf("[2] - Simular evolucao\n");
                printf("[3] - Limpar mundo\n");
                printf("[4] - Configuracoes\n");
                printf("[0] - Voltar\n");
                maximo = 4;
                break;
            case 3:
                printf("\n| CONFIGURACOES\n");
                printf("\n[1] - Quantidade de geracoes\n");
                printf("[2] - Velocidade (geracoes por tela)\n");
                printf("[3] - Vizinhas-mortas (sim/nao)\n");
                printf("[0] - Voltar\n");
                maximo = 3;
                break;
            default:
                return -1;
        }
        printf("---------------------------\n");
        printf("Digite uma opcao: ");

        if (!obter_input(entrada, sizeof entrada)) {
            return 0;
        }

        id = strtol(entrada, &fim, 10);

        valido = (fim != entrada && *fim == '\0' && id >= 0 && id <= maximo);

        if (!valido) {
            if (opcao == 1) {
                limparTela();
            }
            printf("\nOpcao invalida. Digite um numero de 0 a %d.\n", maximo);
        }
    } while (!valido);

    return (int)id;
}
