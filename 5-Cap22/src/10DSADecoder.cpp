// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Inclui o arquivo de cabeçalho onde a classe Decoder é definida
#include "../include/10DSADecoder.hpp"

// Construtor da classe Decoder, inicializa o número de camadas e a dimensão do modelo
Decoder::Decoder(int num_layers, int model_dim) : num_layers(num_layers), model_dim(model_dim) {
    
    // Cria 'num_layers' instâncias de DecoderLayer e adiciona ao vetor 'layers'
    for (int i = 0; i < num_layers; ++i) {
        layers.push_back(DecoderLayer(model_dim));
    }
}

// Função que realiza o forward pass no decoder
std::vector<std::vector<double>> *Decoder::forward(const std::vector<std::vector<double>>& input, const std::vector<std::vector<double>>& encoderOutput) {
    
    // Inicializa os outputs como uma cópia dos inputs
    std::vector<std::vector<double>> *outputs = new std::vector<std::vector<double>>(input);
    
    // Itera sobre as camadas do decoder e aplica o forward de cada uma
    for (auto& layer : layers) {

        // Atualiza os outputs ao aplicar a camada de Decoder, passando os encoder outputs
        (*outputs) = layer.forward((*outputs), encoderOutput);
    }

    // Retorna os outputs finais após passar por todas as camadas do decoder
    return outputs;
}

// Função que realiza o backward pass no decoder, propagando os gradientes
void Decoder::backward(const std::vector<std::vector<double>>& dL_dDecoderOutputs, const std::vector<std::vector<double>>& encoderOutputs) {
    
    // Inicializa os gradientes da entrada como os gradientes da saída do decoder
    std::vector<std::vector<double>> dL_dInputs = dL_dDecoderOutputs;

    // Itera sobre as camadas do decoder em ordem reversa (para o backward pass)
    for (auto it = layers.rbegin(); it != layers.rend(); ++it) {
        
        // Aplica o backward pass em cada camada, atualizando os gradientes da entrada
        dL_dInputs = it->backward(dL_dInputs, encoderOutputs);
    }
}
