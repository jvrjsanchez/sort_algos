// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se UTILS_H já foi definido, para evitar múltiplas inclusões
#ifndef UTILS_H

// Define UTILS_H se ainda não tiver sido definido
#define UTILS_H

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui a biblioteca matemática padrão (para funções como std::isnan, exp, etc.)
#include <cmath>

// Inclui a biblioteca padrão de entrada e saída (para depuração, se necessário)
#include <iostream>

// Inclui algoritmos genéricos (como std::any_of)
#include <algorithm>

// Inclui funções numéricas padrão (como std::accumulate)
#include <numeric>

// Declaração da classe Utils, contendo funções auxiliares
class Utils {
    
public:
    
    // Função estática que verifica se um vetor contém algum valor NaN (Not a Number)
    static bool containsNaN(const std::vector<double>& vec) {

        // Usa std::any_of para checar se algum elemento do vetor é NaN
        return std::any_of(vec.begin(), vec.end(), [](float x) { return std::isnan(x); });
    }

    // Função estática que aplica a função softmax a um vetor de scores
    static std::vector<double> softmax(const std::vector<double>& scores) {
        
        // Vetor que armazenará os valores exponenciais de cada score
        std::vector<double> expScores(scores.size());
        
        // Variável para armazenar a soma dos valores exponenciais
        double sumExpScores = 0.0;

        // Calcula a exponencial de cada score e soma os resultados
        for (size_t i = 0; i < scores.size(); ++i) {
            expScores[i] = std::exp(scores[i]);
            sumExpScores += expScores[i];
        }

        // Divide cada valor exponencial pela soma total para obter as probabilidades (softmax)
        for (size_t i = 0; i < expScores.size(); ++i) {
            expScores[i] /= sumExpScores;
        }

        // Retorna o vetor normalizado de probabilidades
        return expScores;
    }
};

#endif
