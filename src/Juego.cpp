#include <iostream>
#include <SFML/Graphics.hpp>
#include "Juego.h"

Juego::Juego()
    : window(sf::VideoMode(1920, 1080), "Espíritu Samurai II"), 
      piso(window.getPosition().x/8, 850.0f, 1400.0f, 650.0f), 
      tiempoDelta(0.0f), 
      tiempoPartida(90.0f), 
      inicioTiempo(reloj.getElapsedTime().asSeconds())
{
    reiniciarJugadores();
}

Juego::~Juego()
{
    delete jugador1;
    delete jugador2;
}

void Juego::reiniciarJugadores()
{
    jugador1 = new Hanzo(window.getPosition().x/2-200, 450.0f, sf::Color::Yellow);
    jugador1->cargarAnimaciones();
    jugador2 = new Samurai(window.getPosition().x/2+200, 450.0f, sf::Color::Red);
    jugador2->cargarAnimaciones();
}

void Juego::manejarAtaques(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::R && jugador1->getHitbox().getGlobalBounds().intersects(jugador2->getRectan().getGlobalBounds()) && !jugador1->getIsDefending())
    {
        jugador2->recibirAtaque(15.0f, sf::Vector2f(direccion1 * 160.0f, -150.0f));
        jugador1->aumentarEnergia(8.0f);
        verificarDerrota(jugador2, "Jugador 1");
    }
    if (event.key.code == sf::Keyboard::P && jugador2->getHitbox().getGlobalBounds().intersects(jugador1->getRectan().getGlobalBounds()) && !jugador2->getIsDefending())
    {
        jugador1->recibirAtaque(15.0f, sf::Vector2f(direccion2 * 175.0f, -150.0f));
        jugador2->aumentarEnergia(10.0f);
        verificarDerrota(jugador1, "Jugador 2");
    }
    if (event.key.code == sf::Keyboard::T  && jugador1->getEnergia()==100 && !jugador1->getIsDefending())
    {
        jugador1->usarUltimate(*jugador2);
        jugador2->recibirAtaque(50.0f, sf::Vector2f(direccion1 * 250.0f, -200.0f));
        verificarDerrota(jugador2, "Jugador 1");
    }
    if (event.key.code == sf::Keyboard::I && jugador2->getEnergia()==100)
    {
        jugador2->usarUltimate(*jugador1);
    }
}

void Juego::manejarProyectiles(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Q && !jugador1->getIsDefending())
    {
        jugador1->lanzarShurikens();
        verificarDerrota(jugador2, "Jugador 1");
    }
    if (event.key.code == sf::Keyboard::O && !jugador2->getIsDefending())
    {
        jugador2->lanzarShurikens();
        verificarDerrota(jugador1, "Jugador 2");
    }
}

void Juego::verificarDerrota(Luchador *jugador, const std::string &ganador)
{
    if (jugador->getLives() == 0)
    {
        std::cout << ganador << " gana!" << std::endl;
        window.close();
    }
}

void Juego::dibujarTiempoRestante()
{
    float tiempoRestante = calcularTiempoRestante();
    int minutos = static_cast<int>(tiempoRestante) / 60;
    int segundos = static_cast<int>(tiempoRestante) % 60;

    sf::Font fuente;
    if (!fuente.loadFromFile("../assets/fonts/upheavtt.ttf")) // Ajusta la ruta si es necesario
    {
        std::cerr << "Error cargando la fuente." << std::endl;
        return;
    }

    sf::Text textoTiempo;
    textoTiempo.setFont(fuente);
    textoTiempo.setCharacterSize(50);
    textoTiempo.setFillColor(sf::Color::White);
    textoTiempo.setString(
        (minutos < 10 ? "0" : "") + std::to_string(minutos) + ":" +
        (segundos < 10 ? "0" : "") + std::to_string(segundos));
    textoTiempo.setPosition(window.getSize().x / 2.0f - textoTiempo.getGlobalBounds().width / 2.0f, 25.0f);

    window.draw(textoTiempo);
}

float Juego::calcularTiempoRestante() 
{
    return tiempoPartida - (reloj.getElapsedTime().asSeconds() - inicioTiempo);
}

