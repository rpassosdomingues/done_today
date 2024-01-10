import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_data(filename):
    # Read data from the CSV file
    data = pd.read_csv(filename)
    return data

def plot_pie_chart(target_count0, target_count1):
    labels = ['Target 0', 'Target 1']
    sizes = [target_count0, target_count1]
    colors = ['lightcoral', 'lightskyblue']
    explode = (0.1, 0)  # explode 1st slice

    plt.figure(figsize=(8, 8))
    plt.pie(sizes, explode=explode, labels=labels, colors=colors, autopct='%1.1f%%', shadow=True, startangle=140)
    plt.title('Database Representativeness')
    plt.show()

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
    for i, col in enumerate(data.columns):
        plt.subplot(1, len(data.columns), i + 1)
        plt.hist(data[col], bins=20, edgecolor='black')
        plt.title(col)
        plt.xlabel('Value')
        plt.ylabel('Frequency')
    plt.suptitle('Histograms of Feature Statistics')
    plt.tight_layout()
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
    ax = plt.gca()
    data.plot(kind='bar', ax=ax)
    plt.title('Comparative Analysis of Feature Statistics')
    plt.xlabel('Feature Index')
    plt.ylabel('Value')
    plt.show()

if __name__ == "__main__":
    filename = "statistical_summary.csv"
    dataset = read_data(filename)
    
    target_count0 = 357
    target_count1 = 212
    plot_pie_chart(target_count0, target_count1)
    
    plot_boxplots(dataset)
    plot_histograms(dataset)
    plot_correlation_heatmap(dataset)
    plot_2d_scatter(dataset)
    comparative_analysis(dataset)
