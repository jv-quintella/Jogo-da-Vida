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
    ** Inicia a simulacao do Jogo da Vida, obtendo o tamanho do mundo,
    ** inicializando a matriz e exibindo seu estado inicial.
    ** Parametros:
    **      Nenhum.
    */
    void iniciar_simulacao()
    {
        struct Mundo mundo;
        int tamanho;
        char entrada[10];
        int mostrarvizinho;
        int menu2, menu1;

        do{
            limparTela();
            menu1 = mostrar_Menu(1);

            switch(menu1) // Executa a escolha do usuario no menu inicial
            {
                case 1:
                    tamanho = obter_tamanho();
                    //Passa o endereco de memoria (&) da struct para o Model preencher os pontos 
                    criar_mundo(&mundo, tamanho);
                    mundo.geracaoAtual = 0;
                    mundo.qtdgeracoes = obter_qtdgeracoes(sizeof entrada, entrada);
                    mostrarvizinho = mostrar_mortos(sizeof entrada, entrada);
                    contar_celulas(&mundo, mostrarvizinho);

                    do{
                        limparTela();
                        imprimir_mundo(mundo.tamanho, &mundo, mostrarvizinho);
                        contar_celulas(&mundo, mostrarvizinho);

                        menu2 = mostrar_Menu(2); // Exibe o menu de simulacao e armazena a escolha do usuario

                        if(menu2 == 1)
                        {
                            colocar_celula(&mundo, sizeof entrada, entrada);
                            contar_celulas(&mundo, mostrarvizinho);
                            limparTela();
                            imprimir_mundo(mundo.tamanho, &mundo, mostrarvizinho);
                            continue;
                        }
                        else if(menu2 == 2)
                        {
                            evoluir_geracoes(&mundo, mostrarvizinho);
                            continue;
                        }
                        else if(menu2 == 3)
                        {
                            limpar_celula(&mundo);
                            limparTela();
                            contar_celulas(&mundo, mostrarvizinho);
                            imprimir_mundo(mundo.tamanho, &mundo, mostrarvizinho);
                            continue;
                        }
                        else if (menu2 == 0)
                        {
                            mostrarMensagem("Saindo da simulacao...\n");
                        }
                        else
                        {
                            limparTela();
                            contar_celulas(&mundo, mostrarvizinho);
                            imprimir_mundo(mundo.tamanho, &mundo, mostrarvizinho);
                            mostrarMensagem("\nOpcao invalida. Tente novamente.");
                            pause();
                            continue;
                        }
                    }while(menu2 != 0); 
                    break;
                case 2:
                    return;
                case 0:
                    mostrarMensagem("Saindo do programa...\n");
                    return;
                default:
                    mostrarMensagem("Opcao invalida. Tente novamente.\n");
                    break;
            }
        } while(menu1 != 0);
    }

/*
** Permite ao usuario escolher se deseja mostrar os vizinhos mortos das celulas vivas do mundo.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      tamanho - o tamanho utilizado na leitura das entradas
**      entrada - o vetor utilizado para armazenar as entradas do usuario
*/
int mostrar_mortos(int tamanho, char entrada[])
{
    int valido = 0;

    do
    {
        mostrarMensagem("Deseja mostrar os vizinhos mortos das celulas? Nao e possivel desativar durante o jogo [s/n]: ");
        obter_input(entrada, tamanho);
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
** Permite adicionar ou excluir celulas vivas do mundo, a partir
** das posicoes informadas pelo usuario.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      tamanho - o tamanho utilizado na leitura das entradas
**      entrada - o vetor utilizado para armazenar as entradas do usuario
*/
void colocar_celula(struct Mundo *mundo, int tamanho, char entrada[])
{
    int temp_alt;
    int temp_lar;
    int valido = 0;

    mostrarMensagem("\nInforme a linha: ");
    temp_alt = obter_posicao(mundo->tamanho, tamanho, entrada);

    mostrarMensagem("Informe a coluna: ");
    temp_lar = obter_posicao(mundo->tamanho, tamanho, entrada);

    //Ajusta as coordenadas para os indices da matriz.
    temp_alt--;
    temp_lar--;

    if (mundo->celulas[temp_alt][temp_lar] == 'O') {
        do {
            mostrarMensagem("\nDeseja excluir esta celula? [s/n]: ");

            if (obter_input(entrada, tamanho) == 0) 
            {
                mostrarMensagem("Valor invalido.\n");
                valido = 0;
            }
            else if (entrada[0] == 's' || entrada[0] == 'S') 
            {
                mundo->celulas[temp_alt][temp_lar] = '.';
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
    }
}

/*
** Limpa todas as celulas do mundo, preenchendo a matriz com
** celulas mortas e exibindo o mundo atualizado.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
*/
void limpar_celula(struct Mundo *mundo)
    {
        limparTela();
        memset(mundo->celulas, '.', sizeof(mundo->celulas));
        //contar_celulas(mundo, mostrarvizinho); check
        //imprimir_mundo(mundo->tamanho, mundo, mostrarvizinho, qtdgeracoes);
    }
    
/*
** Evolui o mundo geracao por geracao, usando uma matriz auxiliar.
** A cada volta calcula a proxima geracao, torna-a a atual e a exibe,
** perguntando ao usuario se deseja continuar.
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

    criar_mundo(&mundo_auxiliar, mundo->tamanho);

    do {
        calcular_geracao(mundo, &mundo_auxiliar);
        *mundo = mundo_auxiliar;

        // restaura os campos sobrescritos pela copia
        atual++;
        mundo->qtdgeracoes = total;
        mundo->geracaoAtual = atual;

        limparTela();
        contar_celulas(mundo, mostrarvizinho);
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