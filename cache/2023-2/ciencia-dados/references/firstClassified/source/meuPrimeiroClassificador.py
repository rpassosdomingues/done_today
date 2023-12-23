import tensorflow as tf
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

# Carregar o conjunto de dados Iris
iris = datasets.load_iris()
X = iris.data  # Recursos (características)
y = iris.target  # Rótulos (classes)

# Dividir o conjunto de dados em treinamento e teste
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Normalizar os dados para melhor desempenho da rede neural
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Criar um modelo de rede neural simples
model = tf.keras.Sequential([
    tf.keras.layers.Input(shape=(4,)),
    tf.keras.layers.Dense(128, activation='relu'),
    tf.keras.layers.Dense(3, activation='softmax')
])

# Compilar o modelo
model.compile(optimizer='adam', loss='sparse_categorical_crossentropy', metrics=['accuracy'])

# Treinar o modelo com os dados de treinamento
model.fit(X_train, y_train, epochs=100, batch_size=32, verbose=1)

# Avaliar o modelo com os dados de teste
_, accuracy = model.evaluate(X_test, y_test)
print(f'Acurácia do modelo: {accuracy}')
