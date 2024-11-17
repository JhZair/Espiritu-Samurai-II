#include "Piso.h"

Piso::Piso(float x, float y) {
    rectan.setSize(sf::Vector2f(800.0f, 50.0f));
    rectan.setPosition(x, y);
    rectan.setFillColor(sf::Color::Black);
}
