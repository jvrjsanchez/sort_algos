/*

Manipulando Structs

Há muitas situações em programação em que precisamos de mais de uma variável para representar um objeto. 

Por exemplo, para representar um funcionário, você pode armazenar nome, aniversário, altura, peso ou qualquer outra característica.

Felizmente, C++ nos permite criar nossos próprios tipos de dados agregados definidos pelo usuário. 

Um tipo de dado agregado é um tipo de dado que agrupa diversas variáveis individuais. 

Um dos tipos de dados agregados mais simples é o struct. 

Um struct (abreviação de estrutura) nos permite agrupar variáveis de tipos de dados mistos em uma única unidade.

*/

#include <iostream>
using namespace std;

// Declara um struct
struct Funcionario
{
    int id;
    int idade;
    double salario;
};
 
// Função
void imprimeFunc(Funcionario func)
{
    cout << "ID:   " << func.id << '\n';
    cout << "Idade:  " << func.idade << '\n';
    cout << "Salário: " << func.salario << '\n';
}
 
int main()
{
    // Inicializa a variável chamada bob do tipo Funcionario
    Funcionario bob = { 1001, 42, 3589.15 };

    // Inicializa a variável chamada maria do tipo Funcionario
    Funcionario maria = { 2003, 28, 4561.27 };
 
    // Imprime Bob
    cout << "\nDados do Bob:" << "\n";
    imprimeFunc(bob);
 
    // Imprime Maria
    cout << "\nDados da Maria:" << "\n";
    imprimeFunc(maria);
 }


 