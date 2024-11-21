#include "Hanzo.h"
#include <SFML/Graphics.hpp>
#include <iostream> 
Hanzo::Hanzo(float x, float y, sf::Color color) : Luchador(x, y, color) {}

void Hanzo::lanzarCuchillo() {
    if (clock.getElapsedTime().asSeconds() >= 2) {
        Shuriken cuchillo1(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 3);
        Shuriken cuchillo2(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + 2 * rectan.getSize().y / 3);
        shurikens.push_back(cuchillo1);
        shurikens.push_back(cuchillo2);
        clock.restart();
    }
}
