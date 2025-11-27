# Projeto 10 - API RESTful Para Deploy do Modelo com C++ e Consumo da API com App Web em Python
# Módulo da App Web em Python

# Imports
from flask import Flask, render_template, request
import requests
import json

# Cria a app
app = Flask(__name__)

# URL da API em C++
API_URL = "http://localhost:5001/predict"

# Cria a rota raiz
@app.route('/', methods=['GET', 'POST'])
def index():
    
    # Inicializa variáveis de controle
    prediction = None
    error = None

    # Verifica se é método POST
    if request.method == 'POST':

        # Captura os dados do formulário
        feature1 = request.form.get('feature1', type=float)
        feature2 = request.form.get('feature2', type=float)

        # Monta os dados para enviar à API
        data = {
            "feature1": feature1,
            "feature2": feature2
        }

        try:
            # Faz a requisição à API
            response = requests.post(API_URL, data = json.dumps(data), headers = {"Content-Type": "application/json"})

            # Verifica se a requisição foi bem-sucedida
            if response.status_code == 200:
                result = response.json()
                prediction = result['prediction']
            else:
                error = f"Erro na API: {response.status_code}"
        except Exception as e:
            error = f"Erro ao conectar à API: {str(e)}"

    return render_template('index.html', prediction = prediction, error = error)

if __name__ == '__main__':
    app.run(debug=True)
