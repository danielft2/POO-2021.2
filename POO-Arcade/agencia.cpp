#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>

using namespace std;

class Conta {
protected:
    float saldo {0.0};
    string idCliente;
    int id;
    string tipo {""};
public: 
    Conta(int id = -1, string idCliente = "") : id{id}, idCliente{idCliente} {
    }

    virtual void deposito(float valor) {
        if (valor > 0) {
            this->saldo = valor;
        } else {
            cout << "Erro deposito: Insira um valor valido.\n";
        }
    }

    virtual void transferencia(shared_ptr<Conta> OutraConta, float valor) {
        if (OutraConta == nullptr) {
            cout << "A conta nao existe, informe outra.\n";
        } else if (valor <= 0) {
            cout << "Informe um valor valido.\n";
        } else {
            if (this->saldo >= valor) {
                OutraConta->saldo += valor;
                this->saldo -= valor;
            } else {
                cout << "Erro transferencia: Saldo insuficiente.\n";
            }          
        }
    }

    virtual void saque(float valor) {
        if (this->saldo >= valor) {
            this->saldo = this->saldo - valor;
        } else {
            cout << "Erro saque: Saldo insuficiente\n";
        }
    }

    virtual void atualizacaoMensal() = 0;

    float getSaldo() {
        return this->saldo;
    }

    string getIdCliente() {
        return this->idCliente;
    }

    int getId() {
        return this->id;
    }

    string getTipo() {
        return this->tipo;
    }

    friend std::ostream& operator<<(std::ostream& os, const Conta& conta) {
        os << conta.id << " : " << conta.idCliente <<  " : " << "R$" << conta.saldo <<  " : " << conta.tipo << "\n";
        return os;
    }
};

class ContaPoupanca : public Conta {
public:
    ContaPoupanca(int id, string idCliente) : Conta(id, idCliente) {
        this->tipo = "CP";
    }

    void atualizacaoMensal() {
        if (this->saldo > 0)
            this->saldo = (this->saldo * 0.01) + this->saldo;
        else 
            this->saldo += 0.01;
    }

    friend std::ostream& operator<<(std::ostream& os, const ContaPoupanca& contaPoupanca) {
        const Conta& conta = contaPoupanca;
        os << conta;
        return os;
    }
};

class ContaCorrente : public Conta {
public:
    ContaCorrente(int id, string idCliente) : Conta(id, idCliente) {
        this->tipo = "CC";
    }
 
    void atualizacaoMensal() {
        this->saldo -= 20;
    }

    friend std::ostream& operator<<(std::ostream& os, const ContaCorrente& contaCorrente) {
        const Conta& conta = contaCorrente;
        os << conta;
        return os;
    }
};

class Cliente {
private:
    vector<shared_ptr<Conta>> contas;
    string idCliente {""};
public:
    Cliente(string idCliente) : idCliente{idCliente} {
    }

    void addConta(shared_ptr<Conta> conta) {
        contas.push_back(conta);
    }

    vector<shared_ptr<Conta>> getContas() {
        return this->contas;
    }

    string getIdCliente() {
        return this->idCliente;
    }

    void setIdCliente( string novoIdCliente) {
        this->idCliente = novoIdCliente;
    }

    void setContas(vector<shared_ptr<Conta>> contas) {
        this->contas.clear();
        for (auto& conta : contas) {
            this->contas.push_back(conta);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Cliente& cliente) {
        os << cliente.idCliente << " ";
        for (auto conta : cliente.contas) {
            os << "| " << conta->getId() << " |";
        }
        os << "\n";
        return os;
    }
};  

class AgenciaBancaria {
private:
    vector<shared_ptr<Conta>> contas;
    vector<shared_ptr<Cliente>> clientes;
    int proximoIdConta {0};
    int numCliente {0};

    shared_ptr<Conta> getConta(int id) {
        for (auto& conta : contas) {
            if (conta->getId() == id)
                return conta;
        }
         
        return nullptr;
    }

    bool buscaCliente(string idCliente) {
        for (auto cliente : clientes) {
            if (cliente->getIdCliente() == idCliente)
               return true;
        }

        return false;
    }

    void criarCliente(string idCliente) {
        clientes.push_back(make_shared<Cliente>(idCliente));
        if (this->proximoIdConta != 0) {
            this->proximoIdConta++;
        }
        clientes[numCliente]->addConta(make_shared<ContaCorrente>(this->proximoIdConta, idCliente));
        this->proximoIdConta++;
        clientes[numCliente]->addConta(make_shared<ContaPoupanca>(this->proximoIdConta, idCliente));

        for (auto& conta : clientes[numCliente]->getContas()) {
            contas.push_back(conta);
        }

        this->numCliente += 1;
    }

public:
    AgenciaBancaria() {
    }

    void addCliente(string idCliente) {     
        if (buscaCliente(idCliente)) {
            cout << "O cliente ja existe\n";
        } else {
            criarCliente(idCliente); 
        }
    }

    void deposito(int id, float valor) {
        auto conta = this->getConta(id);
        if (conta != nullptr) {
            conta->deposito(valor);
        } else {
            cout << "Conta nao encontrada\n";
        }

    }

    void saque(int id, float valor) {
        auto conta = this->getConta(id);
        if (conta != nullptr) {
            conta->saque(valor);
        } else {
            cout << "Conta nao encontrada.\n";
        }
    }

    void transferencia(int contaDe, int contaPara, float valor) {
        auto contaRe = this->getConta(contaDe);
        auto contaDes =  this->getConta(contaPara);

        if (contaRe != nullptr && contaDes != nullptr) {
            contaRe->transferencia(contaDes, valor);
        } else {
            cout << "Insira contas validas.\n";
        }
    }

    void atualizacaoMensal() {
        for (auto& conta : contas) {
            conta->atualizacaoMensal();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const AgenciaBancaria& agencia) {
        os << "----CLIENTES----" << "\n";
        for (auto cliente : agencia.clientes) {
            os << "- "<< *cliente;
        }

        os << "\n----CONTAS----" << "\n";
        for (auto conta : agencia.contas) {
            os << *conta;
        }

        return os;
    }
};

int main() {
    system("cls");
    AgenciaBancaria bank;
    bank.addCliente("Daniel");
    bank.addCliente("Luana");
    bank.deposito(1, 1200.55);
    cout << bank << "\n";

    bank.saque(1, 800);
    bank.deposito(2, 555.95);
    cout << bank << "\n";

    bank.transferencia(3, 2, 230.65);
    bank.addCliente("Maria");
    bank.atualizacaoMensal();
    cout << bank;

}