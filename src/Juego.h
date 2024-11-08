#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include "Luchador.h"
#include "Hanzo.h"
#include "Samurai.h"
#include "Piso.h"

class Juego {
private:
    sf::RenderWindow window;
    Luchador* jugador1;
    Luchador* jugador2;
    Piso piso;
    sf::Clock reloj;
    float tiempoDelta;

public:
    Juego();
    ~Juego();
    void ejecutar();

private:
    void procesarEventos();
    void actualizar();
    void renderizar();
};

#endif