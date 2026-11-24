//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "JVIDA_HJRV_controller_jogo.h"
#include "../../model/jogo/JVIDA_HJRV_model_jogo.h"
#include "../../view/jogo/JVIDA_HJRV_view_jogo.h"
#include "../../view/menu/JVIDA_HJRV_view_menu.h"
#include "../../view/utilidades/JVIDA_HJRV_view_utilidades.h"

/*
    ** Inicia a simulacao do Jogo da Vida, exibindo o menu principal.
    ** Permite criar um novo mundo, continuar a simulacao em andamento ou consultar
    ** as regras do jogo, ate o usuario escolher sair.
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
        mundo.velocidade = 0;
        mundo.intervalo = 0;

        do{
            limparTela();
            menu1 = mostrar_Menu(1);

            switch(menu1) // Executa a escolha do usuario no menu inicial
            {
                case 1:
                    tamanho = obter_tamanho();
                    geracoes = obter_qtdgeracoes(sizeof entrada, entrada);
                    //Passa o endereco de memoria (&) da struct para o Model preencher os pontos 
                    liberarVivos();
                    liberarMortos();
                    liberarVivosProx();
                    criar_mundo(&mundo, tamanho);
                    mundo.geracaoAtual = 0;
                    mundo.qtdgeracoes = geracoes;
                    mundo.velocidade = 0;
                    mundo.intervalo = 0;
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
                case 3:
                    menu_regras();
                    break;
                case 0:
                    liberarVivos();
                    liberarMortos();
                    liberarVivosProx();
                    mostrarMensagem("Saindo do programa...\n");
                    return;
            }
        } while(menu1 != 0);
    }

/*
** Exibe o menu de regras do jogo e, a cada topico escolhido, mostra o texto
** correspondente e aguarda o usuario, repetindo ate ele escolher voltar.
** Parametros:
**      (nenhum)
*/
void menu_regras(void)
{
    int topico;

    do{
        limparTela();
        topico = mostrar_Menu(4);

        if(topico >= 1 && topico <= 9)
        {
            limparTela();
            mostrar_regra(topico);
            pause();
        }
    }while(topico != 0);
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
        else if(menu2 == 5)
        {
            opcoes_carregamento(mundo, mostrarvizinho);
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
        else if(menu3 == 4)
        {
            mundo->intervalo = obter_intervalo(sizeof entrada, entrada);
        }
    }while(menu3 != 0);
}

void opcoes_carregamento(struct Mundo *mundo, int *mostrarvizinho)
{
    int menu5;
    int indice_geracao = 0;

    do{
        limparTela();
        imprimir_mundo(mundo->tamanho, mundo, *mostrarvizinho);

        menu5 = mostrar_Menu(5);

        if(menu5 == 1)
        {
            salvar_geracao_controller(mundo);
        }
        else if(menu5 == 2)
        {
            carregar_geracao_selecao_controller(mundo);
        }
        else if(menu5 == 3)
        {
            carregar_geracao_sucessiva_controller(mundo, &indice_geracao);
        }
    }while(menu5 != 0);
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
        // para se o usuário digitar -1 -1
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
                    // sai da pergunta se sem entrada
                    {
                        continuar = 0;
                        valido = 1;
                    }
                    else if (entrada[0] == 's' || entrada[0] == 'S') 
                    {
                        if(removerVivos(temp_alt, temp_lar) == 1)
                        {
                            mundo->celulas[temp_alt][temp_lar] = '.'; // altera pra morta
                            mundo->geracaoAtual = 0; // reseta gerações
                            if(atualizarMortos(mundo -> tamanho) == 0)
                            // recalcula a lista de vizinhas mortas
                            {
                                mostrarMensagem("Falha na alocacao de memoria");
                                pause();
                            }
                            valido = 1;
                        }

                        else
                        // celula aparece no mapa mas nao na lista de vivas
                        {
                            mostrarMensagem("Celula nao encontrada na lista");
                            pause();
                        }
                        valido = 1;
                    }
                    else if (entrada[0] == 'n' || entrada[0] == 'N') 
                    // mantem a celula viva
                    {
                        valido = 1;
                    }
                    else 
                    {
                        mostrarMensagem("Opcao invalida.\n");
                        pause();
                        valido = 0;
                    }
                } while (valido == 0);
            }

            else 
            // se celula morta, cria nova celula
            {
                if (buscarVivos(temp_alt, temp_lar) == NULL)
                // aloca memoria para inserir a celula
                {
                    carregarVivos(temp_alt, temp_lar);
                }

                if (buscarVivos(temp_alt, temp_lar) != NULL)
                {
                    mundo->celulas[temp_alt][temp_lar] = 'O'; // marca como viva
                    mundo->geracaoAtual = 0; // reseta as gerações
                    if(atualizarMortos(mundo -> tamanho) == 0)
                    // recalcula lista de vizinhas mortas
                    {
                        mostrarMensagem("Falha na alocacao de memoria");
                        pause();
                    }
                }
                
                else
                // falha na inserção
                {
                    mundo->celulas[temp_alt][temp_lar] = '.';
                    mostrarMensagem("Falha na alocacao de memoria");
                    pause();
                }
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
        liberarVivos();
        liberarMortos();
        liberarVivosProx();
        mundo->qtdvivos = 0;
        mundo->qtdmortos = 0;
        mundo->geracaoAtual = 0;
        memset(mundo->celulas, '.', sizeof(mundo->celulas));
        mundo->geracaoAtual = 0;
    }
    
