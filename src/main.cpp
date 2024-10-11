#include <SFML/Graphics.hpp>

class Jugador {
public:
    sf::RectangleShape rectan;
    float velocidad;
    float gravity = 1100.5f;
    float velocityY = 0;
    float jumpStrength = -480.0f; 
    bool isJumping = false; 

    Jugador(float x, float y, sf::Color color) {
        rectan.setSize(sf::Vector2f(50.0f, 100.0f));
        rectan.setPosition(x, y);
        rectan.setFillColor(color);
        velocidad = 200.0f;
    }

    void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY) {
        if (sf::Keyboard::isKeyPressed(izquierda) && rectan.getPosition().x > 0) {
            rectan.move(-velocidad * tiempoDelta, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(derecha) && rectan.getPosition().x < 750) {
            rectan.move(velocidad * tiempoDelta, 0.0f);
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
    sf::Vector2f getPosicion() {
        return rectan.getPosition();
    }
};

class Piso {
public:
    sf::RectangleShape rectan;

    Piso(float x, float y) {
        rectan.setSize(sf::Vector2f(800.0f, 50.0f));
        rectan.setPosition(x, y);
        rectan.setFillColor(sf::Color::Green);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Peleitas");

    Jugador jugador1(375.0f, 450.0f, sf::Color::Red);
    Jugador jugador2(175.0f, 450.0f, sf::Color::Black);
    Piso piso(0.0f, 550.0f);

    sf::Clock reloj;
    float tiempoDelta = 0.0f;

    while (window.isOpen()) {
        tiempoDelta = reloj.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        jugador1.move(tiempoDelta, sf::Keyboard::Left, sf::Keyboard::Right,sf::Keyboard::Up, piso.rectan.getPosition().y);
        jugador2.move(tiempoDelta, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, piso.rectan.getPosition().y);


        window.clear(sf::Color::Blue);

        window.draw(piso.rectan);
        window.draw(jugador1.rectan);
        window.draw(jugador2.rectan);
        window.display();
    }

    return 0;
}

//g++ -o juego main.cpp -lsfml-graphics -lsfml-window -lsfml-system
