//JVIDA_HJRV_View - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JVIDA_HJRV_view_jogo.h"
#include "../utilidades/JVIDA_HJRV_view_utilidades.h"
#include "../../model/jogo/JVIDA_HJRV_model_jogo.h"

/*
** Imprime o mundo atual no terminal.
** Imprime os caracteres linha por linha e realiza a quebra para formar a matriz.
** Parametros:
**      tamanho - dimensao da matriz a ser exibida
**      mundo   - a matriz bidimensional contendo o estado das celulas
*/
//implementar indicacao visual de cada linha/coluna
void imprimir_mundo(int tamanho, struct Mundo *mundo, int mostrarvizinho)
    {
        int qtdvivos, qtdmortos; //não sei se isso deveria existir, mas nao funciona sem
        int i, j;
        
        //printa coluna
        printf("    ");
        for(j = 0; j < tamanho; j++)
        {
            printf("%4d ", j+1);
        }
        
        printf("\n");
        
        //printa linha
        for(i = 0; i < tamanho; i++)
        {
            printf("  %2d ", i+1);
            for(j = 0; j < tamanho; j++)
            {
                if ((mundo->celulas[i][j] == '.') && (verificar_vizinho(mundo, i, j) == 1) && (mostrarvizinho == 1))
                {
                    printf("  +  ");
                }
                else
                {
                    printf("  %c  ", mundo->celulas[i][j]);
                }
            }	
            printf("\n");
        }
        printf("\n");
        printf("Quantidade de celulas vivas: %d\n", qtdvivos);
        printf("Quantidade de celulas mortas: %d\n", qtdmortos);
    }

/*
** Solicita, le e valida o tamanho do mundo matricial para a simulacao.
** Garante que a entrada seja um numero inteiro valido entre 10 e 60.
**Funcao baseada em https://github.com/cs50/libcs50/blob/main/src/cs50.c (get_int)
** Parametros:
**      (nenhum)
*/
int obter_tamanho()
{
    int valor;
    char sobra;
    char entrada[100];
    int valido = 0;

    do {
        printf("\nInsira o tamanho do mundo para a simulacao (entre 10 e 60): ");

        //Indica um erro se houver falha na leitura do teclado.
        if (obter_input(entrada, sizeof entrada) == 0) {
            printf("Valor invalido!\n");
            valido = 0;
        }
        /* Converte a entrada para numero e rejeita se:
        O retorno do sscanf for diferente de 1
        O valor lido estiver fora do intervalo de 10 a 60 */
        else if (sscanf(entrada, "%d %c", &valor, &sobra) != 1 || valor < 10 || valor > 60) {
            printf("Valor invalido!\n");
            valido = 0;
        }
        else {
            valido = 1;
        }
    } while (valido == 0);

    return valor;
}

/*
**Solicita, le e valida uma posicao (linha ou coluna) para a matriz do mundo.
**Garante que a entrada seja um numero inteiro valido entre 1 e o limite.
**Funcao baseada em https://github.com/cs50/libcs50/blob/main/src/cs50.c (get_int)
**Parametros:
**      limite - o valor maximo aceito (tamanho do mundo)
**      tamanho - a capacidade do vetor de entrada
**      entrada - o vetor utilizado para armazenar a entrada do usuario
*/
int obter_posicao(int limite, int tamanho, char entrada[])
{
    int valor;
    char sobra;
    int valido = 0;

    do {
        //Indica um erro se houver falha na leitura do teclado.
        if (obter_input(entrada, tamanho) == 0) {
            printf("Valor invalido.\nTente novamente: ");
            valido = 0;
        }
        /* Converte a entrada para numero e rejeita se:
        O retorno do sscanf for diferente de 1
        O valor lido estiver fora do intervalo de 1 ate o limite */
        else if (sscanf(entrada, "%d %c", &valor, &sobra) != 1 || valor < 1 || valor > limite) {
            printf("Posicao invalida.\nTente novamente: ");
            valido = 0;
        }
        else {
            valido = 1;
        }
    } while (valido == 0);

    return valor;
}