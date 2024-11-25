#include "Samurai.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Samurai::Samurai(float x, float y, sf::Color color) : Luchador(x, y, color), remainingJumps(25) {}

void Samurai::cargarAnimaciones() {
    std::string rutaBase = "../assets/anims/samurai/";
    animaciones["idle"] = Animacion::cargarSprites(rutaBase + "idle_samurai.png", 10, 107.6, 140, sf::Color(192, 192, 192), false);
    animaciones["run"] = Animacion::cargarSprites(rutaBase + "caminar_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), false);
    animaciones["run_b"] = Animacion::cargarSprites(rutaBase + "caminata_atras_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), false);
    animaciones["jump"] = Animacion::cargarSprites(rutaBase + "salto_samurai.png", 5, 108.2, 140, sf::Color(192, 192, 192), false);
    animaciones["attack"] = Animacion::cargarSprites(rutaBase + "ataque_samurai.png", 5, 140, 140, sf::Color(192, 192, 192), false);
    animaciones["attack_s"] = Animacion::cargarSprites(rutaBase + "ataque_especial_samurai.png", 12, 160, 140, sf::Color(192, 192, 192), false);
    animaciones["defense"] = Animacion::cargarSprites(rutaBase + "bloqueo_samurai.png", 1, 90, 140, sf::Color(192, 192, 192), false);
    animaciones["shoot"] = Animacion::cargarSprites(rutaBase + "proyectil_samurai.png", 7, 195, 140, sf::Color(192, 192, 192), false);
    animaciones["intro_vict"] = Animacion::cargarSprites(rutaBase + "victoria_samurai.png", 3, 90, 140, sf::Color(192, 192, 192), false);
    animaciones["death"] = Animacion::cargarSprites(rutaBase + "muerte_samurai.png", 9, 155, 120, sf::Color(192, 192, 192), false);

    animacionesEspejadas["idle"] = Animacion::cargarSprites(rutaBase + "idle_samurai.png", 10, 107.6, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["run"] = Animacion::cargarSprites(rutaBase + "caminar_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["run_b"] = Animacion::cargarSprites(rutaBase + "caminata_atras_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["jump"] = Animacion::cargarSprites(rutaBase + "salto_samurai.png", 5, 108.2, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["attack"] = Animacion::cargarSprites(rutaBase + "ataque_samurai.png", 5, 140, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["attack_s"] = Animacion::cargarSprites(rutaBase + "ataque_especial_samurai.png", 12, 160, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["defense"] = Animacion::cargarSprites(rutaBase + "bloqueo_samurai.png", 1, 90, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["shoot"] = Animacion::cargarSprites(rutaBase + "disparo_samurai.png", 7, 195, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["intro_vict"] = Animacion::cargarSprites(rutaBase + "victoria_samurai.png", 3, 90, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["death"] = Animacion::cargarSprites(rutaBase + "muerte_samurai.png", 9, 155, 120, sf::Color(192, 192, 192), true);
}

void Samurai::usarUltimate(Luchador& oponente) {
    health += maxhealth * 0.55f;
    if (health > maxhealth) {
        health = maxhealth;  // No exceder la salud máxima
    }
    energia = 0.0f;
}

void Samurai::move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, float pisoY, sf::Keyboard::Key defensa, sf::Keyboard::Key ataque, sf::Keyboard::Key ataque_s, sf::Keyboard::Key ataque_p, float direccion)
{
    if (!isDefending && !isJumping) {
        cambiarAnimacion("idle" , direccion);
    }
    if (sf::Keyboard::isKeyPressed(izquierda))
    {
        rectan.move(-velocidad * tiempoDelta, 0.0f);
        cambiarAnimacion("run_b", direccion);
    }
    if (sf::Keyboard::isKeyPressed(derecha))
    {
        rectan.move(velocidad * tiempoDelta, 0.0f);
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
        cooldown_animacion = tiempoDelta + 300;
    }
    // Animación de ataque especial
    if (sf::Keyboard::isKeyPressed(ataque_s) && energia == 100.0f && tiempoDelta >= cooldown_animacion) {
        cambiarAnimacion("intro_vict", direccion);
        setCooldownAnim(tiempoDelta + 800);
    }
    if (sf::Keyboard::isKeyPressed(ataque_p) && tiempoDelta >= cooldown_animacion) {
        cambiarAnimacion("shoot", direccion);
        setCooldownAnim(tiempoDelta + 100);
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

    // Aplicar retroceso
    rectan.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);
    hitbox.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);

    // Reducir gradualmente el retroceso
    retroceso_x *= 0.9f;
    retroceso_y *= 0.9f;

    // Comprobar colisión con el piso
    if (rectan.getPosition().y + rectan.getSize().y >= pisoY)
    {
        rectan.setPosition(rectan.getPosition().x, pisoY - rectan.getSize().y);
        velocityY = 0;
        isJumping = false;
        reapareciendo = false;
        remainingJumps = 25;
        retroceso_y = 0.0f;
    }
}