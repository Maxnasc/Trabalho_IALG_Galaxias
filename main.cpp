/*Trabalho prático
Introdução a algoritmos
Período 2023-2

--> GRUPO 15
Integrantes:
    Cleber Henrique Silva Junior - 201910660
    Marcos Tadeu Xavier Ferreira - 201910448
    Max Deivid do Nascimento - 201910445

Tema: Catálogo de galáxias
Campos: 1. Identificador no catálogo (int)
        2. Nome da galáxia (string com espaços)
        3. Tipo da galáxia (string com espaços)
        4. Magnitude (float)
        5. Constelação (string com espaços)

Este trabalho se tarata da criação de um sistema de catálogo de galáxias para astrônomos slavarem as informações
a respeito de qual constelação a galáxia pertence, seu tipo, magnitude e nome. O sistema deve ser capaz de ler e 
escrever no arquivo do catálogo, faser buscas, ordenar os dados e salvar as alterações feitas no arquivo.
*/

// Bibliotecas utilizadas
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>

// Declaração de namespace
using namespace std;

// Declaração de struct para armazenar os dados das galáxias
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

// Função que lê o arquivo CSV e armazena os dados em um vetor de galáxias
void lerCSV(Galaxia galaxias[], const string &nomeArquivo)
{
    ifstream arquivo(nomeArquivo);
    int index = 0;

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

            galaxias[index]=galaxia;
            index++;

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
void salvarCSV(Galaxia galaxias[], string nomeArquivo, int tamanhoArquivo)
{
    ofstream arquivo(nomeArquivo);

    if (arquivo.is_open())
    {
        // Escreve o cabeçalho do arquivo CSV (opcional)
        arquivo << "Identificador, Nome da Galáxia, Tipo da Galáxia, Magnitude, Constelação" << endl;

        for (int i=0; i<tamanhoArquivo; i++)
        {
            arquivo << galaxias[i].identificador << ","
                    << galaxias[i].nome_galaxia << ","
                    << galaxias[i].tipo_galaxia << ","
                    << galaxias[i].magnitude << ","
                    << galaxias[i].constelacao << endl;
        }

        arquivo.close();
        cout << endl << " Dados salvos com sucesso em " << nomeArquivo << endl;
    }
    else
    {
        cerr << endl << " Erro ao criar o arquivo." << endl;
    }
}

// Função que salva os dados do vetor de galáxias em um arquivo binário
bool salvar_dados_bin(Galaxia galaxias[], const string &nomeArquivoBinario, int tamanhoArquivo) {
    ofstream arquivo(nomeArquivoBinario, ios::out | ios::binary);

    if (arquivo.is_open()) {
        for (int i=0; i<tamanhoArquivo; i++) {
            // Escreve os dados da galáxia no arquivo binário
            arquivo.write(reinterpret_cast<const char*>(&galaxias[i]), sizeof(Galaxia));
        }

        arquivo.close();
        cout << endl <<" Dados salvos com sucesso em " << nomeArquivoBinario << endl;
        return true; // Indica que os dados foram salvos com sucesso
    } else {
        cerr << endl <<" Erro ao criar o arquivo binário." << endl;
        return false; // Indica que houve um erro ao salvar os dados
    }
}

// Função que insere uma nova galáxia no vetor de galáxias
void inserirGalaxia(Galaxia galaxias[], int tamanhoArquivo)
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

    // Busca por espaços vazios ou registros marcados para remoção
    for (int i = 0; i < tamanhoArquivo; i++) {
        if (galaxias[i].nome_galaxia == "vazio" || galaxias[i].identificador == -1) {
            galaxias[i] = novaGalaxia;
            cout << endl << " Nova galáxia adicionada com sucesso!" << endl;
            return;
        }
    }
    cout << endl << " Não há mais espaço para adicionar galáxias" << endl;
    
}


