//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//24/11/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#ifndef JVIDA_HJRV_VIEW_JOGO_H
#define JVIDA_HJRV_VIEW_JOGO_H

#include "../../model/struct/JVIDA_HJRV_model_struct.h"

void imprimir_mundo(int tamanho, struct Mundo *mundo, int mostrarvizinho);
int obter_tamanho(void);
int obter_posicao(int limite, int tamanho, char entrada[]);
int obter_qtdgeracoes(int tamanho, char entrada[]);
int obter_velocidade(int tamanho, char entrada[]);
int obter_coordenada(int limite, int tamanho, char entrada[], int *linha, int *coluna);
void mostrar_configuracoes(struct Mundo *mundo, int mostrarvizinho);
void mostrar_regra(int topico);
int obter_intervalo(int tamanho, char entrada[]);
void imprimir_lista(const celula *lista);
int obter_nome_save(char nome[], int tamanho);
int confirmar_sobrescrita(void);
int escolher_save(char nomes[][50], int qtd);
#endif