/*
 
Estruturas Condicionais

Uma instrução condicional é uma instrução que especifica se alguma instrução associada deve ser executada ou não.

Sintaxe:

if (condition)
    true_statement;

Ou:

if (condition)
    true_statement;
else
    false_statement;

*/

#include <iostream>
using namespace std;

int main()
{
    cout << "Digite um número: ";
    int x;
    cin >> x;
 
    if (x > 10)
        cout << x << " é maior que 10\n";
    else
        cout << x << " é não é maior que 10\n";

}

/*

Exercício 4: Usando o script 07 como ponto de partida, desenvolva uma calculadora simples, solicitando ao usuário 2 números 
e a operação desejada. Certifique-se que o programa não gere erro em divisão por zero.

A solução será apresentada no próximo vídeo.

*/