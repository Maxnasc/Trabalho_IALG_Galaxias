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

// void lerCSV(Galaxia& galaxias[], const string &nomeArquivo)
// {
//     ifstream arquivo(nomeArquivo);

//     if (arquivo.is_open())
//     {
//         string linha;

//         while (getline(arquivo, linha))
//         {
//             Galaxia galaxia;
//             istringstream linhaStream(linha);
//             string campo;

//             // Lê os campos da linha e atribui aos membros da struct
//             if (getline(linhaStream, campo, ','))
//             {
//                 galaxia.nome_galaxia = campo;
//             }
//             if (getline(linhaStream, campo, ','))
//             {
//                 galaxia.tipo_galaxia = campo;
//             }
//             if (getline(linhaStream, campo, ','))
//             {
//                 galaxia.magnitude = stof(campo);
//             }
//             if (getline(linhaStream, campo, ','))
//             {
//                 galaxia.constelacao = campo;
//             }
//             if (getline(linhaStream, campo, ','))
//             {
//                 galaxia.identificador = stoi(campo);
//             }

//             galaxias.push_back(galaxia);
//         }
//         cout << "Arquivo lido com sucesso!" << endl;
//         arquivo.close();
//     }
//     else
//     {
//         cerr << "Erro ao abrir o arquivo." << endl;
//     }

// }

void salvarCSV(Galaxia galaxias[], string nomeArquivo)
{
    std::ofstream arquivo(nomeArquivo);

    if (arquivo.is_open())
    {
        // Escreve o cabeçalho do arquivo CSV (opcional)
        arquivo << "Identificador, Nome da Galáxia, Tipo da Galáxia, Magnitude, Constelação" << std::endl;

        for (int i=0; i<sizeof(galaxias); i++)
        {
            arquivo << galaxias[i].identificador << ","
                    << galaxias[i].nome_galaxia << ","
                    << galaxias[i].tipo_galaxia << ","
                    << galaxias[i].magnitude << ","
                    << galaxias[i].constelacao << std::endl;
        }

        arquivo.close();
        std::cout << "Dados salvos com sucesso em " << nomeArquivo << std::endl;
    }
    else
    {
        std::cerr << "Erro ao criar o arquivo." << std::endl;
    }
}

bool salvar_dados_bin(const vector<Galaxia> &galaxias, const string &nomeArquivoBinario) {
    ofstream arquivo(nomeArquivoBinario, ios::out | ios::binary);

    if (arquivo.is_open()) {
        for (const Galaxia &galaxia : galaxias) {
            // Escreve os dados da galáxia no arquivo binário
            arquivo.write(reinterpret_cast<const char*>(&galaxia), sizeof(Galaxia));
        }

        arquivo.close();
        cout << "Dados salvos com sucesso em " << nomeArquivoBinario << endl;
        return true; // Indica que os dados foram salvos com sucesso
    } else {
        cerr << "Erro ao criar o arquivo binário." << endl;
        return false; // Indica que houve um erro ao salvar os dados
    }
}

// void inserirGalaxia(Galaxia galaxias[])
// {
//     Galaxia novaGalaxia;

//     // Solicita os detalhes da nova galáxia ao usuário
//     cout << "Inserir nova galáxia:" << endl;

//     // Pede o identificador
//     cout << "Identificador: ";
//     cin >> novaGalaxia.identificador;

//     // Pede o nome da galáxia (string com espaços)
//     cin.ignore();  // Limpa
//     cout << "Nome da Galáxia: ";
//     getline(cin, novaGalaxia.nome_galaxia);

//     // Pede o tipo da galáxia (string com espaços)
//     cout << "Tipo da Galáxia: ";
//     getline(cin, novaGalaxia.tipo_galaxia);

//     // Pede a magnitude
//     cout << "Magnitude: ";
//     cin >> novaGalaxia.magnitude;

