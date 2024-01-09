import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_data(filename):
    # Lê os dados do arquivo CSV
    data = pd.read_csv(filename, header=None, names=['Mean', 'Variance', 'StdDev'])
    return data

def plot_boxplots(data):
    # Boxplots ou Violin Plots
    plt.figure(figsize=(12, 6))
    data.boxplot()
    plt.title('Boxplots of Feature Statistics')
    plt.ylabel('Value')
    plt.show()

def plot_histograms(data):
    # Histogramas
    plt.figure(figsize=(12, 6))
    data.hist(bins=20, layout=(1, 3), figsize=(12, 6))
    plt.suptitle('Histograms of Feature Statistics')
    plt.show()

def plot_correlation_heatmap(data):
    # Heatmap de Correlação
    plt.figure(figsize=(8, 6))
    correlation_matrix = data.corr()
    plt.imshow(correlation_matrix, cmap='coolwarm', interpolation='none')
    plt.colorbar()
    plt.xticks(range(len(correlation_matrix)), correlation_matrix.columns)
    plt.yticks(range(len(correlation_matrix)), correlation_matrix.columns)
    plt.title('Correlation Heatmap')
    plt.show()

def plot_2d_scatter(data):
    # Gráficos de Dispersão Bidimensional
    plt.figure(figsize=(18, 6))
    for i, col in enumerate(data.columns):
        plt.subplot(1, 3, i+1)
        plt.scatter(data[col], data.index, alpha=0.5)
        plt.title(f'{col} vs. Feature Index')
        plt.xlabel(col)
        plt.ylabel('Feature Index')
    plt.tight_layout()
    plt.show()

def comparative_analysis(data):
    # Análise Comparativa
    plt.figure(figsize=(12, 6))
    data.plot(kind='bar', figsize=(12, 6))
    plt.title('Comparative Analysis of Feature Statistics')
    plt.xlabel('Feature Index')
    plt.ylabel('Value')
    plt.show()

def pareto_chart(data):
    # Gráfico de Pareto
    sorted_means = data['Mean'].sort_values(ascending=False)
    cumulative_percentage = sorted_means.cumsum() / sorted_means.sum()

    fig, ax1 = plt.subplots(figsize=(12, 6))
    ax1.bar(sorted_means.index, sorted_means, color='b', alpha=0.7)
    ax1.set_xlabel('Feature Index')
    ax1.set_ylabel('Mean Value', color='b')
    ax1.tick_params('y', colors='b')

    ax2 = ax1.twinx()
    ax2.plot(sorted_means.index, cumulative_percentage, 'r-')
    ax2.set_ylabel('Cumulative Percentage', color='r')
    ax2.tick_params('y', colors='r')

    plt.title('Pareto Chart of Feature Means')
    plt.show()

def plot_roc_pr_curves():
    # Curvas ROC e Precision-Recall
    # to-do: Resultados do Modelo
    from sklearn.metrics import roc_curve, precision_recall_curve
    # Roc Curve
    fpr, tpr, _ = roc_curve(y_true, y_scores)
    plt.figure(figsize=(8, 8))
    plt.plot(fpr, tpr, color='darkorange', lw=2)
    plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--')
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('Receiver Operating Characteristic (ROC) Curve')
    plt.show()

    # Precision-Recall Curve
    precision, recall, _ = precision_recall_curve(y_true, y_scores)
    plt.figure(figsize=(8, 8))
    plt.plot(recall, precision, color='blue', lw=2)
    plt.xlabel('Recall')
    plt.ylabel('Precision')
    plt.title('Precision-Recall Curve')
    plt.show()

def plot_3d(data):
    # Visualizações 3D
    fig = plt.figure(figsize=(12, 8))
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(data['Mean'], data['Variance'], data['StdDev'], c=data.index, cmap='viridis', s=50)
    ax.set_xlabel('Mean')
    ax.set_ylabel('Variance')
    ax.set_zlabel('Standard Deviation')
    ax.set_title('3D Scatter Plot of Feature Statistics')
    plt.show()

if __name__ == "__main__":
    filename = "summary_statistics.csv"
    dataset = read_data(filename)

    plot_boxplots(dataset)
    plot_histograms(dataset)
    plot_correlation_heatmap(dataset)
    plot_2d_scatter(dataset)
    comparative_analysis(dataset)
    pareto_chart(dataset)
    # plot_roc_pr_curves()
    plot_3d(dataset)
