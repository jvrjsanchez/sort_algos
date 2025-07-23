/*

Library I/O 

A biblioteca de entrada / saída (biblioteca io) é parte da biblioteca padrão C++ que lida com entrada e saída básicas. 

Usaremos a funcionalidade desta biblioteca para obter entrada do teclado e dados de saída para o console. 

A parte io de iostream significa entrada / saída.

Para usar a funcionalidade definida na biblioteca iostream, precisamos incluir o cabeçalho iostream na parte superior de qualquer 
arquivo de código que use o conteúdo definido no iostream.

*/

// Para usar std::cout, std::cin e std::endl
#include <iostream> 
 
int main()
{
    // define a variável inteira x, inicializada com o valor 5
    int x(5); 

    // imprime o valor de x (5) para o console
    std::cout << "\nValor da variável x: " << x << std::endl; 

    // Solicita que o usuário digite um número
    std::cout << "\nDigite um número: "; 

    // define a variável x para manter a entrada do usuário (e inicializa-a com zero)
    int y; 

    // obtém o número do teclado e armazena-o na variável x
    std::cin >> y; 

    // Mensagem de saída
    std::cout << "\nVocê digitou " << y << "\n\n";
}