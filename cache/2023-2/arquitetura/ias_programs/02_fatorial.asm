# Define os endereços de memória
LOAD MQ    # Inicializa MQ com 0
LOAD - |M(1001)|  # Carrega -|M(1001)| para o AC (caso o número seja negativo)
STOR M(1002)  # Inicializa M(1002) com o endereço de memória onde o resultado será armazenado
LOAD MQ    # Inicializa MQ com 0

# Inicializa o contador em 1 (para a fatorial)
LOAD |M(1003)|  # Carrega |M(1003)| (valor absoluto do número) para o AC

# Loop de cálculo da fatorial
LOOP:
    MUL M(1002)  # Multiplica M(1002) por MQ; coloca os bits mais significativos do resultado em AC
    STOR M(1002)  # Armazena o resultado parcial em M(1002)

    # Verifica se o contador é zero
    MUL M(1003)  # Multiplica o contador por MQ
    LOAD |M(1003)|  # Carrega |M(1003)| novamente

    # Se o contador for zero, encerra o loop
    JUMP+ LOOP, 0:19  # Se o valor no AC for não negativo, continue o loop

# Armazena o resultado da fatorial em M(1002)
STOR M(1002)

# Fim do programa
HALT

# Definição de dados
DAT -5  # Número inteiro a ser fornecido como entrada (substitua pelo número desejado)
DAT 0   # Local de armazenamento temporário para a fatorial
DAT 0   # Local de armazenamento temporário para o número absoluto
