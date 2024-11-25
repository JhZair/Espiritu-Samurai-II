#include "Piso.h"
#include <SFML/Graphics.hpp>

Piso::Piso(float x, float y, float width, float height) {
    rectan.setPosition(x+100.0f, y);  // Posición del piso
    rectan.setSize(sf::Vector2f(width, height));  // Tamaño del piso
    rectan.setFillColor(sf::Color::Black);
}

