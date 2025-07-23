// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se LAYERNORM_H já foi definido, para evitar múltiplas inclusões
#ifndef LAYERNORM_H

// Define LAYERNORM_H se ainda não tiver sido definido
#define LAYERNORM_H

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui a biblioteca padrão de entrada e saída (para depuração, se necessário)
#include <iostream>

// Inclui a biblioteca matemática padrão para operações como raiz quadrada
#include <cmath>

// Inclui a biblioteca padrão para algoritmos genéricos (como std::min, std::max)
#include <algorithm>

// Inclui a biblioteca padrão para operações numéricas (como soma)
#include <numeric>

// Declaração da classe LayerNorm, que implementa a normalização por camada
class LayerNorm {

public:
    
    // Construtor que inicializa a dimensão do modelo e os vetores gamma e beta
    explicit LayerNorm(int model_dim);

    // Função que aplica a normalização nos dados de entrada
    std::vector<double> normalize(const std::vector<double>& input) const;

private:
    
    // Dimensão do modelo (tamanho da representação vetorial)
    int model_dim;
    
    // Vetor de escala (gamma) e deslocamento (beta) para a normalização
    std::vector<double> gamma, beta;
};

#endif
