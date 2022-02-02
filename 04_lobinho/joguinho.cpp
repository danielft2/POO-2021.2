#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <windows.h>
#include <ctime>
#include <vector>

void setSize(sf::Sprite& sprite, int width, int height) {
    auto dim = sprite.getLocalBounds();
    sprite.setScale((float) width / dim.width, (float) height / dim.height);
}

struct Entity {
    int x {0}; //atributos
    int y {0};
    int step {0};
    sf::Sprite sprite;

    Entity(int x, int y, int step, sf::Texture& texture):
        x {x}, y {y}, step {step}, sprite(texture) {
    }

    void draw(sf::RenderWindow& window) { //métodos
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }
};

struct Board {
    int nc {0};
    int nl {0};
    int step {0};//atributos
    sf::Sprite sprite;
    sf::RectangleShape rect;
    Board(int nc, int nl, int step, sf::Texture& texture) {
        this->nc = nc;
        this->nl = nl;
        this->step = step;
        this->sprite.setTexture(texture);
        setSize(this->sprite, nc * step, nl * step);
        this->sprite.setPosition(0, 0);

        this->rect.setSize(sf::Vector2f(step, step));
        this->rect.setFillColor(sf::Color::Transparent);
        this->rect.setOutlineColor(sf::Color::Black);
        this->rect.setOutlineThickness(2);
    }
    void draw(sf::RenderWindow& window) {
        window.draw(this->sprite);
        for (int i = 0; i < nc; i++) {
            for (int j = 0; j < nl; j++) {
                rect.setPosition(i * step, j * step);
                window.draw(rect);
            }
        }
    }
};

struct Vidas {

    int x {0};
    int y {0};
    int step {0};
    sf::Sprite sprite;
    
    Vidas(int x, int y, int step, sf::Texture& texture) {
       this->x = x;
       this->y = y;
       this->step = step;
       this->sprite.setTexture(texture);
    }
    
    void draw(sf::RenderWindow& window) { //métodos
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }

    void mudaPosicao(int& x) {
        this->x = x;
    }
};

struct Obstaculo {

    int x {0};
    int y {0};
    int step {0};
    sf::Sprite sprite;

    Obstaculo(int step, sf::Texture& texture) {
        srand(time(0));
        this->x = rand() % 7;
        this->y = rand() % 5;
        this->step = step;
        this->sprite.setTexture(texture);
    }

    void draw(sf::RenderWindow& window) { //métodos
        this->sprite.setPosition(x * step, y * step);
        setSize(this->sprite, step, step);
        window.draw(this->sprite);
    }

    void mudarPosicao() {
        srand(time(0));
        this->x = rand() % 7;
        this->y = rand() % 5;   
    }

};

void moveEntity(sf::Keyboard::Key key, Entity& entity, std::vector<sf::Keyboard::Key> move_keys) {
    if (key == move_keys[0])
        entity.x--;
    else if (key == move_keys[1])
        entity.y--;
    else if (key == move_keys[2])
        entity.x++;
    else if (key == move_keys[3])
        entity.y++;
}

bool existeColisao(Entity& entity1, Entity& entity2) {
    if (entity1.x == entity2.x && entity1.y == entity2.y)
        return true;
    else 
        return false; 
} 

void achouCacto(Board& loser, sf::RenderWindow& window, Entity& coyote, Obstaculo& cacto) {
    if (coyote.x == cacto.x && coyote.y == cacto.y) {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();      
            }

            window.clear();
            loser.draw(window);
            window.display();
        }
    }

}

void exibeFase(Board& fase, sf::RenderWindow& window, int& controllFase, int codigo) {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();      
        }
        
        window.clear();
        if (controllFase == 0 && codigo == 1 ){
            fase.draw(window);
            controllFase++;
        } else if (controllFase > 1 && codigo == 2) {
            fase.draw(window);
            controllFase++;
        } else 
            break;
        window.display();
        Sleep(1500);
        break;
    }   
}

