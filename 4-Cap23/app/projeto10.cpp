// Projeto 10 - API RESTful Para Deploy do Modelo com C++ e Consumo da API com App Web em Python

// Includes
#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;
using namespace std;

// MatrixXd é um tipo de dado fornecido pela biblioteca Eigen, uma biblioteca C++ para álgebra linear, vetores, e matrizes. 
// Especificamente, MatrixXd representa uma matriz de números de ponto flutuante (números decimais) de dimensões dinâmicas. 
// A letra X no tipo MatrixXd indica que tanto o número de linhas quanto o número de colunas da matriz podem variar durante o tempo de execução, 
// diferentemente de Matrix3d, por exemplo, que seria uma matriz de 3x3 com elementos de ponto flutuante de precisão dupla.

// Função sigmoide
MatrixXd sigmoid(const MatrixXd &Z) {
    return 1.0 / (1.0 + (-Z.array()).exp());
}

// Derivada da função sigmoide
MatrixXd sigmoid_derivative(const MatrixXd &Z) {
    return Z.array() * (1.0 - Z.array());
}

// Função para salvar o modelo (pesos)
void dsa_salva_modelo(const MatrixXd &weights1, const MatrixXd &weights2, const string &filename) {

    // ofstream é um objeto da biblioteca padrão em C++ que representa uma saída para arquivo (output file stream). 
    // Ele é usado para escrever dados em arquivos.
    ofstream file(filename, ios::out | ios::binary);

    // Esta linha verifica se o arquivo foi aberto com sucesso. 
    if (!file) {
        cerr << "Erro ao abrir o arquivo para salvar o modelo!" << endl;
        return;
    }

    // Salvar weights1
    for (int i = 0; i < weights1.size(); ++i) {
        file.write(reinterpret_cast<const char *>(&weights1(i)), sizeof(weights1(i)));
    }

    // Salvar weights2
    for (int i = 0; i < weights2.size(); ++i) {
        file.write(reinterpret_cast<const char *>(&weights2(i)), sizeof(weights2(i)));
    }

    file.close();
    cout << "Modelo salvo com sucesso em: " << filename << endl;
}

// Função de treino da rede neural
void dsa_treina_modelo(MatrixXd &X, VectorXd &y, MatrixXd &W1, MatrixXd &W2, double learning_rate, int iterations) {
    
    // Número de amostras
    int m = X.rows(); 

    for (int i = 0; i < iterations; ++i) {

        // Forward propagation
        MatrixXd Z1 = X * W1;
        MatrixXd A1 = sigmoid(Z1);
        MatrixXd Z2 = A1 * W2;
        MatrixXd A2 = Z2; // Sem função de ativação na saída para regressão

        // Calcula o erro
        MatrixXd error = A2 - y.replicate(1, A2.cols());
        
        // Backpropagation
        MatrixXd dZ2 = error;
        MatrixXd dW2 = A1.transpose() * dZ2 / m;
        MatrixXd dZ1 = (dZ2 * W2.transpose()).array() * sigmoid_derivative(A1).array();
        MatrixXd dW1 = X.transpose() * dZ1 / m;

        // Atualiza os pesos
        W1 -= learning_rate * dW1;
        W2 -= learning_rate * dW2;

        // Exibe erro de custo a cada 100 iterações
        if (i % 100 == 0) {
            double cost = error.array().square().mean();
            cout << "Iteração " << i << ", Custo: " << cost << endl;
        }
    }
}

int main() {

    // Dados de entrada de exemplo (4 amostras, 2 características + 1 bias)
    MatrixXd X(4, 3);
    X << 1, 1, 1,
         1, 2, 1,
         2, 2, 1,
         2, 3, 1; 
    
    // Saídas associadas (dados de saída)
    VectorXd y(4);
    y << 6, 8, 9, 11; 

    // Inicializa os pesos da rede neural (1 camada oculta de 3 neurônios)
    MatrixXd W1 = MatrixXd::Random(3, 3); // Pesos entre a entrada e a camada oculta
    MatrixXd W2 = MatrixXd::Random(3, 1); // Pesos entre a camada oculta e a saída

    // Treina a rede neural
    double learning_rate = 0.01;
    int iterations = 1000;
    dsa_treina_modelo(X, y, W1, W2, learning_rate, iterations);

    // Salva o modelo em disco
    string filename = "modelo_cpp_dsa.bin";
    dsa_salva_modelo(W1, W2, filename);

    return 0;
}
