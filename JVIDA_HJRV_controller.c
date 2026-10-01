//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

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
