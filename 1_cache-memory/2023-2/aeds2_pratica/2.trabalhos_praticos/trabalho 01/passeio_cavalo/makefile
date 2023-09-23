# Automatizando o makefile

# Nome do projeto
PROJ_NAME=passeio

# Arquivos .c
C_SOURCE=$(wildcard *.c)

# Arquivos .h
H_SOURCE=$(wildcard *.h)

# Arquivos objeto
OBJ=$(C_SOURCE:.c=.o)

# Compilador
CC=gcc

# Flags (opções) para o compilador
CC_FLAGS=-c         \
         -Wall      \
         -g         \
         -pedantic

# Comando para executar o Python após a compilação
RUN_PYTHON=python gerador_caminhos.py

#########################
# Compilação e linkagem #
#########################
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^

%.o: %.c %.h
	$(CC) -o $@ $< $(CC_FLAGS)

main.o: main.c $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)

run: all
	$(RUN_PYTHON)

clean:
	rm -rf *.o $(PROJ_NAME) *~

