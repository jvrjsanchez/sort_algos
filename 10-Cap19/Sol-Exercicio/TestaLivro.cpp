/*

Solução do Exercício 

Código Para Teste do Programa

*/

#include <iostream>
#include "Livro.h"
using namespace std;
 
int main() {

   Autor bob("Bob Silva", "bob@teste.com", 'm');
   bob.print(); 
 
   Livro livrochoc("Receitas de Bolo de Chocolate", bob, 83.57);
   livrochoc.setquantidadeEstoque(120);
   livrochoc.print();
 
   cout << livrochoc.getquantidadeEstoque() << endl;  
   cout << livrochoc.getValor() << endl;       
   cout << livrochoc.getAutor().getNome() << endl; 
   cout << livrochoc.getAutor().getEmail() << endl; 
   cout << livrochoc.getAutorNome() << endl;        
 
   Livro livroajuda("Como Ser Mais Paciente", bob, -45.32);
   cout << livroajuda.getValor() << endl;  
}