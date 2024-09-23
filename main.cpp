#include <SFML/Graphics.hpp>

class Player {
public:
    sf::RectangleShape shape;
    float speed;

    Player(float x, float y) {
        shape.setSize(sf::Vector2f(50.0f, 100.0f)); 
        shape.setPosition(x, y); 
        shape.setFillColor(sf::Color::Red); 
        speed = 200.0f; 
    }

    void move(float deltaTime, sf::Keyboard::Key leftKey, sf::Keyboard::Key rightKey) {
        if (sf::Keyboard::isKeyPressed(leftKey)) {
            shape.move(-speed * deltaTime, 0.0f); 
        }
        if (sf::Keyboard::isKeyPressed(rightKey)) {
            shape.move(speed * deltaTime, 0.0f); 
        }
    }
};

class Floor {
public:
    sf::RectangleShape shape;

    Floor(float x, float y) {
        shape.setSize(sf::Vector2f(800.0f, 50.0f));
        shape.setPosition(x, y); 
        shape.setFillColor(sf::Color::Green); 
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego Simple - Jugador y Piso");

    Player player(375.0f, 450.0f);
    Floor floor(0.0f, 550.0f);

    sf::Clock clock;
    float deltaTime = 0.0f;

    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        player.move(deltaTime, sf::Keyboard::Left, sf::Keyboard::Right);

        window.clear();

        window.draw(floor.shape);
        window.draw(player.shape);
        window.display();
    }

    return 0;
}


//g++ -o juego main.cpp -lsfml-graphics -lsfml-window -lsfml-system
