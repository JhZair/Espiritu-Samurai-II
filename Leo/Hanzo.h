#ifndef HANZO_H
#define HANZO_H

#include "Luchador.h"
#include <unordered_map>
#include <string>
#include <vector>

class Hanzo : public Luchador {
    std::vector<sf::CircleShape> ultimates;

    std::unordered_map<std::string, std::vector<sf::Sprite>> animaciones;  // Animaciones normales
    std::unordered_map<std::string, std::vector<sf::Sprite>> animacionesEspejadas; // Animaciones espejadas
    std::string animacionActual;
    size_t indiceSprite;
    float tiempoEntreSprites;
    sf::Clock relojSprite;
public:
    Hanzo(float x, float y, sf::Color color);
    void lanzarShurikens() override;
    void usarUltimate(Luchador& oponente) override;
    void actualizarUltimates(float tiempoDelta, float direccion);

    void cargarAnimaciones();
    void cambiarAnimacion(const std::string& nuevaAnimacion, float direccion);
    void actualizarAnimacion(float direccion);
    void dibujar(sf::RenderWindow& window, float direccion) override; // Para dibujar a Hanzo

    // Getters y Setters
    const std::vector<sf::CircleShape>& getUltimates() const { return ultimates; }
    void setUltimates(const std::vector<sf::CircleShape>& UltimateList) { ultimates = UltimateList; }

    void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, Piso& piso, sf::Keyboard::Key defensa, sf::Keyboard::Key ataque, sf::Keyboard::Key ataque_s, sf::Keyboard::Key ataque_p, Luchador& otroJugador, float direccion) override;
};

#endif
