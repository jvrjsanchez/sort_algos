// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Este script implementa um pipeline de geração de texto usando arquitetura Transfomer com as seguintes etapas:

// Tokenização: Transformando texto em tokens.
// Embedding: Convertendo tokens em vetores densos.
// Codificação Posicional: Aplicando codificações posicionais aos embeddings.
// Encoder e Decoder: Usando arquitetura Transformer para processar os inputs e gerar outputs.
// Camada Final: Aplicando uma camada final para calcular as probabilidades de tokens de saída.
// Cálculo da Perda: Usando a perda de cross-entropy para calcular o erro entre a previsão e o valor real.

// Includes
#include <iostream>                               // Biblioteca para entrada e saída de dados
#include <fstream>                                // Biblioteca para manipulação de arquivos
#include "./include/01DSAEmbedding.hpp"           // Header para a classe de embeddings
#include "./include/02DSATokenizer.hpp"           // Header para a classe de tokenização
#include "./include/03DSAPositionalEncoding.hpp"  // Header para codificação posicional
#include "./include/04DSALayerNorm.hpp"           // Header para normalização de camadas
#include "./include/05DSASelfAttention.hpp"       // Header para mecanismo de self-attention
#include "./include/08DSAEncoder.hpp"             // Header para implementação do encoder
#include "./include/10DSADecoder.hpp"             // Header para implementação do decoder
#include "./include/FinalLayer.hpp"               // Header para a camada final de saída
#include "./include/VectorOp.hpp"                 // Header para operações de vetores

// Função para calcular a perda de cross-entropy com base nas probabilidades previstas e o token alvo
double computeCrossEntropyLoss(const std::vector<double> &predictedProbabilities, int targetTokenID)
{
    // Pegando a probabilidade prevista para o token alvo
    double predictedProbability = predictedProbabilities[targetTokenID];  

    // Epsilon para evitar divisão por zero
    double epsilon = 1e-8;  

    // Calculando a perda usando logaritmo
    double loss = -log(predictedProbability + epsilon);  

    return loss;
}

// Função para calcular o gradiente da perda em relação à saída da camada
std::vector<double> computeGradientOfLossWrtLayerOutput(const std::vector<double>& predictions, const std::vector<double>& trueLabels) {

    // Vetor para armazenar os gradientes
    std::vector<double> gradients(predictions.size());  

    // Calculando o gradiente para cada previsão
    for (size_t i = 0; i < predictions.size(); ++i) {

        // Diferença entre previsão e label real
        gradients[i] = predictions[i] - trueLabels[i];  
    }

    return gradients;
}

