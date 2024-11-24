#ifndef LUCHADOR_H
#define LUCHADOR_H

#include <SFML/Graphics.hpp>
#include "Shuriken.h"
#include "Animaciones.h"
#include <vector>

class Luchador : public Animacion
{
protected:
    sf::RectangleShape rectan;
    sf::RectangleShape hitbox;
    float velocidad;
    float gravity;
    float velocityY;
    float jumpStrength;
    bool isJumping;
    float maxhealth;
    float health;
    int lives;
    float energia;
    bool isDefending;
    float velocidadNormal;
    float velocidadReducida;
    bool reapareciendo;
    float retroceso_x;
    float retroceso_y;
    
    sf::Clock clock;
    std::vector<Shuriken> shurikens;
public:
    Luchador(float x, float y, sf::Color color);
    virtual ~Luchador() = default;
    virtual void lanzarShurikens();
    virtual void move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY, sf::Keyboard::Key defensa, sf::Keyboard::Key ataque, sf::Keyboard::Key ataque_s, sf::Keyboard::Key ataque_p, Luchador& otroJugador, float direccion);
    virtual void usarUltimate(Luchador& oponente);
    void recibirAtaque(float damage, sf::Vector2f retroceso);
    void reducirVidas(sf::Vector2f posicionInicial);
    void actualizarShurikens(float tiempoDelta, float direccion, Luchador& oponente);
    void aumentarEnergia(float cantidad);
    void drawHealthBar(sf::RenderWindow& window, sf::Vector2f position);
    void drawEnergiaBar(sf::RenderWindow& window, sf::Vector2f position);

    virtual void cargarAnimaciones()= 0;
    virtual void cambiarAnimacion(const std::string& nuevaAnimacion, float direccion)= 0;
    virtual void actualizarAnimacion(float direccion)= 0;
    virtual void dibujar(sf::RenderWindow& window, float direccion)= 0;

    // Getters y Setters
    const sf::RectangleShape& getRectan() const { return rectan; }
    void setRectan(const sf::RectangleShape& rect) { rectan = rect; }

    const sf::RectangleShape& getHitbox() const { return hitbox; }
    void setHitbox(const sf::RectangleShape& box) { hitbox = box; }

    float getVelocidad() const { return velocidad; }
    void setVelocidad(float vel) { velocidad = vel; }

    float getGravity() const { return gravity; }
    void setGravity(float grav) { gravity = grav; }

    float getVelocityY() const { return velocityY; }
    void setVelocityY(float velY) { velocityY = velY; }

    float getJumpStrength() const { return jumpStrength; }
    void setJumpStrength(float strength) { jumpStrength = strength; }

    bool getIsJumping() const { return isJumping; }
    void setIsJumping(bool jumping) { isJumping = jumping; }

    float getMaxHealth() const { return maxhealth; }
    void setMaxHealth(float maxHP) { maxhealth = maxHP; }

    float getHealth() const { return health; }
    void setHealth(float hp) { health = hp; }

    int getLives() const { return lives; }
    void setLives(int vida) { lives = vida; }

    float getEnergia() const { return energia; }
    void setEnergia(float energy) { energia = energy; }

    bool getIsDefending() const { return isDefending; }
    void setIsDefending(bool defending) { isDefending = defending; }

    float getVelocidadNormal() const { return velocidadNormal; }
    void setVelocidadNormal(float normalSpeed) { velocidadNormal = normalSpeed; }

    float getVelocidadReducida() const { return velocidadReducida; }
    void setVelocidadReducida(float reducedSpeed) { velocidadReducida = reducedSpeed; }

    bool getReapareciendo() const { return reapareciendo; }
    void setReapareciendo(bool respawning) { reapareciendo = respawning; }

    float getRetrocesoX() const { return retroceso_x; }
    void setRetrocesoX(float retroceso) { retroceso_x = retroceso; }

    float getRetrocesoY() const { return retroceso_y; }
    void setRetrocesoY(float retroceso) { retroceso_y = retroceso; }

    const sf::Clock& getClock() const { return clock; }
    void setClock(const sf::Clock& reloj) { clock = reloj; }

    const std::vector<Shuriken>& getShurikens() const { return shurikens; }
    void setShurikens(const std::vector<Shuriken>& shurikenList) { shurikens = shurikenList; }
};

#endif