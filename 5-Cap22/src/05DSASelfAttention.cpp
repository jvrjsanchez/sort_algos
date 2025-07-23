// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Inclui o arquivo de cabeçalho onde a classe SelfAttention é definida
#include "../include/05DSASelfAttention.hpp"

// Construtor da classe SelfAttention, inicializa os pesos W_q, W_k e W_v aleatoriamente
SelfAttention::SelfAttention(int model_dim) : model_dim(model_dim) {
    
    // Gera números aleatórios
    std::random_device rd;
    std::mt19937 gen(rd());

    // Define o intervalo para os pesos com base na dimensão do modelo
    double range = std::sqrt(6.0 / model_dim);  
    
    // Cria uma distribuição uniforme entre -range e range
    std::uniform_real_distribution<> distr(-range, range);

    // Inicializa as matrizes de pesos W_q, W_k, W_v com valores aleatórios
    for (auto* weight_matrix : {&W_q, &W_k, &W_v}) {

        // Redimensiona cada matriz de pesos
        weight_matrix->resize(model_dim);  
        for (auto& row : *weight_matrix) {

            // Redimensiona cada linha da matriz
            row.resize(model_dim);  
            for (auto& elem : row) {

                // Atribui um valor aleatório a cada elemento
                elem = distr(gen);  
            }
        }
    }
}

// Função que realiza o forward pass da self-attention
std::vector<double> SelfAttention::forward(const std::vector<double>& input) const {
    
    // Computa as queries (Q), keys (K) e values (V) aplicando as matrizes de pesos
    auto Q = this->multiply(W_q, input);
    auto K = this->multiply(W_k, input);
    auto V = this->multiply(W_v, input);
    
    // Verifica se algum valor de Q, K ou V contém NaN (Not a Number)
    if (Utils::containsNaN(Q) || Utils::containsNaN(K) || Utils::containsNaN(V)) {
        for (auto x : Q) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        for (auto x : K) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        for (auto x : V) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }

    // Calcula o produto escalar entre Q e K, e ajusta pelo fator de escala
    double score = std::inner_product(Q.begin(), Q.end(), K.begin(), 0.0f) / std::sqrt(model_dim);
    
    // Verifica se o score calculado é NaN
    if (std::isnan(score)) {
        std::cout << "Score: " << score << std::endl;
    } 

    // Calcula o peso da atenção usando a função exponencial no score (operação softmax)
    double attention_weight = std::exp(score) / std::exp(score); 

    // Verifica se o peso da atenção é NaN e corrige para 1
    if (std::isnan(attention_weight)) {
        attention_weight = 1;
    }

    // Verifica novamente se há NaN em Q, K, V, score ou attention_weight
    if (std::isnan(attention_weight)) {
        for (auto x : Q) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        for (auto x : K) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        for (auto x : V) {
            std::cout << x << " ";
        }
        std::cout << std::endl;
        std::cout << "Score: " << score << std::endl;
        std::cout << "Attention weight: " << attention_weight << std::endl;
    }

    // Calcula a saída final multiplicando o valor V pelo peso da atenção
    std::vector<double> output(model_dim);
    for (int i = 0; i < model_dim; ++i) {

        // Atribui o valor ponderado ao output
        output[i] = attention_weight * V[i]; 
    }

    // Retorna o resultado final da atenção
    return output; 
}

// Função que realiza a multiplicação de uma matriz por um vetor
std::vector<double> SelfAttention::multiply(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) const {
    
    // Inicializa o vetor de resultado com zeros
    std::vector<double> result(matrix.size(), 0.0f);
    
    // Realiza a multiplicação matriz-vetor
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < vector.size(); ++j) {

            // Soma o produto de cada elemento
            result[i] += matrix[i][j] * vector[j]; 
        }
    }

    // Retorna o vetor resultante
    return result; 
}

// Função que implementa a atenção cruzada (encoder-decoder attention)
std::vector<double> SelfAttention::forward(const std::vector<double> &input, const std::vector<std::vector<double>> &encoder_input) const {
    
    // Esta implementação é um placeholder que retorna o input sem modificações
    return input;
}
