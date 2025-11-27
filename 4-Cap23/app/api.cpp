// Projeto 10 - API RESTful Para Deploy do Modelo com C++ e Consumo da API com App Web em Python

// Includes
#include "crow.h" 
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

// Função para carregar o modelo a partir de um arquivo binário
VectorXd dsa_carrega_modelo(const string &filename, int size) {

    // Vetor de pesos
    VectorXd weights(size);

    // Cria stream para o arquivo
    ifstream file(filename, ios::in | ios::binary);

    // Verifica se houve erro ao abrir o arquivo
    if (!file) {
        cerr << "Erro ao abrir o arquivo do modelo!" << endl;
        exit(1);
    }

    // Lê o conteúdo do arquivo (ou seja, os pesos)
    for (int i = 0; i < size; ++i) {
        file.read(reinterpret_cast<char *>(&weights[i]), sizeof(weights[i]));
    }

    // Fecha o arquivo
    file.close();
    return weights;
}

// Função para fazer a previsão com novos dados
double predict(const VectorXd &weights, const VectorXd &input) {
    return weights.dot(input);
}

int main() {

    // Nome do modelo salvo
    string model_file = "modelo_cpp_dsa.bin";

    // Modelo com 2 features + bias
    VectorXd weights = dsa_carrega_modelo(model_file, 3); 

    // Inicializa o Crow
    crow::SimpleApp app;

    // Rota de teste (raiz)
    CROW_ROUTE(app, "/")
    ([]() {
        return "API de Previsão C++ está rodando!";
    });

    // Rota para realizar previsões (endpoint)
    CROW_ROUTE(app, "/predict")
    .methods("POST"_method)
    ([&weights](const crow::request &req) {

        // Carrega o corpo da requisição
        auto json_data = crow::json::load(req.body);
        if (!json_data) {
            return crow::response(400, "Dados de entrada inválidos!");
        }

        // Captura as features (atributos) a partir dos dados JSON
        double feature1 = json_data["feature1"].d();
        double feature2 = json_data["feature2"].d();

        // Vetor de entrada (features + bias)
        VectorXd input(3);

        // Adiciona o bias como 1.0
        input << feature1, feature2, 1.0; 

        // Faz a previsão
        double prediction = predict(weights, input);

        // Retorna a previsão em formato JSON
        crow::json::wvalue response;
        response["prediction"] = prediction;
        return crow::response(response);
    });

    // Inicia o servidor na porta 5001
    app.port(5001).multithreaded().run();
}
