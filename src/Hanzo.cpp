#include "Hanzo.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Hanzo::Hanzo(float x, float y, sf::Color color) : Luchador(x, y, color) {}

void Hanzo::lanzarShurikens() {
    if (clock.getElapsedTime().asSeconds() >= 2) {
        Shuriken shuriken1(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 3);
        Shuriken shuriken2(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + 2 * rectan.getSize().y / 3);
        shurikens.push_back(shuriken1);
        shurikens.push_back(shuriken2);
        clock.restart();
    }
}

void Hanzo::usarUltimate(Luchador& oponente) {
    sf::CircleShape ultimate(40.0f); // Puedes ajustar el tamaño
    ultimate.setPosition(rectan.getPosition().x + 50, rectan.getPosition().y); // Posición inicial
    ultimate.setFillColor(sf::Color::Yellow); // Color de la Ultimate
    ultimates.push_back(ultimate);
    energia = 0.0f;
}

void Hanzo::actualizarUltimates(float tiempoDelta, float direccion) {
    for (auto& ultimate : ultimates) {
        ultimate.move(direccion * 1400.0f * tiempoDelta, 0); // Mueve la Ultimate
    }
    ultimates.erase(
        std::remove_if(ultimates.begin(), ultimates.end(), [](const sf::CircleShape& ultimate) {
            return ultimate.getPosition().x > 800; // Fuera de la pantalla
        }),
        ultimates.end()
    );
}
