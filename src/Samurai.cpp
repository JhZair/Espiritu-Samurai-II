#include "Samurai.h"

Samurai::Samurai(float x, float y, sf::Color color) : Luchador(x, y, color), remainingJumps(45) {}

void Samurai::move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY)
{
    if (sf::Keyboard::isKeyPressed(izquierda) && rectan.getPosition().x > 0)
    {
        rectan.move(-velocidad * tiempoDelta, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(derecha) && rectan.getPosition().x < 750)
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

    rectan.move(0.0f, velocityY * tiempoDelta);
    hitbox.setPosition(rectan.getPosition()); // Actualizar la posición de la hitbox

    // Comprobar colisión con el piso
    if (rectan.getPosition().y + rectan.getSize().y >= pisoY)
    {
        rectan.setPosition(rectan.getPosition().x, pisoY - rectan.getSize().y);
        velocityY = 0;
        isJumping = false;
        remainingJumps = 45;
    }
}
