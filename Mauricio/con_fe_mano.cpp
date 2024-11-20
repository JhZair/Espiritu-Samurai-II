//John Zair Oros Perez
//Leonardo André Loayza Paucar
//Mauricio Jerson Payehuanca Diaz
//Sebastian Fabian Flores Pro

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream> 

class Cuchillo {
public:
    sf::RectangleShape forma;
    float velocidad = 500.0f;

    Cuchillo(float x, float y) {
        forma.setSize(sf::Vector2f(30.0f, 5.0f));
        forma.setPosition(x, y);
        forma.setFillColor(sf::Color::White);
    }

    void mover(float tiempoDelta) {
        forma.move(velocidad * tiempoDelta, 0.0f);
    }

    sf::Vector2f getPosicion() {
        return forma.getPosition();
    }
};

class Luchador {
public:
    sf::RectangleShape rectan;
    sf::RectangleShape hitbox;
     float energia = 0.0f;
    float velocidad;
    float gravity = 1100.5f;
    float velocityY = 0;
    float jumpStrength = -480.0f;
    bool isJumping = false;
    float maxhealth = 200;
    float health = maxhealth;
    int lives = 2;
    sf::Clock clock;
    std::vector<Cuchillo> cuchillos;

    Luchador(float x, float y, sf::Color color) {
        rectan.setSize(sf::Vector2f(50.0f, 100.0f));
        rectan.setPosition(x, y);
        rectan.setFillColor(color);

        hitbox.setSize(sf::Vector2f(150.0f, 150.0f));
        hitbox.setOrigin(50.0f, 75.0f);
        hitbox.setPosition(rectan.getPosition());
        hitbox.setFillColor(sf::Color(0, 0, 0, 0));

        velocidad = 200.0f;
        energia=0.0f;
    }

    virtual void usarUltimate(Luchador& oponente) {
    if (energia == 100.0f) {  // Solo si la energía está llena
        std::cout << "Ultimate activada pero no definida para este luchador." << std::endl;
        energia = 0.0f;  // Restablece la energía después de usar la ultimate
    }
}

    virtual void lanzarCuchillo() {
    // Crea un nuevo cuchillo en la posición actual del jugador
    if (clock.getElapsedTime().asSeconds() >= 2) {
        Cuchillo cuchillo(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 2);
        cuchillos.push_back(cuchillo);
        clock.restart(); // Reinicia el reloj para medir el tiempo nuevamente
    }
}

    virtual void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY) {
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
        hitbox.setPosition(rectan.getPosition());

        if (rectan.getPosition().y + rectan.getSize().y >= pisoY) {
            rectan.setPosition(rectan.getPosition().x, pisoY - rectan.getSize().y);
            velocityY = 0;
            isJumping = false;
        }
    }

    void recibirAtaque(float damage) {
        health -= damage;
        if (health <= 0) {
            health = maxhealth;
            lives--;
        }
    }

    void aumentarEnergia(float cantidad) {
    energia += cantidad;
    if (energia > 100.0f) energia = 100.0f;
    if (energia < 0.0f) energia = 0.0f;
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

    void drawHealthBar(sf::RenderWindow& window, sf::Vector2f position) {
        int anchoBarraMax = 200;
        int altoBarra = 30;
        float anchoBarraActual = (static_cast<float>(health) / maxhealth) * anchoBarraMax;

        sf::RectangleShape barraTotal(sf::Vector2f(anchoBarraMax, altoBarra));
        barraTotal.setPosition(position);
        barraTotal.setFillColor(sf::Color(100, 100, 100));
        barraTotal.setOutlineColor(sf::Color::Black);
        barraTotal.setOutlineThickness(2);

        sf::RectangleShape barraSalud(sf::Vector2f(anchoBarraActual, altoBarra));
        barraSalud.setPosition(position);
        barraSalud.setFillColor(sf::Color::Green);

        window.draw(barraTotal);
        window.draw(barraSalud);
    }
    void drawEnergiaBar(sf::RenderWindow& window, sf::Vector2f position) {
    int anchoBarra = 200;
    int altoBarra = 10;
    float anchoBarraActual = (static_cast<float>(energia) / 100.0f) * anchoBarra;

    sf::RectangleShape barraTotal(sf::Vector2f(anchoBarra, altoBarra));
    barraTotal.setPosition(position);
    barraTotal.setFillColor(sf::Color(100, 100, 100));
    barraTotal.setOutlineColor(sf::Color::Black);
    barraTotal.setOutlineThickness(2);

    sf::RectangleShape barraEnergia(sf::Vector2f(anchoBarraActual, altoBarra));
    barraEnergia.setPosition(position);
    barraEnergia.setFillColor(sf::Color::White);

    window.draw(barraTotal);
    window.draw(barraEnergia);
}
};



