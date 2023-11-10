import sys
import numpy as np
import matplotlib.pyplot as plt
from astropy.io import fits
from astropy.wcs import WCS

def obter_centro_ds9():
    # Função para obter manualmente as coordenadas (x, y) do centro da mancha suspeita de câncer de pele no DS9.
    # Substitua as coordenadas abaixo pelos valores obtidos no DS9.
    x_centro = 100
    y_centro = 100
    return x_centro, y_centro

def cortar_regiao_ao_redor_do_centro(image_data):
    # Obtém as coordenadas do centro da mancha suspeita de câncer de pele no DS9.
    x_centro, y_centro = obter_centro_ds9()

    # Define o tamanho da região de corte ao redor do centro.
    tamanho_regiao = 200  # Tamanho da região ao redor do centro

    # Limites da região cortada
    x_min = int(x_centro - tamanho_regiao / 2)
    x_max = int(x_centro + tamanho_regiao / 2)
    y_min = int(y_centro - tamanho_regiao / 2)
    y_max = int(y_centro + tamanho_regiao / 2)

    # Garante que os limites estejam dentro dos limites da imagem.
    x_min = max(0, x_min)
    x_max = min(image_data.shape[1], x_max)
    y_min = max(0, y_min)
    y_max = min(image_data.shape[0], y_max)

    # Verifica se há pixels na região de corte.
    if x_min >= x_max or y_min >= y_max:
        print("Região de corte está fora dos limites da imagem. Ajuste os parâmetros.")
        return None

    # Corta a região da imagem.
    image_data_cortado = image_data[y_min:y_max, x_min:x_max]

    # Exibe o recorte.
    plt.imshow(image_data_cortado, origin='lower', cmap='viridis', vmin=0, vmax=1)
    plt.title('Região Cortada ao Redor do Centro da Mancha Suspeita de Câncer de Pele')
    plt.show()

    return image_data_cortado

def calcular_perfil_intensidade(image_data):
    # Verifica se image_data é None
    if image_data is None:
        return None

    # Encontrar o centro da imagem
    center_x, center_y = np.array(image_data.shape) // 2

    # Criar uma grade de coordenadas
    y, x = np.meshgrid(np.arange(image_data.shape[0]), np.arange(image_data.shape[1]))

    # Calcular a distância de cada pixel para o centro
    r = np.sqrt((x - center_x)**2 + (y - center_y)**2)

    # Número de anéis concêntricos desejados
    num_rings = 50

    # Calcular a média da intensidade dos pixels em cada anel
    intensity_profile = []
    for i in range(num_rings):
        ring_mask = (r >= i) & (r < i + 1)
        intensity = np.mean(image_data[ring_mask])
        intensity_profile.append(intensity)

    return np.array(intensity_profile)

def plotar_perfil_intensidade(intensity_profile):
    # Verifica se intensity_profile é None
    if intensity_profile is None:
        print("Não foi possível calcular o perfil de intensidade. Verifique os parâmetros.")
        return

    # Plotar o perfil de intensidade
    plt.plot(intensity_profile, marker='o', linestyle='-', color='b')
    plt.xlabel('Distância do Centro (pixels)')
    plt.ylabel('Intensidade Média')
    plt.title('Perfil de Intensidade')
    plt.show()

def main(argv=None):
    # Substitua o caminho do arquivo pela sua imagem FITS
    caminho_arquivo = "C:/computacao/github/done_today/insights/science/cancerPele.fits"

    # Abrir o arquivo FITS
    hdul = fits.open(caminho_arquivo)
    hdu = fits.open(caminho_arquivo)[0]

    # Obter os dados da imagem e o sistema de coordenadas
    image_data = hdu.data
    wcs = WCS(hdu.header)

    # Cortar uma região ao redor do centro da mancha suspeita de câncer de pele e exibir
    image_data_cortado = cortar_regiao_ao_redor_do_centro(image_data)

    # Calcular o perfil de intensidade
    intensity_profile = calcular_perfil_intensidade(image_data_cortado)

    # Plotar o perfil de intensidade
    plotar_perfil_intensidade(intensity_profile)

    return 0

if __name__ == "__main__":
    sys.exit(main())
