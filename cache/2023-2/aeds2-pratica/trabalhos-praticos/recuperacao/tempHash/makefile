# Project name
PROJ_NAME=main

# Directory for binaries
BIN_DIR=bin

# Source directory
SRC_DIR=source

# C source files (excluding main.c)
C_SOURCE=$(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))

# Header files
H_SOURCE=$(wildcard $(SRC_DIR)/*.h)

# Object files
OBJ=$(addprefix $(BIN_DIR)/, $(notdir $(C_SOURCE:.c=.o))) $(BIN_DIR)/main.o

# Compiler
CC=gcc

# Compiler flags
CC_FLAGS=-Wall -g -pedantic

# Target: all
all: clean $(BIN_DIR)/$(PROJ_NAME)

# Target: main executable
$(BIN_DIR)/$(PROJ_NAME): $(OBJ) | $(BIN_DIR)
	$(CC) -o $@ $^

# Target: individual object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(H_SOURCE) | $(BIN_DIR)
	$(CC) -o $@ -c $< $(CC_FLAGS)

# Target: create bin directory if not exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Target: clean
clean:
	rm -rf $(BIN_DIR) *~

.PHONY: all clean
