// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Inclui o arquivo de cabeçalho onde a classe Embedding é definida
#include "../include/01DSAEmbedding.hpp"

// Construtor da classe Embedding, inicializa vocab_size, embed_dim e gera a matriz de embeddings
Embedding::Embedding(int vocab_size, int embed_dim){

    // Define o tamanho do vocabulário
    this->vocab_size = vocab_size;
    
    // Define a dimensão dos embeddings
    this->embed_dim = embed_dim;
    
    // Gera uma matriz de embeddings aleatória com as dimensões especificadas
    this->embedding_matrix = generateRandomEmbeddingMatrix(embed_dim, vocab_size);

    // Exibe as dimensões da matriz de embeddings no console
    std::cout << "Embedding matrix dims: " << embedding_matrix->size() << " x " << embedding_matrix[0].size() << std::endl;
}

// Função para imprimir a matriz de embeddings no console
void Embedding::printEmbeddingMatrix() {
    
    // Imprime uma mensagem indicando que a matriz de embeddings será exibida
    std::cout << "Embedding matrix: " << std::endl;
    
    // Itera sobre cada linha (token) da matriz de embeddings
    for (int i = 0; i < this->vocab_size; i++) { 
        
        // Itera sobre cada dimensão (valor do embedding) para o token atual
        for (int j = 0; j < this->embed_dim; j++) {
            
            // Imprime cada valor do embedding com precisão de 2 casas decimais e largura de 6
            std::cout << std::fixed << std::setprecision(2) << std::setw(6) << (*this->embedding_matrix)[i][j] << " ";
        }

        // Pula para a próxima linha após imprimir todos os valores do token atual
        std::cout << std::endl;
    }
}

// Função para salvar a matriz de embeddings em um arquivo
void Embedding::saveEmbeddingMatrix(const std::string& filename) {
    
    // Abre um arquivo para escrita
    std::ofstream file(filename);
    
    // Verifica se o arquivo foi aberto corretamente
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    // Cria um objeto stringstream para montar a string de saída
    std::ostringstream oss;
    
    // Itera sobre as linhas da matriz de embeddings
    for (int i = 0; i < this->vocab_size; i++) {
        
        // Itera sobre as colunas da matriz de embeddings
        for (int j = 0; j < this->embed_dim; j++) {
            
            // Adiciona o valor do embedding ao stringstream
            oss << (*this->embedding_matrix)[i][j] << " ";
        }
        
        // Adiciona uma nova linha após cada linha de embeddings
        oss << '\n'; 
    }

    // Escreve o conteúdo do stringstream no arquivo
    file << oss.str(); 
    
    // Fecha o arquivo após a gravação
    file.close();
}

// Função para carregar a matriz de embeddings de um arquivo
void Embedding::loadEmbeddingMatrix(const std::string& filename) {
    
    // Abre o arquivo para leitura
    std::ifstream file(filename);
    
    // Verifica se o arquivo foi aberto corretamente
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }

    // Redimensiona a matriz de embeddings para corresponder ao vocabulário e dimensões de embedding
    (*this->embedding_matrix).resize(this->vocab_size, std::vector<double>(this->embed_dim, 0.0f));

    // String para armazenar cada linha lida do arquivo
    std::string line;
    
    // Índice da linha atual (token)
    int row = 0;
    
    // Lê o arquivo linha por linha
    while (std::getline(file, line) && row < this->vocab_size) {
        
        // Usa uma stringstream para ler os valores da linha
        std::istringstream iss(line);
        
        // Armazena o valor lido da linha
        double value; 
        
        // Índice da coluna atual (dimensão do embedding)
        int col = 0; 

        // Lê os valores da linha e armazena na matriz de embeddings
        while (iss >> value && col < this->embed_dim) {
            (*this->embedding_matrix)[row][col] = value;
            ++col;
        }

        // Verifica se a linha não tem valores suficientes
        if (col != this->embed_dim) {
            std::cerr << "Error: Line " << (row + 1) << " does not have enough values." << std::endl;
            return;
        }

        ++row; // Avança para a próxima linha
    }

    // Verifica se o arquivo não tem linhas suficientes
    if (row != this->vocab_size) {
        std::cerr << "Error: File does not have enough lines." << std::endl;
        return;
    }

    // Fecha o arquivo após a leitura
    file.close();
}

// Função que gera uma matriz de embeddings aleatória
std::vector<std::vector<double>> *Embedding::generateRandomEmbeddingMatrix(int embed_dim, int vocab_size){
    
    // Aloca a matriz de embeddings
    std::vector<std::vector<double>>* embedding_matrix= new std::vector<std::vector<double>>(vocab_size, std::vector<double>(embed_dim, 0.0));
    
    // Inicializa um gerador de números aleatórios
    std::random_device rd;
    
    // Inicializa o gerador Mersenne Twister
    std::mt19937 gen(rd());
    
    // Define uma distribuição uniforme entre 0 e 1
    std::uniform_real_distribution<> dis(0, 1);
    
    // Preenche a matriz de embeddings com valores aleatórios
    for (int i = 0; i < this->vocab_size; i++){
        for (int j = 0; j < this->embed_dim; j++){

            // Atribui o valor aleatório ao embedding
            (*embedding_matrix)[i][j] = dis(gen); 
        }
    }

    // Retorna o ponteiro para a matriz de embeddings gerada
    return embedding_matrix; 
}

// Função que retorna o embedding correspondente ao token_id fornecido
std::vector<double> Embedding::getEmbedding(int token_id){

    // Retorna o embedding do token
    return (*this->embedding_matrix)[token_id]; 
}

// Função que converte uma lista de tokens em uma lista de embeddings
std::vector<std::vector<double>> *Embedding::tokenToEmbeddings(std::vector<int> tokens){
    
    // Aloca um vetor de embeddings para os tokens fornecidos
    std::vector<std::vector<double>>* embeddings = new std::vector<std::vector<double>>( tokens.size() , std::vector<double>(this->embed_dim, 0.0));
    
    // Associa o embedding correspondente a cada token
    for (int i = 0; i < tokens.size(); i++){
        (*embeddings)[i] = (*this->embedding_matrix)[tokens[i]];
    }
    
    // Retorna o vetor de embeddings
    return embeddings; 
}

// Destrutor da classe Embedding
Embedding::~Embedding()
{
    // Libera a memória alocada para a matriz de embeddings
    delete this->embedding_matrix;
}
