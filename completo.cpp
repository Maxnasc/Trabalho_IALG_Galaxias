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
#include <cstring>

using namespace std;

const int TAMMAX = 50;

struct ClienteNutri
{
  int identificador;
  char nome[100];
  int idade;
  float altura;
  float peso;
  float percentual;

  // funçao salvar arquivo editado
  void salvararquivocsv(string nomedoarq, ClienteNutri clientes[], int numRegistros)
  {
    ofstream arquivocsv(nomedoarq);
    arquivocsv << "#identificador,nome,idade,altura,peso,percentual de gordura" << endl;

    for (int i = 0; i < numRegistros; i++)
    {
      arquivocsv << clientes[i].identificador << ",";
      arquivocsv << clientes[i].nome << ",";
      arquivocsv << clientes[i].idade << ",";
      arquivocsv << clientes[i].altura << ",";
      arquivocsv << clientes[i].peso << ",";
      arquivocsv << clientes[i].percentual << endl;
    }

    arquivocsv.close();
  }

  void imprimir(int pos)
  {
    cout << endl
         << "Cliente " << pos << ":" << endl;
    cout << "Identificador: " << identificador << endl;
    cout << "Nome: " << nome << endl;
    cout << "Idade: " << idade << endl;
    cout << "Altura: " << altura << endl;
    cout << "Peso: " << peso << endl;
    cout << "Percentual de gordura: " << percentual << endl;
  }

  void redimensionarVetor(ClienteNutri *&clientes, int &capacidade)
  {
    int novaCapacidade = capacidade * 2; // Dobrar a capacidade do vetor
    ClienteNutri *novoVetor = new ClienteNutri[novaCapacidade];

    memcpy(novoVetor, clientes, capacidade * sizeof(ClienteNutri));

    // Liberar a memória ocupada pelo vetor antigo
    delete[] clientes;

    // Atualizar o ponteiro do vetor para apontar para o novo vetor
    clientes = novoVetor;

    // Atualizar a capacidade do vetor
    capacidade = novaCapacidade;
  }

  void cadastrarCliente(ClienteNutri *&clientes, int &numRegistros, int &capacidade)
  {
    if (numRegistros >= capacidade)
    {
      redimensionarVetor(clientes, capacidade);
    }
    cin.ignore(); // Descarta o caractere de quebra de linha remanescente

    cout << "Digite o nome do cliente (primeiro e segundo nome): ";
    cin.getline(clientes[numRegistros].nome, 100);

    cout << "Digite a idade do cliente: ";
    cin >> clientes[numRegistros].idade;

    cout << "Digite a altura do cliente: ";
    cin >> clientes[numRegistros].altura;

    cout << "Digite o peso do cliente: ";
    cin >> clientes[numRegistros].peso;

    cout << "Digite o percentual de gordura do cliente: ";
    cin >> clientes[numRegistros].percentual;

    clientes[numRegistros].identificador = numRegistros + 1;

    numRegistros++;

    // // imprimir o cliente cadastrado
    // for (int i = 0; i < numRegistros; i++)
    // {
    //   clientes[i].imprimir(i + 1);
    // }

    cout << endl
         << "Cliente cadastrado com sucesso!" << endl;
  }
  void buscarCliente(ClienteNutri *vetorClientes, int numRegistros)
  {
    cout << "Deseja buscar pelo id ou pelo nome (digite id ou nome): ";

    string nomeORid;
    cin >> nomeORid;

    while ((nomeORid != "id") && (nomeORid != "nome"))
    {
      cout << "Erro: Digite uma opcao valida: ";
      cin >> nomeORid;
    }

    if (nomeORid == "id")
    {
      int id;
      cout << "Digite o identificador do cliente: ";

      bool encontrado = false;

      while (!encontrado) // loop que vai rodar até pegar um id válido
      {
        cin >> id;

        for (int i = 0; i < numRegistros; i++)
        {
          if (vetorClientes[i].identificador == id)
          {
            vetorClientes[i].imprimir(i + 1);
            encontrado = true;
          }
        }

        if (!encontrado)
        {
          cout << "Cliente com identificador " << id << " nao encontrado." << endl;
          cout << "Digite o identificador do cliente: ";
        }
      }
    }
    else if (nomeORid == "nome")
    {
      string nome;
      cout << "Digite o nome do cliente: ";
      cin.ignore();

      bool encontrado = false;

      while (!encontrado) // loop que vai rodar até pegar um nome válido
      {
        getline(cin, nome);

        for (int i = 0; i < numRegistros; i++)
        {
          if (vetorClientes[i].nome == nome)
          {
            vetorClientes[i].imprimir(i + 1);
            encontrado = true;
          }
        }

        if (!encontrado)
        {
          cout << "Cliente com nome " << nome << " nao encontrado." << endl;
          cout << "Digite o nome do cliente (primeiro e segundo nome): ";
        }
      }
    }
  }

