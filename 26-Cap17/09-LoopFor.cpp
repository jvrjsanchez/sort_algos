/* 

Loop For

A instrução de loop mais utilizada em C++ é a instrução for. A instrução for (também chamada de loop for) é preferida quando 
temos uma variável de loop óbvia porque nos permite definir, inicializar, testar e alterar o valor das variáveis de loop de 
maneira fácil e concisa.

Sintaxe:

for (init-statement; condition; end-expression)
   statement

*/

#include <iostream>
using namespace std;

// Imprimir os números de 1 a 10
int main()
{
    for (int count = 1; count <= 10; ++count)
        cout << count << ' ';
 
}


/*

Solução do Exercício 3: Imprima os números ímpares entre 1 e 10 em ordem decrescente usando loop for.

A solução será apresentada no próximo vídeo.

*/