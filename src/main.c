#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <pthread.h>
#include <time.h>
#include "Imagem.h"

int main(int argc, char** argv) {
    printf("Criando imagem\n");
    Imagem* img = criarImagem(100, 100);
    printf("Deletando imagem\n");
    deletarImagem(img);
    printf("Concluido\n");
    return 0;
}
