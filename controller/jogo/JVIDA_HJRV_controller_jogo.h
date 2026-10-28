//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#ifndef JVIDA_HJRV_CONTROLLER_JOGO_H
#define JVIDA_HJRV_CONTROLLER_JOGO_H

#include "../../model/struct/JVIDA_HJRV_model_struct.h"

void iniciar_simulacao(void);
int mostrar_mortos(int tamanho, char entrada[]);
void colocar_celula(struct Mundo *mundo, int tamanho, char entrada[]);
void limpar_celula(struct Mundo *mundo);
void evoluir_geracoes(struct Mundo *mundo, int mostrarvizinho);

#endif