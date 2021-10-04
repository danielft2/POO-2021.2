#include <iostream>
#include <vector>
using namespace std;

int procurar_menor(vector<int> fila) 
{
    int menor = 100;
    for (int i : fila) {
        if (i < menor) {
            menor = i;
        }
    }
    
    return (fila.size() > 0) ? menor : 0;
}

int procurar_menor_pos(vector<int> fila) 
{
    int menor = 100, pos = 0;
    for (int i = 0; i < fila.size(); i++) {
        if (fila[i] < menor) {
            menor = fila[i];
            pos = i;
        }
    }
    
    return (fila.size() > 0) ? pos : -1;
}

int procurar_menor_pos_apartir(vector<int> fila, int posP) 
{   
    int menor = 100, pos = 0;
    for (int i = posP; i < fila.size(); i++) {
        if (fila[i] < menor) {
            menor = fila[i];
            pos = i;
        }
    }
    
    return (fila.size() > 0) ? pos : -1;
}

int procurar_melhor_posicao_se(vector<int> fila) 
{   
    int menor = 100, pos = -1;
    for (int i = 0; i < fila.size(); i++) {
        if (fila[i] > 0 && fila[i] < menor ) {
            menor = fila[i];
            pos = i;
        }
    }
    
    return (fila.size() > 0) ? pos : -1;
}

int main()
{   
    // MENOR VALOR TESTE:
    cout << "Menor valor: " << procurar_menor({5, 3, -1, -50, -1, -99}) << "\n\n";

    // PROCURAR POSIÇÃO DO MENOR TESTE: 
    cout << "Posicao do Menor: " << procurar_menor_pos({5, 3, -1, -50, -1, -99}) << "\n\n";
   
    //POSIÇÃO DO MENOR APOS P TESTE:
    cout << "Posicao do menor apos P: " << procurar_menor_pos_apartir({5, 3, -1, -50, -1, 10}, 3) << "\n\n";
    
    //PROCURAR MELHOR SE TESTES: 
    cout << "Posicao Homem mais calmo: " << procurar_melhor_posicao_se({5, 3, -1, -50, -1, -99}) << "\n";
    cout << "Posicao Homem mais calmo: " << procurar_melhor_posicao_se({-1, -50, -1, -99}) << "\n";
}