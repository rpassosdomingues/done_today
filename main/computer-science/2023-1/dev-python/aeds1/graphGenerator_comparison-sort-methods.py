import csv
import pandas as pd
import matplotlib.pyplot as plt

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

    # Plot the graphics for Random Case
    plt.figure(figsize=(10, 6))
    plt.scatter(sizes, randomBubbleUsages, label="Bubble Sort", marker='o')
    plt.scatter(sizes, randomInsertionUsages, label="Insertion Sort", marker='x')
    plt.scatter(sizes, randomSelectionUsages, label="Selection Sort", marker='^')
    plt.title("Random Case")
    plt.xlabel("Array Size")
    plt.ylabel("Number of Iterations")
    plt.legend()
    plt.show()

    # Plot the graphics for Increasing Case
    plt.figure(figsize=(10, 6))
    plt.scatter(sizes, increasingBubbleUsages, label="Bubble Sort", marker='o')
    plt.scatter(sizes, increasingInsertionUsages, label="Insertion Sort", marker='x')
    plt.scatter(sizes, increasingSelectionUsages, label="Selection Sort", marker='^')
    plt.title("Increasing Case")
    plt.xlabel("Array Size")
    plt.ylabel("Number of Iterations")
    plt.legend()
    plt.show()

    # Plot the graphics for Decreasing Case
    plt.figure(figsize=(10, 6))
    plt.scatter(sizes, decreasingBubbleUsages, label="Bubble Sort", marker='o')
    plt.scatter(sizes, decreasingInsertionUsages, label="Insertion Sort", marker='x')
    plt.scatter(sizes, decreasingSelectionUsages, label="Selection Sort", marker='^')
    plt.title("Decreasing Case")
    plt.xlabel("Array Size")
    plt.ylabel("Number of Iterations")
    plt.legend()
    plt.show()

# Run the main function
if __name__ == "__main__":
    main()
