// Lab 2 - Deep Learning Para Regressão com PyTorch em C++
// Criação do Modelo em C++

// Includes
#include <torch/torch.h>
#include <iostream>
#include <chrono>

using std::chrono::high_resolution_clock;

// Tempo de início da execução do script
auto t1 = high_resolution_clock::now();

// N é o batch size
const int64_t N = 64;

// D_in é a camada de entrada
const int64_t D_in = 1000;

// H é a camada oculta
const int64_t H = 100;

// D_out é a camada de saída
const int64_t D_out = 10;

// Cria o modelo
struct Lab : torch::nn::Module {

  // Construtor
  Lab() : linear1(D_in, H), linear2(H, D_out) {
    register_module("linear1", linear1);
    register_module("linear2", linear2);
  }

  // Método Forward
  torch::Tensor forward(torch::Tensor x) {
    x = torch::relu(linear1->forward(x));
    x = linear2->forward(x);
    return x;
  }

  // Variáveis 
  torch::nn::Linear linear1;
  torch::nn::Linear linear2;
};

// Função main
int main() {

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;

  // Seed
  torch::manual_seed(1);

  // Valores aleatórios para x e y
  torch::Tensor x = torch::rand({N, D_in});
  torch::Tensor y = torch::rand({N, D_out});
  torch::Device device(torch::kCPU); //kCUDA

  // Define o modelo
  Lab modelo;

  // Copia o modelo para o device
  modelo.to(device);

  // Taxa de aprendizado
  float_t learning_rate = 1e-4;

  // Otimizador
  torch::optim::SGD optimizer(modelo.parameters(), torch::optim::SGDOptions(learning_rate));

  // Loop de treinamento
  for (size_t epoch = 1; epoch <= 500; ++epoch) {

    // Previsão do modelo
    auto y_pred = modelo.forward(x);

    // Calcula o erro
    auto loss = torch::mse_loss(y_pred, y.detach());

    // Imprime o erro
    if (epoch%100 == 99)
      std::cout << "Epoch = " << epoch << " " << " - Erro = " << loss << "\n";

    // Zera os gradientes
    optimizer.zero_grad();

    // Backpropagation
    loss.backward();

    // Atualiza os pesos
    optimizer.step();
  }

  // Tempo final
  auto t2 = high_resolution_clock::now();
  
  // Calculando a duração
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "Tempo de execução = " << ms_double.count() << " ms" << "\n";

}
