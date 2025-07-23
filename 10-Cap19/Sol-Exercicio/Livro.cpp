/* Solução do Exercício */
/* Código do Programa */

/* Inclui a biblioteca padrão de entrada e saída */
#include <iostream>

/* Inclui o cabeçalho da classe Livro */
#include "Livro.h"

/* Uso do espaço de nomes padrão */
using namespace std;

/* Implementação do construtor da classe Livro */
Livro::Livro(string nome, Autor autor, double valor, int quantidadeEstoque) : nome(nome), autor(autor) {  

   // Define o valor usando o método setValor
   setValor(valor);

   // Define a quantidade em estoque usando o método setquantidadeEstoque
   setquantidadeEstoque(quantidadeEstoque);
}
 
/* Método para obter o nome do livro */
string Livro::getNome() {
   return nome;
}
 
/* Método para obter o objeto Autor associado ao livro */
Autor Livro::getAutor() {
   return autor;
}
 
/* Método para obter o valor do livro */
double Livro::getValor() {
   return valor;
}
 
/* Método para definir o valor do livro */
void Livro::setValor(double valor) {

   // Verifica se o valor é maior que zero
   if (valor > 0) {
      this -> valor = valor;

   } else {

      // Imprime mensagem de erro se o valor for negativo e define valor como 0
      cout << "O valor não pode ser negativo! Colocando 0." << endl;
      this -> valor = 0;
   }
}
 
/* Método para obter a quantidade de livros em estoque */
int Livro::getquantidadeEstoque() {
   return quantidadeEstoque;
}
 
/* Método para definir a quantidade de livros em estoque */
void Livro::setquantidadeEstoque(int quantidadeEstoque) {

   // Verifica se a quantidade é não-negativa
   if (quantidadeEstoque >= 0) {
      this -> quantidadeEstoque = quantidadeEstoque;

   } else {

      // Imprime mensagem de erro se a quantidade for negativa e define como 0
      cout << "A quantidade não pode ser negativa! Colocando 0." << endl;
      this -> quantidadeEstoque = 0;
   }
}
 
/* Método para imprimir as informações do livro */
void Livro::print() {
   
   // Imprime o nome do livro e as informações do autor
   cout << "'" << nome << "' por ";
   autor.print();
}
 
/* Método para obter o nome do autor do livro */
string Livro::getAutorNome() {
   return autor.getNome();
}
