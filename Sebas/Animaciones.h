#include <SFML/Graphics.hpp>
#ifndef ANIMACIONES_H
#define ANIMACIONES_H

class Animacion: public sf::Sprite
{
protected:    
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
public:        
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
    void setSingleColorFilter(sf::Color color);




    // Getters y setters
    const sf::Texture& getSpriteSheet() const { return spriteSheet; }
    void setSpriteSheet(const sf::Texture& texture) { spriteSheet = texture; }

    const sf::IntRect& getFrameRect() const { return frameRect; }
    void setFrameRect(const sf::IntRect& rect) { frameRect = rect; }

    int getCurrentFrame() const { return currentFrame; }
    void setCurrentFrame(int frame) { currentFrame = frame; }

    int getFrameCount() const { return frameCount; }
    void setFrameCount(int count) { frameCount = count; }

    float getFrameTime() const { return frameTime; }
    void setFrameTime(float time) { frameTime = time; }

    float getCurrentTime() const { return currentTime; }
    void setCurrentTime(float time) { currentTime = time; }

    bool isLooping() const { return loop; }
    void setLoop(bool shouldLoop) { loop = shouldLoop; }

    int getFrameWidth() const { return frameWidth; }
    void setFrameWidth(int width) { frameWidth = width; }

    int getFrameHeight() const { return frameHeight; }
    void setFrameHeight(int height) { frameHeight = height; }

    bool getIsPlaying() const { return isPlaying; }
    void setIsPlaying(bool playing) { isPlaying = playing; }
};

#endif