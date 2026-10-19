//JVIDA_HJRV_Model - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

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

/*
** Verifica se uma celula tem vizinhos vivos.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      linha - a linha da celula a ser verificada
**      coluna - a coluna da celula a ser verificada
*/
int verificar_vizinho(struct Mundo *mundo, int linha, int coluna)
    {
        int resultvizinho = 0;

        for (int i = linha - 1; i <= linha + 1; i++)
        {
            for (int j = coluna - 1; j <= coluna + 1; j++)
            {
                if (i >= 0 && i < mundo->tamanho && j >= 0 && j < mundo->tamanho)
                {
                    if (mundo->celulas[i][j] == 'O')
                    {
                        resultvizinho = 1;
                    }
                }
            }
        }

        return resultvizinho; // retorna 0 se não encontrar vizinhos vivos
    }

void contar_celulas(struct Mundo *mundo)
    {
        for (int i = 0; i < mundo->tamanho; i++)
        {
            for (int j = 0; j < mundo->tamanho; j++)
            {
                if (mundo->celulas[i][j] == 'O')
                {
                    mundo->qtdvivos++;
                }
                else if (mundo->celulas[i][j] == '+')
                {
                    mundo->qtdmortos++;
                }
            }
       }
    }