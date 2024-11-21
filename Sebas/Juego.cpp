#include "Juego.h"
#include <iostream>
#include "Hanzo.h"
#include "Samurai.h"
#include "Piso.h"
#include "Luchador.h"
#include "Cuchillo.h"
#include "Animaciones.h"

Juego::Juego() : window(sf::VideoMode(800, 600), "Peleitas"), piso(0.0f, 550.0f), tiempoDelta(0.0f),animationsInitialized(false)
{
    jugador1 = new Hanzo(175.0f, 450.0f, sf::Color (0,0,0,0));
    jugador2 = new Samurai(375.0f, 450.0f, sf::Color::Red);
    inicializarAnimaciones();
    
}

Juego::~Juego()
{
    delete jugador1;
    delete jugador2;
}

void Juego::ejecutar()
{
    while (window.isOpen())
    {
        procesarEventos();
        actualizar();
        renderizar();
    }
}

void Juego::inicializarAnimaciones() {
    if (!animationsInitialized) {
        // Configurar IDLE
        jugador1->configurarAnimacion(
            EstadoAnimacion::IDLE,
            "../assets/anims/hanzo/Idle_Hanzo.png",
            100,    // ancho
            118,    // alto
            10,     // frames
            0.1f    // tiempo
        );

        // Configurar WALK
        jugador1->configurarAnimacion(
            EstadoAnimacion::WALK,
            "../assets/anims/hanzo/caminata_Hanzo.png",
            120,    // ancho diferente
            130,    // alto diferente
            8,      // frames diferentes
            0.08f   // tiempo diferente
        );

        // Configurar ATTACK
        jugador1->configurarAnimacion(
            EstadoAnimacion::ATTACK,
            "../assets/anims/hanzo/ataque_Hanzo.png",
            140,    // ancho diferente
            120,    // alto diferente
            6,      // frames diferentes
            0.05f   // tiempo diferente
        );

        if (jugador1->cargarTodasLasTexturas()) {
            jugador1->setTransparentColor(sf::Color(64, 176, 72), EstadoAnimacion::IDLE);
            jugador1->setTransparentColor(sf::Color(64, 176, 72), EstadoAnimacion::WALK);
            jugador1->setTransparentColor(sf::Color(64, 176, 72), EstadoAnimacion::ATTACK);
            
            jugador1->playAnimation();
            animationsInitialized = true;
            std::cout << "Animaciones inicializadas correctamente" << std::endl;
        } else {
            std::cerr << "Error al cargar las texturas de animación!" << std::endl;
        }
    }
}




void Juego::procesarEventos()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::R && jugador1->hitbox.getGlobalBounds().intersects(jugador2->rectan.getGlobalBounds()))
            {
               
                if(sf::Event::KeyPressed){
                    if (event.key.code == sf::Keyboard::R)
                    {
                            jugador1->cambiarEstado(EstadoAnimacion::ATTACK);
                            if (event.type == sf::Event::KeyReleased)
                                jugador1->cambiarEstado(EstadoAnimacion::IDLE);
                    }
                    
                }
                
                jugador2->recibirAtaque(20.0f);
                if (jugador2->lives == 0)

                {
                    std::cout << "Jugador 1 gana!" << std::endl;
                    window.close();
                }
                

            }
            
            if (event.key.code == sf::Keyboard::P && jugador2->hitbox.getGlobalBounds().intersects(jugador1->rectan.getGlobalBounds()))
            {

                jugador1->recibirAtaque(20.0f);
                if (jugador1->lives == 0)
                {
                    std::cout << "Jugador 2 gana!" << std::endl;
                    window.close();
                }
            }
            if (event.key.code == sf::Keyboard::Q)
            {
                jugador1->lanzarCuchillo();
            }
            if (event.key.code == sf::Keyboard::O)
            {
                jugador2->lanzarCuchillo();
            } 
            
        }
    }
}



void Juego::actualizar()
{
    tiempoDelta = reloj.restart().asSeconds();
    jugador1->move(tiempoDelta, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, piso.rectan.getPosition().y);
    jugador2->move(tiempoDelta, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, piso.rectan.getPosition().y);

    jugador1->updateAnimation(tiempoDelta);

    jugador1->actualizarCuchillos(tiempoDelta);
    jugador2->actualizarCuchillos(tiempoDelta);

    // std::cout << "DeltaTime: " << tiempoDelta << std::endl;
    //std::cout<<jugador1->rectan.getPosition().x<<" "<<jugador1->rectan.getPosition().y<<std::endl;

    jugador1->setPosition(jugador1->rectan.getPosition().x,jugador1->rectan.getPosition().y);
    
    
    
}

void Juego::renderizar()
{
    window.clear(sf::Color::Blue);
    window.draw(piso.rectan);
    window.draw(jugador1->rectan);
    window.draw(jugador2->rectan);

    window.draw(jugador1->hitbox);
    window.draw(jugador2->hitbox);
    
    

    
    jugador1->draw(window);
    

    jugador1->drawHealthBar(window, sf::Vector2f(25.0f, 50.0f));
    jugador2->drawHealthBar(window, sf::Vector2f(575.0f, 50.0f));

    for (auto &cuchillo : jugador1->shurikens)
    {
        window.draw(cuchillo.forma);
    }
    for (auto &cuchillo : jugador2->shurikens)
    {
        window.draw(cuchillo.forma);
    }

    window.display();
}