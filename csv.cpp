#include <iostream>
#include <fstream>
#include <string>
#include <vector>


// Função para ler um arquivo CSV
std::vector<std::vector<std::string>> lerArquivoCSV(const std::string& nomeArquivo) {
    std::vector<std::vector<std::string>> dadosCSV;
    std::ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        std::string linha;

        while (std::getline(arquivo, linha)) {
            std::vector<std::string> linhaCSV;
            std::string elemento;

            // Use ',' como delimitador para dividir a linha em elementos
            std::istringstream linhaStream(linha);
            while (std::getline(linhaStream, elemento, ',')) {
                linhaCSV.push_back(elemento);
            }

            dadosCSV.push_back(linhaCSV);
        }

        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
    }

    return dadosCSV;
}

int main() {
    std::string nomeArquivo = "galaxys.csv"; // Substitua com o nome do seu arquivo CSV

    std::vector<std::vector<std::string>> dados = lerArquivoCSV(nomeArquivo);

    // Exemplo de como imprimir os dados lidos do arquivo CSV
    for (const auto& linha : dados) {
        for (const std::string& elemento : linha) {
            std::cout << elemento << " | ";
        }
        std::cout << "\n";
    }

    return 0;
}
