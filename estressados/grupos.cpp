#include <iostream>
#include <vector>
#include "testador.hpp"

using namespace std;

bool naoExiste(const vector<int> vet, int num) 
{
    for (int i : vet) {
        if (num == i)
            return false;
    }

    return true;
}

int casais(const vector<int>& vet)
{
    int casais {0};
    for (int i : vet) {
        if (i < 0) {
            i = -i;
            for (int j : vet) {
                if (j > 0) {
                    (i == j) ? casais++ : casais;
                }
            } 
        } 
    }
    return casais;
}

int trios(const vector<int>& vet)
{
    vector<int> contados;
    for (int i : vet) {
        int vezes = {0};
        i = (i < 0) ? -i : i;
        for (int j : vet) {
            j = (j < 0) ? - j : j;
            if (i == j) {
                vezes++; 
            } 

            if (vezes == 3) {
                if (naoExiste(contados, i)) {
                    contados.push_back(i);
                }
                break;
            }  
        } 
    }

    return contados.size();
}

int main() 
{   
    system("cls");

    cout << "testes casais(): " << "\n";
    testar(casais({-2, 2, 33, 56, -78, 87, 22, 78}), 2);
    testar(casais({3, 2, 33, 56, -78, 87, 22, 78}), 1);
    testar(casais({-2, 2, 33, 56, -33, 87, -56, 78}), 3);

    cout << "\n";

    cout << "testes trios()> " << "\n";
    testar(trios({-2, 2, 45, 67, -45, -2, -3, 1, 45}), 2);
    testar(trios({-2, 34, 45, -34, -45, -2, -3, 1, 45, 34, -2}), 3);
    testar(trios({-2, 45, 67, -45, -2, -3, 1, 36, -1}), 0);
}