  void editarDadosCliente(ClienteNutri *&vetorClientes, int numRegistros)
  {
    cout << "Deseja buscar os dados do cliente desejado pelo id ou pelo nome (digite id ou nome): ";

    string nomeORid;
    cin >> nomeORid;

    while (nomeORid != "id" && nomeORid != "nome")
    {
      cout << "Opcao invalida. Por favor, digite 'id' ou 'nome': ";
      cin >> nomeORid;
    }

    if (nomeORid == "id")
    {

      int id;
      cout << "Digite o identificador do cliente: ";
      // verifica se é válido

      while (!(cin >> id))
      {
        cout << "Erro: Digite um numero inteiro: ";
        cin.clear();
        cin.ignore(10000, '\n');
      }

      bool clienteEncontrado = false;
      int i = 0;

      while (i < numRegistros && !clienteEncontrado)
      {
        if (vetorClientes[i].identificador == id)
        {
          vetorClientes[i].imprimir(i + 1);
          clienteEncontrado = true;
        }
        else
        {
          i++;
        }
      }

      if (clienteEncontrado)
      {
        cout << endl;
        cout << "Cliente encontrado. O que deseja editar?" << endl;
        cout << "1. Editar todos os dados do cliente" << endl;
        cout << "2. Editar apenas um dado do cliente" << endl;

        int opcaoEdicao;
        cin >> opcaoEdicao;

        while (opcaoEdicao != 1 && opcaoEdicao != 2)
        {
          cout << endl
               << "Opcao invalida. Por favor, digite 1 ou 2: ";
          cin >> opcaoEdicao;
        }

        if (opcaoEdicao == 1) // Editar todos os dados de uma vez
        {
          cout << "Digite um novo nome: ";
          cin.ignore(); // Descarta o caractere de quebra de linha remanescente
          cin.getline(vetorClientes[i].nome, 100);

          cout << "Digite uma nova idade: ";
          cin >> vetorClientes[i].idade;

          cout << "Digite uma nova altura: ";
          cin >> vetorClientes[i].altura;

          cout << "Digite um novo peso: ";
          cin >> vetorClientes[i].peso;

          cout << "Digite um novo percentual de gordura: ";
          cin >> vetorClientes[i].percentual;

          cout << endl
               << "Dados atualizados com sucesso" << endl;
        }
        else if (opcaoEdicao == 2) // editar apenas 1 dado
        {
          cout << "Qual dado deseja editar?" << endl;
          cout << "Digite 1 para editar: Nome" << endl;
          cout << "Digite 2 para editar: Idade" << endl;
          cout << "Digite 3 para editar: Altura" << endl;
          cout << "Digite 4 para editar: Peso" << endl;
          cout << "Digite 5 para editar: Percentual de Gordura" << endl;
          cout << "Escolha uma das opcoes acima: ";
          int dadoEdicao;
          cin >> dadoEdicao;

          while (dadoEdicao < 1 || dadoEdicao > 5)
          {
            cout << endl
                 << "Opcao invalida. Por favor, digite um numero entre 1 e 5: ";
            cin >> dadoEdicao;
          }

          switch (dadoEdicao)
          {
          case 1:
            cout << "Digite um novo nome: ";
            cin.ignore(); // Descarta o caractere de quebra de linha remanescente
            cin.getline(vetorClientes[i].nome, 100);
            cout << endl
                 << "Nome atualizado com sucesso" << endl;
            break;

          case 2:
            cout << "Digite uma nova idade: ";
            cin >> vetorClientes[i].idade;
            cout << endl
                 << "Idade atualizada com sucesso" << endl;
            break;

          case 3:
            cout << "Digite uma nova altura: ";
            cin >> vetorClientes[i].altura;
            cout << endl
                 << "Altura atualizada com sucesso" << endl;
            break;

          case 4:
            cout << "Digite um novo peso: ";
            cin >> vetorClientes[i].peso;
            cout << endl
                 << "Peso atualizado com sucesso" << endl;
            break;

          case 5:
            cout << "Digite um novo percentual de gordura: ";
            cin >> vetorClientes[i].percentual;
            cout << endl
                 << "Percentual de gordura atualizado com sucesso" << endl;
            break;
          }
        }
      }
      else
      {
        cout << endl
             << "Cliente com identificador " << id << " nao encontrado." << endl;
      }
    }
    else if (nomeORid == "nome")
    {
      string nome;
      cout << "Digite o nome do cliente: ";
      // enquanto o nome nao for letras, pede para digitar novamente
      while (!(cin >> nome))
      {
        cout << "Erro: Digite um nome valido: ";
        cin.clear();
        cin.ignore(10000, '\n');
      }

      bool clienteEncontrado = false;
      int i = 0;

      while (i < numRegistros && !clienteEncontrado)
      {
        if (vetorClientes[i].nome == nome)
        {
          vetorClientes[i].imprimir(i + 1);
          clienteEncontrado = true;
        }
        else
        {
          i++;
        }
      }

      if (clienteEncontrado)
      {
        cout << "Cliente encontrado. O que deseja editar?" << endl;
        cout << "1. Editar todos os dados do cliente" << endl;
        cout << "2. Editar apenas um dado do cliente" << endl;

        int opcaoEdicao;
        cin >> opcaoEdicao;

        while (opcaoEdicao != 1 && opcaoEdicao != 2)
        {
          cout << "Opção inválida. Por favor, digite 1 ou 2: ";
          cin >> opcaoEdicao;
        }

        if (opcaoEdicao == 1)
        {
          cout << "Digite um novo nome: ";
          cin.ignore(); // Descarta o caractere de quebra de linha remanescente
          cin.getline(vetorClientes[i].nome, 100);

          cout << "Digite uma nova idade: ";
          cin >> vetorClientes[i].idade;

          cout << "Digite uma nova altura: ";
          cin >> vetorClientes[i].altura;

          cout << "Digite um novo peso: ";
          cin >> vetorClientes[i].peso;

          cout << "Digite um novo percentual de gordura: ";
          cin >> vetorClientes[i].percentual;

          cout << endl
               << "Dados atualizados com sucesso" << endl;
        }
        else if (opcaoEdicao == 2)
        {
          cout << "Qual dado deseja editar?" << endl;
          cout << "1. Nome" << endl;
          cout << "2. Idade" << endl;
          cout << "3. Altura" << endl;
          cout << "4. Peso" << endl;
          cout << "5. Percentual de Gordura" << endl;

          int dadoEdicao;
          cin >> dadoEdicao;

          while (dadoEdicao < 1 || dadoEdicao > 5)
          {
            cout << "Opção inválida. Por favor, digite um número entre 1 e 5: ";
            cin >> dadoEdicao;
          }

          switch (dadoEdicao)
          {
          case 1:
            cout << "Digite um novo nome: ";
            cin.ignore(); // Descarta o caractere de quebra de linha remanescente
            cin.getline(vetorClientes[i].nome, 100);
            cout << endl
                 << "Nome atualizado com sucesso" << endl;
            break;
          case 2:
            cout << "Digite uma nova idade: ";
            cin >> vetorClientes[i].idade;
            cout << endl
                 << "Idade atualizada com sucesso" << endl;
            break;
          case 3:
            cout << "Digite uma nova altura: ";
            cin >> vetorClientes[i].altura;
            cout << endl
                 << "Altura atualizada com sucesso" << endl;
            break;
          case 4:
            cout << "Digite um novo peso: ";
            cin >> vetorClientes[i].peso;
            cout << endl
                 << "Peso atualizado com sucesso" << endl;
            break;
          case 5:
            cout << "Digite um novo percentual de gordura: ";
            cin >> vetorClientes[i].percentual;
            cout << endl
                 << "Percentual de gordura atualizado com sucesso" << endl;
            break;
          }
        }
      }
      else
      {
        cout << endl
             << "Cliente com nome " << nome << " nao encontrado." << endl;
      }
    }
  }

