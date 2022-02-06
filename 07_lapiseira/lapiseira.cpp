#include <iostream>
#include <vector>
#include <memory>
#include <utility>

using namespace std;

class Grafite {
private:
    float calibre;
    string dureza;
    int tamanho;
public:
    Grafite(float calibre = 0, string dureza = "", int tamanho = 0) : 
        calibre {calibre}, dureza {dureza}, tamanho {tamanho} {
    }

    void desgastePorFolha() {
        if (this->dureza == "HB")
            this->tamanho--;
        else if (this->dureza == "2B")
            this->tamanho-=2;
        else if (this->dureza == "4B")
            this->tamanho-=4;
        else if (this->dureza == "6B")
            this->tamanho-=6;
    }

    float getCalibre() {
        return this->calibre;
    }

    string getDureza() {
        return this->dureza;
    }

    int getTamanho() {
        return this->tamanho;
    }

    void setTamanho(int tam) {
        this->tamanho = tam;
    }

    friend ostream& operator<<(ostream& os, const Grafite& grafite) {
        os << "[";
        os << grafite.calibre << ", ";
        os << grafite.dureza << ", ";
        os << grafite.tamanho;
        os << "]";
        return os;
    }
};

class Lapiseira {
public:
    shared_ptr<Grafite> bico = nullptr;
    vector<shared_ptr<Grafite>> tambor;
    float calibre;

    Lapiseira(float calibre) : calibre {calibre} {
    }
    
    bool inserir (shared_ptr<Grafite> grafite) {
        if (grafite->getCalibre() != this->calibre) {
            cout << "calibre nao compativel.\n";
            return false;
        }
        
        tambor.push_back(grafite);
        return true;
    }

    bool puxarGrafite() {
        if (this->bico != nullptr) {
            cout << "\nJa existe um grafite no bico, remova primeiro.\n";
            return false;
        }
        
        this->bico = this->tambor.front();
        this->tambor.erase(this->tambor.begin());
        return true;
    }

    shared_ptr<Grafite> removerGrafite() {
        if (this->bico == nullptr) {
            cout << "Nao existe nenhum grafite no bico.\n";
            return nullptr;
        }

        return exchange(this->bico, nullptr);
    }

    void escreveFolha() {
        if (this->bico == nullptr) {
            cout << "Nao existe um grafite no bico.\n";
        } else if (this->bico->getTamanho() <= 10) {
            cout << "Nao e mais possivel escrever com esse grafite.\n";
        } else {
            this->bico->desgastePorFolha();
            if (this->bico->getTamanho() < 10) {
                cout << "Nao houve grafite suficiente para terminar a folha.\n";
                int resto = 10 - this->bico->getTamanho();
                this->bico->setTamanho(resto + this->bico->getTamanho());
            } else if (this->bico->getTamanho() == 10) {
                cout << "Grafite acabou.\n";
            }     
        }   
    }

    friend std::ostream& operator<<(std::ostream& os, Lapiseira& lapiseira) {
        os << "calibre: " << lapiseira.calibre << ", ";
        os << "bico: ";
        if (lapiseira.bico != nullptr)
            os << *lapiseira.bico << ", ";
        else 
            os << "[]" << ", ";
        os << "tambor: " << "{";
        if (!lapiseira.tambor.empty()) {
            for (auto grafite : lapiseira.tambor) {
                os << *grafite;
            }
        }
        os << "}";
        return os;
    }

};

int main() {
    system("cls");
    Lapiseira lapiseira(0.5);
    
    //INSERINDO GRAFITE
    cout << lapiseira << "\n";
    lapiseira.inserir(make_shared<Grafite>(0.5, "4B", 14));
    lapiseira.inserir(make_shared<Grafite>(0.5, "4B", 20));
    lapiseira.puxarGrafite();
    
    lapiseira.escreveFolha();
    cout << lapiseira << "\n";
    lapiseira.escreveFolha();
    cout << lapiseira << "\n";

    auto grafite = lapiseira.removerGrafite();
    lapiseira.puxarGrafite();
    cout << lapiseira << "\n";
}


