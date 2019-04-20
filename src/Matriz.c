#include "Matriz.h"

typedef struct matriz {
    GLuint programa;
    GLuint VAO;
    GLuint VBO;
    GLuint altura;
    GLuint largura;
    GLfloat* vbo_data;
    GLuint vbo_tam;
    GLuint numero_pontos;
    Imagem* cores;
} Matriz;

static GLvoid criarBuffers(Matriz* matriz, GLuint largura, GLuint altura);
static GLvoid atualizarCores(Matriz* matriz);
static GLvoid deletarVBO(Matriz* matriz);
static GLvoid criarVBO(Matriz* matriz, GLuint largura, GLuint altura);
static GLvoid atualizarVBO(Matriz* matriz, GLuint largura, GLuint altura);
static GLvoid criarMalhaVBO(Matriz* matriz, GLuint largura, GLuint altura);
static Matriz* matriz;

/* Vertex e Fragment glsl Code {{{{ */
char vertex[] = "                                            \n\
    #version 330                                             \n\
    layout (location = 0) in vec2 posicao;                   \n\
    layout (location = 1) in vec3 corIn;                     \n\
    out vec3 cor;                                            \n\
    void main() {                                            \n\
        gl_Position = vec4(posicao.x, posicao.y, 0.0, 1.0);  \n\
        cor = corIn;                                         \n\
    }                                                        \n";

char fragment [] = \
    "#version 330                                            \n\
    in vec3 cor;                                             \n\
    out vec4 color;                                          \n\
    void main() {                                            \n\
        color = vec4(cor, 1.0);                              \n\
    }                                                        \n";
/*}}}}*/
/* criarMatriz {{{{ */
GLvoid criarMatriz(Imagem* cores) {
    /* Inicializar variaveis */
    matriz = (Matriz*) malloc (sizeof(Matriz));
    matriz->programa = criarShader(vertex, fragment); 
    matriz->VAO = 0;
    matriz->VBO = 0;
    matriz->altura = cores->altura;
    matriz->largura = cores->largura;
    matriz->vbo_data = NULL;
    matriz->vbo_tam = 0;
    matriz->numero_pontos = (matriz->altura + 1) * (matriz->largura + 1);
    matriz->cores = cores;

    criarBuffers(matriz, matriz->largura, matriz->altura);
}/*}}}}*/
/* Deletar Matriz {{{{ */ 
GLvoid deletarMatriz() {
	if (matriz->VAO) {
		glDeleteVertexArrays(1, &(matriz->VAO));
		matriz->VAO = 0;
	}
	if (matriz->VBO) {
        deletarVBO(matriz);
	}

    matriz->programa = 0;
    matriz->VAO = 0;
    matriz->VBO = 0;
    matriz->altura = 0;
    matriz->largura = 0;
    matriz->vbo_data = NULL;
    matriz->vbo_tam = 0;
    matriz->numero_pontos = 0;
    matriz->cores = NULL;
    free (matriz);
    matriz = NULL;
}/*}}}}*/
/* Desenhar {{{{ */
GLvoid desenharMatriz() {
    atualizarCores(matriz);
    glUseProgram(matriz->programa);
    glBindVertexArray(matriz->VAO);

    glDrawArrays(GL_TRIANGLES, 0, matriz->vbo_tam);

    glBindVertexArray(0);
    glUseProgram(0);
}/*}}}}*/

