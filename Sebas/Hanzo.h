#ifndef HANZO_H
#define HANZO_H

#include "Luchador.h"

class Hanzo : public Luchador {
    std::vector<sf::Sprite> ultimates;
public:
    Hanzo(float x, float y, sf::Color color);
    void lanzarShurikens() override;
    void usarUltimate(Luchador& oponente) override;
    void actualizarUltimates(float tiempoDelta, float direccion);

    // Getters y Setters
    const std::vector<sf::Sprite>& getUltimates() const { return ultimates; }
    void setUltimates(const std::vector<sf::Sprite>& UltimateList) { ultimates = UltimateList; }

};

#endif
