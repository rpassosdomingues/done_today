import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.svm import SVR
from sklearn.neural_network import MLPRegressor
from sklearn.ensemble import RandomForestRegressor
from statsmodels.graphics.tsaplots import plot_acf, plot_pacf

class ForecastingModel:
    def __init__(self, file_path):
        self.file_path = file_path
        self.df = None
        self.data = None
        self.load_data()

    def load_data(self):
        self.df = pd.read_csv(self.file_path, parse_dates=["DATE"])
        self.data = self.df["PRICE"].values.reshape(-1, 1)

    def simulate_future_values(self, tam=10):
        values_to_simulate = pd.DataFrame(index=self.df.index[len(self.df)-tam:])
        values_to_simulate['observed'] = self.df['PRICE'][len(self.df)-tam:len(self.df)].values
        self.df = self.df[:-tam]
        return values_to_simulate

    def plot_acf_pacf(self):
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(12, 4))
        plot_acf(self.df['PRICE'].values, lags=20, ax=ax1)
        ax1.set_title("Autocorrelation Function (ACF)")
        plot_pacf(self.df['PRICE'].values, lags=20, ax=ax2)
        ax2.set_title("Partial Autocorrelation Function (PACF)")
        plt.show()

    def univariate_to_tabular(self, lag):
        series = self.df['PRICE'].values
        df_tabular = pd.DataFrame(index=self.df.index[lag:])
        end = lag
        
        for i in range(0, lag):
            df_tabular[f'X{i}'] = series[i:len(series)-end]
            end -= 1
        df_tabular['Y'] = series[lag:]
        
        return df_tabular

    def train_test_split(self, lag=4, test_size=0.3):
        base_knowledge = self.univariate_to_tabular(lag=lag)
        X = base_knowledge.iloc[:, :-1]
        y = base_knowledge.iloc[:, -1]
        X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=test_size, random_state=None)
        return X_train, X_test, y_train, y_test

    def train_models(self, X_train, y_train):
        svm_model = SVR()
        mlp_model = MLPRegressor()
        rf_model = RandomForestRegressor()
        
        svm_model.fit(X_train, y_train)
        mlp_model.fit(X_train, y_train)
        rf_model.fit(X_train, y_train)
        
        return svm_model, mlp_model, rf_model

    def forecast(self, df_orig, steps, model_fit, lag):
        last_observation = df_orig.iloc[-1 - lag:-1, 0].values
        tam = len(last_observation)
        forecasted_values = np.zeros(steps)  # Initialize with zeros

        for i in range(steps):
            if i == 0:
                forecasted_values[i] = model_fit.predict(last_observation[-lag:].reshape(1, -1))
            else:
                last_observation = np.append(last_observation, forecasted_values[i - 1])
                last_observation = last_observation[-lag:]  # Keep only the last lag values
                forecasted_values[i] = model_fit.predict(last_observation[-lag:].reshape(1, -1))

        return forecasted_values

    def main(self):
        future_values_df = self.simulate_future_values()
        self.plot_acf_pacf()
        lag = 4
        X_train, X_test, y_train, y_test = self.train_test_split(lag=lag)
        svm_model, mlp_model, rf_model = self.train_models(X_train, y_train)

        forecast_steps = 5
        svm_forecast = self.forecast(future_values_df, forecast_steps, svm_model, lag)
        mlp_forecast = self.forecast(future_values_df, forecast_steps, mlp_model, lag)
        rf_forecast = self.forecast(future_values_df, forecast_steps, rf_model, lag)

        forecast_df = pd.DataFrame({
            'Observed': future_values_df['observed'].values,
            'SVM': svm_forecast,
            'MLP': mlp_forecast,
            'Random Forest': rf_forecast
        })

        print(forecast_df)

# File path for the dataset
file_path = "../data/PCOFFOTMUSDM.csv"

# Create an instance of the ForecastingModel
forecast_model = ForecastingModel(file_path)

# Execute the main function
forecast_model.main()