//     // Pede a constelação (string com espaços)
//     cin.ignore();  // Limpa
//     cout << "Constelação: ";
//     getline(cin, novaGalaxia.constelacao);

//     // Adiciona a nova galáxia ao vetor
//     galaxias.push_back(novaGalaxia);

//     cout << "Nova galáxia adicionada com sucesso!" << endl;
// }

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

void buscarGalaxia(const vector<Galaxia> &galaxias)
{
    int opcaoBusca;

    // Menu para escolher o critério de busca
    cout << "Escolha o critério de busca:" << endl;
    cout << "1 -> Identificador" << endl;
    cout << "2 -> Nome da Galáxia" << endl;
    cout << "3 -> Tipo da Galáxia" << endl;
    cout << "4 -> Magnitude" << endl;
    cout << "5 -> Constelação" << endl;
    cout << "Opção: ";
    cin >> opcaoBusca;

    bool encontrou = false;

    string termoBusca;

    // Limpa o buffer do teclado
    cin.ignore();

    switch (opcaoBusca)
    {
        case 1:
            int identBuscado;

            cout << "Digite o identificador que deseja buscar: ";
            cin >> identBuscado;

            for (const Galaxia &galaxia : galaxias)
            {
                if (galaxia.identificador == identBuscado)
                {
                    // Encontrou uma galáxia com a magnitude especificada
                    cout << "Identificador: " << galaxia.identificador << endl;
                    cout << "Nome da Galáxia: " << galaxia.nome_galaxia << endl;
                    cout << "Tipo da Galáxia: " << galaxia.tipo_galaxia << endl;
                    cout << "Magnitude: " << galaxia.magnitude << endl;
                    cout << "Constelação: " << galaxia.constelacao << endl;
                    encontrou = true;
                }
            }

            if (!encontrou)
            {
                cout << "Nenhum registro encontrado com a magnitude especificada." << endl;
            }
            break;
        
        case 2:
            cout << "Digite o nome da galáxia que deseja buscar: ";
            getline(cin, termoBusca);
            for (const Galaxia &galaxia : galaxias)
            {
                if (galaxia.nome_galaxia.find(termoBusca) != string::npos)
                {
                    // Encontrou uma galáxia com o nome especificado
                    cout << "Identificador: " << galaxia.identificador << endl;
                    cout << "Nome da Galáxia: " << galaxia.nome_galaxia << endl;
                    cout << "Tipo da Galáxia: " << galaxia.tipo_galaxia << endl;
                    cout << "Magnitude: " << galaxia.magnitude << endl;
                    cout << "Constelação: " << galaxia.constelacao << endl;
                    encontrou = true;
                }
            }
            break;

        case 3:
            cout << "Digite o tipo da galáxia que deseja buscar: ";
            getline(cin, termoBusca);
            for (const Galaxia &galaxia : galaxias)
            {
                if (galaxia.tipo_galaxia.find(termoBusca) != string::npos)
                {
                    // Encontrou uma galáxia com o nome especificado
                    cout << "Identificador: " << galaxia.identificador << endl;
                    cout << "Nome da Galáxia: " << galaxia.nome_galaxia << endl;
                    cout << "Tipo da Galáxia: " << galaxia.tipo_galaxia << endl;
                    cout << "Magnitude: " << galaxia.magnitude << endl;
                    cout << "Constelação: " << galaxia.constelacao << endl;
                    encontrou = true;
                }
            }
            break;

        case 4:
            float magnitudeBuscada;

            cout << "Digite a magnitude que deseja buscar: ";
            cin >> magnitudeBuscada;

            for (const Galaxia &galaxia : galaxias)
            {
                if (galaxia.magnitude == magnitudeBuscada)
                {
                    // Encontrou uma galáxia com a magnitude especificada
                    cout << "Identificador: " << galaxia.identificador << endl;
                    cout << "Nome da Galáxia: " << galaxia.nome_galaxia << endl;
                    cout << "Tipo da Galáxia: " << galaxia.tipo_galaxia << endl;
                    cout << "Magnitude: " << galaxia.magnitude << endl;
                    cout << "Constelação: " << galaxia.constelacao << endl;
                    encontrou = true;
                }
            }

            if (!encontrou)
            {
                cout << "Nenhum registro encontrado com a magnitude especificada." << endl;
            }
            break;

        case 5:
            cout << "Digite a constelação da galáxia que deseja buscar: ";
            getline(cin, termoBusca);
            for (const Galaxia &galaxia : galaxias)
            {
                if (galaxia.constelacao.find(termoBusca) != string::npos)
                {
                    // Encontrou uma galáxia com o nome especificado
                    cout << "Identificador: " << galaxia.identificador << endl;
                    cout << "Nome da Galáxia: " << galaxia.nome_galaxia << endl;
                    cout << "Tipo da Galáxia: " << galaxia.tipo_galaxia << endl;
                    cout << "Magnitude: " << galaxia.magnitude << endl;
                    cout << "Constelação: " << galaxia.constelacao << endl;
                    encontrou = true;
                }
            }
            break;

        default:
            cout << "Opção de busca inválida." << endl;
            break;
    }

    if (!encontrou)
    {
        cout << "Nenhum registro encontrado para o critério de busca especificado." << endl;
    }
}