// Função que remove uma galáxia do arquivo binário
void removerGalaxia(const string &nomeArquivoBinario)
{
    int identificadorParaRemover;

    // Solicita o identificador da galáxia a ser removida
    cout << endl <<" Digite o identificador da galáxia que deseja remover: ";
    cin >> identificadorParaRemover;

    // Abre o arquivo binário em modo de leitura e escrita
    fstream arquivoBinario(nomeArquivoBinario, ios::binary | ios::in | ios::out);

    if (!arquivoBinario)
    {
        cerr << endl <<" Erro ao abrir o arquivo binário." << endl;
        return;
    }

    // Procura a galáxia no arquivo pelo identificador
    Galaxia galaxia;
    while (arquivoBinario.read(reinterpret_cast<char*>(&galaxia), sizeof(Galaxia)))
    {
        if (galaxia.identificador == identificadorParaRemover)
        {
            // Marca a galáxia como removida no arquivo
            galaxia.identificador = -1;  // Usando -1 como marcação de remoção lógica
            arquivoBinario.seekp(-static_cast<int>(sizeof(Galaxia)), ios::cur);  // Volta para a posição antes da leitura
            arquivoBinario.write(reinterpret_cast<char*>(&galaxia), sizeof(Galaxia));  // Escreve a galáxia modificada
            cout << endl <<" Galáxia removida com sucesso!" << endl;
            arquivoBinario.close();
            return;  // Sai da função após a remoção
        }
    }

    // Se o identificador não for encontrado
    cout << endl <<" Galáxia com identificador " << identificadorParaRemover << " não encontrada." << endl;

    arquivoBinario.close();
}


// Função que busca uma galáxia no vetor de galáxias
void buscarGalaxia(Galaxia galaxias[], int tamanhoArquivo)
{
    int opcaoBusca;

    // Menu para escolher o critério de busca
    cout << " Escolha o critério de busca:" << endl;
    cout << " 1 -> Identificador" << endl;
    cout << " 2 -> Nome da Galáxia" << endl;
    cout << " 3 -> Tipo da Galáxia" << endl;
    cout << " 4 -> Magnitude" << endl;
    cout << " 5 -> Constelação" << endl;
    cout << " Opção: ";
    cin >> opcaoBusca;

    bool encontrou = false;

    string termoBusca;

    // Limpa o buffer do teclado
    cin.ignore();

    switch (opcaoBusca)
    {
        case 1:
            int identBuscado;

            cout << " Digite o identificador que deseja buscar: ";
            cin >> identBuscado;

            for (int i=0; i<tamanhoArquivo; i++)
            {
                if (galaxias[i].identificador == identBuscado)
                {
                    // Encontrou uma galáxia com a magnitude especificada
                    cout << " Identificador: " << galaxias[i].identificador << endl;
                    cout << " Nome da Galáxia: " << galaxias[i].nome_galaxia << endl;
                    cout << " Tipo da Galáxia: " << galaxias[i].tipo_galaxia << endl;
                    cout << " Magnitude: " << galaxias[i].magnitude << endl;
                    cout << " Constelação: " << galaxias[i].constelacao << endl;
                    encontrou = true;
                }
            }

            if (!encontrou)
            {
                cout << endl <<" Nenhum registro encontrado com a magnitude especificada." << endl;
            }
            break;
        
        case 2:
            cout << endl << " Digite o nome da galáxia que deseja buscar: ";
            getline(cin, termoBusca);
            for (int i=0; i<tamanhoArquivo; i++)
            {
                if (galaxias[i].nome_galaxia == termoBusca)
                {
                    // Encontrou uma galáxia com a magnitude especificada
                    cout << " Identificador: " << galaxias[i].identificador << endl;
                    cout << " Nome da Galáxia: " << galaxias[i].nome_galaxia << endl;
                    cout << " Tipo da Galáxia: " << galaxias[i].tipo_galaxia << endl;
                    cout << " Magnitude: " << galaxias[i].magnitude << endl;
                    cout << " Constelação: " << galaxias[i].constelacao << endl;
                    encontrou = true;
                }
            }
            break;

        case 3:
            cout << endl << " Digite o tipo da galáxia que deseja buscar: ";
            getline(cin, termoBusca);
            
            for (int i=0; i<tamanhoArquivo; i++)
            {
                if (galaxias[i].tipo_galaxia == termoBusca)
                {
                    // Encontrou uma galáxia com a magnitude especificada
                    cout << " Identificador: " << galaxias[i].identificador << endl;
                    cout << " Nome da Galáxia: " << galaxias[i].nome_galaxia << endl;
                    cout << " Tipo da Galáxia: " << galaxias[i].tipo_galaxia << endl;
                    cout << " Magnitude: " << galaxias[i].magnitude << endl;
                    cout << " Constelação: " << galaxias[i].constelacao << endl;
                    encontrou = true;
                }
            }
            break;

        case 4:
            float magnitudeBuscada;

            cout << endl << " Digite a magnitude que deseja buscar: ";
            cin >> magnitudeBuscada;

            for (int i=0; i<tamanhoArquivo; i++)
            {
                if (galaxias[i].magnitude == magnitudeBuscada)
                {
                    // Encontrou uma galáxia com a magnitude especificada
                    cout << " Identificador: " << galaxias[i].identificador << endl;
                    cout << " Nome da Galáxia: " << galaxias[i].nome_galaxia << endl;
                    cout << " Tipo da Galáxia: " << galaxias[i].tipo_galaxia << endl;
                    cout << " Magnitude: " << galaxias[i].magnitude << endl;
                    cout << " Constelação: " << galaxias[i].constelacao << endl;
                    encontrou = true;
                }
            }

            if (!encontrou)
            {
                cout << endl << " Nenhum registro encontrado com a magnitude especificada." << endl;
            }
            break;

        case 5:
            cout << endl << " Digite a constelação da galáxia que deseja buscar: ";
            getline(cin, termoBusca);
            for (int i=0; i<tamanhoArquivo; i++)
            {
                if (galaxias[i].constelacao == termoBusca)
                {
                    // Encontrou uma galáxia com a magnitude especificada
                    cout << " Identificador: " << galaxias[i].identificador << endl;
                    cout << " Nome da Galáxia: " << galaxias[i].nome_galaxia << endl;
                    cout << " Tipo da Galáxia: " << galaxias[i].tipo_galaxia << endl;
                    cout << " Magnitude: " << galaxias[i].magnitude << endl;
                    cout << " Constelação: " << galaxias[i].constelacao << endl;
                    encontrou = true;
                }
            }
            break;

        default:
            cout << endl << " Opção de busca inválida." << endl;
            break;
    }

    if (!encontrou)
    {
        cout << endl << " Nenhum registro encontrado para o critério de busca especificado." << endl;
    }
}

