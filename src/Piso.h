#ifndef PISO_H
#define PISO_H

#include <SFML/Graphics.hpp>

class Piso {
    sf::RectangleShape rectan;
public:
    Piso(float x, float y);

    // Getters y Setters
    const sf::RectangleShape& getRectan() const { return rectan; }
    void setRectan(const sf::RectangleShape& rect) { rectan = rect; }
};

#endif
