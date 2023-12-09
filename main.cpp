#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Constantes
const int MAX_GALAXIAS = 10;

// Declaração de struct para armazenar os dados das galáxias
struct Galaxia
{
    int identificador = 0;
    string nome_galaxia = "";
    string tipo_galaxia = "";
    float magnitude = 0.0;
    string constelacao = "";

    void registra_vazio()
    {
        this->identificador = 99999;
        this->nome_galaxia = "vazio";
        this->tipo_galaxia = "vazio";
        this->magnitude = 0.0;
        this->constelacao = "vazio";
    }
};

// Função que verifica o tamanho do arquivo CSV
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
        cerr << endl << " Erro ao abrir o arquivo." << endl;
        return -1; // Retorna -1 em caso de erro
    }
}

// Função que redimensiona o vetor dinamicamente
vector<Galaxia> redimensionar_vetor(const vector<Galaxia> &vetor)
{
    vector<Galaxia> novoVetor(vetor.begin(), vetor.end());
    novoVetor.resize(novoVetor.size() + MAX_GALAXIAS);
    for (int i = vetor.size(); i < novoVetor.size(); i++)
    {
        novoVetor[i].registra_vazio();
    }

    return novoVetor;
}

// Função que lê o arquivo CSV e armazena os dados em um vetor de galáxias
void lerCSV(vector<Galaxia> &galaxias, const string &nomeArquivo)
{
    ifstream arquivo(nomeArquivo);

    if (arquivo.is_open())
    {
        string linha;

        while (getline(arquivo, linha))
        {
            Galaxia galaxia;
            istringstream linhaStream(linha);
            string campo;

            if (getline(linhaStream, campo, ','))
            {
                galaxia.identificador = stoi(campo);
            }
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

            galaxias.push_back(galaxia);
        }
        cout << endl <<" Arquivo lido com sucesso!" << endl;
        arquivo.close();
    }
    else
    {
        cerr << endl <<" Erro ao abrir o arquivo." << endl;
    }
}

// Função que salva os dados do vetor de galáxias em um arquivo CSV
void salvarCSV(const vector<Galaxia> &galaxias, const string &nomeArquivo)
{
    ofstream arquivo(nomeArquivo);

    if (arquivo.is_open())
    {
        for (const auto &galaxia : galaxias)
        {
            arquivo << galaxia.identificador << ","
                    << galaxia.nome_galaxia << ","
                    << galaxia.tipo_galaxia << ","
                    << galaxia.magnitude << ","
                    << galaxia.constelacao << endl;
        }

        arquivo.close();
        cout << endl << " Dados salvos com sucesso! " << endl;
    }
    else
    {
        cerr << endl << " Erro ao criar o arquivo." << endl;
    }
}

// Função que salva os dados do vetor de galáxias em um arquivo binário
bool salvar_dados_bin(const vector<Galaxia> &galaxias, const string &nomeArquivoBinario)
{
    ofstream arquivo(nomeArquivoBinario, ios::out | ios::binary);

    if (arquivo.is_open())
    {
        for (const auto &galaxia : galaxias)
        {
            arquivo.write(reinterpret_cast<const char *>(&galaxia), sizeof(Galaxia));
        }

        arquivo.close();
        cout << endl <<" Dados salvos com sucesso!" << endl;
        return true;
    }
    else
    {
        cerr << endl <<" Erro ao criar o arquivo binário." << endl;
        return false;
    }
}

// Função que insere uma nova galáxia no vetor de galáxias
void inserirGalaxia(vector<Galaxia> &galaxias)
{
    Galaxia novaGalaxia;
    cout << "Inserir nova galáxia:" << endl;

    cout << "Identificador: ";
    cin >> novaGalaxia.identificador;

    cin.ignore(); // Limpa
    cout << "Nome da Galáxia: ";
    getline(cin, novaGalaxia.nome_galaxia);

    cout << "Tipo da Galáxia: ";
    getline(cin, novaGalaxia.tipo_galaxia);

    cout << "Magnitude: ";
    cin >> novaGalaxia.magnitude;

    cin.ignore(); // Limpa
    cout << "Constelação: ";
    getline(cin, novaGalaxia.constelacao);

    for (auto &galaxia : galaxias)
    {
        if (galaxia.identificador == novaGalaxia.identificador)
        {
            cerr << endl << " Identificador já existente. A operação foi cancelada." << endl;
            return;
        }
    }

    galaxias.push_back(novaGalaxia);
    cout << endl << " Galáxia inserida com sucesso!" << endl;
}

// Declaração da função particiona
int particiona(vector<Galaxia> &vetor, int inicio, int fim, bool ascendente);


