// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Inclui o arquivo de cabeçalho onde a classe PositionalEncoding é definida
#include "../include/03DSAPositionalEncoding.hpp"

// Construtor da classe PositionalEncoding, inicializa max_seq_len e model_dim, e calcula a matriz de codificação posicional
PositionalEncoding::PositionalEncoding(int max_seq_len, int model_dim) : max_seq_len(max_seq_len), model_dim(model_dim){
    
    // Redimensiona a matriz de codificação para o tamanho da sequência máxima e a dimensão do modelo
    encoding_matrix.resize(max_seq_len, std::vector<double>(model_dim));
    
    // Itera sobre cada posição da sequência
    for (int pos = 0; pos < max_seq_len; ++pos)
    {
        // Itera sobre as dimensões pares do modelo (usado para alternar seno e cosseno)
        for (int i = 0; i < model_dim; i += 2)
        {
            // Calcula a posição normalizada usando a fórmula de codificação posicional
            double position = pos / std::pow(10000.0, 2.0 * i / model_dim);
            
            // Atribui o valor do seno para a posição atual e dimensão par
            encoding_matrix[pos][i] = std::sin(position);
            
            // Se houver uma próxima dimensão, atribui o valor do cosseno à dimensão ímpar
            if (i + 1 < model_dim)
            {
                encoding_matrix[pos][i + 1] = std::cos(position);
            }
        }
    }
}

// Função que retorna a codificação posicional para uma posição específica
const std::vector<double>& PositionalEncoding::getEncoding(int pos){
    
    // Verifica se a posição está dentro do intervalo permitido
    if (pos < 0 || pos >= max_seq_len)
    {
        // Lança uma exceção se a posição estiver fora do intervalo
        throw std::out_of_range("PositionalEncoding::getEncoding: Position out of range.");
    }
    
    // Retorna a codificação posicional para a posição especificada
    return encoding_matrix[pos];
}

// Função que aplica a codificação posicional aos embeddings fornecidos
std::vector<std::vector<double>> *PositionalEncoding::getEncodings(std::vector<std::vector<double>> &embeddings){
    
    // Determina o comprimento da sequência como o menor valor entre o tamanho dos embeddings e a matriz de codificação
    int seq_len = std::min(embeddings.size(), encoding_matrix.size());
    
    // Aloca memória para armazenar as codificações finais
    std::vector<std::vector<double>> *encodings = new std::vector<std::vector<double>>(seq_len, std::vector<double>(this->model_dim));
    
    // Itera sobre cada posição da sequência
    for (int i = 0; i < seq_len; ++i)
    {
        // Itera sobre cada dimensão do embedding
        for (int j = 0; j < model_dim; ++j)
        {
            // Soma o valor da codificação posicional ao valor original do embedding
            (*encodings)[i][j] = embeddings[i][j] + encoding_matrix[i][j];
        }
    }
    
    // Retorna o ponteiro para as codificações finais
    return encodings;
}
