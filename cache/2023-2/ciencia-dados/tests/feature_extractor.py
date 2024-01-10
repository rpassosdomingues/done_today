import pandas as pd
from sklearn.svm import SVR
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error
from xgboost import XGBRegressor

class TimeSeries:
    pass

def read_data(filename):
    df = pd.read_csv(filename)
    num_entries = len(df)
    data = [TimeSeries() for _ in range(num_entries)]

    for i in range(num_entries):
        data[i].date = df.loc[i, 'DATE']
        data[i].price = df.loc[i, 'PRICE']
        # Add any additional features you want to use here

    return data

def train_svm(data):
    # X = data[['Feature1', 'Feature2']]  # Use appropriate features obtained from SVM
    X = data[['Feature1']]  # Use appropriate features obtained from SVM
    y = data['Price']

    # Split the data into training and testing sets
    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    # Train SVM
    svm_model = SVR(kernel='rbf', epsilon=0.001, C=1.0)
    svm_model.fit(X_train, y_train)

    # Use SVM predictions as features for XGBoost
    svm_predictions = svm_model.predict(X_test)
    XGB_data = pd.concat([X_test, pd.Series(svm_predictions, name='SVM_Predictions')], axis=1)

    return XGB_data, y_test

def train_xgboost(XGB_data, y_test):
    # Train XGBoost
    xgb_model = XGBRegressor(objective='reg:squarederror')
    xgb_model.fit(XGB_data, y_test)

    return xgb_model

def main():
    filename = "../data/PCOFFOTMUSDM.csv"
    data = read_data(filename)

    # Train SVM model
    XGB_data, y_test = train_svm(data)

    # Train XGBoost model
    xgb_model = train_xgboost(XGB_data, y_test)

    # Make predictions
    xgb_predictions = xgb_model.predict(XGB_data)

    # Evaluate the combined model
    mse = mean_squared_error(y_test, xgb_predictions)
    print(f'Mean Squared Error: {mse}')

    # Save the model if needed
    # xgb_model.save_model('xgboost_model.model')

if __name__ == "__main__":
    main()
