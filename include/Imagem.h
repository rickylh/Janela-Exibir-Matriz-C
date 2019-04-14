#ifndef __IMAGEM__
#define __IMAGEM__

#include "stdio.h"
#include "stdlib.h"

typedef struct imagem {
    unsigned char*** dados;
    int largura;
    int altura;
} Imagem;

Imagem* criarImagem(int largura, int altura);
void deletarImagem(Imagem* img);

#endif
