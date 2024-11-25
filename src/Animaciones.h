#ifndef ANIMACION_H
#define ANIMACION_H

#include <SFML/Graphics.hpp>
#include <vector>

class Animacion {
private:
    std::vector<sf::Sprite> sprites; // Vector de sprites individuales
    std::vector<std::unique_ptr<sf::Texture>> texturas; // Almacena las texturas únicas
    sf::Texture spriteSheet;         // Hoja de spites
public:
    Animacion() = default;

    std::vector<sf::Sprite> cargarSprites(const std::string& rutaHoja, int numSprites, float anchoSprite, int altoSprite, sf::Color colorKey, sf::Color tinte, bool espejo);
};

#endif 
