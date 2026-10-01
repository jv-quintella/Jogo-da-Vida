//JVIDA_HJRV_Model - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include "JVIDA_HJRV_model_struct.h"
#include "JVIDA_HJRV_model_jogo.h"

/*
** Inicializa o mundo com celulas vazias, representadas por pontos.
** Parametros:
**      tamanho - dimensao da matriz quadrada a ser preenchida
*/
void criar_mundo(struct Mundo *mundo, int tamanho)
    {
        int i, j;
        mundo->tamanho = tamanho;
        //Percorre cada linha (i) e cada coluna (j) da matriz, preenchendo com '.' 
        for(i = 0; i < tamanho; i++)
            {
                for(j = 0; j < tamanho; j++)
                {
                    mundo->celulas[i][j] = '.';
                }
            }
    }