class Hanzo : public Luchador {
public:
    std::vector<sf::CircleShape> ultimates; // Vector para almacenar la Ultimate

    Hanzo(float x, float y, sf::Color color) : Luchador(x, y, color) {}

    void lanzarCuchillo() override {
        if (clock.getElapsedTime().asSeconds() >= 2) {
            Cuchillo cuchillo1(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 3);
            Cuchillo cuchillo2(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + 2 * rectan.getSize().y / 3);
            cuchillos.push_back(cuchillo1);
            cuchillos.push_back(cuchillo2);
            clock.restart();
        }
    }

    void usarUltimate(Luchador& oponente) override {
        if (energia == 100.0f) {
            std::cout << "Hanzo lanza su bola gigante!" << std::endl;

            // Reduce la mitad de la barra de salud del oponente
            oponente.recibirAtaque(oponente.maxhealth / 2);

            // Crear la representación gráfica de la Ultimate
            sf::CircleShape ultimate(50.0f); // Puedes ajustar el tamaño
            ultimate.setPosition(rectan.getPosition().x + 50, rectan.getPosition().y); // Posición inicial
            ultimate.setFillColor(sf::Color::Yellow); // Color de la Ultimate
            ultimates.push_back(ultimate);

            // Restablece la energía después de usar la ultimate
            energia = 0.0f;
        }
    }

    void actualizarUltimates(float tiempoDelta) {
        for (auto& ultimate : ultimates) {
            ultimate.move(200.0f * tiempoDelta, 0); // Mueve la Ultimate hacia la derecha
        }

        // Eliminar Ultimate que se sale de la pantalla
        ultimates.erase(
            std::remove_if(ultimates.begin(), ultimates.end(), [](const sf::CircleShape& ultimate) {
                return ultimate.getPosition().x > 800; // Fuera de la pantalla
            }),
            ultimates.end()
        );
    }
};




class Samurai : public Luchador {
private:
    int remainingJumps = 45;

public:
    Samurai(float x, float y, sf::Color color) : Luchador(x, y, color) {}
    
    void usarUltimate(Luchador& oponente) override {
    if (energia == 100.0f) {
        std::cout << "Samurai se cura con su ultimate!" << std::endl;

        // Cura 3/4 de su barra de salud
        health += maxhealth * 0.75f;
        if (health > maxhealth) {
            health = maxhealth;  // No exceder la salud máxima
        }

        // Restablece la energía después de usar la ultimate
        energia = 0.0f;
    }
}

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
        hitbox.setPosition(rectan.getPosition());  // Actualizar la posición de la hitbox

        // Comprobar colisión con el piso
        if (rectan.getPosition().y + rectan.getSize().y >= pisoY) {
            rectan.setPosition(rectan.getPosition().x, pisoY - rectan.getSize().y);
            velocityY = 0;
            isJumping = false;
            remainingJumps = 80;
        }
    }
};



class Piso {
public:
    sf::RectangleShape rectan;

    Piso(float x, float y) {
        rectan.setSize(sf::Vector2f(800.0f, 50.0f));
        rectan.setPosition(x, y);
        rectan.setFillColor(sf::Color::Black);
    }
};




class Juego {
private:
    sf::RenderWindow window;
    Luchador* jugador1;
    Luchador* jugador2;
    Piso piso;
    sf::Clock reloj;
    float tiempoDelta;

public:
    Juego()
        : window(sf::VideoMode(800, 600), "Peleitas"),
          piso(0.0f, 550.0f),
          tiempoDelta(0.0f) {
          jugador1 = new Hanzo(175.0f, 450.0f, sf::Color::Yellow);
          jugador2 = new Samurai(375.0f, 450.0f, sf::Color::Red);
    }

