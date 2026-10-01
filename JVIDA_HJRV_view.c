//JVIDA_HJRV_View - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JVIDA_HJRV_view.h"
/*
** Le um texto, remove a quebra de linha e descarta o excesso.
** Parametros:
**      entrada - vetor que recebe o texto
**      tamanho - capacidade do vetor
*/
int obter_input(char entrada[], int tamanho)
{
    int posicao;
    int lixo;

    //Le a entrada respeitando o limite de tamanho. Retorna 0 em caso de falha
    if (fgets(entrada, tamanho, stdin) == NULL) {
        return 0;
    }

    //Encontra o indice da quebra de linha ('\n') ou o fim da string se o buffer encheu. 
    posicao = strcspn(entrada, "\n");

    if (entrada[posicao] == '\n') {
        //Coloca o fim da string onde estava a quebra de linha.
        entrada[posicao] = '\0';
    } else {
        //Apaga o que sobrou no lixo
        while ((lixo = getchar()) != '\n' && lixo != EOF) {
        }
    }

    return 1;
}

/*
** Pausa a execucao do programa ate que o usuario pressione uma tecla
** Parametros:
**      (nenhum)
*/
void pause() {
    #if defined(_WIN32) || defined(_WIN64)
        printf("\n\n");
        system("pause");
    #elif defined(__linux__) || defined(__unix__)
        printf("\n\nPressione Enter para continuar...");
        getchar();
    #endif
}

/*
** Exibe uma mensagem de texto na tela
** Parametros:
**      msg - (const char*) mensagem a ser exibida
*/
void mostrarMensagem(const char* msg) {
    printf("%s", msg);
}

/*
** Imrpime o mundo atual no terminal.
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