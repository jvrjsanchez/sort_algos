// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Inclui o arquivo de cabeçalho onde a classe DecoderLayer é definida
#include "../include/09DSADecoderLayer.hpp"

// Função que realiza o forward pass na camada do decoder, processando as entradas do decoder e os outputs do encoder
std::vector<std::vector<double>> DecoderLayer::forward(const std::vector<std::vector<double>>& decoderInput, const std::vector<std::vector<double>>& encoderOutput) {

    // Aplicação da self-attention no input do decoder
    std::vector<std::vector<double>> selfAttnOutput(decoderInput.size(), std::vector<double>(decoderInput[0].size()));
    
    for (size_t i = 0; i < decoderInput.size(); ++i) {
        
        // Self-attention é aplicada em cada token da sequência
        selfAttnOutput[i] = selfAttention.forward(decoderInput[i]);
    }

    // Soma residual entre a entrada do decoder e a saída da self-attention, seguida de normalização
    std::vector<std::vector<double>> addNorm1(decoderInput.size(), std::vector<double>(decoderInput[0].size()));
    
    for (size_t i = 0; i < decoderInput.size(); ++i) {
        
        // Soma da entrada original com a saída da self-attention e normalização (LayerNorm1)
        addNorm1[i] = layerNorm1.normalize(add(decoderInput[i], selfAttnOutput[i]));
    }

    // Aplicação da encoder-decoder attention (cross-attention)
    std::vector<std::vector<double>> encDecAttnOutput(addNorm1.size(), std::vector<double>(addNorm1[0].size()));
    
    for (size_t i = 0; i < addNorm1.size(); ++i) {
        
        // Cross-attention entre a saída da normalização e o output do encoder
        encDecAttnOutput[i] = encDecAttention.forward(addNorm1[i], encoderOutput);  
    }

    // Soma residual entre a saída da cross-attention e a saída da normalização anterior, seguida de normalização (LayerNorm2)
    std::vector<std::vector<double>> addNorm2(addNorm1.size(), std::vector<double>(addNorm1[0].size()));
    
    for (size_t i = 0; i < addNorm1.size(); ++i) {
        addNorm2[i] = layerNorm2.normalize(add(addNorm1[i], encDecAttnOutput[i]));
    }

    // Aplicação da rede feedforward para processamento adicional
    std::vector<std::vector<double>> ffOutput(addNorm2.size(), std::vector<double>(addNorm2[0].size()));
    
    for (size_t i = 0; i < addNorm2.size(); ++i) {
        ffOutput[i] = feedForward.forward(addNorm2[i]);
    }

    // Soma residual entre a saída da feedforward network e a saída da normalização anterior, seguida de normalização (LayerNorm3)
    std::vector<std::vector<double>> addNorm3(addNorm2.size(), std::vector<double>(addNorm2[0].size()));
    
    for (size_t i = 0; i < addNorm2.size(); ++i) {
        addNorm3[i] = layerNorm3.normalize(add(addNorm2[i], ffOutput[i]));
    }

    // Retorna o resultado final da camada após o processamento completo
    return addNorm3;
}

// Função que realiza o backward pass na camada do decoder (neste momento, é apenas um placeholder)
std::vector<std::vector<double>> DecoderLayer::backward(const std::vector<std::vector<double>>& dL_dOutputs, const std::vector<std::vector<double>>& encoderOutputs) {
    
    // Não implementado. Apenas retorna o que recebeu como entrada
    return dL_dOutputs;
}
