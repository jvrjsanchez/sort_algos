// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se ENCODERLAYER_H já foi definido, para evitar múltiplas inclusões
#ifndef ENCODERLAYER_H

// Define ENCODERLAYER_H se ainda não tiver sido definido
#define ENCODERLAYER_H

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui o cabeçalho da classe LayerNorm, responsável pela normalização das camadas
#include "04DSALayerNorm.hpp"

// Inclui o cabeçalho da classe SelfAttention, que será usada nesta camada
#include "05DSASelfAttention.hpp"

// Inclui o cabeçalho da classe FeedForwardNetwork, que será usada nesta camada
#include "06DSAFeedForwardNetwork.hpp"

// Inclui a biblioteca padrão de entrada e saída (para depuração, se necessário)
#include <iostream>

// Inclui a biblioteca matemática padrão para operações como soma e raiz quadrada
#include <cmath>

// Declaração da classe EncoderLayer, que representa uma camada de encoder em uma arquitetura Transformer
class EncoderLayer {

public:
    
    // Construtor que inicializa a dimensão do modelo e configura os subcomponentes (self-attention, feedforward e layer norm)
    EncoderLayer(int model_dim);
    
    // Função que executa o forward pass da camada, recebendo os inputs e retornando os outputs processados
    std::vector<std::vector<double>> forward(const std::vector<std::vector<double>>& inputs) ;

private:
    
    // Subcomponente de self-attention responsável por capturar dependências globais nas entradas
    SelfAttention selfAttention;
    
    // Rede neural feedforward que aplica modelagem não linear
    FeedForwardNetwork feedForward;
    
    // Normalização da camada para estabilizar o treinamento
    LayerNorm layerNorm;

    // Função auxiliar que realiza a soma elemento a elemento entre dois vetores
    std::vector<double> add(const std::vector<double>& a, const std::vector<double>& b) const;
};

// Encerra a definição condicional de ENCODERLAYER_H
#endif
