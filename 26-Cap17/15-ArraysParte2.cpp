/*

Arrays

Mais exemplos de manipulação de arrays.

*/ 

#include <iostream>
using namespace std;

int main()
{
    // Observe que estamos inicializando somente os 3 primeiros elementos do array
    // Isso deve ser evitado
    int lista_num1[5] = { 100, 200, 300 }; 
 
    cout << "\n\nImprime Array 1:\n";
    for (int i = 0; i <= 4; ++i)
        cout << "Elemento do array no índice " << i << " é igual a " << lista_num1[i] << "\n";


    // Não definimos o tamanho do array de forma explícita, mas sim através de atribuição dos valores dos elementos.
    // É o que chamamos de alocação dinâmica
    int lista_num2[] = { 1, 2, 3, 4, 5, 6, 7 }; 

    cout << "\n\nImprime Array 2:\n";
    for (int a = 0; a <= 6; ++a)
        cout << "Elemento do array no índice " << a << " é igual a " << lista_num2[a] << "\n";

    
    // Arrays suportam qualquer tipo básico em C++
    string lista_num3[6] = { "Azul", "Verde", "Rosa", "Branco", "Amarelo", "Marrom" }; 

    cout << "\n\nImprime Array 3:\n";
    for (int z = 0; z <= 5; ++z)
        cout << "Elemento do array no índice " << z << " é igual a " << lista_num3[z] << "\n";

}