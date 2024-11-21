#ifndef CUCHILLO_H
#define CUCHILLO_H

#include <SFML/Graphics.hpp>

class Shuriken
{
public:
    sf::RectangleShape forma;
    float velocidad;

    Shuriken(float x, float y);

    void mover(float tiempoDelta);

    sf::Vector2f getPosicion();
};
#endif