// Função que exibe a lista completa de galáxias
void exibirListaCompleta(Galaxia galaxias[], int tamanhoArquivo) {
    if ((galaxias[0].nome_galaxia == "vazio")&&(galaxias[90].nome_galaxia == "vazio")&&(galaxias[45].nome_galaxia == "vazio")) {
        cout << endl << " Nenhuma galáxia cadastrada." << endl;
        return;
    }

    cout << "Lista completa de registros:" << endl;
    for (int i=0; i<tamanhoArquivo; i++) {
        if (galaxias[i].identificador != 99999){
            cout << " Identificador: " << galaxias[i].identificador << endl;
            cout << " Nome da Galáxia: " << galaxias[i].nome_galaxia << endl;
            cout << " Tipo da Galáxia: " << galaxias[i].tipo_galaxia << endl;
            cout << " Magnitude: " << galaxias[i].magnitude << endl;
            cout << " Constelação: " << galaxias[i].constelacao << endl;
            cout << endl;
        }
    }
}

// Função que exibe uma lista parcial de galáxias
void imprimirIntervalo(Galaxia galaxias[], int tamanhoArquivo) {
    
    int inicio, fim;
    cout << endl << " Digite o número do primeiro registro do intervalo: ";
    cin >> inicio;
    cout << endl << " Digite o número do último registro do intervalo: ";
    cin >> fim;
    
    if (inicio < 1 || fim > tamanhoArquivo || inicio > fim) {
        cout << endl <<" Intervalo inválido." << endl;
        return;
    }

    cout << "Registros no intervalo [" << inicio << " - " << fim << "]:" << endl;
    for (int i = inicio - 1; i < fim; i++) {  // Subtrai 1 de 'inicio' para ajustar ao índice base 0
        cout << " Identificador: " << galaxias[i].identificador << endl;
        cout << " Nome da Galáxia: " << galaxias[i].nome_galaxia << endl;
        cout << " Tipo da Galáxia: " << galaxias[i].tipo_galaxia << endl;
        cout << " Magnitude: " << galaxias[i].magnitude << endl;
        cout << " Constelação: " << galaxias[i].constelacao << endl;
        cout << endl;
    }
}

// Função que verifica se uma galáxia foi marcada para remoção lógica
bool marcadoParaRemover(const Galaxia& galaxia)
{
    return galaxia.identificador < 0;
}