  void removerCliente(ClienteNutri *&clientes, int &numRegistros)
  {
    int id;
    cout << "Digite o identificador do cliente a ser removido: ";
    bool clienteEncontrado = false;

    while (!clienteEncontrado) // loop que vai rodar ate pegar um id valido
    {
      cin >> id;
      int posicao = -1;

      for (int i = 0; i < numRegistros; i++)
      {
        if (clientes[i].identificador == id)
        {
          clientes[i].imprimir(i + 1);
          clienteEncontrado = true;
          posicao = i;
        }
      }

      if (clienteEncontrado)
      {
        int confirmacao;
        cout << "Tem certeza que deseja remover o cliente? (1 - Sim, 2 - Nao): ";
        cin >> confirmacao;
        while (confirmacao < 1 || confirmacao > 2)
        {
          cout << endl
               << "ERRO: Digite uma opcao valida: ";
          cin >> confirmacao;
        }

        if (confirmacao == 1)
        {
          for (int i = posicao; i < numRegistros - 1; i++)
          {
            clientes[i] = clientes[i + 1];
          }

          numRegistros--;

          cout << "Cliente removido com sucesso!" << endl;

          for (int i = 0; i < numRegistros; i++)
          {
            clientes[i].identificador = i + 1;
          }
        }
        else if (confirmacao == 2)
        {

          cout << "Remocao cancelada pelo usuário." << endl;
        }
      }
      else
      {
        cout << "Cliente com identificador " << id << " nao encontrado." << endl;
        cout << "Digite o identificador do cliente a ser removido: ";
      }
    }
  }

