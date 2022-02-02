#include <iostream>
#include <vector>
#include "testador.hpp"

using namespace std;

vector<int> sozinhos(const vector<int>& vet) 
{    
    vector<int> solitarios;
    int vezes {0};
    for (int i : vet) {
        i = (i < 0) ? -i : i;
        for (int j : vet) {
            j = (j < 0) ? -j : j;
            if (i == j) 
                vezes++; 
        }

        if (vezes == 1)
            solitarios.push_back(i);

        vezes = 0;
    }

    return solitarios;
}

int maior_ocorrencias(vector<int> vet) 
{
    int vezes {0}, maior {0};
    for (int i : vet) {
        i = (i < 0) ? -i : i;
        for (int j : vet) {
            j = (j < 0) ? -j : j;
            if (i == j) 
                vezes++; 
        }

        if (vezes > maior) {
           maior = vezes;
        }
        vezes = 0;
    }

    return maior;
}

bool nao_existe(const vector<int>& vet, int& num)
{
    for (int i : vet) {
        if (i == num) {
            return false;
        }
    }

    return true;
}

vector<int> maior_recorrencia(const vector<int>& vet)
{
    int vezes {0}, maiorOcorrencia {2};
    vector<int> maiores;
    for (int i : vet) {
        i = (i < 0) ? -i : i;
        for (int j : vet) {
            j = (j < 0) ? -j : j;
            if (i == j) 
                vezes++; 
        }

        if (vezes > maiorOcorrencia) {
            maiorOcorrencia = vezes;
            maiores[0] = i;
        } else if (vezes == maiorOcorrencia) {
            if(nao_existe(maiores, i))
                maiores.push_back(i);
        }
        vezes = 0;
    }

    return maiores;
}

int main() 
{
    system("cls");

    cout << "testes sozinhos(): " << "\n";
    testar(sozinhos({1, 3, 4, 3, -3, -3}), {1, 4});
    testar(sozinhos({1, 3, 4, 3, -1, -3, -3, -2, 2, 2, 87}), {4, 87});
    testar(sozinhos({1, 3, 4, 3, -1, -3, -3, -5, -87, 87, 33, 33}), {4, 5});
    
    cout << "\n";

    cout << "testes maior_ocorrencia(): " << "\n";
    testar(maior_ocorrencias({1, 3, 4, 3, -1, -3, -3}), {4});
    testar(maior_ocorrencias({1, 3, 4, 3, -1, -3, -3, 1, -1}), {4});
    testar(maior_ocorrencias({1, 34, 54, -67, 22}), {1});

    cout << "\n";

    cout << "testes maior_recorrencia(): " << "\n";
    testar(maior_recorrencia({1, 3, 4, 5, -1, -5, -5, 3, -3}), {3, 5});
    testar(maior_recorrencia({1, 3, 4, 5, -1, -5, 6 -5, 3, -3, 1, 6, 22, 6, 6 }), {6});

    return 0;
}