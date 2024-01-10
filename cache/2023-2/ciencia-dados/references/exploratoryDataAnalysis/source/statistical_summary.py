import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_data(filename):
    # Read data from the CSV file
    data = pd.read_csv(filename)
    return data

def plot_boxplots(data):
    # Boxplots or Violin Plots
    plt.figure(figsize=(12, 6))
    data.boxplot()
    plt.title('Boxplots of Feature Statistics')
    plt.ylabel('Value')
    plt.show()

def plot_histograms(data):
    # Histograms
    plt.figure(figsize=(12, 6))
    data.hist(bins=20, layout=(1, 5), figsize=(12, 6))
    plt.suptitle('Histograms of Feature Statistics')
    plt.show()

def plot_correlation_heatmap(data):
    # Correlation Heatmap
    plt.figure(figsize=(10, 8))
    correlation_matrix = data.corr()
    plt.imshow(correlation_matrix, cmap='coolwarm', interpolation='none')
    plt.colorbar()
    plt.xticks(range(len(correlation_matrix)), correlation_matrix.columns)
    plt.yticks(range(len(correlation_matrix)), correlation_matrix.columns)
    plt.title('Correlation Heatmap')
    plt.show()

def plot_2d_scatter(data):
    # 2D Scatter Plots
    plt.figure(figsize=(18, 6))
    for col in data.columns:
        plt.scatter(data.index, data[col], alpha=0.5, label=col)

    plt.title('2D Scatter Plot of Feature Statistics')
    plt.xlabel('Feature Index')
    plt.ylabel('Value')
    plt.legend()
    plt.show()

def comparative_analysis(data):
    # Comparative Analysis
    plt.figure(figsize=(12, 6))
    data.plot(kind='bar', figsize=(12, 6))
    plt.title('Comparative Analysis of Feature Statistics')
    plt.xlabel('Feature Index')
    plt.ylabel('Value')
    plt.show()

if __name__ == "__main__":
    filename = "statistical_summary.csv"
    dataset = read_data(filename)

    plot_boxplots(dataset)
    plot_histograms(dataset)
    plot_correlation_heatmap(dataset)
    plot_2d_scatter(dataset)
    comparative_analysis(dataset)
