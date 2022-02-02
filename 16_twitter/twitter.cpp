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
    }

    friend std::ostream& operator<<(std::ostream& os, const Tweet& tweet) {
        int cont {0};
        if (!tweet.deletado && tweet.rt == nullptr) {
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
        } else if (tweet.rt != nullptr) {
            os << tweet.id << ":" << tweet.nome << " " << "(" << tweet.msg << ")";
            if (!tweet.rt->deletado) 
                os << "\n" << "   " <<  *tweet.rt;
            else 
                os << "\n" << "  " << "O rt foi deletado\n";
            
        }
    
        return os;
    }
};  

class Inbox {
    
    map<int, Tweet*> meusTweets;
public:
    map<int, Tweet*> timeLine;
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

        for (auto [key, user] : seguidores) {
            user->inbox.guardarNaTimeLine(tweet);
        }
    }

    void like(int twId) {
       auto tweet = this->inbox.getTweet(twId);
       tweet->like(this->nome);
    }

    void unfollowAll() {
        vector<Usuario*> remSeguidos;
        for (auto user : this->seguidos) {
            remSeguidos.push_back(user.second);
        }

        for (auto user : remSeguidos) {
            this->seguidos.erase(user->nome);
            user->seguidores.erase(this->nome);
        }
    }

    void rejectAll() {
        vector<Usuario*> remSeguidores;
        for (auto user : this->seguidores) {
            remSeguidores.push_back(user.second);
        }

        for (auto user : remSeguidores) {
            this->seguidores.erase(user->nome);
            user->seguidos.erase(this->nome);
        }
    }

    Inbox& getInbox() {
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

    void remove(string nome) {
        auto user = buscarUser(nome);
        user->unfollowAll();
        user->rejectAll();

        for (auto tweet : user->getInbox().getMeusTweets()) {
            tweet->setDelete();
        }

        this->usuarios.erase(nome);
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
 
    controle.addUsuario("goku");
    controle.addUsuario("sara");
    controle.addUsuario("tina");

    auto goku = controle.buscarUser("goku");
    auto sara = controle.buscarUser("sara");
    auto tina = controle.buscarUser("tina");

    goku->seguir(sara);
    goku->seguir(tina);
    sara->seguir(tina);
    sara->seguir(goku);

    controle.enviarTweet("tina", "bom final de semana guys");
    controle.enviarTweet("goku", "Bom diaa");
    controle.enviarRt("sara", 0, "pra voce tambem");
 
  
    cout << controle;
    cout << goku->getInbox();
    cout << sara->getInbox();

    controle.remove("tina");
    cout << controle;
    
    cout << goku->getInbox();
  
     
    return 0;
}


