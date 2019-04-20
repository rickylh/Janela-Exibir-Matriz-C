#include "Imagem.h"

Imagem* criarImagem(unsigned int largura, unsigned int altura) {
    unsigned int i, j;
    Imagem* img = (Imagem*) malloc (sizeof(Imagem));
    img->largura = largura;
    img->altura = altura;
    img->dados = (unsigned char***) malloc (sizeof(char**) * largura);
    for (i = 0; i < largura; i++) {
        img->dados[i] = (unsigned char**) malloc(sizeof(char*) * altura);
        for (j = 0; j < altura; j++) {
            img->dados[i][j] = (unsigned char*) malloc(sizeof(char) * 3);
            img->dados[i][j][0] = 100;
            img->dados[i][j][1] = 100;
            img->dados[i][j][2] = 100;
        }
    }
    return img;
}

void deletarImagem(Imagem* img) {
    unsigned int i, j;
    for (i = 0; i < img->largura; i++) {
        for (j = 0; j < img->altura; j++) {
            free (img->dados[i][j]);
        }
        free (img->dados[i]);
    }
    img->altura = 0;
    img->largura = 0;
    img->dados = NULL;
    free (img->dados);
    free (img);
}

void preecherAleatorio(Imagem* img) {
    unsigned int i, j, k;
    srand(time(NULL));
    for (i = 0; i < img->largura; i++) {
        for (j = 0; j < img->altura; j++) {
            for (k = 0; k < 3; k++) {
                img->dados[i][j][k] = rand() % 255;
            }
        }
    }
}
