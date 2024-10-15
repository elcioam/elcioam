#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <string>
#include <filesystem> // Necessário para manipulação de diretórios

// Função para remover pontuação e padronizar para minúscula
std::string removePontuacaoPadronizaMinuscula(const std::string& linhaLivro) {
    std::string linhaNormalizada;

    // Processa cada caractere na string
    for (char c : linhaLivro) {
        if (!ispunct(c)) { // Se não for pontuação
            // Converte para minúscula e adiciona ao resultado normalizado
            linhaNormalizada.push_back(tolower(c));
        }
    }

    return linhaNormalizada;
}

// Função para ler um arquivo contendo um livro e retornar um vetor de strings
std::vector<std::string> lerLivro(const std::string& nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    std::string linha; // String para armazenar cada linha do arquivo
    std::vector<std::string> livro; // Vetor de strings para armazenar as linhas do arquivo

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
        return livro; // Retorna um vetor vazio em caso de erro
    }

    while (std::getline(arquivo, linha)) {
        // Remove pontuação e padroniza para minúscula
        std::string linhaProcessada = removePontuacaoPadronizaMinuscula(linha);
        // Adiciona a linha processada ao vetor, se não estiver vazia
        if (!linhaProcessada.empty()) {
            livro.push_back(linhaProcessada);
        }
    }

    arquivo.close();
    return livro;
}

// Função para salvar o conteúdo processado em um arquivo
void salvarLivroProcessado(const std::vector<std::string>& livro, const std::string& nomeArquivoSaida) {
    // Verifica se a pasta "output" existe, caso contrário, cria
    std::filesystem::create_directory("output");

    // Cria o arquivo na pasta "output"
    std::ofstream arquivoSaida("output/" + nomeArquivoSaida);
    if (!arquivoSaida.is_open()) {
        std::cerr << "Erro ao criar o arquivo de saída: " << nomeArquivoSaida << std::endl;
        return;
    }

    // Escreve cada linha do vetor no arquivo
    for (const auto& linha : livro) {
        arquivoSaida << linha << std::endl;
    }

    arquivoSaida.close();
    std::cout << "Arquivo salvo em: output/" << nomeArquivoSaida << std::endl;
}

int main() {
    std::string nomeArquivoEntrada = "input/biblia.txt"; // Nome do arquivo para leitura
    std::string nomeArquivoSaida = "livro_processado.txt"; // Nome do arquivo de saída

    // Lê o livro e processa
    std::vector<std::string> livro = lerLivro(nomeArquivoEntrada);

    // Salva o resultado processado em um arquivo na pasta "output"
    salvarLivroProcessado(livro, nomeArquivoSaida);

    return 0;
}
