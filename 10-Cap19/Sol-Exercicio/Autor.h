/* Solução do Exercício */
/* Biblioteca da Classe Autor */

/* Inclusão da biblioteca de strings */
#include <string>

/* Uso do espaço de nomes padrão */
using namespace std;

/* Definição da classe Autor */
class Autor {

/* Declaração de variáveis privadas */
private:
   string nome;   // Nome do autor
   string email;  // Email do autor
   char genero;   // Gênero do autor (assumido como 'm', 'f', etc.)

/* Declaração de métodos públicos */
public:
   
   // Construtor da classe Autor
   Autor(string nome, string email, char genero);

   // Método para obter o nome do autor
   string getNome() const;

   // Método para obter o email do autor
   string getEmail() const;

   // Método para definir o email do autor
   void setEmail(string email);

   // Método para obter o gênero do autor
   char getGenero() const;

   // Método para imprimir informações do autor
   void print() const;
};
