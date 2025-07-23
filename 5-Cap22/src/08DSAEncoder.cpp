// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Inclui o arquivo de cabeçalho onde a classe Encoder é definida
#include "../include/08DSAEncoder.hpp"

// Construtor da classe Encoder, inicializa o número de camadas e a dimensão do modelo
Encoder::Encoder(int num_layers, int model_dim) : num_layers(num_layers), model_dim(model_dim) {
    
    // Adiciona 'num_layers' instâncias de EncoderLayer ao vetor 'layers'
    for (int i = 0; i < num_layers; ++i) {
        
        // Cria uma nova camada de EncoderLayer com a dimensão do modelo e adiciona à lista de camadas
        layers.push_back(EncoderLayer(model_dim));
    }
}

// Função que realiza o forward pass no encoder, processando os inputs através das camadas de Encoder
std::vector<std::vector<double>> Encoder::forward(const std::vector<std::vector<double>>& inputs) {
    
    // Inicializa os outputs como sendo os próprios inputs
    auto outputs = inputs;
    
    // Itera sobre cada camada do encoder e passa os outputs pela camada
    for (auto& layer : this->layers) {
        
        // Atualiza os outputs ao aplicar a função forward da camada atual
        outputs = layer.forward(outputs);
    }
    
    // Retorna os outputs finais após passar por todas as camadas
    return outputs;
}
