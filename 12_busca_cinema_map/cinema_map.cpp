#include <iostream>
#include <list>
#include <vector>
#include <memory>
#include <unordered_map>

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
    unordered_map<int, shared_ptr<Cliente>> cadeiras;
public:
    Sala() {
    }

    void reservar(shared_ptr<Cliente> cliente, int ind) {  
        auto it = cadeiras.find(ind);
        if (it == cadeiras.end()) {
            cadeiras[ind] = cliente;
        } else {
            if(cadeiras[ind] == nullptr) 
               cadeiras[ind] = cliente;
            else 
               cout << "O cliente ja esta na sala.\n";
        }
    
    }

    void cancelar(string id) {
        for (auto cliente : cadeiras) {
            if (cliente.second->getId() == id) {
                cadeiras[cliente.first] = nullptr;
            }     
        }
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Sala& sala) {
        os << "[";
        for (auto cadeira : sala.cadeiras) {
            if (cadeira.second == nullptr)
                os << " - ";
            else 
                os << "Cadeira " <<  ": " << *cadeira.second << " ";
        }
        os << "]";

        return os;
    }

};

int main() {
    system("cls");
    Sala cinema;

    //ADICIONANDO UMA PESSOA NA SALA
    cout << cinema << "\n";
    cinema.reservar(make_shared<Cliente>("Daniel", 2222), 1);
    cout << cinema << "\n\n";
  
    //ADICIONANDO ALGUEM NA MESMA CADEIRA
    cout << cinema << "\n";
    cinema.reservar(make_shared<Cliente>("Islane", 2212), 1);
    cinema.reservar(make_shared<Cliente>("Islane", 2212), 2);
    cout << cinema << "\n\n";

    //CANCELANDO RESERVA
    cinema.cancelar("Daniel");
    cout << cinema << "\n";
}