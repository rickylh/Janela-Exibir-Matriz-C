#include "Shader.h"

/* Compila um codigo glsl */
static GLvoid compilarShader(GLint programaID, const GLchar* codigo, GLenum tipo);

/* Implementacao da strlen da biblioteca string.h */
static size_t strlen(const char* str);

/* CriarShader {{{{ */
GLint criarShader(GLchar* vertex, GLchar* fragment) {
	int programaID = glCreateProgram();
	if (!programaID) {
		printf("criarShader -> Não foi possivel criar o programa");
	}

	compilarShader(programaID, vertex, GL_VERTEX_SHADER);
	compilarShader(programaID, fragment, GL_FRAGMENT_SHADER);

	GLint sucesso;
	GLchar log[2048] = { 0 };

	glLinkProgram(programaID);
	glGetProgramiv(programaID, GL_LINK_STATUS, &sucesso);

	if (!sucesso) {
		glGetProgramInfoLog(programaID, sizeof(log), NULL, log);
		printf("criarShader -> Não foi possivel linkar o programa: %s\n", log);
	}

	glValidateProgram(programaID);
	glGetProgramiv(programaID, GL_VALIDATE_STATUS, &sucesso);

	if (!sucesso) {
		glGetProgramInfoLog(programaID, sizeof(log), NULL, log);
		printf("criarShader -> Não foi possivel validar o programa: ");
        printf(log);
	}

    return programaID;
}/*}}}}*/

/* CompilarShader {{{{ */
void compilarShader(GLint programaID, const GLchar* codigo, GLenum tipo) {
	GLuint shader = glCreateShader(tipo);
	GLint tamanhoCodigo = (GLint) strlen(codigo);

	glShaderSource(shader, 1, &codigo, &tamanhoCodigo);
	glCompileShader(shader);

	GLint sucesso = GL_FALSE;
	GLchar log[2048] = { 0 };

	glGetShaderiv(shader, GL_COMPILE_STATUS, &sucesso);
	if (!sucesso) {
		glGetShaderInfoLog(shader, 2048, NULL, log);
		printf("compilarShader -> ");
		printf("Nao foi possivel compilar o shader ");
        printf(log);
		printf("\n");
	}

	glAttachShader(programaID, shader);
}/*}}}}*/
/* Strlen {{{{ */
static size_t strlen(const char* str) {
    int tam = 0;
    while(str[tam++] != '\0');
    return tam;
}/*}}}}*/
