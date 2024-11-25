#include "Samurai.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Piso.h"

Samurai::Samurai(float x, float y, sf::Color color) : Luchador(x, y, color), remainingJumps(25), animacionActual("idle"), indiceSprite(0), tiempoEntreSprites(0.13f) {}

void Samurai::cargarAnimaciones() {
    std::string rutaBase = "../assets/anims/samurai/";
    animaciones["idle"] = Animacion::cargarSprites(rutaBase + "idle_samurai.png", 10, 107.6, 140, sf::Color(192, 192, 192), false);
    animaciones["run"] = Animacion::cargarSprites(rutaBase + "caminar_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), false);
    animaciones["run_b"] = Animacion::cargarSprites(rutaBase + "caminata_atras_samurai.png", 8, 110, 140, sf::Color(192, 192, 192), false);
    animaciones["jump"] = Animacion::cargarSprites(rutaBase + "salto_samurai.png", 5, 108.2, 140, sf::Color(192, 192, 192), false);
    animaciones["attack"] = Animacion::cargarSprites(rutaBase + "ataque_samurai.png", 5, 140, 140, sf::Color(192, 192, 192), false);
    animaciones["attack_s"] = Animacion::cargarSprites(rutaBase + "ataque_especial_samurai.png", 12, 160, 140, sf::Color(192, 192, 192), false);
    animaciones["defense"] = Animacion::cargarSprites(rutaBase + "bloqueo_samurai.png", 1, 90, 140, sf::Color(192, 192, 192), false);
    animaciones["hit"] = Animacion::cargarSprites(rutaBase + "dañado_samurai.png", 5, 121.6, 140, sf::Color(192, 192, 192), false);
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
    animacionesEspejadas["hit"] = Animacion::cargarSprites(rutaBase + "dañado_samurai.png", 5, 121.6, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["shoot"] = Animacion::cargarSprites(rutaBase + "proyectil_samurai.png", 7, 195, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["intro_vict"] = Animacion::cargarSprites(rutaBase + "victoria_samurai.png", 3, 90, 140, sf::Color(192, 192, 192), true);
    animacionesEspejadas["death"] = Animacion::cargarSprites(rutaBase + "muerte_samurai.png", 9, 155, 120, sf::Color(192, 192, 192), true);
}

void Samurai::cambiarAnimacion(const std::string& nuevaAnimacion, float direccion) {
    if(direccion > 0){
        if (animaciones.find(nuevaAnimacion) != animaciones.end()) {
            animacionActual = nuevaAnimacion;
        }
    }else{
         if (animacionesEspejadas.find(nuevaAnimacion) != animacionesEspejadas.end()) {
            animacionActual = nuevaAnimacion;
        }
    indiceSprite = 0; // Reiniciar el índice del sprite
    relojSprite.restart(); // Reiniciar el temporizador
    }
}

void Samurai::actualizarAnimacion(float direccion) {
    if (relojSprite.getElapsedTime().asSeconds() >= tiempoEntreSprites) {
        if(direccion > 0) {
            indiceSprite = (indiceSprite + 1) % animaciones[animacionActual].size(); // Ciclo entre los sprites
        }else{
            indiceSprite = (indiceSprite + 1) % animacionesEspejadas[animacionActual].size(); // Ciclo entre los sprites
        }
        relojSprite.restart();
    }
}

void Samurai::dibujar(sf::RenderWindow& window, float direccion) {
    actualizarAnimacion(direccion);
    if(direccion > 0){
        sf::Sprite& spriteActual = animaciones[animacionActual][indiceSprite];
        spriteActual.setPosition(rectan.getPosition());
        window.draw(spriteActual);
    }else{
        sf::Sprite& spriteActual = animacionesEspejadas[animacionActual][indiceSprite];
        spriteActual.setPosition(rectan.getPosition());
        window.draw(spriteActual);
    }
}

void Samurai::move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up, Piso& piso, sf::Keyboard::Key defensa, sf::Keyboard::Key ataque, sf::Keyboard::Key ataque_s, sf::Keyboard::Key ataque_p, Luchador& otroJugador, float direccion)
{
    if (sf::Keyboard::isKeyPressed(izquierda))
    {
        rectan.move(-velocidad * tiempoDelta, 0.0f);
    }
    if (sf::Keyboard::isKeyPressed(derecha))
    {
        rectan.move(velocidad * tiempoDelta, 0.0f);
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
    if (sf::Keyboard::isKeyPressed(defensa)) {
        isDefending = true;
        velocidad = velocidadReducida;
    } else {
        isDefending = false;
        velocidad = velocidadNormal;
    }
    rectan.move(0.0f, velocityY * tiempoDelta);
    hitbox.setPosition(rectan.getPosition()); // Actualizar la posición de la hitbox

    // Aplicar retroceso
    rectan.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);
    hitbox.move(retroceso_x * tiempoDelta, retroceso_y * tiempoDelta);

    // Reducir gradualmente el retroceso
    retroceso_x *= 0.9f;
    retroceso_y *= 0.9f;

    // Comprobar colisión con el piso
    if (piso.colisionaCon(rectan)) {
        // Ajustar la posición del luchador para que quede sobre el piso
        rectan.setPosition(rectan.getPosition().x, piso.getPosY() - rectan.getSize().y);
        velocityY = 0.0f;  // Detener la gravedad
        isJumping = false; // Ya no está saltando
        reapareciendo = false;
        remainingJumps = 25;
        retroceso_y = 0.0f; // Resetear retroceso en Y
    }
    else {
        // Si no colisiona con el piso, la gravedad sigue actuando
        isJumping = true;
    }

    if (rectan.getPosition().y > 1080) 
    {
        reducirVidas({900.0f, -rectan.getSize().y});
    }


}

void Samurai::usarUltimate(Luchador& oponente) {
    health += maxhealth * 0.55f;
    if (health > maxhealth) {
        health = maxhealth;  // No exceder la salud máxima
    }
    energia = 0.0f;
}