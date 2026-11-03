//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <string.h>
#include "JVIDA_HJRV_controller_jogo.h"
#include "../../model/jogo/JVIDA_HJRV_model_jogo.h"
#include "../../view/jogo/JVIDA_HJRV_view_jogo.h"
#include "../../view/menu/JVIDA_HJRV_view_menu.h"
#include "../../view/utilidades/JVIDA_HJRV_view_utilidades.h"

/*
    ** Inicia a simulacao do Jogo da Vida, exibindo o menu principal.
    ** Permite criar um novo mundo (informando apenas o tamanho, com configuracao padrao)
    ** ou continuar a simulacao em andamento, ate o usuario escolher sair.
    ** Parametros:
    **      Nenhum.
    */
    void iniciar_simulacao()
    {
        struct Mundo mundo;
        int tamanho;
        int geracoes;
        char entrada[10];
        int mostrarvizinho = 0;
        int simulacao_ativa = 0;
        int menu1;

        do{
            limparTela();
            menu1 = mostrar_Menu(1);

            switch(menu1) // Executa a escolha do usuario no menu inicial
            {
                case 1:
                    tamanho = obter_tamanho();
                    geracoes = obter_qtdgeracoes(sizeof entrada, entrada);
                    //Passa o endereco de memoria (&) da struct para o Model preencher os pontos 
                    criar_mundo(&mundo, tamanho);
                    mundo.geracaoAtual = 0;
                    mundo.qtdgeracoes = geracoes;
                    mundo.velocidade = 0;
                    mostrarvizinho = 0;
                    simulacao_ativa = 1;
                    menu_simulacao(&mundo, &mostrarvizinho);
                    break;
                case 2:
                    if(simulacao_ativa == 1)
                    {
                        menu_simulacao(&mundo, &mostrarvizinho);
                    }
                    else
                    {
                        mostrarMensagem("\nNenhuma simulacao em andamento. Escolha a opcao 1 para criar um mundo.\n");
                        pause();
                    }
                    break;
                case 0:
                    mostrarMensagem("Saindo do programa...\n");
                    return;
            }
        } while(menu1 != 0);
    }

/*
** Exibe o mapa e o menu da simulacao e executa a opcao escolhida pelo usuario
** (editar celulas, simular evolucao, limpar o mapa ou configurar), ate ele voltar.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      mostrarvizinho - ponteiro para o indicador de exibicao das vizinhas-mortas ('+');
**                       1 para exibir, 0 caso contrario
*/
void menu_simulacao(struct Mundo *mundo, int *mostrarvizinho)
{
    char entrada[10];
    int menu2;

    do{
        limparTela();
        contar_celulas(mundo);
        imprimir_mundo(mundo->tamanho, mundo, *mostrarvizinho);

        menu2 = mostrar_Menu(2); // Exibe o menu de simulacao e armazena a escolha do usuario

        if(menu2 == 1)
        {
            colocar_celula(mundo, sizeof entrada, entrada, *mostrarvizinho);
        }
        else if(menu2 == 2)
        {
            evoluir_geracoes(mundo, *mostrarvizinho);
        }
        else if(menu2 == 3)
        {
            limpar_mapa(mundo);
        }
        else if(menu2 == 4)
        {
            configurar_simulacao(mundo, mostrarvizinho);
        }
        else if (menu2 == 0)
        {
            mostrarMensagem("Saindo da simulacao...\n");
        }
    }while(menu2 != 0);
}

/*
** Exibe o menu de configuracoes e permite alterar a quantidade de geracoes,
** a velocidade e a exibicao das vizinhas-mortas, ate o usuario voltar.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo (recebe quantidade de geracoes e velocidade)
**      mostrarvizinho - ponteiro para o indicador de exibicao das vizinhas-mortas ('+');
**                       1 para exibir, 0 caso contrario
*/
void configurar_simulacao(struct Mundo *mundo, int *mostrarvizinho)
{
    char entrada[10];
    int menu3;

    do{
        limparTela();
        mostrar_configuracoes(mundo, *mostrarvizinho);

        menu3 = mostrar_Menu(3);

        if(menu3 == 1)
        {
            mundo->qtdgeracoes = obter_qtdgeracoes(sizeof entrada, entrada);
        }
        else if(menu3 == 2)
        {
            mundo->velocidade = obter_velocidade(sizeof entrada, entrada);
        }
        else if(menu3 == 3)
        {
            *mostrarvizinho = mostrar_mortos(sizeof entrada, entrada);
        }
    }while(menu3 != 0);
}

/*
** Solicita ao usuario se deseja destacar as celulas mortas com vizinhos vivos.
** Aceita 's' ou 'S' para mostrar e 'n' ou 'N' para ocultar.
** Parametros:
**      tamanho - capacidade do vetor de entrada
**      entrada - vetor utilizado para armazenar a resposta do usuario
** Retorno:
**      1 para mostrar as celulas mortas com vizinhos vivos; 0 para ocultar
*/
int mostrar_mortos(int tamanho, char entrada[])
{
    int valido = 0;

    do
    {
        mostrarMensagem("\nDeseja mostrar as vizinhas-mortas das celulas? [s/n]: ");
        if(obter_input(entrada, tamanho) == 0)
        {
            return 0;
        }
        if(entrada[0] == 's' || entrada[0] == 'S')
        {
            valido = 1;
            return 1;
        }
        else if(entrada[0] == 'n' || entrada[0] == 'N')
        {
            valido = 1;
            return 0;
        }
        else
        {
            mostrarMensagem("Opcao invalida.\n\n");
            valido = 0;
        }
    } while (valido == 0);
    return 0;
}


