// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Inclui o arquivo de cabeçalho onde a classe EncoderLayer é definida
#include "../include/07DSAEncoderLayer.hpp"

// Construtor da classe EncoderLayer, inicializa as subcamadas (SelfAttention, FeedForwardNetwork e LayerNorm)
EncoderLayer::EncoderLayer(int model_dim) : selfAttention(model_dim), feedForward(model_dim), layerNorm(model_dim) {}

// Função auxiliar que verifica se algum valor do vetor é NaN (Not a Number)
bool containsNaN(const std::vector<double>& vec) {
    
    // Usa std::any_of para detectar se algum valor no vetor é NaN
    return std::any_of(vec.begin(), vec.end(), [](float x) { return std::isnan(x); });
}

// Função que realiza o forward pass na camada do Encoder
std::vector<std::vector<double>> EncoderLayer::forward(const std::vector<std::vector<double>>& inputs) {
    
    // Vetor que armazenará os outputs da operação de self-attention
    std::vector<std::vector<double>> attentionOutputs;

    // Itera sobre cada entrada (um vetor representando um token ou embedding)
    for (const auto& input : inputs) {
        
        // Aplica a camada de self-attention no input
        auto attentionOutput = selfAttention.forward(input); 
        
        // Verifica se a saída contém NaN e, se sim, lança uma exceção
        if (containsNaN(attentionOutput)) {
            for (auto x : attentionOutput) {
                std::cerr << x << " ";
            }
            std::cerr << std::endl;
            for (auto x : input) {
                std::cerr << x << " ";
            }
            std::cerr << "NaN detected after self-attention" << std::endl;
            throw std::runtime_error("NaN detected after self-attention");  
        }

        // Adiciona o resultado da self-attention à lista de outputs
        attentionOutputs.push_back(attentionOutput);
    }

    // Vetor que armazenará os outputs após a primeira etapa de add e norm
    std::vector<std::vector<double>> addNorm1Outputs;
    
    // Itera sobre os inputs para realizar a soma residual e a normalização
    for (size_t i = 0; i < inputs.size(); ++i) {
        
        // Aplica a soma residual e a normalização
        // Soma o input original com o output da self-attention
        auto addNorm1 = layerNorm.normalize(add(inputs[i], attentionOutputs[i])); 
        if (containsNaN(addNorm1)) {
            std::cerr << "NaN detected after addNorm1" << std::endl;
            throw std::runtime_error("NaN detected after addNorm1");
        }
        
        // Armazena o resultado da soma e normalização
        addNorm1Outputs.push_back(addNorm1);
    }

    // Vetor que armazenará os outputs da rede feedforward
    std::vector<std::vector<double>> ffOutputs;

    // Itera sobre os outputs da primeira etapa (addNorm1Outputs) e passa pela rede feedforward
    for (const auto& addNorm1Output : addNorm1Outputs) {
        
        // Aplica a rede feedforward
        auto ffOutput = feedForward.forward(addNorm1Output); 
        if (containsNaN(ffOutput)) {
            std::cerr << "NaN detected after ffOutput" << std::endl;
            throw std::runtime_error("NaN detected after ffOutput");
        }
        
        // Armazena o resultado da feedforward network
        ffOutputs.push_back(ffOutput);
    }

    // Vetor que armazenará os outputs após a segunda etapa de add e norm
    std::vector<std::vector<double>> addNorm2Outputs;
    
    // Itera sobre os outputs da primeira etapa e os resultados da feedforward
    for (size_t i = 0; i < addNorm1Outputs.size(); ++i) {
        
        // Aplica a soma residual (add) e a normalização (norm) novamente
        // Soma o output da primeira normalização com o da feedforward
        auto addNorm2 = layerNorm.normalize(add(addNorm1Outputs[i], ffOutputs[i])); 
        if (containsNaN(addNorm2)) {
            std::cerr << "NaN detected after addNorm2" << std::endl;
            throw std::runtime_error("NaN detected after addNorm2");
        }
        
        // Armazena o resultado da segunda soma e normalização
        addNorm2Outputs.push_back(addNorm2);
    }

    // Retorna os outputs finais da camada do encoder
    return addNorm2Outputs;
}

// Função auxiliar que realiza a soma de dois vetores (elemento a elemento)
std::vector<double> EncoderLayer::add(const std::vector<double>& a, const std::vector<double>& b) const {
    
    // Vetor que armazenará o resultado da soma
    std::vector<double> result(a.size());
    
    // Itera sobre os elementos de 'a' e 'b', somando-os elemento a elemento
    for (size_t i = 0; i < a.size(); ++i) {
        result[i] = a[i] + b[i];
    }
    
    // Retorna o vetor resultante
    return result;
}
