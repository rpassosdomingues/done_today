import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.ensemble import RandomForestRegressor
from sklearn.svm import SVR
from xgboost import XGBRegressor
from sklearn.metrics import mean_squared_error
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense

class CoffeePricePredictor:
    def __init__(self, file_path, seq_length=12):
        self.file_path = file_path
        self.seq_length = seq_length
        self.df = None
        self.data = None
        self.data_normalized = None
        self.X_train, self.y_train, self.X_test, self.y_test = None, None, None, None
        self.actual_test = None
        self.scaler = None
        self.lstm_model = None
        self.linear_model = None
        self.rf_model = None
        self.svm_model = None
        self.xgboost_model = None
        self.train_predictions_lstm, self.test_predictions_lstm = None, None
        self.predictions_linear, self.predictions_train_rf, self.predictions_test_rf = None, None, None
        self.predictions_svm, self.predictions_train_xgboost, self.predictions_test_xgboost = None, None, None

    def load_data(self):
        self.df = pd.read_csv(self.file_path, parse_dates=["DATE"])
        self.data = self.df["PRICE"].values.reshape(-1, 1)

    def normalize_data(self):
        self.scaler = MinMaxScaler()
        self.data_normalized = self.scaler.fit_transform(self.data)

    def create_sequences(self, data, seq_length):
        X, y = [], []
        for i in range(len(data) - seq_length):
            seq = data[i:i + seq_length, 0]
            X.append(seq)
            y.append(data[i + seq_length, 0])
        return np.array(X), np.array(y)

    def train_evaluate_lstm(self, epochs=100, batch_size=32):
        self.lstm_model = Sequential()
        self.lstm_model.add(LSTM(50, input_shape=(self.X_train.shape[1], 1)))
        self.lstm_model.add(Dense(1))
        self.lstm_model.compile(loss="mean_squared_error", optimizer="adam")
        
        self.lstm_model.fit(self.X_train, self.y_train, epochs=epochs, batch_size=batch_size, verbose=0)
        self.train_predictions_lstm = self.lstm_model.predict(self.X_train)
        self.test_predictions_lstm = self.lstm_model.predict(self.X_test)

    def train_evaluate_linear_regression(self):
        self.linear_model = LinearRegression()
        self.linear_model.fit(self.X_train, self.y_train)
        self.predictions_linear = self.linear_model.predict(self.X_test)

    def train_evaluate_random_forest(self):
        self.rf_model = RandomForestRegressor(n_estimators=100, random_state=42)
        self.rf_model.fit(self.X_train, self.y_train)
        self.predictions_train_rf = self.rf_model.predict(self.X_train)
        self.predictions_test_rf = self.rf_model.predict(self.X_test)

    def train_evaluate_svm(self):
        self.svm_model = SVR(kernel='linear')
        self.svm_model.fit(self.X_train, self.y_train)
        self.predictions_svm = self.svm_model.predict(self.X_test)

    def train_evaluate_xgboost(self):
        self.xgboost_model = XGBRegressor()
        self.xgboost_model.fit(self.X_train, self.y_train)
        self.predictions_train_xgboost = self.xgboost_model.predict(self.X_train)
        self.predictions_test_xgboost = self.xgboost_model.predict(self.X_test)

    def evaluate_model(self, model_name, actual, predictions):
        mse = mean_squared_error(actual.ravel(), predictions.ravel())
        print(f"Metrics for {model_name}:")
        print(f"Mean Squared Error: {mse:.4f}")
        print("-" * 40)

    def denormalize_data(self, data):
        return self.scaler.inverse_transform(data.reshape(-1, 1))

    def plot_results(self):
        plt.figure(figsize=(12, 6))

        # Plot LSTM predictions
        plt.plot(self.df["DATE"].values[self.seq_length:len(self.X_train) + self.seq_length],
             self.denormalize_data(self.train_predictions_lstm), label="LSTM Training Predictions", color="blue")
        plt.plot(self.df["DATE"].values[len(self.X_train) + self.seq_length:len(self.X_train) + len(self.X_test) + self.seq_length],
             self.denormalize_data(self.test_predictions_lstm), label="LSTM Test Predictions", color="green")

        # Plot actual test data
        #plt.plot(self.df["DATE"].values[len(self.data_normalized) - len(self.y_test):],
        #     self.denormalize_data(self.actual_test), label="Test Actual Data", color="red")

        # Add predictions for other models to the plot
        plt.plot(self.df["DATE"].values[len(self.X_train) + self.seq_length:len(self.X_train) + len(self.X_test) + self.seq_length],
             self.denormalize_data(self.predictions_linear),
             label="Linear Regression Test Predictions", linestyle='dashed', color="purple")
        plt.plot(self.df["DATE"].values[len(self.X_train) + self.seq_length:len(self.X_train) + len(self.X_test) + self.seq_length],
             self.denormalize_data(self.predictions_test_rf),
             label="Random Forest Test Predictions", linestyle='dashed', color="cyan")
        plt.plot(self.df["DATE"].values[len(self.X_train) + self.seq_length:len(self.X_train) + len(self.X_test) + self.seq_length],
             self.denormalize_data(self.predictions_test_xgboost),
             label="XGBoost Test Predictions", linestyle='dashed', color="pink")

        plt.title("Coffee Price Prediction with Multiple Models")
        plt.xlabel("Date")
        plt.ylabel("Price (USDM)")
        plt.legend()
        plt.show()

    def run(self):
        self.load_data()
        self.normalize_data()
        self.create_sequences(self.data_normalized, self.seq_length)

        train_size = int(len(self.data_normalized) * 0.67)
        self.X_train, self.y_train = self.create_sequences(self.data_normalized[:train_size], self.seq_length)
        self.X_test, self.y_test = self.create_sequences(self.data_normalized[train_size:], self.seq_length)
        self.actual_test = self.data[train_size + self.seq_length:]

        self.train_evaluate_lstm()
        self.train_evaluate_linear_regression()
        self.train_evaluate_random_forest()
        self.train_evaluate_svm()
        self.train_evaluate_xgboost()

        self.evaluate_model("LSTM (Train)", self.y_train, self.train_predictions_lstm)
        self.evaluate_model("LSTM (Test)", self.y_test, self.test_predictions_lstm)

        self.evaluate_model("Linear Regression (Test)", self.actual_test, self.predictions_linear)

        self.evaluate_model("Random Forest (Train)", self.y_train, self.predictions_train_rf)
        self.evaluate_model("Random Forest (Test)", self.y_test, self.predictions_test_rf)

        self.evaluate_model("SVM (Test)", self.actual_test, self.predictions_svm)

        self.evaluate_model("XGBoost (Train)", self.y_train, self.predictions_train_xgboost)
        self.evaluate_model("XGBoost (Test)", self.y_test, self.predictions_test_xgboost)

        self.plot_results()

if __name__ == "__main__":
    predictor = CoffeePricePredictor(file_path="../data/PCOFFOTMUSDM.csv")
    predictor.run()