/*
** Permite adicionar ou excluir celulas vivas do mundo, a partir das coordenadas
** informadas pelo usuario, repetindo a leitura ate ele digitar -1 -1.
** Cada alteracao reinicia o contador de geracoes e atualiza o mapa exibido.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      tamanho - capacidade do vetor de entrada
**      entrada - o vetor utilizado para armazenar as entradas do usuario
**      mostrarvizinho - 1 para exibir as vizinhas-mortas ('+') no mapa; 0 caso contrario
*/
void colocar_celula(struct Mundo *mundo, int tamanho, char entrada[], int mostrarvizinho)
{
    int temp_alt;
    int temp_lar;
    int valido;
    int continuar = 1;

    do {
        limparTela();
        contar_celulas(mundo);
        imprimir_mundo(mundo->tamanho, mundo, mostrarvizinho);
        mostrarMensagem("\nInforme linha e coluna (ex: 5 4) ou -1 -1 para parar: ");

        if (obter_coordenada(mundo->tamanho, tamanho, entrada, &temp_alt, &temp_lar) == 0)
        {
            continuar = 0;
        }
        else
        {
            //Ajusta as coordenadas para os indices da matriz.
            temp_alt--;
            temp_lar--;

            if (mundo->celulas[temp_alt][temp_lar] == 'O') {
                valido = 0;
                do {
                    mostrarMensagem("\nDeseja excluir esta celula? [s/n]: ");

                    if (obter_input(entrada, tamanho) == 0) 
                    {
                        continuar = 0;
                        valido = 1;
                    }
                    else if (entrada[0] == 's' || entrada[0] == 'S') 
                    {
                        mundo->celulas[temp_alt][temp_lar] = '.';
                        mundo->geracaoAtual = 0;
                        valido = 1;
                    }
                    else if (entrada[0] == 'n' || entrada[0] == 'N') 
                    {
                        valido = 1;
                    }
                    else 
                    {
                        mostrarMensagem("Opcao invalida.\n");
                        valido = 0;
                    }
                } while (valido == 0);
            }
            else 
            {
                mundo->celulas[temp_alt][temp_lar] = 'O';
                mundo->geracaoAtual = 0;
            }
        }
    } while (continuar == 1);
}

/*
** Preenche toda a matriz de celulas com pontos e reinicia o contador de geracoes.
** Parametros:
**      mundo - ponteiro para a estrutura cuja matriz sera preenchida
*/
void limpar_mapa(struct Mundo *mundo)
    {
        memset(mundo->celulas, '.', sizeof(mundo->celulas));
        mundo->geracaoAtual = 0;
    }
    
/*
** Evolui o mundo, usando uma matriz auxiliar, e exibe o resultado a cada tela.
** Com velocidade 0 avanca uma geracao por tela (passo a passo); com velocidade N
** maior que 0 avanca N geracoes por tela, sem ultrapassar a quantidade total.
** Apos cada tela, pergunta ao usuario se deseja continuar.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo atual (lido e atualizado)
**      mostrarvizinho - 1 para exibir as vizinhas-mortas ('+'), 0 caso contrario
*/
void evoluir_geracoes(struct Mundo *mundo, int mostrarvizinho)
{
    struct Mundo mundo_auxiliar;
    char entrada[10];
    int continuar = 1;
    int valido;
    int total = mundo->qtdgeracoes;
    int atual = mundo->geracaoAtual;
    int passo;
    int i, j, k;

    if (atual >= total)
    {
        mostrarMensagem("\nQuantidade de geracoes atingida. Aumente-a nas configuracoes ou edite o mapa para recomecar.\n");
        pause();
        return;
    }

    criar_mundo(&mundo_auxiliar, mundo->tamanho);

    do {
        passo = 1;
        if (mundo->velocidade > 0)
        {
            passo = mundo->velocidade;
            if (passo > total - atual)
            {
                passo = total - atual;
            }
        }

        for (k = 0; k < passo; k++)
        {
            //Calcula toda a proxima geracao no mundo auxiliar, preservando o mundo atual.
            calcular_geracao(mundo, &mundo_auxiliar);
            //Copia a geracao calculada para o mundo atual somente apos a varredura completa.
            for (i = 0; i < mundo->tamanho; i++)
            {
                for (j = 0; j < mundo->tamanho; j++)
                {
                    mundo->celulas[i][j] = mundo_auxiliar.celulas[i][j];
                }
            }
        }

        //Avanca o contador pela quantidade real de geracoes calculadas.
        atual += passo;
        mundo->geracaoAtual = atual;

        limparTela();
        contar_celulas(mundo);
        imprimir_mundo(mundo->tamanho, mundo, mostrarvizinho);

        if (atual >= total)
        {
            mostrarMensagem("\nQuantidade de geracoes atingida.\n");
            pause();
            break;
        }

        valido = 0;
        do {
            mostrarMensagem("\nMostrar a proxima geracao? [s/n]: ");

            if (obter_input(entrada, sizeof entrada) == 0)
            {
                continuar = 0;
                valido = 1;
            }
            else if (entrada[0] == 's' || entrada[0] == 'S')
            {
                continuar = 1;
                valido = 1;
            }
            else if (entrada[0] == 'n' || entrada[0] == 'N')
            {
                continuar = 0;
                valido = 1;
            }
            else
            {
                mostrarMensagem("Opcao invalida.\n");
            }
        } while (valido == 0);

    } while (continuar == 1);
}
