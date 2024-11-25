#ifndef SAMURAI_H
#define SAMURAI_H

#include "Luchador.h"

class Samurai : public Luchador {
private:
    int remainingJumps;

    std::unordered_map<std::string, std::vector<sf::Sprite>> animaciones;  // Animaciones normales
    std::unordered_map<std::string, std::vector<sf::Sprite>> animacionesEspejadas; // Animaciones espejadas
    std::string animacionActual;
    size_t indiceSprite;
    float tiempoEntreSprites;
    sf::Clock relojSprite;
public:
    Samurai(float x, float y, sf::Color color);
    void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, Piso& piso, sf::Keyboard::Key defensa, sf::Keyboard::Key ataque, sf::Keyboard::Key ataque_s, sf::Keyboard::Key ataque_p, Luchador& otroJugador, float direccion) override;
    void usarUltimate(Luchador& oponente) override;

    void cargarAnimaciones();
    void cambiarAnimacion(const std::string& nuevaAnimacion, float direccion);
    void actualizarAnimacion(float direccion);
    void dibujar(sf::RenderWindow& window, float direccion) override;

    // Getters y Setters
    int getRemainingJumgs() const { return remainingJumps; }
    void setRemainingJumgs(int rJumps) { remainingJumps = rJumps; }
};

#endif