// Função principal
int main()
{

    // Inicializando o tokenizador
    Tokenizer tok;  

    // Variável para manipular o arquivo
    std::fstream file;  

    // Abrindo o arquivo de dados
    file.open("./dados/dataset.txt", std::ios::in);  

    // Vetor para armazenar as linhas do arquivo
    std::vector<std::string> text;  

    // Lendo o arquivo linha por linha
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty())
            {
                continue;  // Ignorando linhas vazias
            }

            text.push_back(line);  // Adicionando linha ao vetor de texto
        }
        file.close();  // Fechando o arquivo
    }
    else
    {
        // Erro se o arquivo não for encontrado
        std::cout << "Error: File not found" << std::endl;  

        // Saída com código de erro
        return 1;  
    }

    // Exibindo o número de linhas lidas
    std::cout << text.size() << std::endl;  

    // Vetor para armazenar as entradas
    std::vector<std::string> input_text;  

    // Vetor para armazenar as saídas esperadas
    std::vector<std::string> output_text;  

    // Vetor para armazenar os tokens das entradas
    std::vector<std::vector<int>> input_tokens;  

    // Vetor para armazenar os tokens das saídas
    std::vector<std::vector<int>> output_tokens;  

    // Processando o texto em pares de entrada e saída
    for (int i = 0; i < text.size(); i += 2)
    {
        input_text.push_back(text[i]);                       // Adicionando texto de entrada
        output_text.push_back(text[i + 1]);                  // Adicionando texto de saída
        input_tokens.push_back(tok.tokenize(text[i]));       // Tokenizando o texto de entrada
        output_tokens.push_back(tok.tokenize(text[i + 1]));  // Tokenizando o texto de saída
    }

    // Definindo o token de finalização
    std::string end_token = "<end>";  

    // Pegando o ID do token de finalização
    int end_token_id = tok.tokenize(end_token)[0];  

    // Vetor para armazenar as perdas
    std::vector<std::unordered_map<int, double>> losses;  

    // Vetor para armazenar os gradientes
    std::vector<std::vector<double>> gradients;  

    // Loop para processar cada par de entrada e saída
    for (int i = 0; i < input_text.size(); i++)
    {

        // Definindo a dimensionalidade do modelo
        int model_dim = 128;  

        // Obtendo o tamanho do vocabulário
        int vocab_size = tok.getVocabSize();  

        // Criando camada de embedding
        Embedding embedding(vocab_size, model_dim);  

        // Convertendo tokens de entrada para embeddings
        std::vector<std::vector<double>> *embedded_input = embedding.tokenToEmbeddings(input_tokens[i]);  

        // Convertendo tokens de saída para embeddings
        std::vector<std::vector<double>> *embedded_output = embedding.tokenToEmbeddings(output_tokens[i]); 

        // Criando camada de codificação posicional
        PositionalEncoding pe(640, model_dim);  

        // Aplicando codificações posicionais aos embeddings de entrada
        std::vector<std::vector<double>> *encoded_inputs = pe.getEncodings(*embedded_input);  

        // Aplicando codificações posicionais aos embeddings de saída
        std::vector<std::vector<double>> *encoded_outputs = pe.getEncodings(*embedded_output);  

        // Criando encoder com 6 camadas
        Encoder encoder(6, model_dim);  

        // Passando os dados pelo encoder
        std::vector<std::vector<double>> encoder_outputs = encoder.forward(*encoded_inputs);  

        // Criando decoder com 6 camadas
        Decoder decoder(6, model_dim);  

        // Passando os dados pelo decoder
        std::vector<std::vector<double>> *decoder_outputs = decoder.forward((*encoded_inputs), encoder_outputs);  

        // Criando a camada final para calcular probabilidades
        FinalLayer finalLayer(model_dim, vocab_size);  

        // Vetor para armazenar as probabilidades de saída
        std::vector<std::vector<double>> output_probabilities;  

        // Passando os outputs do decoder pela camada final para obter as probabilidades
        for (const auto &decoder_output : *decoder_outputs)
        {
            // Calculando as probabilidades de cada token
            std::vector<double> token_probabilities = finalLayer.forward(decoder_output);  

            // Armazenando as probabilidades
            output_probabilities.push_back(token_probabilities);  
        }

        // Vetor para armazenar os tokens de resposta amostrados
        std::vector<int> resp_tokens;  

        // Vetor para armazenar os tokens com maior probabilidade
        std::vector<int> resp_tokens_max;  

        // Inicializando o gerador de números aleatórios
        std::default_random_engine generator;  

        // Ajustando as probabilidades de saída para ter o mesmo tamanho que os tokens de saída
        size_t size_difference = std::max(output_probabilities[i].size(), output_tokens[i].size()) - std::min(output_probabilities[i].size(), output_tokens[i].size());

        // Caso as probabilidades de saída sejam menores que o número de tokens de saída, adiciona padding
        if (output_probabilities[i].size() < output_tokens[i].size())
        {
            // Probabilidade restante
            double remaining_probability = 0.49;  

            // Valor de padding para cada posição
            double pad_value = remaining_probability / (size_difference - 1);  

            // Inserindo valores de padding
            output_probabilities[i].insert(output_probabilities[i].end(), size_difference - 1, pad_value);  

            // Garantindo que o último valor seja maior que 0.5
            output_probabilities[i].push_back(0.51);  
        }

        // Caso o número de tokens de saída seja menor, adiciona tokens de finalização
        else if (output_probabilities[i].size() > output_tokens[i].size())
        {
            // Inserindo tokens de finalização
            output_tokens[i].insert(output_tokens[i].end(), size_difference, end_token_id);  

            // Garantindo que a última probabilidade seja maior que 0.5
            output_probabilities[i].back() = 0.51;  

            // Somando as probabilidades
            double sum = std::accumulate(output_probabilities[i].begin(), output_probabilities[i].end() - 1, 0.0);  

            // Probabilidade restante
            double remaining_probability = 0.49;  

             // Ajustando as probabilidades
            std::transform(output_probabilities[i].begin(), output_probabilities[i].end() - 1, output_probabilities[i].begin(),
                           [sum, remaining_probability](double &c)
                           { return (c / sum) * remaining_probability; }); 
        }

        // Processando os tokens e calculando perdas
        for (int j = 0; j < output_tokens[i].size(); j++)
        {
            // Pegando as probabilidades de saída
            std::vector<double> output_probability = output_probabilities[i];  

            // Pegando o token alvo
            int target_token_id = output_tokens[i][j];  

            // Distribuição discreta para amostragem de tokens
            std::discrete_distribution<int> distribution(output_probability.begin(), output_probability.end());  

            // Amostrando o token baseado nas probabilidades
            int sampled_token_id = distribution(generator);  

            // Armazenando o token amostrado
            resp_tokens.push_back(sampled_token_id);  

            // Pegando o token com maior probabilidade
            int max_token_id = std::distance(output_probability.begin(), std::max_element(output_probability.begin(), output_probability.end()));  

            // Armazenando o token com maior probabilidade
            resp_tokens_max.push_back(max_token_id);  

            // Calculando a perda de cross-entropy
            double loss = computeCrossEntropyLoss(output_probability, target_token_id);  
            std::unordered_map<int, double> temp_loss_map;

            // Armazenando a perda para o token alvo
            temp_loss_map[target_token_id] = loss;  

            // Adicionando a perda ao vetor de perdas
            losses.push_back(temp_loss_map);  
        }

        // Gerando a resposta prevista e removendo o token de finalização
        std::string response = tok.detokenize(resp_tokens);
        response = response.substr(0, response.find(end_token));

        // Exibindo a resposta prevista
        std::cout << "Valor Previsto: \n" << response << std::endl;  

        // Gerando a resposta real e removendo o token de finalização
        std::string actual_response = tok.detokenize(output_tokens[i]);
        actual_response = actual_response.substr(0, actual_response.find(end_token));

        // Exibindo a resposta real
        std::cout << "Valor Real: \n" << actual_response << std::endl;  
        std::cout << std::endl;
    }

    // Calculando o erro total e médio
    double total_loss = 0.0;
    for (const auto &loss_map : losses)
    {
        for (const auto &loss_entry : loss_map)
        {
            // Somando todas as perdas
            total_loss += loss_entry.second;  
        }
    }

    double average_loss = total_loss / losses.size();          // Calculando o erro médio
    std::cout << "Erro Total: " << total_loss << std::endl;    // Exibindo o erro total
    std::cout << "Erro Medio: " << average_loss << std::endl;  // Exibindo o erro médio

    return 0;  // Finalizando o programa
}
