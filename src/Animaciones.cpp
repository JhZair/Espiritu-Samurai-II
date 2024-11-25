#include <SFML/Graphics.hpp>
#include "Animaciones.h"
#include <iostream>
#include <vector>


// Método para cargar los sprites desde una hoja de sprites
std::vector<sf::Sprite> Animacion::cargarSprites(const std::string& rutaHoja, int numSprites, float anchoSprite, int altoSprite, sf::Color colorKey,  sf::Color tinte, bool espejo) {
    std::vector<sf::Sprite> sprites;

    std::unique_ptr<sf::Texture> textura = std::make_unique<sf::Texture>();
    sf::Image imagen;

    if (!imagen.loadFromFile(rutaHoja)) {
        std::cerr << "Error: No se pudo cargar la imagen desde " << rutaHoja << std::endl;
        return sprites;
    }

    imagen.createMaskFromColor(colorKey);

    if (!textura->loadFromImage(imagen)) {
        std::cerr << "Error: No se pudo cargar la textura desde la imagen" << std::endl;
        return sprites;
    }

    for (int i = 0; i < numSprites; ++i) {
        sf::IntRect rect(i * anchoSprite, 0, anchoSprite, altoSprite);
        sf::Sprite sprite(*textura, rect);

        // Aplicar el tinte al sprite
        sprite.setColor(tinte);

        if (espejo) {
            sprite.setScale(-1.f, 1.f);
            sprite.setOrigin(static_cast<float>(anchoSprite), 0.f);
        }

        sprites.push_back(sprite);
    }

    texturas.push_back(std::move(textura));

    return sprites;
}

