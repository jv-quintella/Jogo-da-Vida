//JVIDA_HJRV_Model - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#ifndef JVIDA_HJRV_MODEL_JOGO_H
#define JVIDA_HJRV_MODEL_JOGO_H

#include "../struct/JVIDA_HJRV_model_struct.h"

void criar_mundo(struct Mundo *mundo, int tamanho);
int verificar_vizinho(struct Mundo *mundo, int linha, int coluna);
int contar_celulas(struct Mundo *mundo, int qtdvivos, int qtdmortos);

#endif
