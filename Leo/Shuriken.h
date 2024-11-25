#ifndef SHURIKEN_H
#define SHURIKEN_H

#include <SFML/Graphics.hpp>

class Shuriken
{
private:
    sf::RectangleShape forma;
    float velocidad;
public:
    Shuriken(float x, float y);
    void mover(float tiempoDelta, float direccion);
    sf::Vector2f getPosicion();

    // Getters y Setters
    const sf::RectangleShape& getForma() const { return forma; }
    void setForma(const sf::RectangleShape& rect) { forma = rect; }

    float getVelocidad() const { return velocidad; }
    void setVelocidad(float _velocidad) { velocidad = _velocidad; }
};
#endif