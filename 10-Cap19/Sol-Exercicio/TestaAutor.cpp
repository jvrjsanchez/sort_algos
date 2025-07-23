/*

Solução do Exercício 

Código Para Teste do Programa

*/

#include "Autor.h"
 
int main() {

   Autor bob("Bob Silva", "bob@teste.com", 'm');
   bob.print();
   bob.setEmail("bob@superteste.com");
   bob.print();

   Autor mary("Mary Jane", "@super.com", 'f');
   mary.setEmail("mary@");
   mary.print();

}