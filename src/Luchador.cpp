#include <SFML/Graphics.hpp>
#include <iostream>
#include "Luchador.h"
#include <vector>

Luchador::Luchador(float x, float y, sf::Color color) : 
    velocidad(200.0f), gravity(1100.5f), velocityY(0), jumpStrength(-480.0f),
    isJumping(false), maxhealth(200), health(maxhealth), lives(2), retroceso_x(0.0f),
    retroceso_y(0.0f), reapareciendo(false), isDefending(false), velocidadNormal(200.0f),
    velocidadReducida(50.0f), energia(0.0f), animacionActual("idle"), indiceSprite(0), 
    tiempoEntreSprites(0.13f)
{
    rectan.setSize(sf::Vector2f(50.0f, 100.0f));
    rectan.setPosition(x, y);
    rectan.setFillColor(color);

    hitbox.setSize(sf::Vector2f(115.0f, 150.0f));
    hitbox.setOrigin(35.0f, 50.0f);
    hitbox.setPosition(rectan.getPosition());
    hitbox.setFillColor(sf::Color(255, 0, 0, 100));
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
    reapareciendo = true;
    rectan.setPosition(posicionInicial);
    hitbox.setPosition(posicionInicial);

    retroceso_x = 0.0f;
    retroceso_y = 0.0f;
}

void Luchador::lanzarShurikens()
{
    if (clock.getElapsedTime().asSeconds() >= 2) {
        Shuriken shuriken(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 2);
        shurikens.push_back(shuriken);
        clock.restart();
    }
}

void Luchador::actualizarShurikens(float tiempoDelta, float direccion, Luchador& oponente)
{
    for (auto &shuriken : shurikens)
    {
        shuriken.mover(tiempoDelta, direccion);
        if(shuriken.getForma().getGlobalBounds().intersects(oponente.rectan.getGlobalBounds())){
            oponente.recibirAtaque(0.4f, sf::Vector2f(direccion * 15.0f, -50.0f));
        }
    }
    shurikens.erase(
        std::remove_if(shurikens.begin(), shurikens.end(), [](Shuriken &shuriken)
                       { return shuriken.getPosicion().x > 800; }),
        shurikens.end());
}

void Luchador::aumentarEnergia(float cantidad) {
    energia += cantidad;
    if (energia > 100.0f) energia = 100.0f;
    if (energia < 0.0f) energia = 0.0f;
}

void Luchador::usarUltimate(Luchador& oponente) {
    if (energia == 100.0f) { 
        energia = 0.0f;
    }
}

void Luchador::cambiarAnimacion(const std::string& nuevaAnimacion, float direccion) {
    if (direccion > 0) {
        if (animaciones.find(nuevaAnimacion) != animaciones.end()) {
            if (animacionActual != nuevaAnimacion) {
                animacionActual = nuevaAnimacion;
                indiceSprite = 0;
                relojSprite.restart();
            }
        }
    }
    if(direccion < 0) 
    {
        if (animacionesEspejadas.find(nuevaAnimacion) != animacionesEspejadas.end()) {
            if (animacionActual != nuevaAnimacion) {
                animacionActual = nuevaAnimacion;
                indiceSprite = 0;
                relojSprite.restart();
            }
        }
    }
}

void Luchador::actualizarAnimacion(float direccion) {
    if (relojSprite.getElapsedTime().asSeconds() >= tiempoEntreSprites) {
        if (direccion > 0) {
            indiceSprite = (indiceSprite + 1) % animaciones[animacionActual].size();
        } else {
            indiceSprite = (indiceSprite + 1) % animacionesEspejadas[animacionActual].size();
        }
        relojSprite.restart();
    }
}

void Luchador::dibujar(sf::RenderWindow& window, float direccion) {
    actualizarAnimacion(direccion);
    if (direccion > 0) {
        sf::Sprite& spriteActual = animaciones[animacionActual][indiceSprite];
        spriteActual.setPosition(rectan.getPosition());
        window.draw(spriteActual);
    } else {
        sf::Sprite& spriteActual = animacionesEspejadas[animacionActual][indiceSprite];
        spriteActual.setPosition(rectan.getPosition());
        window.draw(spriteActual);
    }
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

void Luchador::drawEnergiaBar(sf::RenderWindow& window, sf::Vector2f position) {
    int anchoBarra = 200;
    int altoBarra = 10;
    float anchoBarraActual = (static_cast<float>(energia) / 100.0f) * anchoBarra;

    sf::RectangleShape barraTotal(sf::Vector2f(anchoBarra, altoBarra));
    barraTotal.setPosition(position);
    barraTotal.setFillColor(sf::Color(100, 100, 100));
    barraTotal.setOutlineColor(sf::Color::Black);
    barraTotal.setOutlineThickness(2);

    sf::RectangleShape barraEnergia(sf::Vector2f(anchoBarraActual, altoBarra));
    barraEnergia.setPosition(position);
    barraEnergia.setFillColor(sf::Color::White);

    window.draw(barraTotal);
    window.draw(barraEnergia);
}
