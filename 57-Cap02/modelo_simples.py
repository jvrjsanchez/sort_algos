import numpy as np
import tensorflow as tf
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import accuracy_score, confusion_matrix

# Criar dados de exemplo
np.random.seed(0)
num_samples = 1000
feature1 = np.random.rand(num_samples)  # Variável preditora 1
feature2 = np.random.rand(num_samples)  # Variável preditora 2
feature3 = np.random.rand(num_samples)  # Variável preditora 3
target = np.random.choice(['A', 'B', 'C'], num_samples)  # Variável alvo categórica

# Dividir o conjunto de dados em treinamento e teste
X_train, X_test, y_train, y_test = train_test_split(
    np.column_stack((feature1, feature2, feature3)),
    target,
    test_size=0.2,
    random_state=42
)

# Pré-processamento de dados
encoder = LabelEncoder()
y_train_encoded = encoder.fit_transform(y_train)
y_test_encoded = encoder.transform(y_test)

y_train_one_hot = tf.keras.utils.to_categorical(y_train_encoded, num_classes=3)
y_test_one_hot = tf.keras.utils.to_categorical(y_test_encoded, num_classes=3)

# Criar a arquitetura do modelo MLP
model = tf.keras.Sequential([
    tf.keras.layers.Dense(64, activation='relu', input_shape=(3,)),
    tf.keras.layers.Dense(32, activation='relu'),
    tf.keras.layers.Dense(3, activation='softmax')  # Camada de saída com 3 classes
])

# Compilar o modelo
model.compile(optimizer='adam', loss='categorical_crossentropy', metrics=['accuracy'])

# Treinar o modelo
model.fit(X_train, y_train_one_hot, epochs=20, batch_size=32, validation_split=0.2)

# Avaliar o modelo usando métricas
y_pred = model.predict(X_test)
y_pred_classes = np.argmax(y_pred, axis=1)

accuracy = accuracy_score(y_test_encoded, y_pred_classes)
confusion = confusion_matrix(y_test_encoded, y_pred_classes)

print("Acurácia do modelo:", accuracy)
print("Matriz de Confusão:")
print(confusion)
