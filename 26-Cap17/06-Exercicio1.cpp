/* 

Solução do Exercício 1: Crie um programa que imprima a seguinte sequência:

1
1 2
1 2 3
1 2 3 4
1 2 3 4 5

*/

#include <iostream>
using namespace std;

// Resolvemos o exercício como se estivéssemos percorrendo uma matriz, usando 2 loops, externo e interno.
int main()
{
    // Variável externa
    int externo = 1;

    // Loop externo
    while (externo <= 5)
    {
        // Variável interna
        int interno = 1;
        
        // Loop interno
        while (interno <= externo)
        {
            cout << interno << ' ';
            ++interno;
        }
 
        // Imprime nova linha
        cout << '\n';
        ++externo;
    }
 
}