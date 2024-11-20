#ifndef HANZO_H
#define HANZO_H

#include "Luchador.h"

class Hanzo : public Luchador {
public:
    Hanzo(float x, float y, sf::Color color);
    void lanzarCuchillo() override;
};

#endif
