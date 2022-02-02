#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

bool existe(vector<int> fila, int valor)
{
    for (int i : fila) {
        if (i == valor) {
            return true;
        }
    }

    return false;
}

int contar(vector<int> fila, int valor) 
{
    int vezes = 0;
    for (int i : fila) {
        if (i == valor) {
            vezes++;
        }
    }

    return vezes;
}

int procurar_valor(vector<int> fila, int valor) 
{
    for (int i = 0; i < (int) fila.size(); i++) {
        if (fila[i] == valor) {
            return i;
        }
    }
    
    return -1;
}

int procuar_valor_apos(vector<int> vet, int valor, int posInicial)
{
    for (int i = posInicial; i < (int) vet.size(); i++) {
        if (vet[i] == valor) {
            return i;
        }
    }

    return -1;
}

int main()
{   
    system("cls");
    // EXISTE TESTES:
    cout << "Encontrado: " << existe({-1, -50, -99}, -1) << "\n";
    cout << "Encontrado: " << existe({-1, -50, -99}, 10) << "\n\n";
    
    // CONTAR TESTES:
    cout << "Numero de vezes: " << contar({-1, -50, -1, -99}, -1) << "\n";
    cout << "Numero de vezes: " << contar({-1, -50, -1, -99}, 10) << "\n\n";

    // POSICAÇÃO TESTES:
    cout << "Posicao: " << procurar_valor({-1, -50, -1 -99}, -50) << "\n";
    cout << "Posicao: " << procurar_valor({-1, -50, -1 -99}, 10) << "\n\n";

    // POSIÇÃO APOS TESTES: 
    cout << "Posicao_apos: " << procuar_valor_apos({5, 3, -1, -50, -1, -99}, -1, 0) << "\n";
    cout << "Posicao_apos: " << procuar_valor_apos({5, 3, -1, -50, -1, -99}, -1, 3) << "\n";
    cout << "Posicao_apos: " << procuar_valor_apos({5, 3, -1, -50, -1, -99}, -1, 4) << "\n";
}