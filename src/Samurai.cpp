#include "Samurai.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Samurai::Samurai(float x, float y, sf::Color color) : Luchador(x, y, color), remainingJumps(25) {}

void Samurai::move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY, sf::Keyboard::Key defensa)
{
    if (sf::Keyboard::isKeyPressed(izquierda))
    {
        rectan.move(-velocidad * tiempoDelta, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(derecha))
    {
        rectan.move(velocidad * tiempoDelta, 0.0f);
    }

    if (isJumping)
    {
        velocityY += gravity * tiempoDelta;
    }

    if (sf::Keyboard::isKeyPressed(up) && remainingJumps > 0)
    {
        isJumping = true;
        velocityY = jumpStrength;
        remainingJumps--;
    }
    if (sf::Keyboard::isKeyPressed(defensa)) {
        isDefending = true;
        velocidad = velocidadReducida;
    } else {
        isDefending = false;
        velocidad = velocidadNormal;
    }
    rectan.move(0.0f, velocityY * tiempoDelta);
    hitbox.setPosition(rectan.getPosition()); // Actualizar la posición de la hitbox

    // Aplicar retroceso
    rectan.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);
    hitbox.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);

    // Reducir gradualmente el retroceso
    retroceso_x *= 0.9f;
    retroceso_y *= 0.9f;

    // Comprobar colisión con el piso
    if (rectan.getPosition().y + rectan.getSize().y >= pisoY)
    {
        rectan.setPosition(rectan.getPosition().x, pisoY - rectan.getSize().y);
        velocityY = 0;
        isJumping = false;
        remainingJumps = 25;
        retroceso_y = 0.0f;
    }
}

void Samurai::usarUltimate(Luchador& oponente) {
    health += maxhealth * 0.55f;
    if (health > maxhealth) {
        health = maxhealth;  // No exceder la salud máxima
    }
    energia = 0.0f;
}