#include <iostream>
#include <list>
#include <vector>
#include <memory>

using namespace std;

class Crianca {
private:
    string nome;
    int idade;
public:
    Crianca(string nome, int idade) : nome {nome}, idade {idade} {
    }

    string getNome() {
        return this->nome;
    }

    int getIdade() {
        return this->idade;
    }

    void setNome(string novoNome) {
        this->nome = novoNome;
    }

    void setIdade(int novaIdade) {
        this->idade = novaIdade;
    }

    friend std::ostream& operator<<(std::ostream& os, const Crianca& crianca) {
        os << crianca.nome << ":" << crianca.idade;
        return os;
    }
};

class PulaPula {
private:
    list<shared_ptr<Crianca>> espera;
    list<shared_ptr<Crianca>> pulando;
public:

    PulaPula() {
    }

    void insereCrianca(shared_ptr<Crianca> crianca) {
        espera.push_back(crianca);
    }

    bool pular() {
        if (espera.empty()) {
            cout << "Nao tem ninguem na fila de espera.\n";
            return false;
        }
            
        this->pulando.push_front(espera.front());
        this->espera.pop_front();
        return true;
    } 

    void sair() {
        if (pulando.empty()) {
            cout << "Nao tem ninguem no pula pula.\n";
        } else {
            this->espera.push_back(pulando.back());
            this->pulando.pop_back();
        }
    }

    shared_ptr<Crianca> papai_chegou(string nome) {
        int i = 0;
        for (auto crianca : pulando) {
            if (crianca->getNome() == nome) {
                pulando.erase(next(this->pulando.begin(), i));
                return crianca;
            }

            i++;
        }
        
        i = 0;

        for (auto crianca : espera) {
            if (crianca->getNome() == nome) {
                espera.erase(next(this->espera.begin(), i));
                return crianca;
            }

            i++;
        }

        return nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const PulaPula& pulaPula) {
        if (pulaPula.espera.empty()) {
            os << "=> " << "[ ] ";
        } else {
            os << "=> ";
            for (int i = (int) pulaPula.espera.size() - 1; i >= 0; i--) {
                shared_ptr<Crianca> copia = *next(pulaPula.espera.begin(), i);
                os << *copia << " ";
            }
        }

        if (pulaPula.pulando.empty()) {
            os << "=> " << "[ ] ";
        } else {
            os << "=> [";
            for (auto crianca : pulaPula.pulando) {
                os << *crianca << " ";
            }
            os << "]";
        }
        
        return os;
    }
};

int main() {
    system("cls");
    PulaPula pulaPula;

    //INSERINDO CRIANÇAS NA FILA DE ESPERA
    cout << pulaPula << "\n";
    pulaPula.insereCrianca(make_shared<Crianca>("Daniel", 10));
    pulaPula.insereCrianca(make_shared<Crianca>("islane", 6));
    pulaPula.insereCrianca(make_shared<Crianca>("luana", 8));
    cout << pulaPula << "\n\n";

    //COLOCANDO NO PULA PULA
    pulaPula.pular();
    cout << pulaPula << "\n";
    pulaPula.pular();
    cout << pulaPula << "\n\n";

    //SAINDO DO PULA PULA
    cout << pulaPula << "\n";
    pulaPula.sair();
    cout << pulaPula << "\n\n";

    //O PAPAI CHEGOU
    cout << pulaPula << "\n";
    auto c = pulaPula.papai_chegou("luana");
    cout << pulaPula << "\n\n";

    //TENTANDO PULAR SEM TER NINGUEM
    cout << pulaPula << "\n";
    pulaPula.pular();
    cout << pulaPula << "\n";
    pulaPula.pular();

}