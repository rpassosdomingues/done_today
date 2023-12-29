# Project name
PROJ_NAME=main

# Source directory
SRC_DIR=source

# Directory for binaries
BIN_DIR=bin

# C source files in source directory
C_SOURCE_SOURCE=$(wildcard $(SRC_DIR)/*.c)

# C source files (excluding main.c) in the parent directory
C_SOURCE_PARENT=$(filter-out $(SRC_DIR)/main.c, $(wildcard *.c))

# Header files
H_SOURCE=$(wildcard $(SRC_DIR)/*.h)

# Object files for the source directory
OBJ_SOURCE=$(addprefix $(BIN_DIR)/, $(notdir $(C_SOURCE_SOURCE:.c=.o)))

# Object files for the parent directory
OBJ_PARENT=$(addprefix $(BIN_DIR)/, $(notdir $(C_SOURCE_PARENT:.c=.o))) $(BIN_DIR)/main.o

# Compiler
CC=gcc

# Compiler flags
CC_FLAGS=-Wall -g -pedantic

# Libsvm library flags
LIBSVM_FLAGS=-L/../../../../usr/lib -lsvm
# FFTW library flags
LIBFFTW_FLAGS=-lfftw3 -lm
# Combined libraries
LIBS=$(LIBFFTW_FLAGS) $(LIBSVM_FLAGS)

# Target: all
all: clean compile_source compile_parent

# Target: compile files in the source directory
compile_source: $(OBJ_SOURCE) | $(BIN_DIR)

# Target: compile files in the parent directory
compile_parent: $(OBJ_PARENT) | $(BIN_DIR)
	$(CC) -o $(BIN_DIR)/$(PROJ_NAME) $^ $(LIBS)

# Target: individual object files in the source directory
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(H_SOURCE) | $(BIN_DIR)
	$(CC) -o $@ -c $< $(CC_FLAGS)

# Target: individual object files in the parent directory
$(BIN_DIR)/%.o: %.c $(H_SOURCE) | $(BIN_DIR)
	$(CC) -o $@ -c $< $(CC_FLAGS)

# Target: create the bin directory if it does not exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Target: clean
clean:
	rm -rf $(BIN_DIR) *~

.PHONY: all compile_source compile_parent clean
