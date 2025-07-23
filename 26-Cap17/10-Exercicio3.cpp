/* 

Solução do Exercício 3: Imprima os números ímpares entre 1 e 10 em ordem decrescente usando loop for.

*/

#include <iostream>
using namespace std;

int main()
{
    for (int contador = 9; contador >= 0; contador -= 2)
        cout << contador << ' ';
    
    cout << '\n';

}
