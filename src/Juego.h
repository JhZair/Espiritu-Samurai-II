#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include "Luchador.h"
#include "Hanzo.h"
#include "Samurai.h"
#include "Piso.h"
#include "Animaciones.h"

class Juego
{
public:
    Juego();
    ~Juego();

    void ejecutar();

private:
    sf::RenderWindow window;
    sf::Clock reloj;
    sf::Clock relojMov;
    Piso piso;

    Luchador* jugador1;
    Luchador* jugador2;

    float tiempoDelta;
    float tiempoPartida;
    float inicioTiempo;
    bool animationsInitialized;

    float direccion1;
    float direccion2;

    void procesarEventos();
    void actualizar();
    void renderizar();

    void inicializarAnimaciones();

    void reiniciarJugadores();
    void manejarAtaques(const sf::Event& event);
    void manejarProyectiles(const sf::Event& event);
    void verificarDerrota(Luchador* jugador, const std::string& ganador);
    void determinarGanador();
    void dibujarTiempoRestante();
    float calcularTiempoRestante();
};

#endif