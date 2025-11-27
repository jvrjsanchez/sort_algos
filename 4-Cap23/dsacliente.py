# Projeto 10 - API RESTful Para Deploy do Modelo com C++ e Consumo da API com App Web em Python
# Módulo Cliente Para Testar a API

# Imports
import requests
import json

# URL da API que está rodando no container como micro-serviço
url = "http://localhost:5001/predict"

# Dados de entrada para a previsão (exemplo de dados)
data = {
    "feature1": 1.5,
    "feature2": 2.0
}

# Enviar a requisição POST com os dados em formato JSON
response = requests.post(url, data = json.dumps(data), headers = {"Content-Type": "application/json"})

# Verificar se a requisição foi bem-sucedida
if response.status_code == 200:
    # Converter a resposta JSON e exibir o resultado da previsão
    result = response.json()
    print(f"Previsão: {result['prediction']}")
else:
    print(f"Erro ao fazer a requisição: {response.status_code}")
    print(response.text)
