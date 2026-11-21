//JVIDA_HJRV_Model - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include "JVIDA_HJRV_model_jogo.h"
#include <stdlib.h>

//ponteiros/variaveis globais
//TODO:comentar
celula *pvivo = NULL;
celula *pmorto = NULL;
celula *pvivoprox = NULL;

int totvivo = 0;
int totmorto = 0;
int totvivoprox = 0;

/*
** Inicializa o mundo com celulas vazias, representadas por pontos.
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo a ser inicializado
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
** Verifica se a celula informada possui pelo menos um vizinho vivo,
** sem incluir a propria celula e respeitando os limites do mundo.
** Parametros:
**      mundo - ponteiro para a estrutura do mundo consultado
**      linha - indice da linha da celula, de 0 a tamanho - 1
**      coluna - indice da coluna da celula, de 0 a tamanho - 1
** Retorno:
**      1 se existir pelo menos um vizinho vivo; 0 caso contrario
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
** Conta as celulas vivas e as celulas vizinhas-mortas do mundo.
** Atualiza os campos qtdvivos e qtdmortos da estrutura.
** Parametros:
**      mundo - ponteiro para a estrutura cujo mapa sera percorrido
**              e cujos contadores serao atualizados
*/
void contar_celulas(struct Mundo *mundo)
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
                else if (mundo->celulas[i][j] == '.' && verificar_vizinho(mundo, i, j) == 1) 
                {
                    mundo->qtdmortos++;
                }
            }
        }
    }

/*
** Conta os vizinhos vivos da celula informada, sem incluir a propria
** celula e sem considerar posicoes fora dos limites do mundo.
** Parametros:
**      mundo - ponteiro para a estrutura do mundo consultado
**      linha - indice da linha da celula, de 0 a tamanho - 1
**      coluna - indice da coluna da celula, de 0 a tamanho - 1
** Retorno:
**      quantidade de vizinhos vivos, entre 0 e 8
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
                            if(buscarVivos(i, j) != NULL)
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
void calcular_geracao(struct Mundo *mundo)
    {
        celula *aux;
        int qtd, ant;
        liberarVivosProx();

        aux = pvivo;
        while (aux != NULL)
        {
            qtd = contar_vizinhos(mundo, aux -> linha, aux -> coluna);
            if (qtd == 2 || qtd == 3)
            {
                ant = totvivoprox;
                carregarVivosProx(aux -> linha; aux -> coluna);
                if(totvivoprox != ant + 1)
                {
                    liberarVivosProx();
                    return 0;
                }
            }
            aux = aux -> proximo;
        }

        aux = pmorto;
        while(aux != NULL)
        {
            qtd = contar_vizinhos(mundo, aux -> linha, aux -> coluna);
            if (qtd == 3)
            {
                ant = totvivoprox;
                carregarVivosProx(aux -> linha, aux -> coluna);
                if (totvivoprox != ant + 1)
                {
                    liberarVivosProx();
                    return 0;
                }
            }
            aux = aux -> proximo;
        }

        return 1;
    }

//TODO: comentar
void carregarVivos(int linha, int coluna)
{
    celula *aux;
    aux = (celula*)malloc(sizeof (celula));

    if (aux == NULL)
    {
        return;
    }

    aux -> linha = linha;
    aux -> coluna = coluna;

    if (totvivo == 0)
    {
        pvivo = aux;
        aux -> proximo = NULL;
    }

    else
    {
        aux -> proximo = pvivo;
        pvivo = aux;
    }

    totvivo++;
}

//TODO: comentar
celula *buscarVivos(int linha, int coluna)
{
    celula *aux;
    aux = pvivo;
    while (aux != NULL)
    {
        if((aux -> linha == linha) && (aux -> coluna == coluna))
        {
            return aux;
        }
        
        else
        {
            aux = aux -> proximo;
        }
        
    }
    
    return NULL;
}

//TODO: comentar
void liberarVivos(void)
{
    celula *aux;
    while(pvivo != NULL)
    {
        aux = pvivo;
        pvivo = aux -> proximo;
        free(aux);
        totvivo--;
    }

    pvivo = NULL;
    totvivo = 0;
}


//TODO: comentar
int removerVivos(int linha, int coluna)
{
    celula *atual = pvivo;
    celula *anterior = NULL;

    while(atual != NULL && (atual -> linha != linha || atual -> coluna != coluna))
    {
        anterior = atual;
        atual = atual -> proximo;
    }

    if (atual == NULL)
    {
        return 0;
    } 
    else
    {
        if(anterior == NULL)
        {
            *pvivo = atual -> proximo;
        }
        else
        {
            anterior -> proximo = atual -> proximo;
        }
    }
    totvivo --;
    free(atual);
    return 1;
}

//TODO: comentar
celula *buscarMortos(int linha, int coluna)
{
    celula *aux = pmorto;
    while(aux != NULL)
    {
        if ((aux -> linha == linha) && (aux -> coluna == coluna))
        {
            return aux;
        }
        else
        {
            aux = aux -> proximo;
        }

    }
    return NULL;
}

//TODO; comentar
void liberarMortos(void)
{
    celula *aux;
    while (pmorto != NULL)
    {
        aux = pmorto;
        pmorto = aux -> proximo;
        free(aux);
        totmorto --;
    }
    totmorto = 0;
}


//TODO: comentar
void carregarMortos(int linha, int coluna)
{
    celula *aux;
    aux = (celula*)malloc(sizeof(celula));

    if(aux == NULL)
    {
        return;
    }

    aux -> linha = linha;
    aux -> coluna = coluna;
    aux -> proximo = pmorto;
    pmorto = aux;
    totmorto ++;
}

//TODO: comentar
int atualizarMortos(int tamanho)
{
    celula *aux = pvivo;
    int linha, coluna;
    liberarMortos();
    while (aux != NULL)
    {
        for(linha = aux -> linha - 1; linha <= aux -> linha + 1; linha++)
        {
            for(coluna = aux -> coluna -1; coluna <= aux -> coluna + 1; coluna++)
            {
                if (linha == aux -> linha && coluna == aux -> coluna)
                {
                    continue;
                }

                if(linha < 0 || linha >= tamanho || coluna < 0 || coluna >= tamanho)
                {
                    continue;
                }

                if(buscarVivo(linha, coluna) != NULL)
                {
                    continue;
                }

                if(buscarMortos(linha, coluna) != NULL)
                {
                    continue;
                }

                carregarMortos(linha, coluna);

                if(buscarMortos(linha, coluna) == NULL)
                {
                    liberarMortos();
                    return 0;
                }
            }
        }
        aux = aux -> proximo;
    }

    return 1;
}

//TODO: comentar
celula *obterVivos(void)
{
    return pvivo;
}

celula *obterMortos(void)
{
    return pmorto;
}

//TODO: comentar
void carregarVivosProx(int linha, int coluna)
{
    celula *aux;
    aux = (celula*) malloc(sizeof(celula));

    if (aux == NULL)
    {
        return;
    }

    aux -> linha = linha;
    aux -> coluna = coluna;
    aux -> proximo = pvivoprox;
    pvivoprox = aux;
    totvivoprox++;
}

//TODO: comentar
void liberarVivosProx(int linha, int coluna)
{
    celula *aux;
    while (pvivoprox != NULL)
    {
        aux = pvivoprox;
        pvivoprox = aux -> proximo;
        free(aux);
        totvivoprox--;
    }
    totvivoprox = 0;
}