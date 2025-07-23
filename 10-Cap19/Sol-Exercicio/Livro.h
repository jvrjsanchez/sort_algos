/* Solução do Exercício */
/* Biblioteca da Classe Livro */

/* Inclui a biblioteca de strings do C++ */
#include <string>

/* Inclui o cabeçalho da classe Autor para poder usar a classe Autor como tipo */
#include "Autor.h"

/* Uso do espaço de nomes padrão */
using namespace std;

/* Definição da classe Livro */
class Livro {

/* Membros privados da classe Livro */
private:
   
   string nome;               // Nome do livro
   Autor autor;               // Objeto Autor associado ao livro
   double valor;              // Preço do livro
   int quantidadeEstoque;     // Quantidade do livro em estoque

/* Membros públicos da classe Livro */
public:
   
   // Construtor que inicializa um livro com nome, autor, valor e quantidade em estoque (padrão 0)
   Livro(string nome, Autor autor, double valor, int quantidadeEstoque = 0);

   // Método que retorna o nome do livro
   string getNome();

   // Método que retorna o autor do livro
   Autor getAutor();

   // Método que retorna o valor do livro
   double getValor();

   // Método que define o valor do livro
   void setValor(double valor);

   // Método que retorna a quantidade de livros em estoque
   int getquantidadeEstoque();

   // Método que define a quantidade de livros em estoque
   void setquantidadeEstoque(int quantidadeEstoque);

   // Método que imprime as informações do livro
   void print();

   // Método que retorna o nome do autor do livro
   string getAutorNome();
};
