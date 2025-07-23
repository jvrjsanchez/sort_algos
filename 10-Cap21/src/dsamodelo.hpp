// Projeto 8 - Deep Learning com Rede Neural Convolucional em C++
// Construção do Modelo

// Esta é uma diretiva de pré-processador utilizada em arquivos de cabeçalho em C e C++ 
// para garantir que o conteúdo daquele arquivo seja incluído apenas uma vez durante a compilação, 
// mesmo que o arquivo seja incluído múltiplas vezes em um projeto.
#pragma once 

#include <iostream>   // Biblioteca padrão para saída
#include <iomanip>    // Biblioteca para manipulação de formatação de saída
#include <fstream>    // Biblioteca para manipulação de arquivos
#include <vector>     // Biblioteca de vetores
#include <random>     // Biblioteca para geração de números aleatórios
#include <cassert>    // Biblioteca para assertivas (verificações)
#include <cmath>      // Biblioteca para operações matemáticas, como std::ceil

// Definição da classe Tensor que representa um tensor multidimensional
class Tensor {

// Especificação pública da classe    
public:

    // Construtor padrão
    Tensor() = default; 

    // Construtor para tensores 1D
    Tensor(int size0) {
        shape = {size0};    // Define a forma como um vetor de tamanho 1
        data.resize(size0); // Redimensiona o vetor de dados para o tamanho fornecido
    }

    // Construtor para tensores 2D
    Tensor(int size0, int size1) {
        shape = {size0, size1};   // Define a forma como um vetor de tamanho 2
        data.resize(size0*size1); // Redimensiona o vetor de dados
    }

    // Construtor para tensores 3D
    Tensor(int size0, int size1, int size2) {
        shape = {size0, size1, size2};  // Define a forma como um vetor de tamanho 3
        data.resize(size0*size1*size2); // Redimensiona o vetor de dados
    }

    // Construtor para tensores 4D
    Tensor(int size0, int size1, int size2, int size3) {
        shape = {size0, size1, size2, size3}; // Define a forma como um vetor de tamanho 4
        data.resize(size0*size1*size2*size3); // Redimensiona o vetor de dados
    }

    // Sobrecarga do operador () para tensores 1D
    float& operator()(int i) {
        assert(shape.size() == 1); // Verifica se o tensor é 1D
        assert(i < shape[0]);      // Verifica se o índice está dentro do intervalo
        return data[i];            // Retorna a referência para o dado no índice fornecido
    }

    float operator()(int i) const {
        assert(shape.size() == 1);  // Verifica se o tensor é 1D
        assert(i < shape[0]);       // Verifica se o índice está dentro do intervalo
        return data[i];             // Retorna o dado no índice fornecido
    }

    // Sobrecarga do operador () para tensores 2D
    float& operator()(int i, int j) {
        assert(shape.size() == 2);   // Verifica se o tensor é 2D
        assert(i < shape[0]);        // Verifica se o primeiro índice está dentro do intervalo
        assert(j < shape[1]);        // Verifica se o segundo índice está dentro do intervalo
        return data[i*shape[1] + j]; // Calcula o índice no vetor de dados e retorna a referência
    }

    float operator()(int i, int j) const {
        assert(shape.size() == 2);   // Verifica se o tensor é 2D
        assert(i < shape[0]);        // Verifica se o primeiro índice está dentro do intervalo
        assert(j < shape[1]);        // Verifica se o segundo índice está dentro do intervalo
        return data[i*shape[1] + j]; // Calcula o índice no vetor de dados e retorna o valor
    }

    // Sobrecarga do operador () para tensores 3D
    float& operator()(int i, int j, int k) {
        assert(shape.size() == 3);                         // Verifica se o tensor é 3D
        assert(i < shape[0]);                              // Verifica se o primeiro índice está dentro do intervalo
        assert(j < shape[1]);                              // Verifica se o segundo índice está dentro do intervalo
        assert(k < shape[2]);                              // Verifica se o terceiro índice está dentro do intervalo
        return data[i*shape[1]*shape[2] + j*shape[2] + k]; // Calcula o índice no vetor de dados e retorna a referência
    }

    float operator()(int i, int j, int k) const {
        assert(shape.size() == 3);                           // Verifica se o tensor é 3D
        assert(i < shape[0]);                                // Verifica se o primeiro índice está dentro do intervalo
        assert(j < shape[1]);                                // Verifica se o segundo índice está dentro do intervalo
        assert(k < shape[2]);                                // Verifica se o terceiro índice está dentro do intervalo
        return data[i*shape[1]*shape[2] + j*shape[2] + k];   // Calcula o índice no vetor de dados e retorna o valor
    }

