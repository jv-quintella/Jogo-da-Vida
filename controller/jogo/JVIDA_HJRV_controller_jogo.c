//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <string.h>
#include "JVIDA_HJRV_controller_jogo.h"
#include "../../model/jogo/JVIDA_HJRV_model_jogo.h"
#include "../../view/jogo/JVIDA_HJRV_view_jogo.h"
#include "../../view/menu/JVIDA_HJRV_view_menu.h"
#include "../../view/utilidades/JVIDA_HJRV_view_utilidades.h"

/*
** Inicia a simulacao do Jogo da Vida, obtendo o tamanho do mundo,
** inicializando a matriz e exibindo seu estado inicial.
** Parametros:
**      Nenhum.
*/
void iniciar_simulacao()
{
    struct Mundo mundo;
    int tamanho;
    char entrada[10];
    int mostrarvizinho;
    int valido = 0;

    tamanho = obter_tamanho();

    //Passa o endereco de memoria (&) da struct para o Model preencher os pontos 
    criar_mundo(&mundo, tamanho);

    mostrarvizinho = mostrar_mortos(&mundo, sizeof entrada, entrada);
    primeira_celula(&mundo, sizeof entrada, entrada);
    imprimir_mundo(mundo.tamanho, &mundo, mostrarvizinho);

    do {
        mostrarMensagem("Deseja limpar o mundo? [s/n]: ");

        if (obter_input(entrada, sizeof entrada) == 0) 
        {
            mostrarMensagem("Valor invalido.\n");
            valido = 0;
        }
        else if (entrada[0] == 's' || entrada[0] == 'S') 
        {
            limpar_celula(&mundo);
            valido = 1;
        }
        else if (entrada[0] == 'n' || entrada[0] == 'N') 
        {
            valido = 1;
        }
        else 
        {
            mostrarMensagem("Opcao invalida.\n");
            valido = 0;
        }
    } while (valido == 0);
}

/*
** Permite ao usuario escolher se deseja mostrar os vizinhos mortos das celulas vivas do mundo.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      tamanho - o tamanho utilizado na leitura das entradas
**      entrada - o vetor utilizado para armazenar as entradas do usuario
*/
int mostrar_mortos(struct Mundo *mundo, int tamanho, char entrada[])
{
    int valido = 0;

    do
    {
        mostrarMensagem("Deseja mostrar os vizinhos mortos das celulas? [s/n]: ");
        obter_input(entrada, tamanho);
        if(entrada[0] == 's' || entrada[0] == 'S')
        {
            valido = 1;
            return 1;
        }
        else if(entrada[0] == 'n' || entrada[0] == 'N')
        {
            valido = 1;
            return 0;
        }
        else
        {
            mostrarMensagem("Opcao invalida. Tente novamente.\n\n");
            valido = 0;
        }
    } while (valido == 0);
}


/*
** Permite adicionar ou excluir celulas vivas do mundo, a partir
** das posicoes informadas pelo usuario.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      tamanho - o tamanho utilizado na leitura das entradas
**      entrada - o vetor utilizado para armazenar as entradas do usuario
*/
void primeira_celula(struct Mundo *mundo, int tamanho, char entrada[])
{
    int temp_alt;
    int temp_lar;
    int valido = 0;

    mostrarMensagem("Informe a linha: ");
    temp_alt = obter_posicao(mundo->tamanho, tamanho, entrada);

    mostrarMensagem("Informe a coluna: ");
    temp_lar = obter_posicao(mundo->tamanho, tamanho, entrada);

    //Ajusta as coordenadas para os indices da matriz.
    temp_alt--;
    temp_lar--;

    if (mundo->celulas[temp_alt][temp_lar] == 'O') {
        do {
            mostrarMensagem("Deseja excluir esta celula? [s/n]: ");

            if (obter_input(entrada, tamanho) == 0) 
            {
                mostrarMensagem("Valor invalido.\n");
                valido = 0;
            }
            else if (entrada[0] == 's' || entrada[0] == 'S') 
            {
                mundo->celulas[temp_alt][temp_lar] = '.';
                mostrarMensagem("Celula excluida.\n");
                valido = 1;
            }
            else if (entrada[0] == 'n' || entrada[0] == 'N') 
            {
                mostrarMensagem("Celula mantida.\n");
                valido = 1;
            }
            else 
            {
                mostrarMensagem("Opcao invalida.\n");
                valido = 0;
            }
        } while (valido == 0);
    }
    else 
    {
        mundo->celulas[temp_alt][temp_lar] = 'O';
        mostrarMensagem("Celula adicionada.\n");
    }
}

/*
** Limpa todas as celulas do mundo, preenchendo a matriz com
** celulas mortas e exibindo o mundo atualizado.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
*/
void limpar_celula(struct Mundo *mundo)
    {
        //limpar_tela(); como usa?
	    int mostrarvizinho = 0;
        memset(mundo->celulas, '.', sizeof(mundo->celulas));	
        imprimir_mundo(mundo->tamanho, mundo, mostrarvizinho);
    }
    
