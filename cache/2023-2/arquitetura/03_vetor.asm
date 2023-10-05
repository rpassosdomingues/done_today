LOAD MQ     # Inicializa MQ com 0
LOAD - |M(1001)|     # Carrega o negativo do escalar para o AC
STOR M(1002)     # Inicializa M(1002) com o endereço do vetor
LOAD MQ     # Inicializa MQ com 0
LOAD M(1004)     # Carrega o tamanho do vetor para o AC
STOR M(1005)     # Armazena o tamanho do vetor em M(1005)
LOAD MQ     # Inicializa MQ com 0
LOAD 1     # Inicializa AC com 1 (para multiplicação ou soma)
STOR M(1006)     # Armazena o índice/multiplicador em M(1006)

LOOP:
    LOAD |M(1002)|     # Carrega o valor absoluto do vetor para o AC

    # Verifica o sinal do escalar
    JNEG SUM     # Se o escalar for negativo, vá para a soma
    JUMP MULTIPLY     # Caso contrário, vá para a multiplicação

SUM:
    ADD |M(1002)|     # Soma o valor absoluto do vetor ao AC
    JUMP CONTINUE

MULTIPLY:
    MUL |M(1002)|     # Multiplica o valor absoluto do vetor por MQ
    JUMP CONTINUE

CONTINUE:
    LOAD M(1006)     # Carrega o índice/multiplicador
    ADD 1     # Incrementa o índice/multiplicador em 1
    STOR M(1006)     # Armazena o novo índice/multiplicador
    LOAD M(1006)     # Carrega o índice/multiplicador
    SUB M(1005)     # Subtrai o tamanho do vetor do índice/multiplicador
    JUMP+ LOOP, 0:19     # Se o índice/multiplicador for menor que o tamanho do vetor, continue o loop

STOR M(1003)     # Armazena o resultado na memória
HALT     # Fim do programa
