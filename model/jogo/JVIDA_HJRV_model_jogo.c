//JVIDA_HJRV_Model - Projeto Jogo da Vida LP2026
//24/11/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include "JVIDA_HJRV_model_jogo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//ponteiros/variaveis globais
/*
** Listas encadeadas globais que guardam o estado do jogo:
**      pvivo     - celulas vivas da geracao atual
**      pmorto    - celulas mortas que tem pelo menos um vizinho vivo
**                  (candidatas a nascer na proxima geracao)
**      pvivoprox - celulas vivas da proxima geracao, montada em
**                  calcular_geracao antes de substituir a lista atual
** Contadores globais (um para cada lista):
**      totvivo, totmorto, totvivoprox - quantidade de nos em cada lista
*/
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
** Verifica se existe uma celula viva na regiao de ate nove posicoes
** centrada nas coordenadas informadas, respeitando os limites do mundo.
** A verificacao inclui a propria posicao central.
** Parametros:
**      mundo - ponteiro para a estrutura cuja matriz sera consultada
**      linha - indice da linha da posicao central, de 0 a tamanho - 1
**      coluna - indice da coluna da posicao central, de 0 a tamanho - 1
** Retorno:
**      1 se existir alguma celula viva nessa regiao; 0 caso contrario
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
** Percorre a area ativa da matriz do mundo e atualiza os contadores
** de celulas vivas (qtdvivos) e de celulas vizinhas-mortas (qtdmortos)
** na estrutura do mundo.
** Parametros:
**      mundo - ponteiro para a estrutura do mundo cujos contadores serao atualizados
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
** A consulta e feita na lista encadeada de celulas vivas (pvivo),
** e nao na matriz do mundo.
** Parametros:
**      mundo - ponteiro para a estrutura do mundo consultado (usado
**              apenas para obter o tamanho e validar os limites)
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
                // Validacoes antes de consultar a lista de vivas:
                // (>= 0 e < tamanho) ignora posicoes fora dos limites do mundo.
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
** Calcula a proxima geracao e armazena na lista de vivas da proxima
** geracao (pvivoprox). 
** Parametros:
**      mundo - o ponteiro para a estrutura do mundo atual (usado para
**              obter o tamanho e validar os limites)
** Retorno:
**      1 se a proxima geracao foi calculada com sucesso;
**      0 se houve falha de alocacao (a lista da proxima geracao e liberada)
*/
int calcular_geracao(struct Mundo *mundo)
{
    celula *aux;
    int qtd, ant;
    liberarVivosProx(); // descarta resultado anterior

    // percorre as celulas vivas
    aux = pvivo;
    while (aux != NULL)
    {
        qtd = contar_vizinhos(mundo, aux -> linha, aux -> coluna);
        if (qtd == 2 || qtd == 3)
        {
            // guarda o total anterior para detectar falha do malloc
            ant = totvivoprox;
            carregarVivosProx(aux -> linha, aux -> coluna);
            if(totvivoprox != ant + 1)
            // se nao aumentou em 1, alocacao falhou
            {
                liberarVivosProx();
                return 0;
            }
        }
        aux = aux -> proximo;
    }

    // percorre as vizinhas mortas, nascem as com exatamente 3 vizinhos
    aux = pmorto;
    while(aux != NULL)
    {
        qtd = contar_vizinhos(mundo, aux -> linha, aux -> coluna);
        if (qtd == 3)
        {
            ant = totvivoprox;
            carregarVivosProx(aux -> linha, aux -> coluna);
            if (totvivoprox != ant + 1)
            // mesma checagem da falha de alocacao
            {
                liberarVivosProx();
                return 0;
            }
        }
        aux = aux -> proximo;
    }

    return 1;
}

/*
** Aloca e insere uma nova celula no inicio da lista de vivas (pvivo),
** incrementando totvivo. Nao verifica limites nem coordenadas repetidas.
** Em caso de falha no malloc, retorna sem alterar a lista ou o contador.
** Parametros:
**      linha - indice da linha da celula
**      coluna - indice da coluna da celula
*/
void carregarVivos(int linha, int coluna)
{
    celula *aux;
    aux = (celula*)malloc(sizeof (celula));

    // falha de alocacao nao altera a lista
    if (aux == NULL)
    {
        return;
    }

    aux -> linha = linha;
    aux -> coluna = coluna;

    // lista vazia: novo no e' o unico
    if (totvivo == 0)
    {
        pvivo = aux;
        aux -> proximo = NULL;
    }

    // lista com elemento: insere no inicio
    else
    {
        aux -> proximo = pvivo;
        pvivo = aux;
    }

    totvivo++;
}

