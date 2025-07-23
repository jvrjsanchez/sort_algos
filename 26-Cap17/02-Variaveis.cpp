/* 

Manipulando Variáveis

Um programa pode adquirir dados para trabalhar de várias maneiras: de um arquivo ou banco de dados, através de uma rede, 
do usuário fornecendo entrada em um teclado ou do programador colocando dados diretamente no código-fonte do próprio programa. 

No programa “Hello world”, o texto “Hello world!” foi inserido diretamente no código-fonte do programa, fornecendo dados para o programa usar. 

O programa então manipula esses dados enviando-os ao monitor para serem exibidos.

Os dados em um computador são normalmente armazenados em um formato que é eficiente para armazenamento ou processamento 
(e, portanto, não pode ser lido por humanos). Assim, quando o programa “Hello World” é compilado, o texto “Hello world!” é convertido 
em um formato mais eficiente para o programa usar.

Em C++ acessamos a memória indiretamente por meio de um objeto. 

Um objeto é uma região de armazenamento (geralmente memória) que tem um valor e outras propriedades associadas. Quando um objeto é definido, 
o compilador determina automaticamente onde o objeto será colocado na memória. Como resultado, em vez de dizer vá obter o valor armazenado 
na caixa de correio número 320, podemos dizer, vá obter o valor armazenado por esse objeto e o compilador saberá onde procurar esse 
valor na memória. Isso significa que podemos nos concentrar no uso de objetos para armazenar e recuperar valores, e não precisamos nos 
preocupar onde na memória eles estão realmente sendo colocados.

Os objetos podem ser nomeados ou não nomeados (anônimos). 

Um objeto nomeado é chamado de variável e o nome do objeto é chamado de identificador. Em nossos programas, a maioria dos objetos que 
criamos serão variáveis.

A linha using namespace std; no código C++ é usada para evitar a necessidade de prefixar todos os nomes das entidades da 
biblioteca padrão C++ (por exemplo, cout, cin, endl, etc.) com std::.

Sem esta linha, você teria que escrever std::cout em vez de apenas cout, std::endl em vez de apenas endl, e assim por diante. 
Isso pode tornar o código mais conciso e legível.

*/

#include <iostream>
using namespace std;

int main()
{
    // Declaramos a variável
    int x;

    // Inicializamos a variável
    x = 10;

    cout << "Hello world!" << endl;
    
    // Imprimimos o valor de x
    cout << "Valor de x: " << x << endl;

    return 0;
}
