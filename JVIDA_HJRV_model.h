//JVIDA_HJRV_Model - Projeto Jogo da Vida LP2026
//30/09/2026
//Hellen Araujo da Silva, João Vitor Carvalho Magalhaes Quintella, Rodrigo Corio Ferrer dos Santos, Victoria Spina Tavares


struct Mundo {
     char celulas[60][60];
    int tamanho;
};

void criar_mundo(struct Mundo *mundo, int tamanho);