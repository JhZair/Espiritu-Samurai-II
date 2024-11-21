#ifndef LUCHADOR_H
#define LUCHADOR_H

#include <SFML/Graphics.hpp>
#include "Cuchillo.h"
#include "Animaciones.h"
#include <vector>

class Luchador : public Animación
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
    float energia;
    bool isDefending;
    float velocidadNormal;
    float velocidadReducida;
    bool reapareciendo;
    float retroceso_x;
    float retroceso_y;
    
    sf::Clock clock;
    std::vector<Cuchillo> cuchillos;

    Luchador(float x, float y, sf::Color color);
    virtual ~Luchador() = default;
    virtual void lanzarCuchillo();
    virtual void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY, sf::Keyboard::Key defensa);
    virtual void usarUltimate(Luchador& oponente);
    void recibirAtaque(float damage, sf::Vector2f retroceso);
    void reducirVidas(sf::Vector2f posicionInicial);
    void actualizarCuchillos(float tiempoDelta);
    void aumentarEnergia(float cantidad);
    void drawHealthBar(sf::RenderWindow& window, sf::Vector2f position);
    void drawEnergiaBar(sf::RenderWindow& window, sf::Vector2f position);    
};

#endif