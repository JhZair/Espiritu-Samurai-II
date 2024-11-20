#include <SFML/Graphics.hpp>
#include <iostream>
#include "Luchador.h"
#include <vector>

Luchador::Luchador(float x, float y, sf::Color color) : velocidad(200.0f), gravity(1100.5f), velocityY(0), jumpStrength(-480.0f),
                                                        isJumping(false), maxhealth(200), health(maxhealth), lives(2), retroceso_x(0.0f),
                                                        retroceso_y(0.0f), reapareciendo(false), isDefending(false), velocidadNormal(200.0f), velocidadReducida(50.0f)
{
    rectan.setSize(sf::Vector2f(50.0f, 100.0f));
    rectan.setPosition(x, y);
    rectan.setFillColor(color);

    hitbox.setSize(sf::Vector2f(115.0f, 150.0f));
    hitbox.setOrigin(35.0f, 50.0f);
    hitbox.setPosition(rectan.getPosition());
    hitbox.setFillColor(sf::Color(255, 0, 0, 100)); // Cambiar último 0 para ver hitbox
}

void Luchador::lanzarCuchillo()
{
    if (clock.getElapsedTime().asSeconds() >= 2) {
        Cuchillo cuchillo(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 2);
        cuchillos.push_back(cuchillo);
        clock.restart(); // Reinicia el reloj para medir el tiempo nuevamente
    }
}

void Luchador::move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY, sf::Keyboard::Key defensa)
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
    if (sf::Keyboard::isKeyPressed(up) && !isJumping)
    {
        velocityY = jumpStrength;
        isJumping = true;
    }
    if (sf::Keyboard::isKeyPressed(defensa)) {
        isDefending = true;
        velocidad = velocidadReducida;
    } else {
        isDefending = false;
        velocidad = velocidadNormal;
    }

    rectan.move(0.0f, velocityY * tiempoDelta);
    hitbox.setPosition(rectan.getPosition());

    // Aplicar retroceso
    rectan.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);
    hitbox.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);

    // Reducir gradualmente el retroceso
    retroceso_x *= 0.9f;
    retroceso_y *= 0.9f;

    if (rectan.getPosition().y + rectan.getSize().y >= pisoY)
    {
        rectan.setPosition(rectan.getPosition().x, pisoY - rectan.getSize().y);
        velocityY = 0;
        isJumping = false;

        retroceso_y = 0.0f;
    }
}

void Luchador::recibirAtaque(float damage, sf::Vector2f retroceso)
{   
    if (isDefending) {
        damage /= 2;
        retroceso_x = retroceso.x * 2.0f;
        retroceso_y = retroceso.y * 3.0f;
    }else
    {
        retroceso_x = retroceso.x * 6.0f;
        retroceso_y = retroceso.y * 5.0f;    
    }
    health -= damage;
    isJumping = true;
    if (health <= 0) {
        health = maxhealth;
        reducirVidas({400.0f, -rectan.getSize().y});
    }
}

void Luchador::reducirVidas(sf::Vector2f posicionInicial)
{
    lives--;
    rectan.setPosition(posicionInicial);
    hitbox.setPosition(posicionInicial);

    retroceso_x = 0.0f;
    retroceso_y = 0.0f;
}

void Luchador::actualizarCuchillos(float tiempoDelta)
{
    for (auto &cuchillo : cuchillos)
    {
        cuchillo.mover(tiempoDelta);
    }

    cuchillos.erase(
        std::remove_if(cuchillos.begin(), cuchillos.end(), [](Cuchillo &cuchillo)
                       { return cuchillo.getPosicion().x > 800; }),
        cuchillos.end());
}

void Luchador::drawHealthBar(sf::RenderWindow &window, sf::Vector2f position)
{
    int anchoBarraMax = 200;
    int altoBarra = 30;
    float anchoBarraActual = (static_cast<float>(health) / maxhealth) * anchoBarraMax;

    sf::RectangleShape barraTotal(sf::Vector2f(anchoBarraMax, altoBarra));
    barraTotal.setPosition(position);
    barraTotal.setFillColor(sf::Color(100, 100, 100));
    barraTotal.setOutlineColor(sf::Color::Black);
    barraTotal.setOutlineThickness(2);

    sf::RectangleShape barraSalud(sf::Vector2f(anchoBarraActual, altoBarra));
    barraSalud.setPosition(position);
    barraSalud.setFillColor(sf::Color::Green);

    window.draw(barraTotal);
    window.draw(barraSalud);
}