void proximaFase(Board& fase, int& controllFase, Vidas& vida1, Vidas& vida2, Vidas& vida3, sf::RenderWindow& window) {
    if (controllFase > 1) {
        int pos1 {0}, pos2 {1}, pos3 {2};
        vida1.mudaPosicao(pos1);
        vida2.mudaPosicao(pos2);
        vida3.mudaPosicao(pos3);
        exibeFase(fase, window, controllFase, 2);
    } else {
        
    }

}

void fimDeJogo(Board& loser, sf::RenderWindow& window, int& controllFase) {

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();      
        }

        window.clear();
        loser.draw(window);
        window.display();
    } 
     
}

void perdeVida(bool confirmacao, Vidas& vida1, Vidas& vida2, Vidas& vida3, int& controll, int& controllFase) {
    int pos = -1;
    if (confirmacao) {
        if (controll == 3) {
            vida3.mudaPosicao(pos);
            controll--;
        } else if (controll == 2) {
            vida2.mudaPosicao(pos);
            controll--;
        } else {
            vida1.mudaPosicao(pos);
            controll--;
            controllFase++;
        }       
    }
}

sf::Texture loadTexture(std::string path) {
    sf::Texture texture;
    if (!texture.loadFromFile(path)) {
        std::cout << "Error loading texture" << std::endl;
        exit(1);
    }
    return texture;
}

int main() {

    sf::Texture papalegua_tex { loadTexture("papaleguas.png") };
    sf::Texture coyote_tex { loadTexture("coyote.png") };
    sf::Texture vida_tex { loadTexture("vida.png")};
    sf::Texture deserto_tex { loadTexture("fundo.jpg") };
    sf::Texture obstaculo_tex { loadTexture("cacto.png")};
    sf::Texture fase1_tex { loadTexture("fase1.png")};
    sf::Texture fase2_tex { loadTexture("fase2.png")};
    sf::Texture game_over_tex { loadTexture("game_over.jpg")};
    
    const int STEP {100};
    const int STEPv {25};
    
    Entity papalegua(0, 1, STEP, papalegua_tex);
    Entity coyote(3, 3, STEP, coyote_tex);
    Board board(7, 5, STEP, deserto_tex);
    Board loser(7, 5, STEP, game_over_tex);
    Board fase1(7, 5, STEP, fase1_tex);
    Board fase2(7, 5, STEP, fase2_tex);
    Vidas vida1(0, 0, STEPv, vida_tex);
    Vidas vida2(1, 0, STEPv, vida_tex);
    Vidas vida3(2, 0, STEPv, vida_tex);
    Obstaculo cacto(STEP, obstaculo_tex);


    sf::RenderWindow window(sf::VideoMode(board.nc * STEP, board.nl * STEP), "SFML works!");

    int controllVida {3};
    int fase {0};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                moveEntity(event.key.code, coyote, {sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Right, sf::Keyboard::Down});
                moveEntity(event.key.code, papalegua, {sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::D, sf::Keyboard::S});
                perdeVida(existeColisao(coyote, papalegua), vida1, vida2, vida3, controllVida, fase);
                achouCacto(loser, window, coyote, cacto);
            }
        }

        exibeFase(fase1, window, fase, 1);
        if(controllVida == 0 && fase == 2) {
            proximaFase(fase2, fase, vida1, vida2, vida3, window);
            controllVida = 3;
        }

        if (controllVida < 3 && fase == 3) {
            cacto.mudarPosicao();
        } 

        if (controllVida < 1 && fase > 3) {
            fimDeJogo(loser, window, fase);
        }

        window.clear();
        board.draw(window);
        cacto.draw(window);
        vida1.draw(window);
        vida2.draw(window);
        vida3.draw(window);
        papalegua.draw(window);
        coyote.draw(window);
        window.display();
    }

    return 0;
}