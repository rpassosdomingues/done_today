# Define os endereços de memória
LOAD 1001, NUM1     # Carrega o primeiro número em 1001
LOAD 1002, NUM2     # Carrega o segundo número em 1002
LOAD 1003, ACC      # Inicializa o acumulador com 0 (para armazenar o resultado)

# Inicializa o contador em 0
LOAD 1004, COUNT
CLEAR COUNT, COUNT

# Loop de multiplicação
LOOP:   ADD NUM1, ACC, ACC   # Adiciona NUM1 ao acumulador
        ADD -1, COUNT, COUNT  # Decrementa o contador em 1
        JZRO COUNT, 10        # Se o contador for zero, vá para o endereço 10
        JMP LOOP              # Volte para o início do loop

# Armazena o resultado na memória
STORE ACC, 1005

# Fim do programa
HALT

# Definição de dados
NUM1:   DAT 5
NUM2:   DAT 10
COUNT:  DAT 0
