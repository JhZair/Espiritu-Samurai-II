#include <iostream>
#include <SFML/Graphics.hpp>
#include "Juego.h"

Juego::Juego()
    : window(sf::VideoMode(800, 600), "Peleitas"), 
      piso(0.0f, 550.0f), 
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
    jugador1 = new Hanzo(175.0f, 450.0f, sf::Color::Yellow);
    jugador2 = new Samurai(375.0f, 450.0f, sf::Color::Red);
    inicializarAnimaciones();
}

void Juego::manejarAtaques(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::R && jugador1->hitbox.getGlobalBounds().intersects(jugador2->rectan.getGlobalBounds()) && !jugador1->isDefending)
    {
        jugador2->recibirAtaque(15.0f, sf::Vector2f(direccion1 * 160.0f, -150.0f));
        jugador1->aumentarEnergia(8.0f);
        verificarDerrota(jugador2, "Jugador 1");
    }
    if (event.key.code == sf::Keyboard::P && jugador2->hitbox.getGlobalBounds().intersects(jugador1->rectan.getGlobalBounds()) && !jugador2->isDefending)
    {
        jugador1->recibirAtaque(15.0f, sf::Vector2f(direccion2 * 175.0f, -150.0f));
        jugador2->aumentarEnergia(10.0f);
        verificarDerrota(jugador1, "Jugador 2");
    }
    if (event.key.code == sf::Keyboard::T  && jugador1->energia==100 && !jugador1->isDefending)
    {
        jugador1->usarUltimate(*jugador2);
        jugador2->recibirAtaque(50.0f, sf::Vector2f(direccion1 * 250.0f, -200.0f));
        verificarDerrota(jugador2, "Jugador 1");
    }
    if (event.key.code == sf::Keyboard::I && jugador2->energia==100)
    {
        jugador2->usarUltimate(*jugador1);
    }
}

void Juego::manejarProyectiles(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Q && !jugador1->isDefending)
    {
        jugador1->lanzarShurikens();
        verificarDerrota(jugador2, "Jugador 1");
    }
    if (event.key.code == sf::Keyboard::O && !jugador2->isDefending)
    {
        jugador2->lanzarShurikens();
        verificarDerrota(jugador1, "Jugador 2");
    }
}

void Juego::actualizar()
{
    tiempoDelta = relojMov.restart().asSeconds();
    // Actualizar movimiento de jugadores
    jugador1->move(tiempoDelta, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::W, piso.rectan.getPosition().y, sf::Keyboard::S);
    jugador2->move(tiempoDelta, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Up, piso.rectan.getPosition().y, sf::Keyboard::Down);

    jugador1->setPosition(jugador1->rectan.getPosition().x,jugador1->rectan.getPosition().y);
    jugador1->updateAnimation(tiempoDelta);

    static_cast<Hanzo*>(jugador1)->actualizarUltimates(tiempoDelta, direccion1); // Actualiza las ultimates de Hanzo


    // Actualizar proyectiles
    jugador1->actualizarShurikens(tiempoDelta, direccion1, *jugador2);
    jugador2->actualizarShurikens(tiempoDelta, direccion2, *jugador1);
}

void Juego::verificarDerrota(Luchador *jugador, const std::string &ganador)
{
    if (jugador->lives == 0)
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
    if (jugador1->health > jugador2->health)
    {
        std::cout << "Jugador 1 gana por salud!" << std::endl;
    }
    else if (jugador2->health > jugador1->health)
    {
        std::cout << "Jugador 2 gana por salud!" << std::endl;
    }
    else
    {
        std::cout << "¡Empate!" << std::endl;
    }
    window.close();
}

void Juego::inicializarAnimaciones() {
        if (!animationsInitialized) {
        if (jugador1->CargarTexture("../assets/anims/hanzo/Idle_Hanzo.png")) {
            jugador1->setTransparentColor(sf::Color(64, 176, 72));
            jugador1->IniciarAnimation(100, 118, 10, 0.1f, true);
            jugador1->playAnimation();  // Aseguramos que la animación está activa
            animationsInitialized = true;
            std::cout << "Animación inicializada correctamente" << std::endl;
        } else {
            std::cerr << "Error al cargar la textura de la animación!" << std::endl;
        }
    }
}

void Juego::ejecutar()
{
    while (window.isOpen())
    {
        procesarEventos();
        actualizar();
        renderizar();

        // Verificar si el tiempo ha terminado
        if (calcularTiempoRestante() <= 0)
        {
            determinarGanador();
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
            direccion1 = (jugador1->rectan.getPosition().x < jugador2->rectan.getPosition().x) ? 1.0f : -1.0f;
            direccion2 = (jugador2->rectan.getPosition().x < jugador1->rectan.getPosition().x) ? 1.0f : -1.0f;
            manejarAtaques(event);
            manejarProyectiles(event);
        }
    }
}

void Juego::renderizar()
{
    window.clear(sf::Color::Blue);

    // Dibujar el escenario
    window.draw(piso.rectan);

    // Dibujar jugadores
    // window.draw(jugador1->rectan);
    window.draw(jugador2->rectan);

    jugador1->draw(window);

    // Dibujar hitboxes (opcional, para depuración)
    // window.draw(jugador1->hitbox);
    // window.draw(jugador2->hitbox);

    // Dibujar barras de salud
    jugador1->drawHealthBar(window, sf::Vector2f(25.0f, 50.0f));
    jugador2->drawHealthBar(window, sf::Vector2f(575.0f, 50.0f));

    jugador1->drawEnergiaBar(window, sf::Vector2f(25.0f, 75.0f));
    jugador2->drawEnergiaBar(window, sf::Vector2f(575.0f, 75.0f));

    // Dibujar proyectiles
    for (auto &shuriken : jugador1->shurikens)
    {
        window.draw(shuriken.forma);
    }
    for (auto &shuriken : jugador2->shurikens)
    {
        window.draw(shuriken.forma);
    }
    for (const auto& ultimate : static_cast<Hanzo*>(jugador1)->ultimates) 
    {
        window.draw(ultimate);
    }

    dibujarTiempoRestante();

    window.display();
}