void exibirListaCompleta(const vector<Galaxia> &galaxias) {
    if (galaxias.empty()) {
        cout << "Nenhuma galáxia cadastrada." << endl;
        return;
    }

    cout << "Lista completa de registros:" << endl;
    for (const Galaxia &galaxia : galaxias) {
        cout << "Identificador: " << galaxia.identificador << endl;
        cout << "Nome da Galáxia: " << galaxia.nome_galaxia << endl;
        cout << "Tipo da Galáxia: " << galaxia.tipo_galaxia << endl;
        cout << "Magnitude: " << galaxia.magnitude << endl;
        cout << "Constelação: " << galaxia.constelacao << endl;
        cout << endl;
    }
}

void imprimirIntervalo(Galaxia galaxias[]) {
    
    unsigned inicio, fim;
    cout << "Digite o número do primeiro registro do intervalo: ";
    cin >> inicio;
    cout << "Digite o número do último registro do intervalo: ";
    cin >> fim;
    
    if (inicio < 1 || fim > sizeof(galaxias) || inicio > fim) {
        cout << "Intervalo inválido." << endl;
        return;
    }

    cout << "Registros no intervalo [" << inicio << " - " << fim << "]:" << endl;
    for (unsigned i = inicio - 1; i < fim; i++) {  // Subtrai 1 de 'inicio' para ajustar ao índice base 0
        cout << "Identificador: " << galaxias[i].identificador << endl;
        cout << "Nome da Galáxia: " << galaxias[i].nome_galaxia << endl;
        cout << "Tipo da Galáxia: " << galaxias[i].tipo_galaxia << endl;
        cout << "Magnitude: " << galaxias[i].magnitude << endl;
        cout << "Constelação: " << galaxias[i].constelacao << endl;
        cout << endl;
    }
}

void ordenarDados(Galaxia galaxias[], string nome_arquivo_binario) {

    cout << "Ordenador de dados" << endl;
    cout << "É possível ordenar os dados do catálogo com base no valor de todas as colunas, para selecionar\n a coluna referência para ordenação selecione a opção de acordo com o menu abaixo:" << endl;
    cout << "1 -> Por identificador" << endl;
    cout << "2 -> nome_galaxia" << endl;
    cout << "3 -> tipo_galaxia" << endl;
    cout << "4 -> magnitude" << endl;
    cout << "5 -> constelacao" << endl;
    cout << endl << "Critério de seleção: ";
    int criterio = 0;
    cin >> criterio;
    
    int n = sizeof(galaxias);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            bool trocar = false;

            switch (criterio) {
                case 1:
                    trocar = galaxias[j].identificador > galaxias[j + 1].identificador;
                    break;
                case 2:
                    trocar = galaxias[j].nome_galaxia > galaxias[j + 1].nome_galaxia;
                    break;
                case 3:
                    trocar = galaxias[j].tipo_galaxia > galaxias[j + 1].tipo_galaxia;
                    break;
                case 4:
                    trocar = galaxias[j].magnitude > galaxias[j + 1].magnitude;
                    break;
                case 5:
                    trocar = galaxias[j].constelacao > galaxias[j + 1].constelacao;
                    break;
                default:
                    cerr << "Critério de seleção inválido." << std::endl;
                    return;
            }

            if (trocar) {
                swap(galaxias[j], galaxias[j + 1]);
            }
        }
    }

    // salvar_dados_bin(galaxias, nome_arquivo_binario);

}

