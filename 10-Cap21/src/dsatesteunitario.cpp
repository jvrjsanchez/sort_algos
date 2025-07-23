// Projeto 8 - Deep Learning com Rede Neural Convolucional em C++
// Módulo de Teste Unitário

// Um teste unitário é um tipo de teste de software que verifica se uma parte específica (ou "unidade") de código está funcionando corretamente. 
// Essas "unidades" normalmente correspondem a pequenas funções, métodos ou classes em um programa. O objetivo dos testes unitários é isolar 
// e validar o comportamento dessas partes individuais do código, garantindo que elas retornem os resultados esperados para diferentes entradas.

#undef NDEBUG            // Garante que as verificações com assert estejam ativas, mesmo em builds release
#include "dsamodelo.hpp" // Inclui a biblioteca do modelo de rede
#include <iostream>      // Inclui biblioteca de entrada e saída padrão

// Definição de constantes de tolerância e delta para verificação numérica
const float TOL = 0.01;                     // Tolerância para verificar se os valores estão corretos dentro de um limite
const float DELTA = 0.001;                  // Delta para calcular derivadas numéricas
std::default_random_engine random_gen{42};  // Gerador de números aleatórios com semente fixa

// Função para testar a criação e acesso de tensores
void test_Tensor() {
    std::cout << "Testando Tensor" << "\n";

    // Cria tensores com diferentes dimensões
    Tensor a(2);
    Tensor b(2, 2);
    Tensor c(2, 2, 2);
    Tensor d(2, 2, 2, 2);

    // Atribui valores e verifica com assert se os valores estão corretos
    a(1) = 1;
    assert(a(1) == 1);

    b(1, 1) = 1;
    assert(b(1, 1) == 1);

    c(1, 1, 1) = 1;
    assert(c(1, 1, 1) == 1);

    d(1, 1, 1, 1) = 1;
    assert(d(1, 1, 1, 1) == 1);
}

// Função para testar a camada ReLU
void test_ReLU() {
    std::cout << "Testando ReLU" << "\n";

    // Cria tensores de entrada e gradientes
    Tensor x(4);
    Tensor delta(4);
    ReLU relu;

    // Define os valores da entrada
    x(0) = -1;
    x(1) = -2;
    x(2) = 3;
    x(3) = 4;

    // Define os valores do delta (gradientes)
    delta(0) = 2;
    delta(1) = 2;
    delta(2) = 2;
    delta(3) = 2;

    // Executa a função ReLU e o cálculo do gradiente
    Tensor y = relu(x);
    Tensor deriv = relu.backward(delta);

    // Verifica se os valores de saída e gradientes estão corretos
    assert(y(0) == 0);
    assert(y(1) == 0);
    assert(y(2) == 3);
    assert(y(3) == 4);

    assert(deriv(0) == 0);
    assert(deriv(1) == 0);
    assert(deriv(2) == 2);
    assert(deriv(3) == 2);
}

// Função para testar a camada Conv2D
void test_Conv2D() {
    std::cout << "Testando Camada Conv2D" << "\n";

    // Cria uma imagem de entrada
    Tensor img(1, 28, 28);

    // Define os parâmetros da camada Conv2D
    int in_channels = 1;
    int out_channels = 4;
    int ksize = 2;
    int stride = 2;

    // Inicializa a camada convolucional
    Conv2D conv(in_channels, out_channels, ksize, stride); 

    // Preenche a imagem com valores aleatórios
    img.set_random(1.0, random_gen); 

    Tensor y = conv(img);      // Aplica a convolução
    assert(y.shape[0] == 4);   // Verifica a saída esperada
    assert(y.shape[1] == 14);
    assert(y.shape[2] == 14);

    // Prepara o delta para o cálculo do gradiente
    Tensor delta = y;
    delta.set_one();

    Tensor deriv = conv.backward(delta); // Calcula o gradiente da convolução
   
    // Calcula a derivada numérica e compara com a derivada analítica
    for (int i = 0; i < img.shape[1]; i++) {
        for (int j = 0; j < img.shape[2]; j++) {
            Tensor img2 = img;
            img2(0, i, j) += DELTA; // Pequena perturbação no tensor
            Tensor y2 = conv(img2); // Recalcula a saída

            float d = (y2 - y).sum() / DELTA; // Derivada numérica
            assert(std::abs(deriv(0, i, j) - d) < TOL); // Verifica se a diferença é aceitável
        }
    }
}

