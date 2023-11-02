import pandas as pd
import tensorflow as tf
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error, r2_score
import matplotlib.pyplot as plt

# Passo 1: Carregar os dados
coffee_data = pd.read_csv('dados_cafe.csv')  # Substitua 'dados_cafe.csv' pelo seu arquivo de dados

# Passo 2: Explorar os dados
print(coffee_data.head())  # Exibe as primeiras linhas dos dados
print(coffee_data.info())  # Verifica informações sobre os dados, como valores faltantes

# Passo 3: Pré-processamento
# Suponhamos que você queira usar 'Tempo', 'Chuva' e 'Fertilizante' como recursos para prever o preço do café.
features = coffee_data[['Tempo', 'Chuva', 'Fertilizante']]
target = coffee_data['Preco']

# Normalização dos recursos
scaler = StandardScaler()
features = scaler.fit_transform(features)

# Divisão dos dados em conjuntos de treino, validação e teste
X_train, X_temp, y_train, y_temp = train_test_split(features, target, test_size=0.3, random_state=42)
X_val, X_test, y_val, y_test = train_test_split(X_temp, y_temp, test_size=0.5, random_state=42)

# Passo 4: Escolher um algoritmo de IA e definir a arquitetura
model = tf.keras.models.Sequential([
    tf.keras.layers.Input(shape=(3,)),  # 3 recursos
    tf.keras.layers.Dense(1)  # Camada de saída com 1 neurônio
])

model.compile(optimizer='adam', loss='mean_squared_error')

# Passo 5: Treinar o modelo
model.fit(X_train, y_train, epochs=100, validation_data=(X_val, y_val))

# Passo 6: Avaliar o modelo
y_pred = model.predict(X_test)
mse = mean_squared_error(y_test, y_pred)
r2 = r2_score(y_test, y_pred)
print(f'MSE: {mse}')
print(f'R²: {r2}')

# Passo 7: Visualizar os resultados
plt.scatter(y_test, y_pred)
plt.xlabel('Preço Real')
plt.ylabel('Preço Previsto')
plt.show()
