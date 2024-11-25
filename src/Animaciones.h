#ifndef ANIMACION_H
#define ANIMACION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animacion {
private:
    std::vector<sf::Sprite> sprites; // Vector de sprites individuales
    std::vector<std::unique_ptr<sf::Texture>> texturas; // Almacena las texturas únicas
    sf::Texture spriteSheet;         // Hoja de sprites
    sf::Texture textura;
    sf::Image imagen;
public:
    // Constructor vacío
    Animacion() = default;

    // Método para cargar los sprites desde una hoja de sprites
    std::vector<sf::Sprite> cargarSprites(const std::string& rutaHoja, int numSprites, float anchoSprite, int altoSprite, sf::Color colorKey, bool espejo);

    // Obtener el sprite en un índice específico
    const sf::Sprite& getSprite(size_t indice) const;

    // Obtener la cantidad de sprites
    size_t getNumSprites() const;

    // Dibujar un sprite específico en una ventana
    void dibujarSprite(sf::RenderWindow& ventana, size_t indice, float x, float y);
};

#endif // ANIMACION_H
