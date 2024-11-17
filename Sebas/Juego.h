#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include "Hanzo.h"
#include "Samurai.h"
#include "Piso.h"
#include "Luchador.h"
#include "Cuchillo.h"
#include "Animaciones.h"

class Juego {
private:
    sf::RenderWindow window;
    Luchador* jugador1;
    Luchador* jugador2;
    Piso piso;
    sf::Clock reloj;
    float tiempoDelta;
    bool animationsInitialized;

public:
    Juego();
    ~Juego();
    void ejecutar();

private:
    void procesarEventos();
    void actualizar();
    void renderizar();
    void inicializarAnimaciones();
};

#endif