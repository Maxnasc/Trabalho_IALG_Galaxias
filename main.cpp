/*Trabalho prático
Introdução a algoritmos
2023-2

Feito por:
Cleber Henrique Silva Junior - 201910660
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

int verificarTamanhoArquivoCSV(const string &nomeArquivo)
{
    ifstream arquivo(nomeArquivo);
    int numeroDeLinhas = 0;

    if (arquivo.is_open())
    {
        string linha;

        while (getline(arquivo, linha))
        {
            numeroDeLinhas++;
        }

        arquivo.close();

        return numeroDeLinhas;
    }
    else
    {
        cerr << "Erro ao abrir o arquivo." << endl;
        return -1; // Retorna -1 em caso de erro
    }
}

vector<Galaxia> lerCSV(const string &nomeArquivo)
{
    vector<Galaxia> galaxias;
    ifstream arquivo(nomeArquivo);

    if (arquivo.is_open())
    {
        string linha;

        while (getline(arquivo, linha))
        {
            Galaxia galaxia;
            istringstream linhaStream(linha);
            string campo;

            // Lê os campos da linha e atribui aos membros da struct
            if (getline(linhaStream, campo, ','))
            {
                galaxia.nome_galaxia = campo;
            }
            if (getline(linhaStream, campo, ','))
            {
                galaxia.tipo_galaxia = campo;
            }
            if (getline(linhaStream, campo, ','))
            {
                galaxia.magnitude = stof(campo);
            }
            if (getline(linhaStream, campo, ','))
            {
                galaxia.constelacao = campo;
            }
            if (getline(linhaStream, campo, ','))
            {
                galaxia.identificador = stoi(campo);
            }

            galaxias.push_back(galaxia);
        }
        cout << "Arquivo lido com sucesso!" << endl;
        arquivo.close();
    }
    else
    {
        cerr << "Erro ao abrir o arquivo." << endl;
    }

    return galaxias;
}

void salvarCSV(vector<Galaxia> galaxias, string nomeArquivo)
{
    std::ofstream arquivo(nomeArquivo);

    if (arquivo.is_open())
    {
        // Escreve o cabeçalho do arquivo CSV (opcional)
        arquivo << "Identificador, Nome da Galáxia, Tipo da Galáxia, Magnitude, Constelação" << std::endl;

        for (const Galaxia &galaxia : galaxias)
        {
            arquivo << galaxia.identificador << ","
                    << galaxia.nome_galaxia << ","
                    << galaxia.tipo_galaxia << ","
                    << galaxia.magnitude << ","
                    << galaxia.constelacao << std::endl;
        }

        arquivo.close();
        std::cout << "Dados salvos com sucesso em " << nomeArquivo << std::endl;
    }
    else
    {
        std::cerr << "Erro ao criar o arquivo." << std::endl;
    }
}

void inserirGalaxia(vector<Galaxia> &galaxias)
{
    Galaxia novaGalaxia;

    // Solicita os detalhes da nova galáxia ao usuário
    cout << "Inserir nova galáxia:" << endl;

    // Pede o identificador
    cout << "Identificador: ";
    cin >> novaGalaxia.identificador;

    // Pede o nome da galáxia (string com espaços)
    cin.ignore();  // Limpa
    cout << "Nome da Galáxia: ";
    getline(cin, novaGalaxia.nome_galaxia);

    // Pede o tipo da galáxia (string com espaços)
    cout << "Tipo da Galáxia: ";
    getline(cin, novaGalaxia.tipo_galaxia);

    // Pede a magnitude
    cout << "Magnitude: ";
    cin >> novaGalaxia.magnitude;

    // Pede a constelação (string com espaços)
    cin.ignore();  // Limpa
    cout << "Constelação: ";
    getline(cin, novaGalaxia.constelacao);

    // Adiciona a nova galáxia ao vetor
    galaxias.push_back(novaGalaxia);

    cout << "Nova galáxia adicionada com sucesso!" << endl;
}

void removerGalaxia(vector<Galaxia> &galaxias)
{
    int identificadorParaRemover;
    
    // Solicita o identificador da galáxia a ser removida
    cout << "Digite o identificador da galáxia que deseja remover: ";
    cin >> identificadorParaRemover;
    
    // Procura a galáxia no vetor pelo identificador
    for (auto it = galaxias.begin(); it != galaxias.end(); ++it)
    {
        if (it->identificador == identificadorParaRemover)
        {
            // Remove efetivamente a galáxia do vetor
            galaxias.erase(it);
            cout << "Galáxia removida com sucesso!" << endl;
            return;  // Sai da função após a remoção
        }
    }
    
    // Se o identificador não for encontrado
    cout << "Galáxia com identificador " << identificadorParaRemover << " não encontrada." << endl;
}


void menu(vector<Galaxia> galaxias, string nomeArquivoCSVimport, string nomeArquivoCSVexport)
{

    // Bloco de indicação de quais as funções disponíveis para o usuário
    cout << "Bem vindo ao sistema de gerenciamento de informações galácticas!" << endl;
    int escolha = 100;

    while (escolha != 0)
    {
        cout << endl << "====================================================================" << endl;
        cout << "Escolha uma das opções:" << endl;
        cout << "1  -> Importar dados de arquivo .csv" << endl;
        cout << "2  -> Exportar dados para arquivo .csv" << endl;
        cout << "3  -> Ordenar dados de acordo com característica especificada" << endl;
        cout << "4  -> Inserir registro" << endl;
        cout << "5  -> Apagar registro" << endl;
        cout << "6  -> Buscar registro" << endl;
        cout << "7  -> Exibir lista completa de registros" << endl;
        cout << "8  -> Exibir lista parcial de registros" << endl;
        cout << "9  -> Exibir modificação atual" << endl;
        cout << "10 -> Salvar alterações" << endl;
        cout << "0  -> Sair do programa" << endl;
        cout << endl << "====================================================================" << endl;
        cout << endl << "Opção: ";
        cin >> escolha;
        cout << endl;
        switch (escolha)
        {
        case 1: // Importar dados de arquivo .csv
            galaxias = lerCSV(nomeArquivoCSVimport);
            break;
        case 2: // Exportar dados para arquivo .csv
            salvarCSV(galaxias, nomeArquivoCSVexport);
            break;
        case 3: // Ordenar dados de acordo com característica especificada
            cout << "Não implementado" << endl;
            break;
        case 4: // Inserir registro
            inserirGalaxia(galaxias);
            break;
        case 5: // Apagar registro
            removerGalaxia(galaxias);
            break;
        case 6: // Buscar registro
            cout << "Não implementado" << endl;
            break;
        case 7: // Exibir lista completa de registros
            cout << "Não implementado" << endl;
            break;
        case 8: // Exibir lista parcial de registros
            cout << "Não implementado" << endl;
            break;
        case 9: // Exibir lista parcial de registros
            cout << "Não implementado" << endl;
            break;
        case 10: // Salvar alterações
            cout << "Não implementado" << endl;
            break;
        case 0: // Exibir lista parcial de registros
            cout << endl << "Obrigado! :)" << endl;
            break;
        default:
            cout << "Opção não disponível" << endl;
            break;
        }
    }
}


int main()
{
    // Declaração de nomes de arquivos de import e export de .csv
    string nomeArquivoCSVimport = "C:/Users/clebe/OneDrive/Documentos/UFLA_Periodo_10/IALG/Trabalho_IALG_Galaxias/galaxys_import.csv";
    string nomeArquivoCSVexport = "C:/Users/clebe/OneDrive/Documentos/UFLA_Periodo_10/IALG/Trabalho_IALG_Galaxias/galaxys_export.csv";
    //int tamanhoCSV; // Verificador de galáxias cadastradas em arquivos .csv

    // Verificar tamanho do arquivo .csv
    // tamanhoCSV = verificarTamanhoArquivoCSV(nomeArquivoCSVimport);
    // cout << tamanhoCSV << endl;

    // Struct de dados
    vector<Galaxia> galaxias;
    menu(galaxias, nomeArquivoCSVimport, nomeArquivoCSVexport);
    // for (const Galaxia& galaxia : galaxias) {
    //     cout << "Identificador: " << galaxia.identificador << endl;
    //     cout << "Nome da Galáxia: " << galaxia.nome_galaxia << endl;
    //     cout << "Tipo da Galáxia: " << galaxia.tipo_galaxia << endl;
    //     cout << "Magnitude: " << galaxia.magnitude << endl;
    //     cout << "Constelação: " << galaxia.constelacao << endl;
    //     cout << endl;
    // }

    return 0;
}
