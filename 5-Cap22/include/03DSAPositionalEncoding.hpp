// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se POSITIONAL_ENCODING_H já foi definido, para evitar múltiplas inclusões
#ifndef POSITIONAL_ENCODING_H

// Define POSITIONAL_ENCODING_H se não tiver sido definido ainda
#define POSITIONAL_ENCODING_H

// Inclui a biblioteca matemática padrão para funções como seno e cosseno
#include <cmath>

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui a biblioteca padrão de exceções
#include <stdexcept>

// Inclui a biblioteca padrão de entrada e saída para depuração e exibição
#include <iostream>

// Declaração da classe PositionalEncoding
class PositionalEncoding {

public:
    
    // Construtor que inicializa o comprimento máximo da sequência e a dimensão do modelo
    PositionalEncoding(int max_seq_len, int model_dim);
    
    // Função que retorna a codificação posicional para uma posição específica
    const std::vector<double>& getEncoding(int pos);
    
    // Função que aplica a codificação posicional a um conjunto de embeddings e retorna um ponteiro para os embeddings modificados
    std::vector<std::vector<double>> *getEncodings(std::vector<std::vector<double>> &embeddings);

private:
    
    // Comprimento máximo da sequência
    int max_seq_len;
    
    // Dimensão do modelo, ou seja, o tamanho da representação de cada token
    int model_dim;
    
    // Matriz que armazena as codificações posicionais para cada posição da sequência
    std::vector<std::vector<double>> encoding_matrix;
};

// Encerra o bloco de definição condicional de POSITIONAL_ENCODING_H
#endif
