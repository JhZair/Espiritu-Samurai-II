#include "Animaciones.h"
#include <iostream>

Animar::Animar() : 
    currentFrame(0),
    currentTime(0),
    loop(true),
    isPlaying(true),
    estadoActual(EstadoAnimacion::IDLE) {
}

Animar::~Animar() {
}

void Animar::configurarAnimacion(
    EstadoAnimacion estado, 
    const std::string& path, 
    int ancho, 
    int alto, 
    int frames, 
    float tiempoFrame
) {
    rutas[estado] = path;
    anchos[estado] = ancho;
    altos[estado] = alto;
    numFrames[estado] = frames;
    tiemposFrame[estado] = tiempoFrame;
}

bool Animar::cargarTodasLasTexturas() {
    bool success = true;
    
    for (const auto& par : rutas) {
        EstadoAnimacion estado = par.first;
        const std::string& ruta = par.second;
        
        if (!texturas[estado].loadFromFile(ruta)) {
            std::cerr << "Error cargando textura: " << ruta << std::endl;
            success = false;
        }
    }
    
    if (success) {
        cambiarEstado(EstadoAnimacion::IDLE);
    }
    
    return success;
}

void Animar::setTransparentColor(sf::Color color, EstadoAnimacion estado) {
    auto it = texturas.find(estado);
    if (it != texturas.end()) {
        sf::Image spriteImage = it->second.copyToImage();
        spriteImage.createMaskFromColor(color);
        it->second.loadFromImage(spriteImage);
        if (estado == estadoActual) {
            setTexture(it->second);
        }
    }
}

void Animar::updateAnimation(float deltaTime) {
    if (!isPlaying) return;
    
    float tiempoFrameActual = tiemposFrame[estadoActual];
    int framesActuales = numFrames[estadoActual];
    int anchoActual = anchos[estadoActual];
    int altoActual = altos[estadoActual];
    
    currentTime += deltaTime;
    
    if (currentTime >= tiempoFrameActual) {
        currentTime -= tiempoFrameActual;
        
        currentFrame++;
        if (currentFrame >= framesActuales) {
            if (loop) {
                currentFrame = 0;
            } else {
                currentFrame = framesActuales - 1;
                isPlaying = false;
                return;
            }
        }
        
        frameRect.left = currentFrame * anchoActual;
        frameRect.top = 0;
        frameRect.width = anchoActual;
        frameRect.height = altoActual;
        setTextureRect(frameRect);
    }
}

void Animar::cambiarEstado(EstadoAnimacion nuevoEstado) {
    if (estadoActual != nuevoEstado) {
        auto itTextura = texturas.find(nuevoEstado);
        
        if (itTextura != texturas.end()) {
            estadoActual = nuevoEstado;
            setTexture(itTextura->second);
            
            frameRect.width = anchos[nuevoEstado];
            frameRect.height = altos[nuevoEstado];
            resetAnimation();
        } else {
            std::cerr << "Animación no encontrada para el estado solicitado." << std::endl;
        }
    }
}

void Animar::resetAnimation() {
    currentFrame = 0;
    currentTime = 0;
    frameRect.left = 0;
    frameRect.top = 0;
    setTextureRect(frameRect);
}

void Animar::draw(sf::RenderWindow& window) {
    window.draw(*this);
}

void Animar::setPosition(float x, float y) {
    sf::Sprite::setPosition(x, y);
}