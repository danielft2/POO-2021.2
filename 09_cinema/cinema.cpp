#include <iostream>
#include <list>
#include <vector>
#include <memory>

using namespace std;

class Cliente {
private:
    int telefone;
    string id;
public:
    Cliente(string id = "", int numero = 0) : id {id}, telefone {numero} {
    } 

    int getFone() {
        return this->telefone;
    }

    string getId() {
        return this->id;
    }
    
    void setNumero(int numero) {
        this->telefone = numero;
    }

    void setId(string id) {
        if (id == "")
            cout << "informe um nome valido\n.";
        else 
           this->id = id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Cliente& cliente) {
        os << cliente.id << "-" << cliente.telefone << "";
        return os;
    }
};

class Sala {
private:
    vector<shared_ptr<Cliente>> cadeiras;
public:
    Sala(int qntdCadeiras) : cadeiras(qntdCadeiras, nullptr) {
    }

    bool verifica(string name) {
        for (auto cadeira : cadeiras) {
            if (cadeira != nullptr && cadeira->getId() == name) 
                return true;   
        }  

        return false;
    }

    void reservar(shared_ptr<Cliente> cliente, int ind) {  
        if (this->verifica(cliente->getId())) {
            cout << "O cliente ja esta na sala.\n";
        } else {
            if (ind > cadeiras.size() || ind < 0)
                cout << "A cadeira nao existe, informe outra.\n";
            else if (cadeiras[ind] != nullptr) {
                cout << "A cadeira ja esta reservada.\n";
            } else 
                cadeiras[ind] = cliente;
        }
    }

    void cancelar(string id) {
        for (int i = 0; i < (int) cadeiras.size(); i++) {
            if (cadeiras[i] != nullptr && cadeiras[i]->getId() == id) {
                cadeiras[i] = nullptr;
            }     
        }
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Sala& sala) {
        os << "[";
        for (int i = 0; i < (int) sala.cadeiras.size(); i++) {
            if (sala.cadeiras[i] == nullptr)
                os << " - ";
            else 
                os << "Cadeira " << i << ": " << *sala.cadeiras[i] << " ";
        }
        os << "]";

        return os;
    }

};

int main() {
    system("cls");
    Sala cinema(5);

    //ADICIONANDO UMA PESSOA NA SALA
    cout << cinema << "\n";
    cinema.reservar(make_shared<Cliente>("Daniel", 2222), 0);
    cout << cinema << "\n\n";
  
    //ADICIONANDO ALGUEM NA MESMA CADEIRA
    cout << cinema << "\n";
    cinema.reservar(make_shared<Cliente>("Islane", 2212), 0);
    cinema.reservar(make_shared<Cliente>("Islane", 2212), 2);
    cout << cinema << "\n\n";

    //CANCELANDO RESERVA
    cinema.cancelar("Daniel");
    cout << cinema << "\n";
}