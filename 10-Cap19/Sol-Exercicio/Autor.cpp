/* Solução do Exercício */
/* Código do Programa */

/* Inclui a biblioteca de entrada e saída padrão */
#include <iostream>

/* Inclui o cabeçalho da classe Autor */
#include "Autor.h"

/* Uso do espaço de nomes padrão */
using namespace std;

/* Implementação do construtor da classe Autor */
Autor::Autor(string nome, string email, char genero) {

   /* Atribui o nome fornecido ao membro nome da classe */
   this -> nome = nome;
   
   /* Chama o método setEmail para definir o email */
   setEmail(email); 
   
   /* Verifica se o gênero é válido ('m' ou 'f') */
   if (genero == 'm' || genero == 'f') {

      /* Atribui o gênero fornecido ao membro gênero da classe */
      this -> genero = genero;

   } else {

      /* Imprime mensagem de erro se o gênero for inválido */
      cout << "Gênero Inválido!" << endl;
   }
}
 
/* Método para obter o nome do autor */
string Autor::getNome() const {
   return nome;
}
 
/* Método para obter o email do autor */
string Autor::getEmail() const {
   return email;
}
 
/* Método para definir o email do autor */
void Autor::setEmail(string email) {

   /* Busca a posição do caractere '@' no email */
   size_t atIndex = email.find('@');
   
   /* Verifica se o '@' está em posição válida */
   if (atIndex != string::npos && atIndex != 0 && atIndex != email.length()-1) {

      /* Atribui o email válido ao membro email */
      this -> email = email; 

   } else {

      /* Imprime mensagem de erro se o email for inválido */
      cout << "Email Inválido! Colocando NA." << endl;

      /* Atribui "NA" ao membro email caso seja inválido */
      this -> email = "NA";
   }
}
 
/* Método para obter o gênero do autor */
char Autor::getGenero() const {
   return genero;
}
 
/* Método para imprimir informações do autor */
void Autor::print() const {
   
   /* Imprime o nome, gênero e email do autor */
   cout << nome << " (" << genero << ") e e-mail: " << email << endl;
}
