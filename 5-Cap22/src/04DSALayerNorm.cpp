// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// A LayerNorm (normalização de camada) nos Transformers é usada para normalizar as ativações dentro de uma camada, estabilizando o treinamento da rede.

// Inclui o arquivo de cabeçalho onde a classe LayerNorm é definida
#include "../include/04DSALayerNorm.hpp"

// Construtor da classe LayerNorm, inicializa os vetores gamma e beta
LayerNorm::LayerNorm(int model_dim) : model_dim(model_dim) { 

    // Inicializa o vetor gamma com valores muito pequenos (0.001) para todas as dimensões
    gamma.resize(model_dim, 0.001f); 
    
    // Inicializa o vetor beta com valores zero (nenhum deslocamento inicialmente)
    beta.resize(model_dim, 0.0f); 
}

// Função que aplica a normalização de camada em um vetor de entrada
std::vector<double> LayerNorm::normalize(const std::vector<double>& input) const {
    
    // Calcula a média dos valores de entrada
    double mean = std::accumulate(input.begin(), input.end(), 0.0f) / input.size();

    // Calcula a variância
    double variance = 0.0f;

    for (double val : input) {

        // Soma dos quadrados das diferenças em relação à média
        variance += (val - mean) * (val - mean); 
    }
    
    // Divide pelo número de elementos para obter a variância
    variance /= input.size(); 

    // Define um pequeno valor para evitar divisão por zero
    const double epsilon = 1e-5; 
    
    // Vetor para armazenar o resultado normalizado
    std::vector<double> normalized(input.size());

    // Aplica a normalização para cada elemento do vetor de entrada
    for (size_t i = 0; i < input.size(); ++i) {
        
        // Normaliza o valor subtraindo a média e dividindo pelo desvio padrão
        normalized[i] = (input[i] - mean) / std::sqrt(variance + epsilon);
        
        // Aplica a escala gamma e o deslocamento beta
        normalized[i] = gamma[0] * normalized[i] + beta[0]; // Nota: gamma[0] e beta[0] são constantes aqui
    }

    // Retorna o vetor normalizado
    return normalized;
}
