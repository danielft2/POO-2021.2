#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Fone {
private:
    string id;
    string number;
public:
    Fone(string ident = "vivo", string num = "0") {
        this->setId(ident);
        this->setNumber(num);
    }

    bool validateNumber(string number) {
        if (number.size() > 13 || number.size() <= 0) {
            cout << "Numero invalido\n";
            return false;
        }
       
        for (auto caractere : number) {
            if ((int)caractere > 57 || (int)caractere < 40) {
                if ((int)caractere != 40 && (int)caractere != 41 && (int)caractere !=  46 ) {
                    cout << "Numero invalido\n";
                    return false;
                }
            } 
        }    

        return true;
    }

    string getId() {
        return this->id;
    }

    string getNumber() {
        return this->number;
    }
    
    void setId(string id) {
        if (id != "casa" && id != "fixo" && id != "oi" && id != "tim" && id != "claro" && id != "vivo") 
           cout << "Id invalido, informe outro\n";
        else 
           this->id = id;
    }

    void setNumber(string number) {
        this->number = number;
    }

    friend std::ostream& operator<<(std::ostream& os, Fone& fone) {
        os << fone.id << ":" << fone.number;
        return os;
    }
};

class Contact {
private:
    string prefix {"-"};
    list<Fone> fones;
    string name;
    int ind {0};
public:
    Contact(string name = "") {
        this->setName(name);
    }

    void addFone(Fone fone) {
        string copia = fone.getNumber();
        if(fone.validateNumber(copia)) {
            fones.push_back(fone);
        }  
    }

    void removeFone(int ind) {
        if (ind < 0 || ind > (int) fones.size()) {
            cout << "O numero nao foi encontrado\n";
        } else {
            fones.erase(next(fones.begin(), ind));
        }
    }
    
    list<Fone> getFones() {
        return this->fones;
    }

    string getName() const {
        return this->name;
    }

    void setName(string name) {
        if (name != "") 
            fones.clear();
        this->name = name;
    }

    friend std::ostream& operator<<(std::ostream& os, Contact& contact) {
        if (contact.fones.empty()) {
            os << contact.prefix << " " << contact.name;
            os << " []";
        } else {
            int i = 0;
            os << contact.prefix << " " << contact.name;
            for (auto fone: contact.fones) {
                os << " [" << i << ":" << fone << "]";
                i++;
            }
        }
        return os;
    }
};

class Agenda {
private:
    unordered_map<string, Contact> contatos;
    void analisarTelefones(Contact contact, string chave) {
        for (auto telefone : contact.getFones()) {
            auto novoTelefone = comparaTelefones(contatos[chave].getFones(), telefone);
            if (novoTelefone) 
               contatos[chave].addFone(telefone);
        }
    }

    bool comparaTelefones(list<Fone> fones, Fone telefone) {
        for (auto fone : fones) {
            if (fone.getId() == telefone.getId() && fone.getNumber() == telefone.getNumber()) 
                return false;
        }

        return true;
    }

    bool comparaPattern(Contact contato, string pattern) {
        string line = contato.getName();

        for (auto telefone : contato.getFones()) {
            line += telefone.getId();
            line += telefone.getNumber();

            int pos = line.find(pattern);
            if (pos != string::npos)
                return true;
        }

        return false;
    } 
    
public:
    Agenda() {
    }

    void addContact(Contact contact) {
        auto it = contatos.find(contact.getName());
        if (it == contatos.end()) {
            contatos[contact.getName()] = contact;
        } else {
            analisarTelefones(contact, it->first);
        }

    }

    void removeContato(string name) {
        auto it = contatos.find(name);
        if (it == contatos.end()) {
            cout << "O contanto nao foi encontrado\n";
        } else {
            contatos.erase(it);
        }
    }

    void removerTelefone(string name, int ind) {
        auto it = contatos.find(name);
        if (it == contatos.end()) {
            cout << "O contanto nao foi encontrado\n";
        } else {
            contatos[name].removeFone(ind);
        }
    }

    list<Contact> search(string pattern) {
        list<Contact> contatosPadroes;
        for (auto contato : contatos) {
            if (comparaPattern(contato.second, pattern))
                contatosPadroes.push_back(contato.second);
        }

        return contatosPadroes;
    }

    Contact* getContato(string name) {
        auto it = contatos.find(name);
        if (it == contatos.end()) {
            cout << "O contato nao foi encontrado\n";
            return nullptr;
        } else {
            return &contatos[name];
        }
        
    }

    friend ostream& operator<<(ostream& os, const Agenda& agenda) {
        if (agenda.contatos.empty()) {
            os << "[AGENDA VAZIA]\n";
        } else {
            for (auto contato : agenda.contatos) {
                os << contato.second << "\n";
            }
        }
        return os;
    }
};

int main() {
    system("cls");
    
    Agenda agenda;
    cout << agenda << "\n";
    
    Contact contact("Daniel");
    contact.addFone(Fone("fixo", "8899"));
    contact.addFone(Fone("oi", "9977"));

    Contact contact1("Daniel");
    contact1.addFone(Fone("fixo", "8899"));
    contact1.addFone(Fone("oi", "9977"));
    contact1.addFone(Fone("casa", "99779"));

    Contact contact2("islane");
    contact2.addFone(Fone("tim", "(88)99"));
    contact2.addFone(Fone("vivo", "99.779.22"));
    

    cout << "Adicionando o mesmo contato: \n";
    agenda.addContact(contact);
    cout << agenda;
    agenda.addContact(contact1);
    cout << agenda << "\n\n";

    cout << "Adicionando um novo contato: \n";
    agenda.addContact(contact2);
    cout << agenda << "\n\n";

    cout << "Removendo telefone de um contato: \n";
    cout << agenda << "\n";
    agenda.removerTelefone("Daniel", 2);
    cout << agenda << "\n\n";
    
    cout << "Fazendo busca de padroes: \n";
    for (auto contato : agenda.search("Da")) {
        cout << contato << "\n";
    }

    cout << "\nRemovendo contato: \n";
    cout << agenda << "\n";
    agenda.removeContato("Daniel");
    cout << agenda;
}