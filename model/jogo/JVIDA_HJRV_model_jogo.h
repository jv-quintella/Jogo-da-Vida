//JVIDA_HJRV_Model - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#ifndef JVIDA_HJRV_MODEL_JOGO_H
#define JVIDA_HJRV_MODEL_JOGO_H

#include "../struct/JVIDA_HJRV_model_struct.h"

void criar_mundo(struct Mundo *mundo, int tamanho);
int verificar_vizinho(struct Mundo *mundo, int linha, int coluna);
void contar_celulas(struct Mundo *mundo);
int contar_vizinhos(struct Mundo *mundo, int linha, int coluna);
int calcular_geracao(struct Mundo *mundo);
void carregarVivos(int linha, int coluna);
celula *buscarVivos(int linha, int coluna);
void liberarVivos(void);
int removerVivos(int linha, int coluna);
celula *buscarMortos(int linha, int coluna);
void liberarMortos(void);
int atualizarMortos(int tamanho);
void carregarMortos(int linha, int coluna);
celula *obterVivos(void);
celula *obterMortos(void);
void carregarVivosProx(int linha, int coluna);
void liberarVivosProx(void);
void atualizarVivos(void);
void atualizarMapa(struct Mundo *mundo);
#endif
