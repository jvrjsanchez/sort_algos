/*

Arrays
 
Um array é um tipo de dado agregado que nos permite acessar muitas variáveis do mesmo tipo por meio de um único identificador.

Para declarar um array, usamos colchetes ([]) para dizer ao compilador que esta é uma variável de array (em vez de uma variável normal), 
bem como quantas variáveis alocar (chamado de comprimento do array).

Cada uma das variáveis em um array é chamada de elemento. Os elementos não têm seus próprios nomes exclusivos. Em vez disso, para 
acessar elementos individuais de um array, usamos o nome do array, junto com o operador subscrito ([]) e um parâmetro chamado 
subscrito (ou índice) que informa ao compilador qual elemento queremos. Esse processo é chamado de subscrito ou indexação do array.

*/

#include <iostream>
using namespace std;

int main()
{
    // Cria um array de números inteiros
    int lista[5]; 

    // Atribui valores a cada elemento do array
    lista[0] = 1; 
    lista[1] = 2;
    lista[2] = 3;
    lista[3] = 4;
    lista[4] = 5; 
 
    cout << "\nEste é o primeiro elemento do array: " << lista[0] << '\n';
    cout << "Aqui está a soma de todos os elementos do array: " << lista[0] + lista[1] + lista[2] + lista[3] + lista[4] << "\n\n";
 
}

/*

Exercício 5: Crie um loop para percorrer o array acima e imprimir o índice e o valor de cada elemento do array.

A solução será apresentada no próximo vídeo.

*/