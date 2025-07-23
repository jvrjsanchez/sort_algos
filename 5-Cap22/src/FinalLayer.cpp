// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Inclui o arquivo de cabeçalho onde a classe FinalLayer é definida
#include "../include/FinalLayer.hpp"

// Construtor da classe FinalLayer, inicializa os pesos e bias
FinalLayer::FinalLayer(int input_dim, int output_dim) : input_dim(input_dim), output_dim(output_dim) {
    
    // Inicializa a matriz de pesos W com valores constantes (0.1f)
    W.resize(output_dim, std::vector<double>(input_dim, 0.1f)); 
    
    // Inicializa o vetor de bias b com zeros
    b.resize(output_dim, 0.0f); 
}

// Função que realiza o forward pass: aplica a transformação linear e depois a softmax
std::vector<double> FinalLayer::forward(const std::vector<double>& input) const {
    
    // Primeiro aplica a transformação linear
    auto z = linear(input);
    
    // Em seguida, aplica a softmax para normalizar as saídas
    return softmax(z);
}

// Função que aplica a transformação linear (W * input + b)
std::vector<double> FinalLayer::linear(const std::vector<double>& input) const {
    
    // Vetor de saída inicializado com zeros
    std::vector<double> output(output_dim, 0.0f);
    
    // Realiza a multiplicação matriz-vetor e adiciona o bias
    for (int i = 0; i < output_dim; ++i) {
        for (int j = 0; j < input_dim; ++j) {

            // Multiplica a entrada pelo peso
            output[i] += W[i][j] * input[j]; 
        }

        // Adiciona o bias ao resultado final
        output[i] += b[i]; 
    }

    // Retorna o vetor resultante da transformação linear
    return output; 
}

// Função que atualiza os parâmetros (pesos W) com base nos gradientes e taxa de aprendizado
void FinalLayer::updateParameters(std::vector<double>& gradients, int index, double learning_rate) {
    
    // Atualiza os pesos da linha correspondente ao índice "index" com base nos gradientes
    for (size_t j = 0; j < W[index].size(); ++j) {

        // Atualiza o peso W com base no gradiente
        W[index][j] -= learning_rate * gradients[j];  
    }
}

// Função que aplica a softmax para normalizar as saídas em forma de probabilidades
std::vector<double> FinalLayer::softmax(const std::vector<double>& input) const {
    
    // Vetor de saída inicializado com zeros
    std::vector<double> output(input.size(), 0.0f);
    
    // Encontra o valor máximo da entrada para estabilidade numérica (evitar overflow)
    double maxElement = *max_element(input.begin(), input.end());
    
    // Soma acumulada para normalizar a softmax
    double sum = 0.0f;

    // Aplica a função exponencial ao input e calcula a soma
    for (size_t i = 0; i < input.size(); ++i) {

        // Subtrai o máximo para estabilidade
        output[i] = std::exp(input[i] - maxElement); 
        sum += output[i];
    }

    // Divide cada elemento da softmax pela soma total para normalizar
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] /= sum;
    }

    // Retorna o vetor normalizado
    return output; 
}
