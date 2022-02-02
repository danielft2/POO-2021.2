#include <iostream>
#include <vector>

using namespace std;

class Funcionario {
private:
    string name {""};
    float wage {0.f}; 
    float extraHour {0};
    vector<string> ponto;
public:
    Funcionario(string name, float wage): name{name}, wage{wage}, ponto(2, "-") {       
    }

    virtual ~Funcionario() {
    }

    virtual string getName() const {
        return this->name;
    }

    virtual void setName(string name) {
        this->name = name;
    }

    virtual void setWage(float wage) {
        this->wage = wage;
    }

    virtual void setHoraExtra(int extraHours) {
        this->extraHour = extraHours;
    }

    virtual void baterPontoEntada(string hour) {
        if (hour == "07:55") {
            cout << "Ponto batido, bom trabalho\n";
            ponto[0] = hour;
        }
        else {
            cout << "Ponto fora do horario previsto.\n";
        }
    }

    virtual void baterPontoSaida(string hour) {
        if (hour == "16:55") {
            cout << "Ponto batido, boa viagem.\n\n";
            ponto[1] = hour;
        }
        else 
            cout << "Ponto fora do horário previsto.";
    }
    
    virtual void horaExtra(int hour) {
        this->extraHour =+ hour * 6.0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Funcionario& funcionario) {
        os << "Dados: ";
        os << funcionario.name << ":" << funcionario.wage << "R$" << "\n";
        os << "Hora extra: " << funcionario.extraHour << "R$" << "\n";
        os << "Ponto: ";
        os << "Entrada: " << funcionario.ponto[0] << " Saida: " << funcionario.ponto[1];
        return os;
    }
};

class Gerente : public Funcionario {
    int password {0};
    string type {""};
public: 
    Gerente(string name, string type, float wage, int pass): Funcionario(name, wage), password{pass}, type{type} {
    }

    virtual ~Gerente() {
    }

    virtual void horaExtra(int hour) {
        this->Funcionario::setHoraExtra(hour * 10);
    }

    virtual bool autenticPass(int pass) {
        if (pass == this->password) {
            cout << "Senha Autenticada.\n";
            return true;
        } else {
            cout << "Senha Nao Autenticada.\n";
            return false;
        }
    }

    virtual void supervisionar() {
        cout << "Setor supervisionado\n";
    }

    virtual string getType() {
        return this->type;
    }

    virtual string setType(string type) {
        this->type = type;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Gerente& gerente) {
        const Funcionario& funcionario = gerente;
        os << "Tipo: " << gerente.type << "\n";
        os << funcionario;
        return os;
    }
};

class GerenteFinanceiro : public Gerente {
    int securityKey {0};
public:
    GerenteFinanceiro(string name, string type, float wage, int pass, int key): Gerente(name, type, wage, pass) {
        this->securityKey = key;
    }

    virtual ~GerenteFinanceiro() {
    }

    virtual bool checkKey(int key) {
        if (key == this->securityKey) 
            return true;
        
        return false;
    }

    virtual void relatorioCustos(int custos, int valorBruto, int key) {
        if (checkKey(key)) {
            cout << "Valor liquido do mes: " << valorBruto - custos << "R$\n";
        } else {
            cout << "Acesso negado\n";
        }
    }

    virtual void emitirNotasFiscais(int key) {
        if (checkKey(key)) 
            cout << "Nota fiscal emitada\n";
        else 
           cout << "Acesso negado.\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const GerenteFinanceiro& gerenteFinanceiro) {
        const Gerente& gerente = gerenteFinanceiro;
        os << "\nChave de seguranca: " << gerenteFinanceiro.securityKey << "\n";
        os << gerente;
        return os;
    }
};


int main() {
    system("cls");
    GerenteFinanceiro daniel("Daniel", "Financeiro", 2200.87, 95795, 22);
    daniel.baterPontoEntada("07:55");
    daniel.supervisionar();
    daniel.relatorioCustos(5000, 10000, 22);
    daniel.horaExtra(22);
    daniel.baterPontoSaida("16:55");
    cout << daniel << "\n\n";

    Gerente& gerente = daniel;
    cout << gerente;
    gerente.horaExtra(22);
}