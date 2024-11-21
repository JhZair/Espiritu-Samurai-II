#ifndef SAMURAI_H
#define SAMURAI_H

#include "Luchador.h"

class Samurai : public Luchador {
private:
    int remainingJumps;
public:
    Samurai(float x, float y, sf::Color color);
    void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY, sf::Keyboard::Key defensa) override;
    void usarUltimate(Luchador& oponente) override;

    // Getters y Setters
    int getRemainingJumgs() const { return remainingJumps; }
    void setRemainingJumgs(int rJumps) { remainingJumps = rJumps; }
};

#endif