void salvar_dados_bin(vector<Galaxia>& galaxias) {
    // Implementarlear
}

void carregar_dados_bin(vector<Galaxia>& galaxias) {
    std::ofstream arquivo(nomeArquivo, std::ios::binary);

    if (arquivo.is_open()) {
        for (const Galaxia &galaxia : galaxias) {
            // Escreve cada objeto Galaxia no arquivo binário
            arquivo.write(reinterpret_cast<const char*>(&galaxia), sizeof(Galaxia));
        }

        arquivo.close();
        std::cout << "Dados salvos com sucesso em " << nomeArquivo << " (formato binário)." << std::endl;
    } else {
        std::cerr << "Erro ao criar o arquivo binário." << std::endl;
    }
}

void menu(string nomeArquivoCSVimport, string nomeArquivoCSVexport)
{

    // Bloco de indicação de quais as funções disponíveis para o usuário
    cout << "Bem vindo ao sistema de gerenciamento de informações galácticas!" << endl;
    int escolha = 100;
    bool saved = false;
    Galaxia galaxias[100];

    //Dados dos arquivos binários
    string nome_arquivo_binario = "";

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
        cout << "9 -> Salvar alterações" << endl;
        cout << "0  -> Sair do programa" << endl;
        cout << endl << "====================================================================" << endl;
        cout << endl << "Opção: ";
        cin >> escolha;
        cout << endl;
        
        switch (escolha)
        {
        case 1: // Importar dados de arquivo .csv
            // lerCSV(galaxias, nomeArquivoCSVimport); // retorna os dados para o vetor de galáxias > verificar se nenhum dado é perdido
            break;
        case 2: // Exportar dados para arquivo .csv
            salvarCSV(galaxias, nomeArquivoCSVexport);
            break;
        case 3: // Ordenar dados de acordo com característica especificada
            cout << "em desenvolvimento" << endl;   
            ordenarDados(galaxias, nome_arquivo_binario);
            break;
        // case 4: // Inserir registro
        //     inserirGalaxia(galaxias);
        //     break;
        // case 5: // Apagar registro
        //     removerGalaxia(galaxias);
        //     break;
        // case 6: // Buscar registro
        //     buscarGalaxia(galaxias);
        //     break;
        // case 7: // Exibir lista completa de registros
        //     exibirListaCompleta(galaxias);
        //     break;
        // case 8: // Exibir lista parcial de registros
        //     imprimirIntervalo(galaxias);
        //     break;
        // case 9: // Salvar alterações
        //     saved = salvar_dados_bin(galaxias, nome_arquivo_binario);
            break;
        case 0: // Sair do programa
            if (saved != true) {
                // chama função de salvar em arquivo binário
            }
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
    string nome_arquivo_binario = "dados_binarios.dat";
    //int tamanhoCSV; // Verificador de galáxias cadastradas em arquivos .csv

    // Verificar tamanho do arquivo .csv
    // tamanhoCSV = verificarTamanhoArquivoCSV(nomeArquivoCSVimport);
    // cout << tamanhoCSV << endl;

    // Struct de dados
    menu(nomeArquivoCSVimport, nomeArquivoCSVexport);
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
