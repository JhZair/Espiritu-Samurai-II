#include "Hanzo.h"
#include <SFML/Graphics.hpp>

Hanzo::Hanzo(float x, float y, sf::Color color) : Luchador(x, y, color) {}

void Hanzo::lanzarCuchillo() {
    Cuchillo cuchillo1(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 3);
        Cuchillo cuchillo2(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + 2 * rectan.getSize().y / 3);
        cuchillos.push_back(cuchillo1);
        cuchillos.push_back(cuchillo2);
}
