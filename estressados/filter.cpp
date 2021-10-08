#include <iostream>
#include <vector>
#include "testador.hpp"

using namespace std;

vector<int> clone(const vector<int>& vet)
{
    vector<int> vet_copia {};
    for (int i : vet) {
        vet_copia.push_back(i);
    }

    return vet_copia;
}

vector<int> pegar_homens(const vector<int>& vet) 
{
    vector<int> so_homens {};
    for (int i : vet) {
        if (i > 0)
            so_homens.push_back(i);
    }

    return so_homens;
}

vector<int> pegar_calmos(const vector<int>& vet)
{
    vector<int> stress_menor { };
    for (int i : vet) {
        i = (i < 0) ? -i : i;
        if (i < 10)
            stress_menor.push_back(i);
    }

    return stress_menor;
}

vector<int> pegar_mulheres_calmas(const vector<int>& vet) 
{
    vector<int> mulheres_calmas { };
    for (int i : vet) {
        if (i < 0 && i > - 10)
            mulheres_calmas.push_back(i);
    }

    return mulheres_calmas;
}

int main() 
{   
    system("cls");

    cout << "testes clone(): " << "\n";
    testar(clone({2, 4, 5, 6, 6, 8, 8}), {2, 4, 5, 6, 6, 8, 8 });
    testar(clone({-4, 5, 6, 5,}), {-4, 5, 6, 5});
    testar(clone({1, 2, 3, 4, 5, 6}), {1, 2, 3, 4, 5, 6});

    cout << "testes pegar_homens(): " << "\n";
    testar(pegar_homens({-1, -5, -44, -66, 2}), {2});
    testar(pegar_homens({10, -4, 20, -55, 99}), {10, 20, 99});
    testar(pegar_homens({-10, -4, -77, -55, -33}), { });

    cout << "testes pegar_calmos(): " << "\n";
    testar(pegar_calmos({-9, -10, 11, 8, 7, 5}), {9, 8, 7, 5});
    testar(pegar_calmos({-11, -10, 11, 33, 52,12}), { });
    testar(pegar_calmos({-9, -10, 11, 24, 77, 5}), {9, 5});

    cout << "testes pegar_mulheres_calmas(): " << "\n";
    testar(pegar_mulheres_calmas({-9, -8, -6, -11, 44, 55, 66, 10}), {-9, -8, -6});
    testar(pegar_mulheres_calmas({-10, 22, -16, 44, -11, 10, 45, 11}), { });
    testar(pegar_mulheres_calmas({-8, -7, -99, -11, 3, 5, 66, -2}), {-8, -7, -2});

    return 0;
}