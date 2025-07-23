/* 

Statements e Funções

Um programa de computador é uma sequência de instruções que dizem ao computador o que fazer. 

Um statement é um tipo de instrução que faz com que o programa execute alguma ação.

Os statements são de longe o tipo mais comum de instrução em um programa C++. Isso ocorre porque eles são a menor unidade de 
computação independente na linguagem C++. Eles agem de forma muito semelhante à das sentenças em linguagem natural. 

Quando queremos transmitir uma ideia a outra pessoa, normalmente escrevemos ou falamos em frases (não em palavras ou sílabas aleatórias). 
Em C++, quando queremos que nosso programa faça algo, normalmente escrevemos statements.

A maioria (mas não todos) os statements em C++ termina em ponto-e-vírgula. Se você vir uma linha que termina em ponto-e-vírgula, 
provavelmente é statement.

Em uma linguagem de alto nível como C++, um único statement pode ser compilado em várias instruções de linguagem de máquina.

Existem muitos tipos diferentes de statements em C++:

Statements de declaração
Statements de jump
Statements de expressão
Statements compostas
Statements condicionais
Statements de iteração (loops)
Statements de blocos try

Em C++, statements são normalmente agrupados em unidades chamadas funções. Uma função é uma coleção de instruções que são executadas 
sequencialmente. Conforme você aprende a escrever seus próprios programas, você será capaz de criar suas próprias funções e misturar 
e combinar instruções da maneira que quiser.

*/

#include <iostream>
using namespace std;

int main()
{
   cout << "Hello world!" << endl;
   return 0;
}
