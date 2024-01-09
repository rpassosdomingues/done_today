import pandas as pd
import matplotlib.pyplot as plt

def read_statistics(filename):
    # Read the CSV file into a DataFrame
    df = pd.read_csv(filename, header=None, names=['Mean', 'Variance', 'Standard Deviation'])
    return df

def plot_boxplots(data, labels):
    plt.figure(figsize=(12, 6))
    plt.boxplot(data, labels=labels)
    plt.title('Boxplots of Feature Statistics')
    plt.xlabel('Statistics')
    plt.ylabel('Value')
    plt.show()

def plot_histograms(data, labels):
    plt.figure(figsize=(12, 6))
    for i in range(len(labels)):
        plt.subplot(1, len(labels), i+1)
        plt.hist(data.iloc[:, i], bins=20, color='blue', alpha=0.7)
        plt.title(labels[i])
        plt.xlabel('Value')
        plt.ylabel('Frequency')
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    filename = "boxplot.csv"  # Replace with your actual file name
    df = read_statistics(filename)

    # Plot boxplots for each column (Mean, Variance, Standard Deviation)
    plot_boxplots([df['Mean'], df['Variance'], df['Standard Deviation']],
                  ['Mean', 'Variance', 'Standard Deviation'])

    # Plot histograms for each column
    plot_histograms(df, ['Mean', 'Variance', 'Standard Deviation'])
