/*
 
Solução do Exercício 2: Imprima os números de 1 a 5 usando do-while

*/

#include <iostream>
using namespace std;

int main()
{
    int contador = 1;

    // Usando do-while
    cout << "Usando do-while:" << endl;
    do {
        cout << contador << "\n";
        ++contador;
    } while (contador <= 5);

    // Reinicializa a variável contador
    contador = 1;

    // Usando while
    cout << "Usando while:" << endl;
    while (contador <= 5) {
        cout << contador << "\n";
        ++contador;
    }

    return 0;
}