/* Funcoes Auxiliares {{{{ */
/* criar Buffers {{{{ */
static GLvoid criarBuffers(Matriz* matriz, GLuint largura, GLuint altura) {
	glGenVertexArrays(1, &(matriz->VAO));
	glBindVertexArray(matriz->VAO);

    criarVBO(matriz, largura, altura);

	glBindVertexArray(0);
}/*}}}}*/
/* Atualizar Cores {{{{ */
static GLvoid atualizarCores(Matriz* matriz) {
    GLuint x, y, k;
    /* Permite que seja alterado o numero de pixeis durante a execucao */
    if (matriz->largura != matriz->cores->largura || matriz->altura != matriz->cores->altura) {
        atualizarVBO(matriz, matriz->cores->largura, matriz->cores->altura);
    }
    GLuint altura = matriz->altura;
    GLuint largura = matriz->largura;
    GLfloat* vbo = matriz->vbo_data;
    GLubyte*** cores = matriz->cores->dados;

    /* Cada pixel possui 30 vertices, destes 18 para cores */
    for (y = 0; y < 0 + 1 * altura; y++) {
        for (x = 0; x < 0 + 1 *largura; x++) {
            for(k = 0; k < 6; k++) {
                vbo[30 * (y * (largura+1) + x) + 5 * k + 2] = (float)cores[x][y][0] / 255.0f;
                vbo[30 * (y * (largura+1) + x) + 5 * k + 3] = (float)cores[x][y][1] / 255.0f;
                vbo[30 * (y * (largura+1) + x) + 5 * k + 4] = (float)cores[x][y][2] / 255.0f;
            }
        }
    }
    glBindBuffer(GL_ARRAY_BUFFER, matriz->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * matriz->vbo_tam, matriz->vbo_data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}/*}}}}*/
/* Deletar VBO {{{{ */
static GLvoid deletarVBO(Matriz* matriz) {
    glDeleteBuffers(1, &(matriz->VBO));
    free(matriz->vbo_data);
    matriz->VBO = 0;
    matriz->vbo_data = NULL;
}/*}}}}*/
/* Criar VBO {{{{ */
static GLvoid criarVBO(Matriz* matriz, GLuint largura, GLuint altura) {
    criarMalhaVBO(matriz, largura, altura);

	glGenBuffers(1, &(matriz->VBO));
	glBindBuffer(GL_ARRAY_BUFFER, matriz->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * matriz->vbo_tam, matriz->vbo_data, GL_DYNAMIC_DRAW);

    /* Os dois primeiros bytes correspondem a posicao do vertice
     * e os 3 ultimos correspodem a cor do vertice */
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5 , (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5 , (GLvoid*) (2 * sizeof(float)));
	glEnableVertexAttribArray(1);
    
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}/*}}}}*/
/* Criar Malha VBO {{{{ */
static GLvoid criarMalhaVBO(Matriz* matriz, GLuint largura, GLuint altura) {
    GLuint x, k = 0;
    GLint y;
    matriz->vbo_tam = (altura) * (largura + 1) * 30;
    matriz->vbo_data = (GLfloat*) malloc (sizeof(GLfloat) * matriz->vbo_tam);
    matriz->largura = largura;
    matriz->altura = altura;

    GLfloat delta_x = 2.0f / (GLfloat)matriz->largura;
    GLfloat delta_y = 2.0f / (GLfloat)matriz->altura;
    for (y = (int)matriz->altura-1; y >= 0; y--) {
        for (x = 0; x <= matriz->largura; x++) {
            matriz->vbo_data[k++] = x * delta_x - 1.0f;
            matriz->vbo_data[k++] = y * delta_y - 1.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 1.0f;
            matriz->vbo_data[k++] = 0.0f;
            
            matriz->vbo_data[k++] = (x + 1) * delta_x - 1.0f;
            matriz->vbo_data[k++] = y * delta_y - 1.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;

            matriz->vbo_data[k++] = x * delta_x - 1.0f;
            matriz->vbo_data[k++] = (y + 1) * delta_y - 1.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;

            matriz->vbo_data[k++] = x * delta_x - 1.0f;
            matriz->vbo_data[k++] = (y + 1) * delta_y - 1.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;

            matriz->vbo_data[k++] = (x + 1) * delta_x - 1.0f;
            matriz->vbo_data[k++] = y * delta_y - 1.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;

            matriz->vbo_data[k++] = (x + 1) * delta_x - 1.0f;
            matriz->vbo_data[k++] = (y + 1) * delta_y - 1.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;
            matriz->vbo_data[k++] = 0.0f;
        }
    }
}/*}}}}*/
/* Atualizar VBO {{{{ */
static GLvoid atualizarVBO(Matriz* matriz, GLuint largura, GLuint altura) {
    criarMalhaVBO(matriz, largura, altura);
    glBindBuffer(GL_ARRAY_BUFFER, matriz->VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * matriz->vbo_tam, matriz->vbo_data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}/*}}}}*/
/*}}}}*/
