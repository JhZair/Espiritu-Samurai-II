#include <SFML/Graphics.hpp>

class Jugador {
public:
    sf::RectangleShape rectan;
    float velocidad;

    Jugador(float x, float y) {
        rectan.setSize(sf::Vector2f(50.0f, 100.0f)); 
        rectan.setPosition(x, y); 
        rectan.setFillColor(sf::Color::Red); 
        velocidad = 200.0f; 
    }

    void move(float tiempoDelta, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey) {
        if (sf::Keyboard::isKeyPressed(leftKey)) {
            rectan.move(-velocidad * tiempoDelta, 0.0f); 
        }
        if (sf::Keyboard::isKeyPressed(rightKey)) {
            rectan.move(velocidad * tiempoDelta, 0.0f); 
        }
    }
};

class Floor {
public:
    sf::RectangleShape rectan;

    Floor(float x, float y) {
        rectan.setSize(sf::Vector2f(800.0f, 50.0f));
        rectan.setPosition(x, y); 
        rectan.setFillColor(sf::Color::Green); 
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Peleitas");

    Jugador jugador1(375.0f, 450.0f);
    Floor piso(0.0f, 550.0f);

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

        jugador1.move(tiempoDelta, sf::Keyboard::Left, sf::Keyboard::Right);

        window.clear();

        window.draw(piso.rectan);
        window.draw(jugador1.rectan);
        window.display();
    }

    return 0;
}


//g++ -o juego main.cpp -lsfml-graphics -lsfml-window -lsfml-system
