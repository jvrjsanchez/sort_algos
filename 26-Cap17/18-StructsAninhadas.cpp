/*

Structs Aninhadas

*/ 

#include <cstdint>
#include <iostream>
using namespace std;

// Primeira struct
struct Funcionario
{
    int16_t id;
    int32_t idade;
    double salario;
};
 
// Segunda struct
struct Empresa
{
    Funcionario CEO; 
    int numFun;
};
 
// Função
void imprimeEmpresa(Empresa empresa)
{
    cout << "ID do CEO:   " << empresa.CEO.id << '\n';
    cout << "Idade do CEO:  " << empresa.CEO.idade << '\n';
    cout << "Salário do CEO: " << empresa.CEO.salario << '\n';
    cout << "Número de Funcionários: " << empresa.numFun << '\n';
}

// Função
void imprimeFunc(Funcionario func)
{
    cout << "ID:   " << func.id << '\n';
    cout << "Idade:  " << func.idade << '\n';
    cout << "Salário: " << func.salario << '\n';
}
 
int main()
{
    // Inicializa a variável chamada ABC do tipo Empresa
    Empresa ABC;

    // Atribui valores às variáveis
    ABC.CEO.id = 1;
    ABC.CEO.idade = 62;
    ABC.CEO.salario = 75000.00;
    ABC.numFun = 120;

    // Imprime ABC
    cout << "\nDados da Empresa ABC:" << "\n";
    imprimeEmpresa(ABC);

    // Inicializa a variável chamada ZXY do tipo Empresa
    Empresa ZXY = {{ 10, 58, 85000.0 }, 140 };

    // Imprime ZXY
    cout << "\nDados da Empresa ZXY:" << "\n";
    imprimeEmpresa(ZXY);

    // Inicializa a variável chamada bob do tipo Funcionario
    Funcionario bob = { 1001, 42, 3589.15 };

    // Imprime Bob
    cout << "\nDados do Bob:" << "\n";
    imprimeFunc(bob);
 
    
 
 }