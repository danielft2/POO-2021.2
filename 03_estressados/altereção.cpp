#include <iostream>
#include <vector>
#include "testador.hpp"

using namespace std;

void remove(vector<int>& vet, int pessoa) 
{   
    bool removido = false;
    for (int i = 0; i < (int) vet.size(); i++) {
        if (vet[i] == pessoa) {
            vet.erase(vet.begin() + i);
            removido = true;
        } 
    }

    if (removido) {
        cout << vet << "\n";
        cout << "Pessoa Removida: " << pessoa;
    } else {
        cout << "Pessoa nao encontrada";
    }
    cout << "\n\n";
}

void insert(vector<int>& vet, int pos, int pessoa) 
{   
    vector<int> aux = vet;
    if (pos > vet.size() || pos < 0) {
        cout << "Posicao invalida.";
    } else {
        vet.emplace(vet.begin() + pos, pessoa);
        cout << "adicionando: " << pessoa << "\n";
        cout << "Antes: " << aux << "\n";
        cout << "Depois: " << vet << "\n\n";

    }
}

vector<int> dance(vector<int>& vet)
{   
    vector<int> copia = vet;
    for (int i = 0; i < (int) vet.size(); i++) {
        for (int j = 0; j < (int) vet.size() - 1; j++) {
            copia[j] = (copia[j] < 0) ? -copia[j] : copia[j];
            if (copia[j] == copia[j + 1]) {
                vet.erase(vet.begin() + j);
                vet.erase(vet.begin() + j);
                copia.clear();
                copia = vet;
            }
        }
    }

    return vet;
}

int main() 
{
    system("cls");

    vector<int> vet1 {1, 22, -22, -1, 56, 5,};
    vector<int> vet2 {-78, 2, -45, 4, -87, 1};
    vector<int> vet3 {1, 55, 56, -99, 8, 78};
    vector<int> vet4 {6, 5, 4, 3, 2, 1, -90};
    vector<int> vet5 {6, 5, 44, -44, -5, 1};
    vector<int> vet6 {6, 6, -80, -44, -54, 54, 87, -2, 2};

    cout << "testes remove(): " << "\n";
    remove(vet1, -56);
    remove(vet2, -45);

    cout << "testes insert(): " << "\n";
    insert(vet3, 3, 90);
    insert(vet4, 5, -44);

    cout << "testes dance(): " << "\n";
    testar(dance(vet5), {6, 1});
    testar(dance(vet6), {-80, -44, 87});

    return 0;
}