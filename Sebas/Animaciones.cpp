#include "Animaciones.h"
#include <iostream>
Animacion::Animacion() : 
    currentFrame(0),
    frameCount(0),
    frameTime(0.1f),
    currentTime(0),
    loop(true),
    frameWidth(0),
    frameHeight(0),
    isPlaying(true)
{
}
Animacion::~Animacion(){}

bool Animacion::CargarTexture(const std::string& texturePath) {
    if (!spriteSheet.loadFromFile(texturePath)) {
        
        return false;
    }
    setTexture(spriteSheet);
    
    return true;
}

void Animacion::setTransparentColor(sf::Color color) {
    sf::Image spriteImage = spriteSheet.copyToImage();
    spriteImage.createMaskFromColor(color);
    spriteSheet.loadFromImage(spriteImage);
    setTexture(spriteSheet);
}

void Animacion::IniciarAnimation(int width, int height, int numFrames, float frameDuration, bool shouldLoop) {
    frameWidth = width;
    frameHeight = height;
    frameCount = numFrames;
    frameTime = frameDuration;
    loop = shouldLoop;
    
    frameRect = sf::IntRect(0, 0, frameWidth, frameHeight);
    setTextureRect(frameRect);
    
    // Resetear la animación
    currentFrame = 0;
    currentTime = 0;
}

void Animacion::updateAnimation(float deltaTime) {
    if (!isPlaying || frameCount <= 1) return;
    
    currentTime += deltaTime;
    
    if (currentTime >= frameTime) {
        currentTime -= frameTime;  // Restamos el tiempo transcurrido en lugar de ponerlo a 0
        
        currentFrame++;
        if (currentFrame >= frameCount) {
            if (loop) {
                currentFrame = 0;
            } else {
                currentFrame = frameCount - 1;
                isPlaying = false;
                return;
            }
        }
        
        // Actualizar el rectángulo de la textura
        frameRect.left = currentFrame * frameWidth;
        setTextureRect(frameRect);
    }
}

// void Animacion::resetAnimation() {
//     currentFrame = 0;
//     currentTime = 0;
//     frameRect.left = 0;
//     setTextureRect(frameRect);
// }
void Animacion::draw(sf::RenderWindow& window) {
    window.draw(*this);  // Dibuja el sprite con la animación
}
void Animacion::setPosition(float x , float y)
{
    sf::Sprite::setPosition(x, y);
}

void Animacion::setSingleColorFilter(sf::Color color) {
    sf::Image spriteImage = spriteSheet.copyToImage();

    // Recorrer todos los píxeles de la imagen
    for (unsigned int x = 0; x < spriteImage.getSize().x; ++x) {
        for (unsigned int y = 0; y < spriteImage.getSize().y; ++y) {
            sf::Color currentPixel = spriteImage.getPixel(x, y);

            // Ignorar los píxeles transparentes (si los hay)
            if (currentPixel.a != 0) {
                // Aplica el color deseado a todos los píxeles no transparentes
                spriteImage.setPixel(x, y, color);
            }
        }
    }

    spriteSheet.loadFromImage(spriteImage);
    setTexture(spriteSheet);
}