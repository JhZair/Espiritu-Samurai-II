#include <SFML/Graphics.hpp>

class Jugador {
public:
    sf::RectangleShape rectan;
    float velocidad;

    Jugador(float x, float y, sf::Color color) {
        rectan.setSize(sf::Vector2f(50.0f, 100.0f));
        rectan.setPosition(x, y);
        rectan.setFillColor(color);
        velocidad = 200.0f;
    }

    void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha) {
        if (sf::Keyboard::isKeyPressed(izquierda)) {
            rectan.move(-velocidad * tiempoDelta, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(derecha)) {
            rectan.move(velocidad * tiempoDelta, 0.0f);
        }
    }
    sf::Vector2f getPosicion(){
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


        jugador1.move(tiempoDelta, sf::Keyboard::Left, sf::Keyboard::Right);
        jugador2.move(tiempoDelta, sf::Keyboard::A, sf::Keyboard::D);

        if(jugador1.getPosicion().x>799){
            jugador1.rectan.move(-300, 0.0f);
        }
        if (jugador2.getPosicion().x < 0) {
            jugador2.rectan.move(300, 0.0f);
        }
      
        window.clear(sf::Color::Blue);

        window.draw(piso.rectan);
        window.draw(jugador1.rectan);
        window.draw(jugador2.rectan);
        window.display();
    }

    return 0;
}