  void mostrarClientes(ClienteNutri *&vetorClientes, int numRegistros)
  {
    // Lógica para mostrar todos os clientes
    cout << "Digite 1 se deseja mostrar um intervalo de clientes. Digite 2 se deseja mostrar todos os clientes: ";
    int escolha;
    cin >> escolha;

    while (escolha != 1 && escolha != 2)
    {
      cout << "Erro: Digite uma opcao valida: ";
      cin >> escolha;
    }

    if (escolha == 1)
    {
      cout << "Digite o ID de inicio: ";
      int idInicio;
      cin >> idInicio;

      cout << "Digite o ID de fim: ";
      int idFim;
      cin >> idFim;

      while (idInicio > idFim)
      {
        cout << "ERRO: A id de inicio nao pode ser maior que a id do fim" << endl;
        cout << "Digite o ID de inicio: ";
        cin >> idInicio;
        cout << "Digite o ID de fim: ";
        cin >> idFim;
      }
      // Lógica para mostrar os clientes a partir do ID de início até o ID de fim
      for (int i = 0; i < numRegistros; i++)
      {
        if (vetorClientes[i].identificador >= idInicio && vetorClientes[i].identificador <= idFim)
        {
          vetorClientes[i].imprimir(i + 1);
        }
      }
    }
    else if (escolha == 2)
    {
      for (int i = 0; i < numRegistros; i++)
      {
        vetorClientes[i].imprimir(i + 1);
      }
    }
  }

