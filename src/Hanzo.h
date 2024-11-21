#ifndef HANZO_H
#define HANZO_H

#include "Luchador.h"

class Hanzo : public Luchador {
    std::vector<sf::CircleShape> ultimates;
public:
    Hanzo(float x, float y, sf::Color color);
    void lanzarShurikens() override;
    void usarUltimate(Luchador& oponente) override;
    void actualizarUltimates(float tiempoDelta, float direccion);

    // Getters y Setters
    const std::vector<sf::CircleShape>& getUltimates() const { return ultimates; }
    void setUltimates(const std::vector<sf::CircleShape>& UltimateList) { ultimates = UltimateList; }

};

#endif
