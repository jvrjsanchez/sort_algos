/*

Loop Do-While

Considere o caso em que queremos mostrar ao usuário um menu e pedir-lhe para fazer uma seleção - e se o usuário escolher uma seleção 
inválida, perguntar novamente. Obviamente, o menu e a seleção devem entrar em algum tipo de loop (para que possamos continuar 
perguntando ao usuário até que ele insira uma entrada válida), mas que tipo de loop devemos escolher?

Já que um loop while avalia a condição de antemão, não é a escolha ideal.
 
Para ajudar a resolver problemas como o acima, C++ oferece a instrução do-while:

do
     statement
while (condição);

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
        cout << "1 - C++\n";
        cout << "2 - Python\n";
        cout << "3 - Rust\n";
        cout << "4 - Java\n";
        cin >> seletor;
    }
    while (seletor != 1 && seletor != 2 && seletor != 3 && seletor != 4);

    cout << "Você escolheu a opção: " << seletor << endl;
 
}

/*

Exercício 2: Imprima os números de 1 a 5 usando do-while

A solução será apresentada no próximo vídeo.

*/