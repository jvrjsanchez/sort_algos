// Projeto 8 - Deep Learning com Rede Neural Convolucional em C++
// Preparação do Dataset 

// Esta é uma diretiva de pré-processador utilizada em arquivos de cabeçalho em C e C++ 
// para garantir que o conteúdo daquele arquivo seja incluído apenas uma vez durante a compilação, 
// mesmo que o arquivo seja incluído múltiplas vezes em um projeto.
#pragma once 

#include <fstream>  // Inclui a biblioteca para manipulação de arquivos
#include <vector>   // Inclui a biblioteca de vetores
#include <cassert>  // Inclui a biblioteca para assertivas (verificações)

#include "dsamodelo.hpp"  // Inclui o arquivo de cabeçalho "dsamodelo.hpp" que define a classe Tensor

// Classe para definição do dataset
class DSA_Dataset {

// Especificação pública da classe
public:

    // Construtor que carrega as imagens e rótulos dos arquivos fornecidos
    DSA_Dataset(const char* image_path, const char* label_path) {
        images = load_images(image_path); // Carrega as imagens do arquivo
        labels = load_labels(label_path); // Carrega os rótulos do arquivo

        // Verifica se o número de rótulos corresponde ao número de imagens
        assert(static_cast<int>(labels.size()) == images.shape[0]);
    }

    // Função que retorna uma imagem com base no índice fornecido
    Tensor get_image(int idx) const {

        // Verifica se o índice é válido
        assert(idx >= 0 && idx < static_cast<int>(labels.size()));

        // Define a altura e a largura da imagem
        int h = images.shape[2];
        int w = images.shape[3];

        // Cria um tensor para armazenar a imagem extraída
        Tensor img(1, h, w);
        
        // Copia os dados da imagem do tensor de imagens
        std::copy(&images.data[idx*h*w], &images.data[(idx+1)*h*w], img.data.begin());

        return img; // Retorna a imagem como um tensor
    }

    // Inicializa tensor e vetor
    Tensor images;
    std::vector<int> labels;

// Especificação privada da classe
private:

    // Função para carregar as imagens a partir de um arquivo binário
    Tensor load_images(const char* path) {

        // Abre o arquivo binário
        std::ifstream is(path, std::ios::binary); 

        if (!is) {
            // Lança um erro se o arquivo não puder ser aberto
            throw std::runtime_error("Não foi possível carregar o arquivo " + std::string(path));
        }

        char magic_str[4];      // Armazena a assinatura do arquivo
        char num_images_str[4]; // Armazena o número de imagens
        char num_rows_str[4];   // Armazena o número de linhas
        char num_cols_str[4];   // Armazena o número de colunas
        
        is.read(magic_str, 4);       // Lê a assinatura 
        is.read(num_images_str, 4);  // Lê o número de imagens
        is.read(num_rows_str, 4);    // Lê o número de linhas
        is.read(num_cols_str, 4);    // Lê o número de colunas

        // Converte os cabeçalhos binários para inteiros
        int num_images = char4_to_int(num_images_str);
        int num_rows = char4_to_int(num_rows_str);
        int num_cols = char4_to_int(num_cols_str);

        // Cria um buffer para armazenar os dados de imagem
        std::vector<char> buf(num_images * num_rows * num_cols);

        // Lê os dados do arquivo
        is.read(buf.data(), buf.size()); 

        // Cria um tensor para armazenar as imagens carregadas
        Tensor ret(num_images, 1, num_rows, num_cols);

        // Converte os valores dos pixels para o intervalo [0, 1]
        for (size_t i = 0; i < buf.size(); i++) {
            ret.data[i] = static_cast<uint8_t>(buf[i]) / 255.f;
        }

        return ret;  // Retorna o tensor com as imagens carregadas
    }

    // Função para carregar os rótulos a partir de um arquivo binário
    std::vector<int> load_labels(const char* path) {

        // Abre o arquivo binário
        std::ifstream is(path, std::ios::binary);  
        
        if (!is) {
            // Lança um erro se o arquivo não puder ser aberto
            throw std::runtime_error("Não foi possível carregar o arquivo " + std::string(path));
        }

        char magic_str[4];  // Armazena a assinatura do arquivo
        char num_str[4];    // Armazena o número de rótulos
        
        is.read(magic_str, 4);  // Lê a assinatura
        is.read(num_str, 4);    // Lê o número de rótulos

        // Converte o número de rótulos para inteiro
        int num = char4_to_int(num_str);  

        // Cria um buffer para armazenar os rótulos
        std::vector<char> buf(num);

        // Lê os dados dos rótulos do arquivo
        is.read(buf.data(), buf.size());  

        // Cria um vetor para armazenar os rótulos como inteiros
        std::vector<int> ret(num);

        // Converte os rótulos do formato char para int
        for (int i = 0; i < num; i++) {
            ret[i] = buf[i];
        }

        return ret;  // Retorna o vetor de rótulos
    }

    // Função que converte um array de 4 chars para um inteiro
    int char4_to_int(char str[4]) {
        std::swap(str[0], str[3]);  // Inverte a ordem dos bytes para corresponder à ordem correta de bits
        std::swap(str[1], str[2]);

        int num = *reinterpret_cast<int*>(str);  // Converte os 4 chars em um inteiro

        return num;  // Retorna o número convertido
    }
};
