#ifndef LUCHADOR_H
#define LUCHADOR_H

#include <SFML/Graphics.hpp>
#include "Cuchillo.h"
#include "Animaciones.h"

class Luchador: public Animacion
{
public:

    sf::RectangleShape rectan;
    sf::RectangleShape hitbox;
    float velocidad;
    float gravity;
    float velocityY;
    float jumpStrength;
    bool isJumping;
    float maxhealth;
    float health;
    int lives;
    

    std::vector<Shuriken> shurikens;


    Luchador(float x, float y, sf::Color color);
    virtual ~Luchador() = default;
    virtual void lanzarCuchillo();
    virtual void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY);
    void recibirAtaque(float damage);
    void actualizarCuchillos(float tiempoDelta);
    void drawHealthBar(sf::RenderWindow& window, sf::Vector2f position);
 
};
#endif