    // Sobrecarga do operador () para tensores 4D
    float& operator()(int i, int j, int k, int l) {
        assert(shape.size() == 4); // Verifica se o tensor é 4D
        assert(i < shape[0]);                                                             // Verifica se o primeiro índice está dentro do intervalo
        assert(j < shape[1]);                                                             // Verifica se o segundo índice está dentro do intervalo
        assert(k < shape[2]);                                                             // Verifica se o terceiro índice está dentro do intervalo
        assert(l < shape[3]);                                                             // Verifica se o quarto índice está dentro do intervalo
        return data[i*shape[1]*shape[2]*shape[3] + j*shape[2]*shape[3] + k*shape[3] + l]; // Calcula o índice no vetor de dados e retorna a referência
    }

    float operator()(int i, int j, int k, int l) const {
        assert(shape.size() == 4); // Verifica se o tensor é 4D
        assert(i < shape[0]);                                                             // Verifica se o primeiro índice está dentro do intervalo
        assert(j < shape[1]);                                                             // Verifica se o segundo índice está dentro do intervalo
        assert(k < shape[2]);                                                             // Verifica se o terceiro índice está dentro do intervalo
        assert(l < shape[3]);                                                             // Verifica se o quarto índice está dentro do intervalo
        return data[i*shape[1]*shape[2]*shape[3] + j*shape[2]*shape[3] + k*shape[3] + l]; // Calcula o índice no vetor de dados e retorna o valor
    }

    // Função para inicializar o tensor com valores aleatórios usando uma distribuição normal
    template <typename RandGenerator>
    void set_random(double stdev, RandGenerator& gen) {
        std::normal_distribution dice(0.0, stdev); // Define uma distribuição normal com média 0 e desvio padrão stdev
        for (float &d: data) {                     // Itera sobre todos os elementos do tensor
            d = dice(gen);                         // Atribui um valor aleatório a cada elemento
        }
    }

    // Função para inicializar todos os elementos com zero
    void set_zero() {
        for (float &d: data) {
            d = 0.0;
        }
    }

    // Função para inicializar todos os elementos com um
    void set_one() {
        for (float &d: data) {
            d = 1.0;
        }
    }

    // Função que verifica se dois tensores têm a mesma forma
    bool same_shape(const Tensor &rhs) const {
        if (shape.size() != rhs.shape.size()) { // Verifica se o número de dimensões é o mesmo
            return false;
        }

        for (size_t i = 0; i < shape.size(); i++) { // Verifica se todas as dimensões correspondem
            if (shape[i] != rhs.shape[i]) {
                return false;
            }
        }

        return true; // Retorna true se as formas forem iguais
    }

    // Operador de multiplicação escalar
    Tensor operator* (float v) const {
        Tensor ret = *this;             // Cria uma cópia do tensor atual
        for (auto &x: ret.data) {       // Itera sobre todos os elementos
            x *= v;                     // Multiplica cada elemento pelo valor fornecido
        }
        return ret; // Retorna o tensor resultante
    }

    // Operador de multiplicação escalar in-place
    Tensor operator*= (float v) {
        for (auto &x: data) {   // Itera sobre todos os elementos
            x *= v;             // Multiplica cada elemento pelo valor fornecido
        }
        return *this; // Retorna o tensor modificado
    }

    // Operador de soma de dois tensores
    Tensor operator+ (const Tensor& rhs) const {
        Tensor ret = *this; // Cria uma cópia do tensor atual
        for (size_t i = 0; i < rhs.data.size(); i++) { // Itera sobre os elementos do tensor rhs
            ret.data[i] += rhs.data[i]; // Soma os elementos correspondentes
        }
        return ret; // Retorna o tensor resultante
    }

    // Operador de soma in-place
    Tensor& operator+= (const Tensor& rhs) {
        for (size_t i = 0; i < rhs.data.size(); i++) { // Itera sobre os elementos do tensor rhs
            data[i] += rhs.data[i]; // Soma os elementos correspondentes in-place
        }
        return *this; // Retorna o tensor modificado
    }

    // Operador de subtração de dois tensores
    Tensor operator- (const Tensor& rhs) {
        Tensor ret = *this; // Cria uma cópia do tensor atual
        for (size_t i = 0; i < rhs.data.size(); i++) { // Itera sobre os elementos do tensor rhs
            ret.data[i] -= rhs.data[i]; // Subtrai os elementos correspondentes
        }
        return ret; // Retorna o tensor resultante
    }

    // Operador de subtração in-place
    Tensor& operator-= (const Tensor& rhs) {
        for (size_t i = 0; i < rhs.data.size(); i++) { // Itera sobre os elementos do tensor rhs
            data[i] -= rhs.data[i]; // Subtrai os elementos correspondentes in-place
        }
        return *this; // Retorna o tensor modificado
    }

    // Função para somar todos os elementos do tensor
    float sum() const {
        return std::accumulate(data.begin(), data.end(), 0.f); // Soma todos os elementos e retorna
    }

