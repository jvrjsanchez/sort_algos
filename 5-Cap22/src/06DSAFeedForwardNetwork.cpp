// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Em um modelo Transformers, a camada Feed Forward serve principalmente para adicionar capacidade de modelagem não linear. 
// Ela realiza transformações adicionais nas representações intermediárias de cada token (vetores de entrada) após a atenção ser aplicada.

// Inclui o arquivo de cabeçalho onde a classe FeedForwardNetwork é definida
#include "../include/06DSAFeedForwardNetwork.hpp"

// Construtor da classe FeedForwardNetwork
FeedForwardNetwork::FeedForwardNetwork(int model_dim) 
    : model_dim(model_dim) 
{
    // Inicializa os pesos e vieses para as duas camadas lineares

    W1.resize(hidden_dim, std::vector<double>(model_dim));
    b1.resize(hidden_dim);

    W2.resize(model_dim, std::vector<double>(hidden_dim));
    b2.resize(model_dim);

    initialize_weights(W1, hidden_dim, model_dim);
    initialize_bias(b1, hidden_dim);

    initialize_weights(W2, model_dim, hidden_dim);
    initialize_bias(b2, model_dim);
}

// Função para inicializar os pesos com valores aleatórios
void FeedForwardNetwork::initialize_weights(std::vector<std::vector<double>>& weights, int rows, int cols) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-0.1, 0.1);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            weights[i][j] = dis(gen);
        }
    }
}

// Função para inicializar os vieses
void FeedForwardNetwork::initialize_bias(std::vector<double>& bias, int size) {
    std::fill(bias.begin(), bias.end(), 0.0); // Inicializa vieses como 0
}

// Função de ativação ReLU
std::vector<double> FeedForwardNetwork::relu(const std::vector<double>& x) const {
    std::vector<double> output(x.size());
    for (size_t i = 0; i < x.size(); ++i) {
        output[i] = std::max(0.0, x[i]);
    }
    return output;
}

// Função que realiza o forward pass na rede feedforward
std::vector<double> FeedForwardNetwork::forward(const std::vector<double> &input) const {
    
    // Passo 1: Aplicar a primeira transformação linear: xW1 + b1
    std::vector<double> hidden_layer(hidden_dim, 0.0);
    for (int i = 0; i < hidden_dim; ++i) {
        for (int j = 0; j < model_dim; ++j) {
            hidden_layer[i] += input[j] * W1[i][j];
        }
        hidden_layer[i] += b1[i];
    }

    // Passo 2: Aplicar a função de ativação ReLU
    hidden_layer = relu(hidden_layer);

    // Passo 3: Aplicar a segunda transformação linear: hidden_layer * W2 + b2
    std::vector<double> output_layer(model_dim, 0.0);
    for (int i = 0; i < model_dim; ++i) {
        for (int j = 0; j < hidden_dim; ++j) {
            output_layer[i] += hidden_layer[j] * W2[i][j];
        }
        output_layer[i] += b2[i];
    }

    // Retorna o resultado da rede feedforward
    return output_layer;
}
