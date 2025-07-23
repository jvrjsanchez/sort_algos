// Projeto 7 - Construindo Aplicação em C++ Usando Programação Orientada a Objetos

// Inclusão da biblioteca iostream para operações de entrada/saída
#include <iostream>

// Inclusão da biblioteca fstream para operações de arquivo
#include <fstream>

// Inclusão da biblioteca cstring para funções de manipulação de strings
#include <cstring>

// A sstream oferece classes e funções para manipular strings de maneira semelhante à manipulação de fluxos de entrada e saída, como cin e cout.
#include <sstream>  

// Declaração de uso do namespace std para evitar a necessidade de prefixar as funções da STL com 'std::'
using namespace std;

// Declaração da classe BinarySearchTree
class BinarySearchTree {

private:
    
    // Estrutura interna Node para representar cada nó da árvore
    struct Node {

        int value;  // Valor armazenado no nó
        Node *left; // Ponteiro para o filho à esquerda
        Node *right; // Ponteiro para o filho à direita

        // Construtor de Node inicializa o nó com um valor e ponteiros nulos para os filhos
        Node(int val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root; // Ponteiro para o nó raiz da árvore

    // Método privado para inserir um valor na árvore
    Node* insert(Node* node, int value) {

        // Se o nó atual é nulo, cria um novo nó com o valor
        if (!node) return new Node(value);

        // Decide se o valor deve ser inserido à esquerda ou à direita
        if (value < node->value)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);

        // Retorna o nó após inserção
        return node;
    }

    // Método privado para imprimir a árvore
    void print(Node* node, int space) {

        // Se o nó é nulo, retorna sem fazer nada
        if (!node) return;

        // Aumenta o espaço para formatação
        space += 10;

        // Imprime o filho à direita primeiro (árvore invertida)
        print(node->right, space);
        cout << endl;

        // Imprime espaços para alinhamento visual
        for (int i = 10; i < space; i++) cout << " ";

        // Imprime o valor do nó
        cout << node->value << "\n";

        // Imprime o filho à esquerda
        print(node->left, space);
    }

    // Método privado para buscar um valor na árvore
    Node* search(Node* node, int value) {

        // Retorna nulo se o nó é nulo ou se o valor foi encontrado
        if (!node || node->value == value) return node;

        // Busca recursivamente à esquerda ou à direita dependendo do valor
        if (value < node->value)
            return search(node->left, value);
        else
            return search(node->right, value);
    }

    // Método privado para deletar um nó da árvore
    Node* deleteNode(Node* node, int value) {

        // Se nó é nulo, retorna nulo
        if (!node) return node;

        // Navega na árvore para encontrar o nó a ser deletado
        if (value < node->value)
            node->left = deleteNode(node->left, value);
        else if (value > node->value)
            node->right = deleteNode(node->right, value);
        else {
            // Encontra o nó a ser deletado
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Substitui o valor do nó pelo menor valor à direita
            Node* temp = minValueNode(node->right);
            node->value = temp->value;

            // Deleta o menor nó à direita que foi movido para substituição
            node->right = deleteNode(node->right, temp->value);
        }

        return node;
    }

    // Método privado para encontrar o menor nó na subárvore
    Node* minValueNode(Node* node) {
        Node* current = node;

        // Percorre para encontrar o nó mais à esquerda
        while (current && current->left)
            current = current->left;
        return current;
    }

public:

    // Construtor da classe BinarySearchTree inicializa a raiz como nula
    BinarySearchTree() : root(nullptr) {}

    // Método público para inserir valor na árvore
    void insert(int value) {
        root = insert(root, value);
    }

    // Método público para imprimir a árvore
    void print() {
        print(root, 0);
    }

    // Método público para buscar valor na árvore e retornar se encontrado
    bool search(int value) {
        return search(root, value) != nullptr;
    }

    // Método público para deletar valor da árvore
    void deleteValue(int value) {
        root = deleteNode(root, value);
    }
};

// Função principal que executa o programa
int main() {

    // Cria uma instância da árvore binária de busca
    BinarySearchTree bst; 

    // Variável de controle para loop principal
    bool running = true; 

    // Buffer para entrada do usuário
    char input[999]; 

    // Loop principal do programa
    while (running) {
        
        cout << "\nEscolha Uma Opção do Menu (Digite a Letra em Maiúsculo):" << endl;
        cout << "(C)arregar, (I)mprimir, (D)eletar, (B)uscar, (E)ncerrar" << endl;
        cin >> input;

        switch (input[0]) {
            case 'C': {
                cout << "(T)erminal, (A)rquivo" << endl;
                cin >> input;
                if (input[0] == 'T') {
                    cout << "Digite números separados com espaço, por exemplo: 1 2 3 4 5" << endl;
                    cin.ignore();
                    string line;
                    getline(cin, line);
                    istringstream iss(line);
                    int num;
                    while (iss >> num) bst.insert(num);
                } else if (input[0] == 'A') {
                    cout << "Digite o nome do arquivo:" << endl;
                    string filename;
                    cin >> filename;
                    ifstream file(filename);
                    int num;
                    while (file >> num) bst.insert(num);
                    cout << "Arquivo carregado na memória!" << endl;
                }
                break;
            }
            case 'I':
                bst.print();
                break;
            case 'D': {
                cout << "Digite o valor que você deseja deletar:" << endl;
                int delVal;
                cin >> delVal;
                bst.deleteValue(delVal);
                break;
            }
            case 'B': {
                cout << "Digite o valor que você deseja buscar:" << endl;
                int searchVal;
                cin >> searchVal;
                bool found = bst.search(searchVal);
                if (found)
                    cout << "SUCESSO! O valor foi encontrado no conjunto de dados!" << endl;
                else
                    cout << "O valor não foi encontrado no conjunto de dados!" << endl;
                break;
            }
            case 'E':
                running = false; // Encerra o loop e o programa
                break;
        }
    }

    return 0; // Encerra a função main
}