/*
** Calcula as geracoes sucessivas usando uma matriz auxiliar,
** atualizando os contadores e exibindo cada geracao calculada.
** Com velocidade 0, pede confirmacao a cada passo; com velocidade positiva,
** espera esse numero de segundos e segue automaticamente.
** O intervalo define quantas geracoes sao exibidas a cada passo,
** sem ultrapassar a quantidade total configurada.
** Parametros:
**      mundo - ponteiro para a estrutura do mundo, cuja matriz
**              e cujos contadores serao atualizados
**      mostrarvizinho - 1 para exibir as vizinhas-mortas como '+';
**                       0 para representa-las como pontos
*/
void evoluir_geracoes(struct Mundo *mundo, int mostrarvizinho)
{
    char entrada[10];
    int continuar = 1;
    int valido;
    int total = mundo->qtdgeracoes;
    int atual = mundo->geracaoAtual;
    int passo;
    int k;

    if (atual >= total)
    {
        mostrarMensagem("\nQuantidade de geracoes atingida. Aumente-a nas configuracoes ou edite o mapa para recomecar.\n");
        pause();
        return;
    }

    if (!atualizarMortos(mundo->tamanho))
    {
        mostrarMensagem("\nErro ao alocar memoria para celulas vizinhas.\n");
        pause();
        return;
    }

    do {
        passo = 1;
        if (mundo->intervalo > 0)
        {
            passo = mundo->intervalo;
            if (passo > total - atual)
            {
                passo = total - atual;
            }
        }

        limparTela();

        for (k = 0; k < passo; k++)
        {
            if (!calcular_geracao(mundo))
            {
                mostrarMensagem("\nErro ao alocar memoria para a proxima geracao.\n");
                pause();
                return;
            }

            atualizarVivos();
            atualizarMapa(mundo);

            atual++;
            mundo->geracaoAtual = atual;

            if (!atualizarMortos(mundo->tamanho))
            {
                mostrarMensagem("\nErro ao alocar memoria para celulas vizinhas.\n");
                pause();
                return;
            }

            contar_celulas(mundo);
            imprimir_mundo(mundo->tamanho, mundo, mostrarvizinho);
        }

        if (atual >= total)
        {
            mostrarMensagem("\nQuantidade de geracoes atingida.\n");
            pause();
            break;
        }

        if (mundo->qtdvivos == 0)
        {
            mostrarMensagem("\n0 CELULAS VIVAS - FIM DA SIMULACAO\n");
            pause();
            break;
        }

        if (mundo->velocidade > 0)
        {
            //Automatico: espera N segundos e segue direto, sem perguntar
            tempo(mundo->velocidade);
            continuar = 1;
        }
        else
        {
            //Manual: pergunta somente neste caminho
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
        }

    } while (continuar == 1);
}

/*
** Pede o nome do save ao usuario, verifica se ja existe (permitindo sobrescrever
** sob confirmacao) e grava a geracao no arquivo correspondente.
*/
void salvar_geracao_controller(struct Mundo *mundo)
{
    char nome[MAX_NOME_SAVE];
    char nomeArquivo[MAX_NOME_SAVE + 10];

    if (!obter_nome_save(nome, sizeof nome))
    {
        return;
    }

    sprintf(nomeArquivo, "%s.bin", nome);

    if (arquivo_existe(nomeArquivo))
    {
        if (!confirmar_sobrescrita())
        {
            mostrarMensagem("\nGravacao cancelada.\n");
            pause();
            return;
        }
    }

    if (salvar_geracao_arquivo(mundo, nomeArquivo) == 1 && registrar_nome_save(nome) == 1)
    {
        mostrarMensagem("\nGeracao salva com sucesso!\n");
    }
    else
    {
        mostrarMensagem("\nErro ao salvar a geracao.\n");
    }
    pause();
}

/*
** Lista as geracoes salvas e carrega o arquivo selecionado pelo usuario.
*/
void carregar_geracao_selecao_controller(struct Mundo *mundo)
{
    char nomes[MAX_SAVES][MAX_NOME_SAVE];
    char nomeArquivo[MAX_NOME_SAVE + 10];
    int qtd = listar_saves(nomes, MAX_SAVES);
    int escolha;
    int status;

    limparTela();

    if (qtd == 0)
    {
        mostrarMensagem("\nNenhuma geracao salva encontrada.\n");
        pause();
        return;
    }

    escolha = escolher_save(nomes, qtd);
    if (escolha == -1)
    {
        return;
    }

    sprintf(nomeArquivo, "%s.bin", nomes[escolha]);
    status = carregar_geracao_arquivo(mundo, nomeArquivo);

    if (status == 1)
    {
        mostrarMensagem("\nGeracao carregada com sucesso!\n");
    }
    else
    {
        mostrarMensagem("\nErro ao carregar a geracao selecionada.\n");
    }
    pause();
}

/*
** Carrega a proxima geracao da lista de saves de forma sucessiva,
** voltando para a primeira quando chegar ao final.
*/
void carregar_geracao_sucessiva_controller(struct Mundo *mundo, int *indice)
{
    char nomes[MAX_SAVES][MAX_NOME_SAVE];
    char nomeArquivo[MAX_NOME_SAVE + 10];
    char msg[120];
    int qtd = listar_saves(nomes, MAX_SAVES);
    int status;

    if (qtd == 0)
    {
        mostrarMensagem("\nNenhuma geracao salva encontrada.\n");
        pause();
        return;
    }

    if (*indice >= qtd)
    {
        *indice = 0;
    }

    sprintf(nomeArquivo, "%s.bin", nomes[*indice]);
    status = carregar_geracao_arquivo(mundo, nomeArquivo);

    if (status == 1)
    {
        sprintf(msg, "\nGeracao '%s' (%d/%d) carregada com sucesso!\n", nomes[*indice], *indice + 1, qtd);
        mostrarMensagem(msg);
        (*indice)++;
    }
    else
    {
        mostrarMensagem("\nErro ao carregar a proxima geracao.\n");
    }
    pause();
}