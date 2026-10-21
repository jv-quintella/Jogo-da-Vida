//JVIDA_HJRV_Main - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares

#include "view/menu/JVIDA_HJRV_view_menu.h"

int main(void)
    {
        int id;

        do{
            id = mostrar_Menu();
        } while (id != 0);
        
        return 0;
    }   
