#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>
#include <vector>
#include <functional>
#include <ctime> 

using namespace std;

void setSize(sf::Sprite& sprite, int width, int height) {
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

struct Play {
    sf::RenderWindow& window;
    int x {290};
    int y {390};
    
    Play(sf::RenderWindow& window) :
        window {window} {
    }

    void draw() {
        static sf::RectangleShape rect; 
        rect.setSize(sf::Vector2f(200, 30));
        rect.setPosition(x, y);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(2);
        window.draw(rect);
    }
     
    int update(sf::Keyboard::Key key, vector<sf::Keyboard::Key> move_keys) {
        if (key == move_keys[0]) 
            this->y = 390;
        else if (key == move_keys[1])
            this->y = 450;
        else if (key == move_keys[2] && this->y == 390)
            return 1;
        else if (key == move_keys[2] && this->y == 450)
            return 2; 

        return 0;
    }       
    
};

struct Fundo {
    int nc {0};
    int nl {0};
    int step {0};//atributos
    sf::Sprite sprite;
    Fundo(int nc, int nl, int step, sf::Texture& texture) {
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step);
        this->sprite.setPosition(0, 0);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(this->sprite);
    }
};

struct Pincel {
 
    sf::Font font;
    sf:: Text text;
    sf:: RenderWindow& window;

    Pincel(sf::RenderWindow& window) :
        window {window} {
        if(!font.loadFromFile("font.ttf"))
            cout << "error\n";
        text.setFont(font);
    }
    
    void write(string str, int x, int y, int size, sf::Color color) {
        text.setString(str);
        text.setCharacterSize(size);
        text.setPosition(x, y);
        text.setFillColor(color);
        window.draw(text);
    }
};

struct Bolha {
    int x;
    int y;
    char letra;
    int velo;

    const static int raio {20}; 
    bool viva {true};

    Bolha(int x, int y, char letra, int velo) :
        x {x}, y {y}, letra {letra}, velo {velo} {
    }

    void update() {
        this->y += this->velo;
    }

    void draw(sf::RenderWindow& window) {
        sf::CircleShape circlo (Bolha::raio);
        circlo.setPosition(x, y);
        circlo.setFillColor(sf::Color::Transparent);
        window.draw(circlo);

        static Pincel pencil(window);
        pencil.write(string(1, letra), x + 0.5 * Bolha::raio, y, Bolha::raio * 1.5, sf::Color::White); 
    }
};

struct Board {
    vector<Bolha> bolhas;
    sf::RenderWindow& window;
    Pincel pincel;
    int acertos {0};
    int erros {0};
    int velo {30};
    int recorde {0};

    Board(sf::RenderWindow& window) : 
        window(window), pincel(window) {
        bolhas.push_back(Bolha(100, 100, 'A', 2));
        bolhas.push_back(Bolha(200, 100, 'B', 3));
        bolhas.push_back(Bolha(300, 100, 'C', 4));
    }

    void update() {
        if (this->check_new_bolha()) 
            this->add_new_bolha();

        for (Bolha& bolha : bolhas) {
            bolha.update();
        }

        this->marcar_bolhas();
        this->romover_bolhas_mortas();
    }

    void romover_bolhas_mortas() {
        vector<Bolha> vivas;
        for (Bolha& bolha : bolhas) {
            if (bolha.viva) {
                vivas.push_back(bolha);
            }
        }

        this->bolhas = vivas;
    }

    void draw() {
        pincel.write("ACERTOS: " + to_string(this->acertos) + "  ERROS: " + to_string(this->erros), 10, 10, 15, sf::Color::White);
        pincel.write("RECORDE: " + to_string(this->recorde), 10, 30, 15, sf::Color::White);
        for (Bolha& bolha : bolhas) {
            bolha.draw(window);
        }
    }

    void marcar_bolhas() {
        for (Bolha& bolha : bolhas) {
            if (bolha.y + 2 * Bolha::raio > (int) this->window.getSize().y) {
                if (bolha.viva) {
                    bolha.viva = false;
                    this->erros++;
                }
            }
        } 
    }

    void mark_by_hit(char letra) {
        for (Bolha& bolha : bolhas) {
            if (bolha.letra == letra) {
                bolha.viva = false;
                this->acertos++;
                break;
            }
        }
        
    }

