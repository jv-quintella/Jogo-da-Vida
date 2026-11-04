//JVIDA_HJRV_Model - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#ifndef JVIDA_HJRV_MODEL_STRUCT_H
#define JVIDA_HJRV_MODEL_STRUCT_H

struct Mundo {
    char celulas[60][60];
    int tamanho;
    int qtdvivos;
    int qtdmortos;
    int qtdgeracoes;
    int geracaoAtual;
    int velocidade;
};

#endif