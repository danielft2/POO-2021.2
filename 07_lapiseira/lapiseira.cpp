#include <iostream>
#include <vector>
#include <memory>
#include <utility>

using namespace std;

class Grafite {
public:
    float calibre;
    string dureza;
    int tamanho;

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
        if (grafite->calibre != this->calibre) {
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
        } else if (this->bico->tamanho <= 10) {
            cout << "Nao e mais possivel escrever com esse grafite.\n";
        } else {
            this->bico->desgastePorFolha();
            if (this->bico->tamanho < 10) {
                cout << "Nao houve grafite suficiente para terminar a folha.\n";
                int resto = 10 - this->bico->tamanho;
                this->bico->tamanho + resto;
            } else if (this->bico->tamanho == 10) {
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
    lapiseira.inserir(make_shared<Grafite>(0.5, "4B", 30));
    lapiseira.inserir(make_shared<Grafite>(0.7, "HB", 50));
    lapiseira.inserir(make_shared<Grafite>(0.5, "6B", 20));
    cout << lapiseira << "\n\n";

    //PUXANDO GRAFITE DA LAPISEIRA
    lapiseira.puxarGrafite();
    cout << lapiseira;
    lapiseira.puxarGrafite();
    cout << "\n";

    //REMOVENDO DO BICO
    cout << lapiseira << "\n";
    shared_ptr<Grafite> g = lapiseira.removerGrafite();
    cout << lapiseira << "\n\n";

    //ESCREVENDO COM O GRAFITE
    cout << lapiseira << "\n";
    lapiseira.puxarGrafite();
    lapiseira.escreveFolha();
    cout << lapiseira << "\n\n";
    
    //ESCREVENDO COM GRAFITE
    cout << lapiseira << "\n";
    lapiseira.escreveFolha();
    lapiseira.escreveFolha();
    cout << "\n";

    shared_ptr<Grafite> b = lapiseira.removerGrafite();
    cout << lapiseira << "\n";
    
    //GRAFITE ACABOU
    lapiseira.inserir(make_shared<Grafite>(0.5, "4B", 14));
    cout << lapiseira << "\n";
    lapiseira.puxarGrafite();
    cout << lapiseira << "\n";
    lapiseira.escreveFolha();
    cout << lapiseira << "\n";
}


