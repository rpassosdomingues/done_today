import matplotlib.pyplot as plt
import random

# Classe Cache representa uma memória cache
class Cache:
    def __init__(self, size, associativity, block_size):
        # Inicializa a cache com o tamanho, associatividade e tamanho do bloco especificados
        self.size = size
        self.associativity = associativity
        self.block_size = block_size
        self.blocks = size // block_size
        self.data = [None] * self.blocks  # Cada bloco é inicializado como vazio

    def read(self, address):
        # Simula a operação de leitura da cache (não lidamos com dados específicos neste exemplo)
        # Retorna True se o endereço estiver na cache (hit), False caso contrário (miss)
        pass

    def write(self, address, data):
        # Simula a operação de escrita na cache (usaremos dados fictícios)
        # O bloco correspondente ao endereço é atualizado com os dados fornecidos
        block_index = address // self.block_size
        self.data[block_index] = data

# Classe CacheSimulator é responsável por simular o comportamento da cache
class CacheSimulator:
    def __init(self, cache):
        self.cache = cache
        self.hit_rates = []  # Lista para armazenar as taxas de acerto
        self.memory_sizes = []  # Lista para armazenar os tamanhos de memória simulados

    def simulate(self, program, memory_size):
        hits = 0
        misses = 0

        for address in program:
            if self.cache.read(address):
                hits += 1
            else:
                data = random.randint(1, 1000)  # Dados fictícios para escrita
                self.cache.write(address, data)
                misses += 1

        hit_rate = hits / (hits + misses)

        self.hit_rates.append(hit_rate)
        self.memory_sizes.append(memory_size)

# Função para plotar gráficos
def plot_graphs(memory_sizes, avg_memory_costs, efficiency_access, hit_rates_vs_memory_sizes):
    # 1. Relacionamento do custo de memória médio com tamanho de memória relativo
    plt.figure(1)
    plt.plot(memory_sizes, avg_memory_costs, marker='o', linestyle='-')
    plt.xlabel('Tamanho de Memória Relativo')
    plt.ylabel('Custo de Memória Médio')
    plt.title('Custo de Memória Médio x Tamanho de Memória Relativo')

    # 2. Eficiência de acesso como uma função da taxa de acerto (r = T2/T1)
    plt.figure(2)
    plt.plot(efficiency_access, hit_rates_vs_memory_sizes, marker='o', linestyle='-')
    plt.xlabel('Eficiência de Acesso (r = T2/T1)')
    plt.ylabel('Taxa de Acerto (T1)')
    plt.title('Eficiência de Acesso x Taxa de Acerto')

    # 3. Razão de acerto como uma função do tamanho de memória relativo
    plt.figure(3)
    plt.plot(memory_sizes, hit_rates_vs_memory_sizes, marker='o', linestyle='-')
    plt.xlabel('Tamanho de Memória Relativo')
    plt.ylabel('Taxa de Acerto (T1)')
    plt.title('Razão de Acerto x Tamanho de Memória Relativo')

    # 4. Razão de acerto como uma função do tamanho de memória relativo (mesmo gráfico)
    plt.figure(4)
    plt.plot(memory_sizes, hit_rates_vs_memory_sizes, marker='o', linestyle='-')
    plt.xlabel('Tamanho de Memória Relativo')
    plt.ylabel('Taxa de Acerto (T1)')
    plt.title('Razão de Acerto x Tamanho de Memória Relativo')

    plt.show()

def amdahl_law_speedup(fraction_parallel, num_processors):
    # Função para calcular o speedup baseado na Lei de Amdahl
    speedup = 1 / ((1 - fraction_parallel) + fraction_parallel / num_processors)
    return speedup

if __name__ == "__main__":
    cache_size = 8192  # Tamanho da cache
    associativity = 4  # Associatividade da cache
    block_size = 64  # Tamanho do bloco
    program = [0x100, 0x200, 0x300, 0x400, 0x100, 0x500, 0x200, 0x600]  # Programa de acesso à memória
    memory_sizes = [1024, 2048, 4096, 8192, 16384]  # Tamanhos de memória para simulação

    avg_memory_costs = []  # Lista para armazenar os custos médios de memória
    efficiency_access = []  # Lista para armazenar a eficiência de acesso
    hit_rates_vs_memory_sizes = []  # Lista para armazenar as taxas de acerto

    for memory_size in memory_sizes:
        cache = Cache(cache_size, associativity, block_size)
        simulator = CacheSimulator(cache)

        # Neste exemplo, estamos gerando dados fictícios para a escrita na cache
        # Devemos substituir isso por dados reais
        simulator.simulate(program, memory_size)

        avg_memory_cost = cache_size / memory_size
        avg_memory_costs.append(avg_memory_cost)

        r = len(simulator.hit_rates) - 1
        if r == 0:
            efficiency_access.append(1)
        else:
            efficiency_access.append(simulator.hit_rates[r] / simulator.hit_rates[r - 1])
        hit_rates_vs_memory_sizes.append(simulator.hit_rates[-1])

    # Chama a função para plotar os gráficos
    plot_graphs(memory_sizes, avg_memory_costs, efficiency_access, hit_rates_vs_memory_sizes)

    # Agora vamos calcular o speedup baseado na Lei de Amdahl
    fraction_parallel = 0.8  # Fração paralela do programa
    num_processors = range(1, 17)  # Número de processadores de 1 a 16

    speedup_values = [amdahl_law_speedup(fraction_parallel, p) for p in num_processors]

    # Plotar o gráfico do speedup baseado na Lei de Amdahl
    plt.figure(5)
    plt.plot(num_processors, speedup_values, marker='o', linestyle='-')
    plt.xlabel('Número de Processadores')
    plt.ylabel('Speedup')
    plt.title('Speedup baseado na Lei de Amdahl')
    plt.show()
