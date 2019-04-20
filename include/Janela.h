/*============================================================================*/
/* Janela para exibir uma matriz (imagem)                                     */
/*----------------------------------------------------------------------------*/
/* Autor: Ricky Lemes Habegger                                                */
/*============================================================================*/
/** Biblioteca para exibir uma matriz em uma janela
 * 
 * Nota: Essa biblioteca funciona com imagens que possuam boa resolução, mas
 *  ela foi desenvolvida com foco em imagens em torno de 100x100, normalmente 
 *  derivadas de jogos para console                                           */
/*============================================================================*/

#ifndef __JANELA__
#define __JANELA__
#include "Matriz.h"
#include <SDL2/SDL.h> 
#include <SDL2/SDL_opengl.h> 
#include <pthread.h>

/*============================================================================*/
/* Janela                                                                     */
/*============================================================================*/
/** Inicia a Janela
 *
 * Parâmetros: largura: largura da janela
 *             altura: altura da janela
 *             nome: nome exibido acima da janel
 *             cores: imagem que se deseja desenhar, ela será utilizada
 *                    até a janela ser fechada.
 *
 * Valor de retorno: 1 se foi iniciado a thread da janela com sucesso e
 *                   0 caso ocorreu um erro ou a janela ja foi iniciada */
GLint iniciarJanela(GLuint largura, GLuint altura, GLchar* nome, Imagem* cores);


/*============================================================================*/
/** Verifica se a janela ainda esta aberta
 *
 * Parâmetros: nenhum
 *
 * Valor de retorno: 1 se a janela está aberta e 0 do contrário */
GLint janelaAberta(void);


/*============================================================================*/
/** Fecha a Janela
 *
 * Parâmetros: nenhum
 *
 * Valor de retorno: nenhum */
GLvoid fecharJanela(void); 

#endif
