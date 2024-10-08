#include <SFML/Graphics.hpp>

class Jugador {
public:
    sf::RectangleShape rectan;
    float velocidad;
    float gravity = 20.5f;
    float velocityY = 0;
    float jumpStrength = -80.0f; // Upward velocity for jumping
    bool isJumping = false; // Flag to check if the player is jumping

    Jugador(float x, float y) {
        rectan.setSize(sf::Vector2f(50.0f, 100.0f)); 
        rectan.setPosition(x, y); 
        rectan.setFillColor(sf::Color::Red); 
        velocidad = 200.0f; 
    }

    void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY) {
    // Horizontal Movement
    if (sf::Keyboard::isKeyPressed(izquierda)) {
        rectan.move(-velocidad * tiempoDelta, 0.0f); 
    }
    if (sf::Keyboard::isKeyPressed(derecha)) {
        rectan.move(velocidad * tiempoDelta, 0.0f); 
    }

    // Apply gravity only when the player is jumping or falling
    if (isJumping) {
        velocityY += gravity * tiempoDelta;  // Gravity increases velocity downwards over time
    }

    // Jump logic - only if the player is not already jumping
    if (sf::Keyboard::isKeyPressed(up) && !isJumping) {
        velocityY = jumpStrength;  // Apply upward velocity
        isJumping = true;  // Mark as jumping
    }

    // Move the player vertically by the current velocity
    rectan.move(0.0f, velocityY * tiempoDelta);

    // Check if player has landed on the ground
    if (rectan.getPosition().y + rectan.getSize().y >= pisoY) {
        rectan.setPosition(rectan.getPosition().x, pisoY - rectan.getSize().y);  // Snap to the ground
        velocityY = 0;  // Reset vertical velocity
        isJumping = false;  // Allow jumping again
    }
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

    Jugador jugador1(375.0f, 450.0f);
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

        jugador1.move(tiempoDelta, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, piso.rectan.getPosition().y);

        window.clear();

        window.draw(piso.rectan);
        window.draw(jugador1.rectan);
        window.display();
    }

    return 0;
}
//g++ -o juego main.cpp -lsfml-graphics -lsfml-window -lsfml-system
