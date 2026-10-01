//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, JoÃ£o Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <stdio.h>
#include "JVIDA_HJRV_Model.h"
#include "JVIDA_HJRV_view.h"

void iniciar_simulacao()
    {
        struct Mundo mundo;
        int tamanho = obter_tamanho();
        //Passa o endereco de memoria (&) da struct para o Model preencher os pontos 
        criar_mundo(&mundo, tamanho);
        imprimir_mundo(mundo.tamanho, mundo.celulas);

    }

void primeira_celula()
{
	int temp_alt = obter_input();
	int temp_lar = obter_input();
	int excluir;
	
	if(temp_alt < 1 || temp_alt > mundo->tamanho || temp_lar < 1 || temp_lar > mundo->tamanho)
	{
		mostrarMensagem("Posicao invalida");
	}
	
	if(mundo->celula[temp_alt][temp_lar] == O)
	{
		mostrarMensagem("Deseja excluir esta celula? [s][n]:");
		excluir = obter_input();
		if(excluir == s)
		{
			mundo->celula[temp_alt][temp_lar] = '.';
		}
	}
	else
	{
		mundo->celula[temp_alt][temp_lar] =; //função 3;
	}
}
