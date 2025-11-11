# Projeto 5 - Pipeline Automatizado de IA Para Detecção de Fraudes em Transações Financeiras Imobiliárias
# Python - Executa o Pipeline

# Imports
import subprocess
import time

# Função para executar comandos de terminal
def dsa_executa_comando(command):
    try:
        result = subprocess.run(command, shell=True, check=True, capture_output=True, text=True)
        print(f"\nComando '{command}' executado com sucesso.")
        print("\nSaída:\n", result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"\nErro ao executar o comando '{command}'.")
        print("\nErro:\n", e.stderr)

# Função para executar outros scripts Python
def dsa_executa_pipeline(script_name):
    try:
        result = subprocess.run(['python', script_name], check=True, capture_output=True, text=True)
        print(f"\nScript {script_name} executado com sucesso.")
        print("\nSaída:\n", result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"\nErro ao executar o script {script_name}.")
        print("\nErro:\n", e.stderr)

# Comandos para criação do container Docker e instalação dos pacotes
docker_command = "docker run --name dsa-projeto5 -p 5553:5432 -e POSTGRES_USER=dsa -e POSTGRES_PASSWORD=dsa1010 -e POSTGRES_DB=dsadb -d postgres:16.1"
pip_command = "pip install -r requirements.txt"

# Inicia o timer
start_time = time.time()

# Executa os comandos de terminal
dsa_executa_comando(docker_command)
dsa_executa_comando(pip_command)

# Lista de scripts
scripts = [
    'Projeto5-02-CriaTabelas.py',
    'Projeto5-03-CarregaDados.py',
    'Projeto5-04-ExecutaLLM.py'
]

# Executa os scripts em um loop
for script in scripts:
    dsa_executa_pipeline(script)

# Comando para destruir o container Docker
destroy_docker_command = "docker rm -f dsa-projeto5"
dsa_executa_comando(destroy_docker_command)

# Calcula o tempo total de execução
end_time = time.time()
total_time = end_time - start_time

print(f"\nPipeline executado com sucesso.")
print(f"Tempo total de execução: {total_time:.2f} segundos.\n")
