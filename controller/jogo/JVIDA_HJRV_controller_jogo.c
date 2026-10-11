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
        int tamanho = obter_tamanho();
        char entrada[10];
        int mostrarvizinho = mostrar_mortos(&mundo, tamanho, entrada);
        //Passa o endereco de memoria (&) da struct para o Model preencher os pontos 
        criar_mundo(&mundo, tamanho);
        imprimir_mundo(mundo.tamanho, &mundo, mostrarvizinho);

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
    mostrarMensagem("Deseja mostrar os vizinhos mortos das celulas? [s/n]:");
    obter_input(entrada, tamanho);
    if(entrada[0] == 's')
    {
        return 1;
    }
    else if(entrada[0] == 'n')
    {
        return 0;
    }
    else
    {
        mostrarMensagem("Opcao invalida");
        return 0;
    }
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
    {

        int temp_alt = obter_input(entrada, tamanho) - 1;
        int temp_lar = obter_input(entrada, tamanho) - 1;

        if(temp_alt < 1 || temp_alt > mundo->tamanho || temp_lar < 1 || temp_lar > mundo->tamanho)
	    {
		    mostrarMensagem("Posicao invalida");
            return;
	    }
	
	    if(mundo->celulas[temp_alt][temp_lar] == 'O')
	    {
	    	mostrarMensagem("Deseja excluir esta celula? [s/n]:");
		    obter_input(entrada, tamanho);

		    if(entrada[0] == 's')
            {
                mostrarMensagem("Celula excluida");
			    mundo->celulas[temp_alt][temp_lar] = '.';
		    }
            else if(entrada[0] == 'n')
            {
                mostrarMensagem("Celula mantida");
            }
            else
            {
                mostrarMensagem("Opcao invalida");
            }
	    }
	    else
	    {
		    mundo->celulas[temp_alt][temp_lar] = 'O';
	    }
    }
}

/*
** Limpa todas as celulas do mundo, preenchendo a matriz com
** celulas mortas e exibindo o mundo atualizado.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      tamanho - parametro recebido pela funcao, atualmente nao utilizado
*/
void limpar_celula(struct Mundo *mundo, int tamanho)
    {
	    int mostrarvizinho = 0;
        memset(mundo->celulas, '.', sizeof(mundo->celulas));	
        imprimir_mundo(mundo->tamanho, mundo, mostrarvizinho);
    }
    
