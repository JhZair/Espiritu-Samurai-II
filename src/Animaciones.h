#include <SFML/Graphics.hpp>
#ifndef ANIMACIONES_H
#define ANIMACIONES_H

class Animacion: public sf::Sprite
{
    public:
        sf::Texture spriteSheet;     // Textura para el sprite sheet
        sf::IntRect frameRect;       // Rectángulo para el frame actual
        int currentFrame;            // Frame actual
        int frameCount;              // Número total de frames
        float frameTime;             // Tiempo entre frames
        float currentTime;           // Tiempo acumulado
        bool loop;                   // Si la animación debe repetirse
        int frameWidth;              // Ancho de cada frame
        int frameHeight;             // Alto de cada frame
        bool isPlaying;              // Comprobar si ta jugando   
            
         // Constructor
    Animacion();
    ~Animacion();
    // Métodos principales
    virtual bool CargarTexture(const std::string& texturePath);
    virtual void setTransparentColor(sf::Color color);
    virtual void IniciarAnimation(int frameWidth, int frameHeight, int numFrames, float frameTime = 0.1f, bool loop = true);
    virtual void updateAnimation(float deltaTime);
    // virtual void resetAnimation();
    virtual void draw(sf::RenderWindow& window);
    virtual void setPosition(float x, float y);
    void pauseAnimation() { isPlaying = false; }
    void playAnimation() { isPlaying = true; }
};

#endif 