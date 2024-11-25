#ifndef PISO_H
#define PISO_H

#include <SFML/Graphics.hpp>

class Piso {
    sf::RectangleShape rectan;
public:
    // Piso(float x, float y);
    Piso(float x, float y, float width, float height);

    // Getters y Setters
    const sf::RectangleShape& getRectan() const { return rectan; }
    void setRectan(const sf::RectangleShape& rect) { rectan = rect; }

    // Método para verificar colisión con el luchador
    bool colisionaCon(const sf::RectangleShape& luchador) const {
        return rectan.getGlobalBounds().intersects(luchador.getGlobalBounds());
    }

    // Obtener las coordenadas del piso
    float getPosY() const { return rectan.getPosition().y; }
};

#endif
