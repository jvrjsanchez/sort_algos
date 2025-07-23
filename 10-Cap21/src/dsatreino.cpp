// Projeto 8 - Deep Learning com Rede Neural Convolucional em C++
// Módulo de Treinamento

#include <iostream>
#include <algorithm> // Inclui funções de manipulação de algoritmos

#include "dsamodelo.hpp"  // Inclui a biblioteca para a definição do modelo de rede
#include "dsadataset.hpp" // Inclui a biblioteca para a manipulação de datasets

// Função para dividir o índice de treino em treino e validação com base em uma proporção
std::tuple<std::vector<size_t>, std::vector<size_t>> split_index(const std::vector<size_t> &train_idx, float validation_per) {
    
    assert(validation_per > 0 && validation_per < 1); // Assegura que a proporção de validação está dentro de um intervalo válido

    int valid_size = static_cast<int>(train_idx.size() * validation_per); // Calcula o tamanho do conjunto de validação
    int train_size = static_cast<int>(train_idx.size() - valid_size);     // Calcula o tamanho do conjunto de treino

    std::vector<size_t> valid_idx(valid_size);     // Cria um vetor para armazenar os índices de validação
    std::vector<size_t> new_train_idx(train_size); // Cria um vetor para armazenar os novos índices de treino

    // Copia os índices para o novo conjunto de treino
    std::copy(train_idx.begin(), train_idx.begin() + train_size, new_train_idx.begin());
    
    // Copia os índices para o conjunto de validação
    std::copy(train_idx.begin() + train_size, train_idx.end(), valid_idx.begin());

    // Retorna o conjunto de treino e validação
    return {new_train_idx, valid_idx};
}

// Função para calcular a média e o desvio padrão de um vetor de floats
std::tuple<double, double> mean_stdev(const std::vector<float> &x) {
    double mean = std::accumulate(x.begin(), x.end(), 0.0) / x.size(); // Calcula a média dos elementos
    double stdev = 0;

    // Calcula o desvio padrão
    for (float a : x) {
        stdev += (a - mean)*(a - mean);
    }

    // Conclui o cálculo do desvio padrão
    stdev = std::sqrt(stdev / x.size()); 

    // Retorna a média e o desvio padrão
    return {mean, stdev}; 
}

