#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> 

class Cuchillo {
public:
    sf::RectangleShape forma;
    float velocidad = 500.0f; // Velocidad del cuchillo
    int direccion;
    Cuchillo(float x, float y,int direccion) {
        forma.setSize(sf::Vector2f(30.0f, 5.0f)); // Tamaño del cuchillo
        forma.setPosition(x, y);
        forma.setFillColor(sf::Color::White); // Color del cuchillo
        this->direccion = direccion;
    }

    void mover(float tiempoDelta) {
        forma.move(velocidad * tiempoDelta*direccion, 0.0f); // Movimiento hacia la derecha
    }

    sf::Vector2f getPosicion() {
        return forma.getPosition();
    }
};

class Jugador {
public:
    sf::RectangleShape rectan;
    float velocidad;
    float gravity = 1100.5f;
    float velocityY = 0;
    float jumpStrength = -480.0f; 
    bool isJumping = false;
    float maxhealth = 700;
    float health = maxhealth; 
    int vidas = 2;
    bool facingLeft=true;

    std::vector<Cuchillo> cuchillos; 

    Jugador(float x, float y, sf::Color color) {
        rectan.setSize(sf::Vector2f(50.0f, 100.0f));
        rectan.setPosition(x, y);
        rectan.setFillColor(color);
        velocidad = 200.0f;
    }

    virtual void lanzarCuchillo() {
        int direccion=facingLeft ? -1 : 1;
        Cuchillo cuchillo((rectan.getPosition().x + rectan.getSize().x)*(facingLeft ? -1 : 1), (rectan.getPosition().y + rectan.getSize().y/ 2),direccion);
        cuchillos.push_back(cuchillo);
    }

    virtual void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY) {
        if (sf::Keyboard::isKeyPressed(izquierda) && rectan.getPosition().x > 0) {
            rectan.move(-velocidad * tiempoDelta, 0.0f);
            facingLeft=true;
            rectan.setScale(-1.0f,1.0f);
            rectan.setPosition(rectan.getPosition().x , rectan.getPosition().y);
        }
        if (sf::Keyboard::isKeyPressed(derecha) && rectan.getPosition().x < 750) {
            rectan.move(velocidad * tiempoDelta, 0.0f);
            facingLeft=false;
            rectan.setScale(1.0f,1.0f);
            rectan.setPosition(rectan.getPosition().x , rectan.getPosition().y);
        }
        if (isJumping) {
            velocityY += gravity * tiempoDelta;  
        }

        if (sf::Keyboard::isKeyPressed(up) && !isJumping) {
            velocityY = jumpStrength;  
            isJumping = true; 
        }

        rectan.move(0.0f, velocityY * tiempoDelta);

        if (rectan.getPosition().y + rectan.getSize().y >= pisoY) {
            rectan.setPosition(rectan.getPosition().x, pisoY - rectan.getSize().y);
            velocityY = 0;
            isJumping = false;
        }
    }

    void actualizarCuchillos(float tiempoDelta) {
        for (auto& cuchillo : cuchillos) {
            cuchillo.mover(tiempoDelta);
        }
        
        cuchillos.erase(
            std::remove_if(cuchillos.begin(), cuchillos.end(), [](Cuchillo& cuchillo) { return cuchillo.getPosicion().x > 800; }),
            cuchillos.end()
        );
    }

    // crear funcion para mostrar barra de salud 
    void drawHealthBar(sf::RenderWindow& window, sf::Vector2f position) 
    {
        int anchoBarraMax = 200;
        int altoBarra = 30;
        float anchoBarraActual = (static_cast<float>(health) / maxhealth) * anchoBarraMax;

        sf::RectangleShape barraTotal(sf::Vector2f(anchoBarraMax, altoBarra));
        barraTotal.setPosition(position);
        barraTotal.setFillColor(sf::Color(100, 100, 100));
        barraTotal.setOutlineColor(sf::Color::White);
        barraTotal.setOutlineThickness(2);

        sf::RectangleShape barraSalud(sf::Vector2f(anchoBarraActual, altoBarra));
        barraSalud.setPosition(position);
        barraSalud.setFillColor(sf::Color::Green);      

        window.draw(barraTotal); 
        window.draw(barraSalud);
    }
};

