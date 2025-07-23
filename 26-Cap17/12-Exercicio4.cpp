/*
 
Solução do Exercício 4: Usando o script 07 como ponto de partida, desenvolva uma calculadora simples, solicitando ao usuário 2 números 
e a operação desejada. Certifique-se que o programa não gere erro em divisão por zero.

*/


#include <iostream>
using namespace std;
 
int main()
{
    // Declara a variável
    int seletor;
 
    // Loop
    do
    {
        cout << "\nPor favor escolha uma opção (de 1 a 4): \n";
        cout << "1 - Soma\n";
        cout << "2 - Subtração\n";
        cout << "3 - Multiplicação\n";
        cout << "4 - Divisão\n";
        cin >> seletor;
    }
    while (seletor != 1 && seletor != 2 && seletor != 3 && seletor != 4);

    int num1;
    int num2;

    cout << "Digite o primeiro número: ";
    cin >> num1;

    cout << "Digite o segundo número: ";
    cin >> num2;

    if (seletor == 1){
        cout << "A soma dos números é: " << num1 + num2 << "\n\n";
    }

    if (seletor == 2){
        cout << "A subtração do número 1 pelo número 2 é: " << num1 - num2 << "\n\n";
    }

    if (seletor == 3){
        cout << "A multiplicação dos números é: " << num1 * num2 << "\n\n";
    }

    if (seletor == 4){
        if (num2 == 0){
            cout << "Desculpe, mas não há divisão por 0" << "\n\n";
        }
        else{
            cout << "A divisão do número 1 pelo número 2 é: " << num1 / num2 << "\n\n";
        }
    }
 
}