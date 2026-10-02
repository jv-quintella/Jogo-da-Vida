//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

//verificar obter_input()

#include "JVIDA_HJRV_model_jogo.h"
#include "JVIDA_HJRV_model_struct.h"
#include "JVIDA_HJRV_view_jogo.h"
#include "JVIDA_HJRV_view_menu.h"
#include "JVIDA_HJRV_view_utilidades.h"
#include "JVIDA_HJRV_controller_jogo.h"

void iniciar_simulacao()
    {
        struct Mundo mundo;
        int tamanho = obter_tamanho();
        //Passa o endereco de memoria (&) da struct para o Model preencher os pontos 
        criar_mundo(&mundo, tamanho);
        imprimir_mundo(mundo.tamanho, mundo.celulas);

    }

void primeira_celula(struct Mundo *mundo, int tamanho, char entrada[])
    {	
        int temp_alt = obter_input(entrada, tamanho);	
        int temp_lar = obter_input(entrada, tamanho);	
        int excluir;

        if(temp_alt < 1 || temp_alt > mundo->tamanho || temp_lar < 1 || temp_lar > mundo->tamanho)
	{
		mostrarMensagem("Posicao invalida");
	}
	
	if(mundo->celulas[temp_alt][temp_lar] == 'O')
	{
		mostrarMensagem("Deseja excluir esta celula? [s][n]:");
		excluir = obter_input(entrada, tamanho);

		if(excluir == 's')
        {
			mundo->celulas[temp_alt][temp_lar] = '.';
		}
	}

	else
	{
		//mundo->celula[temp_alt][temp_lar] = função 3; 
	}
}

void mostrar_celula(struct Mundo *mundo, int tamanho)
    {
        int i, j;
        mundo->tamanho = tamanho;
        //inserir entrada no mapa
        for(i = 0; i < tamanho; i++)
            {
                for(j = 0; j < tamanho; j++)
                {
                    mundo->celulas[i][j] = '.';
                }
            }
}
