#include <iostream>
#include <map>
#include <memory>
#include <sstream>

using namespace std;
class Imedico;

class Ipaciente {
public:
    virtual string getId() = 0;
    virtual void addMedico(Imedico* medico) = 0;
    virtual void removerMedico(string idMedico) = 0;
    virtual map<string, Imedico*> getMedicos() = 0;
    virtual string getDiagnostico() = 0;
};

class Imedico {
public:
    virtual string getId() = 0;
    virtual void addPaciente(Ipaciente* paciente) = 0;
    virtual void removerPaciente(string idPaciente) = 0;
    virtual map<string, Ipaciente*> getPacientes() = 0;
    virtual string getClasse() = 0;
};

class Medico : public Imedico {
private:
    string id;
    string especialidade;
    map<string, Ipaciente*> pacientes;
public:
    Medico(string id = "", string especialidade = "") : id{id}, especialidade{especialidade} {
    }

    virtual void addPaciente(Ipaciente* paciente) {
        auto key = paciente->getId();
        auto it = pacientes.find(key);
        if (it == pacientes.end()) {
            pacientes[key] = paciente;
            paciente->addMedico(this);
        } 
    }

    virtual void removerPaciente(string idPaciente) {
        auto it = pacientes.find(idPaciente);
        if (it != pacientes.end()) {
            auto paciente = this->pacientes[idPaciente];
            this->pacientes.erase(idPaciente);
            paciente->removerMedico(this->id);
        } 
    }

    virtual map<string, Ipaciente*> getPacientes() {
        return this->pacientes;
    }

    virtual string getId() {
        return this->id;
    }

    virtual string getClasse() {
        return this->especialidade;
    }

    friend std::ostream& operator<<(std::ostream& os, const Medico& medico) {
        int cont = 0;
        os << "Med: " << medico.id << ":" << medico.especialidade << "  ";
        os << "Pacs: " << "[";
        for (auto& [key, paciente] : medico.pacientes) {
            if (cont == 0) 
                os << key;
            else 
                os << ", " << key;
            cont++;
        }
        os << "]" << "\n";
        return os;
    }
};

class Paciente : public Ipaciente {
protected:
    string id;
    string diagnostico;
    map<string, Imedico*> medicos;
public:
    Paciente(string id = "", string diagnostico = "") : id{id}, diagnostico{diagnostico} {
    }

    bool verificarMedico(Imedico* novoMedico) {
        for (auto medico : medicos) {
            if (medico.second->getClasse() == novoMedico->getClasse()) 
                return true;
        }

        return false;
    }

    virtual void addMedico(Imedico* medico) {
        auto key = medico->getId();
        auto it = medicos.find(key);
        if (it == medicos.end()) {
            if(!verificarMedico(medico)) {
                medicos[key] = medico;
                medico->addPaciente(this);
            }   
        } 
    }

    virtual void removerMedico(string idMedico) {
        auto it = medicos.find(idMedico);
        if (it != medicos.end()) {
            auto medico = this->medicos[idMedico];
            this->medicos.erase(idMedico);
            medico->removerPaciente(this->id);
        } 
    }

    virtual map<string, Imedico*> getMedicos() {
        return this->medicos;
    }

    virtual string getId() {
        return this->id;
    }

    virtual string getDiagnostico() {
        return this->diagnostico;
    }

    friend std::ostream& operator<<(std::ostream& os, const Paciente& paciente) {
        int cont = 0;
        os << "Pac: " << paciente.id << ":" << paciente.diagnostico << "  ";
        os << "Medcs: " << "[";
        for (auto& [key, medico] : paciente.medicos) {
            if (cont == 0) 
                os << key;
            else 
                os << ", " << key;
            cont++;
        }
        os << "]" << "\n";
        return os;
    }
};

class Hospital {
private:
    map<string, shared_ptr<Ipaciente>> pacientes;
    map<string, shared_ptr<Imedico>> medicos;
public:
    Hospital() {
    }

    Imedico* buscarMedc(string nomeMed) {
        auto it = medicos.find(nomeMed);
        if (it != medicos.end()) 
            return it->second.get();
        else 
            throw runtime_error("O medico nao foi encontrado.\n");
    }

    Ipaciente* buscarPac(string nomePac) {
        auto it = pacientes.find(nomePac);
        if (it != pacientes.end()) 
            return it->second.get();
        else 
            throw runtime_error("O paciente nao foi encontrado.\n");
    }

    void addPaciente(shared_ptr<Ipaciente> paciente) {
        auto key = paciente->getId();
        auto it = pacientes.find(key);
        if (it == pacientes.end()) 
            pacientes[key] = paciente;
        else 
            throw runtime_error("O paciente ja existe.\n");
         
    }

    void addMedico(shared_ptr<Imedico> medico) {
        auto key = medico->getId();
        auto it = medicos.find(key);
        if (it == medicos.end()) 
            medicos[key] = medico;
        else 
            throw runtime_error("O medico ja existe.\n");
    }

    void removerPaciente(string idPaciente) {
        auto it = pacientes.find(idPaciente);
        if (it != pacientes.end()) {
            for (auto& [key, medico] : pacientes[idPaciente]->getMedicos()) {
                medico->removerPaciente(idPaciente);
            }   
            pacientes.erase(idPaciente);
        } else 
            throw runtime_error("O paciente nao existe.\n");
    }

    void removerMedico(string idMedico) {
        auto it = medicos.find(idMedico);
        if (it != medicos.end()) {
            for (auto& [key, paciente] : medicos[idMedico]->getPacientes()) {
                paciente->removerMedico(idMedico);
            }
           
        } else 
            throw runtime_error("O medico nao existe.\n");
    }

    void vincular(string nomePac, string nomeMedc) {
        auto paciente = this->buscarPac(nomePac);
        auto medico = this->buscarMedc(nomeMedc);
        medico->addPaciente(paciente);
    }
    
    friend std::ostream& operator<<(std::ostream& os, Hospital& hospital) {
        for (auto paciente : hospital.pacientes) {
            auto pacienteCast = dynamic_cast<Paciente*>(paciente.second.get());
            os << *pacienteCast;
        }

        for (auto medico : hospital.medicos) {
            auto medicoCast = dynamic_cast<Medico*>(medico.second.get());
            os << *medicoCast;
        }

        return os;
    }

};

int main() {
    system("cls");
    Hospital hospital;
    
    while (true) {
        string linha{}, cmd{};
        getline(cin, linha);
        stringstream ss(linha);
        ss >> cmd;
        cout << "$" << linha << "\n\n";
        try {
            if (cmd == "addPac") {
                string nome{}, diag{};
                ss >> nome >> diag;
                auto pac = make_shared<Paciente>(nome, diag);
                hospital.addPaciente(pac);
            } else if (cmd == "addMedc") {
                string nome{}, especi{};
                ss >> nome >> especi;
                auto medc = make_shared<Medico>(nome, especi);
                hospital.addMedico(medc);
            } else if (cmd == "show") {
                system("cls");
                cout << hospital << "\n";
            } else if (cmd == "remPaciente") {
                string nome{};
                ss >> nome;
                hospital.removerPaciente(nome);
            } else if (cmd == "remMedico") {
                string nome{};
                ss >> nome;
                hospital.removerMedico(nome);
            } else if (cmd == "end") {
                break;
            } else if (cmd == "vinc") {
                string paciente{}, medico{};
                ss >> paciente >> medico;
                hospital.vincular(paciente, medico);
            } else {
                cout << "Comando invalido\n";
            }
            
        } catch (runtime_error &e) {
            cout << e.what() << "\n";
        }
    }

    return 0;
}