// Função auxiliar para particionar o vetor para o QuickSort
int particionar(Galaxia galaxias[], int baixo, int alto, int criterio) {
    Galaxia pivo = galaxias[alto];
    int i = baixo - 1;

    for (int j = baixo; j <= alto - 1; j++) {
        bool trocar = false;

        // Verifica se as galáxias estão marcadas para remoção lógica
        bool marcadoParaRemoverJ = marcadoParaRemover(galaxias[j]);

        switch (criterio) {
            case 1:
                trocar = (!marcadoParaRemoverJ && galaxias[j].identificador <= pivo.identificador);
                break;
            case 4:
                trocar = (!marcadoParaRemoverJ && galaxias[j].magnitude <= pivo.magnitude);
                break;
            default:
                cerr << " Critério de seleção inválido." << endl;
                return 0;
        }

        if (trocar) {
            i++;
            swap(galaxias[i], galaxias[j]);
        }
    }

    swap(galaxias[i + 1], galaxias[alto]);
    return i + 1;
}

// Função principal do QuickSort
void quickSort(Galaxia galaxias[], int baixo, int alto, int criterio) {
    if (baixo < alto) {
        int pi = particionar(galaxias, baixo, alto, criterio);

        quickSort(galaxias, baixo, pi - 1, criterio);
        quickSort(galaxias, pi + 1, alto, criterio);
    }
}

// Função que ordena os dados do vetor de galáxias utilizando o método QuickSort
void ordenarDados(Galaxia galaxias[], int tamanhoArquivo) {
    cout << " Ordenador de dados" << endl;
    cout << " É possível ordenar os dados do catálogo com base no valor de todas as colunas, para selecionar\n a coluna referência para ordenação selecione a opção de acordo com o menu abaixo:" << endl;
    cout << " 1 -> Por identificador" << endl;
    cout << " 2 -> nome_galaxia" << endl;
    cout << " 3 -> tipo_galaxia" << endl;
    cout << " 4 -> magnitude" << endl;
    cout << " 5 -> constelacao" << endl;
    cout << endl << " Critério de seleção: ";
    int criterio = 0;
    cin >> criterio;

    switch (criterio) {
        case 1:
            quickSort(galaxias, 0, tamanhoArquivo - 1, criterio);
            break;
        case 2:
            sort(galaxias, galaxias + tamanhoArquivo, [](const Galaxia& a, const Galaxia& b) {
                return a.nome_galaxia < b.nome_galaxia;
            });
            break;
        case 3:
            sort(galaxias, galaxias + tamanhoArquivo, [](const Galaxia& a, const Galaxia& b) {
                return a.tipo_galaxia < b.tipo_galaxia;
            });
            break;
        case 4:
            quickSort(galaxias, 0, tamanhoArquivo - 1, criterio);
            break;
        case 5:
            sort(galaxias, galaxias + tamanhoArquivo, [](const Galaxia& a, const Galaxia& b) {
                return a.constelacao < b.constelacao;
            });
            break;
        default:
            cerr << " Critério de seleção inválido." << endl;
            return;
    }
}

// Função que carrega os dados do arquivo binário para o vetor de galáxias
void carregar_dados_bin(Galaxia galaxias[], string nomeArquivo, int tamanhoArquivo) {
    ifstream arquivo(nomeArquivo, std::ios::binary);

    if (arquivo.is_open()) {
        for (int i=0; i<tamanhoArquivo; i++) {
            // Escreve cada objeto Galaxia no arquivo binário
            arquivo.read(reinterpret_cast<char*>(&galaxias[i]), sizeof(Galaxia));
        }

        arquivo.close();
        cout << endl << "  Mensagem do sistema: Dados atualizados na memória com sucesso provenientes do arquivo binário." << endl << endl;
        } 
    else {
        cout << "  Mensagem do sistema: Erro ao carregar o arquivo binário." << endl;
    }
}

