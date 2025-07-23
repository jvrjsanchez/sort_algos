/*

Use o comando abaixo para compilar o programa definindo o padrão desejado da Linguagem C++.

g++ 20-ArrayString.cpp -o array3 -std=c++20

Este programa em C++ tem como objetivo buscar e exibir frases que contêm uma palavra específica ("especial") dentro de um vetor de strings.

*/

#include <iostream>
#include <string>
#include <vector>

int main() {

    // Definindo o vetor com algumas frases de exemplo
    // Um std::vector é usado para armazenar várias frases. Cada elemento do vetor é uma string.
    std::vector<std::string> frases = {
        "Esta é uma frase especial para testes.",
        "Aqui não tem a palavra-chave.",
        "C++ é uma linguagem muito poderosa e especial.",
        "Outra frase sem a palavra desejada.",
        "Programação em C++ pode ser muito especial."
    };

    // Palavra que estamos buscando
    std::string palavraBuscada = "especial";

    // Loop para verificar cada frase no vetor
    for (const std::string& frase : frases) {

        // Verificando se a palavraBuscada está na frase
        // std::string::npos indica que a substring não foi encontrada.
        if (frase.find(palavraBuscada) != std::string::npos) {

            // Imprime a frase se contém a palavra
            std::cout << frase << std::endl; 
        }
    }

    return 0;
}



