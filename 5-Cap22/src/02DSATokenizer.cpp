// Projeto 9 - Construindo Um LLM a Partir do Zero com Arquitetura Transformers em C++

// Inclui o arquivo de cabeçalho onde a classe Tokenizer é definida
#include "../include/02DSATokenizer.hpp"

// Construtor da classe Tokenizer
Tokenizer::Tokenizer(){

    // Inicializa o mapa de palavras para IDs de tokens como um mapa vazio
    this->word_to_token_id = std::unordered_map<std::string, int>();
}

// Função que transforma um texto em uma sequência de IDs de tokens
std::vector<int> Tokenizer::tokenize(std::string text){
    
    // Vetor que armazenará os tokens (IDs)
    std::vector<int> tokens;
    
    // Cria um stream de entrada baseado na string de texto fornecida
    std::istringstream iss(text);
    
    // String temporária para armazenar cada palavra lida do texto
    std::string word;
    
    // Loop que extrai cada palavra da string de entrada
    while (iss >> word)
    {
        // Se a palavra não estiver no mapa de word_to_token_id, ela é adicionada
        if (this->word_to_token_id.find(word) == this->word_to_token_id.end())
        {
            // Cria um novo token_id baseado no tamanho atual do mapa
            int token_id = this->word_to_token_id.size();
            
            // Mapeia a palavra para o novo token_id
            this->word_to_token_id[word] = token_id;
            
            // Mapeia o token_id de volta para a palavra no mapa token_id_to_word
            this->token_id_to_word[token_id] = word;
        }
        // Adiciona o token (ID) correspondente à palavra no vetor de tokens
        tokens.push_back(this->word_to_token_id[word]);
    }
    // Retorna o vetor de tokens gerado
    return tokens;
}

// Função que imprime o mapa de palavras para IDs de tokens
void Tokenizer::printWordToTokenIdMap() const{

    // Exibe uma mensagem no console
    std::cout << "Word to Token ID Map:" << std::endl;
    
    // Itera sobre o mapa word_to_token_id e imprime cada par palavra -> token_id
    for (const auto &pair : this->word_to_token_id)
    {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }
}

// Função que retorna o tamanho do vocabulário (número de palavras únicas)
int Tokenizer::getVocabSize(){

    // Retorna o número de entradas no mapa word_to_token_id
    return this->word_to_token_id.size();
}

// Função que converte uma sequência de IDs de tokens de volta para uma string de texto
std::string Tokenizer::detokenize(std::vector<int> tokens){

    // String que armazenará o texto detokenizado
    std::string text;
    
    // Itera sobre o vetor de tokens (IDs) e reconstrói o texto original
    for (int i = 0; i < tokens.size(); i++)
    {
        // Adiciona a palavra correspondente ao token_id ao texto, seguida de um espaço
        text+=this->token_id_to_word[tokens[i]] + " ";
    }
    // Retorna o texto detokenizado
    return text;
}

// Função que salva o mapa de tokens em um arquivo
void Tokenizer::saveTokenMap(std::string filename){

    // Cria um objeto de saída de arquivo
    std::ofstream file;
    
    // Abre o arquivo para escrita
    file.open(filename);
    
    // Itera sobre o mapa word_to_token_id e salva cada par palavra -> token_id no arquivo
    for (const auto &pair : this->word_to_token_id)
    {
        file << pair.first << " " << pair.second << std::endl;
    }
    // Fecha o arquivo após a gravação
    file.close();
}

// Função que carrega o mapa de tokens de um arquivo
void Tokenizer::loadTokenMap(std::string filename){

    // Cria um objeto de entrada de arquivo
    std::ifstream file;
    
    // Tenta abrir o arquivo e captura exceções caso falhe
    try
    {
        file.open(filename);
    }
    catch(const std::exception& e)
    {
        return;
    }
    
    // Mensagem de sucesso após carregar o mapa de tokens
    std::cout << "Loaded token map successfully" << std::endl;
    
    // Strings temporárias para armazenar as palavras e IDs durante a leitura do arquivo
    std::string word;
    int token_id;
    
    // Lê cada linha do arquivo e preenche os mapas word_to_token_id e token_id_to_word
    while (file >> word >> token_id)
    {
        this->word_to_token_id[word] = token_id;
        this->token_id_to_word[token_id] = word;
    }
    
    // Fecha o arquivo após a leitura
    file.close();
}

// Função que gera uma codificação one-hot para um token específico
std::vector<std::vector<double>> Tokenizer::oneHotEncode(int token_id) {
    
    // Cria um vetor que armazenará a codificação one-hot
    std::vector<std::vector<double>> oneHotLabels;
    
    // Cria um vetor preenchido com zeros, com o tamanho igual ao vocabulário
    std::vector<double> oneHotLabel(this->word_to_token_id.size(), 0);
    
    // Define o valor 1 na posição correspondente ao token_id
    oneHotLabel[token_id] = 1;
    
    // Adiciona a codificação one-hot gerada ao vetor de rótulos
    oneHotLabels.push_back(oneHotLabel);

    // Retorna o vetor de codificações one-hot
    return oneHotLabels;
}

// Destrutor da classe Tokenizer
Tokenizer::~Tokenizer()
{
    // O destrutor não faz nada explicitamente, pois não há recursos dinâmicos para liberar
}