// Função que exibe o menu principal do programa
void menu(int tamanhoArquivo, string nomeArquivoCSVimport, string nomeArquivoCSVexport, string nome_arquivo_binario)
{

    // Bloco de indicação de quais as funções disponíveis para o usuário
    cout << endl << " ====================================================================" << endl;
    cout << endl << "                Bem vindo ao Catálogo de Galáxias!                    " << endl;
    cout << endl << " ====================================================================" << endl << endl;
    int escolha = 100;
    bool saved = false;
    string sairSemSalvar = "a";
    Galaxia empty_galaxy;
    empty_galaxy.constelacao = "vazio";
    empty_galaxy.identificador = 99999;
    empty_galaxy.magnitude = 0;
    empty_galaxy.nome_galaxia = "vazio";
    empty_galaxy.tipo_galaxia = "vazio";
    Galaxia galaxias[150];
    // inicializa galáxia vazia
    for (int i=0; i<tamanhoArquivo; i++) {
        galaxias[i] = empty_galaxy;
    }



    //Dados dos arquivos binários

    while (escolha != 0)
    {   
        cout << endl;
        cout << " ====================================================================" << endl;
        cout << " Escolha uma das opções:" << endl;
        cout << " 1  -> Importar dados de arquivo .csv" << endl;
        cout << " 2  -> Exportar dados para arquivo .csv" << endl;
        cout << " 3  -> Ordenar dados de acordo com característica especificada" << endl;
        cout << " 4  -> Inserir registro" << endl;
        cout << " 5  -> Apagar registro" << endl;
        cout << " 6  -> Buscar registro" << endl;
        cout << " 7  -> Exibir lista completa de registros" << endl;
        cout << " 8  -> Exibir lista parcial de registros" << endl;
        cout << " 9 -> Salvar alterações" << endl;
        cout << " 10 -> Carregar dados do arquivo binário" << endl;
        cout << " 0  -> Sair do programa" << endl;
        cout << endl << "====================================================================" << endl;     

        cout << " --> Opção: ";

        cin >> escolha;

        switch (escolha)
        {
            case 1: // Importar dados de arquivo .csv
                lerCSV(galaxias, nomeArquivoCSVimport); // retorna os dados para o vetor de galáxias > verificar se nenhum dado é perdido
                break;
            case 2: // Exportar dados para arquivo .csv
                salvarCSV(galaxias, nomeArquivoCSVexport, tamanhoArquivo);
                break;
            case 3: // Ordenar dados de acordo com característica especificada
                carregar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                ordenarDados(galaxias, tamanhoArquivo);
                salvar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                saved = false;
                break;
            case 4: // Inserir registro
                carregar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                inserirGalaxia(galaxias, tamanhoArquivo);
                salvar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                saved = false;
                break;
            case 5: // Apagar registro
                carregar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                removerGalaxia(nome_arquivo_binario);
                saved = false;
                break;
            case 6: // Buscar registro
                carregar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                buscarGalaxia(galaxias, tamanhoArquivo);
                break;
            case 7: // Exibir lista completa de registros
                carregar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                exibirListaCompleta(galaxias, tamanhoArquivo);
                break;
            case 8: // Exibir lista parcial de registros
                carregar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                imprimirIntervalo(galaxias, tamanhoArquivo);
                break;
            case 9: // Salvar alterações
                saved = salvar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                break;
            case 10: // Carregar dados do arquivo binário
                carregar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                break;
            case 0: // Sair do programa
                if (saved != true) {
                    cout << "Deseja salvar os dados antes de sair (Y/N) ?" << endl;
                    cin >> sairSemSalvar;
                    if ((sairSemSalvar == "Y") or (sairSemSalvar == "y")) {
                        saved = salvar_dados_bin(galaxias, nome_arquivo_binario, tamanhoArquivo);
                        cout << endl << "Obrigado! :)" << endl;
                    } else {
                        cout << endl << "Saindo sem salvar os dados!\nObrigado! :)" << endl;
                    }
                }
                break;
            default:
                cout << "Opção não disponível" << endl;
                break;
        }
    }
}

// Função principal
int main()
{
    // Declaração de nomes de arquivos de import e export de .csv
    // Necessário alterar o diretório para o local onde os arquivos estão salvos
    string nomeArquivoCSVimport = "C:/Users/clebe/OneDrive/Documentos/UFLA_Periodo_10/IALG/Trabalho_IALG_Galaxias/galaxys_import.csv";
    string nomeArquivoCSVexport = "C:/Users/clebe/OneDrive/Documentos/UFLA_Periodo_10/IALG/Trabalho_IALG_Galaxias/galaxys_export.csv";
    string nome_arquivo_binario = "C:/Users/clebe/OneDrive/Documentos/UFLA_Periodo_10/IALG/Trabalho_IALG_Galaxias/dados_binarios.dat";
    int tamanhoArquivo = 150;
    
    menu(tamanhoArquivo, nomeArquivoCSVimport, nomeArquivoCSVexport, nome_arquivo_binario);

    return 0;
}
