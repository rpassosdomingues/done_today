import matplotlib.pyplot as plt

# Lista para armazenar os dados da árvore binária desbalanceada
desbalanceada_data = []

# Lista para armazenar os dados da árvore AVL balanceada
balanceada_data = []

# Leitura dos dados da árvore binária desbalanceada
with open("C:/computacao/github/done_today/cache/2023-2/aeds2-pratica/trabalhos-praticos/trabalho2/arvores/arvore_desbalanceada.txt", "r") as arquivo_desbalanceada:
    for linha in arquivo_desbalanceada:
        instancia_num, tempo_execucao = map(float, linha.split())
        desbalanceada_data.append((instancia_num, tempo_execucao))

# Leitura dos dados da árvore AVL balanceada
with open("C:/computacao/github/done_today/cache/2023-2/aeds2-pratica/trabalhos-praticos/trabalho2/arvores/arvore_balanceada.txt", "r") as arquivo_balanceada:
    for linha in arquivo_balanceada:
        instancia_num, tempo_execucao = map(float, linha.split())
        balanceada_data.append((instancia_num, tempo_execucao))

# Separa os dados em listas separadas
instancias_desbalanceada, tempos_desbalanceada = zip(*desbalanceada_data)
instancias_balanceada, tempos_balanceada = zip(*balanceada_data)

# Cria um gráfico de dispersão sobreposto
plt.figure(figsize=(10, 6))
plt.scatter(instancias_desbalanceada, tempos_desbalanceada, label="Árvore Binária Desbalanceada", marker='o', s=20)
plt.scatter(instancias_balanceada, tempos_balanceada, label="Árvore AVL Balanceada", marker='x', s=20)

plt.title("Tempo de Execução vs. Número de Elementos")
plt.xlabel("Número de Elementos")
plt.ylabel("Tempo de Execução (segundos)")
plt.legend()
plt.grid(True)

plt.show()
