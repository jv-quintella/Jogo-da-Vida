//JVIDA_HJRV_Controller - Projeto Jogo da Vida LP2026
//24/11/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#ifndef JVIDA_HJRV_CONTROLLER_JOGO_H
#define JVIDA_HJRV_CONTROLLER_JOGO_H

#include "../../model/struct/JVIDA_HJRV_model_struct.h"

void iniciar_simulacao(void);
void menu_regras(void);
void menu_simulacao(struct Mundo *mundo, int *mostrarvizinho);
void configurar_simulacao(struct Mundo *mundo, int *mostrarvizinho);
int mostrar_mortos(int tamanho, char entrada[]);
void colocar_celula(struct Mundo *mundo, int tamanho, char entrada[], int mostrarvizinho);
void limpar_mapa(struct Mundo *mundo);
void evoluir_geracoes(struct Mundo *mundo, int mostrarvizinho);
void salvar_geracao_controller(struct Mundo *mundo);
void carregar_geracao_selecao_controller(struct Mundo *mundo);
void carregar_geracao_sucessiva_controller(struct Mundo *mundo, int *indice);
void opcoes_carregamento(struct Mundo *mundo, int *mostrarvizinho);
    
#endif