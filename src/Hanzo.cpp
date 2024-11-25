#include "Hanzo.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Hanzo::Hanzo(float x, float y, sf::Color color) : Luchador(x, y, color) {}

void Hanzo::lanzarShurikens() {
    if (clock.getElapsedTime().asSeconds() >= 2) {
        Shuriken shuriken1(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + rectan.getSize().y / 3);
        Shuriken shuriken2(rectan.getPosition().x + rectan.getSize().x, rectan.getPosition().y + 2 * rectan.getSize().y / 3);
        shurikens.push_back(shuriken1);
        shurikens.push_back(shuriken2);
        clock.restart();
    }
}

void Hanzo::usarUltimate(Luchador& oponente) {
    sf::CircleShape ultimate(40.0f); // Puedes ajustar el tamaño
    ultimate.setPosition(rectan.getPosition().x + 50, rectan.getPosition().y); // Posición inicial
    ultimate.setFillColor(sf::Color::Yellow); // Color de la Ultimate
    ultimates.push_back(ultimate);
    energia = 0.0f;
}

void Hanzo::actualizarUltimates(float tiempoDelta, float direccion) {
    for (auto& ultimate : ultimates) {
        ultimate.move(direccion * 1400.0f * tiempoDelta, 0); // Mueve la Ultimate
    }
    ultimates.erase(
        std::remove_if(ultimates.begin(), ultimates.end(), [](const sf::CircleShape& ultimate) {
            return ultimate.getPosition().x > 800; // Fuera de la pantalla
        }),
        ultimates.end()
    );
}

void Hanzo::cargarAnimaciones() {
    std::string rutaBase = "../assets/anims/hanzo/";
    animaciones["idle"] = cargarSprites(rutaBase + "Idle_Hanzo.png", 10, 100, 118, sf::Color(64, 176, 72), sf::Color::Black, false);
    animaciones["run"] = cargarSprites(rutaBase + "caminata_Hanzo.png", 10, 110, 120, sf::Color(64, 176, 72), sf::Color::Black, false);
    animaciones["run_b"] = cargarSprites(rutaBase + "caminataparaatras_Hanzo.png", 10, 100, 130, sf::Color(64, 176, 72), sf::Color::Black, false);
    animaciones["jump"] = cargarSprites(rutaBase + "salto_Hanzo.png", 6, 80, 150, sf::Color(64, 176, 72), sf::Color::Black, false);
    animaciones["attack"] = cargarSprites(rutaBase + "ataque_Hanzo.png", 6, 140, 120, sf::Color(64, 176, 72), sf::Color::Black, false); 
    animaciones["attack_s"] = cargarSprites(rutaBase + "ataquespecial_Hanzo.png", 10, 130, 140, sf::Color(64, 176, 72), sf::Color::Black, false);
    animaciones["defense"] = cargarSprites(rutaBase + "bloqueo_Hanzo.png", 1, 110, 120, sf::Color(64, 176, 72), sf::Color::Black, false);
    animaciones["shoot"] = cargarSprites(rutaBase + "ataquep_Hanzo.png", 5, 155, 120, sf::Color(64, 176, 72), sf::Color::Black, false);
    animaciones["intro_vict"] = cargarSprites(rutaBase + "victoria_Hanzo.png", 6, 86, 120, sf::Color(64, 176, 72), sf::Color::Black, false);
    animaciones["death"] = cargarSprites(rutaBase + "muerte_Hanzo.png", 9, 130, 110, sf::Color(64, 176, 72), sf::Color::Black, false);

    animacionesEspejadas["idle"] = cargarSprites(rutaBase + "Idle_Hanzo.png", 10, 100, 118, sf::Color(64, 176, 72), sf::Color::Black, true);
    animacionesEspejadas["run"] = cargarSprites(rutaBase + "caminata_Hanzo.png", 10, 110, 120, sf::Color(64, 176, 72), sf::Color::Black, true);
    animacionesEspejadas["run_b"] = cargarSprites(rutaBase + "caminataparaatras_Hanzo.png", 10, 100, 130, sf::Color(64, 176, 72), sf::Color::Black, true);
    animacionesEspejadas["jump"] = cargarSprites(rutaBase + "salto_Hanzo.png", 6, 80, 150, sf::Color(64, 176, 72), sf::Color::Black, true);
    animacionesEspejadas["attack"] = cargarSprites(rutaBase + "ataque_Hanzo.png", 6, 140, 120, sf::Color(64, 176, 72), sf::Color::Black, true);
    animacionesEspejadas["attack_s"] = cargarSprites(rutaBase + "ataquespecial_Hanzo.png", 10, 130, 140, sf::Color(64, 176, 72), sf::Color::Black, true);
    animacionesEspejadas["defense"] = cargarSprites(rutaBase + "bloqueo_Hanzo.png", 1, 110, 120, sf::Color(64, 176, 72), sf::Color::Black, true);
    animacionesEspejadas["shoot"] = cargarSprites(rutaBase + "ataquep_Hanzo.png", 5, 155, 120, sf::Color(64, 176, 72), sf::Color::Black, true);
    animacionesEspejadas["intro_vict"] = cargarSprites(rutaBase + "victoria_Hanzo.png", 6, 86, 120, sf::Color(64, 176, 72), sf::Color::Black, true);
    animacionesEspejadas["death"] = cargarSprites(rutaBase + "muerte_Hanzo.png", 9, 130, 110, sf::Color(64, 176, 72), sf::Color::Black, true);
}

void Hanzo::move(float tiempoDelta, sf::Keyboard::Key izquierda, sf::Keyboard::Key derecha, sf::Keyboard::Key up,  Piso& piso, sf::Keyboard::Key defensa, sf::Keyboard::Key ataque, sf::Keyboard::Key ataque_s, sf::Keyboard::Key ataque_p, float direccion)
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
    if (sf::Keyboard::isKeyPressed(up) && !isJumping)
    {
        velocityY = jumpStrength;
        isJumping = true;
    }
    if (isJumping && animacionActual != "attack" && animacionActual != "attack_s" && animacionActual != "shoot") {
        cambiarAnimacion("jump", direccion);
    }
    if (sf::Keyboard::isKeyPressed(ataque)) {
        cambiarAnimacion("attack", direccion);
    }
    // Animación de ataque especial
    if (sf::Keyboard::isKeyPressed(ataque_s) && energia == 100.0f) {
        cambiarAnimacion("attack_s", direccion);
    }
    if (sf::Keyboard::isKeyPressed(ataque_p)) {
        cambiarAnimacion("shoot", direccion);
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

    if (piso.colisionaCon(rectan)) {
        // Ajustar la posición del luchador para que quede sobre el piso
        rectan.setPosition(rectan.getPosition().x, piso.getPosY() - rectan.getSize().y);
        velocityY = 0.0f;  // Detener la gravedad
        isJumping = false; // Ya no está saltando
        reapareciendo = false;
        retroceso_y = 0.0f; // Resetear retroceso en Y
    }
    else {
        // Si no colisiona con el piso, la gravedad sigue actuando
        isJumping = true;
    }

    if (rectan.getPosition().y > 1080) 
    {
        reducirVidas({750.0f, -rectan.getSize().y-1});
    }
}