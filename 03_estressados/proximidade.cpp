#include <iostream>
#include <vector>
#include "testador.hpp"

using namespace std;

vector<int> absolute(vector<int> vet) 
{   
    vector <int> copia;
    for (int i = 0; i < (int) vet.size(); i++) {
        if (vet[i] < 0) {
            vet[i] = vet[i] * -1;
        }

        copia.push_back(vet[i]);
    }
    
    return copia;
}

int briga(const vector<int>& vet)
{
    vector<int> vetAbs = absolute(vet);
    int vezes {0}, size = vet.size();
    
    for (int i = 1; i < size; i++) {
        if(i <= size - 2) {
            if (vetAbs[i] > 50 && vetAbs[i - 1] > 30 && vetAbs[i + 1] > 30) 
                vezes++;
        }
    }
     
    return vezes;
}

vector<int> apaziguado(vector<int> vet) 
{   
    vector<int> vetAbs = absolute(vet);
    vector<int> posApaziguados;
    int vezes {0}, size = vet.size();

    for (int i = 1; i < size; i++) {
        if(i <= size - 2) {
            if (vetAbs[i] > 80 && (vetAbs[i - 1] < 10 || vetAbs[i + 1] < 10))
                posApaziguados.push_back(i);  
        }
    }
     
    return posApaziguados;
}

int main() 
{
    system("cls");

    cout << "testes briga(): " << "\n";
    testar(briga({22, 33, 4, 5, 6, 34, 55, 66}), {1});
    testar(briga({22, 65, 4, -43, -65, 34, 55, 66, -45, -55, -45}), {4});

    cout << "\n";
    
    cout << "testes apaziguados(): " << "\n";
    testar(apaziguado({22, 9, 85, -43, -65, 34, 55, 66, 90, -9}), {2, 8});
    testar(apaziguado({10, 80, -4, -89, -56, 2, 87, 97, 90, -9}), {3, 6, 8});


    return 0;
}