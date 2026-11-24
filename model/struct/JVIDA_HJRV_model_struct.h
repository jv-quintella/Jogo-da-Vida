//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//24/11/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#ifndef JVIDA_HJRV_MODEL_STRUCT_H
#define JVIDA_HJRV_MODEL_STRUCT_H
/*
** Estrutura que representa o mundo do jogo.
** Campos:
**      celulas - matriz do mapa ('O' = viva, '.' = morta), com capacidade maxima de 60x60
**      tamanho - dimensao usada da matriz quadrada (tamanho x tamanho), ate 60
**      qtdvivos - quantidade de celulas vivas (atualizada em contar_celulas)
**      qtdmortos - quantidade de vizinhas-mortas, ou seja, celulas mortas com
**                  pelo menos um vizinho vivo (atualizada em contar_celulas)
**      qtdgeracoes - quantidade de geracoes a simular
**      geracaoAtual - numero da geracao em exibicao; volta para 0 quando o usuario
**                     adiciona ou remove celulas manualmente
**      velocidade - velocidade da simulacao escolhida pelo usuario
**      intervalo - quantidade de geracoes por vez
*/
struct Mundo {
    char celulas[60][60];
    int tamanho;
    int qtdvivos;
    int qtdmortos;
    int qtdgeracoes;
    int geracaoAtual;
    int velocidade;
    int intervalo;
};

/*
** No de uma lista ligada simples de celulas, usado nas listas de vivas,
** mortas e de vivas da proxima geracao.
** Campos:
**      linha - indice da linha da celula na matriz
**      coluna - indice da coluna da celula na matriz
**      proximo - ponteiro para o proximo no da lista; NULL no ultimo no
*/
typedef struct Celula {
    int linha;
    int coluna;
    struct Celula *proximo;
} celula;

#endif