    // Operador de inserção para imprimir o tensor
    // Em C++, a palavra-chave friend indica que uma função ou classe tem permissão especial para acessar membros privados e protegidos de outra classe
    friend std::ostream& operator<<(std::ostream& os, Tensor t) {
        int count = 0; // Variável para acompanhar a posição atual nos dados

        os << "shape ("; // Imprime a forma do tensor
        for (size_t i = 0; i < t.shape.size(); i++) { // Itera sobre o vetor de forma
            os << t.shape[i]; // Imprime o tamanho de cada dimensão

            if (i != t.shape.size() - 1) { // Se não for a última dimensão
                os << ", "; // Adiciona uma vírgula
            }
        }
        os << ")\n"; // Fecha a linha da forma

        // Imprime os dados dependendo da quantidade de dimensões
        switch (t.shape.size()) {
            case 0: os << "shape (empty)"; break; // Caso tensor vazio
            case 1: // Tensor 1D
                for (auto d: t.data) { // Itera sobre os dados
                    os << d << " "; // Imprime cada dado
                }
                os << "\n";
                break;
            case 2: // Tensor 2D
                for (int i = 0; i < t.shape[0]; i++) { // Itera sobre as linhas
                    for (int j = 0; j < t.shape[1]; j++) { // Itera sobre as colunas
                        os << t.data[count] << " "; // Imprime o dado atual
                        count++;
                    }
                    os << "\n"; // Nova linha após cada linha do tensor
                }
                break;
            case 3: // Tensor 3D
                for (int i = 0; i < t.shape[0]; i++) {
                    for (int j = 0; j < t.shape[1]; j++) {
                        for (int k = 0; k < t.shape[2]; k++) {
                            os << t.data[count] << " "; // Imprime o dado atual
                            count++;
                        }
                        os << "\n"; // Nova linha após cada camada
                    }
                    os << "\n"; // Nova linha após cada grupo de camadas
                }

                break;
            case 4: // Tensor 4D
                for (int i = 0; i < t.shape[0]; i++) {
                    for (int j = 0; j < t.shape[1]; j++) {
                        for (int k = 0; k < t.shape[2]; k++) {
                            for (int l = 0; l < t.shape[3]; l++) {
                                os << t.data[count] << " "; // Imprime o dado atual
                                count++;
                            }
                            os << "\n"; // Nova linha após cada coluna
                        }
                        os << "\n"; // Nova linha após cada camada
                    }
                }
                break;

            default: return os; break; // Caso tensor com mais dimensões (não esperado)
        }

        return os; // Retorna o stream de saída
    }

    // Define as estruturas
    std::vector<float> data; // Dados armazenados no tensor
    std::vector<int> shape;  // Forma do tensor
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Classe base abstrata para camadas de uma rede neural
class Layer {

// Especificação pública da classe    
public:

    virtual ~Layer() = default; // Destrutor virtual
    virtual Tensor operator()(const Tensor& in) = 0;  // Função virtual pura para forward pass
    virtual Tensor backward(const Tensor& delta) = 0; // Função virtual pura para backward pass
    virtual void print(std::ostream& os) const = 0;   // Função virtual pura para impressão

    // Operador de inserção para imprimir a camada
    friend std::ostream& operator<<(std::ostream& os, const Layer& rhs) {
        rhs.print(os); // Chama a função print da camada
        return os;
    }

    Tensor weight; // Pesos da camada (opcional)
    Tensor bias;   // Bias da camada (opcional)