  void intercalaIdade(ClienteNutri clientes[], int inicio, int meio, int fim)
  {
    int i = inicio, j = meio + 1;
    int tamanho = fim - inicio + 1;
    ClienteNutri *aux = new ClienteNutri[tamanho];

    for (int k = 0; k < tamanho; k++)
    {
      if ((i <= meio) && (j <= fim))
      {
        if (clientes[i].idade <= clientes[j].idade)
        {
          aux[k] = clientes[i];
          i++;
        }
        else
        {
          aux[k] = clientes[j];
          j++;
        }
      }
      else if (i > meio)
      {
        aux[k] = clientes[j];
        j++;
      }
      else
      {
        aux[k] = clientes[i];
        i++;
      }
    }

    for (int k = 0; k < tamanho; k++)
    {
      clientes[inicio + k] = aux[k];
    }

    delete[] aux;
  }

  void intercalaNome(ClienteNutri nomes[], int inicio, int meio, int fim)
  {
    int i = inicio, j = meio + 1;
    int tamanho = fim - inicio + 1;
    ClienteNutri *aux = new ClienteNutri[tamanho];

    for (int k = 0; k < tamanho; k++)
    {
      if ((i <= meio) && (j <= fim))
      {
        if (strcmp(nomes[i].nome, nomes[j].nome) <= 0)
        {
          aux[k] = nomes[i];
          i++;
        }
        else
        {
          aux[k] = nomes[j];
          j++;
        }
      }
      else if (i > meio)
      {
        aux[k] = nomes[j];
        j++;
      }
      else
      {
        aux[k] = nomes[i];
        i++;
      }
    }

    for (int k = 0; k < tamanho; k++)
    {
      nomes[inicio + k] = aux[k];
    }

    delete[] aux;
  }

  void mergeSortIdade(ClienteNutri clientes[], int inicio, int fim)
  {
    if (inicio < fim)
    {
      int meio = (inicio + fim) / 2;
      mergeSortIdade(clientes, inicio, meio);
      mergeSortIdade(clientes, meio + 1, fim);
      intercalaIdade(clientes, inicio, meio, fim);
    }
  }

  void mergeSortNome(ClienteNutri clientes[], int inicio, int fim)
  {
    if (inicio < fim)
    {
      int meio = (inicio + fim) / 2;
      mergeSortNome(clientes, inicio, meio);
      mergeSortNome(clientes, meio + 1, fim);
      intercalaNome(clientes, inicio, meio, fim);
    }
  }

  void ordenarClientes(ClienteNutri *&vetorClientes, int numRegistros)
  {
    int opcao;
    cout << "1. Ordenar por nome" << endl;
    cout << "2. Ordenar por idade" << endl;
    cout << "Escolha uma opcao: ";
    cin >> opcao;

    while (opcao < 1 || opcao > 2)
    {
      cout << "Erro: Digite uma opcao valida: ";
      cin >> opcao;
    }

    switch (opcao)
    {
    case 1:
      mergeSortNome(vetorClientes, 0, numRegistros - 1);
      cout << endl
           << "*Clientes ordenados por nome com sucesso!*" << endl;
      break;

    case 2:
      mergeSortIdade(vetorClientes, 0, numRegistros - 1);
      cout << endl
           << "*Clientes ordenados por idade com sucesso!*" << endl;
      break;

    default:
      cout << "Opcao invalida. Nenhum cliente foi ordenado." << endl;
      break;
    }
  }
};

