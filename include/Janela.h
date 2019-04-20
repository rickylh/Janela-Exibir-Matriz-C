#ifndef __JANELA__
#define __JANELA__

#include "Matriz.h"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_opengl.h> 
#include <pthread.h>

GLvoid iniciarJanela(GLuint largura, GLuint altura, GLchar* nome, Imagem* cores);

GLint janelaAberta();
GLvoid fecharJanela();

#endif