    ~Juego() {
        delete jugador1;
        delete jugador2;
    }

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
            // Ataque del jugador 1 (tecla R)
            if (event.key.code == sf::Keyboard::R) {
                if (jugador1->hitbox.getGlobalBounds().intersects(jugador2->rectan.getGlobalBounds())) {
                    jugador2->recibirAtaque(5.0f);  // Jugador 2 pierde vida
                    jugador1->aumentarEnergia(8.0f); // Jugador 1 gana energía
                    std::cout << "Jugador 1 atacó a jugador 2" << std::endl;
                    std::cout << "Energía jugador 1: " << jugador1->energia << std::endl;
                    std::cout << "Energía jugador 2: " << jugador2->energia << std::endl;

                    if (jugador2->lives == 0) {
                        std::cout << "Jugador 1 gana!" << std::endl;
                        window.close();
                    }
                }
            }

            // Ataque del jugador 2 (tecla P)
            if (event.key.code == sf::Keyboard::P) {
                if (jugador2->hitbox.getGlobalBounds().intersects(jugador1->rectan.getGlobalBounds())) {
                    jugador1->recibirAtaque(5.0f);  // Jugador 1 pierde vida
                    jugador2->aumentarEnergia(8.0f); // Jugador 2 gana energía
                    std::cout << "Jugador 2 atacó a jugador 1" << std::endl;
                    std::cout << "Energía jugador 1: " << jugador1->energia << std::endl;
                    std::cout << "Energía jugador 2: " << jugador2->energia << std::endl;

                    if (jugador1->lives == 0) {
                        std::cout << "Jugador 2 gana!" << std::endl;
                        window.close();
                    }
                }
            }

            // Lanzar cuchillo por el jugador 1
            if (event.key.code == sf::Keyboard::Q) {
                jugador1->lanzarCuchillo();
            }

            // Lanzar cuchillo por el jugador 2
            if (event.key.code == sf::Keyboard::O) {
                jugador2->lanzarCuchillo();
            }
            //ULTIS
             if (event.key.code == sf::Keyboard::T) {
                jugador1->usarUltimate(*jugador2);
            }
            if (event.key.code == sf::Keyboard::I) {
                jugador2->usarUltimate(*jugador1);
            }
        }
    }
}



    void actualizar() {
    tiempoDelta = reloj.restart().asSeconds();
    jugador1->move(tiempoDelta, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, piso.rectan.getPosition().y);
    jugador2->move(tiempoDelta, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, piso.rectan.getPosition().y);

    jugador1->actualizarCuchillos(tiempoDelta);
    jugador2->actualizarCuchillos(tiempoDelta);
    static_cast<Hanzo*>(jugador1)->actualizarUltimates(tiempoDelta); // Actualiza las ultimates de Hanzo
}
    void renderizar() {
    window.clear(sf::Color::Blue);
    window.draw(piso.rectan);
    window.draw(jugador1->rectan);
    window.draw(jugador2->rectan);

    window.draw(jugador1->hitbox);
    window.draw(jugador2->hitbox);

    jugador1->drawHealthBar(window, sf::Vector2f(25.0f, 50.0f));
    jugador2->drawHealthBar(window, sf::Vector2f(575.0f, 50.0f));

    jugador1->drawEnergiaBar(window, sf::Vector2f(25.0f, 75.0f));
    jugador2->drawEnergiaBar(window, sf::Vector2f(575.0f, 75.0f));

    // Dibuja los cuchillos de ambos jugadores
    for (auto& cuchillo : jugador1->cuchillos) {
        window.draw(cuchillo.forma);
    }
    for (auto& cuchillo : jugador2->cuchillos) {
        window.draw(cuchillo.forma);
    }

    // Dibuja las ultimates de Hanzo
    for (const auto& ultimate : static_cast<Hanzo*>(jugador1)->ultimates) {
        window.draw(ultimate);
    }

    window.display();
}
};





int main() {
    Juego juego;
    juego.ejecutar();
    
    return 0;
}