/*
** Procura uma celula na lista de vivas (pvivo).
** Parametros:
**      linha - indice da linha procurada
**      coluna - indice da coluna procurada
** Retorno:
**      ponteiro para o no encontrado; NULL se a celula nao esta na lista
*/
celula *buscarVivos(int linha, int coluna)
{
    celula *aux;
    aux = pvivo;
    // percorre ate achar coordenadas ou chegar no fim
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

/*
** Libera todos os nos da lista de vivas (pvivo) e zera o contador.
** Ao final, a lista fica vazia.
*/
void liberarVivos(void)
{
    celula *aux;
    // avanca o ponteiro da cabeca antes de liberar o no, para nao perder o resto da lista
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


/*
** Remove uma celula da lista de vivas (pvivo) e libera sua memoria.
** Parametros:
**      linha - indice da linha da celula a remover
**      coluna - indice da coluna da celula a remover
** Retorno:
**      1 se a celula foi removida; 0 se nao foi encontrada na lista
*/
int removerVivos(int linha, int coluna)
{
    celula *atual = pvivo;
    celula *anterior = NULL; // guarda o no anterior para religar a lista

    // procura o no, lembrando de quem veio antes dele
    while(atual != NULL && (atual -> linha != linha || atual -> coluna != coluna))
    {
        anterior = atual;
        atual = atual -> proximo;
    }

    // chegou ao fim sem achar
    if (atual == NULL)
    {
        return 0;
    } 
    else
    {
        // sem anterior: o no removido e a cabeca, entao a cabeca passa a ser o proximo
        if(anterior == NULL)
        {
            pvivo = atual -> proximo;
        }
        // caso contrario, o anterior "pula" o no removido
        else
        {
            anterior -> proximo = atual -> proximo;
        }
    }
    totvivo --;
    free(atual);
    return 1;
}

/*
** Procura uma celula na lista de mortas (pmorto), que guarda as
** vizinhas-mortas das celulas vivas.
** Parametros:
**      linha - indice da linha procurada
**      coluna - indice da coluna procurada
** Retorno:
**      ponteiro para o no encontrado; NULL se a celula nao esta na lista
*/
celula *buscarMortos(int linha, int coluna)
{
    celula *aux = pmorto;
    // percorre a lista ate achar as coordenadas ou chegar ao fim
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

/*
** Libera todos os nos da lista de mortas (pmorto) e zera o contador.
** Ao final, a lista fica vazia.
*/
void liberarMortos(void)
{
    celula *aux;
    // avanca o ponteiro da cabeca antes de liberar o no, para nao perder o resto da lista
    while (pmorto != NULL)
    {
        aux = pmorto;
        pmorto = aux -> proximo;
        free(aux);
        totmorto --;
    }
    totmorto = 0;
}


/*
** Insere uma nova celula morta no inicio da lista de mortas (pmorto).
** Parametros:
**      linha - indice da linha da celula
**      coluna - indice da coluna da celula
*/
void carregarMortos(int linha, int coluna)
{
    celula *aux;
    aux = (celula*)malloc(sizeof(celula));

    // falha de alocacao: nao altera a lista
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

/*
** Reconstroi a lista de mortas (pmorto) a partir da lista de vivas:
** cada posicao vizinha de uma celula viva que nao seja viva entra na
** lista, sem repeticoes e respeitando os limites do mundo.
** Deve ser chamada sempre que a lista de vivas for alterada.
** Parametros:
**      tamanho - dimensao do mundo, usada para validar os limites
** Retorno:
**      1 se a lista foi montada com sucesso;
**      0 se houve falha de alocacao (a lista de mortas e liberada)
*/
int atualizarMortos(int tamanho)
{
    celula *aux = pvivo;
    int linha, coluna;
    // descarta a lista antiga antes de montar a nova
    liberarMortos();
    // para cada celula viva, examina as 8 posicoes ao redor
    while (aux != NULL)
    {
        for(linha = aux -> linha - 1; linha <= aux -> linha + 1; linha++)
        {
            for(coluna = aux -> coluna -1; coluna <= aux -> coluna + 1; coluna++)
            {
                // ignora a propria celula viva
                if (linha == aux -> linha && coluna == aux -> coluna)
                {
                    continue;
                }

                // ignora posicoes fora do mundo
                if(linha < 0 || linha >= tamanho || coluna < 0 || coluna >= tamanho)
                {
                    continue;
                }

                // ignora posicoes que ja sao celulas vivas
                if(buscarVivos(linha, coluna) != NULL)
                {
                    continue;
                }

                // ignora posicoes que ja estao na lista de mortas
                if(buscarMortos(linha, coluna) != NULL)
                {
                    continue;
                }

                carregarMortos(linha, coluna);

                // se nao foi inserida, o malloc falhou: desfaz tudo e avisa quem chamou
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

/*
** Retorna o ponteiro para o inicio da lista de vivas (pvivo),
** permitindo que outros arquivos percorram a lista sem acessar
** a variavel global diretamente.
*/
celula *obterVivos(void)
{
    return pvivo;
}

/*
** Retorna o ponteiro para o inicio da lista de mortas (pmorto).
*/
celula *obterMortos(void)
{
    return pmorto;
}

/*
** Insere uma celula no inicio da lista de vivas da proxima geracao
** (pvivoprox).
** Parametros:
**      linha - indice da linha da celula
**      coluna - indice da coluna da celula
*/
void carregarVivosProx(int linha, int coluna)
{
    celula *aux;
    aux = (celula*) malloc(sizeof(celula));

    // falha de alocacao: nao altera a lista
    if (aux == NULL)
    {
        return;
    }

    aux -> linha = linha;
    aux -> coluna = coluna;
    // insere no inicio da lista
    aux -> proximo = pvivoprox;
    pvivoprox = aux;
    totvivoprox++;
}

/*
** Libera todos os nos da lista de vivas da proxima geracao (pvivoprox)
** e zera o contador. Ao final, a lista fica vazia.
*/
void liberarVivosProx(void)
{
    celula *aux;
    // avanca o ponteiro da cabeca antes de liberar o no, para nao perder o resto da lista
    while (pvivoprox != NULL)
    {
        aux = pvivoprox;
        pvivoprox = aux -> proximo;
        free(aux);
        totvivoprox--;
    }
    totvivoprox = 0;
}

/*
** Avanca o jogo para a proxima geracao: descarta a lista de vivas atual
** e a substitui pela lista calculada em calcular_geracao.
** Depois da troca, pvivoprox fica vazia. Nao atualiza a lista de mortas
** nem a matriz; use atualizarMortos e atualizarMapa em seguida.
*/
void atualizarVivos(void)
{
    // libera a geracao antiga
    liberarVivos();
    // os nos da proxima geracao passam a ser a lista de vivas (sem copiar)
    pvivo = pvivoprox;
    totvivo = totvivoprox;
    // zera a lista da proxima geracao sem liberar, pois seus nos agora pertencem a pvivo
    pvivoprox = NULL;
    totvivoprox = 0;
}

/*
** Atualiza a area da matriz correspondente ao tamanho do mundo:
** primeiro preenche essa area com '.', depois marca com 'O' as coordenadas
** presentes na lista de celulas vivas. Nao atualiza os contadores.
** Parametros:
**      mundo - ponteiro para a estrutura cuja matriz sera atualizada
*/
void atualizarMapa(struct Mundo *mundo)
{
    celula *aux;
    
    // limpa a matriz inteira
    for (int linha = 0; linha < mundo -> tamanho; linha++)
    {
        for(int coluna = 0; coluna < mundo -> tamanho; coluna++)
        {
            mundo -> celulas[linha][coluna] = '.';
        }
    }
    
    // marca as celulas vivas da lista
    aux = pvivo;
    while(aux != NULL)
    {
       mundo -> celulas[aux -> linha][aux -> coluna] = 'O';
       aux = aux -> proximo; 
    }
}

/*
** Acrescenta a configuracao atual de celulas vivas ao final do arquivo
** binario, preservando os registros anteriores.
** Cada registro contem o tamanho do mundo, totvivo e os pares de inteiros
** (linha, coluna) dos nos da lista pvivo.
** Parametros:
**      mundo - ponteiro para a estrutura que fornece o tamanho do mundo
**      nomeArquivo - caminho/nome do arquivo binario de gravacao
** Retorno:
**      1 se todas as chamadas de fwrite gravaram os elementos solicitados;
**      0 se houver falha na abertura ou em alguma dessas gravacoes
**      O resultado do fechamento do arquivo nao e verificado.
*/
int salvar_geracao(struct Mundo *mundo, const char *nomeArquivo)
{
    FILE *fp;
    celula *aux;
    int coord[2];

    fp = fopen(nomeArquivo, "ab");
    if (fp == NULL)
    {
        return 0;
    }

    if (fwrite(&mundo->tamanho, sizeof(int), 1, fp) != 1 ||
        fwrite(&totvivo, sizeof(int), 1, fp) != 1)
    {
        fclose(fp);
        return 0;
    }

    aux = pvivo;
    while (aux != NULL)
    {
        coord[0] = aux->linha;
        coord[1] = aux->coluna;

        if (fwrite(coord, sizeof(int), 2, fp) != 2)
        {
            fclose(fp);
            return 0;
        }
        aux = aux->proximo;
    }

    fclose(fp);
    return 1;
}

/*
** Tenta abrir o arquivo informado para leitura binaria e o fecha
** quando a abertura e bem-sucedida.
** Parametros:
**      nomeArquivo - caminho/nome do arquivo a consultar
** Retorno:
**      1 se o arquivo puder ser aberto para leitura;
**      0 se a abertura falhar, inclusive por inexistencia ou falta de permissao
*/
int arquivo_existe(const char *nomeArquivo)
{
    FILE *fp = fopen(nomeArquivo, "rb");
    if (fp != NULL)
    {
        fclose(fp);
        return 1;
    }
    return 0;
}

/*
** Consulta ate MAX_SAVES nomes do indice e, se o nome informado nao estiver
** entre eles, acrescenta esse nome ao arquivo ARQ_INDICE.
** Parametros:
**      nome - nome do save a registrar, sem a extensao do arquivo binario
** Retorno:
**      1 se o nome ja foi encontrado ou se o indice foi aberto e a escrita tentada;
**      0 se nao foi possivel abrir o indice para acrescentar o nome
**      Os resultados da escrita e do fechamento nao sao verificados.
*/
int registrar_nome_save(const char *nome)
{
    char nomes[MAX_SAVES][MAX_NOME_SAVE];
    int qtd = listar_saves(nomes, MAX_SAVES);
    int i;
    FILE *fp;

    // Se o nome ja estiver no indice (sobrescrita), nao duplica
    for (i = 0; i < qtd; i++)
    {
        if (strcmp(nomes[i], nome) == 0)
        {
            return 1;
        }
    }

    fp = fopen(ARQ_INDICE, "a");
    if (fp == NULL)
    {
        return 0;
    }

    fprintf(fp, "%s\n", nome);
    fclose(fp);
    return 1;
}

/*
** Le nomes do arquivo de indice, remove as quebras de linha e ignora
** entradas vazias, armazenando no maximo maxSaves nomes.
** Parametros:
**      nomes - matriz de strings que recebera os nomes encontrados
**      maxSaves - quantidade maxima de nomes que podem ser armazenados
** Retorno:
**      quantidade de nomes armazenados;
**      0 se o indice nao puder ser aberto ou nenhum nome for armazenado
*/
int listar_saves(char nomes[][MAX_NOME_SAVE], int maxSaves)
{
    FILE *fp = fopen(ARQ_INDICE, "r");
    int qtd = 0;
    char linha[MAX_NOME_SAVE];

    if (fp == NULL)
    {
        return 0;
    }

    while (qtd < maxSaves && fgets(linha, sizeof linha, fp) != NULL)
    {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (linha[0] != '\0')
        {
            strncpy(nomes[qtd], linha, MAX_NOME_SAVE - 1);
            nomes[qtd][MAX_NOME_SAVE - 1] = '\0';
            qtd++;
        }
    }

    fclose(fp);
    return qtd;
}

/*
** Grava a configuracao atual em um arquivo binario, substituindo
** o conteudo anterior caso o arquivo ja exista.
** Grava o tamanho do mundo, totvivo, os pares de inteiros
** (linha, coluna) dos nos da lista pvivo e o indice geracaoAtual.
** Parametros:
**      mundo - ponteiro para a estrutura que fornece o tamanho, a geracao e o mapa
**      nomeArquivo - caminho/nome do arquivo binario de gravacao
** Retorno:
**      1 se todas as chamadas de fwrite gravaram os elementos solicitados;
**      0 se houver falha na abertura ou em alguma dessas gravacoes
**      O resultado do fechamento do arquivo nao e verificado.
*/
int salvar_geracao_arquivo(struct Mundo *mundo, const char *nomeArquivo)
{
    FILE *fp;
    celula *aux;
    int coord[2];

    fp = fopen(nomeArquivo, "wb");
    if (fp == NULL)
    {
        return 0;
    }

    if (fwrite(&mundo->tamanho, sizeof(int), 1, fp) != 1 ||
        fwrite(&totvivo, sizeof(int), 1, fp) != 1)
    {
        fclose(fp);
        return 0;
    }

    aux = pvivo;
    while (aux != NULL)
    {
        coord[0] = aux->linha;
        coord[1] = aux->coluna;

        if (fwrite(coord, sizeof(int), 2, fp) != 2)
        {
            fclose(fp);
            return 0;
        }
        aux = aux->proximo;
    }

    if (fwrite(&mundo->geracaoAtual, sizeof(int), 1, fp) != 1)
    {
        fclose(fp);
        return 0;
    }

    fclose(fp);
    return 1;
}

/*
** Le uma configuracao do inicio do arquivo binario informado.
** Apos validar o tamanho e a quantidade declarada, libera as tres listas,
** inicializa o mapa e reinicia o contador da geracao atual.
** Insere as coordenadas dentro dos limites, ignorando as demais, e le
** o indice geracaoAtual caso esteja presente no final do arquivo.
** Ao concluir, atualiza a matriz, as vizinhas-mortas e os contadores,
** preservando as configuracoes de quantidade de geracoes, velocidade e intervalo.
** Uma falha apos a limpeza das listas nao restaura a configuracao anterior.
** Parametros:
**      mundo - ponteiro para a estrutura que recebera a configuracao
**      nomeArquivo - caminho/nome do arquivo binario de leitura
** Retorno:
**      1 se o carregamento e a reconstrucao das vizinhas-mortas terminarem;
**      0 se o arquivo nao puder ser aberto;
**     -2 se houver falha de leitura, tamanho fora de 10 a 60,
**        quantidade negativa ou falha de alocacao
*/
int carregar_geracao_arquivo(struct Mundo *mundo, const char *nomeArquivo)
{
    FILE *fp;
    int tamanhoLido;
    int qtdLida;
    int coord[2];
    int i;
    int ant;

    fp = fopen(nomeArquivo, "rb");
    if (fp == NULL)
    {
        return 0;
    }

    if (fread(&tamanhoLido, sizeof(int), 1, fp) != 1 ||
        fread(&qtdLida, sizeof(int), 1, fp) != 1)
    {
        fclose(fp);
        return -2;
    }

    if (tamanhoLido < 10 || tamanhoLido > 60 || qtdLida < 0)
    {
        fclose(fp);
        return -2;
    }

    liberarVivos();
    liberarMortos();
    liberarVivosProx();
    criar_mundo(mundo, tamanhoLido);
    mundo->geracaoAtual = 0;

    for (i = 0; i < qtdLida; i++)
    {
        if (fread(coord, sizeof(int), 2, fp) != 2)
        {
            liberarVivos();
            fclose(fp);
            return -2;
        }

        if (coord[0] >= 0 && coord[0] < tamanhoLido &&
            coord[1] >= 0 && coord[1] < tamanhoLido)
        {
            ant = totvivo;
            carregarVivos(coord[0], coord[1]);
            if (totvivo != ant + 1)
            {
                liberarVivos();
                fclose(fp);
                return -2;
            }
        }
    }

    if (fread(&ant, sizeof(int), 1, fp) == 1)
    {
        if (ant < 0)
        {
            liberarVivos();
            fclose(fp);
            return -2;
        }

        mundo->geracaoAtual = ant;
    }

    fclose(fp);

    atualizarMapa(mundo);
    if (!atualizarMortos(mundo->tamanho))
    {
        return -2;
    }
    contar_celulas(mundo);

    return 1;
}