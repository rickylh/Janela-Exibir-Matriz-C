#ifndef __IMAGEM__
#define __IMAGEM__

#include "stdio.h"
#include "stdlib.h"

typedef struct imagem {
    unsigned char*** datos;
    int largura;
    int altura;
} Imagem;

Imagem* criarImagem(int largura, altura);
void deletarImagem(Imagem* img);

#endif
