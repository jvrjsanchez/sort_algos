/*

Solução do Exercício 5: Crie um loop para percorrer o array e imprimir o índice e o valor de cada elemento do array.

*/

 
#include <iostream>
using namespace std;

// Imprimir os números de um array
int main()
{
    // Cria um array de números inteiros
    int lista[5]; 

    // Atribui valores a cada elemento do array
    lista[0] = 1; 
    lista[1] = 2;
    lista[2] = 3;
    lista[3] = 4;
    lista[4] = 5; 

    for (int count = 0; count <= 4; ++count)
        cout << "Elemento do array no índice " << count << " é igual a " << lista[count] << "\n";
 
}
