#include "Imagem.h"

Imagem* criarImagem(int largura, int altura) {
    int i, j;
    Imagem* img = (Imagem*) malloc (sizeof(Imagem));
    img->largura = largura;
    img->altura = altura;
    img->dados = (unsigned char***) malloc (sizeof(char**) * largura);
    for (i = 0; i < largura; i++) {
        img->dados[i] = (unsigned char**) malloc(sizeof(char*) * altura);
        for (j = 0; j < altura; j++) {
            img->dados[i][j] = (unsigned char*) malloc(sizeof(char) * 3);
        }
    }
    return img;
}

void deletarImagem(Imagem* img) {
    int i, j;
    for (i = 0; i < img->largura; i++) {
        for (j = 0; j < img->altura; j++) {
            free (img->dados[i][j]);
        }
        free (img->dados[i]);
    }
    img->altura = 0;
    img->largura = 0;
    free (img->dados);
    free (img);
}
