#ifndef SHURIKEN_H
#define SHURIKEN_H

#include <SFML/Graphics.hpp>

class Shuriken
{
public:
    sf::RectangleShape forma;
    float velocidad;

    Shuriken(float x, float y);

    void mover(float tiempoDelta, float direccion);

    sf::Vector2f getPosicion();
};
#endif