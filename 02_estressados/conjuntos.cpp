#include <iostream>
#include <vector>
#include "testador.hpp"

using namespace std;

vector<int> exclusivos(const vector<int>& vet)
{   
    bool pode_add = false;
    vector<int> nova_lista {};

    nova_lista.push_back(vet[0]);
    for (int i : vet) {
        for (int j : nova_lista) {
            if (i != j) {
                pode_add = true;
            } else {
                pode_add = false;
                break;
            }       
        }

        if (pode_add)
            nova_lista.push_back(i);
    }
    
    return nova_lista;
}

vector<int> diferentes(const vector<int>& vet) 
{
    bool pode_add = false;
    vector<int> nova_lista {};

    nova_lista.push_back(vet[0]);
    for (int i : vet) {
        i = (i < 0) ? -i : i;
        for (int j : nova_lista) {
            if (i != j) {
                pode_add = true;
            } else {
                pode_add = false;
                break;
            }       
        }

        if (pode_add)
            nova_lista.push_back(i);
    }
    
    return nova_lista;
}

vector<int> abandonados(const vector<int>& vet)
{
    vector<int> abandoned {};
    vector<int> excluidos {};

    for (int i : vet) {
        if (excluidos.empty()) {
            excluidos.push_back(i);
        }else {
            bool nao_tem = false;
            for (int j : excluidos) {
                if (i == j) {
                    abandoned.push_back(i);
                    nao_tem = false;
                    break;
                } else {
                    nao_tem = true;
                }
            }

            if (nao_tem)
                excluidos.push_back(i);
        }
    }

    return abandoned;
}


int main() 
{
    system("cls");

    cout << "testes exclusivos(): " << "\n";
    testar(exclusivos({1, 3, 4, 3, -1, -2, -2}), {1, 3, 4, -1, -2});
    testar(exclusivos({1, 2, 2, -99, -1, -77, -2}), {1, 2, -99, -1, -77, -2});
    cout << "\n";

    cout << "testes diferentes(): " << "\n";
    testar(diferentes({1, 3, 4, 3, -1, -2, -2}), {1, 3, 4, 2});
    testar(diferentes({1, -1, 4, -4, -5, 5, 2}), {1, 4, 5, 2});
    cout << "\n";

    cout << "testes abandonados(): " << "\n";
    testar(abandonados({1, 3, 4, 3, -1, -2, -2, 3, 3}), {3, -2, 3, 3});
    testar(abandonados({1, 3, 4, -1, -2, 5}), { });

    return 0;
}