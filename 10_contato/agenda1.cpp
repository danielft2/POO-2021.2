#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Fone {
private:
    string id;
    string number;
public:
    Fone(string id = "", string number = "0") {
        this->setId(id);
        this->setNumber(number);
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

    string getName() {
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

int main() {
    system("cls");
 
    Contact contact("Daniel");

    //ADICIONANDO OS TELEFONES
    cout << "Adicionando: \n";
    cout << contact << "\n";
    contact.addFone(Fone("fixo", "8899"));
    contact.addFone(Fone("oi", "9977"));
    contact.addFone(Fone("tim", "1244"));
    cout << contact << "\n\n";

    //REMOVENDO TELEFONE POR INDICE
    cout << "Removendo: \n";
    cout << contact << "\n";
    contact.removeFone(1);
    cout << contact << "\n\n";

    //VERIFICANDO TELEFONE
    cout << "Verificando: \n";
    contact.addFone(Fone("vivo", "99."));
    cout << contact << "\n\n";
}