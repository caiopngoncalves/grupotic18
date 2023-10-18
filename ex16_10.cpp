#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Contato {
    static int contador;

    int cod;
    string nome;
    string telefone;
    string email;

public:

    static int getContador(){
        return contador;
    }

    static void incContador () {
        contador++;
    }

    Contato () {
        this->cod = Contato::getContador();
        Contato::incContador();
    }

    void setNome(string _nome) {
        nome = _nome;
    }

    string getNome() {
        return nome;
    }

    void setTelefone(string _telefone) {
        telefone = _telefone;
    }

    string getTelefone() {
        return telefone;
    }

    void setEmail(string _email) {
        email = _email;
    }

    string getEmail() {
        return email;
    }

    void setCod(int _cod) {
        cod = _cod;
    }

    int getCod() {
        return cod;
    }
};

// Define the static member variable outside the class
int Contato::contador = 0;

class Gerenciador {
    vector<Contato> contatos;

public:
    void salvarNoVector(Contato c) {
        contatos.push_back(c);
    }

    void salvarContato() {
        ofstream contatos_out("contatos.dt");
        for (Contato x : contatos) {
            if (x.getCod()) {  
                contatos_out << x.getCod() << endl;
            }

            if (x.getNome() != "") {  
                contatos_out << x.getNome() << endl;
            }

            if (x.getTelefone() != "") {  
                contatos_out << x.getTelefone() << endl;
            }

            if (x.getEmail() != "") { 
                contatos_out << x.getEmail() << endl;
            }
        }
    }

    void carregarContatos() {
        ifstream contatos_in("contatos.dt");
        while (!contatos_in.eof()) {
            Contato contatoAuxiliar;
            for (int i = 0; i <= 3; i++) {
                std::string linha;
                std::getline(contatos_in, linha);
                if (i == 0) {
                    int x = stoi(linha);
                    contatoAuxiliar.setCod(x);
                }
                else if (i == 1) {
                    contatoAuxiliar.setNome(linha);
                } else if (i == 2) {  
                    contatoAuxiliar.setTelefone(linha);
                } else if (i == 3) {  
                    contatoAuxiliar.setEmail(linha);
                }
            }
            contatos.push_back(contatoAuxiliar);
        }
    }

    void listagem () {
        for (Contato x : contatos) {
             if (x.getNome() != "") {
                // cout << "\nContato numero " << x.getCod() << endl;
                cout << "Nome: " << x.getNome () << endl;
                cout << "Telefone: " << x.getTelefone () << endl;
                cout << "E-mail: " << x.getEmail () << endl;
             }
        }
    }
};

int main() {
    string contador = "s";
    int opcao;
    Gerenciador gerenciador;
    ifstream contatos_in("contatos.dt");
  
    if(!contatos_in.peek())gerenciador.carregarContatos();

    do {
        cout << "1. Incluir" << endl;
        cout << "2. Listar" << endl;
        cin >> opcao;

        if (opcao == 1) {
            Contato contato;
            cout << "Digite o nome:" << endl;
            string nome;
            cin >> nome;
            contato.setNome(nome);

            cout << "Digite o telefone:" << endl;
            string telefone;
            cin >> telefone;
            contato.setTelefone(telefone);

            cout << "Digite o email:" << endl;
            string email;
            cin >> email;
            contato.setEmail(email);
            gerenciador.salvarNoVector(contato);
        }

        if (opcao == 2) {
            gerenciador.listagem();
        }

        cin.ignore(); // Limpar a quebra de linha pendente no buffer
        cout << "Digite s para continuar e n para finalizar" << endl;
        getline(cin, contador);

    } while (contador == "s");

    gerenciador.salvarContato(); // Salvar contatos no arquivo antes de sair

    return 0;
}