    void num_acertos() {
        if (this->acertos == 25) {
            this->velo = 30;
        } else if (this->acertos == 45) {
            this->velo = 20;
        } else if (this->velo == 60) {
            this->velo = 10;
        }
    }

    bool check_new_bolha() {
        this->num_acertos();
        static const int nova_bolha_crono {this->velo};
        static int nova_bolha_time {0};
        nova_bolha_time--;
        if (nova_bolha_time <= 0) {
            nova_bolha_time = nova_bolha_crono;
            return true;
        }
        
        return false;
    }

    void add_new_bolha() {
        int x = rand() % ((int) this->window.getSize().x - 2 * Bolha::raio);
        int y = -2 * Bolha::raio;
        int velo = rand() % 5 + 1;
        char letra = rand() % 26 + 'A';
        bolhas.push_back(Bolha(x, y, letra, velo));
    }
};

sf::Texture loadTexture(std::string path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    return texture;
} 
    
struct Game {
    sf::RenderWindow window;
    Board board;
    Play play;
    function<void()> on_update;
    vector<sf::Texture> texturas;
    bool fim_de_jogo = false;
    bool inicio_jogo = true;

    Game() :
        window(sf::VideoMode(800, 600), "Bubbles"), board(window), play(window) {
        this->on_update = [&]() {
            this->tela_inical();
        };
        window.setFramerateLimit(30);
        texturas.push_back(sf::Texture {loadTexture("fundo.jpg")});
        texturas.push_back(sf::Texture {loadTexture("gameover.jpg")});
        texturas.push_back(sf::Texture {loadTexture("velocidade.jpg")});
        texturas.push_back(sf::Texture {loadTexture("inicio.jpg")});
    }

    void process_event() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                char code = static_cast<char>(event.text.unicode);
                code = toupper(code);
                board.mark_by_hit(code);
            }

            if (event.type == sf::Event::KeyPressed) {
                if (fim_de_jogo || inicio_jogo) {
                    int new_game = play.update(event.key.code, {sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Enter});
                    if (new_game == 1)
                        this->muda_tela(true);
                    else if (new_game == 2)
                        window.close();
                }
            }
        }
    }

    void gameplay() {
        static Fundo fundo(8, 6, 100, texturas[0]);
        board.update();
        window.clear();
        fundo.draw(window);
        board.draw();
        window.display();
        this->muda_tela(false);
    }

    void gameover() {
        fim_de_jogo = true;
        static Fundo over(8, 6, 100, texturas[1]);
        static Pincel pincel(window);
        window.clear();
        over.draw(window);
        play.draw();
        pincel.write("JOGAR DE NOVO", 290, 390, 20, sf::Color::Green);
        pincel.write("SAIR", 355, 450, 20, sf::Color::Green);
        window.display();
    }

    void tela_inical() {
        static Fundo fundo(8, 6, 100, texturas[3]);
        static Pincel pincel(window);
        window.clear();
        fundo.draw(window);
        play.draw();
        pincel.write("INICIAR", 352, 390, 20, sf::Color::Green);
        window.display();
    }

    void muda_tela(bool inicio) {
        if (board.acertos == 25 || board.acertos == 45 || board.acertos == 60) {
            this->on_update = [&]() {
                this->velo_aumentada();
            };
        } 

        if(board.erros > 10) {
            this->on_update = [&]() {
                this->gameover();
            };
        } 

        if (inicio) {
            this->on_update = [&]() {
                this->gameplay();
            };

            if (board.recorde < board.acertos) {
                board.recorde = board.acertos;
            }

            fim_de_jogo = false;
            inicio_jogo = false;
            board.acertos = 0;
            board.erros = 0;
            board.velo = 40;
        }
    }

    void velo_aumentada() {
        static Fundo velo(8, 6, 100, texturas[2]);
        window.clear();
        velo.draw(window);
        window.display();
        Sleep(1000);
        board.acertos++;
        this->on_update = [&]() {
            this->gameplay();
        };
    }

    void main_loop() {
        while (window.isOpen()) {
            process_event();
            on_update();
        }
    }
};

int main() {
    Game game;
    game.main_loop();
    return 0;
}