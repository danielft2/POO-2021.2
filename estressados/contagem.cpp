#include <iostream>
#include <vector>

using namespace std;

float calcular_stress_medio(vector<int> fila)
{   
    float soma = 0;
    for (int i : fila) {
        if (i < 0) {
            i*=-1;
            soma+=i;
        } else {
            soma+=i;
        }
    }

    return (fila.size() > 0) ? (soma / fila.size()) : 0;
}

string mais_homem_ou_mais_mulher(vector<int> fila)
{
    int homem = 0, mulher = 0;
    for (int i : fila) {
        (i > 0) ? homem++ : mulher++;
    }
    
    if (fila.size() > 0)
        return (homem > mulher) ? "Homem" : (homem < mulher) ? "Mulher" : "Empate";
    else
        return "Lista Vazia";
}

string qual_metade_eh_mais_estresada(vector<int> fila)
{
    int primeira = 0, segunda = 0;

    for (int i = 0; i < fila.size(); i++) {
        (fila[i] < 0) ? fila[i]*=-1 : fila[i];

        if (i < (fila.size() / 2))
            primeira+=fila[i];
        else 
            segunda+=fila[i];
    }
    
    if (fila.size() > 0)
        return (primeira > segunda) ? "Primeira" : (primeira < segunda) ? "Segunda" : "Empate";
    else 
        return "Lista vazia";
}

string homens_sao_mais_estressados_que_mulheres(vector<int> fila)
{
    float stress_homem = 0, stress_mulher = 0;
    int numHomem = 0, numMulher = 0;

    for (int i : fila) {
        if (i > 0) {
            stress_homem+=i;
            numHomem++;
        } else {
            i*=-1;
            stress_mulher+=i;
            numMulher++;
        }       
    }
    
    stress_homem = stress_homem / numHomem;
    stress_mulher = stress_mulher / numMulher;

    if (fila.size() > 0)
        return (stress_homem > stress_mulher) ? "Homem" : (stress_homem < stress_mulher ) ? "mulher" : "empate"; 
    else 
        return "Lista vazia";
}

int main()
{   
    system("cls");
    
    // STRESSE MEDIO TESTES:
    cout.precision(3);
    cout << "Stress Medio: " << calcular_stress_medio({5, 3, -1, -50, -1, -99}) << "\n";
    cout.precision(3);
    cout << "Stress Medio: " << calcular_stress_medio({-8, 10, -1, -50}) << "\n\n";

    // MAIS HOMENS OU MAIS MULHERES TESTES: 
    cout << "Mais homens ou mais mulheres: " << mais_homem_ou_mais_mulher({5, 3, -1, -50, -1, -99}) << "\n";
    cout << "Mais homens ou mais mulheres: " << mais_homem_ou_mais_mulher({5, 3, 1, -50, -1, -99}) << "\n";
    cout << "Mais homens ou mais mulheres: " << mais_homem_ou_mais_mulher({5, 3, 1, -50, -1, 99}) << "\n\n";
    
    // QUAL METADE É MAIS ESTRESSADA TESTES:
    cout << "Metade mais estressada: " << qual_metade_eh_mais_estresada({5, 3, -1, -50, -1, -99}) << "\n";
    cout << "Metade mais estressada: " << qual_metade_eh_mais_estresada({50, 98, 2, -50, -1, -99}) << "\n";
    cout << "Metade mais estressada: " << qual_metade_eh_mais_estresada({-51, 99, 1, -50, -1, -99}) << "\n\n";
    
    // MAIS ESTRESSADO TESTES: 
    cout << "Mais estressados: " << homens_sao_mais_estressados_que_mulheres({5, 3, 1, -50, -1, -99}) << "\n";
    cout << "Mais estressados: " << homens_sao_mais_estressados_que_mulheres({99, 67, 45, -50, -1, 99}) << "\n";
    
    return 0;
}