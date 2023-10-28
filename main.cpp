/*Trabalho prático
Introdução a algoritmos
2023-2

Feito por:
Cleber
Marcos Tadeu Xavier Ferreira - 201910448
Max Deivid do Nascimento - 201910445
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

struct Galaxia
{
    // 1. Identificador no catálogo (int)
    // 2. Nome da galáxia (string com espaços)
    // 3. Tipo da galáxia (string com espaços)
    // 4. Magnitude (float)
    // 5. Constelação (string com espaços)
    int identificador = 0;
    string nome_galaxia = "";
    string tipo_galaxia = "";
    float magnitude = 0.0;
    string constelacao = "";
};

int verificarTamanhoArquivoCSV(const string& nomeArquivo) {
    ifstream arquivo(nomeArquivo);
    int numeroDeLinhas = 0;

    if (arquivo.is_open()) {
        string linha;

        while (getline(arquivo, linha)) {
            numeroDeLinhas++;
        }

        arquivo.close();

        return numeroDeLinhas;
    } else {
        cerr << "Erro ao abrir o arquivo." << endl;
        return -1; // Retorna -1 em caso de erro
    }
}

vector<Galaxia> lerCSV(const string& nomeArquivo) {
    vector<Galaxia> galaxias;
    ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        string linha;

        while (getline(arquivo, linha)) {
            Galaxia galaxia;
            istringstream linhaStream(linha);
            string campo;

            // Lê os campos da linha e atribui aos membros da struct
            if (getline(linhaStream, campo, ',')) {
                galaxia.identificador = stoi(campo);
            }
            if (getline(linhaStream, campo, ',')) {
                galaxia.nome_galaxia = campo;
            }
            if (getline(linhaStream, campo, ',')) {
                galaxia.tipo_galaxia = campo;
            }
            if (getline(linhaStream, campo, ',')) {
                galaxia.magnitude = stof(campo);
            }
            if (getline(linhaStream, campo, ',')) {
                galaxia.constelacao = campo;
            }

            galaxias.push_back(galaxia);
        }

        arquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo." << endl;
    }

    return galaxias;
}

int main () {
    string nomeArquivoCSV = "/home/maxnas7/Documentos/IALG/trabalho/Trabalho_IALG_Galaxias/galaxys.csv";
    int tamanhoCSV;
    // Ler o arquivo .csv
    tamanhoCSV = verificarTamanhoArquivoCSV(nomeArquivoCSV);
    Galaxia galaxias[tamanhoCSV];

    galaxias = lerCSV;

    cout << tamanhoCSV << endl;
    // ler_csv (); //Importar dados
    // escreve_csv (); //Exportar dados

    return 0;
}