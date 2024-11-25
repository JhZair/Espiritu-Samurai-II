#include "Shuriken.h"
#include <SFML/Graphics.hpp>

Shuriken::Shuriken(float x, float y) : velocidad(500.0f)
{
    forma.setSize(sf::Vector2f(5.0f, 10.0f));
    forma.setPosition(x, y);
    forma.setFillColor(sf::Color(120,120,120));
};

void Shuriken::mover(float tiempoDelta, float direccion) {
    forma.move(direccion * velocidad * tiempoDelta, 0.0f);
}

sf::Vector2f Shuriken::getPosicion() {
    return forma.getPosition();
}