void Juego::determinarGanador()
{
    if (jugador1->getHealth() > jugador2->getHealth())
    {
        std::cout << "Jugador 1 gana por salud!" << std::endl;
    }
    else if (jugador2->getHealth() > jugador1->getHealth())
    {
        std::cout << "Jugador 2 gana por salud!" << std::endl;
    }
    else
    {
        std::cout << "¡Empate!" << std::endl;
    }
    window.close();
}

void Juego::ejecutar()
{
    while (window.isOpen())
    {
        procesarEventos();
        actualizar();
        renderizar();

        if (calcularTiempoRestante() <= 0)
        {
            determinarGanador(); // Anuncia el ganador y cierra la ventana.
            break;
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
            direccion1 = (jugador1->getRectan().getPosition().x < jugador2->getRectan().getPosition().x) ? 1.0f : -1.0f;
            direccion2 = (jugador2->getRectan().getPosition().x < jugador1->getRectan().getPosition().x) ? 1.0f : -1.0f;
            manejarAtaques(event);
            manejarProyectiles(event);
        }
    }
}

void Juego::actualizar()
{
    tiempoDelta = relojMov.restart().asSeconds();
    // Actualizar movimiento de jugadores
    jugador1->move(
    tiempoDelta, 
    sf::Keyboard::A, // Tecla para moverse a la izquierda
    sf::Keyboard::D, // Tecla para moverse a la derecha
    sf::Keyboard::W, // Tecla para saltar
    piso, // Posición del piso
    sf::Keyboard::S, // Tecla para defensa
    sf::Keyboard::R, // Tecla para ataque básico
    sf::Keyboard::T, // Tecla para ataque especial
    sf::Keyboard::Q, // Tecla para ataque de proyectiles
    direccion1
);
    jugador2->move(
    tiempoDelta, 
    sf::Keyboard::Left,   // Tecla para moverse a la izquierda
    sf::Keyboard::Right,  // Tecla para moverse a la derecha
    sf::Keyboard::Up,     // Tecla para saltar
    piso, // Posición del piso
    sf::Keyboard::Down,   // Tecla para defensa
    sf::Keyboard::P,   // Tecla para ataque básico
    sf::Keyboard::I,   // Tecla para ataque especial
    sf::Keyboard::O,   // Tecla para ataque de proyectiles
    direccion2
);

    static_cast<Hanzo*>(jugador1)->actualizarUltimates(tiempoDelta, direccion1); // Actualiza las ultimates de Hanzo


    // Actualizar proyectiles
    jugador1->actualizarShurikens(tiempoDelta, direccion1, *jugador2);
    jugador2->actualizarShurikens(tiempoDelta, direccion2, *jugador1);
}

void Juego::renderizar()
{
    window.clear(sf::Color::Blue);

    // Dibujar el escenario
    window.draw(piso.getRectan());

    // Dibujar jugadores
    // window.draw(jugador1->getRectan());
    // window.draw(jugador2->getRectan());

    jugador1->dibujar(window, direccion1);
    jugador2->dibujar(window, direccion2);

    // Dibujar hitboxes (opcional, para depuración)
    // window.draw(jugador1->getHitbox());
    // window.draw(jugador2->getHitbox());

    // Dibujar barras de salud
    jugador1->drawHealthBar(window, sf::Vector2f(25.0f, 50.0f));
    jugador2->drawHealthBar(window, sf::Vector2f(window.getSize().x - 625.0f, 50.0f));

    jugador1->drawEnergiaBar(window, sf::Vector2f(25.0f, 95.0f));
    jugador2->drawEnergiaBar(window, sf::Vector2f(window.getSize().x - 625.0f, 95.0f));

    // Dibujar proyectiles
    for (auto &shuriken : jugador1->getShurikens())
    {
        window.draw(shuriken.getForma());
    }
    for (auto &shuriken : jugador2->getShurikens())
    {
        window.draw(shuriken.getForma());
    }
    for (const auto& ultimate : static_cast<Hanzo*>(jugador1)->getUltimates()) 
    {
        window.draw(ultimate);
    }

    dibujarTiempoRestante();

    window.display();
}