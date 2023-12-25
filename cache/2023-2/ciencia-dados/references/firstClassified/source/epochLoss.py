import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('../data/epochs_losses.csv')

plt.scatter(df['Epoch'], df['Loss'])
plt.title('Loss Over Epochs')
plt.xlabel('Epoch')
plt.ylabel('Loss')
plt.show()
