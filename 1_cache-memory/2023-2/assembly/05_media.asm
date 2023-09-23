# Define os endereços de memória
LOAD M(1001)  # Carrega o valor de x em AC
STOR M(1002)  # Armazena o valor de x em M(1002)
LOAD M(1002)  # Carrega o valor de x de M(1002) de volta para AC
SUB 43  # Subtrai 43 de x
JPOS GREATER_THAN_43  # Se o resultado for positivo, vá para a média, caso contrário, vá para a outra expressão

# Calcula (x + y) * z / 2
LOAD M(1002)  # Carrega o valor de x em AC
ADD M(1003)  # Soma o valor de y a AC
MUL M(1004)  # Multiplica o resultado por z
LSH 1  # Divide o resultado por 2 (desloca um bit à esquerda)
STOR M(1005)  # Armazena o resultado em M(1005)
JUMP END_PROGRAM  # Vá para o final do programa

GREATER_THAN_43:
# Calcula a média entre y e z
LOAD M(1003)  # Carrega o valor de y em AC
ADD M(1004)  # Soma o valor de z a AC
DIV 2  # Divide o resultado por 2
STOR M(1005)  # Armazena a média em M(1005)

END_PROGRAM:
# Fim do programa
HALT