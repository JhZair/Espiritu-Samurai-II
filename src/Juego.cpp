#include "Juego.h"
#include <iostream>

Juego::Juego() : window(sf::VideoMode(800, 600), "Peleitas"), piso(0.0f, 550.0f), tiempoDelta(0.0f)
{
    jugador1 = new Hanzo(175.0f, 450.0f, sf::Color::Yellow);
    jugador2 = new Samurai(375.0f, 450.0f, sf::Color::Red);
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

    jugador1->actualizarCuchillos(tiempoDelta);
    jugador2->actualizarCuchillos(tiempoDelta);
}

void Juego::renderizar()
{
    window.clear(sf::Color::Blue);
    window.draw(piso.rectan);
    window.draw(jugador1->rectan);
    window.draw(jugador2->rectan);

    window.draw(jugador1->hitbox);
    window.draw(jugador2->hitbox);

    jugador1->drawHealthBar(window, sf::Vector2f(25.0f, 50.0f));
    jugador2->drawHealthBar(window, sf::Vector2f(575.0f, 50.0f));

    for (auto &cuchillo : jugador1->cuchillos)
    {
        window.draw(cuchillo.forma);
    }
    for (auto &cuchillo : jugador2->cuchillos)
    {
        window.draw(cuchillo.forma);
    }

    window.display();
}