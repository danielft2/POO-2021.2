#include <iostream>
#include <vector>
#include <ctime>
#include "testador.hpp"

using namespace std;

vector<int> inverte_com_copia(const vector<int>& vet) 
{
    vector<int> invertido { };
    for (int i = (int) vet.size() - 1; i >= 0; i--) {
        invertido.push_back(vet[i]);
    }

    return invertido;
}

void inverte_inplace(vector<int>& vet) 
{  
    int size = vet.size(); 
    for (int i = 0; i < (int) vet.size(); i++) {
        int aux {0}, num_fixado = vet[0];
        for (int j = 1; j < size; j++) {
            aux = vet[j]; 
            vet[j] = num_fixado;  
            vet[j - 1] = aux; 
        }
        --size;
    }
}

int sortear(const vector<int>& vet) 
{   
    int pos = rand() % vet.size();
    return vet[pos];
}

void embaralhar(vector<int>& vet) 
{   
    int size = vet.size();
    for (int i = 0; i < (int) vet.size(); i++) {
        int pos = rand() % vet.size();
        swap(vet[i], vet[pos]);
    }
}

void ordenar(vector<int>& vet) 
{   
    int j {0};
    int troca {0};

    for (int i = 0; i < (int) vet.size(); i++) {
        int menor {vet[i]}, pos_menor {-1};
        j = j + i;
        for ( j < (int) vet.size(); j++;) {
            if (vet[j] < menor) {
                menor = vet[j]; 
                pos_menor = j; 
                troca++; 
            } 
        }

        j = 0;
        if (troca > 0) {
            swap(vet[i], vet[pos_menor]);
            troca = 0;
        }
           
    }

}

int main()
{   
    system("cls");
    srand(time(0));

    cout << "testes do invete_com_copia(): " << "\n";
    testar(inverte_com_copia({1, 2, 3, 4, 5, 6}), {6, 5, 4, 3, 2, 1});
    testar(inverte_com_copia({8, -12, -44, 96, 4, 5}), {5, 4, 96, -44, -12, 8});
    testar(inverte_com_copia({-1, -4, -6, -8, -9}), {-9, -8, -6, -4, -1});
    cout << "\n";

    vector<int> vet1 {1, 2, 3, 4, 5, 99, -44 };
    vector<int> vet2 {-78, 2, -45, 4, -87, 1};
    vector<int> vet3 {1, 55, 56, -99, 8, 78};
    vector<int> vet4 {6, 5, 4, 3, 2, 1};
    vector<int> vet5 {-87, 4, -45, 2, -78, 98, 77, -22, 28, 56};

    cout << "testes do reverter_inplace(): " << "\n";
    cout << "Original: " << vet1 << "\n";
    inverte_inplace(vet1);
    cout << "Invertido: " << vet1 << "\n\n";
    
    cout << "Original: " << vet2 << "\n";
    inverte_inplace(vet2);
    cout << "Invertido: " << vet2 << "\n\n";

    cout << "teste sortear(): " << "\n";
    cout << vet5 << "\n";
    cout << "numero sorteado: " << sortear(vet5) << "\n\n";

    cout << "teste embaralhar(): " << "\n";
    cout << "Original: " << vet3 << "\n";
    embaralhar(vet3);
    cout << "Embaralhado: " << vet3 << "\n\n";
    
    cout << "teste ordernar(): " << "\n";
    cout << "Original: " << vet2 << "\n";
    ordenar(vet2);
    cout << "Ordenado: " << vet2;

    return 0;
}