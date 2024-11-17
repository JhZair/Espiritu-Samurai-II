#include "Animaciones.h"
#include <iostream>
Animar::Animar() : 
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
Animar::~Animar(){}

bool Animar::CargarTexture(const std::string& texturePath) {
    if (!spriteSheet.loadFromFile(texturePath)) {
        
        return false;
    }
    setTexture(spriteSheet);
    
    return true;
}

void Animar::setTransparentColor(sf::Color color) {
    sf::Image spriteImage = spriteSheet.copyToImage();
    spriteImage.createMaskFromColor(color);
    spriteSheet.loadFromImage(spriteImage);
    setTexture(spriteSheet);
}

void Animar::IniciarAnimation(int width, int height, int numFrames, float frameDuration, bool shouldLoop) {
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

void Animar::updateAnimation(float deltaTime) {
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

void Animar::resetAnimation() {
    currentFrame = 0;
    currentTime = 0;
    frameRect.left = 0;
    setTextureRect(frameRect);
}
void Animar::draw(sf::RenderWindow& window) {
    window.draw(*this);  // Dibuja el sprite con la animación
}
void Animar::setPosition(float x , float y)
{
    sf::Sprite::setPosition(x, y);
}