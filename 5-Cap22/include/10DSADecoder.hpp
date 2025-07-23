// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se DECODER_H já foi definido, para evitar múltiplas inclusões
#ifndef DECODER_H

// Define DECODER_H se ainda não tiver sido definido
#define DECODER_H

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui o cabeçalho da classe DecoderLayer, que será usada na construção do Decoder
#include "09DSADecoderLayer.hpp"

// Declaração da classe Decoder, responsável pela parte do decoder em uma arquitetura Transformer
class Decoder
{

public:
    
    // Construtor que inicializa o número de camadas e a dimensão do modelo
    Decoder(int num_layers, int model_dim);

    // Função que realiza o forward pass no decoder, recebendo as entradas e as saídas do encoder
    std::vector<std::vector<double>> *forward(const std::vector<std::vector<double>> &input, const std::vector<std::vector<double>> &encoderOutput);
    
    // Função que realiza o backward pass no decoder, propagando os gradientes
    void backward(const std::vector<std::vector<double>> &dL_dDecoderOutputs, const std::vector<std::vector<double>> &encoderOutputs);

private:
    
    // Número de camadas no decoder
    int num_layers;
    
    // Dimensão do modelo (o tamanho da representação de cada token)
    int model_dim;
    
    // Vetor que armazena as camadas do decoder (cada uma é uma instância de DecoderLayer)
    std::vector<DecoderLayer> layers;
};

#endif
