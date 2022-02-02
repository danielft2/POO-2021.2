#include <iostream>
#include <vector>
#include "testador.hpp"

using namespace std;

bool formou_time(const vector<int>& vet) 
{   
    if (vet[0] < 0) {
        for (int i: vet) {
            if (i > 0) 
                return false;
        }

        return true;
    } else {
        for (int i: vet) {
            if (i < 0) 
                return false;
        }

        return true;
    }
}

int quantos_times(const vector<int>& vet) 
{   
    vector<int> time;
    int times {0}, j {0};

    for (int i = 0; i < vet.size(); i++) { 
        time.push_back(vet[i]); 
        int size = vet.size() - 1, k = i;
        for(k; k < size; k++) { 
            j = k + 1; 
            int tam = j + 1;
            for (j; j < tam; j++) { 
                time.push_back(vet[j]); 
            }
            
            int sinal = formou_time(time);
            if (sinal)
                times++;
            j = 0;
        }
        
        time.clear();
    }
        
    return times;
}

vector<int> maior_time(const vector<int>& vet)
{
    vector<int> time;
    vector<int> timeMaior;
    int j {0};

    for (int i = 0; i < vet.size(); i++) { 
        time.push_back(vet[i]); 
        int size = vet.size() - 1, k = i;
        for(k; k < size; k++) { 
            j = k + 1; 
            int tam = j + 1;
            for (j; j < tam; j++) { 
                time.push_back(vet[j]); 
            }
            
            int sinal = formou_time(time);
            if (sinal) {
                if (time.size() > timeMaior.size()) {
                    timeMaior.clear();
                    timeMaior.assign(time.begin(), time.end());
                }
            }
                
            j = 0;
        }
        
        time.clear();
    }

    return timeMaior;
}

int sozinhos(const vector<int>& vet)
{
    int solitario {0};
    for (int i = 0; i < (int) vet.size(); i++) {
        if (vet[i] < 0) {
            
            if (i == 0) {
                if (vet[i + 1] > 0) 
                    solitario++;
            } else if (i == vet.size() - 1) {
                if (vet[i - 1] > 0)
                    solitario++;
            } else {
                if (vet[i - 1] > 0 && vet[i + 1] > 0)
                    solitario++;
            }    
        }
        else {
            if (i == 0) {
                if (vet[i + 1] < 0) 
                    solitario++;
            } else if (i == vet.size() - 1) {
                if (vet[i - 1] < 0)
                    solitario++;
            } else {
                if (vet[i - 1] < 0 && vet[i + 1] < 0)
                    solitario++;
            }    
        }
    }   

    return solitario;
}

int main() 
{
    system("cls");

    cout << "testes quantos_times(): " << "\n";
    testar(quantos_times({ -22, -45, -55, 98, 89}), 4);
    testar(quantos_times({ -22, -99, -55, -55, -32, -21, -22}), 21);

    cout << "\n";

    cout << "testes maior_time(): " << "\n";
    testar(maior_time({ -22, -45, -55, 98, 89}), {-22, -45, -55});
    testar(maior_time({ -22, -45, -55, 98, 89, 87, 22}), {98, 89, 87, 22});

    cout << "\n";

    cout << "testes sozinhos(): " << "\n";
    testar(sozinhos({22, 33, -55, 55, 44, -98}), 2);
    testar(sozinhos({22, 33, -55, -88, 44, 23, 89}), 0);
    testar(sozinhos({22, -78, -55, 55, 44, -98, -78}), 1);
   
    return 0;
}