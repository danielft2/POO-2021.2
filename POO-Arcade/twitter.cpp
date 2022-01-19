#include <iostream>
#include <memory>
#include <map>
#include <unordered_set>
#include <vector>
#include <sstream>


using namespace std;

class Mensagem {
    int id {0};
    unordered_set<string> likes;
    string msg = "";
    string nome = "";
public:
    Mensagem(int id, string nome, string msg) : id{id}, nome{nome}, msg{msg} {
    }

    void like(string nome) {
        likes.insert(nome);
    }

    int getId() {
        return this->id;
    }

    friend std::ostream& operator<<(std::ostream& os, const Mensagem& mensagem) {
        os << mensagem.id << ":" << mensagem.nome << " " << "(" << mensagem.msg << ")";
        if(!mensagem.likes.empty()) {
            os << " [";
            for(auto like : mensagem.likes) {
                os << like << ", ";
            }
            os << "]";
        }
        return os;
    }
};  

class Inbox {
    map<int, shared_ptr<Mensagem>> naoLidas;
    map<int, shared_ptr<Mensagem>> todasMsgs;
public:
    Inbox() {
    }

    Mensagem* buscarMsg(int id) {
        auto it = naoLidas.find(id);
        if (it == naoLidas.end()) 
           throw runtime_error("Mensagem nao encontrada\n");
        return it->second.get();
    }
    
    void novoRecebido(shared_ptr<Mensagem> tweet) {
        naoLidas[tweet->getId()] = tweet;
        todasMsgs[tweet->getId()] = tweet;
    }

    void salvarComoNaoLida(shared_ptr<Mensagem> tweet) {
        naoLidas[tweet->getId()] = tweet;
    }

    map<int, shared_ptr<Mensagem>> getNaoLidas() {
        auto msgNaoLidas = this->getNaoLidas();
        this->naoLidas.clear();
        for (auto& [key, msg] : msgNaoLidas) {
            this->todasMsgs[key] = msg;
        }
        return msgNaoLidas; 
    }

    map<int, shared_ptr<Mensagem>> getTodasMsgs() {
        return this->todasMsgs;
    }

    Mensagem* getTweet(int id) {
        auto tweet = buscarMsg(id);
        return tweet;
    }

    
    friend std::ostream& operator<<(std::ostream& os, const Inbox& inbox) {
        for (auto& [key, msg]: inbox.naoLidas) {
            os << *msg << "\n";
        }
        os << "\n";
        return os;
    }

};

class Usuario {
private:
    map<string, Usuario*> seguidos;
    map<string, Usuario*> seguidores;
    Inbox inbox;
    string nome;
public:
    int idMsg {0};

    Usuario(string nome) : nome{nome} {
    }

    bool jaSegue(string nome) {
        auto it = seguidos.find(nome);
        if (it == seguidos.end()) 
            return true;
        throw runtime_error("Voce ja segue essa pessoa.");
    }

    bool NaoSegue(string nome) {
        auto it = seguidos.find(nome);
        if (it == seguidos.end()) 
            throw runtime_error("Voce nao segue essa pessoa.");
        return true;
    }

    virtual void seguir(Usuario* outro) {
        auto key = outro->nome;
        if (jaSegue(key)) {
            outro->seguidores[this->nome] = this;
            this->seguidos[key] = outro;
        }
    }

    virtual void deixarDeSeguir(Usuario* outro) {
        auto key = outro->nome;
        if (NaoSegue(key)) {
            this->seguidos.erase(key);
            outro->seguidores.erase(this->nome);
        }
    }

    Inbox getInbox() {
        return this->inbox;
    }

    void like(int id) {
        auto tweet = this->inbox.getTweet(id);
        tweet->like(this->nome);
    }

    void twiitar(shared_ptr<Mensagem> tweet) {
        this->inbox.novoRecebido(tweet);
        for (auto& [key, seguidor] : seguidores) {
            seguidor->inbox.salvarComoNaoLida(tweet);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Usuario& user) {
        os << user.nome << "\n";
        os << "  Seguidos: [";
        for (auto& seguidor : user.seguidos) {
            os << seguidor.second->nome << ", ";
        }
        os << "]\n";
        os << "  Seguidores: [";
        for (auto& seguidor : user.seguidores) {
            os << seguidor.second->nome << ", ";
        }
        os << "]\n\n";
        return os;
    }

};

class Controle {
    map<string, shared_ptr<Usuario>> usuarios;
    map<string, shared_ptr<Mensagem>> tweets;
    int proximoId {0};
public:
    Controle() {
    }

    bool naoExiste(string nome) {
        auto it = usuarios.find(nome);
        if (it == usuarios.end()) 
            return true;
        throw runtime_error("O" + nome + "ja existe\n");
    }

    void addUsuario(string nome) {
        if (naoExiste(nome)) {
            auto user = make_shared<Usuario>(nome);
            usuarios[nome] = user;
        }
    }
    
    Usuario* buscarUser(string nome) {
        auto it = usuarios.find(nome);
        if (it == usuarios.end())
           throw runtime_error(nome + " nao foi encontrado.\n");
        return it->second.get();
    }

    void enviarTweet(string nome, string msg) {
        auto user = buscarUser(nome);
        auto msgEnviada = make_shared<Mensagem>(this->proximoId, nome, msg);
        user->twiitar(msgEnviada);
        this->proximoId++;
    }

    friend std::ostream& operator<<(std::ostream& os, const Controle& controle) {
        for (auto user : controle.usuarios) {
            os << *user.second;
        }
        return os;
    }
};

int main() {
    system("cls");
    Controle controle;

    while (true) {
        string linha{}, cmd{};
        getline(cin, linha);
        stringstream ss(linha);
        ss >> cmd;
        cout << "$" << linha << "\n\n";
        try {
            if (cmd == "add") {
                string nome{};
                ss >> nome;
                controle.addUsuario(nome);
            } else if (cmd == "show") {
                system("cls");
                cout << controle;
            } else if (cmd == "timeline") {
                string nome{};
                ss >> nome;
                auto user = controle.buscarUser(nome);
                cout << user->getInbox();
            } else if (cmd == "twittar") {
                string nome{}, msg{};
                ss >> nome;
                getline(ss, msg);
                controle.enviarTweet(nome, msg.substr(1));
            } else if (cmd == "end") {
                break;
            } else if (cmd == "seguir") {
                string nome1{}, nome2{};
                ss >> nome1 >> nome2;
                auto seguidor = controle.buscarUser(nome1);
                auto seguido = controle.buscarUser(nome2);
                seguidor->seguir(seguido);
            } else if (cmd == "paraSeguir") {
                string nome1{}, nome2{};
                ss >> nome1 >> nome2;
                auto user = controle.buscarUser(nome1);
                auto seguido = controle.buscarUser(nome2);
                user->deixarDeSeguir(seguido);
            } else if (cmd == "like") {
                string nome{}; int id{};
                ss >> nome >> id;
                auto user = controle.buscarUser(nome);
                user->like(id);
            } else {
                cout << "Comando invalido\n";
            }
            
        } catch (runtime_error &e) {
            cout << e.what() << "\n";
        }
    }

    return 0;
}


