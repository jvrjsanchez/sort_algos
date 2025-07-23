/*

Loop While 

A instrução while (também chamada de loop while) é o mais simples dos três tipos de loops fornecidos por C++ e tem uma definição 
muito semelhante à de uma instrução if:

while (condição)
    statement;

*/ 

#include <iostream>
using namespace std;

int main()
{
    // Contador
    int contador;
    contador = 1;

    // Loop
    while (contador <= 10)
    {
        cout << contador << " ";
        ++contador;
    }
 
    cout << "\nConcluído!\n";
 
    return 0;
}

/*

Exercício 1: Crie um programa que imprima a seguinte sequência:

1
1 2
1 2 3
1 2 3 4
1 2 3 4 5

A solução será apresentada no próximo vídeo.

*/