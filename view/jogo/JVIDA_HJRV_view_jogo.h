//JVIDA_HJRV_View - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#ifndef JVIDA_HJRV_VIEW_JOGO_H
#define JVIDA_HJRV_VIEW_JOGO_H

#include "../../model/struct/JVIDA_HJRV_model_struct.h"

void imprimir_mundo(int tamanho, struct Mundo *mundo, int mostrarvizinho);
int obter_tamanho(void);
int obter_posicao(int limite, int tamanho, char entrada[]);
int obter_qtdgeracoes(int tamanho, char entrada[]);
int velocidade_evolucao(struct Mundo *mundo, int tamanho, char entrada[]);//FIX
#endif