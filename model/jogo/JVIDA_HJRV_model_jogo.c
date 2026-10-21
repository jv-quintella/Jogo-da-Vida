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

/*
** Conta as celulas vivas e, quando solicitado, as celulas mortas com vizinhos vivos.
** Atualiza os campos qtdvivos e qtdmortos da estrutura do mundo.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      mostrarvizinho - indica se as celulas mortas com vizinhos vivos devem ser contadas (1 para contar)
*/
void contar_celulas(struct Mundo *mundo, int mostrarvizinho)
    {
        mundo->qtdvivos = 0;
        mundo->qtdmortos = 0;

        for (int i = 0; i < mundo->tamanho; i++)
        {
            for (int j = 0; j < mundo->tamanho; j++)
            {
                if (mundo->celulas[i][j] == 'O')
                {
                    mundo->qtdvivos++;
                }
                else if (mundo->celulas[i][j] == '.' && verificar_vizinho(mundo, i, j) == 1 && mostrarvizinho == 1) 
                {
                    mundo->qtdmortos++;
                }
            }
        }
    }

/*
** Conta os vizinhos vivos de uma celula, sem incluir a propria celula.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo
**      linha - a linha da celula a ser verificada
**      coluna - a coluna da celula a ser verificada
*/
int contar_vizinhos(struct Mundo *mundo, int linha, int coluna)
    {
        int count = 0;
        for(int i = linha -1; i <= linha + 1; i++)
            {
                for(int j = coluna - 1; j <= coluna + 1; j++)
                {
                    // Validacoes antes de acessar a matriz:
                    // (>= 0 e < tamanho) impede acesso a lixo de memoria.
                    // (i != linha || j != coluna) garante que a celula nao conte a si mesma.
                    if((i >= 0 && i < mundo-> tamanho) && (j >= 0 && j < mundo -> tamanho) && (i != linha || j != coluna))
                        {
                            // Verifica se a posicao vizinha valida contem o caractere de celula viva
                            if(mundo-> celulas[i][j] == 'O')
                                {
                                    count++;
                                }
                        }
                }
            }
        return count;
    }

/*
** Calcula a proxima geracao e armazena no mundo auxiliar.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo atual (leitura)
**      mundo_auxiliar - o ponteiro para a estrutura do mundo futuro (escrita)
*/
void calcular_geracao(struct Mundo *mundo, struct Mundo *mundo_auxiliar)
    {
        for(int i = 0; i < mundo -> tamanho; i++)
            {
                for(int j = 0; j < mundo -> tamanho; j++)
                    {
                        // Obtem a quantidade exata de vizinhos vivos da celula atual
                        int qtd = contar_vizinhos(mundo, i, j);
                        // Celula viva com 2 ou 3 vizinhos continua viva
                        if(mundo -> celulas[i][j] == 'O' && (qtd == 2 || qtd == 3))
                            {
                                mundo_auxiliar -> celulas[i][j] = 'O';
                            }
                        // Celula morta com exatamente 3 vizinhos nasce
                        else if (mundo -> celulas[i][j] == '.' && qtd == 3)
                            {
                                    mundo_auxiliar -> celulas[i][j] = 'O';
                            }
                        // Morte por solidao (0 ou 1) ou superpopulacao (4 ou mais)   
                        else
                            {
                                mundo_auxiliar -> celulas[i][j] = '.';
                            }
                        

                    }
            }
    }