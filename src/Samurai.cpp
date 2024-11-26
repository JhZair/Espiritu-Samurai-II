#include "Samurai.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Samurai::Samurai(float x, float y, sf::Color color) : Luchador(x, y, color), remainingJumps(25) {}

void Samurai::cargarAnimaciones() {
    std::string rutaBase = "../assets/anims/samurai/";
    animaciones["idle"] = cargarSprites(rutaBase + "idle_samurai.png", 10, 107.6, 140, sf::Color(192, 192, 192), sf::Color::Black, false);
    animaciones["run"] = cargarSprites(rutaBase + "caminar_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), sf::Color::Black, false);
    animaciones["run_b"] = cargarSprites(rutaBase + "caminata_atras_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), sf::Color::Black, false);
    animaciones["jump"] = cargarSprites(rutaBase + "salto_samurai.png", 5, 108.2, 140, sf::Color(192, 192, 192), sf::Color::Black, false);
    animaciones["attack"] = cargarSprites(rutaBase + "ataque_samurai.png", 5, 140, 140, sf::Color(192, 192, 192), sf::Color::Black, false);
    animaciones["attack_s"] = cargarSprites(rutaBase + "ataque_especial_samurai.png", 12, 160, 140, sf::Color(192, 192, 192), sf::Color::Black, false);
    animaciones["defense"] = cargarSprites(rutaBase + "bloqueo_samurai.png", 1, 90, 140, sf::Color(192, 192, 192), sf::Color::Black, false);
    animaciones["shoot"] = cargarSprites(rutaBase + "proyectil_samurai.png", 7, 195, 140, sf::Color(192, 192, 192), sf::Color::Black, false);
    animaciones["intro_vict"] = cargarSprites(rutaBase + "victoria_samurai.png", 3, 90, 140, sf::Color(192, 192, 192), sf::Color::Black, false);
    animaciones["death"] = cargarSprites(rutaBase + "muerte_samurai.png", 9, 155, 120, sf::Color(192, 192, 192), sf::Color::Black, false);

    animacionesEspejadas["idle"] = cargarSprites(rutaBase + "idle_samurai.png", 10, 107.6, 140, sf::Color(192, 192, 192), sf::Color::Black, true);
    animacionesEspejadas["run"] = cargarSprites(rutaBase + "caminar_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), sf::Color::Black, true);
    animacionesEspejadas["run_b"] = cargarSprites(rutaBase + "caminata_atras_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), sf::Color::Black, true);
    animacionesEspejadas["jump"] = cargarSprites(rutaBase + "salto_samurai.png", 5, 108.2, 140, sf::Color(192, 192, 192), sf::Color::Black, true);
    animacionesEspejadas["attack"] = cargarSprites(rutaBase + "ataque_samurai.png", 5, 140, 140, sf::Color(192, 192, 192), sf::Color::Black, true);
    animacionesEspejadas["attack_s"] = cargarSprites(rutaBase + "ataque_especial_samurai.png", 12, 160, 140, sf::Color(192, 192, 192), sf::Color::Black, true);
    animacionesEspejadas["defense"] = cargarSprites(rutaBase + "bloqueo_samurai.png", 1, 90, 140, sf::Color(192, 192, 192), sf::Color::Black, true);
    animacionesEspejadas["shoot"] = cargarSprites(rutaBase + "disparo_samurai.png", 7, 195, 140, sf::Color(192, 192, 192), sf::Color::Black, true);
    animacionesEspejadas["intro_vict"] = cargarSprites(rutaBase + "victoria_samurai.png", 3, 90, 140, sf::Color(192, 192, 192), sf::Color::Black, true);
    animacionesEspejadas["death"] = cargarSprites(rutaBase + "muerte_samurai.png", 9, 155, 120, sf::Color(192, 192, 192), sf::Color::Black, true);
}

void Samurai::usarUltimate(Luchador& oponente) {
    health += maxhealth * 0.55f;
    if (health > maxhealth) {
        health = maxhealth;
    }
    energia = 0.0f;
}

void Samurai::move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up,  Piso& piso, sf::Keyboard::Key defensa, sf::Keyboard::Key ataque, sf::Keyboard::Key ataque_s, sf::Keyboard::Key ataque_p, float direccion)
{   
    if (!isDefending && !isJumping) {
        cambiarAnimacion("idle" , direccion);
    }
    if (sf::Keyboard::isKeyPressed(izquierda))
    {
        rectan.move(-velocidad * tiempoDelta, 0.0f);
        if(!isJumping)
            cambiarAnimacion("run_b", direccion);
    }
    if (sf::Keyboard::isKeyPressed(derecha))
    {
        rectan.move(velocidad * tiempoDelta, 0.0f);
        if(!isJumping)
            cambiarAnimacion("run", direccion);
    }
    if (isJumping)
    {
        velocityY += gravity * tiempoDelta;
    }
    if (sf::Keyboard::isKeyPressed(up) && remainingJumps > 0)
    {
        isJumping = true;
        velocityY = jumpStrength;
        remainingJumps--;
    }
    if (isJumping && animacionActual != "attack" && animacionActual != "attack_s" && animacionActual != "shoot") {
        cambiarAnimacion("jump", direccion);
    }
    if (sf::Keyboard::isKeyPressed(ataque)) {
        cambiarAnimacion("attack", direccion);
    }
    // Animación de ataque especial
    if (sf::Keyboard::isKeyPressed(ataque_s) && energia == 100.0f) {
        cambiarAnimacion("intro_vict", direccion);
    }
    if (sf::Keyboard::isKeyPressed(ataque_p)) {
        cambiarAnimacion("attack", direccion);
    }
    if (sf::Keyboard::isKeyPressed(defensa)) {
        isDefending = true;
        velocidad = velocidadReducida;
        cambiarAnimacion("defense", direccion);
    } else {
        isDefending = false;
        velocidad = velocidadNormal;
    }
    if (reapareciendo){
        cambiarAnimacion("death", direccion);
    }

    rectan.move(0.0f, velocityY * tiempoDelta);
    hitbox.setPosition(rectan.getPosition());

    rectan.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);
    hitbox.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);

    retroceso_x *= 0.9f;
    retroceso_y *= 0.9f;

    if (piso.colisionaCon(rectan)) {
        // Ajustar la posición del luchador para que quede sobre el piso
        rectan.setPosition(rectan.getPosition().x, piso.getPosY() - rectan.getSize().y);
        velocityY = 0.0f;  // Detener la gravedad
        isJumping = false; // Ya no está saltando
        reapareciendo = false;
        remainingJumps = 25;
        retroceso_y = 0.0f; // Resetear retroceso en Y
    }
    if(!piso.colisionaCon(rectan) && (rectan.getPosition().x  < 240 - rectan.getSize().x - 20|| rectan.getPosition().x > 1640)) {
        isJumping = true;
    }

    if (rectan.getPosition().y > 1080) 
    {
        reducirVidas({960.0f, -rectan.getSize().y});
    }
}