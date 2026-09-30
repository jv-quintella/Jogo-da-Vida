#include <stdio.h>
#include <stdlib.h>

/*
** Le um texto, remove a quebra de linha e descarta o excesso.
** Parametros:
**      entrada - vetor que recebe o texto
**      tamanho - capacidade do vetor, no minimo 2
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
