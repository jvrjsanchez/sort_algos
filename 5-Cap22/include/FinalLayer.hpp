// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se FINAL_LAYER_H já foi definido, para evitar múltiplas inclusões
#ifndef FINAL_LAYER_H

// Define FINAL_LAYER_H se ainda não tiver sido definido
#define FINAL_LAYER_H

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui a biblioteca matemática para funções como exp e log
#include <cmath>

// Inclui a biblioteca padrão de entrada e saída 
#include <iostream>

// Inclui algoritmos genéricos, como std::min e std::max
#include <algorithm>

// Inclui funções numéricas como std::accumulate
#include <numeric>

// Declaração da classe FinalLayer, responsável pela última camada do modelo
class FinalLayer {

public:
    
    // Construtor que inicializa as dimensões de entrada e saída da camada
    explicit FinalLayer(int input_dim, int output_dim);

    // Função que realiza o forward pass na última camada
    std::vector<double> forward(const std::vector<double>& input) const;
    
    // Função que atualiza os parâmetros (pesos e bias) com base nos gradientes
    void updateParameters(std::vector<double>& gradients, int index, double learning_rate);

private:
    
    // Dimensões de entrada e saída
    int input_dim, output_dim;
    
    // Matriz de pesos W (input_dim x output_dim)
    std::vector<std::vector<double>> W;
    
    // Vetor de bias b (output_dim)
    std::vector<double> b;

    // Função auxiliar que aplica uma transformação linear ao input
    std::vector<double> linear(const std::vector<double>& input) const;
    
    // Função auxiliar que aplica softmax para normalizar as saídas
    std::vector<double> softmax(const std::vector<double>& input) const;
};

#endif
