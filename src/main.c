#include <stdio.h>
#include <stdlib.h>
#include "Janela.h"

/* Deslisar_para_cima {{{{ */
void deslisar_para_cima (Imagem* img, unsigned int largura, unsigned int altura) { 
    unsigned int i, j;
    GLubyte c1, c2, c3 = 0;
    for (i = 0; i < largura; i++) {
        c1 = img->dados[i][0][0];
        c2 = img->dados[i][0][1];
        c3 = img->dados[i][0][2];
        for (j = 0; j < altura -1; j++) {
            img->dados[i][j][0] = img->dados[i][j+1][0];
            img->dados[i][j][1] = img->dados[i][j+1][1];
            img->dados[i][j][2] = img->dados[i][j+1][2];
        }
        img->dados[i][altura - 1][0] = c1;
        img->dados[i][altura - 1][1] = c2; 
        img->dados[i][altura - 1][2] = c3;
    }
}/*}}}}*/
/* Deslisar_para_direita {{{{ */
void deslisar_para_direita (Imagem* img, unsigned int largura, unsigned int altura) {
    unsigned int i, j;
    GLubyte c1, c2, c3 = 0;
    for (i = 0; i < altura; i++) {
        c1 = img->dados[0][i][0];
        c2 = img->dados[0][i][1];
        c3 = img->dados[0][i][2];
        for (j = 0; j < largura-1; j++) {
            img->dados[j][i][0] = img->dados[j+1][i][0];
            img->dados[j][i][1] = img->dados[j+1][i][1];
            img->dados[j][i][2] = img->dados[j+1][i][2];
        }
        img->dados[largura - 1][i][0] = c1;
        img->dados[largura - 1][i][1] = c2; 
        img->dados[largura - 1][i][2] = c3;
    }
}/*}}}}*/

int main (int argc, char *argv[]) {
    Imagem* img = abrirImagemPGM("imagens_teste/linuxp2.pgm");
    iniciarJanela(img->largura, img->altura, "Janela", img);
    while (janelaAberta()) {
        deslisar_para_direita(img, img->largura, img->altura);
    }
    deletarImagem(img);
  return 0;
}