// Função para testar a camada Softmax
void test_Softmax() {
    std::cout << "Testando Softmax" << "\n";

    // Cria os tensores de entrada e gradientes
    Tensor x(3);
    Tensor delta(3);
    Softmax softmax;

    // Define os valores de entrada
    x(0) = -1;
    x(1) = 0; 
    x(2) = 1;

    // Define os valores do delta
    delta(0) = 1;
    delta(1) = 0;
    delta(2) = 0;

    // Aplica a função Softmax e calcula o gradiente
    Tensor y = softmax(x);
    Tensor deriv = softmax.backward(delta);

    // Verifica se os valores de saída estão corretos
    assert(std::abs(y(0) - 0.090031) < TOL);
    assert(std::abs(y(1) - 0.244728) < TOL);
    assert(std::abs(y(2) - 0.665241) < TOL);

    // Derivada numérica para comparação
    x(0) += DELTA;
    Tensor y1 = softmax(x);

    for (int i = 0; i < x.shape[0]; i++) {
        float d = (y1(i) - y(i)) / DELTA;     // Derivada numérica
        assert(std::abs(deriv(i) - d) < TOL); // Verifica se a derivada é próxima o suficiente
    }
}

// Função para testar a função de perda CrossEntropy
void test_CrossEntropyLoss() {
    std::cout << "Testando CrossEntropyLoss" << "\n";

    // Cria o tensor de probabilidades
    Tensor y(3);
    CrossEntropyLoss CELoss;
    int target = 1; // Rótulo esperado

    y(0) = 0.25;
    y(1) = 0.50;
    y(2) = 0.25;

    float loss = CELoss(y, target);         // Calcula a perda
    assert(std::abs(loss - 1.2685) < TOL);  // Verifica a perda

    // Calcula o gradiente da perda
    Tensor deriv = CELoss.backward(); 
    assert(std::abs(deriv(0) - 1.3333) < TOL);
    assert(std::abs(deriv(1) - -2) < TOL);
    assert(std::abs(deriv(2) - 1.3333) < TOL);

    // Derivada numérica para comparação
    for (int i = 0; i < y.shape[0]; i++) {
        Tensor y2 = y;
        y2(i) += DELTA;
        float loss2 = CELoss(y2, target);
        float dloss = (loss2 - loss) / DELTA;
        assert(std::abs(deriv(i) - dloss) < TOL); // Verifica se a diferença é aceitável
    }   
}

// Função para testar a camada Flatten
void test_Flatten() {    
    std::cout << "Testando Flatten" << "\n";

    // Cria os tensores de entrada e gradientes
    Tensor x(1, 2, 2);
    Tensor delta(4);
    Flatten flatten;

    // Define os valores da entrada
    x(0,0,0) = 1;
    x(0,0,1) = 2;
    x(0,1,0) = 3;
    x(0,1,1) = 4;

    // Define os valores do delta
    delta(0) = -1;
    delta(1) = -2;
    delta(2) = -3;
    delta(3) = -4;

    // Aplica a função Flatten e calcula o gradiente
    Tensor y = flatten(x);

    // Verifica as dimensões e os valores da saída
    assert(y.shape.size() == 1);
    assert(y(0) == 1);
    assert(y(1) == 2);
    assert(y(2) == 3);
    assert(y(3) == 4);

    Tensor d = flatten.backward(delta); // Calcula o gradiente da camada

    // Verifica as dimensões e os valores do gradiente
    assert(d.shape.size() == 3);
    assert(d(0,0,0) == -1);
    assert(d(0,0,1) == -2);
    assert(d(0,1,0) == -3);
    assert(d(0,1,1) == -4);
}

