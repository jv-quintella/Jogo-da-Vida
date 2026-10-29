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
** Exibe o mundo atual, as coordenadas e os contadores da simulacao.
** Quando solicitado, representa com '+' as celulas mortas com vizinhos vivos.
** Parametros:
**      tamanho - dimensao da matriz a ser exibida
**      mundo - ponteiro para a estrutura que armazena o mundo e seus contadores
**      mostrarvizinho - 1 para destacar as celulas mortas com vizinhos vivos;
**                       0 para exibir os caracteres armazenados na matriz
*/
void imprimir_mundo(int tamanho, struct Mundo *mundo, int mostrarvizinho)
    {
        int i, j;
        
        //Exibe os numeros das colunas a partir de 1.
        printf("    ");
        for(j = 0; j < tamanho; j++)
        {
            printf("%4d ", j+1);
        }
        
        printf("\n");
        
        //Exibe cada linha da matriz a partir de 1.
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
        printf("Geracoes: %d\n", mundo->qtdgeracoes);
        printf("Quantidade de celulas vivas: %d\n", mundo->qtdvivos);
        printf("Quantidade de celulas mortas: %d\n", mundo->qtdmortos);
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

/*
** Solicita, le e valida a quantidade de geracoes a serem simuladas.
** Repete a leitura enquanto a entrada for invalida ou o valor for menor que 1.
** Parametros:
**      tamanho - capacidade do vetor de entrada
**      entrada - vetor utilizado para armazenar a entrada do usuario
** Retorno:
**      quantidade de geracoes informada pelo usuario, maior ou igual a 1
*/
int obter_qtdgeracoes(int tamanho, char entrada[])
{
    int valido;
    int quantidade;
    char sobra;

    printf("Quantidade de geracoes a serem simuladas: ");

    do {
        //Indica um erro se houver falha na leitura do teclado.
        if (obter_input(entrada, tamanho) == 0) {
            printf("Opcao invalida.\nTente novamente: ");
            valido = 0;
        }
        /* Converte a entrada para numero e rejeita se:
        O retorno do sscanf for diferente de 1
        O valor lido estiver fora do intervalo de 1 ate o limite */
        else if (sscanf(entrada, "%d %c", &quantidade, &sobra) != 1 || quantidade < 1) {
            printf("Opcao invalida.\nTente novamente: ");
            valido = 0;
        }
        else {
            valido = 1;
        }
    } while (valido == 0);

    return quantidade;
}