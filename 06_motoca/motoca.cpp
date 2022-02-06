#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pessoa
{
    string nome;
    int idade; 

    Pessoa(string nome = "", int idade = 0) :
        nome {nome}, idade {idade} {
    }

    string getNome() {
        this->nome;
    }

    int getIdade() {
        this->idade;
    }

    friend std::ostream& operator<<(std::ostream& os, const Pessoa& pessoa) {
        os << "Pessoa: " << "[" << pessoa.nome << ":" << pessoa.idade << "]" << "\n";
    }
};

bool confirma(Pessoa* pessoa, int& time) {
    if (pessoa->idade > 10 && time <= 0 ) {
        cout << "Tempo e idade fora de padrao.\n";
        return false;
    }

    if (pessoa->idade > 10) {
        cout << "Muito grande para andar de moto.\n";
        return false;
    } else if (time <= 0 ) {
        cout << "Voce nao tem tempo disponivel\n";
        return false;
    } 
       
    return true;
}

struct Motoca
{
    int potencia{0};
    int minutos {0};
    Pessoa* pessoa = nullptr;

    Motoca(int potencia) :
        potencia {potencia} {  
    }

    void subir(Pessoa* pessoa) {
        if (this->pessoa != nullptr) {
            cout << "ja existe alguem na moto.\n";
        } else {
            this->pessoa = pessoa;
        }       
    }
    
    Pessoa* descer() {
        if (this->pessoa == nullptr) {
            cout << "Nao tem ninguem na moto.\n";
            return nullptr;
        } else {
            Pessoa* copia = this->pessoa;
            this->pessoa = nullptr;
            return copia;
        } 
    }

    void comprarTempo(int time) {
        this->minutos = time + this->minutos;
    }

    void drive(int time) {
        if (this->pessoa != nullptr) {
            if (confirma(this->pessoa, this->minutos)) {
                int restante = this->minutos - time;
                if(restante < 0) {
                    cout << "Andou " << this->minutos << " e acabou o tempo.\n";
                    this->minutos = 0;
                } else {
                    this->minutos = restante;
                }  
            }      
        } else {
            cout << "A moto esta vazia\n";
        } 
    }

    void buzinar() {
        if (this->pessoa != nullptr) {
            cout << "p";
            for (int i = 0; i < this->potencia; i++)
                cout << "e";
            cout << "m";
        } else {
            cout << "A moto esta vazia.\n";
        }
    }

    Pessoa* getPesssoa() {
        return this->pessoa;
    }

    int getPotencia() {
        return this->potencia;
    }

    int getTempo() {
        return this->minutos;
    }

    friend std::ostream& operator<<(std::ostream& os, const Motoca& motoca) {
        os << "Potencia: " << motoca.potencia<< ", ";
        os << "Minutos: " << motoca.minutos << ", ";
        if (motoca.pessoa != nullptr)
            os << "Pessoa: " << "[" << motoca.pessoa->nome << ":" << motoca.pessoa->idade << "]" << "\n";
        else {
            os << "Pessoa: null\n";
        }
        return os;
    }
};

int main() {
    
    system("cls");
    Motoca* moto = new Motoca(1);
    
    cout << "SUBINDO E BUZINANDO\n";
    cout << *moto;
    moto->buzinar();
    Pessoa pessoa("Daniel", 8);
    moto->subir(&pessoa);
    cout << *moto;
    moto->buzinar();
    delete exchange(moto, nullptr);

    cout << "\n\n";

    cout << "SUBINDO E BUZINANDO\n";
    moto = new Motoca(5);
    cout << *moto;
    moto->subir(&pessoa);
    cout << *moto;
    moto->buzinar();
    delete exchange(moto, nullptr);

    cout << "\n\n";

    cout << "SUBINDO E TROCANDO\n";
    moto = new Motoca(7);
    cout << *moto;
    moto->subir(new Pessoa("Lucas", 5));
    Pessoa* lucas = moto->descer();
    cout << *lucas; 
    moto->descer();
    moto->subir(new Pessoa("Islane", 20));
    cout << *moto;
    delete exchange(moto, nullptr);

    cout << "\n\n";

    cout << "PASSEANDO\n";
    moto = new Motoca(7);
    moto->subir(new Pessoa("Suzana", 8));
    moto->drive(10);
    moto->comprarTempo(40);
    cout << *moto << "\n";

    return 0;
}
