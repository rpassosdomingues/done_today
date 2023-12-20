import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Dense, LSTM

class CoffeeFeatureExtractor:
    def __init__(self, file_path, seq_length=12, num_variables=2):
        self.file_path = file_path
        self.seq_length = seq_length
        self.num_variables = num_variables
        self.df = None
        self.data = None
        self.data_normalized = None
        self.X_train, self.y_train, self.X_test, self.y_test = None, None, None, None
        self.actual_test = None
        self.scaler = None
        self.model = None
        self.predictions = None

    def load_data(self):
        self.df = pd.read_csv(self.file_path, parse_dates=["DATE"])
        self.data = self.df["PRICE"].values.reshape(-1, 1)

    def normalize_data(self):
        self.scaler = MinMaxScaler()
        self.data_normalized = self.scaler.fit_transform(self.data)

    def sliding_window(self, data, seq_length, step=1):
        X, y = [], []
        for i in range(0, len(data) - seq_length, step):
            seq = data[i:i + seq_length, 0]
            X.append(seq)
            next_values = data[i + seq_length:i + seq_length + self.num_variables, 0]
            y.append(next_values)
        return np.array(X), np.array(y)

    def train_evaluate_feature_extractor(self, window_size=12, step=1):
        X, y = self.sliding_window(self.data_normalized, window_size, step)
        train_size = int(len(X) * 0.67)

        self.X_train, self.y_train = X[:train_size], y[:train_size]
        self.X_test, self.y_test = X[train_size:], y[train_size:]

        # Construir modelo de rede neural simples
        self.model = Sequential()
        self.model.add(Dense(100, activation='relu', input_shape=(window_size,)))
        self.model.add(Dense(self.num_variables))

        self.model.compile(optimizer='adam', loss='mean_squared_error')

        # Treinar o modelo
        self.model.fit(self.X_train, self.y_train, epochs=50, batch_size=32, verbose=0)

        # Fazer previsões
        self.predictions = self.model.predict(self.X_test)

    def evaluate_model(self, actual, predictions):
        mse = mean_squared_error(actual.ravel(), predictions.ravel())
        print(f"Mean Squared Error: {mse:.4f}")
        print("-" * 40)

    def denormalize_data(self, data):
        return self.scaler.inverse_transform(data.reshape(-1, 1))

    def plot_results(self):
        plt.figure(figsize=(12, 6))

        date_values = self.df["DATE"].dt.to_pydatetime()
        actual_dates = date_values[-len(self.y_test):]

        plt.plot(actual_dates, self.denormalize_data(self.y_test), label="Actual Prices", color="blue")
        plt.plot(actual_dates, self.denormalize_data(self.predictions), label="Predicted Prices", linestyle='dashed', color="orange")

        plt.title("Actual vs Predicted Prices")
        plt.xlabel("Date")
        plt.ylabel("Price")
        plt.legend()
        plt.show()

    def save_output(self, output_file):
        # Denormalize predicted prices
        denormalized_predictions = self.denormalize_data(self.predictions)

        # Transform predicted prices into specified number of representative variables
        predicted_price_variables = self.transform_price_to_variables(denormalized_predictions)

        # Create a DataFrame with date and predicted price variables
        output_df = pd.DataFrame({
            'DATE': self.df["DATE"].values[-len(self.y_test):],
        })

        # Add predicted price variables to the DataFrame
        for i in range(1, self.num_variables + 1):
            output_df[f'Predicted_Variable_{i}'] = predicted_price_variables[:, i-1]

        # Save DataFrame to a CSV file
        output_df.to_csv(output_file, index=False)

        print(f"Output saved to {output_file}")

    def run(self):
        self.load_data()
        self.normalize_data()

        # Train and evaluate feature extractor with sliding window
        self.train_evaluate_feature_extractor(window_size=12, step=1)

        self.evaluate_model(self.y_test, self.predictions)

        # Plot results
        self.plot_results()

        # Save the generated variables to a CSV file
        self.save_output("output_file.csv")

if __name__ == "__main__":
    feature_extractor = CoffeeFeatureExtractor(file_path="../data/PCOFFOTMUSDM.csv", num_variables=5)
    feature_extractor.run()
