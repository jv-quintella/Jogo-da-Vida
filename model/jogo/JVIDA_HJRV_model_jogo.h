//JVIDA_HJRV_Model - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#ifndef JVIDA_HJRV_MODEL_JOGO_H
#define JVIDA_HJRV_MODEL_JOGO_H
#define ARQ_INDICE "saves_index.txt"
#define MAX_SAVES 100
#define MAX_NOME_SAVE 50

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
int salvar_geracao(struct Mundo *mundo, const char *nomeArquivo);
int carregar_geracao(struct Mundo *mundo, const char *nomeArquivo, int *indice);
int arquivo_existe(const char *nomeArquivo);
int registrar_nome_save(const char *nome);
int listar_saves(char nomes[][MAX_NOME_SAVE], int maxSaves);
int salvar_geracao_arquivo(struct Mundo *mundo, const char *nomeArquivo);
int carregar_geracao_arquivo(struct Mundo *mundo, const char *nomeArquivo);
#endif
