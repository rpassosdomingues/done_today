import numpy as np
import matplotlib.pyplot as plt

# Function to compute Kendall's tau-b correlation coefficient
def kendalls_tau_b(a, b):
    concordantPairs = 0
    discordantPairs = 0
    tiedPairsA = 0
    tiedPairsB = 0

    for i in range(len(a)):
        for j in range(i + 1, len(a)):
            a1, a2 = a[i], a[j]
            b1, b2 = b[i], b[j]

            if a1 == a2 or b1 == b2:
                continue

            if (a1 < a2 and b1 < b2) or (a1 > a2 and b1 > b2):
                concordantPairs += 1
            elif (a1 < a2 and b1 > b2) or (a1 > a2 and b1 < b2):
                discordantPairs += 1

            if a1 == a2 and b1 != b2:
                tiedPairsA += 1

            if b1 == b2 and a1 != a2:
                tiedPairsB += 1

    numerator = concordantPairs - discordantPairs
    denominator = np.sqrt((concordantPairs + discordantPairs + tiedPairsA) *
                          (concordantPairs + discordantPairs + tiedPairsB))
    return numerator / denominator

def main():
    with open("random_array.txt", "r") as inputFile:
        randomArrays = [list(map(int, line.strip().split())) for line in inputFile]

    numVectors = len(randomArrays)

    # Calculate the average Kendall's tau-b coefficient for elements within a vector
    totalIntraRandomness = 0.0
    totalComparisonsIntra = 0

    for i in range(numVectors):
        for j in range(i + 1, numVectors):
            correlation = kendalls_tau_b(randomArrays[i], randomArrays[j])
            totalIntraRandomness += correlation
            totalComparisonsIntra += 1

    averageIntraRandomness = totalIntraRandomness / totalComparisonsIntra

    # Calculate the average Kendall's tau-b coefficient for elements between different vectors
    totalInterRandomness = 0.0
    totalComparisonsInter = 0

    for i in range(1, numVectors):
        correlation = kendalls_tau_b(randomArrays[0], randomArrays[i])
        totalInterRandomness += correlation
        totalComparisonsInter += 1

    averageInterRandomness = totalInterRandomness / totalComparisonsInter

    # Ensure the results are within the range [-1, 1]
    averageIntraRandomness = max(-1.0, min(1.0, averageIntraRandomness))
    averageInterRandomness = max(-1.0, min(1.0, averageInterRandomness))

    print("Average Kendall's tau-b coefficient for elements within a vector:", averageIntraRandomness)
    print("Average Kendall's tau-b coefficient for elements between different vectors:", averageInterRandomness)

if __name__ == "__main__":
    main()
