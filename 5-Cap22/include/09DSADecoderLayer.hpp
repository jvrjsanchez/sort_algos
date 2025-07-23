// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se DECODERLAYER_H já foi definido, para evitar múltiplas inclusões
#ifndef DECODERLAYER_H

// Define DECODERLAYER_H se ainda não tiver sido definido
#define DECODERLAYER_H

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui o cabeçalho da classe LayerNorm, usada para normalização em várias etapas
#include "04DSALayerNorm.hpp"

// Inclui o cabeçalho da classe SelfAttention, usada para self-attention e encoder-decoder attention
#include "05DSASelfAttention.hpp"

// Inclui o cabeçalho da classe FeedForwardNetwork, usada para processar os embeddings após as atenções
#include "06DSAFeedForwardNetwork.hpp"

// Declaração da classe DecoderLayer, que representa uma camada do decoder em uma arquitetura Transformer
class DecoderLayer {

public:

    // Construtor que inicializa as subcamadas: duas Self-Attention, uma FeedForward e três LayerNorm
    DecoderLayer(int model_dim) : 
        selfAttention(model_dim),   // Atenção interna do decoder (self-attention)
        encDecAttention(model_dim), // Atenção entre encoder e decoder (cross-attention)
        feedForward(model_dim),     // Rede feedforward para processamento posterior
        layerNorm1(model_dim),      // Normalização após self-attention
        layerNorm2(model_dim),      // Normalização após encoder-decoder attention
        layerNorm3(model_dim)       // Normalização após a feedforward network
    {}

    // Função que realiza o forward pass na camada do decoder, processando as entradas do decoder e os outputs do encoder
    std::vector<std::vector<double>> forward(const std::vector<std::vector<double>>& decoderInput, const std::vector<std::vector<double>>& encoderOutput);
    
    // Função que realiza o backward pass, calculando os gradientes para as entradas do decoder e os outputs do encoder
    std::vector<std::vector<double>> backward(const std::vector<std::vector<double>>& dL_dOutputs, const std::vector<std::vector<double>>& encoderOutputs);

private:
    
    // Instância de self-attention, usada para processar as dependências dentro da sequência do decoder
    SelfAttention selfAttention;
    
    // Instância de encoder-decoder attention (cross-attention), que conecta as saídas do encoder às entradas do decoder
    SelfAttention encDecAttention; 
    
    // Rede neural feedforward para processamento adicional dos embeddings
    FeedForwardNetwork feedForward;
    
    // Três normalizações de camada: uma após self-attention, outra após cross-attention e uma após feedforward
    LayerNorm layerNorm1, layerNorm2, layerNorm3;

    // Função auxiliar que realiza a soma de dois vetores, elemento a elemento
    std::vector<double> add(const std::vector<double>& a, const std::vector<double>& b) const {
        std::vector<double> result(a.size());
        
        // Soma cada elemento de 'a' com o correspondente em 'b'
        for (size_t i = 0; i < a.size(); ++i) {
            result[i] = a[i] + b[i];
        }
        return result;
    }
};

#endif
