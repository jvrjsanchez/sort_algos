// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Verifica se SELF_TOKENIZER_H já foi definido, para evitar múltiplas inclusões
#ifndef SELF_TOKENIZER_H

// Define SELF_TOKENIZER_H se não tiver sido definido ainda
#define SELF_TOKENIZER_H

// Inclui a biblioteca padrão de entrada e saída
#include <iostream>

// Inclui a biblioteca padrão de manipulação de strings
#include <sstream>

// Inclui a biblioteca padrão de vetores
#include <vector>

// Inclui a biblioteca padrão de mapas não ordenados (hash map)
#include <unordered_map>

// Inclui a biblioteca padrão para manipulação de arquivos
#include <fstream>

// Declaração da classe Tokenizer
class Tokenizer
{

private:
    
    // Mapa que relaciona palavras a IDs de tokens
    std::unordered_map<std::string, int> word_to_token_id; 
    
    // Mapa que relaciona IDs de tokens às palavras originais
    std::unordered_map<int, std::string> token_id_to_word; 
    
    // Tamanho do vocabulário (número de palavras únicas no vocabulário)
    int vocab_size;

public:
    
    // Construtor da classe Tokenizer
    Tokenizer();
    
    // Função que transforma um texto em uma sequência de IDs de tokens
    std::vector<int> tokenize(std::string text);
    
    // Função que retorna o tamanho do vocabulário
    int getVocabSize();
    
    // Função que imprime o mapa de palavras para IDs de tokens no console
    void printWordToTokenIdMap() const;
    
    // Função que transforma uma sequência de IDs de tokens de volta para uma string
    std::string detokenize(std::vector<int> tokens);
    
    // Função que salva o mapa de tokens em um arquivo
    void saveTokenMap(std::string filename);
    
    // Função que carrega o mapa de tokens de um arquivo
    void loadTokenMap(std::string filename);
    
    // Função que gera uma codificação one-hot para um token específico
    std::vector<std::vector<double>> oneHotEncode(int token_id);
    
    // Destrutor da classe Tokenizer
    ~Tokenizer();
};

// Encerra o bloco da definição condicional de SELF_TOKENIZER_H
#endif
