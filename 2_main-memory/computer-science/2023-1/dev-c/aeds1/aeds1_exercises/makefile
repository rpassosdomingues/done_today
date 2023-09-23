# Variáveis
CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra -Werror
SRC_DIR = source
BIN_DIR = $(SRC_DIR)/bin
DATA_DIR = $(SRC_DIR)/data
SOURCES := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(filter %.cpp,$(SOURCES))) \
           $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(filter %.c,$(SOURCES)))

# Nome do executável
EXECUTABLE := $(notdir $(CURDIR))

# Regra padrão
all: create_dirs $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c -o $@ $<

# Cria os diretórios "bin" e "data" dentro de "source" se eles não existirem
create_dirs:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(DATA_DIR)

clean:
	rm -rf $(EXECUTABLE) $(BIN_DIR)/*.o

run: $(EXECUTABLE)
	./$<

.PHONY: all clean run create_dirs
