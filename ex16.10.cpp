#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Contato {
    string nome;
    string telefone;
    string email;

public:
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
};

class Gerenciador {
    vector<Contato> contatos;

public:
    void salvarNoVector(Contato c) {
        contatos.push_back(c);
    }

    void salvarContato() {
        ofstream contatos_out("contatos.dt");
        for (Contato x : contatos) {
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
            for (int i = 0; i <= 2; i++) {
                std::string linha;
                std::getline(contatos_in, linha);
                if (i == 0) {
                    contatoAuxiliar.setNome(linha);
                } else if (i == 1) {  
                    contatoAuxiliar.setTelefone(linha);
                } else if (i == 2) {  
                    contatoAuxiliar.setEmail(linha);
                }
            }
            contatos.push_back(contatoAuxiliar);
        }
    }

    void listagem () {
        int contador = 1;
        for (Contato x : contatos) {
             if (x.getNome() != "") {
                cout << "\nContato numero " << contador << endl;
                cout << "Nome: " << x.getNome () << endl;
                cout << "Telefone: " << x.getTelefone () << endl;
                cout << "E-mail: " << x.getEmail () << endl;
                contador++;
             }
        }
    }
};

int main() {
    string contador = "s";
    int opcao;
    Gerenciador gerenciador;
    gerenciador.carregarContatos();

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

            gerenciador.listagem ();
        }

        cin.ignore(); // Limpar a quebra de linha pendente no buffer
        cout << "Digite s para continuar e n para finalizar" << endl;
        getline(cin, contador);

    } while (contador == "s");

    gerenciador.salvarContato(); // Salvar contatos no arquivo antes de sair

    return 0;
}