// Função principal do programa
int main(int argc, char **argv) {

    // Verifica se os argumentos foram passados corretamente
    if (argc < 5) {
        std::cout << "Execute assim: ./programa [train_images] [train_labels] [test_images] [test_labels]\n";
        return 1;
    }

    std::cout << "\n";
    std::cout << "Iniciando o Treinamento!\n";
    std::cout << "\n";

    // Configurações de hiperparâmetros
    int iterations = 10;          // Número de iterações (epochs)
    int batch_size = 64;          // Tamanho do batch (lote)
    float lr = 0.01;              // Taxa de aprendizado
    float momentum = 0.9;         // Momentum do otimizador
    int num_classes = 10;         // Número de classes
    float validation_per = 0.05;  // Proporção de validação

    // Gerador de números aleatórios com semente fixa
    std::default_random_engine random_gen{42}; 

    // Inicializa os datasets de treino e teste
    DSA_Dataset train(argv[1], argv[2]);
    DSA_Dataset test(argv[3], argv[4]);

    // Configura a arquitetura da rede neural convolucional
    std::vector<Layer*> net {
        new Conv2D(1, 4, 2, 2),  
        new ReLU(),
        new Conv2D(4, 8, 2, 2),  
        new ReLU(),
        new Conv2D(8, 8, 2, 1),  
        new ReLU(),
        new Conv2D(8, 16, 2, 2), 
        new ReLU(),
        new Conv2D(16, 10, 3),   
        new Flatten(),
        new Softmax()
    };

    // Imprime as informações da rede
    print_network_info(net); 

    // Inicializa os pesos da rede
    init_network_weight(net, random_gen); 

    // Inicializa a função de perda e a métrica de acurácia
    CrossEntropyLoss CELoss;
    AccuracyMetric accuracy(num_classes);

    // Inicializa os índices de treino 
    std::vector<size_t> train_idx(train.labels.size());
    for (size_t k = 0; k < train_idx.size(); k++) {
        train_idx[k] = k;
    } 
    std::ranges::shuffle(train_idx, random_gen);

    // Divide o conjunto de treino em treino e validação
    std::vector<size_t> valid_idx;
    std::tie(train_idx, valid_idx) = split_index(train_idx, validation_per);

    std::cout << "Tamanho Dataset de Treino: " << train_idx.size() << "\n";
    std::cout << "Tamanho Dataset de Validação: " << valid_idx.size() << "\n";

    // Loop de iteração do treinamento
    for (int i = 0; i < iterations; i++) {

        // Embaralha os índices de treino
        std::ranges::shuffle(train_idx, random_gen); 

        // Limpa as métricas de acurácia
        accuracy.clear(); 
        double sum_loss = 0;

        // Armazena as ativações das camadas
        std::vector<float> acts[net.size()]; 

        // Lida com o processamento em batches
        for (size_t j = 0; j < train_idx.size(); j+=batch_size) {
            for (int k = 0; k < batch_size; k++) {
                if (j + k >= train_idx.size()) {
                     break;
                 }

                // Índice da amostra atual
                int idx = train_idx[j + k]; 

                // Obtém a imagem de treino
                Tensor x = train.get_image(idx); 

                // Obtém o rótulo correspondente
                int target = train.labels[idx]; 

                // Propagação direta
                for (size_t l = 0; l < net.size(); l++) {
                    Layer *layer = net[l];
                    x = (*layer)(x);

                    // Armazena as ativações
                    acts[l].insert(acts[l].end(), x.data.begin(), x.data.end()); 
                }

                // Atualiza a métrica de acurácia
                accuracy.update(x, target); 

                // Calcula a perda
                float loss = CELoss(x, target); 
                sum_loss += loss;

                // Propagação reversa do erro
                Tensor delta = CELoss.backward(); 

                for (int l = net.size() - 1; l >= 0; l--) {

                    // Atualiza os deltas nas camadas
                    delta = net[l]->backward(delta); 
                }
            }

            // Atualiza os pesos com o otimizador SGD
            SGD_weight_update(net, lr, momentum); 
        }

        // Calcula a perda média e a acurácia de treino
        double avg_loss = sum_loss / train_idx.size();
        float train_accuracy = accuracy.accuracy();

        // Validação
        accuracy.clear();
        for (auto idx : valid_idx) {
            Tensor x = train.get_image(idx);
            int target = train.labels[idx];

            for (auto layer: net) {
                x = (*layer)(x); // Propagação direta no conjunto de validação
            }

            accuracy.update(x, target); // Atualiza a acurácia de validação
        }

        float valid_accuracy = accuracy.accuracy(); // Acurácia de validação

        // Exibe as métricas da iteração atual
        std::cout << "\n";
        std::cout << "Iteração " << i << ": Erro Médio: " << avg_loss << ", Acurácia em Treino: " << train_accuracy << ", Acurácia em Validação: " << valid_accuracy << "\n";

        // Exibe as estatísticas das ativações de cada camada
        for (size_t j = 0; j < net.size(); j++) {
            auto[mean, stdev] = mean_stdev(acts[j]);
            std::cout << "\n";
            std::cout << "  Camada " << j << ": output mean=" << mean << " stdev=" << stdev << "\n";
        }
    }

    // Avaliação no conjunto de teste
    accuracy.clear();
    for (size_t i = 0; i < test.labels.size(); i++) {
        Tensor x = test.get_image(i);
        for (auto layer: net) {
            x = (*layer)(x); // Propagação direta no conjunto de teste
        }

        // Atualiza a acurácia de teste
        accuracy.update(x, test.labels[i]); 
    }

    std::cout << "\n";
    std::cout << "Acurácia em Teste: " << accuracy.accuracy() << "\n"; // Exibe a acurácia final em teste
    std::cout << "Matriz de Confusão Para os Dados de Teste:\n";
    std::cout << "\n";
    accuracy.print_confusion_matrix(); // Exibe a matriz de confusão

    // Libera a memória alocada para as camadas da rede
    for (auto layer : net) {
        delete layer;
    }

    std::cout << "\n";
    std::cout << "Treinamento Concluído!\n"; // Indica o término do treinamento
    std::cout << "\n";

    return 0; // Retorna 0 para indicar execução bem-sucedida
}