void importarArquivo(string nomedoarq, ClienteNutri *&clientes, int &numRegistros, int &capacidade)
{
  ifstream arquivocsv(nomedoarq);

  if (!arquivocsv.is_open())
  {
    cout << "Erro ao abrir o arquivo" << endl;
    return;
  }

  string linha;
  getline(arquivocsv, linha);

  while (getline(arquivocsv, linha))
  {
    if (numRegistros >= capacidade)
    {
      int novaCapacidade = capacidade * 2; // Dobrar a capacidade do vetor
      ClienteNutri *novoVetor = new ClienteNutri[novaCapacidade];

      copy(&clientes[0], &clientes[capacidade], novoVetor);

      // Liberar a memória ocupada pelo vetor antigo
      delete[] clientes;

      // Atualizar o ponteiro do vetor para apontar para o novo vetor
      clientes = novoVetor;

      // Atualizar a capacidade do vetor
      capacidade = novaCapacidade;
    }

    // int identificador = stoi(linha.substr(0, linha.find(",")));
    linha.erase(0, linha.find(",") + 1);

    string nome = linha.substr(0, linha.find(","));
    linha.erase(0, linha.find(",") + 1);

    int idade = stoi(linha.substr(0, linha.find(",")));
    linha.erase(0, linha.find(",") + 1);

    float altura = stof(linha.substr(0, linha.find(",")));
    linha.erase(0, linha.find(",") + 1);

    float peso = stof(linha.substr(0, linha.find(",")));
    linha.erase(0, linha.find(",") + 1);

    float percentual = stof(linha.substr(0, linha.find(",")));
    linha.erase(0, linha.find(",") + 1);

    clientes[numRegistros].identificador = numRegistros + 1;
    strcpy(clientes[numRegistros].nome, nome.c_str());
    clientes[numRegistros].idade = idade;
    clientes[numRegistros].altura = altura;
    clientes[numRegistros].peso = peso;
    clientes[numRegistros].percentual = percentual;

    numRegistros++;
  }

  arquivocsv.close();
}

