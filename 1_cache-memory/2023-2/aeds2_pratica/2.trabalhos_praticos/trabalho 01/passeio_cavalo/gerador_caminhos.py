import numpy as np
import matplotlib.pyplot as plt

# Ler o arquivo de saída gerado pelo programa C
with open('saida.txt', 'r') as file:
    lines = file.readlines()

# Converter os números do arquivo em uma matriz numpy
matrix = []
for line in lines:
    row = [int(num) for num in line.strip().split()]
    matrix.append(row)
matrix = np.array(matrix)

# Tamanho da matriz
n, m = matrix.shape

# Criar um tabuleiro translúcido para exibir o caminho do cavalo
fig, ax = plt.subplots()
ax.imshow(np.ones((n, m)), cmap='gray', alpha=0.5)

# Cores para os caminhos do cavalo
colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k', 'w']

# Encontrar os caminhos do cavalo
for i in range(1, n * m):
    x, y = np.where(matrix == i)
    ax.plot(y, x, marker='o', color=colors[i % 8], markersize=8)

# Configurar o aspecto da imagem
ax.set_aspect('equal')
plt.gca().invert_yaxis()  # Inverter o eixo Y para coincidir com o tabuleiro

# Exibir o tabuleiro
plt.show()

