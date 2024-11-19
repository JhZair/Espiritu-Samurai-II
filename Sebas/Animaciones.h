#ifndef ANIMACIONES_H
#define ANIMACIONES_H
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

enum class EstadoAnimacion { IDLE, WALK, ATTACK, BLOCK, JUMP };

class Animacion : public sf::Sprite {
private:
    std::map<EstadoAnimacion, sf::Texture> texturas;
    std::map<EstadoAnimacion, std::string> rutas;
    std::map<EstadoAnimacion, int> anchos;
    std::map<EstadoAnimacion, int> altos;
    std::map<EstadoAnimacion, int> numFrames;
    std::map<EstadoAnimacion, float> tiemposFrame;
    
public:
    sf::IntRect frameRect;
    int currentFrame;
    float currentTime;
    bool loop;
    bool isPlaying;
    EstadoAnimacion estadoActual;

    Animacion();
    ~Animacion();

    // Método para configurar una animación específica
    void configurarAnimacion(
        EstadoAnimacion estado, 
        const std::string& path, 
        int ancho, 
        int alto, 
        int frames, 
        float tiempoFrame
    );

    bool cargarTodasLasTexturas();
    void setTransparentColor(sf::Color color, EstadoAnimacion estado);
    void updateAnimation(float deltaTime);
    void resetAnimation();
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    void pauseAnimation() { isPlaying = false; }
    void playAnimation() { isPlaying = true; }
    void cambiarEstado(EstadoAnimacion nuevoEstado);
};
#endif