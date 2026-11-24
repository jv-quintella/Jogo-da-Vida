//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//24/11/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "JVIDA_HJRV_view_jogo.h"
#include "../utilidades/JVIDA_HJRV_view_utilidades.h"
#include "../../model/jogo/JVIDA_HJRV_model_jogo.h"
#include "../../model/struct/JVIDA_HJRV_model_struct.h"

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
        printf("Geracao: %d/%d\n", mundo->geracaoAtual, mundo->qtdgeracoes);
        printf("Quantidade de celulas vivas: %d\n", mundo->qtdvivos);
        printf("Quantidade de celulas vizinhas-mortas: %d\n", mundo->qtdmortos);
        printf("Celulas vivas: ");
        imprimir_lista(obterVivos());
        printf("Vizinhas-mortas: ");
        if (mundo->qtdmortos > 0 && obterMortos() == NULL)
        {
            printf("Lista indisponivel\n");
        }

        else
        {
            imprimir_lista(obterMortos());
        }   
    }

/*
** Solicita, le e valida o tamanho do mundo matricial para a simulacao.
** Garante que a entrada seja um numero inteiro valido entre 10 e 60.
**Funcao baseada em https://github.com/cs50/libcs50/blob/main/src/cs50.c (get_int)
** Parametros:
**      (nenhum)
** Retorno:
**      dimensao do mundo, entre 10 e 60
*/
int obter_tamanho()
{
    int valor;
    char sobra;
    char entrada[100];
    int valido = 0;

    do {
        printf("\nInsira o tamanho do mundo para a simulacao entre 10 e 60 (0 para voltar): ");

        if (obter_input(entrada, sizeof entrada) == 0) {
            printf("Valor invalido!\n");
            valido = 0;
        }
        else if (sscanf(entrada, "%d %c", &valor, &sobra) != 1) {
            printf("Valor invalido!\n");
            valido = 0;
        }
        else if (valor == 0) {
            limparTela();
            return 0;
        }
        else if (valor < 10 || valor > 60) {
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
** Retorno:
**      posicao validada, entre 1 e limite
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

/*
** Solicita, le e valida a velocidade da simulacao.
** Um valor de 1 a 10 define quantos segundos esperar entre as geracoes
** (modo automatico); 0 indica confirmacao manual a cada geracao.
** Parametros:
**      tamanho - capacidade do vetor de entrada
**      entrada - vetor utilizado para armazenar o texto digitado
** Retorno:
**      velocidade informada pelo usuario, entre 0 e 10
*/
int obter_velocidade(int tamanho, char entrada[])
{
    int velocidade;
    int valido;
    char sobra;

    printf("Velocidade: segundos entre geracoes (1 a 10, 0 para manual): ");

    do {
        //Indica um erro se houver falha na leitura do teclado.
        if (obter_input(entrada, tamanho) == 0) {
            printf("Opcao invalida.\nTente novamente: ");
            valido = 0;
        }
        /* Converte a entrada para numero e rejeita se:
        O retorno do sscanf for diferente de 1
        O valor lido for menor que 0 */
        else if (sscanf(entrada, "%d %c", &velocidade, &sobra) != 1 || velocidade < 0 || velocidade > 10) {
            printf("Opcao invalida.\nTente novamente: ");
            valido = 0;
        }
        else {
            valido = 1;
        }
    } while (valido == 0);

    return velocidade;
}

/*
** Solicita, le e valida uma coordenada (linha e coluna) do mundo, digitadas na mesma linha.
** A entrada -1 -1 indica que o usuario deseja parar de informar coordenadas.
** Se a entrada for invalida ou estiver fora do mundo, exibe uma mensagem de erro e repete a leitura.
** Parametros:
**      limite - o valor maximo aceito para linha e coluna (tamanho do mundo)
**      tamanho - a capacidade do vetor de entrada
**      entrada - o vetor utilizado para armazenar a entrada do usuario
**      linha - ponteiro que recebe a linha informada
**      coluna - ponteiro que recebe a coluna informada
** Retorno:
**      1 se uma coordenada valida foi lida; 0 se o usuario digitou -1 -1 ou houve EOF na entrada
*/
int obter_coordenada(int limite, int tamanho, char entrada[], int *linha, int *coluna)
{
    char sobra;

    while (1) {
        //Encerra a leitura se houver falha na leitura do teclado.
        if (obter_input(entrada, tamanho) == 0) {
            return 0;
        }
        else if (sscanf(entrada, "%d %d %c", linha, coluna, &sobra) != 2) {
            printf("Entrada invalida. Digite linha e coluna separadas por espaco (ex: 5 4) ou -1 -1 para parar.\nTente novamente: ");
        }
        else if (*linha == -1 && *coluna == -1) {
            return 0;
        }
        else if (*linha < 1 || *linha > limite || *coluna < 1 || *coluna > limite) {
            printf("Coordenada fora do mundo. Use valores de 1 a %d ou -1 -1 para parar.\nTente novamente: ", limite);
        }
        else {
            return 1;
        }
    }
}

/*
** Exibe os valores atuais da configuracao da simulacao.
** Parametros:
**      mundo - ponteiro para a estrutura que armazena a configuracao do mundo
**      mostrarvizinho - 1 se as vizinhas-mortas estao sendo exibidas; 0 caso contrario
*/
void mostrar_configuracoes(struct Mundo *mundo, int mostrarvizinho)
{
    printf("\n| CONFIGURACOES ATUAIS\n\n");
    printf("Quantidade de geracoes: %d\n", mundo->qtdgeracoes);
    if (mundo->velocidade == 0)
    {
        printf("Velocidade: 0 (manual, confirmacao a cada geracao)\n");
    }
    else
    {
        printf("Velocidade: %d segundo(s) entre geracoes\n", mundo->velocidade);
    }
    if (mostrarvizinho == 1)
    {
        printf("Vizinhas-mortas: sim\n");
    }
    else
    {
        printf("Vizinhas-mortas: nao\n");
    }
    if (mundo->intervalo == 0)
    {
        printf("Intervalo: 0 (uma geracao por vez)\n");
    }
    else
    {
        printf("Intervalo: %d (geracoes por tela)\n", mundo->intervalo);
    }
}


/*
** Exibe o texto de um topico das regras do Jogo da Vida, conforme o enunciado do projeto.
** Parametros:
**      topico - numero do topico a ser exibido, igual a opcao do menu de regras:
**               1 = ideia base, 2 = vizinhos, 3 = reproducao,
**               4 = sobrevivencia, 5 = morte por falta de comida,
**               6 = morte por solidao, 7 = geracoes, 8 = mundo e simbolos
*/
void mostrar_regra(int topico)
{
    switch(topico)
    {
        case 1:
            printf("\n| IDEIA BASE\n\n");
            printf("Um ser vivo necessita de outros seres vivos para sobreviver e\n");
            printf("procriar, mas um excesso de densidade populacional provoca a morte\n");
            printf("do ser vivo devido a escassez de comida.\n\n");
            printf("Os individuos vivem num mundo matricial e a geracao seguinte e\n");
            printf("gerada a partir da geracao anterior de acordo com as regras de\n");
            printf("reproducao, sobrevivencia e morte.\n");
            break;
        case 2:
            printf("\n| VIZINHOS\n\n");
            printf("Cada celula tem um maximo de 8 celulas vizinhas.\n\n");
            printf("Vizinha-morta e a celula morta vizinha a uma celula viva\n");
            printf("(representada pelo caracter '+').\n");
            break;
        case 3:
            printf("\n| REPRODUCAO\n\n");
            printf("Um ser vivo nasce numa celula vazia se essa celula vazia tiver\n");
            printf("exatamente 3 seres vivos vizinhos.\n");
            break;
        case 4:
            printf("\n| SOBREVIVENCIA\n\n");
            printf("Um ser vivo que tenha 2 ou 3 vizinhos sobrevive para a geracao\n");
            printf("seguinte.\n");
            break;
        case 5:
            printf("\n| MORTE POR FALTA DE COMIDA\n\n");
            printf("Um ser vivo com 4 ou mais vizinhos morre porque fica sem comida.\n");
            break;
        case 6:
            printf("\n| MORTE POR SOLIDAO\n\n");
            printf("Um ser vivo com 0 ou apenas 1 vizinho morre de solidao.\n");
            break;
        case 7:
            printf("\n| GERACOES\n\n");
            printf("A cada geracao, as regras devem ser aplicadas para todos os seres\n");
            printf("vivos ao mesmo tempo (isto e, no mesmo passo) para obtermos o\n");
            printf("proximo passo ou geracao.\n");
            break;
        case 8:
            printf("\n| O MUNDO E OS SIMBOLOS\n\n");
            printf("Os individuos vivem numa matriz. Cada posicao da matriz e uma\n");
            printf("celula, representada por:\n\n");
            printf("  O  - ser vivo\n");
            printf("  .  - celula vazia ou morta\n");
            printf("  +  - celula vizinha-morta\n\n");
            printf("O mundo e plano: a ultima celula nao e vizinha da primeira.\n");
            printf("O tamanho do mundo vai de 10 a 60.\n");
            break;
    }
}

/*
** Solicita, le e valida o intervalo da simulacao.
** Um valor positivo define quantas geracoes serao calculadas e exibidas
** antes da proxima espera ou confirmacao; 0 indica uma geracao por vez.
** Parametros:
**      tamanho - capacidade do vetor de entrada
**      entrada - vetor utilizado para armazenar o texto digitado
** Retorno:
**      intervalo informado pelo usuario, maior ou igual a 0
*/
int obter_intervalo(int tamanho, char entrada[])
{
    int intervalo;
    int valido;
    char sobra;

    printf("Intervalo: geracoes por tela (0 para uma por vez): ");

    do {
        if (obter_input(entrada, tamanho) == 0) {
            printf("Opcao invalida.\nTente novamente: ");
            valido = 0;
        }
        else if (sscanf(entrada, "%d %c", &intervalo, &sobra) != 1 || intervalo < 0) {
            printf("Opcao invalida.\nTente novamente: ");
            valido = 0;
        }
        else {
            valido = 1;
        }
    } while (valido == 0);

    return intervalo;
}

/*
** Imprime no terminal as coordenadas de todas as celulas de uma lista,
** no formato (linha, coluna), separadas por espaco, em uma unica linha.
** As coordenadas sao exibidas a partir de 1 (indice da matriz + 1),
** igual ao que o usuario digita em colocar_celula.
** Se a lista estiver vazia, imprime "Lista vazia".
** Parametros:
**      lista - ponteiro para o inicio da lista a ser impressa (somente leitura),
**              como pvivo ou pmorto
*/
void imprimir_lista(const celula *lista)
{
    const celula *aux = lista;
    
    // lista vazia: avisa e sai sem imprimir nada mais
    if (aux == NULL)
    {
        printf("Lista vazia\n");
        return;
    }

    // percorre a lista imprimindo cada no
    while(aux != NULL)
    {
        // soma 1 para converter do indice da matriz (base 0) para a contagem do usuario (base 1)
        printf("(%d, %d) ", aux->linha + 1, aux->coluna + 1);
        aux = aux -> proximo;
    }

    printf("\n");
}

/*
** Solicita ao usuario um nome valido para o arquivo de geracao.
** Retorno:
**      1 se um nome valido foi lido; 0 em caso de falha na entrada
*/
int obter_nome_save(char nome[], int tamanho)
{
    int valido = 0;

    do {
        printf("\nDigite o nome para salvar a geracao (sem extensao): ");
        if (obter_input(nome, tamanho) == 0)
        {
            return 0;
        }

        if (nome[0] == '\0' || strchr(nome, '/') != NULL || strchr(nome, '\\') != NULL)
        {
            printf("Nome invalido. Nao deixe vazio e nao use barras.\n");
            valido = 0;
        }
        else
        {
            valido = 1;
        }
    } while (valido == 0);

    return 1;
}

/*
** Pergunta ao usuario se deseja sobrescrever um save ja existente.
** Retorno:
**      1 para sobrescrever ('s'/'S'); 0 para cancelar ('n'/'N')
*/
int confirmar_sobrescrita(void)
{
    char entrada[10];

    while (1)
    {
        printf("Ja existe um save com esse nome. Deseja sobrescrever? [s/n]: ");
        if (obter_input(entrada, sizeof entrada) == 0)
        {
            return 0;
        }
        if (entrada[0] == 's' || entrada[0] == 'S')
        {
            return 1;
        }
        if (entrada[0] == 'n' || entrada[0] == 'N')
        {
            return 0;
        }
        printf("Opcao invalida.\n");
    }
}

/*
** Exibe a lista numerada de saves disponiveis e le a escolha do usuario.
** Retorno:
**      indice escolhido (0 a qtd - 1); -1 se o usuario cancelar (0)
*/
int escolher_save(char nomes[][50], int qtd)
{
    char entrada[10];
    char sobra;
    int escolha;
    int i;

    printf("\n| GERACOES SALVAS\n\n");
    for (i = 0; i < qtd; i++)
    {
        printf("[%d] - %s\n", i + 1, nomes[i]);
    }
    printf("[0] - Cancelar\n");
    printf("---------------------------\n");

    while (1)
    {
        printf("Escolha o numero da geracao: ");
        if (obter_input(entrada, sizeof entrada) == 0)
        {
            return -1;
        }
        if (sscanf(entrada, "%d %c", &escolha, &sobra) == 1 && escolha >= 0 && escolha <= qtd)
        {
            return escolha - 1; // 0 vira -1 (cancelar)
        }
        printf("Opcao invalida. Digite um numero de 0 a %d.\n", qtd);
    }
}