    int sum_count = 0;       // Contador de iterações de soma
    Tensor sum_weight_grad;  // Gradiente acumulado dos pesos
    Tensor sum_bias_grad;    // Gradiente acumulado dos bias
    Tensor prev_weight_grad; // Gradiente anterior dos pesos
    Tensor prev_bias_grad;   // Gradiente anterior dos bias
};

// O destrutor é uma função especial que é chamada quando um objeto é destruído (por exemplo, quando ele sai do escopo ou é deletado). 

// As funções virtuais puras, como as listadas acima, são funções que não têm uma implementação na classe base e devem ser implementadas 
// pelas classes derivadas. A sintaxe para definir uma função virtual pura em C++ é usar = 0 no final da declaração da função. Isso faz com que 
// a classe se torne uma classe abstrata, ou seja, você não pode instanciá-la diretamente.

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Conv2D : public Layer {  // Classe Conv2D que herda de Layer, representando uma camada de convolução 2D

// Especificação pública da classe
public:

    // Construtor que inicializa os pesos e biases da camada Conv2D
    Conv2D(int in_channels, int out_channels, int ksize, int stride=1, int padding=0) {
        stride_ = stride;    // Inicializa o valor do stride
        padding_ = padding;  // Inicializa o valor do padding

        // Inicializa os pesos como um tensor de 4 dimensões: [out_channels, in_channels, ksize, ksize]
        weight = Tensor(out_channels, in_channels, ksize, ksize);
        
        // Inicializa o bias como um tensor 1D de tamanho out_channels
        bias = Tensor(out_channels);

        // Gradientes dos pesos e biases também são inicializados para acumular gradientes durante o backpropagation
        sum_weight_grad = Tensor(out_channels, in_channels, ksize, ksize);
        sum_bias_grad = Tensor(out_channels);

        // Gradientes anteriores para uso em otimização com momento
        prev_weight_grad = Tensor(out_channels, in_channels, ksize, ksize);
        prev_bias_grad = Tensor(out_channels);
    }

    // Sobrecarga do operador () para a operação de convolução (forward pass)
    Tensor operator()(const Tensor& in) override {

        // Verifica se o número de canais de entrada do tensor de entrada corresponde aos pesos da camada
        assert(in.shape[0] == weight.shape[1]);

        // Se os gradientes de entrada ainda não foram inicializados, calcula as dimensões de saída
        if (input_grad_.shape.empty()) {
            int out_h = new_out_dim(in.shape[1]);  // Calcula a altura da saída
            int out_w = new_out_dim(in.shape[2]);  // Calcula a largura da saída

            // Inicializa o gradiente de entrada e a saída da camada
            input_grad_ = Tensor(in.shape[0], in.shape[1], in.shape[2]);
            output_ = Tensor(weight.shape[0], out_w, out_h);  // [out_channels, out_w, out_h]
        }

        input_ = in;  // Armazena a entrada para uso posterior no backpropagation

        // Loop para calcular a operação de convolução
        for (int oc = 0; oc < output_.shape[0]; oc++) {  // Para cada canal de saída
            for (int oy = 0; oy < output_.shape[1]; oy++) {  // Para cada posição na altura da saída
                for (int ox = 0; ox < output_.shape[2]; ox++) {  // Para cada posição na largura da saída
                    float sum = 0;  // Acumulador para a soma da convolução

                    // Loop sobre os pesos (filtros)
                    for (int wc = 0; wc < weight.shape[1]; wc++) {  // Para cada canal de entrada
                        for (int wy = 0; wy < weight.shape[2]; wy++) {  // Para cada linha do filtro
                            for (int wx = 0; wx < weight.shape[3]; wx++) {  // Para cada coluna do filtro

                                // Calcula as coordenadas na entrada levando em conta o stride e o padding
                                int in_y = oy * stride_ - padding_ + wy;
                                int in_x = ox * stride_ - padding_ + wx;

                                // Verifica se as coordenadas estão dentro dos limites da entrada
                                if (in_y < 0 || in_y >= in.shape[1]) {
                                    continue;
                                }
                                if (in_x < 0 || in_x >= in.shape[2]) {
                                    continue;
                                }

                                // Realiza a multiplicação entre o valor da entrada e o peso correspondente
                                float x = in(wc, in_y, in_x);
                                float w = weight(oc, wc, wy, wx);

                                sum += w * x;  // Acumula o resultado
                            }
                        }
                    }

                    // Adiciona o bias ao resultado da convolução
                    float b = bias(oc);
                    output_(oc, oy, ox) = sum + b;  // Armazena o resultado na posição correspondente da saída
                }
            }
        }

        return output_;  // Retorna o tensor de saída
    }

    // Função para realizar o backward pass (retropropagação)
    Tensor backward(const Tensor& delta) override {

        // Verifica se as dimensões do delta correspondem às dimensões da saída da camada
        for (size_t i = 0; i < delta.shape.size(); i++) {
            assert(delta.shape[i] == output_.shape[i]);
        }

        input_grad_.set_zero();  // Inicializa o gradiente de entrada como zero

        // Calcula o gradiente em relação à entrada e acumula os gradientes dos pesos e bias
        for (int oc = 0; oc < output_.shape[0]; oc++) {  // Para cada canal de saída
            for (int oy = 0; oy < output_.shape[1]; oy++) {  // Para cada posição na altura da saída
                for (int ox = 0; ox < output_.shape[2]; ox++) {  // Para cada posição na largura da saída
                    float d = delta(oc, oy, ox);  // Gradiente da saída

                    // Convolução inversa para calcular o gradiente de entrada e os gradientes dos pesos
                    for (int wc = 0; wc < weight.shape[1]; wc++) {  // Para cada canal de entrada
                        for (int wy = 0; wy < weight.shape[2]; wy++) {  // Para cada linha do filtro
                            for (int wx = 0; wx < weight.shape[3]; wx++) {  // Para cada coluna do filtro
                                int in_y = oy * stride_ - padding_ + wy;
                                int in_x = ox * stride_ - padding_ + wx;

                                // Verifica se as coordenadas estão dentro dos limites da entrada
                                if (in_y < 0 || in_y >= input_.shape[1]) {
                                   continue;
                                }
                                if (in_x < 0 || in_x >= input_.shape[2]) {
                                   continue;
                                }

                                // Obtém o valor da entrada e do peso
                                float x = input_(wc, in_y, in_x);
                                float w = weight(oc, wc, wy, wx);

                                // Calcula o gradiente de entrada e acumula o gradiente dos pesos
                                input_grad_(wc, in_y, in_x) += w * d;
                                sum_weight_grad(oc, wc, wy, wx) += x * d;
                            }
                        }
                    }

                    // Acumula o gradiente do bias
                    sum_bias_grad(oc) += d;
                }
            }
        }

        sum_count++;  // Incrementa o contador de somas para os gradientes

        return input_grad_;  // Retorna o gradiente da entrada
    }

    // Função para imprimir informações sobre a camada
    void print(std::ostream& os) const override { 
        os << "Conv2D (in=" << weight.shape[1] << " out=" << weight.shape[0]
           << " ksize=" << weight.shape[2] << " stride=" << stride_
           << " padding=" << padding_ << ")";
    }

// Especificação privada da classe
private:

    // Função para calcular a dimensão de saída com base na entrada, stride e padding
    int new_out_dim(int x) {
        int ksize = weight.shape[2];  // Tamanho do kernel (filtro)

        // Calcula a nova dimensão após a operação de convolução
        float a = std::ceil(1.0 * (x + 2 * padding_ - ksize + 1) / stride_);
        return static_cast<int>(a);  // Retorna a nova dimensão como inteiro
    }

    int padding_;  // Valor do padding usado na convolução
    int stride_;   // Valor do stride usado na convolução

    Tensor input_;       // Tensor de entrada armazenado para o backpropagation
    Tensor input_grad_;  // Gradiente da entrada
    Tensor output_;      // Tensor de saída (resultado da convolução)
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Dense : public Layer {  // Classe Dense que herda da classe Layer, representando uma camada densa (fully connected)

// Especificação pública da classe
public:

    // Construtor que inicializa a camada densa com os tamanhos de entrada e saída
    Dense(int in_size, int out_size) {
        weight = Tensor(out_size, in_size);  // Inicializa os pesos como um tensor de [out_size, in_size]
        bias = Tensor(out_size);  // Inicializa o bias como um tensor de tamanho out_size

        // Inicializa os gradientes acumulados dos pesos e bias para backpropagation
        sum_weight_grad = Tensor(out_size, in_size);
        sum_bias_grad = Tensor(out_size);

        // Inicializa os gradientes anteriores para cálculo com momento (momentum)
        prev_weight_grad = Tensor(out_size, in_size);
        prev_bias_grad = Tensor(out_size);

        // Inicializa os tensores de saída e gradiente da entrada
        output_ = Tensor(out_size);
        input_grad_ = Tensor(out_size, in_size);
    }

    // Sobrecarga do operador () para realizar o forward pass da camada
    Tensor operator()(const Tensor& in) override {

        // Verifica se a entrada é 1D e se o tamanho da entrada corresponde ao tamanho dos pesos
        assert(in.shape.size() == 1);
        assert(in.shape[0] == weight.shape[1]);

        // Armazena a entrada para uso posterior no backpropagation
        input_ = in;  

        // Calcula a saída da camada densa (pesos * entrada + bias)
        for (int i = 0; i < weight.shape[0]; i++) {  // Para cada neurônio de saída
            float sum = 0;
            for (int j = 0; j < weight.shape[1]; j++) {  // Para cada neurônio de entrada
                sum += weight(i, j) * in(j);  // Soma o produto dos pesos e da entrada
            }
            sum += bias(i);    // Adiciona o bias
            output_(i) = sum;  // Armazena o resultado na saída
        }

        return output_;  // Retorna o tensor de saída
    }

    // Função para realizar o backward pass (retropropagação)
    Tensor backward(const Tensor& delta) override {
        
        // Calcula o gradiente da entrada e acumula os gradientes dos pesos e bias
        for (int i = 0; i < weight.shape[0]; i++) {  // Para cada neurônio de saída
            float d = delta(i);  // Gradiente da saída
            for (int j = 0; j < weight.shape[1]; j++) {  // Para cada neurônio de entrada
                input_grad_(i, j) = weight(i, j) * d;  // Gradiente da entrada
                sum_weight_grad(i, j) += input_(j) * d;  // Acumula o gradiente dos pesos
            }
            sum_bias_grad(i) += d;  // Acumula o gradiente do bias
        }

        sum_count++;  // Incrementa o contador de iterações para os gradientes

        return input_grad_;  // Retorna o gradiente da entrada
    }

    // Função para imprimir informações sobre a camada
    void print(std::ostream& os) const override { 
        os << "Dense (in=" << weight.shape[1] << " out=" << weight.shape[0] << ")";  // Exibe as dimensões da camada
    }

// Especificação privada da classe
private:

    Tensor output_;      // Tensor de saída da camada
    Tensor input_;       // Armazena o tensor de entrada
    Tensor input_grad_;  // Tensor de gradiente da entrada (usado no backward pass)
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ReLU : public Layer {  // Classe ReLU que herda de Layer, representando uma camada de ativação ReLU (Rectified Linear Unit)

// Especificação pública da classe
public:

    // Sobrecarga do operador () para realizar o forward pass da função de ativação ReLU
    Tensor operator()(const Tensor& in) override {
        
        // Se a saída ainda não foi inicializada, copia a entrada para output_ e input_grad_
        if (output_.data.empty()) {
            output_ = in;      // Inicializa o tensor de saída com a mesma estrutura da entrada
            input_grad_ = in;  // Inicializa o gradiente de entrada
        }

        // Aplica a função de ativação ReLU (máximo entre 0 e o valor da entrada)
        int i = 0;
        for (float x : in.data) {  // Itera sobre cada elemento da entrada
            output_.data[i] = std::max(0.f, x);  // Substitui valores negativos por 0, mantendo os positivos
            i++;
        }

        return output_;  // Retorna o tensor de saída após a ativação
    }

    // Função para realizar o backward pass (retropropagação) da função de ativação ReLU
    Tensor backward(const Tensor& delta) override {

        int i = 0;

        // Para cada elemento da saída, verifica se é positivo para calcular o gradiente
        for (float x : output_.data) {
            if (x > 0) {  // Se o valor da saída for positivo, o gradiente da entrada é o mesmo que o gradiente da saída
                input_grad_.data[i] = delta.data[i]; 
            } else {  // Se o valor da saída for zero ou negativo, o gradiente é zero
                input_grad_.data[i] = 0;
            }
            i++;
        }

        return input_grad_;  // Retorna o gradiente da entrada
    }

    // Função para imprimir informações sobre a camada
    void print(std::ostream& os) const override { 
        os << "ReLU";  // Imprime o nome da camada
    }

// Especificação privada da classe
private:

    Tensor output_;      // Tensor de saída após a ativação
    Tensor input_grad_;  // Gradiente da entrada para a retropropagação
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Flatten : public Layer {  // Classe Flatten que herda de Layer, representando uma camada que "achata" um tensor multidimensional em um vetor 1D

// Especificação pública da classe
public:

    // Sobrecarga do operador () para realizar o forward pass (achatar o tensor de entrada)
    Tensor operator()(const Tensor& in) override {
        // Verifica se o tensor de saída (achatado) ainda não foi inicializado
        if (output_.shape.empty()) {
            output_ = Tensor(in.data.size());  // Inicializa o tensor de saída com o tamanho equivalente ao número total de elementos da entrada
        }

        input_ = in;  // Armazena a entrada original para uso no backpropagation
        output_.data = in.data;  // Copia os dados da entrada para o tensor achatado (mantendo a mesma ordem dos dados)

        return output_;  // Retorna o tensor achatado
    }

    // Função para realizar o backward pass (retropropagação) 
    Tensor backward(const Tensor& delta) override {
        // Verifica se o tamanho do gradiente (delta) corresponde ao tamanho da entrada original
        assert(input_.data.size() == delta.data.size());

        // Copia os gradientes do delta de volta para a entrada original
        input_.data = delta.data;

        return input_;  // Retorna o tensor de entrada com os gradientes aplicados
    }

    // Função para imprimir informações sobre a camada
    void print(std::ostream& os) const override { 
        os << "Flatten";  // Imprime o nome da camada
    }

// Especificação privada da classe
private:

    Tensor input_;  // Armazena o tensor de entrada original (antes do achatamento)
    Tensor output_;  // Armazena o tensor de saída (achado)
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Softmax : public Layer {  // Classe Softmax que herda de Layer, representando a função de ativação Softmax

// Especificação pública da classe
public:

    // Sobrecarga do operador () para realizar o forward pass da função Softmax
    Tensor operator()(const Tensor& in) override {

        // Verifica se a entrada é um tensor 1D
        assert(in.shape.size() == 1);

        output_ = in;  // Armazena a entrada para cálculo posterior

        // "Sum of exp trick" para melhorar a estabilidade numérica ao calcular a exponenciação
        float max_val = *std::max_element(in.data.begin(), in.data.end());  // Encontra o maior valor da entrada

        float sum_exp = 0;
        // Calcula a soma das exponenciais de cada valor, subtraindo max_val para evitar overflow
        for (auto x : in.data) {
            sum_exp += std::exp(x - max_val);
        }

        // Aplica a função Softmax a cada valor da entrada
        int i = 0;
        for (auto x : in.data) {
            output_.data[i] = std::exp(x - max_val) / sum_exp;  // Normaliza o valor exponencial dividindo pela soma das exponenciais
            i++;
        }

        return output_;  // Retorna o tensor com os valores normalizados pela função Softmax
    }

    // Função para realizar o backward pass (retropropagação) da função Softmax
    Tensor backward(const Tensor& delta) override {

        // Inicializa o tensor de retorno com os valores da saída da Softmax
        Tensor ret = output_;  

        // Calcula o gradiente para cada posição da saída
        for (int i = 0; i < output_.shape[0]; i++) { 
            float sum = 0;
            // Loop para calcular a soma ponderada dos gradientes da função Softmax
            for (int j = 0; j < output_.shape[0]; j++) {
                if (i == j) {
                    sum += output_(i) * (1 - output_(i)) * delta(j);  // Derivada para o caso em que i == j
                } else {
                    sum += -output_(i) * output_(j) * delta(j);  // Derivada para o caso em que i != j
                }
            }
            ret(i) = sum;  // Armazena o gradiente calculado
        }

        return ret;  // Retorna o tensor com os gradientes
    }

    // Função para imprimir informações sobre a camada
    void print(std::ostream& os) const override { 
        os << "Softmax";  // Imprime o nome da camada
    }

// Especificação privada da classe
private:

    Tensor output_;  // Armazena o tensor de saída da função Softmax
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CrossEntropyLoss {  // Classe para calcular a função de perda Cross-Entropy (Entropia Cruzada)

// Especificação pública da classe
public:

    // Sobrecarga do operador () para calcular a perda com base nas previsões e no rótulo alvo
    float operator()(const Tensor& y, int target) {

        // Verifica se a entrada (previsão) é um tensor 1D
        assert(y.shape.size() == 1);  

        y_ = y;            // Armazena o tensor de previsões para uso no backward pass
        target_ = target;  // Armazena o rótulo correto (índice do alvo)

        float sum = 0;  // Variável para acumular a perda

        // Calcula a perda de entropia cruzada para cada classe
        // Veja a explicação de cada parâmetro no videobook do Capítulo 21 do curso
        for (size_t i = 0; i < y_.data.size(); i++) {

            // Para a classe correta
            if (static_cast<int>(i) == target_) {  

                // Calcula a perda para a classe alvo (log da probabilidade)
                sum += -std::log(std::max(y.data[i], EPS));  

            // Para as outras classes
            } else {  

                // Calcula a perda para as classes não-alvo
                sum += -std::log(std::max(1 - y.data[i], EPS));  
            }
        }

        return sum;  // Retorna a perda total
    }

    // Função para calcular o gradiente da perda em relação às previsões (backward pass)
    Tensor backward() {

        Tensor ret = y_;  // Inicializa o tensor de gradientes com os valores das previsões

        // Calcula o gradiente para cada valor da previsão
        for (size_t i = 0; i < y_.data.size(); i++) {
            if (static_cast<int>(i) == target_) {  // Para a classe alvo
                ret.data[i] = -1.0 / std::max(y_.data[i], EPS);  // Gradiente da classe correta
            } else {  // Para as outras classes
                ret.data[i] = 1.0 / std::max(1 - y_.data[i], EPS);  // Gradiente das classes incorretas
            }
        }

        return ret;  // Retorna o tensor de gradientes
    }

// Especificação privada da classe
private:

    Tensor y_;    // Armazena as previsões (saída da Softmax)
    int target_;  // Armazena o índice da classe correta (rótulo)
    const float EPS = std::numeric_limits<float>::epsilon();  // Valor pequeno para evitar divisão por zero (estabilidade numérica)
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AccuracyMetric {  // Classe para calcular a métrica de acurácia e gerar a matriz de confusão

// Especificação pública da classe
public:

    // Construtor que inicializa a matriz de confusão com base no número de classes
    AccuracyMetric(int num_classes) {
        confusion_ = Tensor(num_classes, num_classes);  // Cria uma matriz de confusão num_classes x num_classes
    }

    // Atualiza a matriz de confusão com base nas previsões e no rótulo alvo
    void update(Tensor y, int target) {
        assert(y.shape[0] == confusion_.shape[0]);  // Verifica se o tamanho da previsão corresponde ao número de classes

        // Encontra a classe com a maior probabilidade (previsão)
        float m = y(0);  // Inicializa a variável m com o valor da primeira classe
        int pred = 0;    // Variável para armazenar a classe prevista

        // Itera sobre as classes para encontrar a classe com maior valor (probabilidade)
        for (int i = 1; i < y.shape[0]; i++) {
            if (y(i) > m) {  // Se a probabilidade da classe i for maior, atualiza a previsão
                m = y(i);
                pred = i;
            }
        }

        assert(pred >= 0);  // Verifica se a previsão é válida

        // Atualiza a matriz de confusão: incrementa a célula correspondente ao rótulo real e à previsão
        confusion_(target, pred)++;

        // Incrementa o contador total de amostras
        total_++;  
    }

    // Calcula a acurácia com base na matriz de confusão
    float accuracy() {

        int correct = 0;

        // Soma os valores da diagonal principal da matriz de confusão (previsões corretas)
        for (int i = 0; i < confusion_.shape[0]; i++) {
            correct += confusion_(i, i);
        }

        // Retorna a acurácia como a proporção de previsões corretas sobre o total
        return 1.0f * correct / total_;
    }

    // Função para imprimir a matriz de confusão
    void print_confusion_matrix() { 

        // Itera sobre as linhas e colunas da matriz de confusão para exibi-la
        for (int i = 0; i < confusion_.shape[0]; i++) {
            for (int j = 0; j < confusion_.shape[0]; j++) {
                std::cout << std::setw(5) << confusion_(i, j);  // Exibe cada célula da matriz com um espaçamento fixo
            }
            std::cout << "\n";  // Nova linha após cada linha da matriz
        }
        std::cout << "\n";
        std::cout << "Linhas = Valor Real\n";  // Explicação: as linhas correspondem ao rótulo real
        std::cout << "Colunas = Previsão\n";   // Explicação: as colunas correspondem à previsão do modelo
    }

    // Função para limpar (resetar) a matriz de confusão e o contador total
    void clear() {
        confusion_.set_zero();  // Zera todos os valores da matriz de confusão
        total_ = 0;  // Reseta o contador total de amostras
    }

// Especificação privada da classe
private:

    Tensor confusion_;  // Matriz de confusão para armazenar as previsões corretas e incorretas
    int total_ = 0;     // Contador total de amostras processadas
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função template para inicializar os pesos da rede neural usando um gerador aleatório (RandGenerator)
template <typename RandGenerator>
void init_network_weight(std::vector<Layer*> &net, RandGenerator& gen) {

    // Itera sobre todas as camadas da rede (net)
    for (auto layer : net) {

        // Zera os valores do bias da camada
        layer->bias.set_zero();

        // Obtém o shape (dimensões) dos pesos da camada
        auto s = layer->weight.shape;
        int fan_in = 0;  // Variável para armazenar o número de unidades de entrada (fan-in)

        // Se a camada for Conv2D, calcula o fan-in como o produto dos canais de entrada e o tamanho do kernel
        if (s.size() == 4) { // Camada Conv2D
            fan_in = s[1] * s[2] * s[3];  // fan-in = número de canais de entrada * altura do kernel * largura do kernel
        }
        // Se a camada for Dense (camada totalmente conectada), o fan-in é o número de unidades de entrada
        else if (s.size() == 2) { // Camada Dense
            fan_in = layer->weight.shape[1];  // fan-in = número de entradas (unidades de entrada)
        }

        // Se o fan-in for maior que 0, calcula o desvio padrão para inicializar os pesos
        if (fan_in > 0) {
            float stdev = std::sqrt(1.f / fan_in);  // Desvio padrão baseado no fan-in (inicialização de He)
            layer->weight.set_random(stdev, gen);  // Inicializa os pesos com valores aleatórios seguindo a distribuição normal
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função para atualizar os pesos da rede neural usando o algoritmo de descida de gradiente estocástico (SGD) com momento
void SGD_weight_update(std::vector<Layer*> &net, float lr, float momentum) {

    // Itera sobre cada camada da rede neural (net)
    for (auto l : net) {

        // Se a camada não tiver pesos (ex: camadas como ReLU ou Flatten), pula para a próxima
        if (l->weight.shape.empty()) {
            continue;  // Pula para a próxima camada
        }

        // Aplica o momento: combina o gradiente atual com o gradiente da iteração anterior multiplicado pelo fator de momento
        Tensor weight_grad = l->sum_weight_grad * (1.f / l->sum_count) + l->prev_weight_grad * momentum;  // Gradiente dos pesos
        Tensor bias_grad = l->sum_bias_grad * (1.f / l->sum_count) + l->prev_bias_grad * momentum;        // Gradiente do bias

        // Atualização dos pesos e bias usando descida de gradiente
        l->weight -= weight_grad * lr;  // Atualiza os pesos com base no gradiente e na taxa de aprendizado (lr)
        l->bias -= bias_grad * lr;      // Atualiza os bias com base no gradiente e na taxa de aprendizado

        // Armazena os gradientes atuais para uso na próxima iteração (para aplicar momento)
        l->prev_weight_grad = weight_grad;  // Armazena o gradiente dos pesos
        l->prev_bias_grad = bias_grad;      // Armazena o gradiente dos bias

        // Reseta os gradientes acumulados e o contador de somas para a próxima iteração de treinamento
        l->sum_weight_grad.set_zero();  // Zera o gradiente acumulado dos pesos
        l->sum_bias_grad.set_zero();    // Zera o gradiente acumulado dos bias
        l->sum_count = 0;               // Reseta o contador de gradientes acumulados
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Função para imprimir informações sobre a rede neural, incluindo a estrutura e o número de parâmetros treináveis
void print_network_info(const std::vector<Layer*> &net) {
    
    // Cabeçalho informando que a lista de camadas será exibida
    std::cout << "Camadas da Rede:\n";  

    // Variável para contar o número total de parâmetros treináveis
    int total_params = 0;  

    // Índice para numerar as camadas
    int i = 0;  

    // Itera sobre cada camada da rede neural
    for (auto layer : net) {
        
        // Imprime o índice da camada e o conteúdo da camada (utilizando o operador << sobrecarregado para as camadas)
        std::cout << "  " << i << ": " << *layer << "\n";

        // Conta o número de parâmetros treináveis (tamanho dos dados dos pesos e bias)
        total_params += layer->weight.data.size() + layer->bias.data.size();

        i++;  // Incrementa o índice da camada
    }

    // Exibe o número total de parâmetros treináveis
    std::cout << "\nTotal de Parâmetros Treináveis: " << total_params << "\n";
}
