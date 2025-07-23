// Hello World em C++

/* As linhas que começam com um sinal de hash (#) são diretivas lidas e interpretadas pelo que é conhecido como pré-processador. 
São linhas especiais interpretadas antes do início da compilação do próprio programa. 
Neste caso, a diretiva #include <iostream> instrui o pré-processador a incluir uma seção do código C++ padrão, 
conhecido como cabeçalho iostream, que permite realizar operações de entrada e saída padrão, como escrever a 
saída deste programa (Hello World ) na tela. */
#include <iostream>

// O namespace indica conjunto de funções para tarefas específicas.
// Nesse caso tarefas padrões.
using namespace std;

// Esta linha inicia a declaração de uma função. Essencialmente, uma função é um grupo de instruções de código que recebem um nome. 
// Neste caso o nome "main" é o nome do grupo de instruções de código que se seguem. 
// As funções serão discutidas em detalhes em um capítulo posterior mas, essencialmente, sua definição é introduzida com uma 
// sucessão de um tipo (int), um nome (main) e um par de parênteses, opcionalmente incluindo parâmetros.
// A função chamada main() é uma função especial em todos os programas C++; é a função chamada quando o programa é executado. 
// A execução de todos os programas C++ começa com a função main(), independentemente de onde a função está realmente 
// localizada no código.
int main() {

  /* Esta linha é uma instrução C++. 
  É a essência de um programa, especificando seu comportamento real. As instruções são executadas na mesma ordem em que 
  aparecem no corpo de uma função. */
  cout << "Hello World DSA!";

  // Função para imprimir no dispositivo de saída.
  // Nesse caso imprime o caracter de nova linha.
  printf("\n");

  // Retorna o resultado da função.
  return 0;

}