class Hanzo : public Jugador {
public:
    Hanzo(float x, float y, sf::Color color) : Jugador(x, y, color) {}

    void lanzarCuchillo() override {
        int direccion = facingLeft ? -1 : 1;
        Cuchillo cuchillo1(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 3,direccion);
        Cuchillo cuchillo2(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + 2 * rectan.getSize().y / 3,direccion);
        cuchillos.push_back(cuchillo1);
        cuchillos.push_back(cuchillo2);
    }
};

class Samurai : public Jugador {
private:
    int remainingJumps = 45;

public:
    Samurai(float x, float y, sf::Color color) : Jugador(x, y, color) {}

    void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY) override {
        if (sf::Keyboard::isKeyPressed(izquierda) && rectan.getPosition().x > 0) {
            rectan.move(-velocidad * tiempoDelta, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(derecha) && rectan.getPosition().x < 750) {
            rectan.move(velocidad * tiempoDelta, 0.0f);
        }

        if (isJumping) {
            velocityY += gravity * tiempoDelta;
        }

        if (sf::Keyboard::isKeyPressed(up) && remainingJumps > 0) {
                isJumping = true;
                velocityY = jumpStrength;
                remainingJumps--;

        }

        rectan.move(0.0f, velocityY * tiempoDelta);

        // Comprobar colisión con el piso
        if (rectan.getPosition().y + rectan.getSize().y >= pisoY) {
            rectan.setPosition(rectan.getPosition().x, pisoY - rectan.getSize().y);
            velocityY = 0;
            isJumping = false;
            remainingJumps = 45;
        }
    }
};

class Piso {
public:
    sf::RectangleShape rectan;

    Piso(float x, float y) {
        rectan.setSize(sf::Vector2f(350.0f, 50.0f));
        rectan.setPosition(x, y);
        rectan.setFillColor(sf::Color::Green);
    }
};

class Juego {
private:
    sf::RenderWindow window;
    Hanzo jugador1;
    Samurai jugador2;
    Piso piso;
    sf::Clock reloj;
    float tiempoDelta;

public:
    Juego()
        : window(sf::VideoMode(800, 600), "Peleitas"),
          jugador1(175.0f, 450.0f, sf::Color::Blue),
          jugador2(375.0f, 450.0f, sf::Color::Red),
          piso(0.0f, 550.0f),
          tiempoDelta(0.0f) {}

    void ejecutar() {
        while (window.isOpen()) {
            procesarEventos();
            actualizar();
            renderizar();
        }
    }

private:
    void procesarEventos() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q) {
                    jugador1.lanzarCuchillo();
                }
                if (event.key.code == sf::Keyboard::P) {
                    jugador2.lanzarCuchillo();
                }
            }
        }
    }

    void actualizar() {
        tiempoDelta = reloj.restart().asSeconds();
        jugador1.move(tiempoDelta, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, piso.rectan.getPosition().y);
        jugador2.move(tiempoDelta, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, piso.rectan.getPosition().y);


        jugador1.actualizarCuchillos(tiempoDelta);
        jugador2.actualizarCuchillos(tiempoDelta);
    }

    void renderizar() {
        window.clear(sf::Color::Black);
        window.draw(piso.rectan);
        window.draw(jugador1.rectan);
        window.draw(jugador2.rectan);

        jugador1.drawHealthBar(window, sf::Vector2f(175.0f, 50.0f)); // Cambié la posición para asegurarnos que esté visible
        jugador2.drawHealthBar(window, sf::Vector2f(375.0f, 50.0f));

        for (auto& cuchillo : jugador1.cuchillos) {
            window.draw(cuchillo.forma);
        }
        for (auto& cuchillo : jugador2.cuchillos) {
            window.draw(cuchillo.forma);
        }

        window.display();
    }
};

int main() {
    Juego juego;
    juego.ejecutar();

    return 0;
}
