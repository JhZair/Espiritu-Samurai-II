#include "Cuchillo.h"

Shuriken::Shuriken(float x, float y) : velocidad(500.0f)
{
    forma.setSize(sf::Vector2f(30.0f, 5.0f));
    forma.setPosition(x, y);
    forma.setFillColor(sf::Color::White);
};

void Shuriken::mover(float tiempoDelta) {
    forma.move(velocidad * tiempoDelta, 0.0f);
}

sf::Vector2f Shuriken::getPosicion() {
    return forma.getPosition();
}
