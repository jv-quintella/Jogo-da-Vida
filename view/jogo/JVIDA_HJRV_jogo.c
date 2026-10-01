//JVIDA_HJRV_View - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
** Imprime o mundo atual no terminal.
** Imprime os caracteres linha por linha e realiza a quebra para formar a matriz.
** Parametros:
**      tamanho - dimensao da matriz a ser exibida
**      mundo   - a matriz bidimensional contendo o estado das celulas
*/
//implementar indicacao visual de cada linha/coluna
void imprimir_mundo(int tamanho, char mundo[60][60])
    {
        int i, j;
        
        for (i = 0; i < tamanho; i++)
            {
                for(j = 0; j < tamanho; j++)
                {
                    printf("%c", mundo[i][j]);
                }
                printf("\n");
            }
    }

/*
** Solicita, le e valida o tamanho do mundo matricial para a simulacao.
** Garante que a entrada seja um numero inteiro valido entre 10 e 60.
** Parametros:
**      (nenhum)
*/
int obter_tamanho()
    {
        long valor;
        char *fim;
        char entrada[100];
        int valido = 0;

        do{
            mostrarMensagem("Insira o tamanho do mundo para a simulacao (entre 10 e 60): ");
            // Indica um erro se houver falha na leitura.
            if (obter_input(entrada, sizeof entrada) == 0)
                {
                    mostrarMensagem("Valor invalido, insira um numero inteiro entre 10 e 60 ");
                    valido = 0;
                    continue;
                }
            
            //converte o texto lido para numero. Se 'fim' apontar para o final da string ('\0'), significa que a conversao foi  bem-sucedida. 
            valor = strtol(entrada, &fim, 10);

            /* Valida se: 
            Nada foi convertido (fim == entrada)
            O usuario digitou letras junto com numeros (*fim != '\0')
            O valor esta fora dos limites (10 a 60) */
            if(fim == entrada || *fim != '\0' || (valor < 10 || valor > 60))
                {
                    mostrarMensagem("Valor invalido, insira um numero inteiro entre 10 e 60 ");
                    valido = 0;
                }
            else 
                {
                    valido = 1;
                }
        } while(valido !=1);
        return (int) valor;
    }