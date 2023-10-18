#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Inclui as bibliotecas necessárias, como iostream para entrada/saída, fstream para manipulação de arquivos,
// vector para armazenar contatos em uma lista dinâmica e string para manipulação de strings.

class Contato {
private:
    string nome;
    string telefone;
    string email;
    vector<Contato*> amigos;

public:
    // Declaração da classe Contato que representa informações de contato, com nome, telefone e email.

    Contato(const string& nome, const string& telefone, const string& email) {
        this->nome = nome;
        this->telefone = telefone;
        this->email = email;
    }

    // Construtor da classe Contato que inicializa os atributos privados com os valores passados.

    string getNome() const {
        return nome;
    }

    string getTelefone() const {
        return telefone;
    }

    string getEmail() const {
        return email;
    }

//void fazer_amigo(Contato *outro){
//  amigos.push_back(outro);
//  outro->amigos.push
//}
    // Métodos para obter os valores dos atributos privados.

};

class Agenda {
private:
    vector<Contato> contatos;

public:
    // Declaração da classe Agenda que gerencia uma lista de contatos representados como objetos da classe Contato.

    void adicionarContato(const Contato& contato) {//recebe o endereço de contatos e deixa constante
        contatos.push_back(contato);
    }

    // Método para adicionar um contato à lista de contatos.

    void listarContatos() {
        for (size_t i = 0; i < contatos.size(); i++) {
            cout << "Índice: " << i << "\nNome: " << contatos[i].getNome() << "\nTelefone: " << contatos[i].getTelefone() << "\nEmail: " << contatos[i].getEmail() << "\n\n";
        }
    }

    // Método para listar todos os contatos na agenda, mostrando seus índices, nomes, telefones e emails.

    void excluirContato(int indice) {
        if (indice >= 0 && static_cast<size_t>(indice) < contatos.size()) {
            contatos.erase(contatos.begin() + indice);
            cout << "Contato excluído com sucesso!" << endl;
        } else {
            cerr << "Índice de contato inválido." << endl;
        }
    }

    // Método para excluir um contato com base no índice fornecido. Verifica se o índice é válido antes de excluir.

    void salvarContatos(const string& nomeArquivo) {
        ofstream arquivo(nomeArquivo); // Abre arquivo para escrita
        if (arquivo.is_open()) {
            for (const Contato& contato : contatos) {
                arquivo << contato.getNome() << "," << contato.getTelefone() << "," << contato.getEmail() << "\n";
            }
            arquivo.close();
            cout << "Contatos salvos com sucesso!" << endl;
        } else {
            cerr << "Erro ao abrir o arquivo para escrita." << endl;
        }
    }




    // Método para salvar os contatos em um arquivo CSV. Cada contato é escrito como uma linha no arquivo.

    void carregarContatos(const string& nomeArquivo) {
        ifstream arquivo(nomeArquivo);//Abre o arquivo para leitura
        if (arquivo.is_open()) {
            string linha;
            while (getline(arquivo, linha)) {
                size_t pos1 = linha.find(',');
                size_t pos2 = linha.find(',', pos1 + 1);
                if (pos1 != string::npos && pos2 != string::npos) {
                    string nome = linha.substr(0, pos1);
                    string telefone = linha.substr(pos1 + 1, pos2 - pos1 - 1);
                    string email = linha.substr(pos2 + 1);
                    Contato contato(nome, telefone, email);
                    adicionarContato(contato);
                }
            }
            arquivo.close();
        } else {
            cerr << "Arquivo de contatos não encontrado." << endl;
        }
    }

    // Método para carregar contatos de um arquivo CSV. O arquivo é lido e cada linha é processada para criar um novo contato.

};

int main() {
    Agenda agenda;
    string nome, telefone, email;
    Contato novoContato("", "", "");
   ifstream arquivo("contatos.txt");
    // Declara a instância da classe Agenda e as variáveis para armazenar informações de entrada do usuário.
   agenda.carregarContatos("contatos.txt");

    while (true) {
        cout << "1. Listar Contatos\n2. Adicionar Contato\n3. Excluir Contato\n4. Salvar Contatos\n5. Sair\n";
        int opcao;
        cin >> opcao;

        // Exibe um menu com opções numeradas para o usuário escolher.

        switch (opcao) {
            case 1:
                agenda.listarContatos();
                break;

            // Se o usuário escolher a opção 1, lista os contatos na agenda.

            case 2:
                cout << "Nome: ";
                cin.ignore();
                getline(cin, nome);
                cout << "Telefone: ";
                getline(cin, telefone);
                cout << "Email: ";
                getline(cin, email);
                novoContato = Contato(nome, telefone, email);
                agenda.adicionarContato(novoContato);
                break;

            // Se o usuário escolher a opção 2, solicita informações do novo contato e o adiciona à agenda.

            case 3:
                int indice;
                cout << "Informe o índice do contato a ser excluído: ";
                cin >> indice;
                agenda.excluirContato(indice);
                break;

            // Se o usuário escolher a opção 3, solicita o índice do contato a ser excluído e realiza a exclusão.

            case 4:
                agenda.salvarContatos("contatos.txt");
                break;

            // Se o usuário escolher a opção 4, salva os contatos em um arquivo chamado "contatos.txt".

            case 5:
                return 0;

            // Se o usuário escolher a opção 5, sai do programa.

            default:
                cout << "Opção inválida. Tente novamente.\n";
        }
    }

    return 0;
}
