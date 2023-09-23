import csv
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

def normalize_data(data):
    max_value = max(data)
    min_value = min(data)
    return [(value - min_value) / (max_value - min_value) for value in data]

def main():
    sizes = []
    randomBubbleUsages = []
    increasingBubbleUsages = []
    decreasingBubbleUsages = []
    randomInsertionUsages = []
    increasingInsertionUsages = []
    decreasingInsertionUsages = []
    randomSelectionUsages = []
    increasingSelectionUsages = []
    decreasingSelectionUsages = []

    # Read the CSV File
    data = pd.read_csv("sort_usages.csv")

    # Extract the data of columns
    sizes = data["Array Size"]
    randomBubbleUsages = data["Random Bubble Sort Usage"]
    increasingBubbleUsages = data["Increasing Bubble Sort Usage"]
    decreasingBubbleUsages = data["Decreasing Bubble Sort Usage"]
    randomInsertionUsages = data["Random Insertion Sort Usage"]
    increasingInsertionUsages = data["Increasing Insertion Sort Usage"]
    decreasingInsertionUsages = data["Decreasing Insertion Sort Usage"]
    randomSelectionUsages = data["Random Selection Sort Usage"]
    increasingSelectionUsages = data["Increasing Selection Sort Usage"]
    decreasingSelectionUsages = data["Decreasing Selection Sort Usage"]

    # Normalize the data
    sizes = normalize_data(sizes)
    randomBubbleUsages = normalize_data(randomBubbleUsages)
    increasingBubbleUsages = normalize_data(increasingBubbleUsages)
    decreasingBubbleUsages = normalize_data(decreasingBubbleUsages)
    randomInsertionUsages = normalize_data(randomInsertionUsages)
    increasingInsertionUsages = normalize_data(increasingInsertionUsages)
    decreasingInsertionUsages = normalize_data(decreasingInsertionUsages)
    randomSelectionUsages = normalize_data(randomSelectionUsages)
    increasingSelectionUsages = normalize_data(increasingSelectionUsages)
    decreasingSelectionUsages = normalize_data(decreasingSelectionUsages)

    # Calculate the mean for each method and create a dictionary
    method_means = {
        "Random Bubble": sum(randomBubbleUsages) / len(randomBubbleUsages),
        "Increasing Bubble": sum(increasingBubbleUsages) / len(increasingBubbleUsages),
        "Decreasing Bubble": sum(decreasingBubbleUsages) / len(decreasingBubbleUsages),
        "Random Insertion": sum(randomInsertionUsages) / len(randomInsertionUsages),
        "Increasing Insertion": sum(increasingInsertionUsages) / len(increasingInsertionUsages),
        "Decreasing Insertion": sum(decreasingInsertionUsages) / len(decreasingInsertionUsages),
        "Random Selection": sum(randomSelectionUsages) / len(randomSelectionUsages),
        "Increasing Selection": sum(increasingSelectionUsages) / len(increasingSelectionUsages),
        "Decreasing Selection": sum(decreasingSelectionUsages) / len(decreasingSelectionUsages),
    }

    # Sort the method_means dictionary by mean values (ascending order)
    sorted_means = sorted(method_means.items(), key=lambda x: x[1])

    # Unpack the sorted_means into two separate lists
    sorted_methods, sorted_means = zip(*sorted_means)

    # Define colors for each method
    colors = {"Random Bubble": "blue", "Increasing Bubble": "blue", "Decreasing Bubble": "blue",
              "Random Insertion": "green", "Increasing Insertion": "green", "Decreasing Insertion": "green",
              "Random Selection": "red", "Increasing Selection": "red", "Decreasing Selection": "red"}

    # Create a pie chart showing the percentage of usage for each method
    plt.figure(figsize=(8, 8))

    # Define the explode values to highlight the method of lowest usage
    explode = [0.1 if method == sorted_methods[0] else 0 for method in sorted_methods]

    plt.pie(sorted_means, labels=sorted_methods, colors=[colors[method] for method in sorted_methods],
            autopct="%1.4f%%", startangle=140, explode=explode)

    plt.title("Percentage of Usage for Each Sorting Algorithm")
    plt.axis("equal")

    plt.show()

    # Calculate the mean normalized usage for each size
    mean_usage_insertion = (np.array(randomInsertionUsages) + np.array(increasingInsertionUsages) + np.array(decreasingInsertionUsages)) / 3

    # Create a scatter plot with regression line for the mean normalized usage (insertion method)
    sns.set_theme(style="whitegrid")
    plt.figure(figsize=(10, 6))
    plt.scatter(sizes, randomBubbleUsages, label="Random Bubble", s=30, color=colors["Random Bubble"], alpha=0.1)
    plt.scatter(sizes, increasingBubbleUsages, label="Increasing Bubble", s=30, color=colors["Increasing Bubble"], alpha=0.1)
    plt.scatter(sizes, decreasingBubbleUsages, label="Decreasing Bubble", s=30, color=colors["Decreasing Bubble"], alpha=0.1)
    plt.scatter(sizes, randomSelectionUsages, label="Random Selection", s=30, color=colors["Random Selection"], alpha=0.1)
    plt.scatter(sizes, increasingSelectionUsages, label="Increasing Selection", s=30, color=colors["Increasing Selection"], alpha=0.1)
    plt.scatter(sizes, decreasingSelectionUsages, label="Decreasing Selection", s=30, color=colors["Decreasing Selection"], alpha=0.1)
    
    plt.plot(sizes, mean_usage_insertion, label="Mean Normalized Usage (Insertion)", color="green", linewidth=2)
    
    plt.xlabel("Normalized Array Size")
    plt.ylabel("Normalized Usage")
    plt.title("Normalized Usage for Each Sorting Algorithm")
    plt.legend(loc="upper left")

    # Adjust y-axis limits for better visualization
    plt.ylim(-0.1, 1.1)

    plt.show()

# Run the main function
if __name__ == "__main__":
    main()