// Função que ordena o vetor de galáxias pelo identificador usando o algoritmo quicksort
void quickSort(vector<Galaxia> &vetor, int inicio, int fim, bool ascendente)
{
    if (inicio < fim)
    {
        int p = particiona(vetor, inicio, fim, ascendente);

        quickSort(vetor, inicio, p - 1, ascendente);
        quickSort(vetor, p + 1, fim, ascendente);
    }
}

// Função auxiliar para o quicksort que particiona o vetor
int particiona(vector<Galaxia> &vetor, int inicio, int fim, bool ascendente)
{
    Galaxia pivo = vetor[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        if ((ascendente && vetor[j].identificador < pivo.identificador) ||
            (!ascendente && vetor[j].identificador > pivo.identificador))
        {
            i++;
            swap(vetor[i], vetor[j]);
        }
    }

    swap(vetor[i + 1], vetor[fim]);

    return i + 1;
}

// Função para listar as galáxias
void listarGalaxias(const vector<Galaxia> &galaxias)
{
    cout << "---- Lista de Galáxias ----" << endl;
    for (const auto &galaxia : galaxias)
    {
        cout << "Identificador: " << galaxia.identificador << endl;
        cout << "Nome: " << galaxia.nome_galaxia << endl;
        cout << "Tipo: " << galaxia.tipo_galaxia << endl;
        cout << "Magnitude: " << galaxia.magnitude << endl;
        cout << "Constelação: " << galaxia.constelacao << endl;
        cout << "--------------------------" << endl;
    }
}

// Função para ordenar as galáxias pelo identificador
void ordenarGalaxias(vector<Galaxia> &galaxias)
{
    bool ascendente;
    cout << "Ordenar em ordem ascendente? (1 para Sim, 0 para Não): ";
    cin >> ascendente;

    quickSort(galaxias, 0, galaxias.size() - 1, ascendente);
    cout << "Galáxias ordenadas com sucesso!" << endl;
}

// Função para salvar os dados em um arquivo CSV
void salvar_dados(const vector<Galaxia> &galaxias, const string &nomeArquivoCSV)
{
    ofstream arquivo(nomeArquivoCSV);

    if (arquivo.is_open())
    {
        for (const auto &galaxia : galaxias)
        {
            arquivo << galaxia.identificador << ","
                    << galaxia.nome_galaxia << ","
                    << galaxia.tipo_galaxia << ","
                    << galaxia.magnitude << ","
                    << galaxia.constelacao << endl;
        }

        arquivo.close();
        cout << "Dados salvos com sucesso!" << endl;
    }
    else
    {
        cerr << "Erro ao criar o arquivo." << endl;
    }
}


// Função que exibe o menu principal
int exibirMenu()
{
    int escolha;
    cout << endl;
    cout << "---- Menu Principal ----" << endl;
    cout << "1. Listar Galáxias" << endl;
    cout << "2. Inserir Nova Galáxia" << endl;
    cout << "3. Ordenar Galáxias" << endl;
    cout << "4. Salvar Dados" << endl;
    cout << "5. Sair" << endl;
    cout << "Escolha uma opção: ";
    cin >> escolha;
    return escolha;
}

// Função principal
int main()
{
    vector<Galaxia> galaxias;

    string nomeArquivoCSV = "galaxias.csv";
    string nomeArquivoBinario = "dados_binarios.dat";

    // Ler dados do arquivo CSV
    lerCSV(galaxias, nomeArquivoCSV);

    int opcao;
    bool alteracoesPendentes = false;

    do
    {
        opcao = exibirMenu();

        switch (opcao)
        {
        case 1:
            // Listar Galáxias
            listarGalaxias(galaxias);
            break;

        case 2:
            // Inserir Nova Galáxia
            inserirGalaxia(galaxias);
            alteracoesPendentes = true;
            break;

        case 3:
            // Ordenar Galáxias
            ordenarGalaxias(galaxias);
            alteracoesPendentes = true;
            break;

        case 4:
            // Salvar Dados
            salvar_dados(galaxias, nomeArquivoCSV);
            salvar_dados_bin(galaxias, nomeArquivoBinario);
            alteracoesPendentes = false;
            break;

        case 5:
            // Sair
            if (alteracoesPendentes)
            {
                cout << "Deseja salvar as alterações antes de sair? (S para Sim, N para Não): ";
                char resposta;
                cin >> resposta;

                if (resposta == 'S' || resposta == 's')
                {
                    salvar_dados(galaxias, nomeArquivoCSV);
                    salvar_dados_bin(galaxias, nomeArquivoBinario);
                }
            }
            cout << "Saindo..." << endl;
            break;

        default:
            cout << "Opção inválida. Tente novamente." << endl;
            break;
        }

    } while (opcao != 5);

    return 0;
}
