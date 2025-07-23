// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se ENCODER_H já foi definido, para evitar múltiplas inclusões
#ifndef ENCODER_H

// Define ENCODER_H se ainda não tiver sido definido
#define ENCODER_H

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui o cabeçalho da classe EncoderLayer, que será usada no Encoder
#include "07DSAEncoderLayer.hpp"

// Declaração da classe Encoder
class Encoder {

public:
    
    // Construtor que inicializa o número de camadas e a dimensão do modelo
    Encoder(int num_layers, int model_dim);

    // Função que realiza o forward pass no encoder, recebendo um vetor de inputs e retornando o resultado
    std::vector<std::vector<double>> forward(const std::vector<std::vector<double>>& inputs);

private:
    
    // Número de camadas no encoder
    int num_layers;
    
    // Dimensão do modelo (o tamanho da representação de cada token)
    int model_dim;
    
    // Vetor que armazena as camadas do encoder (cada uma é uma instância de EncoderLayer)
    std::vector<EncoderLayer> layers;
};

// Encerra a definição condicional de ENCODER_H
#endif
