#include <SFML/Graphics.hpp>
#include <vector>

class Cuchillo {
public:
    sf::RectangleShape forma;
    float velocidad = 500.0f; // Velocidad del cuchillo

    Cuchillo(float x, float y) {
        forma.setSize(sf::Vector2f(30.0f, 5.0f)); // Tamaño del cuchillo
        forma.setPosition(x, y);
        forma.setFillColor(sf::Color::White); // Color del cuchillo
    }

    void mover(float tiempoDelta) {
        forma.move(velocidad * tiempoDelta, 0.0f); // Movimiento hacia la derecha
    }

    sf::Vector2f getPosicion() {
        return forma.getPosition();
    }
};

class Luchador {
public:
    sf::RectangleShape rectan;
    float velocidad;
    float gravity = 1100.5f;
    float velocityY = 0;
    float jumpStrength = -480.0f; 
    bool isJumping = false;
    std::vector<Cuchillo> cuchillos; // Vector para almacenar los cuchillos

    Luchador(float x, float y, sf::Color color) {
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

    void lanzarCuchillo() {
        // Crea un nuevo cuchillo en la posición actual del jugador
        Cuchillo cuchillo(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 2);
        cuchillos.push_back(cuchillo);
    }

    void actualizarCuchillos(float tiempoDelta) {
        // Mover cada cuchillo y eliminar los que salen de la ventana
        for (auto& cuchillo : cuchillos) {
            cuchillo.mover(tiempoDelta);
        }
        
        // Eliminar cuchillos que salgan de la pantalla
        cuchillos.erase(
            std::remove_if(cuchillos.begin(), cuchillos.end(), [](Cuchillo& cuchillo) { return cuchillo.getPosicion().x > 800; }),
            cuchillos.end()
        );
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

    Luchador jugador1(375.0f, 450.0f, sf::Color::Red);
    Luchador jugador2(175.0f, 450.0f, sf::Color::Blue); // Segundo jugador
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
            // Detectar cuando se presiona "O" para lanzar un cuchillo con jugador1
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::O) {
                    jugador1.lanzarCuchillo();
                }
                // Detectar cuando se presiona "P" para lanzar un cuchillo con jugador2
                if (event.key.code == sf::Keyboard::P) {
                    jugador2.lanzarCuchillo();
                }
            }
        }

        // Mover y actualizar cuchillos de ambos jugadores
        jugador1.move(tiempoDelta, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, piso.rectan.getPosition().y);
        jugador2.move(tiempoDelta, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, piso.rectan.getPosition().y);

        jugador1.actualizarCuchillos(tiempoDelta);
        jugador2.actualizarCuchillos(tiempoDelta);

        window.clear(sf::Color::Black); // Fondo negro

        window.draw(piso.rectan);
        window.draw(jugador1.rectan);
        window.draw(jugador2.rectan);

        // Dibujar todos los cuchillos de jugador1
        for (auto& cuchillo : jugador1.cuchillos) {
            window.draw(cuchillo.forma);
        }
        // Dibujar todos los cuchillos de jugador2
        for (auto& cuchillo : jugador2.cuchillos) {
            window.draw(cuchillo.forma);
        }

        window.display();
    }

    return 0;
}
//jugador 1 dispara con o 
//jugadpr 2 dispara con p
