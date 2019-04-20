# **********************************************
# * Makefile para programas escritos em C     **
# * Utilizando SDL2 e OpenGL                  **
# *                                           **
# *  Autor: Ricky Lemes Habegger              **
# *                                           **
# **********************************************
# ==============================================

#-----------------------------------------------
#----              Variaveis                ----
#-----------------------------------------------

# Nome do projeto
NOME_PROJ=Janela
SOURCE_DIR=./src
INCLUDE_DIR=./include
LIB_DIR=./lib
OBJ_DIR=./objetos

# Arquivos fonte
C_SOURCE=$(wildcard $(SOURCE_DIR)/*.c)

# Arquivo headers
H_SOURCE=$(wildcard $(INCLUDE_DIR)/*.h)

# Objetos que serão gerados
OBJ=$(subst .c,.o,$(subst $(SOURCE_DIR),$(OBJ_DIR), $(subst $(SOURCE_DIR)/main.c,,$(C_SOURCE))))

FLAGS=-lSDL2  		\
      -lGL 			\
      -lGLEW 		\
	  -lpthread

# Compilador
CC=gcc
INCLUDE="include"

# Flags para o compilador
CC_FLAGS=-c                     \
		 -O                     \
         -Wall                  \
         -Wextra                \
         -pedantic-errors       \
         -pedantic              \
         -std=c99

# Comando para apagar arquivo não nescessarios
RM = rm -rf

#-----------------------------------------------
#----       Targets de Compilação           ----
#-----------------------------------------------

# Criar os objetos e executavel
all: diretorios $(NOME_PROJ)
	@ echo "\e[01mArquivo binario criado: \e[01;04;32m$(NOME_PROJ)\e[00m"

# linkar os objetos e gerar o executavel
$(NOME_PROJ): $(OBJ) $(OBJ_DIR)/main.o
	@ echo " "
	@ echo "\e[01mCriando arquivo binario:\e[01;32m $@ \e[00m"
	@ $(CC) $(FLAGS) $^ -o $@

# Compilar todas as sources
$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.c $(INCLUDE_DIR)/%.h
	@ echo "Compilando: \e[00;31m $< \e[00m"
	@ $(CC) $< $(CC_FLAGS) -o $@ -I $(INCLUDE)

# Compilar a main
$(OBJ_DIR)/main.o: $(SOURCE_DIR)/main.c $(H_SOURCE)
	@ echo "Compilando: \e[00;31m $< \e[00m"
	@ $(CC) $< $(CC_FLAGS) -o $@ -I $(INCLUDE)

diretorios:
	@ mkdir -p $(OBJ_DIR) $(LIB_DIR)

# Remover os objetos gerados na compilacao
clean:
	@ $(RM) $(NOME_PROJ) $(OBJ_DIR)/*  $(LIB_DIR)/* *~
	@ rmdir --ignore-fail-on-non-empty $(OBJ_DIR) $(LIB_DIR)

lib: diretorios $(OBJ)
	@ echo "\e[01mCriando biblioteca estática:\e[01;32m $(NOME_PROJ) \e[00m"
	@ ar -rcs $(LIB_DIR)/lib$(NOME_PROJ).a $(OBJ)
	@ echo "\e[01mBiblioteca estática criada: \e[01;04;32m$(NOME_PROJ)\e[00m"

# Recompilar o programa do inicio
rebuild: clean all

install: lib
	@ sudo cp -p $(LIB_DIR)/lib$(NOME_PROJ).a /usr/local/lib/
	@ sudo mkdir -p /usr/local/include/$(NOME_PROJ)
	@ sudo cp -p -r $(INCLUDE_DIR)/* /usr/local/include/$(NOME_PROJ)/
	@ sudo ldconfig
	@ echo "\e[01m\e[01;04;32m$(NOME_PROJ)\e[01;0m instalada.\e[00m"

uninstall:
	@ sudo rm /usr/local/lib/lib$(NOME_PROJ).a
	@ sudo rm /usr/local/include/$(NOME_PROJ)/*
	@ sudo rmdir --ignore-fail-on-non-empty /usr/local/include/$(NOME_PROJ)
	@ sudo ldconfig
	@ echo "\e[01m\e[01;04;32m$(NOME_PROJ)\e[01;0m removida.\e[00m"

# Gerar o executavel e executar
run: all
	@ ./$(NOME_PROJ) 

# Evita ambiguidade com arquivo da source
.PHONY: all clean

# Variaveis internas
# $@    Nome da regra. 
# $<    Nome da primeira dependência 
# $^ 	Lista de dependências
# $? 	Lista de dependências mais recentes que a regra.
# $* 	Nome do arquivo sem sufixo
