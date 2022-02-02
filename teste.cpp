#include <iostream>
#include <memory>
#include <map>
#include <unordered_set>
#include <vector>
#include <sstream>


using namespace std;

class Tweet {
    int id {0};
    string msg = "";
    string nome = "";
    unordered_set<string> likes;
    Tweet *rt {nullptr};
    bool rtExist {false};
    bool deletado {false};
public:
    Tweet (int id, string nome, string msg) : id{id}, nome{nome}, msg{msg} {
    }

    void like(string nome) {
        likes.insert(nome);
    }

    int getId() {
        return this->id;
    }

    string getNome() {
        return this->nome;
    }

    string getMsg() {
        return this->msg;
    }

    bool isDelete() {
        return this->deletado;
    }

    void setDelete() {
        this->deletado = true;
    }

    void setRt(Tweet *tweet) {
        this->rt = tweet;
        this->rtExist = true;
    }

    friend std::ostream& operator<<(std::ostream& os, const Tweet& tweet) {
        int cont {0};
        if (!tweet.rtExist) {
            os << tweet.id << ":" << tweet.nome << " " << "(" << tweet.msg << ")";
            if(!tweet.likes.empty()) {
                os << " [";
                for(auto like : tweet.likes) {
                    if (cont == 0)
                        os << like;
                    else 
                        os << ", " << like;
                }
                os << "]";
            }
        } else {
            os << tweet.id << ":" << tweet.nome << " " << "(" << tweet.msg << ")" << "\n";
            os << "  " << *tweet.rt;
        }
            
        return os;
    }
};  

class Inbox {
    map<int, Tweet*> timeLine;
    map<int, Tweet*> meusTweets;
public:
    Inbox() {
    }
    
    void guardarNaTimeLine(Tweet *tweet) {
        this->timeLine[tweet->getId()] = tweet;
    }

    void guardarEmMeusTweets(Tweet *tweet) {
        this->meusTweets[tweet->getId()] = tweet;
    }

    void remMsgsDe(const string& nome) {
        vector<Tweet*> tweetMarck;
        for (auto tweet : timeLine) {
            if (tweet.second->getNome() == nome) 
                tweetMarck.push_back(tweet.second);
        }

        for (auto tweet : tweetMarck) {
            timeLine.erase(tweet->getId());
        }
    }

    vector<Tweet*> getTimeLine() const {
        vector<Tweet*> tweets;
        for (auto& tweet : timeLine) {
            tweets.push_back(tweet.second);
        }

        return tweets;
    }

    vector<Tweet*> getMeusTweets() const {
        vector<Tweet*> tweets;
        for (auto& tweet : meusTweets) {
            tweets.push_back(tweet.second);
        }

        return tweets;
    }

    Tweet* getTweet(int id) {
        auto it  = timeLine.find(id);
        if (it == timeLine.end()) 
           throw runtime_error("Mensagem nao encontrada\n");
        return it->second;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Inbox& inbox) {
        for (auto tweet : inbox.getTimeLine()) {
            os << *tweet << "\n";
        }
        os << "\n";
        return os;
    }

};

class Usuario {
private:
    map<string, Usuario*> seguidos;
    map<string, Usuario*> seguidores;
    string nome;
    Inbox inbox;

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
public:  
    Usuario(string nome) : nome{nome} {
    }

    void seguir(Usuario* outro) {
        auto key = outro->nome;
        if (jaSegue(key)) {
            outro->seguidores[this->nome] = this;
            this->seguidos[key] = outro;
        }
    }

    void deixarDeSeguir(Usuario* outro) {
        auto key = outro->nome;
        if (NaoSegue(key)) {
            this->inbox.remMsgsDe(outro->nome);
            this->seguidos.erase(key);
            outro->seguidores.erase(this->nome);
        }
    }

    void enviarTweet(Tweet *tweet) {
        this->inbox.guardarNaTimeLine(tweet);
        this->inbox.guardarEmMeusTweets(tweet);

        for (auto& [key, user] : seguidores) {
            user->inbox.guardarNaTimeLine(tweet);
        }
    }

    void like(int twId) {
       auto tweet = this->inbox.getTweet(twId);
       tweet->like(this->nome);
    }

    Inbox getInbox() {
        return this->inbox;
    }

    friend std::ostream& operator<<(std::ostream& os, const Usuario& user) {
        int cont {0};
        os << user.nome << "\n";
        os << "  Seguidos: [";
        for (auto& seguidor : user.seguidos) {
            if (cont == 0) 
                os << seguidor.second->nome;
            else 
                os << ", " << seguidor.second->nome;
            cont++;
        }
        os << "]\n";
        os << "  Seguidores: [";
        for (auto& seguidor : user.seguidores) {
            if (cont == 0) 
                os << seguidor.second->nome;
            else 
                os << ", " << seguidor.second->nome;
            cont++;
        }
        os << "]\n\n";
        return os;
    }

};

class Controle {
    map<string, shared_ptr<Usuario>> usuarios;
    map<string, shared_ptr<Tweet>> tweets;
    
    int proximoId {0};

    Tweet* criarTweet(string nome, string msg) {
        auto tweet = make_shared<Tweet>(this->proximoId, nome, msg);
        tweets[nome] = tweet;
        this->proximoId++;
        return tweet.get();
    }
public:
    Controle() {
    }

    bool naoExiste(string nome) {
        auto it = usuarios.find(nome);
        if (it == usuarios.end()) 
            return true;
        throw runtime_error("O" + nome + "ja existe\n");
    }

    Usuario* buscarUser(string nome) {
        auto it = usuarios.find(nome);
        if (it == usuarios.end())
           throw runtime_error(nome + " nao foi encontrado.\n");
        return it->second.get();
    }

    void addUsuario(string nome) {
        if (naoExiste(nome)) {
            auto user = make_shared<Usuario>(nome);
            usuarios[nome] = user;
        }
    }
    
    void enviarTweet(string nome, string msg) {
        auto user = buscarUser(nome);
        auto novoTweet = this->criarTweet(nome, msg);
        user->enviarTweet(novoTweet);
    }

    void enviarRt(string nome, int twId, string msg) {
        auto user = buscarUser(nome);
        auto tweetRt = user->getInbox().getTweet(twId);
        auto novoTweet = this->criarTweet(nome, msg);
        novoTweet->setRt(tweetRt);
        user->enviarTweet(novoTweet);

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
            } else if (cmd == "rt") {
                string nome{}, msg{};
                int id {};
                ss >> nome >> id;
                getline(ss, msg);
                controle.enviarRt(nome, id, msg.substr(1));
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


