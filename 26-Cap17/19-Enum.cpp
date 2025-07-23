/*

Tipos de Dados Definido Pelo Usuário - Enum

C++ contém alguns tipos de dados integrados. Mas esses tipos nem sempre são suficientes para os tipos de coisas que queremos fazer. 

Portanto, C++ contém recursos que permitem aos programadores criar seus próprios tipos de dados. Esses tipos de dados são chamados 
de tipos de dados definidos pelo usuário.

Talvez o tipo de dado mais simples definido pelo usuário seja o tipo enumerado (enum). Um tipo enumerado 
(também chamado de enumeração ou enum) é um tipo de dado em que cada valor possível é definido como uma constante simbólica 
(chamada de enumerador). Enumerações são definidas por meio da palavra-chave enum. 

*/

#include <iostream>
#include <string>
using namespace std;

// Enum
enum Cor
{
    cor_azul,
    cor_marrom,
    cor_verde
};
 
string getCorName(Cor cor)
{
    if (cor == cor_azul)
        return "Azul";
    if (cor == cor_marrom)
        return "Marrom";
    if (cor == cor_verde)
        return "Verde";

    return "?";
}
 
int main()
{

    // Declara variável do tipo enum
    Cor cor_carro = { cor_azul };
 
    // Imprime na tela
    cout << "\nID  da Cor do seu carro: " << cor_carro << "\n\n";

    cout << "\nCor do seu carro: " << getCorName(cor_carro) << "\n\n";

}