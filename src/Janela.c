#include "Janela.h"

struct janela {
    SDL_GLContext* contexto;
    SDL_Window* janela;
    SDL_Event* evento;
    GLint executando;
    GLuint programa;
    GLuint altura;
    GLuint largura;
    GLchar nome[50];
} janela = {NULL, NULL, NULL, 0, 0, 0, 0, "Janela"};

static GLvoid limparJanela(void);
static GLvoid renderizarJanela(void);
static GLvoid criarJanela(int altura, int largura, char* nome);
static GLvoid verificarEventos(void);
static GLvoid deletarJanela(void);
static void* loop(void* varg);
static GLvoid configurarVersaoOpenGL(void);

static struct {
    GLuint largura;
    GLuint altura;
    GLchar* nome;
    Imagem* cores;
} config = {0, 0, NULL, NULL};

/* Iniciar Janela {{{{ */
GLint iniciarJanela(GLuint largura, GLuint altura, GLchar* nome, Imagem* cores) {
    if (janela.executando == 1) {
        return 0;
    }
    config.largura = largura;
    config.altura = altura;
    config.nome = nome;
    config.cores = cores;
    janela.executando = 1;
    pthread_t tid;
    return (!pthread_create(&tid, NULL, loop, (void*) NULL));
}/*}}}}*/
/* Loop {{{{ */
static void* loop(void* varg) {
    criarJanela(config.altura, config.largura, config.nome);
    criarMatriz(config.cores);
    while (janela.executando) {
        limparJanela();
        desenharMatriz();
        verificarEventos();
        renderizarJanela();
    }
    deletarJanela();
    pthread_exit(NULL);
}/*}}}}*/
/* Criar Janela {{{{ */
static GLvoid criarJanela(int altura, int largura, char* nome) {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Não foi possivel inicializar o SDL.\n");
	}

    configurarVersaoOpenGL();

    janela.evento = (SDL_Event*) malloc (sizeof(SDL_Event));
	GLint flags_janela = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
	janela.janela = SDL_CreateWindow (
		nome,
		10,
		10,
		largura,
		altura,
		flags_janela);
    
    janela.contexto = (SDL_GLContext*) malloc (sizeof(SDL_GLContext));
    *(janela.contexto) = SDL_GL_CreateContext(janela.janela);

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK) {
		printf("Não foi possivel inicializar o glew.\n");
	}

	glViewport(0, 0, largura, altura);
	glEnable(GL_DEPTH_TEST);
    janela.executando = 1;
}/*}}}}*/
/* Configurar Versao OpenGL {{{{ */
static GLvoid configurarVersaoOpenGL(void) {
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}/*}}}}*/
/* Renderizar Janela {{{{ */
static GLvoid renderizarJanela(void) {
	SDL_GL_SwapWindow(janela.janela);
}/*}}}}*/
/* Limpar Janela {{{{ */
static GLvoid limparJanela(void) {
	glClearColor(0.0f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}/*}}}}*/
/* Fechar Janela {{{{ */
static GLvoid deletarJanela(void) {
    deletarMatriz();
	SDL_GL_DeleteContext(*(janela.contexto));
	SDL_DestroyWindow(janela.janela);
	SDL_Quit();
    free(janela.contexto);
    free(janela.evento);
}/*}}}}*/
/* Verificar Eventos {{{{ */
static GLvoid verificarEventos(void) {
	while (SDL_PollEvent(janela.evento)) {
		switch (janela.evento->type) {
		case SDL_QUIT:
			janela.executando = 0;
			break;
        case SDL_KEYUP:
            if (janela.evento->key.keysym.sym == SDLK_q) {
                janela.executando = 0;
            }
            break;
        }
    }
}/*}}}}*/
/* Janela Aberta {{{{ */
GLint janelaAberta(void) {
    return janela.executando;
}/*}}}}*/
/* FecharJanela {{{{ */
GLvoid fecharJanela(void) {
    janela.executando = 0;
}/*}}}}*/
