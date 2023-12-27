# Project name
PROJ_NAME=main

# Source directory
SRC_DIR=source

# Directory for binaries
BIN_DIR=bin

# C source files in source directory
C_SOURCE_SOURCE=$(wildcard $(SRC_DIR)/*.c)

# C source files (excluding main.c) in parent directory
C_SOURCE_PARENT=$(filter-out $(SRC_DIR)/main.c, $(wildcard *.c))

# Header files
H_SOURCE=$(wildcard $(SRC_DIR)/*.h)

# Object files for source directory
OBJ_SOURCE=$(addprefix $(BIN_DIR)/, $(notdir $(C_SOURCE_SOURCE:.c=.o)))

# Object files for parent directory
OBJ_PARENT=$(addprefix $(BIN_DIR)/, $(notdir $(C_SOURCE_PARENT:.c=.o))) $(BIN_DIR)/main.o

# Compiler
CC=gcc

# Compiler flags
CC_FLAGS=-Wall -g -pedantic

# Target: all
all: clean compile_source compile_parent

# Target: compile files in source directory
compile_source: $(OBJ_SOURCE) | $(BIN_DIR)

# Target: compile files in parent directory
compile_parent: $(OBJ_PARENT) | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$(PROJ_NAME) $^ -lm

# Target: individual object files in source directory
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(H_SOURCE) | $(BIN_DIR)
	$(CC) -o $@ -c $< $(CC_FLAGS)

# Target: individual object files in parent directory
$(BIN_DIR)/%.o: %.c $(H_SOURCE) | $(BIN_DIR)
	$(CC) -o $@ -c $< $(CC_FLAGS)

# Target: create bin directory if not exists
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Target: clean
clean:
	rm -rf $(BIN_DIR) *~

.PHONY: all compile_source compile_parent clean
