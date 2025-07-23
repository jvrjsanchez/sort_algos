// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se SELF_ATTENTION_H já foi definido, para evitar múltiplas inclusões
#ifndef SELF_ATTENTION_H

// Define SELF_ATTENTION_H se ainda não tiver sido definido
#define SELF_ATTENTION_H

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui a biblioteca padrão de entrada e saída (para depuração, se necessário)
#include <iostream>

// Inclui a biblioteca matemática padrão para operações como raiz quadrada
#include <cmath>

// Inclui a biblioteca padrão de algoritmos, como std::min e std::max
#include <algorithm>

// Inclui o cabeçalho do arquivo "HelpFunc.h" para funções auxiliares
#include "HelpFunc.hpp"

// Inclui a biblioteca padrão para operações numéricas
#include <numeric>

// Inclui exceções padrão
#include <stdexcept>

// Inclui a biblioteca padrão para gerar números aleatórios
#include <random>

// Declaração da classe SelfAttention, que implementa o mecanismo de atenção
class SelfAttention {

private:
    
    // Dimensão do modelo (tamanho da representação vetorial)
    int model_dim;
    
    // Matrizes de pesos para as transformações de query (W_q), key (W_k) e value (W_v)
    std::vector<std::vector<double>> W_q, W_k, W_v;

public:

    // Construtor que inicializa a dimensão do modelo e os pesos da atenção
    explicit SelfAttention(int model_dim);

    // Função que realiza o forward pass, computando a autoatenção (self-attention)
    std::vector<double> forward(const std::vector<double> &input) const;
    
    // Função que multiplica uma matriz por um vetor, usada nos cálculos da atenção
    std::vector<double> multiply(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector) const;

    // Função forward que utiliza a atenção cruzada entre a entrada e os outputs do encoder
    std::vector<double> forward(const std::vector<double> &input, const std::vector<std::vector<double>> &encoder_input) const;

    // Função que computa as pontuações de atenção (scores de atenção) entre Q e K
    std::vector<double> computeAttentionScores(const std::vector<double>& Q, const std::vector<std::vector<double>>& K);

};

#endif
