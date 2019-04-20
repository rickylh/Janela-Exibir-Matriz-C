#ifndef __IMAGEM__
#define __IMAGEM__

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

typedef struct imagem {
    unsigned char*** dados;
    unsigned int largura;
    unsigned int altura;
} Imagem;

Imagem* criarImagem(unsigned int largura, unsigned int altura);
void deletarImagem(Imagem* img);
void preecherAleatorio(Imagem* img);
Imagem* abrirImagemPGM(char* path);

#endif /* __IMAGEM__ */
