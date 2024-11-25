#include <SFML/Graphics.hpp>
#include "Animaciones.h"
#include <iostream>
#include <vector>


// Método para cargar los sprites desde una hoja de sprites
std::vector<sf::Sprite> Animacion::cargarSprites(const std::string& rutaHoja, int numSprites, float anchoSprite, int altoSprite, sf::Color colorKey, bool espejo) {
    std::vector<sf::Sprite> sprites;

    // Crear una textura independiente para esta animación
    std::unique_ptr<sf::Texture> textura = std::make_unique<sf::Texture>();
    sf::Image imagen;

    // Cargar la imagen de la hoja de sprites
    if (!imagen.loadFromFile(rutaHoja)) {
        std::cerr << "Error: No se pudo cargar la imagen desde " << rutaHoja << std::endl;
        return sprites;
    }

    // Configurar el color transparente
    imagen.createMaskFromColor(colorKey);

    // Crear una textura a partir de la imagen con transparencia
    if (!textura->loadFromImage(imagen)) {
        std::cerr << "Error: No se pudo cargar la textura desde la imagen" << std::endl;
        return sprites;
    }

    // Crear sprites individuales
    for (int i = 0; i < numSprites; ++i) {
        sf::IntRect rect(i * anchoSprite, 0, anchoSprite, altoSprite);
        sf::Sprite sprite(*textura, rect); // Asocia la textura independiente a cada sprite

        // Espejar si es necesario
        if (espejo) {
            sprite.setScale(-1.f, 1.f);
            sprite.setOrigin(static_cast<float>(anchoSprite), 0.f);
        }

        sprites.push_back(sprite);
    }

    // Almacenar la textura para que no sea destruida
    texturas.push_back(std::move(textura));

    std::cout << "Sprites creados: " << sprites.size() << std::endl;
    return sprites;
}



// Obtener el sprite en un índice específico
const sf::Sprite& Animacion::getSprite(size_t indice) const {
    return sprites.at(indice); // Retorna por referencia para evitar copias
}

// Obtener la cantidad de sprites
size_t Animacion::getNumSprites() const {
    return sprites.size();
}

// Dibujar un sprite específico en una ventana
void Animacion::dibujarSprite(sf::RenderWindow& ventana, size_t indice, float x, float y) {
    if (indice < sprites.size()) {
        sf::Sprite sprite = sprites[indice];
        sprite.setPosition(x, y);
        ventana.draw(sprite);
    }
}
