#include "Cuchillo.h"

Cuchillo::Cuchillo(float x, float y) : velocidad(500.0f)
{
    forma.setSize(sf::Vector2f(30.0f, 5.0f));
    forma.setPosition(x, y);
    forma.setFillColor(sf::Color::White);
};

void Cuchillo::mover(float tiempoDelta) {
    forma.move(velocidad * tiempoDelta, 0.0f);
}

sf::Vector2f Cuchillo::getPosicion() {
    return forma.getPosition();
}