// Função para testar uma rede neural inteira
void test_network() {
    std::cout << "Testando a Rede Neural" << "\n";

    // Cria uma imagem de entrada aleatória
    Tensor img(1, 28, 28);
    img.set_random(1.0, random_gen);

    // Define a arquitetura da rede
    std::vector<Layer*> net {
        new Conv2D(1, 2, 2, 2), 
        new ReLU(),
        new Conv2D(2, 4, 2, 2), 
        new ReLU(),
        new Conv2D(4, 4, 2, 1), 
        new ReLU(),
        new Conv2D(4, 8, 2, 2),
        new ReLU(),
        new Conv2D(8, 10, 3), 
        new Flatten(),
        new Softmax()
    };

    // Inicializa os pesos da rede
    init_network_weight(net, random_gen); 

    CrossEntropyLoss CELoss;  // Inicializa a função de perda
    int target = 7;           // Rótulo esperado

    // Propaga a imagem pela rede
    Tensor x = img;
    for (Layer* layer: net) {
        std::cout << *layer << "\n";  // Imprime informações sobre a camada
        x = (*layer)(x);              // Propagação direta
    }

    float loss = CELoss(x, target);    // Calcula a perda
    Tensor delta = CELoss.backward();  // Calcula o gradiente da perda

    // Propagação reversa
    for (int l = net.size() - 1; l >= 0; l--) {
        delta = net[l]->backward(delta);
    }

    // Verifica a derivada numérica para a entrada da imagem
    int non_zero = 0;
    for (int i = 0; i < img.shape[1]; i++) {
        for (int j = 0; j < img.shape[2]; j++) {
            Tensor x = img;
            x(0, i, j) += DELTA; // Pequena perturbação no tensor

            for (Layer* layer: net) {
                x = (*layer)(x); // Propagação direta
            }

            float loss2 = CELoss(x, target);        // Recalcula a perda
            float dloss = (loss2 - loss) / DELTA;   // Derivada numérica

            if (dloss != 0) {
                non_zero++; // Conta quantos valores de gradiente não são zero
            }

            assert(std::abs(dloss - delta(0, i, j)) < TOL); // Verifica se o gradiente calculado é correto
        }
    }

    assert(non_zero > 0); // Verifica se existem gradientes não nulos
}

// Função para testar uma camada densa (fully connected)
void test_Dense() {
    std::cout << "Testando Camada Densa\n";

    // Cria os tensores de entrada e gradientes
    Tensor x(3);
    Tensor delta(2);
    Dense dense(3, 2); // Inicializa uma camada densa com 3 entradas e 2 saídas
    
    x.set_random(1.f, random_gen); // Preenche o tensor com valores aleatórios
    delta.set_one(); // Define o delta com valores de 1
    dense.weight.set_random(1.f, random_gen); // Inicializa os pesos aleatoriamente

    Tensor y = dense(x); // Calcula a saída da camada densa
    Tensor deriv = dense.backward(delta); // Calcula o gradiente da camada

    // Verifica as derivadas numéricas em comparação com as analíticas
    for (int i = 0; i < dense.weight.shape[0]; i++) {
        for (int j = 0; j < dense.weight.shape[1]; j++) {
            Tensor x2 = x;
            x2(j) += DELTA; // Pequena perturbação no tensor
            Tensor y2 = dense(x2); // Recalcula a saída
            float d = (y2(i) - y(i)) / DELTA; // Derivada numérica

            assert(std::abs(d - deriv(i, j)) < TOL); // Verifica se a diferença é aceitável
        }
    }
}

// Função para testar a métrica de acurácia e a matriz de confusão
void test_AccuracyMetric() {

    // Inicializa a métrica com 10 classes
    AccuracyMetric acc(10); 

    // Imprime a matriz de confusão
    std::cout << "Testando Formato da Confusion Matrix:\n";
    acc.print_confusion_matrix(); 
}

// Função principal do módulo de testes
int main() {

    std::cout << "\n";
    std::cout << "Iniciando os Testes Unitários!\n";
    std::cout << "\n";

    // Executa os testes unitários para cada componente
    test_Tensor();
    test_ReLU();
    test_Conv2D();
    test_Dense();
    test_Softmax();
    test_CrossEntropyLoss();
    test_Flatten();
    test_network();
    test_AccuracyMetric();

    std::cout << "\n";
    std::cout << "O programa passou em todos os testes!\n"; // Indica que todos os testes foram bem-sucedidos
    std::cout << "\n";
}