int main()
{
  // Leitura do arquivo
  ifstream arquivoEntrada("nutricionista.bin", ios::binary); // arquivo dentro da pasta output

  if (!arquivoEntrada.is_open())
  {
    cout << "Erro ao abrir o arquivo" << endl;
    return 0;
  }

  // utilizcão struct com ponteiro para armazenar os dados do arquivo
  arquivoEntrada.seekg(0, ios::end);

  int tamanhoArquivo = arquivoEntrada.tellg();

  int capacidade = tamanhoArquivo / sizeof(ClienteNutri);

  arquivoEntrada.seekg(0, ios::beg);

  ClienteNutri *vetorClientes = new ClienteNutri[capacidade];
  ClienteNutri cliente;

  string linha;
  int numRegistros = 0;

  while (numRegistros < capacidade && arquivoEntrada.read((char *)&vetorClientes[numRegistros], sizeof(ClienteNutri)))
  {
    numRegistros++;
  }
  
  if (!arquivoEntrada)
  {
    cout << "Erro: nao foi possivel abrir o arquivo" << endl;
    return 1;
  }
  else
  {
    int opcao = 0;

    while (opcao != 8) // menu
    {
      cout << endl;
      cout << "* CADASTRO DE CLIENTES NA NUTRICIONISTA *" << endl
           << endl;
      cout << "1. Cadastrar novo cliente" << endl;
      cout << "2. Buscar cliente" << endl;
      cout << "3. Editar dados do cliente" << endl;
      cout << "4. Remover cliente" << endl;
      cout << "5. Mostrar clientes" << endl;
      cout << "6. Ordenar clientes" << endl;
      cout << "7. Importar/Exportar arquivo" << endl;
      cout << "8. Sair" << endl
           << endl;
      cout << "Escolha uma opcao: ";
      cin >> opcao;

      while (opcao < 1 || opcao > 8)
      {
        cout << "Erro: opcao invalida. Digite a opcao novamente: ";
        cin >> opcao;
      }

      switch (opcao)
      {
      case 1:
      { // Lógica para cadastrar novo cliente
        cliente.cadastrarCliente(vetorClientes, numRegistros, capacidade);

        // Exportar os dados para um arquivo binário
        ofstream arquivoOut("nutricionista.bin", ios::binary); // se for para salvar depois de alterar ou cadastrar, é só colocar o mesmo nome do arquivo bancoDeDados que vai sobrescrever

        if (!arquivoOut.is_open())
        {
          cout << "Erro ao abrir o arquivo" << endl;
          return 0;
        }

        for (int i = 0; i < numRegistros; i++)
        {
          arquivoOut.write((char *)&vetorClientes[i], sizeof(ClienteNutri));
        }

        arquivoOut.close();

        break;
      }

      case 2:
      { // Lógica para buscar cliente
        cliente.buscarCliente(vetorClientes, numRegistros);
        break;
      }
      
      case 3:
      { // Lógica para editar dados do cliente
        cliente.editarDadosCliente(vetorClientes, numRegistros);

        // Exportar os dados para um arquivo binário
        ofstream arquivoOut("nutricionista.bin", ios::binary); // se for para salvar depois de alterar ou cadastrar, é só colocar o mesmo nome do arquivo bancoDeDados que vai sobrescrever

        if (!arquivoOut.is_open())
        {
          cout << "Erro ao abrir o arquivo" << endl;
          return 0;
        }

        for (int i = 0; i < numRegistros; i++)
        {
          arquivoOut.write((char *)&vetorClientes[i], sizeof(ClienteNutri));
        }

        arquivoOut.close();

        break;
      }

      case 4:
      { // Lógica para remover cliente
        cliente.removerCliente(vetorClientes, numRegistros);

        // Exportar os dados para um arquivo binário
        ofstream arquivoOut("nutricionista.bin", ios::binary); // se for para salvar depois de alterar ou cadastrar, é só colocar o mesmo nome do arquivo bancoDeDados que vai sobrescrever

        if (!arquivoOut.is_open())
        {
          cout << "Erro ao abrir o arquivo" << endl;
          return 0;
        }

        for (int i = 0; i < numRegistros; i++)
        {
          arquivoOut.write((char *)&vetorClientes[i], sizeof(ClienteNutri));
        }

        arquivoOut.close();

        break;
      }

      case 5:
      { // Lógica para mostrar os clientes
        cliente.mostrarClientes(vetorClientes, numRegistros);
        break;
      }

      case 6:
      { // Lógica para ordenar
        cliente.ordenarClientes(vetorClientes, numRegistros);
        // Exportar os dados para um arquivo binário
        ofstream arquivoOut("nutricionista.bin", ios::binary); // se for para salvar depois de alterar ou cadastrar, é só colocar o mesmo nome do arquivo bancoDeDados que vai sobrescrever

        if (!arquivoOut.is_open())
        {
          cout << "Erro ao abrir o arquivo" << endl;
          return 0;
        }

        for (int i = 0; i < numRegistros; i++)
        {
          arquivoOut.write((char *)&vetorClientes[i], sizeof(ClienteNutri));
        }

        arquivoOut.close();

        break;
      }

      case 7:
      {
        cout << "Escolha uma opcao: " << endl;
        cout << "1. Importar arquivo" << endl;
        cout << "2. Exportar arquivo" << endl;

        cout << "Digite uma opcao: ";
        int opcao;
        cin >> opcao;

        while (opcao < 1 || opcao > 2)
        {
          cout << "Erro: Digite uma opcao valida: ";
          cin >> opcao;
        }

        if (opcao == 1)
        {
          cout << "Digite o nome do arquivo que deseja importar: ";
          string nomedoarq;
          cin >> nomedoarq;

          importarArquivo(nomedoarq, vetorClientes, numRegistros, capacidade);

          // Exportar os dados para um arquivo binário
          ofstream arquivoOut("nutricionista.bin", ios::binary); // se for para salvar depois de alterar ou cadastrar, é só colocar o mesmo nome do arquivo bancoDeDados que vai sobrescrever

          if (!arquivoOut.is_open())
          {
            cout << "Erro ao abrir o arquivo" << endl;
            return 0;
          }

          for (int i = 0; i < numRegistros; i++)
          {
            arquivoOut.write((char *)&vetorClientes[i], sizeof(ClienteNutri));
          }

          arquivoOut.close();
        }
        else if (opcao == 2)
        {
          cout << "Digite o nome do arquivo que deseja exportar: ";
          string nomedoarq;
          cin >> nomedoarq;

          cliente.salvararquivocsv(nomedoarq, vetorClientes, numRegistros);
        }
      }

      case 8:
      {
        cout << "Encerrando o programa..." << endl;
        break;
      }
      }
    }

    arquivoEntrada.close();
    return 0;
  }
}