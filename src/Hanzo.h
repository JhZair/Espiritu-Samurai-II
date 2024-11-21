#ifndef HANZO_H
#define HANZO_H

#include "Luchador.h"

class Hanzo : public Luchador {
public:
    std::vector<sf::CircleShape> ultimates;

    Hanzo(float x, float y, sf::Color color);
    void lanzarCuchillo() override;
    void usarUltimate(Luchador& oponente) override;
    void actualizarUltimates(float tiempoDelta, float direccion);
};

#endif
