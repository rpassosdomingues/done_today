# Define os endereços de memória
LOAD M(1001)  # Carrega o tamanho dos vetores em AC
STOR M(1003)  # Armazena o tamanho em M(1003) (para uso no loop)

# Inicializa os índices e o resultado
LOAD 0  # Inicializa AC com 0 (para uso como índice)
STOR M(1004)  # Armazena o índice do vetor em M(1004)
STOR M(1005)  # Inicializa M(1005) com o endereço de memória onde o resultado será armazenado

LOOP:
    # Carrega os elementos dos vetores para AC
    LOAD M(1004)  # Carrega o índice do vetor
    ADD M(1002)  # Soma o endereço do primeiro vetor
    LOAD M(1004)  # Carrega o índice do vetor
    ADD M(1006)  # Soma o endereço do segundo vetor
    LOAD M(0)  # Carrega o elemento do primeiro vetor
    ADD M(0)  # Soma o elemento do segundo vetor

    # Armazena a soma no vetor de resultado
    STOR M(1005)  # Armazena a soma no resultado

    # Incrementa os índices
    LOAD M(1004)  # Carrega o índice do vetor
    ADD 1  # Incrementa o índice em 1
    STOR M(1004)  # Armazena o novo índice

    # Verifica se chegou ao final dos vetores
    LOAD M(1004)  # Carrega o índice do vetor
    SUB M(1003)  # Subtrai o tamanho dos vetores
    JUMP+ LOOP, 0:19  # Se o índice for menor que o tamanho, continue o loop

# Fim do programa
HALT