/*

Tipos de Dados em C++

Em C++, o tipo de uma variável deve ser conhecido em tempo de compilação (quando o programa é compilado) e esse tipo não 
pode ser alterado sem recompilar o programa. Isso significa que uma variável inteira pode conter apenas valores inteiros. 

Se você quiser armazenar algum outro tipo de valor, precisará usar uma variável diferente.

Inteiros são apenas um dos muitos tipos de dados que C++ oferece suporte pronto para uso. 

C++ também permite que você crie seus próprios tipos definidos pelo usuário. Isso é algo que faremos principalmente em Machine Learning 
e é parte do que torna C++ uma linguagem poderosa.

*/

#include <iostream>
using namespace std;

int main()
{
    // Declaramos as variáveis
    int x;
    double y;
    int resultado_int;
    double resultado_double;

    // Inicializamos as variáveis
    x = 2;
    y = 3.1;

    // Operação
    resultado_int = x + y;
    resultado_double = x + y;

    // Imprime o resultado
    cout << "Resultado Int: " << resultado_int << endl;
    cout << "Resultado Double: " << resultado_double << endl;

}